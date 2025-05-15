// Implementation file for the log class static functions
#include "log.h"

LogLevel Logger::defaultLevel = LogLevel::INFO;
std::string Logger::defaultFilename = "";

void Logger::setGlobalLogLevel(LogLevel level) {
    Logger::defaultLevel = level;
}

void Logger::setGlobalFilename(const std::string& name) {
    Logger::defaultFilename = name;
}

