// Implicit header files
#include <iostream>
#include <string>

// Explicit header files
#include "app_structs.h"
#include "config_parser.h"
#include "app_defs.h"
#include "log.h"
#include "common.h"
int main() {

  // Log Initialization
  std::string logDir = getenv("LOG_DIR");
  if(logDir.empty()) {
    std::cout<<"Source the enviroment script"<<std::endl;
  }
  std::string logfilePath = logDir + "/log_" + getCurrentDate() + ".log";
  Logger logger(LogLevel::DEBUG, logfilePath);
   
  // Config Initialization
  ConfigParser config;
  if(!config.load("multicast_config.cfg")) {
    logger.warning("The environment script is not sourced");
    return FAILURE;
  }

  
  logger.info("Inisde the main function");
  std::cout<<"In the main function"<<std::endl;
  std::cout<<"The value for the key MC_IP is "<<config.getValue("MC_IP");
  std::cout<<"The value for the key MC_PORT is "<<config.getValue("MC_PORT");
  return 0;
}
