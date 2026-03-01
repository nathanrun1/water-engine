#include "config.h"

#include <filesystem>
#include <unordered_map>

#include "SimpleIni.h"

namespace Config {
    const std::unordered_map<ConfigGroup, std::filesystem::path> CONFIG_FILE_PATHS = {
        {ConfigGroup::Shaders, "config/shaders.ini"}
    };

    const std::unordered_map<ConfigGroup, std::string> CONFIG_GROUP_NAMES = {
        {ConfigGroup::Shaders, "Shaders"}
    };

    std::string get_value(ConfigGroup group, const std::string& section, const std::string& key, const std::string& def) {
        CSimpleIniA ini;
        ini.SetUnicode();

        SI_Error rc = ini.LoadFile(CONFIG_FILE_PATHS.at(group).c_str());
        if (rc < 0) {
            throw config_error("Failed to load config group: " + CONFIG_GROUP_NAMES.at(group));
        }

        const std::string value = ini.GetValue(section.c_str(), key.c_str(), def.c_str());
        if (def == "" && value == "") {
            // Default not set and no value found
            throw config_error("Config value not found! Group: " + CONFIG_GROUP_NAMES.at(group) + ", Section: [" +
                section + "], Key: '" + key + "'");
        }
        return value;
    }

}
