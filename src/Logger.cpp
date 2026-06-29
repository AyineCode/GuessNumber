#include "guessnumber/Logger.hpp"

#include <iostream>
#include <fstream>
#include <sstream>
#include <chrono>
#include <cstring>
#include <iomanip>

Logger::Logger() : _minLevel(LogLevel::INFO), _showFile(true){}

Logger& Logger::Instance(){
    static Logger logger;
    return logger;
}

Logger::~Logger(){
    _logFile.close();
}

int Logger::setMinLevel(LogLevel lvl)
{
    _minLevel = lvl;
    return 0;
}

int Logger::setShowFile(bool isShow){
    _showFile = isShow;
    return 0;
}

LogLevel Logger::minLevel() const
{
    return _minLevel;
}

int Logger::enableFile(const char filepath[])
{
    try{
        _logFile.open(filepath, std::ios::app);
        return 0;
    }catch(std::exception& e){
        LOG_FATAL("Cannot open log file: " << filepath << ". Original message: " << e.what());
        return 1;
    }
}

int Logger::log(const char file[], const int line, const LogLevel lvl, const char msg[])
{
    if(lvl < _minLevel)return 1;

    auto now = std::chrono::system_clock::now();
    auto time_t_now = std::chrono::system_clock::to_time_t(now);
    auto output_time = std::localtime(&time_t_now);
    std::ostringstream oss;
    oss << std::put_time(output_time, "%Y-%m-%d %H:%M:%S");

    std::string fileShowing = _showFile ? std::string("[") + file + ":line " + std::to_string(line) + "] " : "";
    std::string fullLine = "[" + oss.str() + "] [" + getLogLevel(lvl) + "] " + fileShowing + msg + "\n";

    std::cerr << fullLine;

    if(_logFile.is_open()){
        _logFile << fullLine;
        _logFile.flush();
    }

    if(lvl == LogLevel::FATAL){
        std::exit(EXIT_FAILURE);
    }

    return 0;
}
