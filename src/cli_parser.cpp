#include "guessnumber/cli_parser.hpp"

#include <string>
#include <optional>

static std::optional<int> arg_to_int(const char buf[]){
    char ans[20];
    int i = 0;
    for(; i < 12; i++){
        char cur = buf[i];
        if((cur >= '0' && cur <= '9') || (i == 0 && cur == '-' && (buf[1] >= '0' && buf[1] <= '9'))){
            ans[i] = cur;
        }else if(i > 0 && (cur == '\0' || cur == '\n' || cur == '\t')){
            ans[i] = '\0';
            int res = atoi(ans); // unsafe!
            return res;
        }else{
            return std::nullopt;
        }
    }
    return std::nullopt;
}

CommandLinePara parseCliArguments(const int argc, const char *argv[])
{
    CommandLinePara cliPara;
    if(argc < 2)return cliPara;
    std::string opt = std::string(argv[1]);
    if(opt == "-v" || opt == "--version"){
        cliPara.opt = CliOpt::VERSION;
    }else if(opt == "-h" || opt == "--help"){
        cliPara.opt = CliOpt::HELP;
    }else if(opt == "-c" || opt == "--config"){
        cliPara.opt = CliOpt::CONFIG;
        if(argc == 5){
            auto minOpt = arg_to_int(argv[2]);
            auto maxOpt = arg_to_int(argv[3]);
            auto tempOpt = arg_to_int(argv[4]);
            if(minOpt.has_value() && maxOpt.has_value() && tempOpt.has_value()){
                if(minOpt.value() >= maxOpt.value()){
                    cliPara.setError("Invalid config: minNum must be lower than maxNum");
                }else if(tempOpt.value() <= 0){
                    cliPara.setError("Invalid config: maxAttempts must be positive");
                }else{
                    cliPara.minNum = minOpt;
                    cliPara.maxNum = maxOpt;
                    cliPara.maxAttempts = tempOpt;
                }
            }else{
                cliPara.setError("Invalid config parameters");
            }
        }else if(argc == 2){
            cliPara.minNum = std::nullopt;
            cliPara.maxNum = std::nullopt;
            cliPara.maxAttempts = std::nullopt;
        }else{
            cliPara.setError("Invalid config parameter count");
        }
    }else{
        cliPara.setError("Unknown command: " + opt);
    }
    return cliPara;
}

void CommandLinePara::setError(const std::string msg)
{
    errorMsg = msg;
    opt = CliOpt::ERROR;
}