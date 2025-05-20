// This header contains all commonly written functions
#include <iostream>
#include <chrono>
#include <iomanip>
#include <sstream>

// A function that returns current time in seconds
std::string getCurrentMicroseconds();

// A function that binds threads to a core as well as set priority for the application
void setRealtimeCPUPriorityAffinity();

// A function that returns a current timestamp in DD-MM-YYYY H:M:S format
std::string getCurrentDate();

// A function that check if the environment script is sourced or not
bool isEnvScriptSourced();

// A function that returns the current timestamp with milliseconds precision (DD-MM-YYY H:M:S format)
std::string getCurrentTimestampMs();

// A function that returns the current timestamp with microseconds precision (DD-MM-YYY H:M:S format)
std::string getCurrentTimestampUs();
