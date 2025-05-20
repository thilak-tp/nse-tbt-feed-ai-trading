// A header to implement application logging which include log levels and also includes taking arguements

// Implicit headerfiles
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <format>
#include <ctime>

#define LOG_FILE_START "server_log_"

enum class LogLevel {
    DEBUG,
    INFO,
    WARNING,
    ERROR
};

class Logger {

  public:
     

    Logger(LogLevel level = defaultLevel, const std::string& filename = defaultFilename): minLevel(level) {
      //std::string fileToOpen = filename.empty() ? defaultFilename : filename;
      std::string fileToOpen = filename.empty() ? Logger::defaultFilename : filename; 
      if (!fileToOpen.empty()) {
        fileStream.open(fileToOpen, std::ios::app);
        if(!fileStream.is_open()) {
          std::cout<<"Failed to open log file "<<fileToOpen<<std::endl;
        }
      }
      else {
        std::cout<<"Default filename is also empty"<<std::endl;  
      }

    }

    ~Logger() {
      if (fileStream.is_open()) {
        fileStream.close();
      }
    }
    
    // To set the static log level
    static void setGlobalLogLevel(LogLevel level);
    // To set the static log filename
    static void setGlobalFilename(const std::string& filename);

    // A funtion to enable or disable debug mode
    void enableDebug(bool enabled) {
      minLevel = enabled ? LogLevel::DEBUG : LogLevel::INFO;
    }

    // A log function that takes arguements as well
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
    
    // Static data members to have a commonly stored loglevel and filename
    static LogLevel defaultLevel;
    static std::string defaultFilename;
    
    LogLevel minLevel;
    std::ofstream fileStream;

    // To add current time and log level to each log string
    // TODO to add microsecond level logging
    std::string format(LogLevel level, const std::string& msg) {
        std::ostringstream oss;
        oss << "[" << currentTime() << "] ";
        oss << "[" << levelToString(level) << "] ";
        oss << msg << "\n";
        return oss.str();
    }

    // A function to get the current timestamp
    std::string currentTime() {
        std::time_t now = std::time(nullptr);
        char buff[20];
        std::strftime(buff, sizeof(buff), "%d-%m-%Y %H:%M:%S", std::localtime(&now));
        return buff;
    }
    
    // A function to map each log level to a string so we can use it in the log strings while writing log
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

