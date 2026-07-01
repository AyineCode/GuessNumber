#pragma once

#include "guessnumber/version.h"
#include <stdio.h>
#include <iostream>
#include "guessnumber/core/model/Config.hpp"

void printVersion(){
    printf("GuessNumber version %d.%d.%d\n", GUESSNUMBER_VERSION_MAJOR, GUESSNUMBER_VERSION_MINOR, GUESSNUMBER_VERSION_PATCH);
}

void printHelp(const char* prog) {
    std::cout << "Usage: " << prog << " [OPTIONS]\n\n"
              << "Play a number guessing game.\n"
              << "Give a range, guess a number. Win if you get it!\n\n"
              << "Options:\n"
              << "    -h, --help\n"
              << "        Show this help message\n"
              << "    -v, --version\n"
              << "        Show version information\n"
              << "    -c, --config <minNum> <maxNum> <maxAttempts>\n"
              << "        Set game configuration\n"
              << "\nEnvironment variables:\n"
              << "    GUESSNUMBER_MIN, GUESSNUMBER_MAX, GUESSNUMBER_MAX_ATTEMPTS\n"
              << "    These override config file settings.\n";
}

void printConfig(const Config& config){
    std::cout << "Game Configuration:\n"
              << "  Number Range:     [" << config.minNum << "," << config.maxNum << "]\n"
              << "  Maxinum Attempts:  " << config.attempts << "\n";
}
