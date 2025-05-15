// A source file that implements some of the commond functions 

// Implicit header files
#include<string>
#include<ctime>

// A function that return current date in DDMMYYY format
// Used for log file naming convention
std::string getCurrentDate() {
   
  std::time_t now = std::time(nullptr);
  char buff[20];
  strftime(buff, sizeof(buff), "%d%m%Y",std::localtime(&now));

  return buff;
}

// A function to check if the environment script is sourced or not
bool isEnvScriptSourced()
{
  const char* val = getenv("APP_ROOT");
  
  return (val != nullptr);
}
