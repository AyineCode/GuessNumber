#pragma once

#include "Config.hpp"
#include "io_interface.hpp"

class Game{
private:
    Input& _input;
    Output& _output;
    Config _config;

    bool playOnce();
    int genSecrect() const;
    
public:
    Game(Input& input, Output& output, Config config = {});
    void Start_Run();
};