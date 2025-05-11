// Implicit headerfiles
/*#include<fstream>
#include<ctime>
#include<string>
#ifndef LOGGER_H
#define LOGGER_H

#include<sstream>
#include<iostream>
*/
#define LOG_FILE_START "log_"

/*
// Different log level identifiers
enum class LogLevel{
  DEBUG,
  INFO,
  WARNING,
  ERROR
};


class Logger {

  public:

  Logger(LogLevel level = LogLevel::INFO, const std::string& filename = "")
  : minLevel(level)
  {
    if(!filename.empty()) {
      fileStream.open(filename, std::ios::app);
    }
  
  }

  ~ Logger() {
    if(!fileStream.is_open()) fileStream.close();  
  }
  
  void log(LogLevel level, const std::string& msg){
    if(level < minLevel) return;
    
    std::string output = format(level, msg);
    std::cout << output;
  
    if(fileStream.is_open()) {
      fileStream << output;
    }
  }
    
  void info(const std::string &msg) {log(LogLevel::INFO,msg); }  
  void debug(const std::string &msg) {log(LogLevel::DEBUG,msg); }  
  void warning(const std::string &msg) {log(LogLevel::WARNING,msg); }  
  void error(const std::string &msg) {log(LogLevel::ERROR,msg); }  

  private:

  LogLevel minLevel;
  
  std::ofstream fileStream;

  std::string format(LogLevel level, const std::string& msg){
    
    std::ostringstream oss;
    oss << "[" <<currentTime() << "] ";
    oss << "[" <<levelToString(level) << "] ";
    oss << msg << "\n";
    
    return oss.str();

  }  

  std::string currentTime() {
    
    std::time_t now = std::time(nullptr);
    char buff[20];
    strftime(buff, sizeof(buff), "%d-%m-%Y %H:%M:%S",std::localtime(&now));

    return buff;
  }
 
 std::string currentDate() {
    
    std::time_t now = std::time(nullptr);
    char buff[20];
    strftime(buff, sizeof(buff), "%d%m%Y",std::localtime(&now));

    return buff;
  }
  std::string levelToString(LogLevel level) {
    switch(level) {
      case LogLevel::DEBUG: return "DEBG";
      case LogLevel::INFO: return "INFO";
      case LogLevel::WARNING: return "WARN";
      case LogLevel::ERROR: return "ERRO";
      
    }
    return "UNKNOWN";
  }

};*/
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <format>
#include <ctime>

enum class LogLevel {
    DEBUG,
    INFO,
    WARNING,
    ERROR
};

class Logger {
public:
    Logger(LogLevel level = LogLevel::INFO, const std::string& filename = "")
        : minLevel(level)
    {
        if (!filename.empty()) {
            fileStream.open(filename, std::ios::app);
        }
    }

    ~Logger() {
        if (fileStream.is_open()) {
            fileStream.close();
        }
    }
    void enableDebug(bool enabled) {
      minLevel = enabled ? LogLevel::DEBUG : LogLevel::INFO;
    }

    // Variadic log method with formatting (C++20 std::format)
    template<typename... Args>
    void log(LogLevel level, std::format_string<Args...> fmt, Args&&... args) {
        if (level < minLevel) return;

        std::string msg = std::format(fmt, std::forward<Args>(args)...);
        std::string output = format(level, msg);

        std::cout << output;
        if (fileStream.is_open()) {
            fileStream << output;
        }
    }

    // Convenience methods
    template<typename... Args>
    void info(std::format_string<Args...> fmt, Args&&... args) {
        log(LogLevel::INFO, fmt, std::forward<Args>(args)...);
    }

    template<typename... Args>
    void debug(std::format_string<Args...> fmt, Args&&... args) {
        log(LogLevel::DEBUG, fmt, std::forward<Args>(args)...);
    }

    template<typename... Args>
    void warning(std::format_string<Args...> fmt, Args&&... args) {
        log(LogLevel::WARNING, fmt, std::forward<Args>(args)...);
    }

    template<typename... Args>
    void error(std::format_string<Args...> fmt, Args&&... args) {
        log(LogLevel::ERROR, fmt, std::forward<Args>(args)...);
    }

private:
    LogLevel minLevel;
    std::ofstream fileStream;

    std::string format(LogLevel level, const std::string& msg) {
        std::ostringstream oss;
        oss << "[" << currentTime() << "] ";
        oss << "[" << levelToString(level) << "] ";
        oss << msg << "\n";
        return oss.str();
    }

    std::string currentTime() {
        std::time_t now = std::time(nullptr);
        char buff[20];
        std::strftime(buff, sizeof(buff), "%d-%m-%Y %H:%M:%S", std::localtime(&now));
        return buff;
    }

    std::string levelToString(LogLevel level) {
        switch (level) {
            case LogLevel::DEBUG: return "DEBG";
            case LogLevel::INFO: return "INFO";
            case LogLevel::WARNING: return "WARN";
            case LogLevel::ERROR: return "ERRO";
        }
        return "UNKNOWN";
    }
};

//#endif
