#include "guessnumber/game.hpp"
#include <random>

Game::Game(Input& input, Output& output, Config config):_input(input), _output(output), _config(config){}

void Game::Start_Run(){
    _output.showWelcome(_config);
    do{
        if(!playOnce())break;
    }while(_input.askPlayAgain());
}

bool Game::playOnce(){
    int secret = genSecrect();
    int temp = 0;
    int invalidTemp = 0;
    while(temp < _config.attempts){
        auto guess = _input.getGuess();
        if(!guess.has_value()){
            invalidTemp++;
            if(invalidTemp >= 8){
                _output.showError("Too many invalid guess! Kick you out.");
                return false;
            }
            _output.showError("Invalid guess, please try again.");
            continue;
        }

        int ans = guess.value();

        if(ans > _config.maxNum || ans < _config.minNum){
            invalidTemp++;
            if(invalidTemp >= 8){
                _output.showError("Too many invalid guess! Kick you out.");
                return false;
            }
            char msg[100]; //unsafe! need to be repalce.
            sprintf(msg, "Out of range. please guess between %d and %d.", _config.minNum, _config.maxNum);
            _output.showError(msg);
            continue;
        }

        temp++;
        invalidTemp = 0;

        if(ans > secret){
            _output.showTooHigh(ans - secret);
        }else if(ans < secret){
            _output.showTooLow(secret - ans);
        }else{
            _output.showSuccess(temp);
            return true;
        }
    }
    _output.showGameOver(secret);
    return true;
}

int Game::genSecrect() const{
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(_config.minNum, _config.maxNum);
    return dist(gen);
}