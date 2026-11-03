//! Keep the editable resource catalog authoritative while retaining exact image
//! IDs, cursor hotspots, language IDs and binary VERSIONINFO payloads.
const std = @import("std");

const Allocator = std.mem.Allocator;
const resource_directory = "src/client/resources/";

const Catalog = struct {
    schema_version: u32,
    resources: []Resource,
};

const Resource = struct {
    type: u16,
    id: u16,
    language: u16,
    codepage: u32,
    reserved: u32 = 0,
    asset: []const u8,
    format: enum { binary, icon, cursor },
};

/// Create a standard Win32 RES container from the catalog and editable assets.
/// The bytes themselves form the generated-file cache key, so asset edits
/// invalidate resource compilation and the final executable automatically.
pub fn generate(b: *std.Build) std.Build.LazyPath {
    const manifest = b.build_root.handle.readFileAlloc(
        b.graph.io,
        resource_directory ++ "manifest.json",
        b.allocator,
        .limited(1024 * 1024),
    ) catch |err| std.debug.panic("cannot read client resource catalog: {s}", .{@errorName(err)});
    const catalog = std.json.parseFromSlice(Catalog, b.allocator, manifest, .{
        .ignore_unknown_fields = true,
    }) catch |err| std.debug.panic("invalid client resource catalog: {s}", .{@errorName(err)});
    validateCatalog(catalog.value) catch |err|
        std.debug.panic("invalid client resource catalog: {s}", .{@errorName(err)});
    std.mem.sort(Resource, catalog.value.resources, {}, lessThan);

    var bytes: std.ArrayList(u8) = .empty;
    bytes.appendSlice(b.allocator, &header(0, 0, 0, 0, 0)) catch @panic("OOM");
    for (catalog.value.resources) |resource| {
        const path = b.fmt(resource_directory ++ "{s}", .{resource.asset});
        const asset = b.build_root.handle.readFileAlloc(
            b.graph.io,
            path,
            b.allocator,
            .limited(64 * 1024 * 1024),
        ) catch |err| std.debug.panic("cannot read client resource '{s}': {s}", .{ path, @errorName(err) });
        const payload = assetPayload(b.allocator, resource, asset) catch |err|
            std.debug.panic("invalid client resource '{s}': {s}", .{ path, @errorName(err) });
        appendResource(b.allocator, &bytes, resource, payload) catch @panic("OOM");
    }
    return b.addWriteFiles().add("client_resources.res", bytes.items);
}

fn validateCatalog(catalog: Catalog) !void {
    if (catalog.schema_version != 1) return error.UnsupportedResourceSchema;
    if (catalog.resources.len == 0) return error.EmptyResourceCatalog;
    for (catalog.resources, 0..) |resource, index| {
        if (resource.codepage != 0 or resource.reserved != 0)
            return error.UnsupportedResourceMetadata;
        // Catalog assets are simple basenames inside the committed directory.
        if (resource.asset.len == 0 or std.mem.eql(u8, resource.asset, ".") or
            std.mem.eql(u8, resource.asset, "..") or
            std.mem.indexOfAny(u8, resource.asset, "/\\:") != null)
            return error.InvalidResourceAssetPath;
        for (catalog.resources[0..index]) |previous| {
            if (resource.type == previous.type and resource.id == previous.id and
                resource.language == previous.language)
                return error.DuplicateResourceIdentity;
        }
    }
}

fn lessThan(_: void, left: Resource, right: Resource) bool {
    if (left.type != right.type) return left.type < right.type;
    if (left.id != right.id) return left.id < right.id;
    return left.language < right.language;
}

fn assetPayload(allocator: Allocator, resource: Resource, asset: []const u8) ![]const u8 {
    if (resource.format == .binary) return asset;
    if (asset.len < 22) return error.TruncatedImageContainer;
    const image_type: u16 = if (resource.format == .cursor) 2 else 1;
    if (std.mem.readInt(u16, asset[0..2], .little) != 0 or
        std.mem.readInt(u16, asset[2..4], .little) != image_type or
        std.mem.readInt(u16, asset[4..6], .little) != 1)
        return error.ExpectedSingleImageContainer;
    const size = std.mem.readInt(u32, asset[14..18], .little);
    const start = std.mem.readInt(u32, asset[18..22], .little);
    if (start < 22 or size == 0 or start > asset.len or size > asset.len - start)
        return error.InvalidImageRange;
    const image = asset[start..][0..size];
    if (resource.format == .icon) return image;
    // RT_CURSOR begins with its x/y hotspot followed by image bytes.
    return std.mem.concat(allocator, u8, &.{ asset[10..14], image });
}

fn appendResource(allocator: Allocator, bytes: *std.ArrayList(u8), resource: Resource, payload: []const u8) !void {
    try bytes.appendSlice(allocator, &header(@intCast(payload.len), resource.type, resource.id, resource.language, 0x30));
    try bytes.appendSlice(allocator, payload);
    try bytes.appendNTimes(allocator, 0, (4 - payload.len % 4) % 4);
}

fn header(size: u32, kind: u16, id: u16, language: u16, flags: u16) [32]u8 {
    var bytes: [32]u8 = @splat(0);
    std.mem.writeInt(u32, bytes[0..4], size, .little);
    std.mem.writeInt(u32, bytes[4..8], 32, .little);
    std.mem.writeInt(u16, bytes[8..10], 0xffff, .little);
    std.mem.writeInt(u16, bytes[10..12], kind, .little);
    std.mem.writeInt(u16, bytes[12..14], 0xffff, .little);
    std.mem.writeInt(u16, bytes[14..16], id, .little);
    std.mem.writeInt(u16, bytes[20..22], flags, .little);
    std.mem.writeInt(u16, bytes[22..24], language, .little);
    return bytes;
}

test "cursor hotspot and image offset are retained" {
    const resource: Resource = .{ .type = 1, .id = 7, .language = 1042, .codepage = 0, .asset = "test.cur", .format = .cursor };
    var asset: [28]u8 = @splat(0);
    std.mem.writeInt(u16, asset[2..4], 2, .little);
    std.mem.writeInt(u16, asset[4..6], 1, .little);
    std.mem.writeInt(u16, asset[10..12], 3, .little);
    std.mem.writeInt(u16, asset[12..14], 9, .little);
    std.mem.writeInt(u32, asset[14..18], 3, .little);
    std.mem.writeInt(u32, asset[18..22], 25, .little);
    @memcpy(asset[25..28], "DIB");
    const payload = try assetPayload(std.testing.allocator, resource, &asset);
    defer std.testing.allocator.free(payload);
    try std.testing.expectEqualSlices(u8, &.{ 3, 0, 9, 0, 'D', 'I', 'B' }, payload);

    var bytes: std.ArrayList(u8) = .empty;
    defer bytes.deinit(std.testing.allocator);
    try appendResource(std.testing.allocator, &bytes, resource, payload);
    try std.testing.expectEqual(@as(usize, 40), bytes.items.len);
    try std.testing.expectEqual(@as(u32, 7), std.mem.readInt(u32, bytes.items[0..4], .little));
    try std.testing.expectEqual(@as(u16, 1042), std.mem.readInt(u16, bytes.items[22..24], .little));
    try std.testing.expectEqual(@as(u8, 0), bytes.items[39]);
}

test "image containers reject truncated or out of range payloads" {
    const resource: Resource = .{ .type = 3, .id = 8, .language = 1042, .codepage = 0, .asset = "test.ico", .format = .icon };
    try std.testing.expectError(error.TruncatedImageContainer, assetPayload(std.testing.allocator, resource, "short"));
    var asset: [22]u8 = @splat(0);
    std.mem.writeInt(u16, asset[2..4], 1, .little);
    std.mem.writeInt(u16, asset[4..6], 1, .little);
    std.mem.writeInt(u32, asset[14..18], 1, .little);
    std.mem.writeInt(u32, asset[18..22], 22, .little);
    try std.testing.expectError(error.InvalidImageRange, assetPayload(std.testing.allocator, resource, &asset));
}

test "catalog rejects duplicate identities and asset traversal" {
    var entries = [_]Resource{
        .{ .type = 16, .id = 1, .language = 1042, .codepage = 0, .asset = "version.bin", .format = .binary },
        .{ .type = 16, .id = 1, .language = 1042, .codepage = 0, .asset = "version.bin", .format = .binary },
    };
    try std.testing.expectError(error.DuplicateResourceIdentity, validateCatalog(.{ .schema_version = 1, .resources = &entries }));
    entries[1].id = 2;
    entries[1].asset = "../version.bin";
    try std.testing.expectError(error.InvalidResourceAssetPath, validateCatalog(.{ .schema_version = 1, .resources = &entries }));
}
