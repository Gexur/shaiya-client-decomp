# Building and running

Run these commands from the project root with Zig 0.16.0 on your `PATH`.
Zig supplies the C++ compiler, Windows headers and import libraries, resource
compiler and linker. Python, mise, Visual Studio and a separate Windows SDK
are not required.

## Build and check

```powershell
zig build
```

The default build installs the 32-bit Windows GUI client to
`zig-out/bin/game.exe`. It compiles the sources in `src/client`, generates the
IJL import library from its committed definition, and embeds the Windows
resources from the editable catalog and assets. No original executable,
prebuilt client objects or sibling checkout is needed.

```powershell
zig build check
zig build test
```

`check` compiles, links and configures the executable without installing or
launching it. `test` checks Windows resource serialization and PE compatibility
handling. These checks do not exercise the renderer, server interaction or gameplay.

The default `ReleaseFast` mode uses `-O2`. Other supported modes are selected with
`-Doptimize=Debug`, `-Doptimize=ReleaseSafe` or `-Doptimize=ReleaseSmall`.
The recovered pointer layouts and calling conventions require the
`x86-windows-gnu` executable target. Files ending in `_seh.cpp` compile separately
with the MSVC x86 exception ABI; the client supplies its recovered C/C++ runtime
implementations. Link-time optimization is disabled to preserve the exception
ABI and assembly references. See [`build.zig`](../build.zig) for the build definition.

## Runtime requirements

Running requires Windows, a Direct3D 11 device supporting feature level 10.0 or
later, `d3dcompiler_47.dll` for runtime shader compilation, compatible game data
and a compatible server. These runtime inputs are not needed to compile.

Place the game archives `data.sah` and `data.saf`, settings files and required
runtime DLLs, including `ijl15.dll`, in `assets/` or another local directory.
The source project does not redistribute game archives or include a server.

```powershell
zig build -Dassets=assets
zig build run -Dassets=assets
```

`-Dassets` copies archives, settings, DLLs and text files beside the installed
executable; it excludes executables. `assets/` and the installed copies in
`zig-out/` are ignored by version control. Use a different directory with
`-Dassets=path/to/data`.

The run step builds and installs the client, uses `zig-out/bin` as its working
directory, and supplies `start game` by default. To pass arguments explicitly:

```powershell
zig build run -Dassets=assets -- start game
```

The optional `SHAIYA_LOGIN_HOST` environment variable selects a strict
dotted-decimal IPv4 login address. Without a valid override, the recovered
endpoint remains in use. For a local server:

```powershell
$env:SHAIYA_LOGIN_HOST = "127.0.0.1"
zig build run -Dassets=assets
```

## Editor and source documentation

Open [`shaiya-game-decomp.code-workspace`](../shaiya-game-decomp.code-workspace)
or the project directory. VS Code tasks invoke `zig` from `PATH` for build,
check, test and run. Editor extensions are optional.

- [Client source](../src/client/README.md): modules and recovery boundaries.
- [Graphics](../src/client/graphics/README.md): native rendering and visual differences.
- [Windows resources](../src/client/resources/README.md): editing embedded assets.
- [Historical recovery notes](history/README.md): earlier validation and workspace records.
