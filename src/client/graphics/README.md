# Client graphics

The original client's Direct3D 9 rendering path is replaced by a native
Direct3D 11 device, immediate context and DXGI swap chain. Rendering uses
explicit native passes, newly authored shaders and typed asset resources.

- `native_renderer.cpp` owns device creation, presentation, resize and targets.
- `native_resources.cpp` uploads DDS/TGA/BMP/WIC textures and native buffers.
  Buffers retain CPU asset bytes for collision reads and explicit updates.
- `native_render_passes.cpp` and `native_render_shaders.h` define layouts and
  shaders for UI, terrain, lightmaps, static/skinned models, water, projected
  shadows, glow and gamma.
- `native_*_ports.cpp` preserve game entry conventions and CPU asset/scene flow
  while submitting typed passes.
- `native_render_target.cpp` preserves targets, viewports and scene parameters
  around reflection, shadow and postprocessing passes.
- `native_font.cpp` uses a GDI glyph cache and native UI passes.
- `native_capture.cpp` reads the backbuffer and writes JPEG screenshots through
  WIC, preserving the watermark and numbered filenames.

Running requires Windows, Direct3D feature level 10.0 or later, and
`d3dcompiler_47.dll` for HLSL compilation. Device creation tries hardware and
can use D3D11 WARP. Shader source is compiled at runtime; no separate shader
compiler is required to build the client.

Terrain preserves material ranges and authored texture addressing. Actor passes
retain independent transforms and lighting. Portrait, reflection and shadow
passes restore their render targets and scene state. Animation timing retains
fractional milliseconds and shares elapsed time across scene consumers. Nested
menu fades refresh that interval on every update, including frames shorter than
one millisecond.

The floating-island login camera runs its recovered movement at 825 updates per
second and interpolates poses for rendering. The original updates part of this
camera once per rendered frame; disabling intro effects can therefore increase
its speed abruptly. The fixed camera timeline removes that dependency without
limiting rendering. The reference rate is calibrated to a measured original
D3D9 camera approach of about 1.8 seconds, followed by the recovered 1.5-second
UI reveal. It is a native timing policy, not an original frame-rate limit.
See the [timing measurements](../../../docs/visual-audit/login-camera-timing.json)
for settings, executable hashes and the original client's timing variation.

Water reflection and refraction captures re-enter the world render, including
its UI branch that disables depth testing. The water pass restores the engine's
depth, blending, alpha-test and clip flags afterwards, so grass and other
depth-read draws that follow it stay occluded by terrain and objects.

Shadow, clothing and particle passes preserve the original shared blend-state
transitions so subsequent weapon effects retain their authored transparency.

The optional BumpReflect material uses an authored native shader. The original
external `BumpWater_R.fx` source was unavailable, so exact pixel equivalence for
that material is unverified. Complete client rendering/gameplay equivalence
requires runtime testing beyond a successful source build.

See the [build guide](../../../docs/building.md) for current build/run instructions.
The [visual parity audit](../../../docs/visual-parity-audit.md) records known
differences from D3D9, measured shoreline behavior and unverified areas.
The [historical notes](../../../docs/history/README.md) preserve earlier finite
rendering observations from the original workspace.
