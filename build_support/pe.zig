const std = @import("std");

const Step = std.Build.Step;
const LazyPath = std.Build.LazyPath;
const GeneratedFile = std.Build.GeneratedFile;

/// Preserve the executable memory policy required by the recovered x86 thunks.
/// Zig 0.16 does not expose LLD's NXCOMPAT setting, so configure a separate
/// cached copy after linking. The linker artifact is never modified.
pub fn configure(b: *std.Build, executable: LazyPath) LazyPath {
    const self = b.allocator.create(ConfigurePe) catch @panic("OOM");
    self.* = .{
        .step = Step.init(.{
            .id = .custom,
            .name = "configure game.exe PE compatibility",
            .owner = b,
            .makeFn = make,
        }),
        .executable = executable.dupe(b),
        .output = .{ .step = &self.step },
    };
    executable.addStepDependencies(&self.step);
    return .{ .generated = .{ .file = &self.output } };
}

const ConfigurePe = struct {
    step: Step,
    executable: LazyPath,
    output: GeneratedFile,
};

fn make(step: *Step, _: Step.MakeOptions) !void {
    const self: *ConfigurePe = @fieldParentPtr("step", step);
    const b = step.owner;
    const io = b.graph.io;
    try step.singleUnchangingWatchInput(self.executable);

    var manifest = b.graph.cache.obtain();
    defer manifest.deinit();
    manifest.hash.addBytes("shaiya-game-decomp-pe32-nxcompat-v1");
    manifest.hash.addBytes(@embedFile("pe.zig"));
    const input = self.executable.getPath2(b, step);
    _ = try manifest.addFile(input, null);
    const hit = try step.cacheHit(&manifest);
    const digest = manifest.final();
    const directory = b.pathJoin(&.{ "o", &digest });
    const sub_path = b.pathJoin(&.{ directory, "game.exe" });
    self.output.path = try b.cache_root.join(b.allocator, &.{sub_path});
    if (hit) return;

    const bytes = try std.Io.Dir.cwd().readFileAlloc(io, input, b.allocator, .limited(512 * 1024 * 1024));
    defer b.allocator.free(bytes);
    clearNxCompatibility(bytes) catch |err| {
        return step.fail("refusing to configure invalid client PE '{s}': {t}", .{ input, err });
    };
    try b.cache_root.handle.createDirPath(io, directory);
    try b.cache_root.handle.writeFile(io, .{ .sub_path = sub_path, .data = bytes });
    try step.writeManifest(&manifest);
}

pub const PeError = error{
    TruncatedPe,
    InvalidDosSignature,
    InvalidPeSignature,
    UnsupportedMachine,
    UnsupportedOptionalHeader,
    InvalidEntryPoint,
    InvalidSubsystem,
};

/// Clear only IMAGE_DLLCHARACTERISTICS_NX_COMPAT in a valid x86 GUI PE32.
/// All validation completes before modifying the supplied bytes.
pub fn clearNxCompatibility(bytes: []u8) PeError!void {
    if (bytes.len < 0x40) return error.TruncatedPe;
    if (!std.mem.eql(u8, bytes[0..2], "MZ")) return error.InvalidDosSignature;
    const pe: usize = readU32(bytes, 0x3c);
    if (pe < 0x40 or pe > bytes.len - 24) return error.TruncatedPe;
    if (!std.mem.eql(u8, bytes[pe..][0..4], "PE\x00\x00")) return error.InvalidPeSignature;
    if (readU16(bytes, pe + 4) != 0x014c) return error.UnsupportedMachine;
    const optional = pe + 24;
    const optional_size: usize = readU16(bytes, pe + 20);
    if (optional_size < 96 or optional_size > bytes.len - optional) return error.TruncatedPe;
    if (readU16(bytes, optional) != 0x010b) return error.UnsupportedOptionalHeader;
    const entry = readU32(bytes, optional + 16);
    const image_size = readU32(bytes, optional + 56);
    if (entry == 0 or entry >= image_size) return error.InvalidEntryPoint;
    if (readU16(bytes, optional + 68) != 2) return error.InvalidSubsystem;
    const characteristics = optional + 70;
    const flags = readU16(bytes, characteristics);
    std.mem.writeInt(u16, bytes[characteristics..][0..2], flags & ~@as(u16, 0x0100), .little);
}

fn readU16(bytes: []const u8, offset: usize) u16 {
    return std.mem.readInt(u16, bytes[offset..][0..2], .little);
}

fn readU32(bytes: []const u8, offset: usize) u32 {
    return std.mem.readInt(u32, bytes[offset..][0..4], .little);
}

fn fixture() [512]u8 {
    var bytes = [_]u8{0} ** 512;
    @memcpy(bytes[0..2], "MZ");
    std.mem.writeInt(u32, bytes[0x3c..][0..4], 0x80, .little);
    @memcpy(bytes[0x80..][0..4], "PE\x00\x00");
    std.mem.writeInt(u16, bytes[0x84..][0..2], 0x014c, .little);
    std.mem.writeInt(u16, bytes[0x94..][0..2], 224, .little);
    std.mem.writeInt(u16, bytes[0x98..][0..2], 0x010b, .little);
    std.mem.writeInt(u32, bytes[0xa8..][0..4], 0x1000, .little);
    std.mem.writeInt(u32, bytes[0xd0..][0..4], 0x3000, .little);
    std.mem.writeInt(u16, bytes[0xdc..][0..2], 2, .little);
    std.mem.writeInt(u16, bytes[0xde..][0..2], 0x8140, .little);
    return bytes;
}

test "PE compatibility clears exactly the NX bit and is idempotent" {
    var bytes = fixture();
    const before = bytes;
    try clearNxCompatibility(&bytes);
    for (bytes, before, 0..) |actual, original, index| {
        try std.testing.expectEqual(if (index == 0xdf) original ^ @as(u8, 1) else original, actual);
    }
    const configured = bytes;
    try clearNxCompatibility(&bytes);
    try std.testing.expectEqualSlices(u8, &configured, &bytes);
}

test "malformed PE is rejected without changing its bytes" {
    var bytes = fixture();
    bytes[0x84] = 0x64;
    const before = bytes;
    try std.testing.expectError(error.UnsupportedMachine, clearNxCompatibility(&bytes));
    try std.testing.expectEqualSlices(u8, &before, &bytes);

    bytes = fixture();
    try std.testing.expectError(error.TruncatedPe, clearNxCompatibility(bytes[0..0x100]));
    bytes[0] = 0;
    try std.testing.expectError(error.InvalidDosSignature, clearNxCompatibility(&bytes));
    bytes = fixture();
    bytes[0x80] = 0;
    try std.testing.expectError(error.InvalidPeSignature, clearNxCompatibility(&bytes));
    bytes = fixture();
    std.mem.writeInt(u32, bytes[0x3c..][0..4], 0xffffffff, .little);
    try std.testing.expectError(error.TruncatedPe, clearNxCompatibility(&bytes));
    bytes = fixture();
    bytes[0x98] = 0x0c;
    try std.testing.expectError(error.UnsupportedOptionalHeader, clearNxCompatibility(&bytes));
    bytes = fixture();
    @memset(bytes[0xa8..][0..4], 0);
    try std.testing.expectError(error.InvalidEntryPoint, clearNxCompatibility(&bytes));
    bytes = fixture();
    bytes[0xdc] = 3;
    try std.testing.expectError(error.InvalidSubsystem, clearNxCompatibility(&bytes));
}
