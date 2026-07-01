#pragma once

#include <iostream>
#include <fstream>
#include <sstream>

enum class LogLevel{
    TRACE = 0,
    DEBUG = 1,
    INFO = 2,
    WARN = 3,
    ERROR = 4,
    FATAL = 5,
    OFF = 6
};

inline const char* getLogLevel(LogLevel lvl){
    switch (lvl)
    {
    case LogLevel::TRACE:
        return "TRACE";
    case LogLevel::DEBUG:
        return "Debug";
    case LogLevel::INFO:
        return "INFO";
    case LogLevel::WARN:
        return "WARN";
    case LogLevel::ERROR:
        return "ERROR";
    case LogLevel::FATAL:
        return "FATAL";
    case LogLevel::OFF:
        return "OFF";
    default:
        return "UNKNOWN";
    }
}

class Logger{
protected:
    LogLevel _min_fileLevel;
    LogLevel _min_errLevel;
    LogLevel _minLevel;
    bool _showFile;
    std::ofstream _logFile;
    Logger();
public:
    static Logger& Instance();
    virtual ~Logger();
    virtual int setMinLevel(LogLevel flvl, LogLevel elvl);
    virtual int setShowFile(bool isShow);
    virtual LogLevel minLevel() const;
    virtual int enableFile(const char filepath[]);
    virtual int log(const char file[], const int line, const LogLevel lvl, const char msg[]);
};

class LogStream{
private:
    const char* _file;
    const int _line;
    const LogLevel _level;
    std::ostringstream _oss;
public:
    LogStream(const char file[], const int line, const LogLevel lvl):
        _file(file), _line(line), _level(lvl){}
    ~LogStream(){
        Logger::Instance().log(_file, _line, _level, _oss.str().c_str());
    }
    std::ostringstream& stream(){return _oss;}
};

#define LOG_TRACE(expr) \
    if(Logger::Instance().minLevel() > LogLevel::TRACE){}\
    else{LogStream(__FILE__, __LINE__, LogLevel::TRACE).stream() << expr;}

#define LOG_DEBUG(expr) \
    if(Logger::Instance().minLevel() > LogLevel::DEBUG){}\
    else{LogStream(__FILE__, __LINE__, LogLevel::DEBUG).stream() << expr;}

#define LOG_INFO(expr) \
    if(Logger::Instance().minLevel() > LogLevel::INFO){}\
    else{LogStream(__FILE__, __LINE__, LogLevel::INFO).stream() << expr;}

#define LOG_WARN(expr) \
    if(Logger::Instance().minLevel() > LogLevel::WARN){}\
    else{LogStream(__FILE__, __LINE__, LogLevel::WARN).stream() << expr;}

#define LOG_ERROR(expr) \
    if(Logger::Instance().minLevel() > LogLevel::ERROR){}\
    else{LogStream(__FILE__, __LINE__, LogLevel::ERROR).stream() << expr;}

#define LOG_FATAL(expr) \
    if(Logger::Instance().minLevel() > LogLevel::FATAL){}\
    else{LogStream(__FILE__, __LINE__, LogLevel::FATAL).stream() << expr;}
