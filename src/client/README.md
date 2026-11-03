# Client source

This directory contains the AI-assisted reverse-engineered Episode 5.4 C++ client
and explicit x86 instruction transcriptions. All production translation units
participate in the standalone [Zig build](../../docs/building.md). The original
executable and serialized PE sections are not build inputs.

- `startup/`: entry point, application/window startup and global initialization.
- `archive/`: SAH directory loading, SAF access and client archive layouts.
- `config/`: settings, recovered string/map storage and the optional development endpoint.
- `core/`: recovered containers, strings, ownership and common facilities.
- `runtime/`: recovered allocation, locale, I/O and exception/runtime support.
- `crypto/` and `network/`: cryptography, transport and packet processing.
- `game/`: player/world state and game behavior.
- `ui/`: recovered interface behavior and state.
- `graphics/`: [native Direct3D 11 rendering](graphics/README.md), textures and math.
- `platform/`: Windows integration.
- `imports/`: declarations for external vendor DLL imports.
- `resources/`: [editable embedded Windows resources](resources/README.md).

Files ending in `_seh.cpp` preserve Windows structured exception behavior and
compile with the MSVC x86 exception ABI. Other units use the GNU Windows x86 ABI.
Cross-unit boundaries retain explicit recovered calling conventions. The client
supplies its own runtime functions; substituting a host C/C++ runtime changes
those contracts.

Descriptive identifiers represent reviewed contracts. Original addresses and
remaining `fun_...` identifiers are recovery provenance; instruction listings
retain unresolved implementation details. Shared server symbols are supporting
evidence, not authority for client layouts. For example, the client item lookup
uses a 92-byte stride rather than the different server layout.

A successful build verifies compilation and symbol resolution. Complete gameplay
equivalence is unverified. The [historical recovery notes](../../docs/history/README.md)
record earlier finite tests and observations from the original workspace; their
separate toolchain and evidence paths are not required by this project.
