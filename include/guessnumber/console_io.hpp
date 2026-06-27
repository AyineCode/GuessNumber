#pragma once

#include "io_interface.hpp"
#include "Config.hpp"

class ConsoleInput : public Input{
public:
    std::optional<int> getGuess() override;
    bool askPlayAgain() override;
};

class ConsoleOutput : public Output{
public:
    void showWelcome(Config config) override;
    void showTooHigh(int delta) override;
    void showTooLow(int delta) override;
    void showSuccess(int attempt) override;
    void showGameOver(int secret) override;
    void showError(const char msg[]) override;
};