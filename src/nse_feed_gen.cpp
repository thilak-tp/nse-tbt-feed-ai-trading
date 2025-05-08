// Implicit header files
#include <iostream>

// Explicit header files
#include "app_structs.h"
#include "config_parser.h"

int main() {
  // Config Initialization
  ConfigParser config;
  if(!config.load("multicast_config.cfg")) {
    //TODO Add approriate logging when logging is implemented
  }
}
