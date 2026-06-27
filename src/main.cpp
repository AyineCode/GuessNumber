#include <stdio.h>
#include "guessnumber/version.h"
#include "guessnumber/io_interface.hpp"
#include "guessnumber/console_io.hpp"
#include "guessnumber/Config.hpp"
#include "guessnumber/game.hpp"

int main(){
    Config config;
    ConsoleInput consoleInput;
    ConsoleOutput consoleOutput;

    Game game(consoleInput, consoleOutput, config);

    game.Start_Run();
    return 0;
}
