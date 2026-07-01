#pragma once

#include "nlohmann/json.hpp"
#include <optional>

struct Config{
    int minNum = 1;
    int maxNum = 100;
    int attempts = 7;

    Config();
    void setopt(const std::optional<int>& minOpt, const std::optional<int>& maxOpt, const std::optional<int>& tempOpt);

    void applyEnvOverrides();
};

void to_json(nlohmann::json& j, const Config& c);

void from_json(const nlohmann::json& j, Config& c);