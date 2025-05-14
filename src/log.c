/*// A source code to implement application logging which include log levels and also includes taking arguements

#include "log.h"


    Logger::Logger(LogLevel level = LogLevel::INFO, const std::string& filename)
        : minLevel(level)
    {
        if (!filename.empty()) {
            fileStream.open(filename, std::ios::app);
        }
    }

    Logger::~Logger() {
        if (fileStream.is_open()) {
            fileStream.close();
        }
    }

    // A funtion to enable or disable debug mode
    void Logger::enableDebug(bool enabled) {
      minLevel = enabled ? LogLevel::DEBUG : LogLevel::INFO;
    }

    // A log function that takes arguements as well
    template<typename... Args>
    void Logger::log(LogLevel level, std::format_string<Args...> fmt, Args&&... args) {
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
    void Logger::info(std::format_string<Args...> fmt, Args&&... args) {
        log(LogLevel::INFO, fmt, std::forward<Args>(args)...);
    }

    template<typename... Args>
    void Logger::debug(std::format_string<Args...> fmt, Args&&... args) {
        log(LogLevel::DEBUG, fmt, std::forward<Args>(args)...);
    }

    template<typename... Args>
    void Logger::warning(std::format_string<Args...> fmt, Args&&... args) {
        log(LogLevel::WARNING, fmt, std::forward<Args>(args)...);
    }

    template<typename... Args>
    void Logger::error(std::format_string<Args...> fmt, Args&&... args) {
        log(LogLevel::ERROR, fmt, std::forward<Args>(args)...);
    }

private:

    // To add current time and log level to each log string
    // TODO to add microsecond level logging
    std::string  Logger::format(LogLevel level, const std::string& msg) {
        std::ostringstream oss;
        oss << "[" << currentTime() << "] ";
        oss << "[" << levelToString(level) << "] ";
        oss << msg << "\n";
        return oss.str();
    }

    // A function to get the current timestamp
    std::string Logger::currentTime() {
        std::time_t now = std::time(nullptr);
        char buff[20];
        std::strftime(buff, sizeof(buff), "%d-%m-%Y %H:%M:%S", std::localtime(&now));
        return buff;
    }
    
    // A function to map each log level to a string so we can use it in the log strings while writing log
    std::string Logger::levelToString(LogLevel level) {
        switch (level) {
            case LogLevel::DEBUG: return "DEBG";
            case LogLevel::INFO: return "INFO";
            case LogLevel::WARNING: return "WARN";
            case LogLevel::ERROR: return "ERRO";
        }
        return "UNKNOWN";
    }
*/
