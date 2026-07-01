#pragma once

#include <string>
#include "guessnumber/core/model/Config.hpp"

class ConfigStorer{
private:
    std::string _filepath;
    Config _config;
    bool _isDirty = false;
public:
    explicit ConfigStorer(const std::string& dataDir);

    bool load();
    bool save();
    Config getConfig() const;
    bool setConfig(const Config& config);
};