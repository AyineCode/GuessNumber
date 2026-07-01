#include "guessnumber/core/configStorer.hpp"

#include "guessnumber/base/JsonSL.hpp"
#include "guessnumber/base/Logger.hpp"
#include "guessnumber/core/model/Config.hpp"

ConfigStorer::ConfigStorer(const std::string &dataDir) : _filepath(dataDir + "/config.json"){}

bool ConfigStorer::load(){
    nlohmann::json j;
    if(!jsonLoad(j, _filepath.c_str())){
        if(!save()){
            LOG_ERROR("Failed to create an empty configuration file");
            return false;
        }
        return true;
    }else{
        if(j.contains("config")){
            j.at("config").get_to(_config);
        }else{
            LOG_ERROR("Failed to load configuration from: " << _filepath);
            return false;
        }
        return true;
    }
}

bool ConfigStorer::save()
{
    if(!_isDirty)return true;

    nlohmann::json j;
    j["config"] = _config;

    bool flag = jsonSave(j, _filepath.c_str());
    if(flag){
        _isDirty = false;
        LOG_INFO("Configuration saved");
    }else{
        LOG_ERROR("Failed to save configuration");
    }
    return flag;
}

Config ConfigStorer::getConfig() const{
    return _config;
}

bool ConfigStorer::setConfig(const Config& config){
    _isDirty = true;
    _config = config;
    return save();
}
