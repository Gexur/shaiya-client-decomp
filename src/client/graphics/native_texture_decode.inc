// Native asset decoding: zigrebuild/src/assets/{texture,dds}.zig and
// zigrebuild/src/graphics/{texture_quality,wic}.zig are the algorithm sources.
void color16(const unsigned char* sample, bool alpha, unsigned char* rgba) {
    UINT value = read16(sample);
    for (UINT channel = 0; channel < 3; ++channel) {
        UINT bits = (value >> (10 - channel * 5)) & 31;
        rgba[channel] = static_cast<unsigned char>((bits << 3) | (bits >> 2));
    }
    rgba[3] = alpha && !(value & 0x8000) ? 0 : 255;
}
void tga_color(const unsigned char* sample, UINT depth, bool alpha, unsigned char* rgba) {
    if (depth == 15 || depth == 16)
        color16(sample, alpha, rgba);
    else {
        rgba[0] = sample[2];
        rgba[1] = sample[1];
        rgba[2] = sample[0];
        rgba[3] = depth == 32 && alpha ? sample[3] : 255;
    }
}
HRESULT decode_tga(const unsigned char* bytes, size_t size, Image& image) {
    if (size < 18)
        return E_INVALIDARG;
    UINT map = bytes[1], type = bytes[2], base = type & 7, depth = bytes[16];
    UINT map_first = read16(bytes + 3), map_length = read16(bytes + 5), map_depth = bytes[7],
         descriptor = bytes[17];
    if (type > 11 || (base != 1 && base != 2 && base != 3) || map > 1 || (base == 1 && map != 1) ||
        (descriptor & 0xc0) || (base == 1 && depth != 8 && depth != 16) ||
        (base == 2 && depth != 15 && depth != 16 && depth != 24 && depth != 32) ||
        (base == 3 && depth != 8 && depth != 16) ||
        (map && map_depth != 15 && map_depth != 16 && map_depth != 24 && map_depth != 32))
        return E_INVALIDARG;
    Cursor cursor{bytes, size, 18};
    UINT map_stride = (map_depth + 7) / 8, stride = (depth + 7) / 8;
    if (!cursor.take(bytes[0]))
        return E_INVALIDARG;
    const auto* palette = map ? cursor.take(size_t(map_length) * map_stride) : nullptr;
    if (map && !palette)
        return E_INVALIDARG;
    HRESULT result = image.initialize(read16(bytes + 12), read16(bytes + 14));
    if (FAILED(result))
        return result;
    UINT count = image.width * image.height, index = 0;
    while (index < count) {
        UINT packet = 0;
        if (type & 8) {
            const auto* header = cursor.take(1);
            if (!header)
                return E_INVALIDARG;
            packet = *header;
        }
        UINT length = type & 8 ? (packet & 127) + 1 : 1;
        bool repeated = (type & 8) && (packet & 128);
        if (length > count - index)
            return E_INVALIDARG;
        const auto* repeat = repeated ? cursor.take(stride) : nullptr;
        if (repeated && !repeat)
            return E_INVALIDARG;
        for (UINT i = 0; i < length; ++i, ++index) {
            const auto* sample = repeated ? repeat : cursor.take(stride);
            if (!sample)
                return E_INVALIDARG;
            unsigned char rgba[4];
            if (base == 1) {
                UINT entry = depth == 8 ? sample[0] : read16(sample);
                if (entry < map_first || entry - map_first >= map_length)
                    return E_INVALIDARG;
                tga_color(palette + (entry - map_first) * map_stride, map_depth,
                          map_depth == 16 || map_depth == 32, rgba);
            } else if (base == 2)
                tga_color(sample, depth, (descriptor & 15) != 0, rgba);
            else {
                rgba[0] = rgba[1] = rgba[2] = sample[0];
                rgba[3] = depth == 16 ? sample[1] : 255;
            }
            UINT x = index % image.width, y = index / image.width;
            if (descriptor & 16)
                x = image.width - 1 - x;
            if (!(descriptor & 32))
                y = image.height - 1 - y;
            copy_bytes(image.pixels + (size_t(y) * image.width + x) * 4, rgba, 4);
        }
    }
    return S_OK;
}
HRESULT decode_bmp(const unsigned char* bytes, size_t size, Image& image) {
    if (size < 54 || bytes[0] != 'B' || bytes[1] != 'M')
        return E_INVALIDARG;
    UINT offset = read32(bytes + 10), header = read32(bytes + 14), depth = read16(bytes + 28);
    int width = static_cast<int>(read32(bytes + 18)),
        signed_height = static_cast<int>(read32(bytes + 22));
    if (header < 40 || read16(bytes + 26) != 1 || read32(bytes + 30) != 0 || width <= 0 ||
        width > int(maximum_dimension) || signed_height == 0 ||
        signed_height < -int(maximum_dimension) || signed_height > int(maximum_dimension) ||
        (depth != 8 && depth != 16 && depth != 24 && depth != 32))
        return E_INVALIDARG;
    UINT height = UINT(signed_height < 0 ? -signed_height : signed_height),
         pitch = ((UINT(width) * depth + 31) / 32) * 4;
    if (offset > size || size_t(pitch) * height > size - offset)
        return E_INVALIDARG;
    HRESULT result = image.initialize(UINT(width), height);
    if (FAILED(result))
        return result;
    for (UINT y = 0; y < height; ++y) {
        const auto* row = bytes + offset + size_t(signed_height < 0 ? y : height - 1 - y) * pitch;
        for (UINT x = 0; x < UINT(width); ++x) {
            const auto* sample = row + x * (depth / 8);
            auto* rgba = image.pixels + (size_t(y) * width + x) * 4;
            if (depth == 8) {
                size_t entry = size_t(14) + header + UINT(sample[0]) * 4;
                if (entry > size || 4 > size - entry || entry + 4 > offset)
                    return E_INVALIDARG;
                sample = bytes + entry;
            }
            if (depth == 16)
                color16(sample, false, rgba);
            else {
                rgba[0] = sample[2];
                rgba[1] = sample[1];
                rgba[2] = sample[0];
                rgba[3] = 255;
            }
        }
    }
    return S_OK;
}
HRESULT decode_wic(const unsigned char* bytes, size_t size, Image& image) {
    if (!size || size > 0xffffffffu)
        return E_INVALIDARG;
    const GUID factory_class = {
        0xcacaf262, 0x9370, 0x4615, {0xa1, 0x3b, 0x9f, 0x55, 0x39, 0xda, 0x4c, 0x0a}};
    const GUID factory_interface = {
        0xec5ec8a9, 0xc395, 0x4314, {0x9c, 0x77, 0x54, 0xd7, 0xa9, 0x35, 0xff, 0x70}};
    const GUID rgba = {
        0xf5c7ad2d, 0x6a8d, 0x43dd, {0xa7, 0xa8, 0xa2, 0x99, 0x35, 0x26, 0x1a, 0xe9}};
    HRESULT initialized = CoInitializeEx(nullptr, COINIT_MULTITHREADED);
    if (FAILED(initialized) && initialized != RPC_E_CHANGED_MODE)
        return initialized;
    IWICImagingFactory* factory = nullptr;
    IWICStream* stream = nullptr;
    IWICBitmapDecoder* decoder = nullptr;
    IWICBitmapFrameDecode* frame = nullptr;
    IWICFormatConverter* converter = nullptr;
    HRESULT result = CoCreateInstance(factory_class, nullptr, CLSCTX_INPROC_SERVER,
                                      factory_interface, reinterpret_cast<void**>(&factory));
    if (SUCCEEDED(result))
        result = factory->CreateStream(&stream);
    if (SUCCEEDED(result))
        result = stream->InitializeFromMemory(const_cast<BYTE*>(bytes), UINT(size));
    if (SUCCEEDED(result))
        result = factory->CreateDecoderFromStream(stream, nullptr, WICDecodeMetadataCacheOnLoad,
                                                  &decoder);
    if (SUCCEEDED(result))
        result = decoder->GetFrame(0, &frame);
    UINT width = 0, height = 0;
    if (SUCCEEDED(result))
        result = frame->GetSize(&width, &height);
    if (SUCCEEDED(result))
        result = image.initialize(width, height);
    if (SUCCEEDED(result))
        result = factory->CreateFormatConverter(&converter);
    if (SUCCEEDED(result))
        result = converter->Initialize(frame, rgba, WICBitmapDitherTypeNone, nullptr, 0,
                                       WICBitmapPaletteTypeCustom);
    if (SUCCEEDED(result))
        result = converter->CopyPixels(nullptr, width * 4, width * height * 4, image.pixels);
    release_gpu(converter);
    release_gpu(frame);
    release_gpu(decoder);
    release_gpu(stream);
    release_gpu(factory);
    if (SUCCEEDED(initialized))
        CoUninitialize();
    return result;
}
struct Dds {
    UINT width = 0, height = 0, levels = 0, bits = 0, masks[4] = {};
    DXGI_FORMAT format = DXGI_FORMAT_UNKNOWN;
    bool premultiplied = false, cpu_supported = true;
    TextureMip mips[maximum_levels] = {};
};
HRESULT parse_dds(const unsigned char* bytes, size_t size, Dds& dds) {
    if (size < 128 || read32(bytes) != 0x20534444 || read32(bytes + 4) != 124 ||
        read32(bytes + 76) != 32)
        return E_INVALIDARG;
    dds.width = read32(bytes + 16);
    dds.height = read32(bytes + 12);
    dds.levels = read32(bytes + 28);
    if (!dds.levels)
        dds.levels = 1;
    if (!valid_dimensions(dds.width, dds.height) || dds.levels > mip_count(dds.width, dds.height) ||
        (read32(bytes + 112) & 0x20fe00) || read32(bytes + 24) > 1)
        return E_INVALIDARG;
    UINT flags = read32(bytes + 80), fourcc = read32(bytes + 84);
    size_t offset = 128;
    dds.bits = read32(bytes + 88);
    for (UINT c = 0; c < 4; ++c)
        dds.masks[c] = read32(bytes + 92 + c * 4);
    if (flags & 4) {
        switch (fourcc) {
        case 0x31545844:
            dds.format = DXGI_FORMAT_BC1_UNORM;
            break;
        case 0x32545844:
        case 0x33545844:
            dds.format = DXGI_FORMAT_BC2_UNORM;
            dds.premultiplied = fourcc == 0x32545844;
            break;
        case 0x34545844:
        case 0x35545844:
            dds.format = DXGI_FORMAT_BC3_UNORM;
            dds.premultiplied = fourcc == 0x34545844;
            break;
        case 0x31495441:
        case 0x55344342:
            dds.format = DXGI_FORMAT_BC4_UNORM;
            break;
        case 0x32495441:
        case 0x55354342:
            dds.format = DXGI_FORMAT_BC5_UNORM;
            break;
        case 0x30315844:
            if (size < 148 || read32(bytes + 132) != 3 || read32(bytes + 140) != 1 ||
                (read32(bytes + 136) & 4))
                return E_INVALIDARG;
            dds.format = static_cast<DXGI_FORMAT>(read32(bytes + 128));
            offset = 148;
            if (!block_size(dds.format) && !pixel_size(dds.format))
                return E_NOTIMPL;
            dds.bits = pixel_size(dds.format) * 8;
            for (auto& mask : dds.masks)
                mask = 0;
            if (block_size(dds.format))
                break;
            switch (dds.format) {
            case DXGI_FORMAT_R8G8B8A8_UNORM:
            case DXGI_FORMAT_R8G8B8A8_UNORM_SRGB:
                dds.masks[0] = 0xff;
                dds.masks[1] = 0xff00;
                dds.masks[2] = 0xff0000;
                dds.masks[3] = 0xff000000;
                break;
            case DXGI_FORMAT_B8G8R8A8_UNORM:
            case DXGI_FORMAT_B8G8R8A8_UNORM_SRGB:
            case DXGI_FORMAT_B8G8R8X8_UNORM:
            case DXGI_FORMAT_B8G8R8X8_UNORM_SRGB:
                dds.masks[0] = 0xff0000;
                dds.masks[1] = 0xff00;
                dds.masks[2] = 0xff;
                if (dds.format == DXGI_FORMAT_B8G8R8A8_UNORM ||
                    dds.format == DXGI_FORMAT_B8G8R8A8_UNORM_SRGB)
                    dds.masks[3] = 0xff000000;
                break;
            case DXGI_FORMAT_R8_UNORM:
            case DXGI_FORMAT_R16_UNORM:
                dds.masks[0] = dds.bits == 8 ? 0xff : 0xffff;
                break;
            case DXGI_FORMAT_A8_UNORM:
                dds.masks[3] = 0xff;
                break;
            default:
                dds.cpu_supported = false;
                break;
            }
            break;
        default:
            return E_NOTIMPL;
        }
    } else {
        if (!(flags & (0x40 | 0x20000 | 2)) ||
            (dds.bits != 8 && dds.bits != 16 && dds.bits != 24 && dds.bits != 32))
            return E_NOTIMPL;
        if (dds.bits == 32 && dds.masks[0] == 0xff && dds.masks[1] == 0xff00 &&
            dds.masks[2] == 0xff0000 && dds.masks[3] == 0xff000000)
            dds.format = DXGI_FORMAT_R8G8B8A8_UNORM;
        if (dds.bits == 32 && dds.masks[0] == 0xff0000 && dds.masks[1] == 0xff00 &&
            dds.masks[2] == 0xff)
            dds.format = dds.masks[3] == 0xff000000 ? DXGI_FORMAT_B8G8R8A8_UNORM
                         : dds.masks[3] == 0        ? DXGI_FORMAT_B8G8R8X8_UNORM
                                                    : DXGI_FORMAT_UNKNOWN;
    }
    UINT width = dds.width, height = dds.height, block = block_size(dds.format);
    for (UINT level = 0; level < dds.levels; ++level) {
        UINT pitch = block ? ((width + 3) / 4) * block : (width * dds.bits + 7) / 8,
             rows = block ? (height + 3) / 4 : height;
        size_t length = size_t(pitch) * rows;
        if (!pitch || offset > size || length > size - offset || length > 0xffffffffu)
            return E_INVALIDARG;
        dds.mips[level] = {bytes + offset, pitch, UINT(length)};
        offset += length;
        width = half(width);
        height = half(height);
    }
    return S_OK;
}
void rgb565(UINT value, unsigned char* rgba) {
    UINT r = (value >> 11) & 31, g = (value >> 5) & 63, b = value & 31;
    rgba[0] = static_cast<unsigned char>((r << 3) | (r >> 2));
    rgba[1] = static_cast<unsigned char>((g << 2) | (g >> 4));
    rgba[2] = static_cast<unsigned char>((b << 3) | (b >> 2));
    rgba[3] = 255;
}
void decode_block(const unsigned char* bytes, DXGI_FORMAT format, unsigned char rgba[16][4]) {
    bool bc1 = format == DXGI_FORMAT_BC1_UNORM || format == DXGI_FORMAT_BC1_UNORM_SRGB;
    bool bc2 = format == DXGI_FORMAT_BC2_UNORM || format == DXGI_FORMAT_BC2_UNORM_SRGB;
    const auto* colors = bytes + (bc1 ? 0 : 8);
    UINT first = read16(colors), second = read16(colors + 2);
    unsigned char palette[4][4] = {};
    rgb565(first, palette[0]);
    rgb565(second, palette[1]);
    bool four = !bc1 || first > second;
    for (UINT c = 0; c < 3; ++c) {
        UINT a = palette[0][c], b = palette[1][c];
        palette[2][c] = static_cast<unsigned char>(four ? (2 * a + b) / 3 : (a + b) / 2);
        palette[3][c] = static_cast<unsigned char>(four ? (a + 2 * b) / 3 : 0);
    }
    palette[2][3] = 255;
    palette[3][3] = four ? 255 : 0;
    UINT selectors = read32(colors + 4);
    for (UINT index = 0; index < 16; ++index) {
        copy_bytes(rgba[index], palette[selectors & 3], 4);
        selectors >>= 2;
    }
    if (bc2) {
        for (UINT i = 0; i < 16; ++i)
            rgba[i][3] = static_cast<unsigned char>(((bytes[i / 2] >> ((i & 1) * 4)) & 15) * 17);
    } else if (!bc1) {
        unsigned char alpha[8] = {bytes[0], bytes[1], 0, 0, 0, 0, 0, 255};
        if (alpha[0] > alpha[1]) {
            for (UINT i = 2; i < 8; ++i)
                alpha[i] =
                    static_cast<unsigned char>(((8 - i) * alpha[0] + (i - 1) * alpha[1]) / 7);
        } else
            for (UINT i = 2; i < 6; ++i)
                alpha[i] =
                    static_cast<unsigned char>(((6 - i) * alpha[0] + (i - 1) * alpha[1]) / 5);
        for (UINT i = 0; i < 16; ++i) {
            UINT bit = i * 3, byte = 2 + bit / 8, shift = bit & 7, selector = bytes[byte] >> shift;
            if (shift > 5)
                selector |= UINT(bytes[byte + 1]) << (8 - shift);
            rgba[i][3] = alpha[selector & 7];
        }
    }
}
HRESULT decode_dds_level(const Dds& dds, UINT level, Image& image) {
    if (!dds.cpu_supported)
        return E_NOTIMPL;
    UINT width = dds.width, height = dds.height;
    for (UINT i = 0; i < level; ++i) {
        width = half(width);
        height = half(height);
    }
    UINT block = block_size(dds.format);
    if (block && dds.format != DXGI_FORMAT_BC1_UNORM && dds.format != DXGI_FORMAT_BC1_UNORM_SRGB &&
        dds.format != DXGI_FORMAT_BC2_UNORM && dds.format != DXGI_FORMAT_BC2_UNORM_SRGB &&
        dds.format != DXGI_FORMAT_BC3_UNORM && dds.format != DXGI_FORMAT_BC3_UNORM_SRGB)
        return E_NOTIMPL;
    HRESULT result = image.initialize(width, height);
    if (FAILED(result))
        return result;
    const auto* source = static_cast<const unsigned char*>(dds.mips[level].bytes);
    if (block) {
        for (UINT y = 0; y < (height + 3) / 4; ++y)
            for (UINT x = 0; x < (width + 3) / 4; ++x) {
                unsigned char rgba[16][4];
                decode_block(source + y * dds.mips[level].row_pitch + x * block, dds.format, rgba);
                for (UINT dy = 0; dy < 4 && y * 4 + dy < height; ++dy)
                    for (UINT dx = 0; dx < 4 && x * 4 + dx < width; ++dx) {
                        auto* color = rgba[dy * 4 + dx];
                        if (dds.premultiplied && color[3])
                            for (UINT c = 0; c < 3; ++c)
                                color[c] = static_cast<unsigned char>(
                                    smaller(255, UINT(color[c]) * 255 / color[3]));
                        copy_bytes(image.pixels + (size_t(y * 4 + dy) * width + x * 4 + dx) * 4,
                                   color, 4);
                    }
            }
        return S_OK;
    }
    for (UINT y = 0; y < height; ++y)
        for (UINT x = 0; x < width; ++x) {
            const auto* sample = source + y * dds.mips[level].row_pitch + x * (dds.bits / 8);
            auto* color = image.pixels + (size_t(y) * width + x) * 4;
            UINT value = 0;
            for (UINT byte = 0; byte < dds.bits / 8; ++byte)
                value |= UINT(sample[byte]) << (byte * 8);
            color[0] = color[1] = color[2] = 0;
            color[3] = 255;
            for (UINT channel = 0; channel < 4; ++channel) {
                UINT mask = dds.masks[channel];
                if (!mask)
                    continue;
                UINT shift = 0;
                while (!(mask & 1)) {
                    mask >>= 1;
                    ++shift;
                }
                color[channel] = static_cast<unsigned char>(
                    divide_channel(uint64_t((value >> shift) & mask) * 255 + mask / 2, mask));
            }
            if (!dds.masks[1] && !dds.masks[2])
                color[1] = color[2] = color[0];
        }
    return S_OK;
}
float triangle_integral(float value) {
    if (value <= -1)
        return 0;
    if (value <= 0)
        return .5f * (value + 1) * (value + 1);
    if (value < 1)
        return 1 - .5f * (1 - value) * (1 - value);
    return 1;
}
int floor_integer(float value) {
    int result = int(value);
    return float(result) > value ? result - 1 : result;
}
int ceil_integer(float value) {
    int result = int(value);
    return float(result) < value ? result + 1 : result;
}
UINT wrapped(int value, UINT size) {
    int result = value % int(size);
    return UINT(result < 0 ? result + int(size) : result);
}
HRESULT resize_triangle(const Image& source, UINT width, UINT height, Image& image) {
    HRESULT result = image.initialize(width, height);
    if (FAILED(result))
        return result;
    auto* horizontal =
        static_cast<float*>(allocate(size_t(width) * source.height * 4 * sizeof(float)));
    if (!horizontal)
        return E_OUTOFMEMORY;
    float ratio = float(source.width) / float(width);
    for (UINT y = 0; y < source.height; ++y)
        for (UINT x = 0; x < width; ++x) {
            float center = (float(x) + .5f) * ratio - .5f, sum[4] = {};
            int last = ceil_integer(center + ratio * .5f + 1);
            for (int i = floor_integer(center - ratio * .5f - 1); i <= last; ++i) {
                float weight = (triangle_integral(center + ratio * .5f - float(i)) -
                                triangle_integral(center - ratio * .5f - float(i))) /
                               ratio;
                const auto* pixel =
                    source.pixels + (size_t(y) * source.width + wrapped(i, source.width)) * 4;
                for (UINT c = 0; c < 4; ++c)
                    sum[c] += pixel[c] * weight;
            }
            copy_bytes(horizontal + (size_t(y) * width + x) * 4, sum, sizeof(sum));
        }
    ratio = float(source.height) / float(height);
    for (UINT y = 0; y < height; ++y)
        for (UINT x = 0; x < width; ++x) {
            float center = (float(y) + .5f) * ratio - .5f, sum[4] = {};
            int last = ceil_integer(center + ratio * .5f + 1);
            for (int i = floor_integer(center - ratio * .5f - 1); i <= last; ++i) {
                float weight = (triangle_integral(center + ratio * .5f - float(i)) -
                                triangle_integral(center - ratio * .5f - float(i))) /
                               ratio;
                const auto* pixel =
                    horizontal + (size_t(wrapped(i, source.height)) * width + x) * 4;
                for (UINT c = 0; c < 4; ++c)
                    sum[c] += pixel[c] * weight;
            }
            for (UINT c = 0; c < 4; ++c)
                image.pixels[(size_t(y) * width + x) * 4 + c] =
                    static_cast<unsigned char>(sum[c] <= 0     ? 0
                                               : sum[c] >= 255 ? 255
                                                               : UINT(sum[c] + .5f));
        }
    free_bytes(horizontal);
    return S_OK;
}
HRESULT box_mip(const Image& source, Image& image) {
    HRESULT result = image.initialize(half(source.width), half(source.height));
    if (FAILED(result))
        return result;
    for (UINT y = 0; y < image.height; ++y)
        for (UINT x = 0; x < image.width; ++x)
            for (UINT channel = 0; channel < 4; ++channel) {
                UINT sum = 0;
                for (UINT dy = 0; dy < 2; ++dy)
                    for (UINT dx = 0; dx < 2; ++dx)
                        sum += source.pixels[(size_t(smaller(source.height - 1, y * 2 + dy)) *
                                                  source.width +
                                              smaller(source.width - 1, x * 2 + dx)) *
                                                 4 +
                                             channel];
                image.pixels[(size_t(y) * image.width + x) * 4 + channel] =
                    static_cast<unsigned char>((sum + 2) / 4);
            }
    return S_OK;
}
void apply_color_key(Image& image, UINT color) {
    UINT rgb = color & 0xffffff;
    for (size_t i = 0, count = size_t(image.width) * image.height; i < count; ++i) {
        auto* pixel = image.pixels + i * 4;
        if ((UINT(pixel[0]) << 16 | UINT(pixel[1]) << 8 | pixel[2]) == rgb)
            pixel[3] = 0;
    }
}
