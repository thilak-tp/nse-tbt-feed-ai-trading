#include "log.h"

LogLevel Logger::defaultLevel = LogLevel::DEBUG;
std::string Logger::defaultFilename = "default.log";
void Logger::setGlobalLogLevel(LogLevel level) {
    Logger::defaultLevel = level;
}

void Logger::setGlobalFilename(const std::string& name) {
    Logger::defaultFilename = name;
}
/*
// To Get the static log level
std::string Logger::getGlobalLogLevel() {
    return defaultLevel; 
}

// To Get the static filename
std::string Logger::getGlobalFilename() {
    return Logger::defaultFilename; 
}
// To Get the log level
LogLevel Logger::getGlobalLogLevel() {
    return Logger::defaultLevel;
}
*/
