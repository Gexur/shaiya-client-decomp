# Client graphics

The client owns a Direct3D 11 device, immediate context and DXGI swap chain.
Rendering uses explicit native passes and typed asset resources. The former
Direct3D 9 interface implementation, shader-token translator and render-state
interpreter have been removed from production sources.

- `native_renderer.cpp` owns device creation, presentation, resize and targets.
- `native_resources.cpp` uploads DDS/TGA/BMP/WIC textures and native buffers.
  Buffers retain CPU asset bytes for collision reads and explicit updates.
- `native_render_passes.cpp` and `native_render_shaders.h` implement authored
  layouts and shaders for UI, terrain, lightmaps, static/skinned models, water,
  projected shadows, glow and gamma. Materials select concrete native states.
- `native_*_ports.cpp` preserve game entry conventions and CPU asset/scene flow
  while submitting typed passes. These entrypoints do not emulate a graphics
  device, FVF declarations or legacy graphics method tables.
- `native_render_target.cpp` preserves targets, viewports and scene parameters
  around reflection, shadow and postprocessing passes. Native font resources
  use a GDI glyph cache and the UI pass.
- `native_capture.cpp` reads the D3D11 backbuffer and writes quality90 JPEG
  screenshots through WIC, preserving the watermark and numbered filenames.

The renderer requires feature level 10.0 or later and `d3dcompiler_47.dll` for
HLSL compilation. Device creation tries hardware and can use D3D11 WARP.
The normal build remains `-O2` with link-time optimization disabled.

Run `mise run verify-renderer` for the production pass, resource, asset-builder,
lifetime, geometry, water, capture and source-boundary checks. They execute real
D3D11 draws/uploads and staging readback, validate resize/presentation and
resource ownership. Native-only probes reject D3D9 imports and loaded modules;
the separate shoreline comparison harness also runs a hidden D3D9 reference.
Reports are
`evidence/cpp-native-render-passes-verification.json`,
`cpp-native-resources-verification.json`,
`cpp-native-resource-call-verification.json`,
`cpp-native-texture-loading-verification.json`,
`cpp-native-asset-lifetimes-verification.json`,
`cpp-native-geometry-verification.json` and
`cpp-native-water-resources-verification.json` in that directory.
`cpp-native-capture-verification.json` independently decodes native JPEG captures
to verify dimensions, channel order and orientation.
`cpp-native-renderer-contract-verification.json` checks device method calls even
when a renderer is passed through a function argument. Exact reviewed browser
calls and retained SDK bodies are recorded separately; the latter have no
static instruction-symbol path from game procedures.

Terrain checks cover its distinct authored layouts, optional base/lightmap/detail
layers and preserved base alpha. Water resource checks cover signed bump maps,
normal-map generation, authored buffers and target restoration.
Texture loading checks execute the retained cache lookup and native loader with
shipped SMOD/DDS bytes, including its EBX file-mode convention and exact cache keys.

Terrain preserves each material range's base vertex, clamped base/detail textures
and wrapping secondary textures. Skill atlases and the minimap use their authored
wrapping UVs; the minimap combines map RGB with the circular mask's alpha.
Actor passes retain their own clip/model matrices and lighting constants without
replacing the world's transform, camera or lighting. Portrait targets restore
their retained textures and controller state when closed or destroyed.
Attachment draws preserve the original stack arguments and environment texture.
Font calls use typed ANSI/Unicode entrypoints, including gameplay text paths.
Their regression executes the original crashing call packet and checks its
seven-argument return and the caller's separately saved register.

Loading progress updates join an existing frame when one is active. The fade and
loading image then reach the swap chain together; standalone and worker updates
still present their own frames. `cpp-native-loading-frames-verification.json`
checks actual fade pixels, presentation counts and rendering thread ownership.
Resource cleanup uses native texture/buffer and target-scope ownership, including
modal, inventory and static shutdown paths; borrowed render-target views are
cleared without releasing them independently.

The engine's identity-world reset updates both its stored CPU matrix and the
native draw context. Basic water therefore stays at its authored height instead
of inheriting an actor's animated bone transform. Its immutable cached grid
preserves the plane's height, texture coordinates and vertex color while reducing
shoreline depth-interpolation instability. `cpp-native-basic-water-world-verification.json`
checks the actual reset/animation/draw sequence and cache lifetime;
`cpp-native-shore-depth-verification.json` compares eight camera angles against
the old coarse plane and a D3D9 reference using captured terrain geometry.

The client keeps rendering when its window loses focus. Input focus still
follows `WM_ACTIVATEAPP`; the frame dispatcher's render skips are commented out.
Run `python tools/verify_cpp_background_rendering.py` to check all 109 render
and update gates with active and inactive focus flags.

`native_animation_timing.cpp` retains fractional milliseconds between application
updates. MANI/VANI and scene effect consumers share one elapsed interval, so frames
shorter than a millisecond still advance the authored 33 ms rock animation ticks.
The camera continues to use the original floating-point frame delta.
`cpp-native-animation-timing-verification.json` compares compiled animation
callers at 30 through 4,000 FPS and rejects the previous truncating conversion.
`cpp-native-login-rock-timing-observation.json` records a live read-only check
of eight rock animations advancing within 0.5% of their authored speeds.
`cpp-native-login-rock-timing-current-observation.json` checks the later native
client: all eight observed channels advance 60 authored ticks in 2.006 seconds.

The native checks cover finite rendering cases. Full client startup and visual
inspection of login, character selection and gameplay are separate checks.
The optional BumpReflect material uses a new authored native shader; the
original external `BumpWater_R.fx` source was unavailable, so matching that
shader's exact pixels cannot be established.
Earlier COM, state-block and shader-translation fixtures/reports describe the
retired compatibility implementation and are historical evidence.

The migration follows Microsoft's
[Direct3D 11 migration guidance](https://learn.microsoft.com/en-us/windows/win32/direct3d11/d3d11-programming-guide-migrating).
