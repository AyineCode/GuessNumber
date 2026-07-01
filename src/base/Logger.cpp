#include "guessnumber/base/Logger.hpp"

#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>

#include "guessnumber/base/FormatTime.hpp"

Logger::Logger() : _min_fileLevel(LogLevel::INFO), _min_errLevel(LogLevel::ERROR), _showFile(true){
    if(_min_fileLevel <= _min_errLevel){
        _minLevel = _min_fileLevel;
    }else{
        _minLevel = _min_errLevel;
    }
}

Logger& Logger::Instance(){
    static Logger logger;
    return logger;
}

Logger::~Logger(){
    _logFile.close();
}

int Logger::setMinLevel(LogLevel flvl, LogLevel elvl)
{
    _min_fileLevel = flvl;
    _min_errLevel = elvl;

    if(_min_fileLevel <= _min_errLevel){
        _minLevel = _min_fileLevel;
    }else{
        _minLevel = _min_errLevel;
    }

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

    std::ostringstream oss;
    oss << getFormatTime();

    std::string fileShowing = _showFile ? std::string("[") + file + ":line " + std::to_string(line) + "] " : "";
    std::string fullLine = "[" + oss.str() + "] [" + getLogLevel(lvl) + "] " + fileShowing + msg + "\n";

    if(lvl >= _min_errLevel)std::cerr << fullLine;

    if(lvl >= _min_fileLevel && _logFile.is_open()){
        _logFile << fullLine;
        _logFile.flush();
    }

    if(lvl == LogLevel::FATAL){
        std::exit(EXIT_FAILURE);
    }

    return 0;
}
