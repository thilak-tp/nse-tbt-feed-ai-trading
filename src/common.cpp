// A source file that implements some of the commond functions 
#include<common.h>
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
bool isEnvScriptSourced()
{
  const char* val = getenv("APP_ROOT");
  
  return (val != nullptr);
}

// A function to bind the thread to a single core and also set affinity
void setRealtimeCPUPriorityAffinity()
{
  // Setting realtime affinity
  cpu_set_t cpuset;
  CPU_ZERO(&cpuset);
  CPU_SET(2, &cpuset);

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
