// Typed original glow FX asset:11parameters,2techniques,3pixel-shader2.0 programs.
#pragma once
#include <stdint.h>
constexpr uint32_t glow_operand(uint32_t index, uint32_t addressing_type, uint32_t selector,
                                uint32_t modifiers) {
    return index | (addressing_type << 11) | (selector << 16) | (modifiers << 24);
}
constexpr uint32_t glow_pres_opcode(uint32_t operation, uint32_t components, bool scalar) {
    return (operation << 20) | components | (scalar ? 0x80000000U : 0);
}
struct __attribute__((packed)) GlowDirectOperand {
    uint32_t relative, register_table, component_offset;
};
struct __attribute__((packed)) GlowRelativeOperand {
    uint32_t relative, index_table, index_component, register_table, component_offset;
};
struct __attribute__((packed)) GlowAssetField0 {
    uint32_t magic;
    uint32_t metadata_offset;
};
struct __attribute__((packed)) GlowAssetField1 {
    uint32_t length;
};
struct __attribute__((packed)) GlowAssetField2 {
    uint32_t type;
    uint32_t parameter_class;
    uint32_t name_offset;
    uint32_t semantic_offset;
    uint32_t elements;
};
struct __attribute__((packed)) GlowAssetField3 {
    uint32_t object_id;
};
struct __attribute__((packed)) GlowAssetField4 {
    uint32_t length;
    char name[14];
    uint8_t alignment_padding[2];
};
struct __attribute__((packed)) GlowAssetField5 {
    uint32_t type;
    uint32_t parameter_class;
    uint32_t name_offset;
    uint32_t semantic_offset;
    uint32_t elements;
    uint32_t first_dimension;
    uint32_t second_dimension;
};
struct __attribute__((packed)) GlowAssetField6 {
    float values[1];
};
struct __attribute__((packed)) GlowAssetField7 {
    uint32_t length;
    char name[9];
    uint8_t alignment_padding[3];
};
struct __attribute__((packed)) GlowAssetField8 {
    uint32_t type;
    uint32_t parameter_class;
    uint32_t name_offset;
    uint32_t semantic_offset;
    uint32_t elements;
    uint32_t first_dimension;
    uint32_t second_dimension;
};
struct __attribute__((packed)) GlowAssetField9 {
    float values[1];
};
struct __attribute__((packed)) GlowAssetField10 {
    uint32_t length;
    char name[10];
    uint8_t alignment_padding[2];
};
struct __attribute__((packed)) GlowAssetField11 {
    uint32_t type;
    uint32_t parameter_class;
    uint32_t name_offset;
    uint32_t semantic_offset;
    uint32_t elements;
    uint32_t first_dimension;
    uint32_t second_dimension;
};
struct __attribute__((packed)) GlowAssetField12 {
    float values[1];
};
struct __attribute__((packed)) GlowAssetField13 {
    uint32_t length;
    char name[11];
    uint8_t alignment_padding[1];
};
struct __attribute__((packed)) GlowAssetField14 {
    uint32_t type;
    uint32_t parameter_class;
    uint32_t name_offset;
    uint32_t semantic_offset;
    uint32_t elements;
};
struct __attribute__((packed)) GlowAssetField15 {
    uint32_t object_id;
};
struct __attribute__((packed)) GlowAssetField16 {
    uint32_t type;
    uint32_t parameter_class;
    uint32_t name_offset;
    uint32_t semantic_offset;
    uint32_t elements;
};
struct __attribute__((packed)) GlowAssetField17 {
    uint32_t values[1];
};
struct __attribute__((packed)) GlowAssetField18 {
    uint32_t type;
    uint32_t parameter_class;
    uint32_t name_offset;
    uint32_t semantic_offset;
    uint32_t elements;
    uint32_t first_dimension;
    uint32_t second_dimension;
};
struct __attribute__((packed)) GlowAssetField19 {
    uint32_t values[1];
};
struct __attribute__((packed)) GlowAssetField20 {
    uint32_t type;
    uint32_t parameter_class;
    uint32_t name_offset;
    uint32_t semantic_offset;
    uint32_t elements;
    uint32_t first_dimension;
    uint32_t second_dimension;
};
struct __attribute__((packed)) GlowAssetField21 {
    uint32_t values[1];
};
struct __attribute__((packed)) GlowAssetField22 {
    uint32_t type;
    uint32_t parameter_class;
    uint32_t name_offset;
    uint32_t semantic_offset;
    uint32_t elements;
    uint32_t first_dimension;
    uint32_t second_dimension;
};
struct __attribute__((packed)) GlowAssetField23 {
    uint32_t values[1];
};
struct __attribute__((packed)) GlowAssetField24 {
    uint32_t type;
    uint32_t parameter_class;
    uint32_t name_offset;
    uint32_t semantic_offset;
    uint32_t elements;
    uint32_t first_dimension;
    uint32_t second_dimension;
};
struct __attribute__((packed)) GlowAssetField25 {
    uint32_t values[1];
};
struct __attribute__((packed)) GlowAssetField26 {
    uint32_t type;
    uint32_t parameter_class;
    uint32_t name_offset;
    uint32_t semantic_offset;
    uint32_t elements;
    uint32_t first_dimension;
    uint32_t second_dimension;
};
struct __attribute__((packed)) GlowAssetField27 {
    uint32_t states;
};
struct __attribute__((packed)) GlowAssetField28 {
    uint32_t operation;
    uint32_t index;
    uint32_t type_offset;
    uint32_t value_offset;
};
struct __attribute__((packed)) GlowAssetField29 {
    uint32_t operation;
    uint32_t index;
    uint32_t type_offset;
    uint32_t value_offset;
};
struct __attribute__((packed)) GlowAssetField30 {
    uint32_t operation;
    uint32_t index;
    uint32_t type_offset;
    uint32_t value_offset;
};
struct __attribute__((packed)) GlowAssetField31 {
    uint32_t operation;
    uint32_t index;
    uint32_t type_offset;
    uint32_t value_offset;
};
struct __attribute__((packed)) GlowAssetField32 {
    uint32_t operation;
    uint32_t index;
    uint32_t type_offset;
    uint32_t value_offset;
};
struct __attribute__((packed)) GlowAssetField33 {
    uint32_t operation;
    uint32_t index;
    uint32_t type_offset;
    uint32_t value_offset;
};
struct __attribute__((packed)) GlowAssetField34 {
    uint32_t length;
    char name[14];
    uint8_t alignment_padding[2];
};
struct __attribute__((packed)) GlowAssetField35 {
    uint32_t values[1];
};
struct __attribute__((packed)) GlowAssetField36 {
    uint32_t type;
    uint32_t parameter_class;
    uint32_t name_offset;
    uint32_t semantic_offset;
    uint32_t elements;
    uint32_t first_dimension;
    uint32_t second_dimension;
};
struct __attribute__((packed)) GlowAssetField37 {
    uint32_t values[1];
};
struct __attribute__((packed)) GlowAssetField38 {
    uint32_t type;
    uint32_t parameter_class;
    uint32_t name_offset;
    uint32_t semantic_offset;
    uint32_t elements;
    uint32_t first_dimension;
    uint32_t second_dimension;
};
struct __attribute__((packed)) GlowAssetField39 {
    uint32_t values[1];
};
struct __attribute__((packed)) GlowAssetField40 {
    uint32_t type;
    uint32_t parameter_class;
    uint32_t name_offset;
    uint32_t semantic_offset;
    uint32_t elements;
    uint32_t first_dimension;
    uint32_t second_dimension;
};
struct __attribute__((packed)) GlowAssetField41 {
    uint32_t values[1];
};
struct __attribute__((packed)) GlowAssetField42 {
    uint32_t type;
    uint32_t parameter_class;
    uint32_t name_offset;
    uint32_t semantic_offset;
    uint32_t elements;
    uint32_t first_dimension;
    uint32_t second_dimension;
};
struct __attribute__((packed)) GlowAssetField43 {
    uint32_t object_id;
};
struct __attribute__((packed)) GlowAssetField44 {
    uint32_t type;
    uint32_t parameter_class;
    uint32_t name_offset;
    uint32_t semantic_offset;
    uint32_t elements;
};
struct __attribute__((packed)) GlowAssetField45 {
    uint32_t length;
    char name[3];
    uint8_t alignment_padding[1];
};
struct __attribute__((packed)) GlowAssetField46 {
    uint32_t length;
    char name[12];
};
struct __attribute__((packed)) GlowAssetField47 {
    uint32_t type;
    uint32_t parameter_class;
    uint32_t name_offset;
    uint32_t semantic_offset;
    uint32_t elements;
    uint32_t first_dimension;
    uint32_t second_dimension;
};
struct __attribute__((packed)) GlowAssetField48 {
    float values[1];
};
struct __attribute__((packed)) GlowAssetField49 {
    uint32_t length;
    char name[10];
    uint8_t alignment_padding[2];
};
struct __attribute__((packed)) GlowAssetField50 {
    uint32_t type;
    uint32_t parameter_class;
    uint32_t name_offset;
    uint32_t semantic_offset;
    uint32_t elements;
    uint32_t first_dimension;
    uint32_t second_dimension;
};
struct __attribute__((packed)) GlowAssetField51 {
    float values[28];
};
struct __attribute__((packed)) GlowAssetField52 {
    uint32_t length;
    char name[13];
    uint8_t alignment_padding[3];
};
struct __attribute__((packed)) GlowAssetField53 {
    uint32_t type;
    uint32_t parameter_class;
    uint32_t name_offset;
    uint32_t semantic_offset;
    uint32_t elements;
    uint32_t first_dimension;
    uint32_t second_dimension;
};
struct __attribute__((packed)) GlowAssetField54 {
    float values[28];
};
struct __attribute__((packed)) GlowAssetField55 {
    uint32_t length;
    char name[13];
    uint8_t alignment_padding[3];
};
struct __attribute__((packed)) GlowAssetField56 {
    uint32_t type;
    uint32_t parameter_class;
    uint32_t name_offset;
    uint32_t semantic_offset;
    uint32_t elements;
    uint32_t first_dimension;
    uint32_t second_dimension;
};
struct __attribute__((packed)) GlowAssetField57 {
    float values[1];
};
struct __attribute__((packed)) GlowAssetField58 {
    uint32_t length;
    char name[10];
    uint8_t alignment_padding[2];
};
struct __attribute__((packed)) GlowAssetField59 {
    uint32_t type;
    uint32_t parameter_class;
    uint32_t name_offset;
    uint32_t semantic_offset;
    uint32_t elements;
    uint32_t first_dimension;
    uint32_t second_dimension;
};
struct __attribute__((packed)) GlowAssetField60 {
    float values[1];
};
struct __attribute__((packed)) GlowAssetField61 {
    uint32_t length;
    char name[10];
    uint8_t alignment_padding[2];
};
struct __attribute__((packed)) GlowAssetField62 {
    uint32_t type;
    uint32_t parameter_class;
    uint32_t name_offset;
    uint32_t semantic_offset;
    uint32_t elements;
};
struct __attribute__((packed)) GlowAssetField63 {
    uint32_t object_id;
};
struct __attribute__((packed)) GlowAssetField64 {
    uint32_t type;
    uint32_t parameter_class;
    uint32_t name_offset;
    uint32_t semantic_offset;
    uint32_t elements;
};
struct __attribute__((packed)) GlowAssetField65 {
    uint32_t values[1];
};
struct __attribute__((packed)) GlowAssetField66 {
    uint32_t type;
    uint32_t parameter_class;
    uint32_t name_offset;
    uint32_t semantic_offset;
    uint32_t elements;
    uint32_t first_dimension;
    uint32_t second_dimension;
};
struct __attribute__((packed)) GlowAssetField67 {
    uint32_t values[1];
};
struct __attribute__((packed)) GlowAssetField68 {
    uint32_t type;
    uint32_t parameter_class;
    uint32_t name_offset;
    uint32_t semantic_offset;
    uint32_t elements;
    uint32_t first_dimension;
    uint32_t second_dimension;
};
struct __attribute__((packed)) GlowAssetField69 {
    uint32_t values[1];
};
struct __attribute__((packed)) GlowAssetField70 {
    uint32_t type;
    uint32_t parameter_class;
    uint32_t name_offset;
    uint32_t semantic_offset;
    uint32_t elements;
    uint32_t first_dimension;
    uint32_t second_dimension;
};
struct __attribute__((packed)) GlowAssetField71 {
    uint32_t values[1];
};
struct __attribute__((packed)) GlowAssetField72 {
    uint32_t type;
    uint32_t parameter_class;
    uint32_t name_offset;
    uint32_t semantic_offset;
    uint32_t elements;
    uint32_t first_dimension;
    uint32_t second_dimension;
};
struct __attribute__((packed)) GlowAssetField73 {
    uint32_t values[1];
};
struct __attribute__((packed)) GlowAssetField74 {
    uint32_t type;
    uint32_t parameter_class;
    uint32_t name_offset;
    uint32_t semantic_offset;
    uint32_t elements;
    uint32_t first_dimension;
    uint32_t second_dimension;
};
struct __attribute__((packed)) GlowAssetField75 {
    uint32_t states;
};
struct __attribute__((packed)) GlowAssetField76 {
    uint32_t operation;
    uint32_t index;
    uint32_t type_offset;
    uint32_t value_offset;
};
struct __attribute__((packed)) GlowAssetField77 {
    uint32_t operation;
    uint32_t index;
    uint32_t type_offset;
    uint32_t value_offset;
};
struct __attribute__((packed)) GlowAssetField78 {
    uint32_t operation;
    uint32_t index;
    uint32_t type_offset;
    uint32_t value_offset;
};
struct __attribute__((packed)) GlowAssetField79 {
    uint32_t operation;
    uint32_t index;
    uint32_t type_offset;
    uint32_t value_offset;
};
struct __attribute__((packed)) GlowAssetField80 {
    uint32_t operation;
    uint32_t index;
    uint32_t type_offset;
    uint32_t value_offset;
};
struct __attribute__((packed)) GlowAssetField81 {
    uint32_t operation;
    uint32_t index;
    uint32_t type_offset;
    uint32_t value_offset;
};
struct __attribute__((packed)) GlowAssetField82 {
    uint32_t length;
    char name[9];
    uint8_t alignment_padding[3];
};
struct __attribute__((packed)) GlowAssetField83 {
    uint32_t values[1];
};
struct __attribute__((packed)) GlowAssetField84 {
    uint32_t type;
    uint32_t parameter_class;
    uint32_t name_offset;
    uint32_t semantic_offset;
    uint32_t elements;
    uint32_t first_dimension;
    uint32_t second_dimension;
};
struct __attribute__((packed)) GlowAssetField85 {
    uint32_t values[1];
};
struct __attribute__((packed)) GlowAssetField86 {
    uint32_t type;
    uint32_t parameter_class;
    uint32_t name_offset;
    uint32_t semantic_offset;
    uint32_t elements;
    uint32_t first_dimension;
    uint32_t second_dimension;
};
struct __attribute__((packed)) GlowAssetField87 {
    uint32_t values[1];
};
struct __attribute__((packed)) GlowAssetField88 {
    uint32_t type;
    uint32_t parameter_class;
    uint32_t name_offset;
    uint32_t semantic_offset;
    uint32_t elements;
    uint32_t first_dimension;
    uint32_t second_dimension;
};
struct __attribute__((packed)) GlowAssetField89 {
    uint32_t values[1];
};
struct __attribute__((packed)) GlowAssetField90 {
    uint32_t type;
    uint32_t parameter_class;
    uint32_t name_offset;
    uint32_t semantic_offset;
    uint32_t elements;
    uint32_t first_dimension;
    uint32_t second_dimension;
};
struct __attribute__((packed)) GlowAssetField91 {
    uint32_t object_id;
};
struct __attribute__((packed)) GlowAssetField92 {
    uint32_t type;
    uint32_t parameter_class;
    uint32_t name_offset;
    uint32_t semantic_offset;
    uint32_t elements;
};
struct __attribute__((packed)) GlowAssetField93 {
    uint32_t length;
    char name[3];
    uint8_t alignment_padding[1];
};
struct __attribute__((packed)) GlowAssetField94 {
    uint32_t values[1];
};
struct __attribute__((packed)) GlowAssetField95 {
    uint32_t type;
    uint32_t parameter_class;
    uint32_t name_offset;
    uint32_t semantic_offset;
    uint32_t elements;
    uint32_t first_dimension;
    uint32_t second_dimension;
};
struct __attribute__((packed)) GlowAssetField96 {
    uint32_t values[1];
};
struct __attribute__((packed)) GlowAssetField97 {
    uint32_t type;
    uint32_t parameter_class;
    uint32_t name_offset;
    uint32_t semantic_offset;
    uint32_t elements;
    uint32_t first_dimension;
    uint32_t second_dimension;
};
struct __attribute__((packed)) GlowAssetField98 {
    uint32_t values[1];
};
struct __attribute__((packed)) GlowAssetField99 {
    uint32_t type;
    uint32_t parameter_class;
    uint32_t name_offset;
    uint32_t semantic_offset;
    uint32_t elements;
    uint32_t first_dimension;
    uint32_t second_dimension;
};
struct __attribute__((packed)) GlowAssetField100 {
    uint32_t values[1];
};
struct __attribute__((packed)) GlowAssetField101 {
    uint32_t type;
    uint32_t parameter_class;
    uint32_t name_offset;
    uint32_t semantic_offset;
    uint32_t elements;
    uint32_t first_dimension;
    uint32_t second_dimension;
};
struct __attribute__((packed)) GlowAssetField102 {
    uint32_t object_id;
};
struct __attribute__((packed)) GlowAssetField103 {
    uint32_t type;
    uint32_t parameter_class;
    uint32_t name_offset;
    uint32_t semantic_offset;
    uint32_t elements;
};
struct __attribute__((packed)) GlowAssetField104 {
    uint32_t length;
    char name[3];
    uint8_t alignment_padding[1];
};
struct __attribute__((packed)) GlowAssetField105 {
    uint32_t length;
    char name[21];
    uint8_t alignment_padding[3];
};
struct __attribute__((packed)) GlowAssetField106 {
    uint32_t parameters;
    uint32_t techniques;
    uint32_t shaders;
    uint32_t objects;
};
struct __attribute__((packed)) GlowAssetField107 {
    uint32_t type_offset;
    uint32_t value_offset;
    uint32_t flags;
    uint32_t annotations;
};
struct __attribute__((packed)) GlowAssetField108 {
    uint32_t type_offset;
    uint32_t value_offset;
    uint32_t flags;
    uint32_t annotations;
};
struct __attribute__((packed)) GlowAssetField109 {
    uint32_t type_offset;
    uint32_t value_offset;
    uint32_t flags;
    uint32_t annotations;
};
struct __attribute__((packed)) GlowAssetField110 {
    uint32_t type_offset;
    uint32_t value_offset;
    uint32_t flags;
    uint32_t annotations;
};
struct __attribute__((packed)) GlowAssetField111 {
    uint32_t type_offset;
    uint32_t value_offset;
    uint32_t flags;
    uint32_t annotations;
};
struct __attribute__((packed)) GlowAssetField112 {
    uint32_t type_offset;
    uint32_t value_offset;
    uint32_t flags;
    uint32_t annotations;
};
struct __attribute__((packed)) GlowAssetField113 {
    uint32_t type_offset;
    uint32_t value_offset;
    uint32_t flags;
    uint32_t annotations;
};
struct __attribute__((packed)) GlowAssetField114 {
    uint32_t type_offset;
    uint32_t value_offset;
    uint32_t flags;
    uint32_t annotations;
};
struct __attribute__((packed)) GlowAssetField115 {
    uint32_t type_offset;
    uint32_t value_offset;
    uint32_t flags;
    uint32_t annotations;
};
struct __attribute__((packed)) GlowAssetField116 {
    uint32_t type_offset;
    uint32_t value_offset;
    uint32_t flags;
    uint32_t annotations;
};
struct __attribute__((packed)) GlowAssetField117 {
    uint32_t type_offset;
    uint32_t value_offset;
    uint32_t flags;
    uint32_t annotations;
};
struct __attribute__((packed)) GlowAssetField118 {
    uint32_t name_offset;
    uint32_t annotations;
    uint32_t passes;
};
struct __attribute__((packed)) GlowAssetField119 {
    uint32_t name_offset;
    uint32_t annotations;
    uint32_t states;
};
struct __attribute__((packed)) GlowAssetField120 {
    uint32_t operation;
    uint32_t index;
    uint32_t type_offset;
    uint32_t value_offset;
};
struct __attribute__((packed)) GlowAssetField121 {
    uint32_t operation;
    uint32_t index;
    uint32_t type_offset;
    uint32_t value_offset;
};
struct __attribute__((packed)) GlowAssetField122 {
    uint32_t operation;
    uint32_t index;
    uint32_t type_offset;
    uint32_t value_offset;
};
struct __attribute__((packed)) GlowAssetField123 {
    uint32_t operation;
    uint32_t index;
    uint32_t type_offset;
    uint32_t value_offset;
};
struct __attribute__((packed)) GlowAssetField124 {
    uint32_t operation;
    uint32_t index;
    uint32_t type_offset;
    uint32_t value_offset;
};
struct __attribute__((packed)) GlowAssetField125 {
    uint32_t name_offset;
    uint32_t annotations;
    uint32_t passes;
};
struct __attribute__((packed)) GlowAssetField126 {
    uint32_t name_offset;
    uint32_t annotations;
    uint32_t states;
};
struct __attribute__((packed)) GlowAssetField127 {
    uint32_t operation;
    uint32_t index;
    uint32_t type_offset;
    uint32_t value_offset;
};
struct __attribute__((packed)) GlowAssetField128 {
    uint32_t operation;
    uint32_t index;
    uint32_t type_offset;
    uint32_t value_offset;
};
struct __attribute__((packed)) GlowAssetField129 {
    uint32_t operation;
    uint32_t index;
    uint32_t type_offset;
    uint32_t value_offset;
};
struct __attribute__((packed)) GlowAssetField130 {
    uint32_t operation;
    uint32_t index;
    uint32_t type_offset;
    uint32_t value_offset;
};
struct __attribute__((packed)) GlowAssetField131 {
    uint32_t operation;
    uint32_t index;
    uint32_t type_offset;
    uint32_t value_offset;
};
struct __attribute__((packed)) GlowAssetField132 {
    uint32_t name_offset;
    uint32_t annotations;
    uint32_t states;
};
struct __attribute__((packed)) GlowAssetField133 {
    uint32_t operation;
    uint32_t index;
    uint32_t type_offset;
    uint32_t value_offset;
};
struct __attribute__((packed)) GlowAssetField134 {
    uint32_t operation;
    uint32_t index;
    uint32_t type_offset;
    uint32_t value_offset;
};
struct __attribute__((packed)) GlowAssetField135 {
    uint32_t operation;
    uint32_t index;
    uint32_t type_offset;
    uint32_t value_offset;
};
struct __attribute__((packed)) GlowAssetField136 {
    uint32_t operation;
    uint32_t index;
    uint32_t type_offset;
    uint32_t value_offset;
};
struct __attribute__((packed)) GlowAssetField137 {
    uint32_t operation;
    uint32_t index;
    uint32_t type_offset;
    uint32_t value_offset;
};
struct __attribute__((packed)) GlowAssetField138 {
    uint32_t strings;
    uint32_t resources;
};
struct __attribute__((packed)) GlowAssetField139 {
    uint32_t object_id;
    uint32_t bytes;
};
struct __attribute__((packed)) GlowAssetField140 {
    uint32_t technique;
    uint32_t pass_index;
    uint32_t element;
    uint32_t state;
    uint32_t usage;
    uint32_t bytes;
};
struct __attribute__((packed)) GlowAssetField141 {
    uint16_t major_minor;
    uint16_t shader_kind;
};
struct __attribute__((packed)) GlowAssetField142 {
    uint16_t opcode;
    uint16_t word_count;
};
struct __attribute__((packed)) GlowAssetField143 {
    char fourcc[4];
};
struct __attribute__((packed)) GlowAssetField144 {
    uint32_t size;
    uint32_t creator_offset;
    uint32_t version;
    uint32_t constants;
    uint32_t constant_info_offset;
    uint32_t flags;
    uint32_t target_offset;
};
struct __attribute__((packed)) GlowAssetField145 {
    uint32_t name_offset;
    uint16_t register_set, register_index, register_count, reserved;
    uint32_t type_info_offset, default_value_offset;
};
struct __attribute__((packed)) GlowAssetField146 {
    uint32_t name_offset;
    uint16_t register_set, register_index, register_count, reserved;
    uint32_t type_info_offset, default_value_offset;
};
struct __attribute__((packed)) GlowAssetField147 {
    uint32_t name_offset;
    uint16_t register_set, register_index, register_count, reserved;
    uint32_t type_info_offset, default_value_offset;
};
struct __attribute__((packed)) GlowAssetField148 {
    uint32_t name_offset;
    uint16_t register_set, register_index, register_count, reserved;
    uint32_t type_info_offset, default_value_offset;
};
struct __attribute__((packed)) GlowAssetField149 {
    char name[9];
};
struct __attribute__((packed)) GlowAssetField150 {
    uint8_t alignment_padding[3];
};
struct __attribute__((packed)) GlowAssetField151 {
    uint16_t parameter_class, type, rows, columns, elements, members;
    uint32_t member_info_offset;
};
struct __attribute__((packed)) GlowAssetField152 {
    char name[9];
};
struct __attribute__((packed)) GlowAssetField153 {
    uint8_t alignment_padding[3];
};
struct __attribute__((packed)) GlowAssetField154 {
    uint16_t parameter_class, type, rows, columns, elements, members;
    uint32_t member_info_offset;
};
struct __attribute__((packed)) GlowAssetField155 {
    float values[4];
};
struct __attribute__((packed)) GlowAssetField156 {
    char name[13];
};
struct __attribute__((packed)) GlowAssetField157 {
    uint8_t alignment_padding[3];
};
struct __attribute__((packed)) GlowAssetField158 {
    uint16_t parameter_class, type, rows, columns, elements, members;
    uint32_t member_info_offset;
};
struct __attribute__((packed)) GlowAssetField159 {
    float values[28];
};
struct __attribute__((packed)) GlowAssetField160 {
    char name[10];
};
struct __attribute__((packed)) GlowAssetField161 {
    uint8_t alignment_padding[2];
};
struct __attribute__((packed)) GlowAssetField162 {
    float values[4];
};
struct __attribute__((packed)) GlowAssetField163 {
    char name[7];
};
struct __attribute__((packed)) GlowAssetField164 {
    char name[50];
};
struct __attribute__((packed)) GlowAssetField165 {
    uint8_t alignment_padding[3];
};
struct __attribute__((packed)) GlowAssetField166 {
    uint16_t opcode;
    uint16_t word_count;
};
struct __attribute__((packed)) GlowAssetField167 {
    char fourcc[4];
};
struct __attribute__((packed)) GlowAssetField168 {
    uint16_t major_minor;
    uint16_t shader_kind;
};
struct __attribute__((packed)) GlowAssetField169 {
    uint16_t opcode;
    uint16_t word_count;
};
struct __attribute__((packed)) GlowAssetField170 {
    char fourcc[4];
};
struct __attribute__((packed)) GlowAssetField171 {
    uint32_t size;
    uint32_t creator_offset;
    uint32_t version;
    uint32_t constants;
    uint32_t constant_info_offset;
    uint32_t flags;
    uint32_t target_offset;
};
struct __attribute__((packed)) GlowAssetField172 {
    uint32_t name_offset;
    uint16_t register_set, register_index, register_count, reserved;
    uint32_t type_info_offset, default_value_offset;
};
struct __attribute__((packed)) GlowAssetField173 {
    uint32_t name_offset;
    uint16_t register_set, register_index, register_count, reserved;
    uint32_t type_info_offset, default_value_offset;
};
struct __attribute__((packed)) GlowAssetField174 {
    char name[13];
};
struct __attribute__((packed)) GlowAssetField175 {
    uint8_t alignment_padding[3];
};
struct __attribute__((packed)) GlowAssetField176 {
    uint16_t parameter_class, type, rows, columns, elements, members;
    uint32_t member_info_offset;
};
struct __attribute__((packed)) GlowAssetField177 {
    float values[28];
};
struct __attribute__((packed)) GlowAssetField178 {
    char name[10];
};
struct __attribute__((packed)) GlowAssetField179 {
    uint8_t alignment_padding[2];
};
struct __attribute__((packed)) GlowAssetField180 {
    uint16_t parameter_class, type, rows, columns, elements, members;
    uint32_t member_info_offset;
};
struct __attribute__((packed)) GlowAssetField181 {
    float values[4];
};
struct __attribute__((packed)) GlowAssetField182 {
    char name[3];
};
struct __attribute__((packed)) GlowAssetField183 {
    char name[50];
};
struct __attribute__((packed)) GlowAssetField184 {
    uint8_t alignment_padding[3];
};
struct __attribute__((packed)) GlowAssetField185 {
    uint16_t opcode;
    uint16_t word_count;
};
struct __attribute__((packed)) GlowAssetField186 {
    char fourcc[4];
};
struct __attribute__((packed)) GlowAssetField187 {
    uint32_t register_segments[11];
};
struct __attribute__((packed)) GlowAssetField188 {
    uint16_t opcode;
    uint16_t word_count;
};
struct __attribute__((packed)) GlowAssetField189 {
    char fourcc[4];
};
struct __attribute__((packed)) GlowAssetField190 {
    uint32_t literals;
};
struct __attribute__((packed)) GlowAssetField191 {
    uint16_t opcode;
    uint16_t word_count;
};
struct __attribute__((packed)) GlowAssetField192 {
    char fourcc[4];
};
struct __attribute__((packed)) GlowAssetField193 {
    uint32_t instructions;
};
struct __attribute__((packed)) GlowAssetField194 {
    uint32_t operation;
    uint32_t inputs;
    GlowDirectOperand source_0;
    GlowDirectOperand source_1;
    GlowDirectOperand destination;
};
struct __attribute__((packed)) GlowAssetField195 {
    uint32_t operation;
    uint32_t inputs;
    GlowDirectOperand source_0;
    GlowDirectOperand source_1;
    GlowDirectOperand destination;
};
struct __attribute__((packed)) GlowAssetField196 {
    uint32_t operation;
    uint32_t inputs;
    GlowDirectOperand source_0;
    GlowDirectOperand source_1;
    GlowDirectOperand destination;
};
struct __attribute__((packed)) GlowAssetField197 {
    uint32_t operation;
    uint32_t inputs;
    GlowDirectOperand source_0;
    GlowDirectOperand source_1;
    GlowDirectOperand destination;
};
struct __attribute__((packed)) GlowAssetField198 {
    uint32_t operation;
    uint32_t inputs;
    GlowDirectOperand source_0;
    GlowDirectOperand source_1;
    GlowDirectOperand destination;
};
struct __attribute__((packed)) GlowAssetField199 {
    uint32_t operation;
    uint32_t inputs;
    GlowDirectOperand source_0;
    GlowDirectOperand source_1;
    GlowDirectOperand destination;
};
struct __attribute__((packed)) GlowAssetField200 {
    uint32_t operation;
    uint32_t inputs;
    GlowDirectOperand source_0;
    GlowDirectOperand source_1;
    GlowDirectOperand destination;
};
struct __attribute__((packed)) GlowAssetField201 {
    uint32_t operation;
    uint32_t inputs;
    GlowDirectOperand source_0;
    GlowDirectOperand source_1;
    GlowDirectOperand destination;
};
struct __attribute__((packed)) GlowAssetField202 {
    uint32_t operation;
    uint32_t inputs;
    GlowDirectOperand source_0;
    GlowDirectOperand source_1;
    GlowDirectOperand destination;
};
struct __attribute__((packed)) GlowAssetField203 {
    uint32_t operation;
    uint32_t inputs;
    GlowDirectOperand source_0;
    GlowDirectOperand source_1;
    GlowDirectOperand destination;
};
struct __attribute__((packed)) GlowAssetField204 {
    uint32_t operation;
    uint32_t inputs;
    GlowDirectOperand source_0;
    GlowDirectOperand source_1;
    GlowDirectOperand destination;
};
struct __attribute__((packed)) GlowAssetField205 {
    uint32_t operation;
    uint32_t inputs;
    GlowDirectOperand source_0;
    GlowDirectOperand source_1;
    GlowDirectOperand destination;
};
struct __attribute__((packed)) GlowAssetField206 {
    uint32_t operation;
    uint32_t inputs;
    GlowDirectOperand source_0;
    GlowDirectOperand source_1;
    GlowDirectOperand destination;
};
struct __attribute__((packed)) GlowAssetField207 {
    uint32_t operation;
    uint32_t inputs;
    GlowDirectOperand source_0;
    GlowDirectOperand source_1;
    GlowDirectOperand destination;
};
struct __attribute__((packed)) GlowAssetField208 {
    uint32_t first_marker;
    uint32_t second_marker;
};
struct __attribute__((packed)) GlowAssetField209 {
    uint32_t opcode;
};
struct __attribute__((packed)) GlowAssetField210 {
    uint16_t opcode;
    uint8_t control, length_flags;
    uint32_t operands[2];
};
struct __attribute__((packed)) GlowAssetField211 {
    uint16_t opcode;
    uint8_t control, length_flags;
    uint32_t operands[2];
};
struct __attribute__((packed)) GlowAssetField212 {
    uint16_t opcode;
    uint8_t control, length_flags;
    uint32_t operands[3];
};
struct __attribute__((packed)) GlowAssetField213 {
    uint16_t opcode;
    uint8_t control, length_flags;
    uint32_t operands[3];
};
struct __attribute__((packed)) GlowAssetField214 {
    uint16_t opcode;
    uint8_t control, length_flags;
    uint32_t operands[3];
};
struct __attribute__((packed)) GlowAssetField215 {
    uint16_t opcode;
    uint8_t control, length_flags;
    uint32_t operands[3];
};
struct __attribute__((packed)) GlowAssetField216 {
    uint16_t opcode;
    uint8_t control, length_flags;
    uint32_t operands[3];
};
struct __attribute__((packed)) GlowAssetField217 {
    uint16_t opcode;
    uint8_t control, length_flags;
    uint32_t operands[3];
};
struct __attribute__((packed)) GlowAssetField218 {
    uint16_t opcode;
    uint8_t control, length_flags;
    uint32_t operands[3];
};
struct __attribute__((packed)) GlowAssetField219 {
    uint16_t opcode;
    uint8_t control, length_flags;
    uint32_t operands[3];
};
struct __attribute__((packed)) GlowAssetField220 {
    uint16_t opcode;
    uint8_t control, length_flags;
    uint32_t operands[3];
};
struct __attribute__((packed)) GlowAssetField221 {
    uint16_t opcode;
    uint8_t control, length_flags;
    uint32_t operands[3];
};
struct __attribute__((packed)) GlowAssetField222 {
    uint16_t opcode;
    uint8_t control, length_flags;
    uint32_t operands[3];
};
struct __attribute__((packed)) GlowAssetField223 {
    uint16_t opcode;
    uint8_t control, length_flags;
    uint32_t operands[3];
};
struct __attribute__((packed)) GlowAssetField224 {
    uint16_t opcode;
    uint8_t control, length_flags;
    uint32_t operands[3];
};
struct __attribute__((packed)) GlowAssetField225 {
    uint16_t opcode;
    uint8_t control, length_flags;
    uint32_t operands[3];
};
struct __attribute__((packed)) GlowAssetField226 {
    uint16_t opcode;
    uint8_t control, length_flags;
    uint32_t operands[3];
};
struct __attribute__((packed)) GlowAssetField227 {
    uint16_t opcode;
    uint8_t control, length_flags;
    uint32_t operands[3];
};
struct __attribute__((packed)) GlowAssetField228 {
    uint16_t opcode;
    uint8_t control, length_flags;
    uint32_t operands[3];
};
struct __attribute__((packed)) GlowAssetField229 {
    uint16_t opcode;
    uint8_t control, length_flags;
    uint32_t operands[3];
};
struct __attribute__((packed)) GlowAssetField230 {
    uint16_t opcode;
    uint8_t control, length_flags;
    uint32_t operands[3];
};
struct __attribute__((packed)) GlowAssetField231 {
    uint16_t opcode;
    uint8_t control, length_flags;
    uint32_t operands[3];
};
struct __attribute__((packed)) GlowAssetField232 {
    uint16_t opcode;
    uint8_t control, length_flags;
    uint32_t operands[3];
};
struct __attribute__((packed)) GlowAssetField233 {
    uint16_t opcode;
    uint8_t control, length_flags;
    uint32_t operands[3];
};
struct __attribute__((packed)) GlowAssetField234 {
    uint16_t opcode;
    uint8_t control, length_flags;
    uint32_t operands[3];
};
struct __attribute__((packed)) GlowAssetField235 {
    uint16_t opcode;
    uint8_t control, length_flags;
    uint32_t operands[3];
};
struct __attribute__((packed)) GlowAssetField236 {
    uint16_t opcode;
    uint8_t control, length_flags;
    uint32_t operands[3];
};
struct __attribute__((packed)) GlowAssetField237 {
    uint16_t opcode;
    uint8_t control, length_flags;
    uint32_t operands[3];
};
struct __attribute__((packed)) GlowAssetField238 {
    uint16_t opcode;
    uint8_t control, length_flags;
    uint32_t operands[3];
};
struct __attribute__((packed)) GlowAssetField239 {
    uint16_t opcode;
    uint8_t control, length_flags;
    uint32_t operands[3];
};
struct __attribute__((packed)) GlowAssetField240 {
    uint16_t opcode;
    uint8_t control, length_flags;
    uint32_t operands[3];
};
struct __attribute__((packed)) GlowAssetField241 {
    uint16_t opcode;
    uint8_t control, length_flags;
    uint32_t operands[3];
};
struct __attribute__((packed)) GlowAssetField242 {
    uint16_t opcode;
    uint8_t control, length_flags;
    uint32_t operands[3];
};
struct __attribute__((packed)) GlowAssetField243 {
    uint16_t opcode;
    uint8_t control, length_flags;
    uint32_t operands[3];
};
struct __attribute__((packed)) GlowAssetField244 {
    uint16_t opcode;
    uint8_t control, length_flags;
    uint32_t operands[3];
};
struct __attribute__((packed)) GlowAssetField245 {
    uint16_t opcode;
    uint8_t control, length_flags;
    uint32_t operands[3];
};
struct __attribute__((packed)) GlowAssetField246 {
    uint16_t opcode;
    uint8_t control, length_flags;
    uint32_t operands[3];
};
struct __attribute__((packed)) GlowAssetField247 {
    uint16_t opcode;
    uint8_t control, length_flags;
    uint32_t operands[3];
};
struct __attribute__((packed)) GlowAssetField248 {
    uint16_t opcode;
    uint8_t control, length_flags;
    uint32_t operands[4];
};
struct __attribute__((packed)) GlowAssetField249 {
    uint16_t opcode;
    uint8_t control, length_flags;
    uint32_t operands[4];
};
struct __attribute__((packed)) GlowAssetField250 {
    uint16_t opcode;
    uint8_t control, length_flags;
    uint32_t operands[4];
};
struct __attribute__((packed)) GlowAssetField251 {
    uint16_t opcode;
    uint8_t control, length_flags;
    uint32_t operands[4];
};
struct __attribute__((packed)) GlowAssetField252 {
    uint16_t opcode;
    uint8_t control, length_flags;
    uint32_t operands[4];
};
struct __attribute__((packed)) GlowAssetField253 {
    uint16_t opcode;
    uint8_t control, length_flags;
    uint32_t operands[4];
};
struct __attribute__((packed)) GlowAssetField254 {
    uint16_t opcode;
    uint8_t control, length_flags;
    uint32_t operands[2];
};
struct __attribute__((packed)) GlowAssetField255 {
    uint16_t opcode;
    uint8_t control, length_flags;
    uint32_t operands[2];
};
struct __attribute__((packed)) GlowAssetField256 {
    uint32_t opcode;
};
struct __attribute__((packed)) GlowAssetField257 {
    uint32_t technique;
    uint32_t pass_index;
    uint32_t element;
    uint32_t state;
    uint32_t usage;
    uint32_t bytes;
};
struct __attribute__((packed)) GlowAssetField258 {
    uint16_t major_minor;
    uint16_t shader_kind;
};
struct __attribute__((packed)) GlowAssetField259 {
    uint16_t opcode;
    uint16_t word_count;
};
struct __attribute__((packed)) GlowAssetField260 {
    char fourcc[4];
};
struct __attribute__((packed)) GlowAssetField261 {
    uint32_t size;
    uint32_t creator_offset;
    uint32_t version;
    uint32_t constants;
    uint32_t constant_info_offset;
    uint32_t flags;
    uint32_t target_offset;
};
struct __attribute__((packed)) GlowAssetField262 {
    uint32_t name_offset;
    uint16_t register_set, register_index, register_count, reserved;
    uint32_t type_info_offset, default_value_offset;
};
struct __attribute__((packed)) GlowAssetField263 {
    uint32_t name_offset;
    uint16_t register_set, register_index, register_count, reserved;
    uint32_t type_info_offset, default_value_offset;
};
struct __attribute__((packed)) GlowAssetField264 {
    uint32_t name_offset;
    uint16_t register_set, register_index, register_count, reserved;
    uint32_t type_info_offset, default_value_offset;
};
struct __attribute__((packed)) GlowAssetField265 {
    uint32_t name_offset;
    uint16_t register_set, register_index, register_count, reserved;
    uint32_t type_info_offset, default_value_offset;
};
struct __attribute__((packed)) GlowAssetField266 {
    char name[9];
};
struct __attribute__((packed)) GlowAssetField267 {
    uint8_t alignment_padding[3];
};
struct __attribute__((packed)) GlowAssetField268 {
    uint16_t parameter_class, type, rows, columns, elements, members;
    uint32_t member_info_offset;
};
struct __attribute__((packed)) GlowAssetField269 {
    char name[9];
};
struct __attribute__((packed)) GlowAssetField270 {
    uint8_t alignment_padding[3];
};
struct __attribute__((packed)) GlowAssetField271 {
    uint16_t parameter_class, type, rows, columns, elements, members;
    uint32_t member_info_offset;
};
struct __attribute__((packed)) GlowAssetField272 {
    float values[4];
};
struct __attribute__((packed)) GlowAssetField273 {
    char name[13];
};
struct __attribute__((packed)) GlowAssetField274 {
    uint8_t alignment_padding[3];
};
struct __attribute__((packed)) GlowAssetField275 {
    uint16_t parameter_class, type, rows, columns, elements, members;
    uint32_t member_info_offset;
};
struct __attribute__((packed)) GlowAssetField276 {
    float values[28];
};
struct __attribute__((packed)) GlowAssetField277 {
    char name[10];
};
struct __attribute__((packed)) GlowAssetField278 {
    uint8_t alignment_padding[2];
};
struct __attribute__((packed)) GlowAssetField279 {
    float values[4];
};
struct __attribute__((packed)) GlowAssetField280 {
    char name[7];
};
struct __attribute__((packed)) GlowAssetField281 {
    char name[50];
};
struct __attribute__((packed)) GlowAssetField282 {
    uint8_t alignment_padding[3];
};
struct __attribute__((packed)) GlowAssetField283 {
    uint16_t opcode;
    uint16_t word_count;
};
struct __attribute__((packed)) GlowAssetField284 {
    char fourcc[4];
};
struct __attribute__((packed)) GlowAssetField285 {
    uint16_t major_minor;
    uint16_t shader_kind;
};
struct __attribute__((packed)) GlowAssetField286 {
    uint16_t opcode;
    uint16_t word_count;
};
struct __attribute__((packed)) GlowAssetField287 {
    char fourcc[4];
};
struct __attribute__((packed)) GlowAssetField288 {
    uint32_t size;
    uint32_t creator_offset;
    uint32_t version;
    uint32_t constants;
    uint32_t constant_info_offset;
    uint32_t flags;
    uint32_t target_offset;
};
struct __attribute__((packed)) GlowAssetField289 {
    uint32_t name_offset;
    uint16_t register_set, register_index, register_count, reserved;
    uint32_t type_info_offset, default_value_offset;
};
struct __attribute__((packed)) GlowAssetField290 {
    uint32_t name_offset;
    uint16_t register_set, register_index, register_count, reserved;
    uint32_t type_info_offset, default_value_offset;
};
struct __attribute__((packed)) GlowAssetField291 {
    char name[13];
};
struct __attribute__((packed)) GlowAssetField292 {
    uint8_t alignment_padding[3];
};
struct __attribute__((packed)) GlowAssetField293 {
    uint16_t parameter_class, type, rows, columns, elements, members;
    uint32_t member_info_offset;
};
struct __attribute__((packed)) GlowAssetField294 {
    float values[28];
};
struct __attribute__((packed)) GlowAssetField295 {
    char name[10];
};
struct __attribute__((packed)) GlowAssetField296 {
    uint8_t alignment_padding[2];
};
struct __attribute__((packed)) GlowAssetField297 {
    uint16_t parameter_class, type, rows, columns, elements, members;
    uint32_t member_info_offset;
};
struct __attribute__((packed)) GlowAssetField298 {
    float values[4];
};
struct __attribute__((packed)) GlowAssetField299 {
    char name[3];
};
struct __attribute__((packed)) GlowAssetField300 {
    char name[50];
};
struct __attribute__((packed)) GlowAssetField301 {
    uint8_t alignment_padding[3];
};
struct __attribute__((packed)) GlowAssetField302 {
    uint16_t opcode;
    uint16_t word_count;
};
struct __attribute__((packed)) GlowAssetField303 {
    char fourcc[4];
};
struct __attribute__((packed)) GlowAssetField304 {
    uint32_t register_segments[11];
};
struct __attribute__((packed)) GlowAssetField305 {
    uint16_t opcode;
    uint16_t word_count;
};
struct __attribute__((packed)) GlowAssetField306 {
    char fourcc[4];
};
struct __attribute__((packed)) GlowAssetField307 {
    uint32_t literals;
};
struct __attribute__((packed)) GlowAssetField308 {
    uint16_t opcode;
    uint16_t word_count;
};
struct __attribute__((packed)) GlowAssetField309 {
    char fourcc[4];
};
struct __attribute__((packed)) GlowAssetField310 {
    uint32_t instructions;
};
struct __attribute__((packed)) GlowAssetField311 {
    uint32_t operation;
    uint32_t inputs;
    GlowDirectOperand source_0;
    GlowDirectOperand source_1;
    GlowDirectOperand destination;
};
struct __attribute__((packed)) GlowAssetField312 {
    uint32_t operation;
    uint32_t inputs;
    GlowDirectOperand source_0;
    GlowDirectOperand source_1;
    GlowDirectOperand destination;
};
struct __attribute__((packed)) GlowAssetField313 {
    uint32_t operation;
    uint32_t inputs;
    GlowDirectOperand source_0;
    GlowDirectOperand source_1;
    GlowDirectOperand destination;
};
struct __attribute__((packed)) GlowAssetField314 {
    uint32_t operation;
    uint32_t inputs;
    GlowDirectOperand source_0;
    GlowDirectOperand source_1;
    GlowDirectOperand destination;
};
struct __attribute__((packed)) GlowAssetField315 {
    uint32_t operation;
    uint32_t inputs;
    GlowDirectOperand source_0;
    GlowDirectOperand source_1;
    GlowDirectOperand destination;
};
struct __attribute__((packed)) GlowAssetField316 {
    uint32_t operation;
    uint32_t inputs;
    GlowDirectOperand source_0;
    GlowDirectOperand source_1;
    GlowDirectOperand destination;
};
struct __attribute__((packed)) GlowAssetField317 {
    uint32_t operation;
    uint32_t inputs;
    GlowDirectOperand source_0;
    GlowDirectOperand source_1;
    GlowDirectOperand destination;
};
struct __attribute__((packed)) GlowAssetField318 {
    uint32_t operation;
    uint32_t inputs;
    GlowDirectOperand source_0;
    GlowDirectOperand source_1;
    GlowDirectOperand destination;
};
struct __attribute__((packed)) GlowAssetField319 {
    uint32_t operation;
    uint32_t inputs;
    GlowDirectOperand source_0;
    GlowDirectOperand source_1;
    GlowDirectOperand destination;
};
struct __attribute__((packed)) GlowAssetField320 {
    uint32_t operation;
    uint32_t inputs;
    GlowDirectOperand source_0;
    GlowDirectOperand source_1;
    GlowDirectOperand destination;
};
struct __attribute__((packed)) GlowAssetField321 {
    uint32_t operation;
    uint32_t inputs;
    GlowDirectOperand source_0;
    GlowDirectOperand source_1;
    GlowDirectOperand destination;
};
struct __attribute__((packed)) GlowAssetField322 {
    uint32_t operation;
    uint32_t inputs;
    GlowDirectOperand source_0;
    GlowDirectOperand source_1;
    GlowDirectOperand destination;
};
struct __attribute__((packed)) GlowAssetField323 {
    uint32_t operation;
    uint32_t inputs;
    GlowDirectOperand source_0;
    GlowDirectOperand source_1;
    GlowDirectOperand destination;
};
struct __attribute__((packed)) GlowAssetField324 {
    uint32_t operation;
    uint32_t inputs;
    GlowDirectOperand source_0;
    GlowDirectOperand source_1;
    GlowDirectOperand destination;
};
struct __attribute__((packed)) GlowAssetField325 {
    uint32_t first_marker;
    uint32_t second_marker;
};
struct __attribute__((packed)) GlowAssetField326 {
    uint32_t opcode;
};
struct __attribute__((packed)) GlowAssetField327 {
    uint16_t opcode;
    uint8_t control, length_flags;
    uint32_t operands[2];
};
struct __attribute__((packed)) GlowAssetField328 {
    uint16_t opcode;
    uint8_t control, length_flags;
    uint32_t operands[2];
};
struct __attribute__((packed)) GlowAssetField329 {
    uint16_t opcode;
    uint8_t control, length_flags;
    uint32_t operands[3];
};
struct __attribute__((packed)) GlowAssetField330 {
    uint16_t opcode;
    uint8_t control, length_flags;
    uint32_t operands[3];
};
struct __attribute__((packed)) GlowAssetField331 {
    uint16_t opcode;
    uint8_t control, length_flags;
    uint32_t operands[3];
};
struct __attribute__((packed)) GlowAssetField332 {
    uint16_t opcode;
    uint8_t control, length_flags;
    uint32_t operands[3];
};
struct __attribute__((packed)) GlowAssetField333 {
    uint16_t opcode;
    uint8_t control, length_flags;
    uint32_t operands[3];
};
struct __attribute__((packed)) GlowAssetField334 {
    uint16_t opcode;
    uint8_t control, length_flags;
    uint32_t operands[3];
};
struct __attribute__((packed)) GlowAssetField335 {
    uint16_t opcode;
    uint8_t control, length_flags;
    uint32_t operands[3];
};
struct __attribute__((packed)) GlowAssetField336 {
    uint16_t opcode;
    uint8_t control, length_flags;
    uint32_t operands[3];
};
struct __attribute__((packed)) GlowAssetField337 {
    uint16_t opcode;
    uint8_t control, length_flags;
    uint32_t operands[3];
};
struct __attribute__((packed)) GlowAssetField338 {
    uint16_t opcode;
    uint8_t control, length_flags;
    uint32_t operands[3];
};
struct __attribute__((packed)) GlowAssetField339 {
    uint16_t opcode;
    uint8_t control, length_flags;
    uint32_t operands[3];
};
struct __attribute__((packed)) GlowAssetField340 {
    uint16_t opcode;
    uint8_t control, length_flags;
    uint32_t operands[3];
};
struct __attribute__((packed)) GlowAssetField341 {
    uint16_t opcode;
    uint8_t control, length_flags;
    uint32_t operands[3];
};
struct __attribute__((packed)) GlowAssetField342 {
    uint16_t opcode;
    uint8_t control, length_flags;
    uint32_t operands[3];
};
struct __attribute__((packed)) GlowAssetField343 {
    uint16_t opcode;
    uint8_t control, length_flags;
    uint32_t operands[3];
};
struct __attribute__((packed)) GlowAssetField344 {
    uint16_t opcode;
    uint8_t control, length_flags;
    uint32_t operands[3];
};
struct __attribute__((packed)) GlowAssetField345 {
    uint16_t opcode;
    uint8_t control, length_flags;
    uint32_t operands[3];
};
struct __attribute__((packed)) GlowAssetField346 {
    uint16_t opcode;
    uint8_t control, length_flags;
    uint32_t operands[3];
};
struct __attribute__((packed)) GlowAssetField347 {
    uint16_t opcode;
    uint8_t control, length_flags;
    uint32_t operands[3];
};
struct __attribute__((packed)) GlowAssetField348 {
    uint16_t opcode;
    uint8_t control, length_flags;
    uint32_t operands[3];
};
struct __attribute__((packed)) GlowAssetField349 {
    uint16_t opcode;
    uint8_t control, length_flags;
    uint32_t operands[3];
};
struct __attribute__((packed)) GlowAssetField350 {
    uint16_t opcode;
    uint8_t control, length_flags;
    uint32_t operands[3];
};
struct __attribute__((packed)) GlowAssetField351 {
    uint16_t opcode;
    uint8_t control, length_flags;
    uint32_t operands[3];
};
struct __attribute__((packed)) GlowAssetField352 {
    uint16_t opcode;
    uint8_t control, length_flags;
    uint32_t operands[3];
};
struct __attribute__((packed)) GlowAssetField353 {
    uint16_t opcode;
    uint8_t control, length_flags;
    uint32_t operands[3];
};
struct __attribute__((packed)) GlowAssetField354 {
    uint16_t opcode;
    uint8_t control, length_flags;
    uint32_t operands[3];
};
struct __attribute__((packed)) GlowAssetField355 {
    uint16_t opcode;
    uint8_t control, length_flags;
    uint32_t operands[3];
};
struct __attribute__((packed)) GlowAssetField356 {
    uint16_t opcode;
    uint8_t control, length_flags;
    uint32_t operands[3];
};
struct __attribute__((packed)) GlowAssetField357 {
    uint16_t opcode;
    uint8_t control, length_flags;
    uint32_t operands[3];
};
struct __attribute__((packed)) GlowAssetField358 {
    uint16_t opcode;
    uint8_t control, length_flags;
    uint32_t operands[3];
};
struct __attribute__((packed)) GlowAssetField359 {
    uint16_t opcode;
    uint8_t control, length_flags;
    uint32_t operands[3];
};
struct __attribute__((packed)) GlowAssetField360 {
    uint16_t opcode;
    uint8_t control, length_flags;
    uint32_t operands[3];
};
struct __attribute__((packed)) GlowAssetField361 {
    uint16_t opcode;
    uint8_t control, length_flags;
    uint32_t operands[3];
};
struct __attribute__((packed)) GlowAssetField362 {
    uint16_t opcode;
    uint8_t control, length_flags;
    uint32_t operands[3];
};
struct __attribute__((packed)) GlowAssetField363 {
    uint16_t opcode;
    uint8_t control, length_flags;
    uint32_t operands[3];
};
struct __attribute__((packed)) GlowAssetField364 {
    uint16_t opcode;
    uint8_t control, length_flags;
    uint32_t operands[3];
};
struct __attribute__((packed)) GlowAssetField365 {
    uint16_t opcode;
    uint8_t control, length_flags;
    uint32_t operands[4];
};
struct __attribute__((packed)) GlowAssetField366 {
    uint16_t opcode;
    uint8_t control, length_flags;
    uint32_t operands[4];
};
struct __attribute__((packed)) GlowAssetField367 {
    uint16_t opcode;
    uint8_t control, length_flags;
    uint32_t operands[4];
};
struct __attribute__((packed)) GlowAssetField368 {
    uint16_t opcode;
    uint8_t control, length_flags;
    uint32_t operands[4];
};
struct __attribute__((packed)) GlowAssetField369 {
    uint16_t opcode;
    uint8_t control, length_flags;
    uint32_t operands[4];
};
struct __attribute__((packed)) GlowAssetField370 {
    uint16_t opcode;
    uint8_t control, length_flags;
    uint32_t operands[4];
};
struct __attribute__((packed)) GlowAssetField371 {
    uint16_t opcode;
    uint8_t control, length_flags;
    uint32_t operands[2];
};
struct __attribute__((packed)) GlowAssetField372 {
    uint16_t opcode;
    uint8_t control, length_flags;
    uint32_t operands[2];
};
struct __attribute__((packed)) GlowAssetField373 {
    uint32_t opcode;
};
struct __attribute__((packed)) GlowAssetField374 {
    uint32_t technique;
    uint32_t pass_index;
    uint32_t element;
    uint32_t state;
    uint32_t usage;
    uint32_t bytes;
};
struct __attribute__((packed)) GlowAssetField375 {
    char name[14];
    uint8_t alignment_padding[2];
};
struct __attribute__((packed)) GlowAssetField376 {
    uint32_t technique;
    uint32_t pass_index;
    uint32_t element;
    uint32_t state;
    uint32_t usage;
    uint32_t bytes;
};
struct __attribute__((packed)) GlowAssetField377 {
    uint16_t major_minor;
    uint16_t shader_kind;
};
struct __attribute__((packed)) GlowAssetField378 {
    uint16_t opcode;
    uint16_t word_count;
};
struct __attribute__((packed)) GlowAssetField379 {
    char fourcc[4];
};
struct __attribute__((packed)) GlowAssetField380 {
    uint32_t size;
    uint32_t creator_offset;
    uint32_t version;
    uint32_t constants;
    uint32_t constant_info_offset;
    uint32_t flags;
    uint32_t target_offset;
};
struct __attribute__((packed)) GlowAssetField381 {
    uint32_t name_offset;
    uint16_t register_set, register_index, register_count, reserved;
    uint32_t type_info_offset, default_value_offset;
};
struct __attribute__((packed)) GlowAssetField382 {
    uint32_t name_offset;
    uint16_t register_set, register_index, register_count, reserved;
    uint32_t type_info_offset, default_value_offset;
};
struct __attribute__((packed)) GlowAssetField383 {
    char name[9];
};
struct __attribute__((packed)) GlowAssetField384 {
    uint8_t alignment_padding[3];
};
struct __attribute__((packed)) GlowAssetField385 {
    uint16_t parameter_class, type, rows, columns, elements, members;
    uint32_t member_info_offset;
};
struct __attribute__((packed)) GlowAssetField386 {
    float values[4];
};
struct __attribute__((packed)) GlowAssetField387 {
    char name[14];
};
struct __attribute__((packed)) GlowAssetField388 {
    uint8_t alignment_padding[2];
};
struct __attribute__((packed)) GlowAssetField389 {
    uint16_t parameter_class, type, rows, columns, elements, members;
    uint32_t member_info_offset;
};
struct __attribute__((packed)) GlowAssetField390 {
    char name[7];
};
struct __attribute__((packed)) GlowAssetField391 {
    char name[50];
};
struct __attribute__((packed)) GlowAssetField392 {
    uint8_t alignment_padding[3];
};
struct __attribute__((packed)) GlowAssetField393 {
    uint16_t opcode;
    uint16_t word_count;
};
struct __attribute__((packed)) GlowAssetField394 {
    char fourcc[4];
};
struct __attribute__((packed)) GlowAssetField395 {
    uint16_t major_minor;
    uint16_t shader_kind;
};
struct __attribute__((packed)) GlowAssetField396 {
    uint16_t opcode;
    uint16_t word_count;
};
struct __attribute__((packed)) GlowAssetField397 {
    char fourcc[4];
};
struct __attribute__((packed)) GlowAssetField398 {
    uint32_t size;
    uint32_t creator_offset;
    uint32_t version;
    uint32_t constants;
    uint32_t constant_info_offset;
    uint32_t flags;
    uint32_t target_offset;
};
struct __attribute__((packed)) GlowAssetField399 {
    uint32_t name_offset;
    uint16_t register_set, register_index, register_count, reserved;
    uint32_t type_info_offset, default_value_offset;
};
struct __attribute__((packed)) GlowAssetField400 {
    uint32_t name_offset;
    uint16_t register_set, register_index, register_count, reserved;
    uint32_t type_info_offset, default_value_offset;
};
struct __attribute__((packed)) GlowAssetField401 {
    char name[11];
};
struct __attribute__((packed)) GlowAssetField402 {
    uint8_t alignment_padding[1];
};
struct __attribute__((packed)) GlowAssetField403 {
    uint16_t parameter_class, type, rows, columns, elements, members;
    uint32_t member_info_offset;
};
struct __attribute__((packed)) GlowAssetField404 {
    float values[4];
};
struct __attribute__((packed)) GlowAssetField405 {
    char name[10];
};
struct __attribute__((packed)) GlowAssetField406 {
    char name[3];
};
struct __attribute__((packed)) GlowAssetField407 {
    char name[50];
};
struct __attribute__((packed)) GlowAssetField408 {
    uint8_t alignment_padding[1];
};
struct __attribute__((packed)) GlowAssetField409 {
    uint16_t opcode;
    uint16_t word_count;
};
struct __attribute__((packed)) GlowAssetField410 {
    char fourcc[4];
};
struct __attribute__((packed)) GlowAssetField411 {
    uint32_t register_segments[11];
};
struct __attribute__((packed)) GlowAssetField412 {
    uint16_t opcode;
    uint16_t word_count;
};
struct __attribute__((packed)) GlowAssetField413 {
    char fourcc[4];
};
struct __attribute__((packed)) GlowAssetField414 {
    uint32_t literals;
};
struct __attribute__((packed)) GlowAssetField415 {
    double values[12];
};
struct __attribute__((packed)) GlowAssetField416 {
    uint16_t opcode;
    uint16_t word_count;
};
struct __attribute__((packed)) GlowAssetField417 {
    char fourcc[4];
};
struct __attribute__((packed)) GlowAssetField418 {
    uint32_t instructions;
};
struct __attribute__((packed)) GlowAssetField419 {
    uint32_t operation;
    uint32_t inputs;
    GlowDirectOperand source_0;
    GlowDirectOperand destination;
};
struct __attribute__((packed)) GlowAssetField420 {
    uint32_t operation;
    uint32_t inputs;
    GlowDirectOperand source_0;
    GlowDirectOperand source_1;
    GlowDirectOperand destination;
};
struct __attribute__((packed)) GlowAssetField421 {
    uint32_t operation;
    uint32_t inputs;
    GlowDirectOperand source_0;
    GlowDirectOperand source_1;
    GlowDirectOperand destination;
};
struct __attribute__((packed)) GlowAssetField422 {
    uint32_t operation;
    uint32_t inputs;
    GlowDirectOperand source_0;
    GlowDirectOperand destination;
};
struct __attribute__((packed)) GlowAssetField423 {
    uint32_t operation;
    uint32_t inputs;
    GlowDirectOperand source_0;
    GlowDirectOperand source_1;
    GlowDirectOperand destination;
};
struct __attribute__((packed)) GlowAssetField424 {
    uint32_t operation;
    uint32_t inputs;
    GlowDirectOperand source_0;
    GlowDirectOperand source_1;
    GlowDirectOperand destination;
};
struct __attribute__((packed)) GlowAssetField425 {
    uint32_t operation;
    uint32_t inputs;
    GlowDirectOperand source_0;
    GlowDirectOperand destination;
};
struct __attribute__((packed)) GlowAssetField426 {
    uint32_t first_marker;
    uint32_t second_marker;
};
struct __attribute__((packed)) GlowAssetField427 {
    uint32_t opcode;
};
struct __attribute__((packed)) GlowAssetField428 {
    uint16_t opcode;
    uint8_t control, length_flags;
    uint32_t operands[5];
};
struct __attribute__((packed)) GlowAssetField429 {
    uint16_t opcode;
    uint8_t control, length_flags;
    uint32_t operands[2];
};
struct __attribute__((packed)) GlowAssetField430 {
    uint16_t opcode;
    uint8_t control, length_flags;
    uint32_t operands[2];
};
struct __attribute__((packed)) GlowAssetField431 {
    uint16_t opcode;
    uint8_t control, length_flags;
    uint32_t operands[2];
};
struct __attribute__((packed)) GlowAssetField432 {
    uint16_t opcode;
    uint8_t control, length_flags;
    uint32_t operands[2];
};
struct __attribute__((packed)) GlowAssetField433 {
    uint16_t opcode;
    uint8_t control, length_flags;
    uint32_t operands[3];
};
struct __attribute__((packed)) GlowAssetField434 {
    uint16_t opcode;
    uint8_t control, length_flags;
    uint32_t operands[3];
};
struct __attribute__((packed)) GlowAssetField435 {
    uint16_t opcode;
    uint8_t control, length_flags;
    uint32_t operands[2];
};
struct __attribute__((packed)) GlowAssetField436 {
    uint16_t opcode;
    uint8_t control, length_flags;
    uint32_t operands[2];
};
struct __attribute__((packed)) GlowAssetField437 {
    uint16_t opcode;
    uint8_t control, length_flags;
    uint32_t operands[3];
};
struct __attribute__((packed)) GlowAssetField438 {
    uint16_t opcode;
    uint8_t control, length_flags;
    uint32_t operands[3];
};
struct __attribute__((packed)) GlowAssetField439 {
    uint16_t opcode;
    uint8_t control, length_flags;
    uint32_t operands[2];
};
struct __attribute__((packed)) GlowAssetField440 {
    uint16_t opcode;
    uint8_t control, length_flags;
    uint32_t operands[2];
};
struct __attribute__((packed)) GlowAssetField441 {
    uint16_t opcode;
    uint8_t control, length_flags;
    uint32_t operands[2];
};
struct __attribute__((packed)) GlowAssetField442 {
    uint16_t opcode;
    uint8_t control, length_flags;
    uint32_t operands[2];
};
struct __attribute__((packed)) GlowAssetField443 {
    uint16_t opcode;
    uint8_t control, length_flags;
    uint32_t operands[3];
};
struct __attribute__((packed)) GlowAssetField444 {
    uint16_t opcode;
    uint8_t control, length_flags;
    uint32_t operands[3];
};
struct __attribute__((packed)) GlowAssetField445 {
    uint16_t opcode;
    uint8_t control, length_flags;
    uint32_t operands[2];
};
struct __attribute__((packed)) GlowAssetField446 {
    uint16_t opcode;
    uint8_t control, length_flags;
    uint32_t operands[2];
};
struct __attribute__((packed)) GlowAssetField447 {
    uint16_t opcode;
    uint8_t control, length_flags;
    uint32_t operands[2];
};
struct __attribute__((packed)) GlowAssetField448 {
    uint16_t opcode;
    uint8_t control, length_flags;
    uint32_t operands[2];
};
struct __attribute__((packed)) GlowAssetField449 {
    uint16_t opcode;
    uint8_t control, length_flags;
    uint32_t operands[3];
};
struct __attribute__((packed)) GlowAssetField450 {
    uint16_t opcode;
    uint8_t control, length_flags;
    uint32_t operands[3];
};
struct __attribute__((packed)) GlowAssetField451 {
    uint16_t opcode;
    uint8_t control, length_flags;
    uint32_t operands[2];
};
struct __attribute__((packed)) GlowAssetField452 {
    uint16_t opcode;
    uint8_t control, length_flags;
    uint32_t operands[2];
};
struct __attribute__((packed)) GlowAssetField453 {
    uint16_t opcode;
    uint8_t control, length_flags;
    uint32_t operands[3];
};
struct __attribute__((packed)) GlowAssetField454 {
    uint16_t opcode;
    uint8_t control, length_flags;
    uint32_t operands[3];
};
struct __attribute__((packed)) GlowAssetField455 {
    uint16_t opcode;
    uint8_t control, length_flags;
    uint32_t operands[3];
};
struct __attribute__((packed)) GlowAssetField456 {
    uint16_t opcode;
    uint8_t control, length_flags;
    uint32_t operands[3];
};
struct __attribute__((packed)) GlowAssetField457 {
    uint16_t opcode;
    uint8_t control, length_flags;
    uint32_t operands[3];
};
struct __attribute__((packed)) GlowAssetField458 {
    uint16_t opcode;
    uint8_t control, length_flags;
    uint32_t operands[3];
};
struct __attribute__((packed)) GlowAssetField459 {
    uint16_t opcode;
    uint8_t control, length_flags;
    uint32_t operands[3];
};
struct __attribute__((packed)) GlowAssetField460 {
    uint16_t opcode;
    uint8_t control, length_flags;
    uint32_t operands[3];
};
struct __attribute__((packed)) GlowAssetField461 {
    uint16_t opcode;
    uint8_t control, length_flags;
    uint32_t operands[3];
};
struct __attribute__((packed)) GlowAssetField462 {
    uint16_t opcode;
    uint8_t control, length_flags;
    uint32_t operands[3];
};
struct __attribute__((packed)) GlowAssetField463 {
    uint16_t opcode;
    uint8_t control, length_flags;
    uint32_t operands[3];
};
struct __attribute__((packed)) GlowAssetField464 {
    uint16_t opcode;
    uint8_t control, length_flags;
    uint32_t operands[3];
};
struct __attribute__((packed)) GlowAssetField465 {
    uint16_t opcode;
    uint8_t control, length_flags;
    uint32_t operands[3];
};
struct __attribute__((packed)) GlowAssetField466 {
    uint16_t opcode;
    uint8_t control, length_flags;
    uint32_t operands[3];
};
struct __attribute__((packed)) GlowAssetField467 {
    uint16_t opcode;
    uint8_t control, length_flags;
    uint32_t operands[3];
};
struct __attribute__((packed)) GlowAssetField468 {
    uint16_t opcode;
    uint8_t control, length_flags;
    uint32_t operands[3];
};
struct __attribute__((packed)) GlowAssetField469 {
    uint16_t opcode;
    uint8_t control, length_flags;
    uint32_t operands[2];
};
struct __attribute__((packed)) GlowAssetField470 {
    uint16_t opcode;
    uint8_t control, length_flags;
    uint32_t operands[2];
};
struct __attribute__((packed)) GlowAssetField471 {
    uint32_t opcode;
};
struct __attribute__((packed)) GlowAssetField472 {
    uint32_t technique;
    uint32_t pass_index;
    uint32_t element;
    uint32_t state;
    uint32_t usage;
    uint32_t bytes;
};
struct __attribute__((packed)) GlowAssetField473 {
    char name[14];
    uint8_t alignment_padding[2];
};
struct __attribute__((packed)) EmbeddedGlowEffect {
    GlowAssetField0 field_0000_effect_header;                 // effect_header
    GlowAssetField1 field_0008_length_prefixed_name;          // length_prefixed_name
    GlowAssetField2 field_000c_effect_type;                   // effect_type
    GlowAssetField3 field_0020_effect_object_id;              // effect_object_id
    GlowAssetField4 field_0024_length_prefixed_name;          // length_prefixed_name
    GlowAssetField5 field_0038_effect_type;                   // effect_type
    GlowAssetField6 field_0054_numeric_parameter_default;     // numeric_parameter_default
    GlowAssetField7 field_0058_length_prefixed_name;          // length_prefixed_name
    GlowAssetField8 field_0068_effect_type;                   // effect_type
    GlowAssetField9 field_0084_numeric_parameter_default;     // numeric_parameter_default
    GlowAssetField10 field_0088_length_prefixed_name;         // length_prefixed_name
    GlowAssetField11 field_0098_effect_type;                  // effect_type
    GlowAssetField12 field_00b4_numeric_parameter_default;    // numeric_parameter_default
    GlowAssetField13 field_00b8_length_prefixed_name;         // length_prefixed_name
    GlowAssetField14 field_00c8_effect_type;                  // effect_type
    GlowAssetField15 field_00dc_effect_object_id;             // effect_object_id
    GlowAssetField16 field_00e0_effect_type;                  // effect_type
    GlowAssetField17 field_00f4_numeric_parameter_default;    // numeric_parameter_default
    GlowAssetField18 field_00f8_effect_type;                  // effect_type
    GlowAssetField19 field_0114_numeric_parameter_default;    // numeric_parameter_default
    GlowAssetField20 field_0118_effect_type;                  // effect_type
    GlowAssetField21 field_0134_numeric_parameter_default;    // numeric_parameter_default
    GlowAssetField22 field_0138_effect_type;                  // effect_type
    GlowAssetField23 field_0154_numeric_parameter_default;    // numeric_parameter_default
    GlowAssetField24 field_0158_effect_type;                  // effect_type
    GlowAssetField25 field_0174_numeric_parameter_default;    // numeric_parameter_default
    GlowAssetField26 field_0178_effect_type;                  // effect_type
    GlowAssetField27 field_0194_sampler_state_count;          // sampler_state_count
    GlowAssetField28 field_0198_effect_state;                 // effect_state
    GlowAssetField29 field_01a8_effect_state;                 // effect_state
    GlowAssetField30 field_01b8_effect_state;                 // effect_state
    GlowAssetField31 field_01c8_effect_state;                 // effect_state
    GlowAssetField32 field_01d8_effect_state;                 // effect_state
    GlowAssetField33 field_01e8_effect_state;                 // effect_state
    GlowAssetField34 field_01f8_length_prefixed_name;         // length_prefixed_name
    GlowAssetField35 field_020c_numeric_parameter_default;    // numeric_parameter_default
    GlowAssetField36 field_0210_effect_type;                  // effect_type
    GlowAssetField37 field_022c_numeric_parameter_default;    // numeric_parameter_default
    GlowAssetField38 field_0230_effect_type;                  // effect_type
    GlowAssetField39 field_024c_numeric_parameter_default;    // numeric_parameter_default
    GlowAssetField40 field_0250_effect_type;                  // effect_type
    GlowAssetField41 field_026c_numeric_parameter_default;    // numeric_parameter_default
    GlowAssetField42 field_0270_effect_type;                  // effect_type
    GlowAssetField43 field_028c_effect_object_id;             // effect_object_id
    GlowAssetField44 field_0290_effect_type;                  // effect_type
    GlowAssetField45 field_02a4_length_prefixed_name;         // length_prefixed_name
    GlowAssetField46 field_02ac_length_prefixed_name;         // length_prefixed_name
    GlowAssetField47 field_02bc_effect_type;                  // effect_type
    GlowAssetField48 field_02d8_numeric_parameter_default;    // numeric_parameter_default
    GlowAssetField49 field_02dc_length_prefixed_name;         // length_prefixed_name
    GlowAssetField50 field_02ec_effect_type;                  // effect_type
    GlowAssetField51 field_0308_numeric_parameter_default;    // numeric_parameter_default
    GlowAssetField52 field_0378_length_prefixed_name;         // length_prefixed_name
    GlowAssetField53 field_038c_effect_type;                  // effect_type
    GlowAssetField54 field_03a8_numeric_parameter_default;    // numeric_parameter_default
    GlowAssetField55 field_0418_length_prefixed_name;         // length_prefixed_name
    GlowAssetField56 field_042c_effect_type;                  // effect_type
    GlowAssetField57 field_0448_numeric_parameter_default;    // numeric_parameter_default
    GlowAssetField58 field_044c_length_prefixed_name;         // length_prefixed_name
    GlowAssetField59 field_045c_effect_type;                  // effect_type
    GlowAssetField60 field_0478_numeric_parameter_default;    // numeric_parameter_default
    GlowAssetField61 field_047c_length_prefixed_name;         // length_prefixed_name
    GlowAssetField62 field_048c_effect_type;                  // effect_type
    GlowAssetField63 field_04a0_effect_object_id;             // effect_object_id
    GlowAssetField64 field_04a4_effect_type;                  // effect_type
    GlowAssetField65 field_04b8_numeric_parameter_default;    // numeric_parameter_default
    GlowAssetField66 field_04bc_effect_type;                  // effect_type
    GlowAssetField67 field_04d8_numeric_parameter_default;    // numeric_parameter_default
    GlowAssetField68 field_04dc_effect_type;                  // effect_type
    GlowAssetField69 field_04f8_numeric_parameter_default;    // numeric_parameter_default
    GlowAssetField70 field_04fc_effect_type;                  // effect_type
    GlowAssetField71 field_0518_numeric_parameter_default;    // numeric_parameter_default
    GlowAssetField72 field_051c_effect_type;                  // effect_type
    GlowAssetField73 field_0538_numeric_parameter_default;    // numeric_parameter_default
    GlowAssetField74 field_053c_effect_type;                  // effect_type
    GlowAssetField75 field_0558_sampler_state_count;          // sampler_state_count
    GlowAssetField76 field_055c_effect_state;                 // effect_state
    GlowAssetField77 field_056c_effect_state;                 // effect_state
    GlowAssetField78 field_057c_effect_state;                 // effect_state
    GlowAssetField79 field_058c_effect_state;                 // effect_state
    GlowAssetField80 field_059c_effect_state;                 // effect_state
    GlowAssetField81 field_05ac_effect_state;                 // effect_state
    GlowAssetField82 field_05bc_length_prefixed_name;         // length_prefixed_name
    GlowAssetField83 field_05cc_numeric_parameter_default;    // numeric_parameter_default
    GlowAssetField84 field_05d0_effect_type;                  // effect_type
    GlowAssetField85 field_05ec_numeric_parameter_default;    // numeric_parameter_default
    GlowAssetField86 field_05f0_effect_type;                  // effect_type
    GlowAssetField87 field_060c_numeric_parameter_default;    // numeric_parameter_default
    GlowAssetField88 field_0610_effect_type;                  // effect_type
    GlowAssetField89 field_062c_numeric_parameter_default;    // numeric_parameter_default
    GlowAssetField90 field_0630_effect_type;                  // effect_type
    GlowAssetField91 field_064c_effect_object_id;             // effect_object_id
    GlowAssetField92 field_0650_effect_type;                  // effect_type
    GlowAssetField93 field_0664_length_prefixed_name;         // length_prefixed_name
    GlowAssetField94 field_066c_numeric_parameter_default;    // numeric_parameter_default
    GlowAssetField95 field_0670_effect_type;                  // effect_type
    GlowAssetField96 field_068c_numeric_parameter_default;    // numeric_parameter_default
    GlowAssetField97 field_0690_effect_type;                  // effect_type
    GlowAssetField98 field_06ac_numeric_parameter_default;    // numeric_parameter_default
    GlowAssetField99 field_06b0_effect_type;                  // effect_type
    GlowAssetField100 field_06cc_numeric_parameter_default;   // numeric_parameter_default
    GlowAssetField101 field_06d0_effect_type;                 // effect_type
    GlowAssetField102 field_06ec_effect_object_id;            // effect_object_id
    GlowAssetField103 field_06f0_effect_type;                 // effect_type
    GlowAssetField104 field_0704_length_prefixed_name;        // length_prefixed_name
    GlowAssetField105 field_070c_length_prefixed_name;        // length_prefixed_name
    GlowAssetField106 field_0728_effect_counts;               // effect_counts
    GlowAssetField107 field_0738_top_level_parameter;         // top_level_parameter
    GlowAssetField108 field_0748_top_level_parameter;         // top_level_parameter
    GlowAssetField109 field_0758_top_level_parameter;         // top_level_parameter
    GlowAssetField110 field_0768_top_level_parameter;         // top_level_parameter
    GlowAssetField111 field_0778_top_level_parameter;         // top_level_parameter
    GlowAssetField112 field_0788_top_level_parameter;         // top_level_parameter
    GlowAssetField113 field_0798_top_level_parameter;         // top_level_parameter
    GlowAssetField114 field_07a8_top_level_parameter;         // top_level_parameter
    GlowAssetField115 field_07b8_top_level_parameter;         // top_level_parameter
    GlowAssetField116 field_07c8_top_level_parameter;         // top_level_parameter
    GlowAssetField117 field_07d8_top_level_parameter;         // top_level_parameter
    GlowAssetField118 field_07e8_technique;                   // technique
    GlowAssetField119 field_07f4_pass;                        // pass
    GlowAssetField120 field_0800_effect_state;                // effect_state
    GlowAssetField121 field_0810_effect_state;                // effect_state
    GlowAssetField122 field_0820_effect_state;                // effect_state
    GlowAssetField123 field_0830_effect_state;                // effect_state
    GlowAssetField124 field_0840_effect_state;                // effect_state
    GlowAssetField125 field_0850_technique;                   // technique
    GlowAssetField126 field_085c_pass;                        // pass
    GlowAssetField127 field_0868_effect_state;                // effect_state
    GlowAssetField128 field_0878_effect_state;                // effect_state
    GlowAssetField129 field_0888_effect_state;                // effect_state
    GlowAssetField130 field_0898_effect_state;                // effect_state
    GlowAssetField131 field_08a8_effect_state;                // effect_state
    GlowAssetField132 field_08b8_pass;                        // pass
    GlowAssetField133 field_08c4_effect_state;                // effect_state
    GlowAssetField134 field_08d4_effect_state;                // effect_state
    GlowAssetField135 field_08e4_effect_state;                // effect_state
    GlowAssetField136 field_08f4_effect_state;                // effect_state
    GlowAssetField137 field_0904_effect_state;                // effect_state
    GlowAssetField138 field_0914_effect_object_counts;        // effect_object_counts
    GlowAssetField139 field_091c_string_object_header;        // string_object_header
    GlowAssetField140 field_0924_resource_header;             // resource_header
    GlowAssetField141 field_093c_pixel_shader_version;        // pixel_shader_version
    GlowAssetField142 field_0940_shader_comment_token;        // shader_comment_token
    GlowAssetField143 field_0944_shader_comment_fourcc;       // shader_comment_fourcc
    GlowAssetField144 field_0948_constant_table_header;       // constant_table_header
    GlowAssetField145 field_0964_constant_table_entry;        // constant_table_entry
    GlowAssetField146 field_0978_constant_table_entry;        // constant_table_entry
    GlowAssetField147 field_098c_constant_table_entry;        // constant_table_entry
    GlowAssetField148 field_09a0_constant_table_entry;        // constant_table_entry
    GlowAssetField149 field_09b4_shader_name;                 // shader_name
    GlowAssetField150 field_09bd_alignment_padding;           // alignment_padding
    GlowAssetField151 field_09c0_shader_type_information;     // shader_type_information
    GlowAssetField152 field_09d0_shader_name;                 // shader_name
    GlowAssetField153 field_09d9_alignment_padding;           // alignment_padding
    GlowAssetField154 field_09dc_shader_type_information;     // shader_type_information
    GlowAssetField155 field_09ec_shader_default_registers;    // shader_default_registers
    GlowAssetField156 field_09fc_shader_name;                 // shader_name
    GlowAssetField157 field_0a09_alignment_padding;           // alignment_padding
    GlowAssetField158 field_0a0c_shader_type_information;     // shader_type_information
    GlowAssetField159 field_0a1c_shader_default_registers;    // shader_default_registers
    GlowAssetField160 field_0a8c_shader_name;                 // shader_name
    GlowAssetField161 field_0a96_alignment_padding;           // alignment_padding
    GlowAssetField162 field_0a98_shader_default_registers;    // shader_default_registers
    GlowAssetField163 field_0aa8_shader_name;                 // shader_name
    GlowAssetField164 field_0aaf_shader_name;                 // shader_name
    GlowAssetField165 field_0ae1_alignment_padding;           // alignment_padding
    GlowAssetField166 field_0ae4_shader_comment_token;        // shader_comment_token
    GlowAssetField167 field_0ae8_shader_comment_fourcc;       // shader_comment_fourcc
    GlowAssetField168 field_0aec_preshader_version;           // preshader_version
    GlowAssetField169 field_0af0_shader_comment_token;        // shader_comment_token
    GlowAssetField170 field_0af4_shader_comment_fourcc;       // shader_comment_fourcc
    GlowAssetField171 field_0af8_constant_table_header;       // constant_table_header
    GlowAssetField172 field_0b14_constant_table_entry;        // constant_table_entry
    GlowAssetField173 field_0b28_constant_table_entry;        // constant_table_entry
    GlowAssetField174 field_0b3c_shader_name;                 // shader_name
    GlowAssetField175 field_0b49_alignment_padding;           // alignment_padding
    GlowAssetField176 field_0b4c_shader_type_information;     // shader_type_information
    GlowAssetField177 field_0b5c_shader_default_registers;    // shader_default_registers
    GlowAssetField178 field_0bcc_shader_name;                 // shader_name
    GlowAssetField179 field_0bd6_alignment_padding;           // alignment_padding
    GlowAssetField180 field_0bd8_shader_type_information;     // shader_type_information
    GlowAssetField181 field_0be8_shader_default_registers;    // shader_default_registers
    GlowAssetField182 field_0bf8_shader_name;                 // shader_name
    GlowAssetField183 field_0bfb_shader_name;                 // shader_name
    GlowAssetField184 field_0c2d_alignment_padding;           // alignment_padding
    GlowAssetField185 field_0c30_shader_comment_token;        // shader_comment_token
    GlowAssetField186 field_0c34_shader_comment_fourcc;       // shader_comment_fourcc
    GlowAssetField187 field_0c38_preshader_register_segments; // preshader_register_segments
    GlowAssetField188 field_0c64_shader_comment_token;        // shader_comment_token
    GlowAssetField189 field_0c68_shader_comment_fourcc;       // shader_comment_fourcc
    GlowAssetField190 field_0c6c_preshader_literal_count;     // preshader_literal_count
    GlowAssetField191 field_0c70_shader_comment_token;        // shader_comment_token
    GlowAssetField192 field_0c74_shader_comment_fourcc;       // shader_comment_fourcc
    GlowAssetField193 field_0c78_preshader_instruction_count; // preshader_instruction_count
    GlowAssetField194 field_0c7c_preshader_instruction;       // preshader_instruction
    GlowAssetField195 field_0ca8_preshader_instruction;       // preshader_instruction
    GlowAssetField196 field_0cd4_preshader_instruction;       // preshader_instruction
    GlowAssetField197 field_0d00_preshader_instruction;       // preshader_instruction
    GlowAssetField198 field_0d2c_preshader_instruction;       // preshader_instruction
    GlowAssetField199 field_0d58_preshader_instruction;       // preshader_instruction
    GlowAssetField200 field_0d84_preshader_instruction;       // preshader_instruction
    GlowAssetField201 field_0db0_preshader_instruction;       // preshader_instruction
    GlowAssetField202 field_0ddc_preshader_instruction;       // preshader_instruction
    GlowAssetField203 field_0e08_preshader_instruction;       // preshader_instruction
    GlowAssetField204 field_0e34_preshader_instruction;       // preshader_instruction
    GlowAssetField205 field_0e60_preshader_instruction;       // preshader_instruction
    GlowAssetField206 field_0e8c_preshader_instruction;       // preshader_instruction
    GlowAssetField207 field_0eb8_preshader_instruction;       // preshader_instruction
    GlowAssetField208 field_0ee4_preshader_code_footer;       // preshader_code_footer
    GlowAssetField209 field_0eec_shader_end_token;            // shader_end_token
    GlowAssetField210 field_0ef0_pixel_shader_instruction;    // pixel_shader_instruction dcl
    GlowAssetField211 field_0efc_pixel_shader_instruction;    // pixel_shader_instruction dcl
    GlowAssetField212 field_0f08_pixel_shader_instruction;    // pixel_shader_instruction add
    GlowAssetField213 field_0f18_pixel_shader_instruction;    // pixel_shader_instruction add
    GlowAssetField214 field_0f28_pixel_shader_instruction;    // pixel_shader_instruction add
    GlowAssetField215 field_0f38_pixel_shader_instruction;    // pixel_shader_instruction add
    GlowAssetField216 field_0f48_pixel_shader_instruction;    // pixel_shader_instruction add
    GlowAssetField217 field_0f58_pixel_shader_instruction;    // pixel_shader_instruction add
    GlowAssetField218 field_0f68_pixel_shader_instruction;    // pixel_shader_instruction add
    GlowAssetField219 field_0f78_pixel_shader_instruction;    // pixel_shader_instruction add
    GlowAssetField220 field_0f88_pixel_shader_instruction;    // pixel_shader_instruction add
    GlowAssetField221 field_0f98_pixel_shader_instruction;    // pixel_shader_instruction add
    GlowAssetField222 field_0fa8_pixel_shader_instruction;    // pixel_shader_instruction add
    GlowAssetField223 field_0fb8_pixel_shader_instruction;    // pixel_shader_instruction add
    GlowAssetField224 field_0fc8_pixel_shader_instruction;    // pixel_shader_instruction add
    GlowAssetField225 field_0fd8_pixel_shader_instruction;    // pixel_shader_instruction add
    GlowAssetField226 field_0fe8_pixel_shader_instruction;    // pixel_shader_instruction add
    GlowAssetField227 field_0ff8_pixel_shader_instruction;    // pixel_shader_instruction add
    GlowAssetField228 field_1008_pixel_shader_instruction;    // pixel_shader_instruction add
    GlowAssetField229 field_1018_pixel_shader_instruction;    // pixel_shader_instruction add
    GlowAssetField230 field_1028_pixel_shader_instruction;    // pixel_shader_instruction add
    GlowAssetField231 field_1038_pixel_shader_instruction;    // pixel_shader_instruction add
    GlowAssetField232 field_1048_pixel_shader_instruction;    // pixel_shader_instruction add
    GlowAssetField233 field_1058_pixel_shader_instruction;    // pixel_shader_instruction add
    GlowAssetField234 field_1068_pixel_shader_instruction;    // pixel_shader_instruction add
    GlowAssetField235 field_1078_pixel_shader_instruction;    // pixel_shader_instruction add
    GlowAssetField236 field_1088_pixel_shader_instruction;    // pixel_shader_instruction add
    GlowAssetField237 field_1098_pixel_shader_instruction;    // pixel_shader_instruction add
    GlowAssetField238 field_10a8_pixel_shader_instruction;    // pixel_shader_instruction add
    GlowAssetField239 field_10b8_pixel_shader_instruction;    // pixel_shader_instruction add
    GlowAssetField240 field_10c8_pixel_shader_instruction;    // pixel_shader_instruction texld
    GlowAssetField241 field_10d8_pixel_shader_instruction;    // pixel_shader_instruction texld
    GlowAssetField242 field_10e8_pixel_shader_instruction;    // pixel_shader_instruction texld
    GlowAssetField243 field_10f8_pixel_shader_instruction;    // pixel_shader_instruction texld
    GlowAssetField244 field_1108_pixel_shader_instruction;    // pixel_shader_instruction texld
    GlowAssetField245 field_1118_pixel_shader_instruction;    // pixel_shader_instruction texld
    GlowAssetField246 field_1128_pixel_shader_instruction;    // pixel_shader_instruction texld
    GlowAssetField247 field_1138_pixel_shader_instruction;    // pixel_shader_instruction mul
    GlowAssetField248 field_1148_pixel_shader_instruction;    // pixel_shader_instruction mad
    GlowAssetField249 field_115c_pixel_shader_instruction;    // pixel_shader_instruction mad
    GlowAssetField250 field_1170_pixel_shader_instruction;    // pixel_shader_instruction mad
    GlowAssetField251 field_1184_pixel_shader_instruction;    // pixel_shader_instruction mad
    GlowAssetField252 field_1198_pixel_shader_instruction;    // pixel_shader_instruction mad
    GlowAssetField253 field_11ac_pixel_shader_instruction;    // pixel_shader_instruction mad
    GlowAssetField254 field_11c0_pixel_shader_instruction;    // pixel_shader_instruction mov
    GlowAssetField255 field_11cc_pixel_shader_instruction;    // pixel_shader_instruction mov
    GlowAssetField256 field_11d8_shader_end_token;            // shader_end_token
    GlowAssetField257 field_11dc_resource_header;             // resource_header
    GlowAssetField258 field_11f4_pixel_shader_version;        // pixel_shader_version
    GlowAssetField259 field_11f8_shader_comment_token;        // shader_comment_token
    GlowAssetField260 field_11fc_shader_comment_fourcc;       // shader_comment_fourcc
    GlowAssetField261 field_1200_constant_table_header;       // constant_table_header
    GlowAssetField262 field_121c_constant_table_entry;        // constant_table_entry
    GlowAssetField263 field_1230_constant_table_entry;        // constant_table_entry
    GlowAssetField264 field_1244_constant_table_entry;        // constant_table_entry
    GlowAssetField265 field_1258_constant_table_entry;        // constant_table_entry
    GlowAssetField266 field_126c_shader_name;                 // shader_name
    GlowAssetField267 field_1275_alignment_padding;           // alignment_padding
    GlowAssetField268 field_1278_shader_type_information;     // shader_type_information
    GlowAssetField269 field_1288_shader_name;                 // shader_name
    GlowAssetField270 field_1291_alignment_padding;           // alignment_padding
    GlowAssetField271 field_1294_shader_type_information;     // shader_type_information
    GlowAssetField272 field_12a4_shader_default_registers;    // shader_default_registers
    GlowAssetField273 field_12b4_shader_name;                 // shader_name
    GlowAssetField274 field_12c1_alignment_padding;           // alignment_padding
    GlowAssetField275 field_12c4_shader_type_information;     // shader_type_information
    GlowAssetField276 field_12d4_shader_default_registers;    // shader_default_registers
    GlowAssetField277 field_1344_shader_name;                 // shader_name
    GlowAssetField278 field_134e_alignment_padding;           // alignment_padding
    GlowAssetField279 field_1350_shader_default_registers;    // shader_default_registers
    GlowAssetField280 field_1360_shader_name;                 // shader_name
    GlowAssetField281 field_1367_shader_name;                 // shader_name
    GlowAssetField282 field_1399_alignment_padding;           // alignment_padding
    GlowAssetField283 field_139c_shader_comment_token;        // shader_comment_token
    GlowAssetField284 field_13a0_shader_comment_fourcc;       // shader_comment_fourcc
    GlowAssetField285 field_13a4_preshader_version;           // preshader_version
    GlowAssetField286 field_13a8_shader_comment_token;        // shader_comment_token
    GlowAssetField287 field_13ac_shader_comment_fourcc;       // shader_comment_fourcc
    GlowAssetField288 field_13b0_constant_table_header;       // constant_table_header
    GlowAssetField289 field_13cc_constant_table_entry;        // constant_table_entry
    GlowAssetField290 field_13e0_constant_table_entry;        // constant_table_entry
    GlowAssetField291 field_13f4_shader_name;                 // shader_name
    GlowAssetField292 field_1401_alignment_padding;           // alignment_padding
    GlowAssetField293 field_1404_shader_type_information;     // shader_type_information
    GlowAssetField294 field_1414_shader_default_registers;    // shader_default_registers
    GlowAssetField295 field_1484_shader_name;                 // shader_name
    GlowAssetField296 field_148e_alignment_padding;           // alignment_padding
    GlowAssetField297 field_1490_shader_type_information;     // shader_type_information
    GlowAssetField298 field_14a0_shader_default_registers;    // shader_default_registers
    GlowAssetField299 field_14b0_shader_name;                 // shader_name
    GlowAssetField300 field_14b3_shader_name;                 // shader_name
    GlowAssetField301 field_14e5_alignment_padding;           // alignment_padding
    GlowAssetField302 field_14e8_shader_comment_token;        // shader_comment_token
    GlowAssetField303 field_14ec_shader_comment_fourcc;       // shader_comment_fourcc
    GlowAssetField304 field_14f0_preshader_register_segments; // preshader_register_segments
    GlowAssetField305 field_151c_shader_comment_token;        // shader_comment_token
    GlowAssetField306 field_1520_shader_comment_fourcc;       // shader_comment_fourcc
    GlowAssetField307 field_1524_preshader_literal_count;     // preshader_literal_count
    GlowAssetField308 field_1528_shader_comment_token;        // shader_comment_token
    GlowAssetField309 field_152c_shader_comment_fourcc;       // shader_comment_fourcc
    GlowAssetField310 field_1530_preshader_instruction_count; // preshader_instruction_count
    GlowAssetField311 field_1534_preshader_instruction;       // preshader_instruction
    GlowAssetField312 field_1560_preshader_instruction;       // preshader_instruction
    GlowAssetField313 field_158c_preshader_instruction;       // preshader_instruction
    GlowAssetField314 field_15b8_preshader_instruction;       // preshader_instruction
    GlowAssetField315 field_15e4_preshader_instruction;       // preshader_instruction
    GlowAssetField316 field_1610_preshader_instruction;       // preshader_instruction
    GlowAssetField317 field_163c_preshader_instruction;       // preshader_instruction
    GlowAssetField318 field_1668_preshader_instruction;       // preshader_instruction
    GlowAssetField319 field_1694_preshader_instruction;       // preshader_instruction
    GlowAssetField320 field_16c0_preshader_instruction;       // preshader_instruction
    GlowAssetField321 field_16ec_preshader_instruction;       // preshader_instruction
    GlowAssetField322 field_1718_preshader_instruction;       // preshader_instruction
    GlowAssetField323 field_1744_preshader_instruction;       // preshader_instruction
    GlowAssetField324 field_1770_preshader_instruction;       // preshader_instruction
    GlowAssetField325 field_179c_preshader_code_footer;       // preshader_code_footer
    GlowAssetField326 field_17a4_shader_end_token;            // shader_end_token
    GlowAssetField327 field_17a8_pixel_shader_instruction;    // pixel_shader_instruction dcl
    GlowAssetField328 field_17b4_pixel_shader_instruction;    // pixel_shader_instruction dcl
    GlowAssetField329 field_17c0_pixel_shader_instruction;    // pixel_shader_instruction add
    GlowAssetField330 field_17d0_pixel_shader_instruction;    // pixel_shader_instruction add
    GlowAssetField331 field_17e0_pixel_shader_instruction;    // pixel_shader_instruction add
    GlowAssetField332 field_17f0_pixel_shader_instruction;    // pixel_shader_instruction add
    GlowAssetField333 field_1800_pixel_shader_instruction;    // pixel_shader_instruction add
    GlowAssetField334 field_1810_pixel_shader_instruction;    // pixel_shader_instruction add
    GlowAssetField335 field_1820_pixel_shader_instruction;    // pixel_shader_instruction add
    GlowAssetField336 field_1830_pixel_shader_instruction;    // pixel_shader_instruction add
    GlowAssetField337 field_1840_pixel_shader_instruction;    // pixel_shader_instruction add
    GlowAssetField338 field_1850_pixel_shader_instruction;    // pixel_shader_instruction add
    GlowAssetField339 field_1860_pixel_shader_instruction;    // pixel_shader_instruction add
    GlowAssetField340 field_1870_pixel_shader_instruction;    // pixel_shader_instruction add
    GlowAssetField341 field_1880_pixel_shader_instruction;    // pixel_shader_instruction add
    GlowAssetField342 field_1890_pixel_shader_instruction;    // pixel_shader_instruction add
    GlowAssetField343 field_18a0_pixel_shader_instruction;    // pixel_shader_instruction add
    GlowAssetField344 field_18b0_pixel_shader_instruction;    // pixel_shader_instruction add
    GlowAssetField345 field_18c0_pixel_shader_instruction;    // pixel_shader_instruction add
    GlowAssetField346 field_18d0_pixel_shader_instruction;    // pixel_shader_instruction add
    GlowAssetField347 field_18e0_pixel_shader_instruction;    // pixel_shader_instruction add
    GlowAssetField348 field_18f0_pixel_shader_instruction;    // pixel_shader_instruction add
    GlowAssetField349 field_1900_pixel_shader_instruction;    // pixel_shader_instruction add
    GlowAssetField350 field_1910_pixel_shader_instruction;    // pixel_shader_instruction add
    GlowAssetField351 field_1920_pixel_shader_instruction;    // pixel_shader_instruction add
    GlowAssetField352 field_1930_pixel_shader_instruction;    // pixel_shader_instruction add
    GlowAssetField353 field_1940_pixel_shader_instruction;    // pixel_shader_instruction add
    GlowAssetField354 field_1950_pixel_shader_instruction;    // pixel_shader_instruction add
    GlowAssetField355 field_1960_pixel_shader_instruction;    // pixel_shader_instruction add
    GlowAssetField356 field_1970_pixel_shader_instruction;    // pixel_shader_instruction add
    GlowAssetField357 field_1980_pixel_shader_instruction;    // pixel_shader_instruction texld
    GlowAssetField358 field_1990_pixel_shader_instruction;    // pixel_shader_instruction texld
    GlowAssetField359 field_19a0_pixel_shader_instruction;    // pixel_shader_instruction texld
    GlowAssetField360 field_19b0_pixel_shader_instruction;    // pixel_shader_instruction texld
    GlowAssetField361 field_19c0_pixel_shader_instruction;    // pixel_shader_instruction texld
    GlowAssetField362 field_19d0_pixel_shader_instruction;    // pixel_shader_instruction texld
    GlowAssetField363 field_19e0_pixel_shader_instruction;    // pixel_shader_instruction texld
    GlowAssetField364 field_19f0_pixel_shader_instruction;    // pixel_shader_instruction mul
    GlowAssetField365 field_1a00_pixel_shader_instruction;    // pixel_shader_instruction mad
    GlowAssetField366 field_1a14_pixel_shader_instruction;    // pixel_shader_instruction mad
    GlowAssetField367 field_1a28_pixel_shader_instruction;    // pixel_shader_instruction mad
    GlowAssetField368 field_1a3c_pixel_shader_instruction;    // pixel_shader_instruction mad
    GlowAssetField369 field_1a50_pixel_shader_instruction;    // pixel_shader_instruction mad
    GlowAssetField370 field_1a64_pixel_shader_instruction;    // pixel_shader_instruction mad
    GlowAssetField371 field_1a78_pixel_shader_instruction;    // pixel_shader_instruction mov
    GlowAssetField372 field_1a84_pixel_shader_instruction;    // pixel_shader_instruction mov
    GlowAssetField373 field_1a90_shader_end_token;            // shader_end_token
    GlowAssetField374 field_1a94_resource_header;             // resource_header
    GlowAssetField375 field_1aac_state_parameter_name;        // state_parameter_name
    GlowAssetField376 field_1abc_resource_header;             // resource_header
    GlowAssetField377 field_1ad4_pixel_shader_version;        // pixel_shader_version
    GlowAssetField378 field_1ad8_shader_comment_token;        // shader_comment_token
    GlowAssetField379 field_1adc_shader_comment_fourcc;       // shader_comment_fourcc
    GlowAssetField380 field_1ae0_constant_table_header;       // constant_table_header
    GlowAssetField381 field_1afc_constant_table_entry;        // constant_table_entry
    GlowAssetField382 field_1b10_constant_table_entry;        // constant_table_entry
    GlowAssetField383 field_1b24_shader_name;                 // shader_name
    GlowAssetField384 field_1b2d_alignment_padding;           // alignment_padding
    GlowAssetField385 field_1b30_shader_type_information;     // shader_type_information
    GlowAssetField386 field_1b40_shader_default_registers;    // shader_default_registers
    GlowAssetField387 field_1b50_shader_name;                 // shader_name
    GlowAssetField388 field_1b5e_alignment_padding;           // alignment_padding
    GlowAssetField389 field_1b60_shader_type_information;     // shader_type_information
    GlowAssetField390 field_1b70_shader_name;                 // shader_name
    GlowAssetField391 field_1b77_shader_name;                 // shader_name
    GlowAssetField392 field_1ba9_alignment_padding;           // alignment_padding
    GlowAssetField393 field_1bac_shader_comment_token;        // shader_comment_token
    GlowAssetField394 field_1bb0_shader_comment_fourcc;       // shader_comment_fourcc
    GlowAssetField395 field_1bb4_preshader_version;           // preshader_version
    GlowAssetField396 field_1bb8_shader_comment_token;        // shader_comment_token
    GlowAssetField397 field_1bbc_shader_comment_fourcc;       // shader_comment_fourcc
    GlowAssetField398 field_1bc0_constant_table_header;       // constant_table_header
    GlowAssetField399 field_1bdc_constant_table_entry;        // constant_table_entry
    GlowAssetField400 field_1bf0_constant_table_entry;        // constant_table_entry
    GlowAssetField401 field_1c04_shader_name;                 // shader_name
    GlowAssetField402 field_1c0f_alignment_padding;           // alignment_padding
    GlowAssetField403 field_1c10_shader_type_information;     // shader_type_information
    GlowAssetField404 field_1c20_shader_default_registers;    // shader_default_registers
    GlowAssetField405 field_1c30_shader_name;                 // shader_name
    GlowAssetField406 field_1c3a_shader_name;                 // shader_name
    GlowAssetField407 field_1c3d_shader_name;                 // shader_name
    GlowAssetField408 field_1c6f_alignment_padding;           // alignment_padding
    GlowAssetField409 field_1c70_shader_comment_token;        // shader_comment_token
    GlowAssetField410 field_1c74_shader_comment_fourcc;       // shader_comment_fourcc
    GlowAssetField411 field_1c78_preshader_register_segments; // preshader_register_segments
    GlowAssetField412 field_1ca4_shader_comment_token;        // shader_comment_token
    GlowAssetField413 field_1ca8_shader_comment_fourcc;       // shader_comment_fourcc
    GlowAssetField414 field_1cac_preshader_literal_count;     // preshader_literal_count
    GlowAssetField415 field_1cb0_preshader_binary64_literals; // preshader_binary64_literals
    GlowAssetField416 field_1d10_shader_comment_token;        // shader_comment_token
    GlowAssetField417 field_1d14_shader_comment_fourcc;       // shader_comment_fourcc
    GlowAssetField418 field_1d18_preshader_instruction_count; // preshader_instruction_count
    GlowAssetField419 field_1d1c_preshader_instruction;       // preshader_instruction
    GlowAssetField420 field_1d3c_preshader_instruction;       // preshader_instruction
    GlowAssetField421 field_1d68_preshader_instruction;       // preshader_instruction
    GlowAssetField422 field_1d94_preshader_instruction;       // preshader_instruction
    GlowAssetField423 field_1db4_preshader_instruction;       // preshader_instruction
    GlowAssetField424 field_1de0_preshader_instruction;       // preshader_instruction
    GlowAssetField425 field_1e0c_preshader_instruction;       // preshader_instruction
    GlowAssetField426 field_1e2c_preshader_code_footer;       // preshader_code_footer
    GlowAssetField427 field_1e34_shader_end_token;            // shader_end_token
    GlowAssetField428 field_1e38_pixel_shader_instruction;    // pixel_shader_instruction def
    GlowAssetField429 field_1e50_pixel_shader_instruction;    // pixel_shader_instruction dcl
    GlowAssetField430 field_1e5c_pixel_shader_instruction;    // pixel_shader_instruction dcl
    GlowAssetField431 field_1e68_pixel_shader_instruction;    // pixel_shader_instruction mov
    GlowAssetField432 field_1e74_pixel_shader_instruction;    // pixel_shader_instruction mov
    GlowAssetField433 field_1e80_pixel_shader_instruction;    // pixel_shader_instruction add
    GlowAssetField434 field_1e90_pixel_shader_instruction;    // pixel_shader_instruction add
    GlowAssetField435 field_1ea0_pixel_shader_instruction;    // pixel_shader_instruction mov
    GlowAssetField436 field_1eac_pixel_shader_instruction;    // pixel_shader_instruction mov
    GlowAssetField437 field_1eb8_pixel_shader_instruction;    // pixel_shader_instruction add
    GlowAssetField438 field_1ec8_pixel_shader_instruction;    // pixel_shader_instruction add
    GlowAssetField439 field_1ed8_pixel_shader_instruction;    // pixel_shader_instruction mov
    GlowAssetField440 field_1ee4_pixel_shader_instruction;    // pixel_shader_instruction mov
    GlowAssetField441 field_1ef0_pixel_shader_instruction;    // pixel_shader_instruction mov
    GlowAssetField442 field_1efc_pixel_shader_instruction;    // pixel_shader_instruction mov
    GlowAssetField443 field_1f08_pixel_shader_instruction;    // pixel_shader_instruction add
    GlowAssetField444 field_1f18_pixel_shader_instruction;    // pixel_shader_instruction add
    GlowAssetField445 field_1f28_pixel_shader_instruction;    // pixel_shader_instruction mov
    GlowAssetField446 field_1f34_pixel_shader_instruction;    // pixel_shader_instruction mov
    GlowAssetField447 field_1f40_pixel_shader_instruction;    // pixel_shader_instruction mov
    GlowAssetField448 field_1f4c_pixel_shader_instruction;    // pixel_shader_instruction mov
    GlowAssetField449 field_1f58_pixel_shader_instruction;    // pixel_shader_instruction add
    GlowAssetField450 field_1f68_pixel_shader_instruction;    // pixel_shader_instruction add
    GlowAssetField451 field_1f78_pixel_shader_instruction;    // pixel_shader_instruction mov
    GlowAssetField452 field_1f84_pixel_shader_instruction;    // pixel_shader_instruction mov
    GlowAssetField453 field_1f90_pixel_shader_instruction;    // pixel_shader_instruction texld
    GlowAssetField454 field_1fa0_pixel_shader_instruction;    // pixel_shader_instruction texld
    GlowAssetField455 field_1fb0_pixel_shader_instruction;    // pixel_shader_instruction texld
    GlowAssetField456 field_1fc0_pixel_shader_instruction;    // pixel_shader_instruction texld
    GlowAssetField457 field_1fd0_pixel_shader_instruction;    // pixel_shader_instruction texld
    GlowAssetField458 field_1fe0_pixel_shader_instruction;    // pixel_shader_instruction texld
    GlowAssetField459 field_1ff0_pixel_shader_instruction;    // pixel_shader_instruction texld
    GlowAssetField460 field_2000_pixel_shader_instruction;    // pixel_shader_instruction texld
    GlowAssetField461 field_2010_pixel_shader_instruction;    // pixel_shader_instruction add
    GlowAssetField462 field_2020_pixel_shader_instruction;    // pixel_shader_instruction add
    GlowAssetField463 field_2030_pixel_shader_instruction;    // pixel_shader_instruction add
    GlowAssetField464 field_2040_pixel_shader_instruction;    // pixel_shader_instruction add
    GlowAssetField465 field_2050_pixel_shader_instruction;    // pixel_shader_instruction add
    GlowAssetField466 field_2060_pixel_shader_instruction;    // pixel_shader_instruction add
    GlowAssetField467 field_2070_pixel_shader_instruction;    // pixel_shader_instruction add
    GlowAssetField468 field_2080_pixel_shader_instruction;    // pixel_shader_instruction mul
    GlowAssetField469 field_2090_pixel_shader_instruction;    // pixel_shader_instruction mov
    GlowAssetField470 field_209c_pixel_shader_instruction;    // pixel_shader_instruction mov
    GlowAssetField471 field_20a8_shader_end_token;            // shader_end_token
    GlowAssetField472 field_20ac_resource_header;             // resource_header
    GlowAssetField473 field_20c4_state_parameter_name;        // state_parameter_name
};
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_0000_effect_header) == 0x0);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_0008_length_prefixed_name) == 0x8);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_000c_effect_type) == 0xc);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_0020_effect_object_id) == 0x20);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_0024_length_prefixed_name) == 0x24);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_0038_effect_type) == 0x38);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_0054_numeric_parameter_default) == 0x54);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_0058_length_prefixed_name) == 0x58);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_0068_effect_type) == 0x68);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_0084_numeric_parameter_default) == 0x84);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_0088_length_prefixed_name) == 0x88);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_0098_effect_type) == 0x98);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_00b4_numeric_parameter_default) == 0xb4);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_00b8_length_prefixed_name) == 0xb8);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_00c8_effect_type) == 0xc8);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_00dc_effect_object_id) == 0xdc);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_00e0_effect_type) == 0xe0);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_00f4_numeric_parameter_default) == 0xf4);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_00f8_effect_type) == 0xf8);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_0114_numeric_parameter_default) ==
              0x114);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_0118_effect_type) == 0x118);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_0134_numeric_parameter_default) ==
              0x134);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_0138_effect_type) == 0x138);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_0154_numeric_parameter_default) ==
              0x154);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_0158_effect_type) == 0x158);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_0174_numeric_parameter_default) ==
              0x174);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_0178_effect_type) == 0x178);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_0194_sampler_state_count) == 0x194);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_0198_effect_state) == 0x198);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_01a8_effect_state) == 0x1a8);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_01b8_effect_state) == 0x1b8);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_01c8_effect_state) == 0x1c8);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_01d8_effect_state) == 0x1d8);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_01e8_effect_state) == 0x1e8);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_01f8_length_prefixed_name) == 0x1f8);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_020c_numeric_parameter_default) ==
              0x20c);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_0210_effect_type) == 0x210);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_022c_numeric_parameter_default) ==
              0x22c);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_0230_effect_type) == 0x230);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_024c_numeric_parameter_default) ==
              0x24c);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_0250_effect_type) == 0x250);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_026c_numeric_parameter_default) ==
              0x26c);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_0270_effect_type) == 0x270);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_028c_effect_object_id) == 0x28c);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_0290_effect_type) == 0x290);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_02a4_length_prefixed_name) == 0x2a4);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_02ac_length_prefixed_name) == 0x2ac);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_02bc_effect_type) == 0x2bc);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_02d8_numeric_parameter_default) ==
              0x2d8);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_02dc_length_prefixed_name) == 0x2dc);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_02ec_effect_type) == 0x2ec);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_0308_numeric_parameter_default) ==
              0x308);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_0378_length_prefixed_name) == 0x378);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_038c_effect_type) == 0x38c);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_03a8_numeric_parameter_default) ==
              0x3a8);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_0418_length_prefixed_name) == 0x418);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_042c_effect_type) == 0x42c);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_0448_numeric_parameter_default) ==
              0x448);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_044c_length_prefixed_name) == 0x44c);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_045c_effect_type) == 0x45c);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_0478_numeric_parameter_default) ==
              0x478);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_047c_length_prefixed_name) == 0x47c);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_048c_effect_type) == 0x48c);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_04a0_effect_object_id) == 0x4a0);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_04a4_effect_type) == 0x4a4);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_04b8_numeric_parameter_default) ==
              0x4b8);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_04bc_effect_type) == 0x4bc);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_04d8_numeric_parameter_default) ==
              0x4d8);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_04dc_effect_type) == 0x4dc);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_04f8_numeric_parameter_default) ==
              0x4f8);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_04fc_effect_type) == 0x4fc);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_0518_numeric_parameter_default) ==
              0x518);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_051c_effect_type) == 0x51c);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_0538_numeric_parameter_default) ==
              0x538);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_053c_effect_type) == 0x53c);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_0558_sampler_state_count) == 0x558);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_055c_effect_state) == 0x55c);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_056c_effect_state) == 0x56c);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_057c_effect_state) == 0x57c);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_058c_effect_state) == 0x58c);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_059c_effect_state) == 0x59c);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_05ac_effect_state) == 0x5ac);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_05bc_length_prefixed_name) == 0x5bc);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_05cc_numeric_parameter_default) ==
              0x5cc);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_05d0_effect_type) == 0x5d0);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_05ec_numeric_parameter_default) ==
              0x5ec);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_05f0_effect_type) == 0x5f0);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_060c_numeric_parameter_default) ==
              0x60c);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_0610_effect_type) == 0x610);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_062c_numeric_parameter_default) ==
              0x62c);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_0630_effect_type) == 0x630);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_064c_effect_object_id) == 0x64c);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_0650_effect_type) == 0x650);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_0664_length_prefixed_name) == 0x664);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_066c_numeric_parameter_default) ==
              0x66c);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_0670_effect_type) == 0x670);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_068c_numeric_parameter_default) ==
              0x68c);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_0690_effect_type) == 0x690);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_06ac_numeric_parameter_default) ==
              0x6ac);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_06b0_effect_type) == 0x6b0);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_06cc_numeric_parameter_default) ==
              0x6cc);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_06d0_effect_type) == 0x6d0);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_06ec_effect_object_id) == 0x6ec);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_06f0_effect_type) == 0x6f0);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_0704_length_prefixed_name) == 0x704);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_070c_length_prefixed_name) == 0x70c);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_0728_effect_counts) == 0x728);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_0738_top_level_parameter) == 0x738);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_0748_top_level_parameter) == 0x748);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_0758_top_level_parameter) == 0x758);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_0768_top_level_parameter) == 0x768);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_0778_top_level_parameter) == 0x778);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_0788_top_level_parameter) == 0x788);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_0798_top_level_parameter) == 0x798);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_07a8_top_level_parameter) == 0x7a8);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_07b8_top_level_parameter) == 0x7b8);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_07c8_top_level_parameter) == 0x7c8);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_07d8_top_level_parameter) == 0x7d8);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_07e8_technique) == 0x7e8);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_07f4_pass) == 0x7f4);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_0800_effect_state) == 0x800);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_0810_effect_state) == 0x810);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_0820_effect_state) == 0x820);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_0830_effect_state) == 0x830);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_0840_effect_state) == 0x840);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_0850_technique) == 0x850);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_085c_pass) == 0x85c);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_0868_effect_state) == 0x868);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_0878_effect_state) == 0x878);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_0888_effect_state) == 0x888);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_0898_effect_state) == 0x898);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_08a8_effect_state) == 0x8a8);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_08b8_pass) == 0x8b8);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_08c4_effect_state) == 0x8c4);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_08d4_effect_state) == 0x8d4);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_08e4_effect_state) == 0x8e4);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_08f4_effect_state) == 0x8f4);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_0904_effect_state) == 0x904);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_0914_effect_object_counts) == 0x914);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_091c_string_object_header) == 0x91c);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_0924_resource_header) == 0x924);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_093c_pixel_shader_version) == 0x93c);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_0940_shader_comment_token) == 0x940);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_0944_shader_comment_fourcc) == 0x944);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_0948_constant_table_header) == 0x948);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_0964_constant_table_entry) == 0x964);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_0978_constant_table_entry) == 0x978);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_098c_constant_table_entry) == 0x98c);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_09a0_constant_table_entry) == 0x9a0);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_09b4_shader_name) == 0x9b4);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_09bd_alignment_padding) == 0x9bd);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_09c0_shader_type_information) == 0x9c0);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_09d0_shader_name) == 0x9d0);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_09d9_alignment_padding) == 0x9d9);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_09dc_shader_type_information) == 0x9dc);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_09ec_shader_default_registers) == 0x9ec);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_09fc_shader_name) == 0x9fc);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_0a09_alignment_padding) == 0xa09);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_0a0c_shader_type_information) == 0xa0c);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_0a1c_shader_default_registers) == 0xa1c);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_0a8c_shader_name) == 0xa8c);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_0a96_alignment_padding) == 0xa96);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_0a98_shader_default_registers) == 0xa98);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_0aa8_shader_name) == 0xaa8);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_0aaf_shader_name) == 0xaaf);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_0ae1_alignment_padding) == 0xae1);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_0ae4_shader_comment_token) == 0xae4);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_0ae8_shader_comment_fourcc) == 0xae8);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_0aec_preshader_version) == 0xaec);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_0af0_shader_comment_token) == 0xaf0);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_0af4_shader_comment_fourcc) == 0xaf4);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_0af8_constant_table_header) == 0xaf8);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_0b14_constant_table_entry) == 0xb14);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_0b28_constant_table_entry) == 0xb28);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_0b3c_shader_name) == 0xb3c);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_0b49_alignment_padding) == 0xb49);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_0b4c_shader_type_information) == 0xb4c);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_0b5c_shader_default_registers) == 0xb5c);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_0bcc_shader_name) == 0xbcc);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_0bd6_alignment_padding) == 0xbd6);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_0bd8_shader_type_information) == 0xbd8);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_0be8_shader_default_registers) == 0xbe8);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_0bf8_shader_name) == 0xbf8);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_0bfb_shader_name) == 0xbfb);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_0c2d_alignment_padding) == 0xc2d);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_0c30_shader_comment_token) == 0xc30);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_0c34_shader_comment_fourcc) == 0xc34);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_0c38_preshader_register_segments) ==
              0xc38);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_0c64_shader_comment_token) == 0xc64);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_0c68_shader_comment_fourcc) == 0xc68);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_0c6c_preshader_literal_count) == 0xc6c);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_0c70_shader_comment_token) == 0xc70);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_0c74_shader_comment_fourcc) == 0xc74);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_0c78_preshader_instruction_count) ==
              0xc78);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_0c7c_preshader_instruction) == 0xc7c);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_0ca8_preshader_instruction) == 0xca8);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_0cd4_preshader_instruction) == 0xcd4);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_0d00_preshader_instruction) == 0xd00);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_0d2c_preshader_instruction) == 0xd2c);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_0d58_preshader_instruction) == 0xd58);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_0d84_preshader_instruction) == 0xd84);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_0db0_preshader_instruction) == 0xdb0);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_0ddc_preshader_instruction) == 0xddc);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_0e08_preshader_instruction) == 0xe08);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_0e34_preshader_instruction) == 0xe34);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_0e60_preshader_instruction) == 0xe60);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_0e8c_preshader_instruction) == 0xe8c);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_0eb8_preshader_instruction) == 0xeb8);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_0ee4_preshader_code_footer) == 0xee4);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_0eec_shader_end_token) == 0xeec);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_0ef0_pixel_shader_instruction) == 0xef0);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_0efc_pixel_shader_instruction) == 0xefc);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_0f08_pixel_shader_instruction) == 0xf08);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_0f18_pixel_shader_instruction) == 0xf18);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_0f28_pixel_shader_instruction) == 0xf28);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_0f38_pixel_shader_instruction) == 0xf38);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_0f48_pixel_shader_instruction) == 0xf48);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_0f58_pixel_shader_instruction) == 0xf58);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_0f68_pixel_shader_instruction) == 0xf68);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_0f78_pixel_shader_instruction) == 0xf78);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_0f88_pixel_shader_instruction) == 0xf88);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_0f98_pixel_shader_instruction) == 0xf98);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_0fa8_pixel_shader_instruction) == 0xfa8);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_0fb8_pixel_shader_instruction) == 0xfb8);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_0fc8_pixel_shader_instruction) == 0xfc8);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_0fd8_pixel_shader_instruction) == 0xfd8);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_0fe8_pixel_shader_instruction) == 0xfe8);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_0ff8_pixel_shader_instruction) == 0xff8);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_1008_pixel_shader_instruction) ==
              0x1008);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_1018_pixel_shader_instruction) ==
              0x1018);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_1028_pixel_shader_instruction) ==
              0x1028);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_1038_pixel_shader_instruction) ==
              0x1038);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_1048_pixel_shader_instruction) ==
              0x1048);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_1058_pixel_shader_instruction) ==
              0x1058);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_1068_pixel_shader_instruction) ==
              0x1068);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_1078_pixel_shader_instruction) ==
              0x1078);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_1088_pixel_shader_instruction) ==
              0x1088);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_1098_pixel_shader_instruction) ==
              0x1098);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_10a8_pixel_shader_instruction) ==
              0x10a8);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_10b8_pixel_shader_instruction) ==
              0x10b8);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_10c8_pixel_shader_instruction) ==
              0x10c8);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_10d8_pixel_shader_instruction) ==
              0x10d8);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_10e8_pixel_shader_instruction) ==
              0x10e8);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_10f8_pixel_shader_instruction) ==
              0x10f8);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_1108_pixel_shader_instruction) ==
              0x1108);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_1118_pixel_shader_instruction) ==
              0x1118);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_1128_pixel_shader_instruction) ==
              0x1128);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_1138_pixel_shader_instruction) ==
              0x1138);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_1148_pixel_shader_instruction) ==
              0x1148);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_115c_pixel_shader_instruction) ==
              0x115c);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_1170_pixel_shader_instruction) ==
              0x1170);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_1184_pixel_shader_instruction) ==
              0x1184);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_1198_pixel_shader_instruction) ==
              0x1198);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_11ac_pixel_shader_instruction) ==
              0x11ac);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_11c0_pixel_shader_instruction) ==
              0x11c0);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_11cc_pixel_shader_instruction) ==
              0x11cc);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_11d8_shader_end_token) == 0x11d8);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_11dc_resource_header) == 0x11dc);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_11f4_pixel_shader_version) == 0x11f4);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_11f8_shader_comment_token) == 0x11f8);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_11fc_shader_comment_fourcc) == 0x11fc);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_1200_constant_table_header) == 0x1200);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_121c_constant_table_entry) == 0x121c);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_1230_constant_table_entry) == 0x1230);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_1244_constant_table_entry) == 0x1244);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_1258_constant_table_entry) == 0x1258);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_126c_shader_name) == 0x126c);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_1275_alignment_padding) == 0x1275);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_1278_shader_type_information) == 0x1278);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_1288_shader_name) == 0x1288);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_1291_alignment_padding) == 0x1291);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_1294_shader_type_information) == 0x1294);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_12a4_shader_default_registers) ==
              0x12a4);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_12b4_shader_name) == 0x12b4);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_12c1_alignment_padding) == 0x12c1);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_12c4_shader_type_information) == 0x12c4);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_12d4_shader_default_registers) ==
              0x12d4);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_1344_shader_name) == 0x1344);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_134e_alignment_padding) == 0x134e);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_1350_shader_default_registers) ==
              0x1350);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_1360_shader_name) == 0x1360);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_1367_shader_name) == 0x1367);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_1399_alignment_padding) == 0x1399);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_139c_shader_comment_token) == 0x139c);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_13a0_shader_comment_fourcc) == 0x13a0);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_13a4_preshader_version) == 0x13a4);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_13a8_shader_comment_token) == 0x13a8);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_13ac_shader_comment_fourcc) == 0x13ac);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_13b0_constant_table_header) == 0x13b0);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_13cc_constant_table_entry) == 0x13cc);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_13e0_constant_table_entry) == 0x13e0);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_13f4_shader_name) == 0x13f4);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_1401_alignment_padding) == 0x1401);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_1404_shader_type_information) == 0x1404);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_1414_shader_default_registers) ==
              0x1414);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_1484_shader_name) == 0x1484);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_148e_alignment_padding) == 0x148e);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_1490_shader_type_information) == 0x1490);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_14a0_shader_default_registers) ==
              0x14a0);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_14b0_shader_name) == 0x14b0);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_14b3_shader_name) == 0x14b3);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_14e5_alignment_padding) == 0x14e5);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_14e8_shader_comment_token) == 0x14e8);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_14ec_shader_comment_fourcc) == 0x14ec);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_14f0_preshader_register_segments) ==
              0x14f0);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_151c_shader_comment_token) == 0x151c);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_1520_shader_comment_fourcc) == 0x1520);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_1524_preshader_literal_count) == 0x1524);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_1528_shader_comment_token) == 0x1528);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_152c_shader_comment_fourcc) == 0x152c);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_1530_preshader_instruction_count) ==
              0x1530);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_1534_preshader_instruction) == 0x1534);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_1560_preshader_instruction) == 0x1560);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_158c_preshader_instruction) == 0x158c);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_15b8_preshader_instruction) == 0x15b8);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_15e4_preshader_instruction) == 0x15e4);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_1610_preshader_instruction) == 0x1610);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_163c_preshader_instruction) == 0x163c);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_1668_preshader_instruction) == 0x1668);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_1694_preshader_instruction) == 0x1694);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_16c0_preshader_instruction) == 0x16c0);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_16ec_preshader_instruction) == 0x16ec);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_1718_preshader_instruction) == 0x1718);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_1744_preshader_instruction) == 0x1744);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_1770_preshader_instruction) == 0x1770);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_179c_preshader_code_footer) == 0x179c);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_17a4_shader_end_token) == 0x17a4);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_17a8_pixel_shader_instruction) ==
              0x17a8);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_17b4_pixel_shader_instruction) ==
              0x17b4);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_17c0_pixel_shader_instruction) ==
              0x17c0);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_17d0_pixel_shader_instruction) ==
              0x17d0);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_17e0_pixel_shader_instruction) ==
              0x17e0);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_17f0_pixel_shader_instruction) ==
              0x17f0);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_1800_pixel_shader_instruction) ==
              0x1800);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_1810_pixel_shader_instruction) ==
              0x1810);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_1820_pixel_shader_instruction) ==
              0x1820);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_1830_pixel_shader_instruction) ==
              0x1830);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_1840_pixel_shader_instruction) ==
              0x1840);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_1850_pixel_shader_instruction) ==
              0x1850);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_1860_pixel_shader_instruction) ==
              0x1860);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_1870_pixel_shader_instruction) ==
              0x1870);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_1880_pixel_shader_instruction) ==
              0x1880);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_1890_pixel_shader_instruction) ==
              0x1890);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_18a0_pixel_shader_instruction) ==
              0x18a0);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_18b0_pixel_shader_instruction) ==
              0x18b0);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_18c0_pixel_shader_instruction) ==
              0x18c0);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_18d0_pixel_shader_instruction) ==
              0x18d0);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_18e0_pixel_shader_instruction) ==
              0x18e0);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_18f0_pixel_shader_instruction) ==
              0x18f0);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_1900_pixel_shader_instruction) ==
              0x1900);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_1910_pixel_shader_instruction) ==
              0x1910);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_1920_pixel_shader_instruction) ==
              0x1920);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_1930_pixel_shader_instruction) ==
              0x1930);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_1940_pixel_shader_instruction) ==
              0x1940);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_1950_pixel_shader_instruction) ==
              0x1950);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_1960_pixel_shader_instruction) ==
              0x1960);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_1970_pixel_shader_instruction) ==
              0x1970);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_1980_pixel_shader_instruction) ==
              0x1980);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_1990_pixel_shader_instruction) ==
              0x1990);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_19a0_pixel_shader_instruction) ==
              0x19a0);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_19b0_pixel_shader_instruction) ==
              0x19b0);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_19c0_pixel_shader_instruction) ==
              0x19c0);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_19d0_pixel_shader_instruction) ==
              0x19d0);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_19e0_pixel_shader_instruction) ==
              0x19e0);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_19f0_pixel_shader_instruction) ==
              0x19f0);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_1a00_pixel_shader_instruction) ==
              0x1a00);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_1a14_pixel_shader_instruction) ==
              0x1a14);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_1a28_pixel_shader_instruction) ==
              0x1a28);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_1a3c_pixel_shader_instruction) ==
              0x1a3c);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_1a50_pixel_shader_instruction) ==
              0x1a50);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_1a64_pixel_shader_instruction) ==
              0x1a64);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_1a78_pixel_shader_instruction) ==
              0x1a78);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_1a84_pixel_shader_instruction) ==
              0x1a84);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_1a90_shader_end_token) == 0x1a90);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_1a94_resource_header) == 0x1a94);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_1aac_state_parameter_name) == 0x1aac);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_1abc_resource_header) == 0x1abc);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_1ad4_pixel_shader_version) == 0x1ad4);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_1ad8_shader_comment_token) == 0x1ad8);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_1adc_shader_comment_fourcc) == 0x1adc);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_1ae0_constant_table_header) == 0x1ae0);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_1afc_constant_table_entry) == 0x1afc);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_1b10_constant_table_entry) == 0x1b10);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_1b24_shader_name) == 0x1b24);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_1b2d_alignment_padding) == 0x1b2d);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_1b30_shader_type_information) == 0x1b30);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_1b40_shader_default_registers) ==
              0x1b40);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_1b50_shader_name) == 0x1b50);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_1b5e_alignment_padding) == 0x1b5e);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_1b60_shader_type_information) == 0x1b60);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_1b70_shader_name) == 0x1b70);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_1b77_shader_name) == 0x1b77);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_1ba9_alignment_padding) == 0x1ba9);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_1bac_shader_comment_token) == 0x1bac);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_1bb0_shader_comment_fourcc) == 0x1bb0);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_1bb4_preshader_version) == 0x1bb4);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_1bb8_shader_comment_token) == 0x1bb8);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_1bbc_shader_comment_fourcc) == 0x1bbc);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_1bc0_constant_table_header) == 0x1bc0);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_1bdc_constant_table_entry) == 0x1bdc);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_1bf0_constant_table_entry) == 0x1bf0);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_1c04_shader_name) == 0x1c04);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_1c0f_alignment_padding) == 0x1c0f);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_1c10_shader_type_information) == 0x1c10);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_1c20_shader_default_registers) ==
              0x1c20);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_1c30_shader_name) == 0x1c30);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_1c3a_shader_name) == 0x1c3a);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_1c3d_shader_name) == 0x1c3d);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_1c6f_alignment_padding) == 0x1c6f);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_1c70_shader_comment_token) == 0x1c70);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_1c74_shader_comment_fourcc) == 0x1c74);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_1c78_preshader_register_segments) ==
              0x1c78);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_1ca4_shader_comment_token) == 0x1ca4);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_1ca8_shader_comment_fourcc) == 0x1ca8);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_1cac_preshader_literal_count) == 0x1cac);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_1cb0_preshader_binary64_literals) ==
              0x1cb0);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_1d10_shader_comment_token) == 0x1d10);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_1d14_shader_comment_fourcc) == 0x1d14);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_1d18_preshader_instruction_count) ==
              0x1d18);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_1d1c_preshader_instruction) == 0x1d1c);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_1d3c_preshader_instruction) == 0x1d3c);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_1d68_preshader_instruction) == 0x1d68);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_1d94_preshader_instruction) == 0x1d94);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_1db4_preshader_instruction) == 0x1db4);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_1de0_preshader_instruction) == 0x1de0);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_1e0c_preshader_instruction) == 0x1e0c);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_1e2c_preshader_code_footer) == 0x1e2c);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_1e34_shader_end_token) == 0x1e34);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_1e38_pixel_shader_instruction) ==
              0x1e38);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_1e50_pixel_shader_instruction) ==
              0x1e50);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_1e5c_pixel_shader_instruction) ==
              0x1e5c);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_1e68_pixel_shader_instruction) ==
              0x1e68);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_1e74_pixel_shader_instruction) ==
              0x1e74);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_1e80_pixel_shader_instruction) ==
              0x1e80);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_1e90_pixel_shader_instruction) ==
              0x1e90);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_1ea0_pixel_shader_instruction) ==
              0x1ea0);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_1eac_pixel_shader_instruction) ==
              0x1eac);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_1eb8_pixel_shader_instruction) ==
              0x1eb8);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_1ec8_pixel_shader_instruction) ==
              0x1ec8);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_1ed8_pixel_shader_instruction) ==
              0x1ed8);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_1ee4_pixel_shader_instruction) ==
              0x1ee4);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_1ef0_pixel_shader_instruction) ==
              0x1ef0);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_1efc_pixel_shader_instruction) ==
              0x1efc);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_1f08_pixel_shader_instruction) ==
              0x1f08);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_1f18_pixel_shader_instruction) ==
              0x1f18);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_1f28_pixel_shader_instruction) ==
              0x1f28);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_1f34_pixel_shader_instruction) ==
              0x1f34);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_1f40_pixel_shader_instruction) ==
              0x1f40);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_1f4c_pixel_shader_instruction) ==
              0x1f4c);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_1f58_pixel_shader_instruction) ==
              0x1f58);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_1f68_pixel_shader_instruction) ==
              0x1f68);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_1f78_pixel_shader_instruction) ==
              0x1f78);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_1f84_pixel_shader_instruction) ==
              0x1f84);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_1f90_pixel_shader_instruction) ==
              0x1f90);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_1fa0_pixel_shader_instruction) ==
              0x1fa0);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_1fb0_pixel_shader_instruction) ==
              0x1fb0);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_1fc0_pixel_shader_instruction) ==
              0x1fc0);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_1fd0_pixel_shader_instruction) ==
              0x1fd0);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_1fe0_pixel_shader_instruction) ==
              0x1fe0);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_1ff0_pixel_shader_instruction) ==
              0x1ff0);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_2000_pixel_shader_instruction) ==
              0x2000);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_2010_pixel_shader_instruction) ==
              0x2010);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_2020_pixel_shader_instruction) ==
              0x2020);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_2030_pixel_shader_instruction) ==
              0x2030);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_2040_pixel_shader_instruction) ==
              0x2040);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_2050_pixel_shader_instruction) ==
              0x2050);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_2060_pixel_shader_instruction) ==
              0x2060);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_2070_pixel_shader_instruction) ==
              0x2070);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_2080_pixel_shader_instruction) ==
              0x2080);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_2090_pixel_shader_instruction) ==
              0x2090);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_209c_pixel_shader_instruction) ==
              0x209c);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_20a8_shader_end_token) == 0x20a8);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_20ac_resource_header) == 0x20ac);
static_assert(__builtin_offsetof(EmbeddedGlowEffect, field_20c4_state_parameter_name) == 0x20c4);
static_assert(sizeof(EmbeddedGlowEffect) == 0x20d4);
extern "C" const EmbeddedGlowEffect dat_006c9818;
