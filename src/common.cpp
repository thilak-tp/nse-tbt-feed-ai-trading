#include<string>
#include<ctime>
std::string getCurrentDate() {
   
  std::time_t now = std::time(nullptr);
  char buff[20];
  strftime(buff, sizeof(buff), "%d%m%Y",std::localtime(&now));

  return buff;
}

