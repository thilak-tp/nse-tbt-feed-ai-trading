// Implicit header files
#include <iostream>
#include <string>

// Explicit header files
#include "app_structs.h"
#include "config_parser.h"
#include "app_defs.h"

int main() {
  // Config Initialization
  ConfigParser config;
  if(!config.load("multicast_config.cfg")) {
    //TODO Add approriate logging when logging is implemented
    std::cout<<"Config Init Failed"<<std::endl;
    return FAILURE;
  }

  
  std::cout<<"In the main function"<<std::endl;
  std::cout<<"The value for the key MC_IP is "<<config.getValue("MC_IP");
  std::cout<<"The value for the key MC_PORT is "<<config.getValue("MC_PORT");
  return 0;
}
