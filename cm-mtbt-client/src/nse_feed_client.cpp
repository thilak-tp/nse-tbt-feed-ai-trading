// Implementation main file for the NSE MTBT Feed Client
// Implicit header files
#include <iostream>
#include <cstring>
#include <string>
#include <unistd.h>
#include <thread>
#include <fcntl.h>

// Explicit header files
#include "app_structs.h"
#include "config_parser.h"
#include "app_defs.h"
#include "log.h"
#include "common.h"
#include "multicast.h"

int main() {


  // Bind thread to a single core and also set the application priority to max
  setRealtimeCPUPriorityAffinity();
  
  return 0;
}
