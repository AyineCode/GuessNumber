#include "guessnumber/core/model/Config.hpp"

void to_json(nlohmann::json& j, const Config& c){
    j["minNum"] = c.minNum;
    j["maxNum"] = c.maxNum;
    j["maxAttempts"] = c.attempts;
}

void from_json(const nlohmann::json& j, Config& c){
    j.at("minNum").get_to(c.minNum);
    j.at("maxNum").get_to(c.maxNum);
    j.at("maxAttempts").get_to(c.attempts);
}

Config::Config() : minNum(1), maxNum(100), attempts(7){}

void Config::setopt(const std::optional<int> &minOpt, const std::optional<int> &maxOpt, const std::optional<int> &tempOpt){
    if(minOpt.has_value())minNum = minOpt.value();
    if(maxOpt.has_value())maxNum = maxOpt.value();
    if(tempOpt.has_value())attempts = tempOpt.value();
}

void Config::applyEnvOverrides() {
    const char* env;
    if ((env = std::getenv("GUESSNUMBER_MIN"))) {
        try { minNum = std::stoi(env); } catch (...) {}
    }
    if ((env = std::getenv("GUESSNUMBER_MAX"))) {
        try { maxNum = std::stoi(env); } catch (...) {}
    }
    if ((env = std::getenv("GUESSNUMBER_MAX_ATTEMPTS"))) {
        try { attempts = std::stoi(env); } catch (...) {}
    }
}