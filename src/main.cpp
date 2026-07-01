#include <stdio.h>
#include "guessnumber/version.h"
#include "guessnumber/cli_parser.hpp"
#include "guessnumber/cli_options.hpp"
#include "guessnumber/core/configStorer.hpp"
#include "guessnumber/core/io_interface.hpp"
#include "guessnumber/core/console_io.hpp"
#include "guessnumber/core/model/Config.hpp"
#include "guessnumber/core/game.hpp"
#include "guessnumber/core/history.hpp"
#include "guessnumber/base/Logger.hpp"

int main(const int argc, const char* argv[]){
    const char* home = std::getenv("HOME");

    std::string logDir = home ? std::string(home) + "/.guessNumber" : "./.guessNumber";
    std::system(("mkdir -p " + logDir).c_str());
    Logger::Instance().setMinLevel(LogLevel::INFO, LogLevel::ERROR);
    Logger::Instance().setShowFile(false);
    Logger::Instance().enableFile((logDir + "/game.log").c_str());

    std::string configDir = logDir;
    std::system(("mkdir -p " + configDir).c_str());
    ConfigStorer configStorer(configDir);
    configStorer.load();
    Config config = configStorer.getConfig();

    CommandLinePara cli = parseCliArguments(argc, argv);

    switch (cli.opt)
    {
    case CliOpt::ERROR:
        LOG_ERROR("Command line parsing error: " << cli.errorMsg);
        printf("\033[0;31m%s\033[0m\n", cli.errorMsg.c_str());
        printHelp(argv[0]);
        return 1;
    case CliOpt::VERSION:
        printVersion();
        return 0;
    case CliOpt::HELP:
        printHelp(argv[0]);
        return 0;
    case CliOpt::CONFIG:
        if(cli.maxAttempts.has_value() || cli.minNum.has_value() || cli.maxNum.has_value()){
            config.setopt(cli.minNum, cli.maxNum, cli.maxAttempts);
            configStorer.setConfig(config);
            configStorer.save();
            printf("\033[0;32mConfiguration adjusted successfully.\033[0m\n");
        }
        printConfig(config);
        return 0;
    case CliOpt::NONE:
        break;
    default:
        LOG_FATAL("Unknown command line option");
        return 1;
    }

    config.applyEnvOverrides();

    ConsoleInput consoleInput;
    ConsoleOutput consoleOutput;
    
    std::string dataDir = logDir;
    std::system(("mkdir -p " + dataDir).c_str());
    History history(dataDir);

    Game game(consoleInput, consoleOutput, history, config);

    LOG_INFO("===Game start===");
    game.Start_Run();
    LOG_INFO("===Game exited normally===")
    return 0;
}
