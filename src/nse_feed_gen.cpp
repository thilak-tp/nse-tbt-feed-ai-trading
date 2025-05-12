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
    std::cout<<"Unable to get the Log directory! Kindly source the enviroment script"<<std::endl;
  }

  // Populating the current log file path along with its naming convention
  std::string logfilePath = logDir + "/log_" + getCurrentDate() + ".log";
  Logger logger(LogLevel::DEBUG, logfilePath);
   
  // Config Initialization
  ConfigParser config;
  if(!config.load("app_config.cfg")) {
    logger.warning("The configuration file specified was not found!");
    return FAILURE;
  }
  
  // Read the config file for the debug mode value, if true, add debug logs else don't
  std::string debugValue = config.getValue("DEBUG_MODE"); 
  if(debugValue == "1")
    logger.enableDebug(true);
  else
    logger.enableDebug(false);

  logger.info("Inisde the main function");
  logger.debug("The value for the key MC_IP is {}", config.getValue("MC_IP"));
  logger.debug("The value for the key MC_PORT is {}", config.getValue("MC_PORT"));

  return 0;
}
