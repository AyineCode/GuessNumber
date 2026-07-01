#include "guessnumber/core/console_io.hpp"
#include <optional>
#include "guessnumber/core/model/Config.hpp"
#include <cstring>

std::optional<int> ConsoleInput::getGuess(){
    char buf[30];
    char ans[20];
    printf("Guess a number: ");
    fgets(buf, 30, stdin);
    buf[29] = '\0';
    int i = 0;
    for(; i < 12; i++){
        char cur = buf[i];
        if((cur >= '0' && cur <= '9') || (i == 0 && cur == '-' && (buf[1] >= '0' && buf[1] <= '9'))){
            ans[i] = cur;
        }else if(i > 0 && (cur == '\0' || cur == '\n' || cur == '\t')){
            ans[i] = '\0';
            int guess = atoi(ans); // unsafe!
            return guess;
        }else{
            return std::nullopt;
        }
    }
    return std::nullopt;
}

bool ConsoleInput::askPlayAgain(){
    char buf[100];
    printf("Continue to play?(Y/n): ");
    fgets(buf, 100, stdin);
    buf[99] = '\0';
    if(buf[1] == '\n' || buf[1] == '\t')buf[1] = '\0';
    if(buf[3] == '\n' || buf[3] == '\t')buf[3] = '\0';
    if(strcmp(buf, "Y") == 0 || strcmp(buf, "y") == 0 || strcmp(buf, "Yes") == 0 || strcmp(buf, "yes") == 0){
        return true;
    }
    return false;
}

void ConsoleOutput::showWelcome(Config config){
    printf("Welcome to a simple game--GuessNumber!\n");
    printf("You are supposed to guess a number between %d and %d! You have %d chance(s) to guess.\n", config.minNum, config.maxNum, config.attempts);
}

void ConsoleOutput::showRecordBoard(const std::vector<GameRecord> &tops)
{
    if (!tops.empty()) {
        printf("🏆 Hall of Fame (least guesses):\n");
        for (size_t i = 0; i < tops.size(); ++i) {
            printf("  No.%ld   %d guess(es), range  %d ~ %d    %s\n", i + 1, tops[i].attempt, tops[i].config.minNum, tops[i].config.maxNum, tops[i].date.c_str());
        }
    }
}

void ConsoleOutput::showTooHigh(int delta)
{
    printf("You guessed too high!\n");
}

void ConsoleOutput::showTooLow(int delta)
{
    printf("You guessed too low!\n");
}

void ConsoleOutput::showSuccess(int attempt)
{
    printf("\033[0;32mYou win! It took only %d time(s) for you to get it!\033[0m\n", attempt);
}

void ConsoleOutput::showGameOver(int secret)
{
    printf("Uh-oh...you've used up all your tries.\nThe secret number is: %d\n", secret);
}

void ConsoleOutput::showError(const char msg[]){
    printf("\033[0;31m%s\033[0m\n", msg);
}