# shaiya-game-decomp

An AI-assisted reverse-engineered C++ client for Shaiya Episode 5.4. The project
combines recovered C++, x86 instruction transcriptions and newly authored code.

## Build

Install Zig 0.16.0, put `zig` on your `PATH`, and run from this directory:

```powershell
zig build
```

Zig is the only required build tool. The output is `zig-out/bin/game.exe`, a
32-bit Windows executable. The original executable is not needed to build it.

To run on Windows, place compatible `data.sah`, `data.saf`, settings and runtime
DLLs (including `ijl15.dll`) in `assets/`, then run:

```powershell
zig build run -Dassets=assets
```

See [build and runtime details](docs/building.md) for requirements, checks and options.

## Differences from the original client

- **Rendering:** native Direct3D 11 replaces Direct3D 9, with newly authored
  shaders and rendering passes. Some visual effects may differ.
- **Background updates:** rendering continues while unfocused or minimized;
  animation timing retains fractional milliseconds at high frame rates.
- **Server selection:** `SHAIYA_LOGIN_HOST` can override the login server's IPv4
  address for development.

This is an ongoing reconstruction. Complete visual and gameplay equivalence
with the original client has not been established.
