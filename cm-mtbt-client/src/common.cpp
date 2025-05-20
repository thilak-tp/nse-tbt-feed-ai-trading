// A source file that implements some of the commond functions 

// Explicit header files
#include "common.h"

// Implicit header files
#include<string>
#include<ctime>
#include<pthread.h>
#include<sched.h>

// A function that return current date in DDMMYYY format
// Used for log file naming convention
std::string getCurrentDate() {
   
  std::time_t now = std::time(nullptr);
  char buff[20];
  strftime(buff, sizeof(buff), "%d%m%Y",std::localtime(&now));

  return buff;
}

// A function to check if the environment script is sourced or not
bool isEnvScriptSourced() {

  const char* val = getenv("APP_ROOT");  
  return (val != nullptr);
}

// A function to bind the thread to a single core and also set affinity
void setRealtimeCPUPriorityAffinity() {
  
  // Setting realtime affinity
  cpu_set_t cpuset;
  CPU_ZERO(&cpuset);
  CPU_SET(3, &cpuset);

  int result = pthread_setaffinity_np(pthread_self(), sizeof(cpu_set_t), &cpuset);
  if(result != 0)
    std::cout<<"Failed to set CPU affinity"<<std::endl;
  else  
    std::cout<<"Successfully set CPU affinity to core 2"<<std::endl;
  
  // Set realtime priority
  sched_param schParams;
  schParams.sched_priority = 90;
  
  result = pthread_setschedparam(pthread_self(), SCHED_FIFO,&schParams);
  if(result != 0)
    std::cout<<"Failed to set realtime priority"<<std::endl;
  else
    std::cout<<"Successfully set realtime priority (FIFO 90)"<<std::endl;

}


// A millisecond level time function
std::string getCurrentTimestampMs() {
  using namespace std::chrono;

  // Get current time_point
  auto now = system_clock::now();
  auto now_ms = time_point_cast<milliseconds>(now);
  auto value = now_ms.time_since_epoch();
  long ms = value.count() % 1000;

  // Convert to time_t to get calendar time
  std::time_t now_c = system_clock::to_time_t(now);

  std::tm tm_now;
  #if defined(_WIN32) || defined(_WIN64)
    localtime_s(&tm_now, &now_c);
  #else
    localtime_r(&now_c, &tm_now);
  #endif

  // Format timestamp
  std::ostringstream oss;
  oss << std::put_time(&tm_now, "%Y-%m-%d %H:%M:%S")
  << '.' << std::setfill('0') << std::setw(3) << ms;

  return oss.str();
}

//Microsecond level timestamp function
std::string getCurrentTimestampUs() {
  using namespace std::chrono;
  
  auto now = system_clock::now();
  auto now_us = time_point_cast<microseconds>(now);
  auto value = now_us.time_since_epoch();
  long long us = value.count() % 1000000;

  std::time_t now_c = system_clock::to_time_t(now);
  std::tm tm_now;
  
  #if defined(_WIN32) || defined(_WIN64)
    localtime_s(&tm_now, &now_c);
  #else
    localtime_r(&now_c, &tm_now);
  #endif

  std::ostringstream oss;
  oss << std::put_time(&tm_now, "%Y-%m-%d %H:%M:%S")
        << '.' << std::setfill('0') << std::setw(6) << us;

  return oss.str();
}

//Nanosecond level time function
std::string getCurrentMicroseconds() {
  using namespace std::chrono;

  auto now = system_clock::now();
  auto now_us = time_point_cast<microseconds>(now);
  auto value = now_us.time_since_epoch();
  long long us = value.count() % 1000000;

  std::time_t now_c = system_clock::to_time_t(now);
  std::tm tm_now;
  
  #if defined(_WIN32) || defined(_WIN64)
    localtime_s(&tm_now, &now_c);
  #else
    localtime_r(&now_c, &tm_now);
  #endif

  std::ostringstream oss;
  oss << std::put_time(&tm_now, "%S")
        << '.' << std::setfill('0') << std::setw(6) << us;
  return oss.str();
}

