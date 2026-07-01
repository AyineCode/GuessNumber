#pragma once

#include <optional>
#include <string>

enum class CliOpt{
    NONE = 0,
    ERROR = 1,
    VERSION = 2,
    HELP = 3,
    CONFIG = 4
};

struct CommandLinePara{
    CliOpt opt = CliOpt::NONE;
    std::optional<int> minNum;
    std::optional<int> maxNum;
    std::optional<int> maxAttempts;
    std::string errorMsg;

    void setError(const std::string msg);
};

CommandLinePara parseCliArguments(const int argc, const char* argv[]);