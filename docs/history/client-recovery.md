# C++ client source and validation

This is the Episode 5.4 client. The Episode 4.5 server PDBs corroborate shared
names and selected runtime containers; client instructions remain authoritative
for client layouts and behavior. For example, the client item lookup uses a
92-byte stride, while the server PDB describes a different 168-byte `stItemInfo`.
The archive layouts also retain their verified client sizes rather than using
serialized Parsec records as in-memory objects. Pinned upstream sources and PDB
identities are recorded in
[`readability-archive-structures.json`](../../evidence/readability-archive-structures.json).

The client source is organized by responsibility:

- `startup/`: application entry, window, initialization and global registrations.
- `graphics/`: renderer, DirectX support and math; `surface/` contains pixel
  formats/codecs and `texture/` contains texture requirements and selection.
- `archive/`: SAH directory loading, SAF access and asserted archive entry layouts.
- `game/player/` and `game/world/`: recovered player and world state lifetimes.
- `core/`, `runtime/`, `crypto/`, `network/`, `ui/`, `config/` and `platform/`:
  their respective shared facilities and subsystems.

Install `requirements.txt`, then use `mise run format-client` to apply the pinned
clang-format 21.1.8 rules or `mise run check-client-style` to check them.
`build-cpp` checks formatting before compilation, and clangd formats C++ on save.
Include order, string literals and comment text are preserved. Generated
`*_instructions*.cpp` listings are excluded and retain their instruction evidence.
Reviewed functions use descriptive C++ identifiers and linker symbols. Remaining
assembly references use those same names. Original addresses are documentation
and differential-test provenance, with mappings in
[`client_function_names.json`](../../tools/client_function_names.json); the game
contains no compatibility aliases for the renamed symbols. Unknown procedures
retain their current identifiers until their contracts support better names.
The [function naming and documentation report](../../evidence/client-function-naming.json)
records 296 descriptive names across startup, configuration, archives, packet
decoding, cryptography, core helpers and texture selection. Canonical APIs name
their parameters, and all 416 function definitions in the 57 reviewed files have
Doxygen documentation covering their purpose and relevant contracts. Packet
names use proven wire widths and vtable byte offsets where the gameplay meaning
remains unresolved. This coverage applies to the reviewed modules; other
recovered functions and instruction listings still need semantic review.
The naming pass preserves loaded code/data and normalized relocation targets
across all 724 objects. All 296 new linker symbols are defined, and the 297 old
symbols, including one redundant alias, are absent.
`tools/client_source_paths.py` resolves historical verifier unit names to the
current production paths without relocating historical drafts or evidence.

The [readability refactor report](../../evidence/readability-client-refactor.json)
records 505 moved files, 19 assembly replacements and 110,728 finite comparisons.
All 724 units compile and link in the default profile. Allocated code/data and
relocations are identical for 713 objects; the remaining 11 are the tested
refactors. Native resource/render checks, 35 seconds of responsive startup and
normal window close also pass. This pass does not establish complete gameplay
equivalence or refresh the separate optimized LTO build.

The latest build links the recovered original entry point `fun_005d09d4` into
`build/cpp/game.exe` with native D3D11 rendering, no unresolved symbols
or duplicate definitions. [The link report](../../evidence/cpp-client-build.json)
records that result. Native startup passes with a visible, responsive `GAME`
window for at least 35 consecutive seconds. The
[current login screenshot](../../evidence/cpp-client-native-d3d11-login.png)
shows the textured castle, island, clouds and rune. The
[background observation](../../evidence/cpp-native-client-background-verification.json)
records advancing frame and camera state while minimized and confirms no loaded
D3D9 runtime. See [the graphics notes](graphics/README.md) for native pass and
resource validation.

The [current rendering observation](../../evidence/cpp-native-d3d11-render-fixes-observation.json)
also covers normal local-stack login, selected-character rendering and world
entry, including restored atlas/minimap textures, portrait lighting isolation and
the basic-water world reset. Captured shoreline geometry has a separate camera
stability regression. These finite checks do not establish complete gameplay
equivalence.

Earlier tests using the previous renderer completed fixture login, character
selection, creation, world entry, movement and a visible Body Protector cast.
Their [observation](../../evidence/cpp-client-resources-default-observation.json)
and [gameplay report](../../evidence/cpp-client-fixture-gameplay.json) remain
historical evidence. Current full gameplay equivalence is unverified. That
fixture has one actor and the starter self-buff; NPCs, quests, combat damage and
the full skill set remain outside its scope.

Original embedded Windows resources live in [`resources/`](resources/).
The linker includes the application icon, seven cursor groups and version
information with their original IDs and language. All 22 individual resource
entries retain their original payloads. Resource inputs and compiled output
are tracked separately from C++ objects, so editing an icon or cursor requires
a fresh link. `mise run verify-client-resources` checks the resource directory
and actual Windows icon, cursor and version loading.
[The native verification report](../../evidence/cpp-client-resources-verification.json)
checks all resources in both the default and optimized executables.

This directory contains recovered C++ and instruction-level x86/ABI
transcriptions with symbolic references. NASM image reproductions under
`src/rebuild` and `src/local` remain separate reference artifacts. Explicit new
development behavior, such as the optional endpoint setting below, is labeled
separately from original recovery.

Build and link the client from the repository root, then prepare its runtime:

```powershell
mise run build-client
mise run prepare-client-runtime
```

`build/cpp/build.json` records the compiled source/header snapshot.
`mise run build-cpp` produces the intermediate objects and static archive;
`mise run link-cpp` links an existing current archive. `build-client` performs
both steps and writes `build/cpp/game.exe` only after a successful original-entry
link. Missing implementations remain hard link failures.

`mise run run-client -- -O3 -flto` selects `-O3` with full LLVM LTO for GNU
units. `--opt-level 3 --lto` is equivalent. The runner builds
or relinks stale or missing profiles before launching them; profile freshness
includes source/header hashes, optimization flags, archive identity and build
tool hashes. `build-client`, `build-cpp` and `link-cpp` accept the same options.
The default remains `-O2` without LTO under `build/cpp`. Other profiles use
`build/cpp-profiles/`, with `o3-lto/build.json`, `o3-lto/client-build.json` and
`o3-lto/client-startup.json` identifying the optimized executable separately.
LTO archives contain actual GNU LLVM bitcode and directly source-compiled native
MSVC exception-handling objects. The native units also use `-O3`; keeping their
exception ABI separate avoids a crash in the pinned compiler's mixed-bitcode
backend. Native COFF inspection sidecars for GNU bitcode provide dependency
inventories and are excluded from linker input. A linker-directive object
preserves actual external LLVM definitions referenced by recovered assembly;
it contains no executable code or program data.

The optimized executable passes 35 seconds of responsive startup, real fixture
login and [rendered character selection](../../evidence/cpp-client-resources-o3-lto-observation.json).
[The independent audit](../../evidence/cpp-optimized-profile-independent-verification.json)
verifies actual O3 compilation, LTO backend level 3 and the primary archive inputs.

`tools/diagnose_cpp_client_link.py` retains the actual linker diagnostics and
Windows/vendor import libraries used. A successful link establishes that the
providers resolve; runtime behavior requires separate validation.

Runtime preparation copies the supplied `data.sah`, `data.saf`, settings and
DLLs to `build/cpp-run/native-client`, excluding original executables. The
supplied `ijl15.dll` must retain its original 372,736-byte length. The runner
verifies the prepared asset manifest, copies the current linked executable,
sets its working directory and supplies `start game`.

Start the local protocol fixture with `mise run server` in one terminal, then
run `mise run run-client` in another. The fixture uses the real RSA/AES exchange
on `127.0.0.1:30800`, with the game listener on port 30810. Renderer startup
follows a successful login connection; its initial timeout is 30 seconds.
The runner requires a visible, responsive `GAME` window for at least 35
consecutive seconds and writes `evidence/cpp-client-startup.json`. The current
client passes this check. [The fixture instructions](../../server/README.md)
cover creating a Human priest, entering Beika, moving and using quickslot 1 for
the verified starter spell. Characters and movement/resources persist in the
fixture's separate SQLite file.

`config/development_endpoint.cpp` adds the optional `SHAIYA_LOGIN_HOST`
development setting. It accepts four decimal IPv4 octets in 0..255 without
leading zeros, and preserves the original endpoint when absent or invalid.
`run-client` selects `127.0.0.1` for its child process. To choose another real
endpoint, run `.venv\Scripts\python.exe tools\run_cpp_client.py --login-host ADDRESS`.
This is new configuration behavior; actual socket, encryption and packet code
continues to execute. The recovered `TEST_IP` INI field is a country selector,
so it cannot be used as an arbitrary IP override.

Native component tests run font creation/text drawing/GPU readback,
vertex/pixel shader assembly and device acceptance, and the configuration parser
with the recovered heap/string/map runtime. Reviewed storage changes give player
callbacks one contiguous original state object. These component proofs retain
their own limits alongside the now-linked startup/session/subsystem providers.
The genuine player constructor/reset/destructor now run as a native component;
the separate whole-owner comparisons retain their exact allocation/field scope.
The scalar normalizer now preserves the original x87 instruction frame and
schedule, with strict physical floating-point state and access-order evidence.

The client creates a native Direct3D 11 device and DXGI swap chain. The
[renderer](graphics/README.md) uses typed D3D11 resources and explicit authored
shader passes. Game rendering entrypoints submit native UI, terrain, model,
water, shadow and postprocessing work. The former graphics-interface facade,
shader-token translator and legacy state interpreter have been removed.
It requires feature level 10.0 or later and `d3dcompiler_47.dll`.

`mise run verify-renderer` runs native pass, resource, asset-builder, geometry
and water validation executables. They check actual GPU pixels and staging
readback, compressed texture uploads and CPU decoders, typed ownership,
authored layouts and resize/presentation. See the
[pass evidence](../../evidence/cpp-native-render-passes-verification.json),
[resource evidence](../../evidence/cpp-native-resources-verification.json),
[geometry evidence](../../evidence/cpp-native-geometry-verification.json) and
[water resource evidence](../../evidence/cpp-native-water-resources-verification.json).
The executables use D3D11/DXGI without importing or loading D3D9. Full scene and
gameplay visual equivalence remain separate from these finite component checks.

Earlier renderer recovery added the shader owner's deleting destructor and
reset owners at `0x53dd80`, `0x53e610` and `0x54e3b0`. Their recorded COM-service
comparisons are historical; current owners release native typed resources,
with explicit C linkage across GNU/MSVC exception-handling units.
Three block decoder address
declarations now reference their implemented stdcall symbols. The reviewed
correction changes only these relocation identities; no ABI bridge is added.

The 639-unit build added 49 original entries in eight translation units:

- Renderer configuration lookup: 33 functions implement the original nested
  string maps, case conversion, insertion, copying, proxies and lookup. The
  1,958-case corpus and a separate replay retain allocation, C-locale and native
  exception limits.
- Six raw float/half-float texture writers: 3,786 comparisons execute the real
  color conversion and scalar half encoder. The fast half-dispatch slot is
  supplied as an already-selected scalar input; this proof does not execute
  lazy CPU selection. Independent review adds 72 cases.
- Surface base destruction, one-pixel probing, DXT quantization and the actual
  shared empty method: 427 comparisons use genuine CRT frees and RGB24 methods;
  unknown pixel callbacks stop on entry.
- Two geometry dispatch entries and three scalar geometry bodies: 348 and
  3,900 comparisons cover forwarding, weighted transforms and patch interpolation.
  The scalar proof executes recovered transform and integer conversion helpers.
  Its [scope addendum](../../evidence/cpp-render-geometry-scalar-scope-addendum.json)
  excludes volatile EAX equivalence for the two void geometry interfaces and
  records the earlier corrected source mismatch. Native scene traversal remains
  unverified.

Each addition is checked against its reviewed source/object capsule and actual
canonical providers before integration. These finite component comparisons
remain distinct from native rendering and full-client behavior.

Five further source units add 11 original entries: six packed and word-channel
texture writers, block-surface destruction and its deleting wrapper, and three
DXT1/DXT3 color encoders. Their proofs retain 6,284 new original/source comparisons
and 178 earlier encoder comparisons transferred through exact runtime identity.
Each new suite also passed a separate independent replay.

The six writers use the genuine transform, color and error-row helpers. Their
finite proofs compare full public/caller memory, ordered writes, helper state
and raw x87 values; word-channel read streams and arbitrary concurrent reads
remain outside that evidence. Block cleanup preserves the original four-byte
cursor, unsigned traversal, late bounds and flag reads, and actual CRT frees.
The DXT wrappers execute the real encoder, endpoint optimizer and quantizers with
their original nested stack inputs; their reports identify excluded register-save
accesses and finite masked-floating-point limits.

Four further source units add nine more pixel writers and three
DXT5/premultiplied encoding entries. Their 9,191 retained comparisons also passed
separate independent replays. Palette output searches
all 256 RGBA entries using the original extended-precision distance comparison;
the byte-luminance writers preserve in-place color conversion, serpentine
traversal and actual caller scratch words. The packed and dword variants retain
their original channel packing and error diffusion through genuine helpers.
Their evidence distinguishes ordered-read coverage from ordered-write coverage.
The DXT5 paths execute the recovered color encoder, alpha optimizer and
premultiply helper with original nested caller and private-frame inputs.
Native stack growth, GPU texture upload and full scene rendering remain outside
these component comparisons.

The [earlier font and shader assembler dependency audit](../../evidence/cpp-renderer-font-frontier-audit.json)
records the frontier before those native components were recovered. Current
independent reviews cover [font rendering](../../evidence/cpp-graphics-font-quick-native-peer-review.json),
[shader assembly and its storage changes](../../evidence/cpp-renderer-shader-root-peer-review.json),
and [the common runtime](../../evidence/cpp-common-runtime-root-peer-review.json).

Function names derived from addresses retain provenance; they are not claims
about the original names. Data field names retain offsets when semantics are
not established. Every component must document its instruction evidence,
original calling convention, normalized C++ interface where applicable,
dependencies, differential validation and remaining gaps.

Tests may model external dependencies explicitly. Such models belong to test
harnesses and never satisfy production link dependencies or establish recovery
of the substituted behavior.

## Recovered components

| Component | Source | Differential evidence and limits |
| --- | --- | --- |
| SHA-256 and HMAC | `crypto/sha256.cpp` | Complete context/digest comparisons; normalized private register arguments |
| AES schedules, block and counter transform | `crypto/aes.cpp` | Original table provenance, all key widths, context/counter/fragment comparisons |
| Alternate stream transform and PRNG | `crypto/lcg_stream.cpp` | Exact seed arithmetic, stream state, remainder writes and residual returns |
| Bigint arithmetic, division, inverse and modular exponentiation | `crypto/bigint*.cpp` | Actual recovered arithmetic executes, including bounded Toom/FFT/recursive products and positive/negative modular exponentiation; reports retain each tested size and error-path limit |
| Bigint fatal and assertion helpers | `crypto/bigint_failures.cpp` | Original signed divide occurs before either global store; formatting/abort remain explicit CRT boundaries and Windows exception delivery is not reconstructed |
| Complete key-exchange bootstrap and transport wrappers | `crypto/bootstrap.cpp`, `crypto/bootstrap_crypto.cpp`, `crypto/transport.cpp` | Full reply and 704-byte state match the original for the local RSA fixture; separate reports retain the tested exponents, sizes and allocator boundaries |
| Memory and byte/string helpers | `core/` | Signed bytes, overlap direction, alignment, guards and original capacity limits |
| Unsigned 64-bit division and compiler adapter | `core/uint64_divide.cpp` | Original normalization/correction algorithm and hardware divide faults; original RET16 and compiler cdecl contracts are checked separately |
| Unsigned 64-bit remainder and multiplication | `core/uint64_divrem.cpp`, `uint64_multiply.cpp` | Actual register/RET16 contracts and original arithmetic, including quotient correction and hardware division faults |
| Original 96-bit decimal arithmetic and binary conversion | `core/extended96*.cpp` | Original WORD convolution, guard/sticky rounding, all 58 power records, mantissa operations and binary32/64 descriptors; the compiled execution contains no original image or host conversion library |
| Packet readers, consumers and session fields | `network/` | Recovered production callbacks and session vtable link; component callback models and stopped-prefix domains retain their documented scope |
| Socket connection, queued writes and flags | `network/socket_transport.cpp` | Exact archive object compared; explicit Winsock/USER32 test boundaries |
| Outgoing packet framing and dump frontend | `network/outbound.cpp` | Real AES/LCG transforms, original send/queue branches and debug metadata; logger/state owners link and component callback boundaries remain documented |
| Socket-window callback and initialization | `network/window_transport.cpp` | Normal-return comparisons use real readers, dispatcher and crypto; full opcode DWORD is preserved for equal prior scratch bytes; original SEH and native private-stack integration remain unfinished |
| Key-exchange session callback | `network/challenge.cpp` | Real RSA/AES/LCG, framing and flags; full fixture replies compare every wire byte; short replies retain their explicit undefined-tail scope |
| UI constructors and parent ownership | `ui/constructors.cpp`, `parent_owner_seh.cpp`, `parent_release_seh.cpp`, `nested_owner_seh.cpp` | Original construction/cleanup states and ordered partial writes; native C++/foreign/access-violation cleanup checks retain their explicit secondary-failure limits |
| UI rendering and text dependency batch | `ui/parent_draw.cpp`, `font_text.cpp`, `parent_grid.cpp`, `core/quad_draw.cpp` and related units | Historical 44-object transfer into the 386-unit archive retains allocated-section/relocation identity checks and its finite fixture/frame scope |
| CRT environment lookup and updates | `runtime/environment_access.cpp`, `string_search.cpp`, `nls_compare_seh.cpp` | Exact archive bodies, actual recovered allocation/NLS and native stack-overflow fallback; no host environment implementation is substituted |
| Timezone, calendar and timestamp formatting | `runtime/timezone*`, `calendar*`, `strftime*`, `startup/logger_timestamp.cpp` | Original transition arithmetic, live cache/lock ordering, real environment and Win32 integration; native finally, output-fault order and actual stack-overflow fallback retain their finite test domains |
| Windows message pumps and file wrappers | `platform/support.cpp` | Unit boundaries remain explicit; a separate native proof links the five actual recovered CRT file aliases and real Windows file operations |
| Endpoint/settings readers and audio setters | `config/initialization.cpp` | Exact original literals, locale and floating arithmetic; runtime interface/OS/CRT boundaries remain |
| Settings storage and default key tables | `config/storage.cpp` | Original typed settings and default key tables; audio providers link, while component API/callback limits remain documented |
| Timestamp and exit-registration initializers | `startup/` | Binary-proven initializer slots and genuinely empty callbacks; original-entry startup passes the 35-second responsive-window check |
| Clock conversion and PRNG seed initializer | `startup/time_seed.cpp` | Original FILETIME arithmetic and canonical seed storage; only the Windows clock API is a test boundary |
| CRT heap, small-block heap, allocation and locks | `runtime/heap*`, `small_block_heap*`, `allocations*`, `locks*` | Real algorithms, native Windows allocation, and exception/finally lock release; ordinary and native reports retain their boundaries |
| CRT thread data, locale and multibyte/NLS state | `runtime/thread_data*`, `locale*`, `multibyte*`, `nls*` | Typed original storage, code-page transitions, FLS/TLS, real Windows NLS, stack-overflow fallback and cleanup |
| CRT structured and C++ exception runtime | `runtime/exception*`, `cxx_*` | Actual Windows unwind plus typed/value/reference catches, object destruction, rethrow, PMD adjustment, translators and RTTI; compiler adaptations and fatal boundaries are documented |
| CRT I/O, arguments, environment, descriptors and stdio | `runtime/io*`, `startup_args*`, `environment*`, `stdio*`, `descriptor_io*`, `file_*` | Original parsing/encoding/error branches; native startup and actual platform file callers execute recovered open/read/write/seek/tell/close with real Windows files |
| CRT floating input/output and rebinding | `runtime/floating_*`, `fpmath_bindings.cpp` | Actual decimal parsing/formatting, six original slot stores and indirect floating assignment; native checks link the recovered integer/decimal runtime and use retained original outputs as oracles |
| CRT bounded comparison and filesystem wrappers | `runtime/string_compare.cpp`, `path_ops.cpp` | Original two-pass byte-read order and faults; native Win32 move/access/remove-directory operations and error mapping |
| CRT initializer and termination control | `runtime/cinit*`, `initializer_iteration.cpp`, `termination_tables.cpp`, `crt_exit*`, `exit_registry*` | Original table slots, reverse callback traversal and mutation, quick/returning exits, managed discovery and exception cleanup retain their component checks; full application execution remains under validation |
| Cookie, security and fatal-error reporting | `runtime/security*`, `runtime/runtime_error*`, `message_box.cpp`, `string_copy.cpp` | Binary-derived literals and ordinary behavior, actual Windows entropy APIs, throwing security callbacks and native fatal exits; interactive dialogs remain a modeled unit boundary |
| Client strings and static callback pairs | `core/string*`, `startup/global_initializers_strings*`, `global_ownership*` | Original assign/grow/self-alias/destruction, actual heap/SBH and native exceptional growth; additional directly decoded vector/COM ownership callbacks retain their exact observed storage spans |
| Container and resource ownership | `core/pointer_list16*`, `thread_array_owner*`, `resource_lists28*`, `indexed_resource_lists300*`, `resource_manager*`, `tree24*`, `tree48*` | Original recursive ownership, balanced-tree erase, manager references and exact native exception/unwind behavior; each report retains its tested domains and fixture input setup |
| ATL module initialization and cleanup | `core/atl_modules.cpp`, `atl_critical_seh.cpp`, `startup/global_atl_modules.cpp` | Actual Win32 critical sections, exception-to-HRESULT mapping, original typed data and real exit registration; the original fixed module-base requirement is retained |
| COM, vector and ring lifetimes | `core/com_lifetimes*`, `payload_ranges84*`, `paired_pointer_lists24*`, `string_ring*`, `block_ring20*`, `linked_nodes52*` | Original release order, live callback mutations, retained dangling entries and precise partial state; real heap/SBH and native C++/foreign/access-violation propagation are checked |
| File-type metadata and static parents | `core/type_metadata44*`, `startup/global_type_metadata44.cpp` | Actual 44-byte layouts, four labels, canonical parent pointers, real String ownership and deleting table; native construction, exit registration and partial cleanup |
| ATL class/module and application resource owners | `core/atl_window_classes44*`, `atl_base_module44*`, `resource_array_owner492*`, `library_owner8*`, `resource_tree_owner20*` | Original fields, API/callback order and actual FuncInfo cleanup, including distinct retry paths and retained dangling state; component proofs cover real Windows APIs, heaps and exceptions |
| Logging and lazy level names | `core/logger*`, `tree48_lookup*`, `string_compare*`, `log_level_names*` | Real lookup, listener mutation, twelve lazy Strings and selected-bit exception reset; native archive-format consumer chain uses actual formatting/String/heap bodies while remaining creation/close/time dependencies stay explicit |
| Original power and floating exception support | `core/x87_pow*`, `math_error*`, `fp_exception*`, `fp_normalize*`, `fp_raise*` | Actual x87/SSE2 arithmetic, exact incoming register state, control/status words, report callbacks and Windows exception records; no host math substitution |
| Client locale conversion | `startup/client_locale*` | Original shared buffer, two string scans/code-page reads and Win32 conversion order; one canonical locale DWORD remains shared with packet consumers |
| CRT scanning and thread primitives | `runtime/stdio_input_stream*`, `stdio_scan*`, `thread_random*`, `string_token*` | Original input fault order, real scanner/file/multibyte/floating helpers, native SEH and per-thread state; random/token fixtures use retained original outputs |
| Application and graphics/input initialization | `startup/application*`, `game_init*`, `window*`, `render_*`, `input_support*` | Original entry, window and device startup execute natively; login UI and a 3D scene display with rendering artifacts; login and gameplay remain unverified |

`network/packet_tail_conditionals.cpp` adds the complete callers at
`0x00590e80`, `0x00595740` and `0x005957c0`: alternating byte arrays, an
optional word/flag, and conditional counted text. They retain the original
44/12/136-byte private frames, inherited bytes, cdecl reader argument and
thiscall virtual callbacks. The actual recovered packet readers and memory
helpers execute in the comparison; diagnostic and consumer callbacks remain
explicit test boundaries. The
[retained proof](../../evidence/cpp-packet-tail-conditionals-verification.json)
contains 2,895 comparisons, including 2,508 complete returns and 387 reached
stops. Oversized array/text inputs stop before the affected reader operation;
unchecked client behavior is preserved. A diagnostic fixture correction supplies
explicit input count/status/length bytes and retains the prior random-refill
failure without changing the recovered client code.

```powershell
$packetArchive = (Get-Content -Raw build/cpp/build.json | ConvertFrom-Json).archive_sha256
.venv\Scripts\python.exe tools\verify_cpp_packet_tail_conditionals.py --expected-archive $packetArchive
```

Reproduce component comparisons with `tools/verify_cpp_hashing.py`,
`tools/verify_cpp_aes.py`, `tools/verify_cpp_lcg.py`,
`tools/verify_cpp_utilities.py`, `tools/verify_cpp_packets.py`,
`tools/verify_cpp_ui.py`, and `tools/verify_cpp_platform.py` using the project
Python environment. Test reports under `evidence/cpp-*` specify the actual
compiled artifacts, recovered instruction paths, dependency models and limits.

After building, reproduce the incoming key-exchange and startup-seed comparisons:

```powershell
.venv\Scripts\python.exe tools\verify_cpp_challenge.py --case-group incoming
.venv\Scripts\python.exe tools\verify_cpp_time_seed.py
```

The incoming test runs the real clock initializer, packet reader, dispatcher,
consumer, RSA bootstrap and outgoing crypto/framing. Its fixture binds the
binary-proven session slot to the recovered callback and models the external
clock, allocation and socket boundaries. Its finite fixture evidence remains
separate from the original-entry link and native startup validation.

`mise run cpp-status` writes [the current progress report](../../evidence/cpp/progress.json).
It checks the build's complete source/header snapshot and retains the individual
test scopes. Definition counts and passing component tests are not a completion
percentage. Newly recovered source is not considered tested just because it
appears in the archive.

`core/stack_probe.cpp` contains a small naked x86 ABI routine recovered from
the original stack probe. It uses explicit instruction mnemonics because it
must adjust its caller's stack pointer; ordinary C++ cannot express that ABI.
There are no executable byte arrays or serialized PE sections in this build.

The socket callback also uses one explicit x86 memory load: the original WORD
reader overwrites only two bytes of a four-byte opcode slot. A hardware DWORD
load retains the other two bytes without an indeterminate C++ integer read or
an invented zero extension. The test supplies equal prior scratch bytes to
both implementations; it does not assign a fixed value to live stack contents.

The unsigned division helper uses the original hardware `DIV` operation for
each division of two words by one. This retains divide-by-zero faults without
introducing C++ undefined arithmetic. Its compiler adapter calls the recovered
routine; it does not substitute an arithmetic library or division algorithm.

The original startup and network callback inventories needed additional proven
analysis entry points. The separate `recovered/ghidra-startup` and
`recovered/ghidra-network` corpora retain those REA profile identities. Their
pseudocode is reference evidence and is never compiled as recovered source.

The current client links and executes from the recovered original entry, passing
35 seconds of responsive native startup. Visible rendering artifacts remain.
Full application exception/unwind paths, login, character selection and gameplay
still require execution evidence.
