# Project guidance

This is an AI-assisted reverse-engineered Shaiya Episode 5.4 Windows C++ client.
Production sources live in `src/client`. Zig 0.16.0 builds the client through
`build.zig`; keep Zig as the only required build tool.

- Preserve recovered 32-bit layouts, explicit x86 calling conventions and
  exception behavior when refactoring. Files ending in `_seh.cpp` use the
  MSVC x86 exception ABI; other units use the GNU Windows x86 ABI.
- Implement graphics changes in the native Direct3D 11 renderer.
- Keep current instructions in `README.md` and `docs/building.md`.
  `docs/history/` contains records of the previous workspace and toolchain.

Use `zig build check` to check compilation and linking after C++ or build
changes. Use `zig build test` for resource serialization and PE build-support
changes. These tests do not validate rendering or gameplay; check those changes
with targeted runtime observations.
