const std = @import("std");
const resources = @import("build_support/resources.zig");
const pe = @import("build_support/pe.zig");

pub fn build(b: *std.Build) void {
    const target = b.standardTargetOptions(.{
        .default_target = .{ .cpu_arch = .x86, .os_tag = .windows, .abi = .gnu },
    });
    if (target.result.cpu.arch != .x86 or target.result.os.tag != .windows or target.result.abi != .gnu)
        @panic("The recovered client requires -Dtarget=x86-windows-gnu (32-bit pointers and x86 calling conventions).");
    const optimize = b.option(std.builtin.OptimizeMode, "optimize", "Optimization mode (default ReleaseFast, using the recovered build's -O2)") orelse .ReleaseFast;
    const assets = b.option([]const u8, "assets", "Optional directory containing game data, settings and runtime DLLs to install beside game.exe");
    const msvc_target = b.resolveTargetQuery(.{ .cpu_arch = .x86, .os_tag = .windows, .abi = .msvc });
    const module = clientModule(b, target, optimize);
    const exe = b.addExecutable(.{ .name = "game", .root_module = module });
    exe.entry = .{ .symbol_name = "fun_005d09d4" };
    exe.subsystem = .windows;
    exe.image_base = 0x400000;
    exe.pie = false;
    exe.lto = .none;
    exe.bundle_compiler_rt = false;
    exe.rc_includes = .none;

    // Discover the current sources rather than retaining an obsolete unit list.
    const sources = discoverSources(b);
    for (sources) |source| {
        const seh = std.mem.endsWith(u8, source, "_seh.cpp");
        if (seh) {
            // LLVM emits the recovered x86 SEH/C++ unwind metadata only with
            // its MSVC target. Explicit C interfaces keep the unit boundary ABI.
            const native = clientModule(b, msvc_target, optimize);
            native.addCSourceFile(.{ .file = b.path(source), .flags = cxxFlags(b, source, optimize, true) });
            const name = b.allocator.dupe(u8, source["src/client/".len..]) catch @panic("OOM");
            for (name) |*char| if (char.* == '/' or char.* == '\\' or char.* == '.') {
                char.* = '_';
            };
            const object = b.addObject(.{ .name = name, .root_module = native });
            object.lto = .none;
            module.addObjectFile(object.getEmittedBin());
        } else {
            module.addCSourceFile(.{ .file = b.path(source), .flags = cxxFlags(b, source, optimize, false) });
        }
    }

    // Both tools are subcommands of this exact Zig installation.
    const ijl = b.addSystemCommand(&.{ b.graph.zig_exe, "dlltool", "-m", "i386", "-d" });
    ijl.addFileArg(b.path("src/client/imports/ijl15.def"));
    ijl.addArg("-l");
    module.addObjectFile(ijl.addOutputFileArg("ijl15.lib"));
    module.addWin32ResourceFile(.{ .file = resources.generate(b), .flags = &.{ "/:input-format", "res" } });
    for ([_][]const u8{
        "version", "winmm",    "ws2_32",  "dinput8", "dsound",   "ddraw", "kernel32", "user32",
        "gdi32",   "advapi32", "shell32", "ole32",   "oleaut32", "imm32", "d3d11",    "dxgi",
    }) |name| module.linkSystemLibrary(name, .{ .use_pkg_config = .no });

    // The recovered runtime executes writable thunks and requires NXCOMPAT off.
    // Produce a separate cached output; never modify the compiler's artifact.
    const configured = pe.configure(b, exe.getEmittedBin());
    const install = b.addInstallFileWithDir(configured, .bin, "game.exe");
    b.getInstallStep().dependOn(&install.step);
    const check = b.step("check", "Compile, link and configure the client without installing it");
    configured.addStepDependencies(check);

    if (assets) |directory| {
        const copy = b.addInstallDirectory(.{
            .source_dir = .{ .cwd_relative = b.pathFromRoot(directory) },
            .install_dir = .bin,
            .install_subdir = "",
            .include_extensions = &.{ ".sah", ".saf", ".dll", ".DLL", ".ini", ".INI", ".txt", ".TXT" },
        });
        b.getInstallStep().dependOn(&copy.step);
    }
    const run = b.addSystemCommand(&.{b.getInstallPath(.bin, "game.exe")});
    run.step.dependOn(b.getInstallStep());
    run.setCwd(.{ .cwd_relative = b.getInstallPath(.bin, "") });
    if (b.args) |args| run.addArgs(args) else run.addArgs(&.{ "start", "game" });
    b.step("run", "Build and launch the installed client with its runtime assets").dependOn(&run.step);

    const test_step = b.step("test", "Test resources, PE compatibility, animation, effects and connection overrides");
    for ([_][]const u8{ "build_support/resources.zig", "build_support/pe.zig" }) |source| {
        const tests = b.addTest(.{ .root_module = b.createModule(.{
            .root_source_file = b.path(source),
            .target = b.graph.host,
            .optimize = .Debug,
        }) });
        test_step.dependOn(&b.addRunArtifact(tests).step);
    }

    const animation_tests = clientTest(b, target, "animation-timing-test", "animation_timing_test_entry", &.{
        "tests/animation_timing.cpp", "src/client/graphics/native_animation_timing.cpp",
    }, &.{"kernel32"});
    test_step.dependOn(&b.addRunArtifact(animation_tests).step);

    const camera_tests = clientTest(b, target, "login-camera-test", "login_camera_test_entry", &.{
        "tests/login_camera.cpp", "src/client/graphics/native_login_camera.cpp",
    }, &.{"kernel32"});
    test_step.dependOn(&b.addRunArtifact(camera_tests).step);

    const version_tests = clientTest(b, target, "client-version-test", "client_version_test_entry", &.{
        "tests/client_version.cpp",
        "src/client/config/development_version.cpp",
        "src/client/network/outbound.cpp",
        "src/client/crypto/transport.cpp",
        "src/client/crypto/aes.cpp",
        "src/client/crypto/lcg_stream.cpp",
        "src/client/crypto/sha256.cpp",
        "src/client/core/stack_probe.cpp",
        "src/client/core/memory.cpp",
    }, &.{ "kernel32", "user32", "ws2_32" });
    test_step.dependOn(&b.addRunArtifact(version_tests).step);

    const particle_tests = clientTest(b, target, "particle-state-test", "particle_state_test_entry", &.{
        "tests/particle_state.cpp",
        "src/client/graphics/native_resources.cpp",
        "src/client/graphics/native_render_passes.cpp",
        "src/client/graphics/native_scene_ports.cpp",
        "src/client/graphics/native_shadow_ports.cpp",
        "src/client/graphics/native_procedural_ports.cpp",
        "src/client/graphics/native_effect_ports.cpp",
        "src/client/graphics/native_controller_state.cpp",
        "src/client/graphics/native_render_target.cpp",
        "src/client/core/memory.cpp",
        "src/client/core/stack_probe.cpp",
    }, &.{ "d3d11", "dxgi", "kernel32", "user32", "gdi32", "ole32" });
    test_step.dependOn(&b.addRunArtifact(particle_tests).step);
}

fn clientTest(b: *std.Build, target: std.Build.ResolvedTarget, name: []const u8, entry: []const u8, sources: []const []const u8, libraries: []const []const u8) *std.Build.Step.Compile {
    const module = clientModule(b, target, .ReleaseFast);
    for (sources) |source| module.addCSourceFile(.{
        .file = b.path(source),
        .flags = cxxFlags(b, source, .ReleaseFast, false),
    });
    for (libraries) |library| module.linkSystemLibrary(library, .{ .use_pkg_config = .no });
    const tests = b.addExecutable(.{ .name = name, .root_module = module });
    tests.entry = .{ .symbol_name = entry };
    tests.subsystem = .console;
    tests.bundle_compiler_rt = false;
    tests.lto = .none;
    return tests;
}

fn clientModule(b: *std.Build, target: std.Build.ResolvedTarget, optimize: std.builtin.OptimizeMode) *std.Build.Module {
    const module = b.createModule(.{
        .target = target,
        .optimize = optimize,
        .link_libc = false,
        .link_libcpp = false,
        .stack_protector = false,
        .sanitize_c = .off,
    });
    module.addIncludePath(b.path("src/client"));
    // The client's C++ standard library facilities are header-only.
    // Supply Zig's headers without linking a second C++ runtime.
    module.addIncludePath(.{ .cwd_relative = b.pathJoin(&.{ b.graph.zig_lib_directory.path.?, "libcxx", "include" }) });
    module.addCMacro("_LIBCPP_HARDENING_MODE_DEFAULT", "_LIBCPP_HARDENING_MODE_NONE");
    // build-exe/build-obj do not implicitly link libc or add its SDK headers.
    // The Win32 SDK shipped with Zig is also used for the MSVC SEH units.
    module.addSystemIncludePath(.{ .cwd_relative = b.pathJoin(&.{ b.graph.zig_lib_directory.path.?, "libc", "include", "any-windows-any" }) });
    return module;
}

fn cxxFlags(b: *std.Build, source: []const u8, optimize: std.builtin.OptimizeMode, seh: bool) []const []const u8 {
    var flags: std.ArrayList([]const u8) = .empty;
    flags.appendSlice(b.allocator, &.{
        "-std=c++17", "-ffreestanding", "-fno-builtin", "-fno-rtti", "-fno-stack-protector",
        "-mno-sse",   "-mno-sse2",      "-Wall",        "-Wextra",   "-fno-lto",
        switch (optimize) {
            .Debug => "-O0",
            .ReleaseSmall => "-Oz",
            else => "-O2",
        },
    }) catch @panic("OOM");
    if (seh) {
        // Use Zig's bundled Win32 headers with the MSVC exception ABI. Their
        // GNU declarations must retain __attribute__ calling conventions.
        flags.appendSlice(b.allocator, &.{
            "-fexceptions", "-fms-extensions", "-fgnuc-version=4.2.1",
            "-D__i386__=1", "-D_X86_=1",       "-Wno-unused-command-line-argument",
        }) catch @panic("OOM");
        const basename = std.fs.path.basename(source);
        if (std.mem.startsWith(u8, basename, "nls") or
            std.mem.eql(u8, basename, "fpmath_seh.cpp") or
            std.mem.eql(u8, basename, "render_cpu_seh.cpp") or
            std.mem.eql(u8, basename, "stdio_scan_seh.cpp") or
            std.mem.eql(u8, basename, "strftime_locale_seh.cpp"))
            flags.append(b.allocator, "-fasync-exceptions") catch @panic("OOM");
        if (std.mem.eql(u8, basename, "stdio_scan_seh.cpp"))
            flags.append(b.allocator, "-fwrapv") catch @panic("OOM");
    } else flags.append(b.allocator, "-fno-exceptions") catch @panic("OOM");
    return flags.toOwnedSlice(b.allocator) catch @panic("OOM");
}

fn discoverSources(b: *std.Build) []const []const u8 {
    const io = b.graph.io;
    var directory = b.build_root.handle.openDir(io, "src/client", .{ .iterate = true }) catch @panic("Cannot open src/client");
    defer directory.close(io);
    var walker = directory.walk(b.allocator) catch @panic("OOM");
    defer walker.deinit();
    var sources: std.ArrayList([]const u8) = .empty;
    while (walker.next(io) catch @panic("Cannot read src/client")) |entry| {
        if (entry.kind != .file or !std.mem.endsWith(u8, entry.path, ".cpp")) continue;
        const path = b.fmt("src/client/{s}", .{entry.path});
        std.mem.replaceScalar(u8, path, '\\', '/');
        sources.append(b.allocator, path) catch @panic("OOM");
    }
    if (sources.items.len == 0) @panic("No C++ client sources found");
    std.mem.sort([]const u8, sources.items, {}, struct {
        fn lessThan(_: void, lhs: []const u8, rhs: []const u8) bool {
            return std.mem.lessThan(u8, lhs, rhs);
        }
    }.lessThan);
    return sources.toOwnedSlice(b.allocator) catch @panic("OOM");
}
