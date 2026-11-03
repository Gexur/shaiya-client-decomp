#include "config_string_lookup.h"
#include "core/string_internal.h"
namespace {
/**
 * @brief Initialize the recovered inline representation of an empty configuration string.
 * @param string Recovered string whose existing stored bytes are modified in place.
 */
void initialize_empty_config_string(ConfigString* string) {
    string->capacity_018 = 15;
    string->size_014 = 0;
    string->storage_004[0] = 0;
}
struct StringCleanup {
    ConfigString* string;
    bool active = true;
    /**
     * @brief Destroy an active temporary configuration string on scope exit or unwinding.
     */
    ~StringCleanup() noexcept(false) {
        if (active)
            FUN_00529db0(string);
    }
};
struct ProxyCleanup {
    ConfigStringProxy* proxy;
    bool is_section_proxy;
    bool active = true;
    /**
     * @brief Restore an active section or value proxy to its recovered deleting table.
     */
    ~ProxyCleanup() noexcept(false) {
        if (active) {
            if (is_section_proxy)
                destroy_config_section_proxy(proxy, 0);
            else
                destroy_config_value_proxy(proxy, 0);
        }
    }
};
/**
 * @brief Access the section-tree storage at the recovered configuration-object offset.
 * @param object Recovered owning object whose evidenced layout is required.
 * @return The section tree located four bytes after the object address.
 */
OriginalNestedTree56* config_section_tree(void* object) {
    return reinterpret_cast<OriginalNestedTree56*>(static_cast<uint8_t*>(object) + 4);
}
} // namespace
/**
 * @brief Fold a section name to lowercase and obtain a proxy to its value tree.
 *
 * Inserts an empty section when the name is absent. Recovered Ep5.4 entry: 0x005bb790.
 * @param self Destination or owning object required by the recovered thiscall interface.
 * @param output Caller-provided storage for the function result.
 * @param section Configuration section name, folded to lowercase by proxy lookups.
 * @return The output section proxy.
 */
extern "C" ConfigStringProxy* __attribute__((thiscall))
get_config_section_proxy(void* self, ConfigStringProxy* output, const ConfigString* section) {
    ConfigString key;
    initialize_empty_config_string(&key);
    FUN_00405620(&key, section, 0, 0xffffffffu);
    StringCleanup cleanup{&key};
    lowercase_config_key(&key);
    output->value = get_or_insert_config_section(config_section_tree(self), &key);
    output->table = dat_006cf8e8;
    return output;
}
/**
 * @brief Fold a key to lowercase and obtain a proxy to its mapped string.
 *
 * Inserts an empty string when the key is absent. Recovered Ep5.4 entry: 0x005bafe0.
 * @param self Destination or owning object required by the recovered thiscall interface.
 * @param output Caller-provided storage for the function result.
 * @param key Configuration key whose stored bytes and length are used.
 * @return The output value proxy.
 */
extern "C" ConfigStringProxy* __attribute__((thiscall))
get_config_value_proxy(ConfigStringProxy* self, ConfigStringProxy* output,
                       const ConfigString* key) {
    ConfigString folded_key;
    initialize_empty_config_string(&folded_key);
    FUN_00405620(&folded_key, key, 0, 0xffffffffu);
    StringCleanup cleanup{&folded_key};
    lowercase_config_key(&folded_key);
    output->value =
        get_or_insert_config_value(static_cast<OriginalNestedTree72*>(self->value), &folded_key);
    output->table = dat_006cf8e4;
    return output;
}
/**
 * @brief Check whether a lowercased section and key already exist without insertion.
 *
 * Recovered Ep5.4 entry: 0x005bfe40.
 * @param self Destination or owning object required by the recovered thiscall interface.
 * @param section Configuration section name, folded to lowercase by proxy lookups.
 * @param key Configuration key whose stored bytes and length are used.
 * @return One when both lookups succeed; otherwise zero.
 */
extern "C" uint8_t __attribute__((thiscall))
contains_config_value(void* self, const ConfigString* section, const ConfigString* key) {
    ConfigString section_key;
    initialize_empty_config_string(&section_key);
    FUN_00405620(&section_key, section, 0, 0xffffffffu);
    StringCleanup first_cleanup{&section_key};
    lowercase_config_key(&section_key);
    OriginalNestedNode56* found;
    find_config_section(config_section_tree(self), &found, &section_key);
    if (found == config_section_tree(self)->header)
        return 0;
    ConfigString value_key;
    initialize_empty_config_string(&value_key);
    FUN_00405620(&value_key, key, 0, 0xffffffffu);
    StringCleanup second_cleanup{&value_key};
    lowercase_config_key(&value_key);
    OriginalNestedNode72* value;
    find_config_value(&found->payload.values, &value, &value_key);
    return value != found->payload.values.header;
}
/**
 * @brief Copy a configuration value, inserting the fallback when its section/key is absent.
 *
 * Missing entries are created in the configuration tree as part of this read. Recovered Ep5.4 entry: 0x005c0630.
 * @param self Destination or owning object required by the recovered thiscall interface.
 * @param output Caller-provided storage for the function result.
 * @param section Configuration section name, folded to lowercase by proxy lookups.
 * @param key Configuration key whose stored bytes and length are used.
 * @param fallback Default string copied into missing entries and into the output.
 * @return The newly initialized output string.
 */
extern "C" ConfigString* __attribute__((thiscall))
get_config_string_or_insert_default(void* self, ConfigString* output, const ConfigString* section,
                                    const ConfigString* key, const ConfigString* fallback) {
    if (contains_config_value(self, section, key) == 0) {
        ConfigStringProxy section_proxy;
        get_config_section_proxy(self, &section_proxy, section);
        ProxyCleanup first{&section_proxy, true};
        ConfigStringProxy value_proxy;
        get_config_value_proxy(&section_proxy, &value_proxy, key);
        ProxyCleanup second{&value_proxy, false};
        auto* value = static_cast<ConfigString*>(value_proxy.value);
        FUN_00405460(value, 0, 0xffffffffu);
        FUN_00405620(value, fallback, 0, 0xffffffffu);
        initialize_empty_config_string(output);
        first.active = false;
        second.active = false;
        FUN_00405620(output, fallback, 0, 0xffffffffu);
    } else {
        ConfigStringProxy section_proxy;
        get_config_section_proxy(self, &section_proxy, section);
        ProxyCleanup first{&section_proxy, true};
        ConfigStringProxy value_proxy;
        get_config_value_proxy(&section_proxy, &value_proxy, key);
        ProxyCleanup second{&value_proxy, false};
        ConfigString value;
        copy_config_proxy_string(&value_proxy, &value);
        StringCleanup cleanup{&value};
        initialize_empty_config_string(output);
        FUN_00405620(output, &value, 0, 0xffffffffu);
        first.active = false;
        second.active = false;
    }
    return output;
}
