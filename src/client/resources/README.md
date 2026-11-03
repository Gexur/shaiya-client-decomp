# Windows resources

`manifest.json` defines every original Windows resource by type, ID, language,
code page, and asset. The original client has seven cursor images, seven cursor
groups, six icon images, one icon group, and one version resource. Every resource
uses language 1042 (Korean) and code page 0.

The ICO and CUR files are ordinary editable single-image containers. The build
extracts each image and its cursor hotspot, preserving the explicit image IDs
referenced by the original group resources. Group and version files retain their
exact standalone Windows resource payloads. If an image's dimensions or length
change, update the corresponding group metadata as well.

The standalone Zig build generates a standard Win32 RES container and compiles
it with `zig rc` into an x86 resource-only COFF object. The RES header
describes individual type/ID/language entries; it preserves the version payload
without passing it through a compiler's VERSIONINFO text conversion.
Normal builds use only these committed assets. They read neither the original
executable nor a copied PE resource section.
`reference_payload_sha256` records migration provenance;
it does not prevent intentional asset edits.

Run `zig build` from the project root to rebuild the client after changing these
assets or their catalog. Zig is the only build tool needed; see the
[build guide](../../../docs/building.md) for commands and checks.
