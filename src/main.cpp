#include <stdio.h>
#include "guessnumber/version.h"
#include "guessnumber/io_interface.hpp"
#include "guessnumber/console_io.hpp"
#include "guessnumber/Config.hpp"
#include "guessnumber/game.hpp"
#include "guessnumber/Logger.hpp"

int main(){
    const char* home = std::getenv("HOME");
    std::string logDir = home ? std::string(home) + "/.guessNumber" : "./.guessNumber";
    std::system(("mkdir -p " + logDir).c_str());
    Logger::Instance().setMinLevel(LogLevel::INFO);
    Logger::Instance().setShowFile(false);
    Logger::Instance().enableFile((logDir + "/game.log").c_str());

    Config config;
    ConsoleInput consoleInput;
    ConsoleOutput consoleOutput;

    Game game(consoleInput, consoleOutput, config);

    LOG_INFO("===Game start===");
    game.Start_Run();
    LOG_INFO("===Game exited normally===")
    return 0;
}
