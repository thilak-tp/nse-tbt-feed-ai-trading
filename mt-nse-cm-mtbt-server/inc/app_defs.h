// This header contains all the commonly used definitions in the program

#pragma once
// An enum to handle return values
enum RetVal {
  SUCCESS,
  FAILURE
};


#define CORE_INDEX 2
#define SCHED_PRIORITY 90
#define ROOT_DIR_ENV "TAPP_ROOT"
#define LOG_DIR_ENV "TLOG_DIR"
#define DIRECTORY_SEPARATOR "/"
#define CONFIG_FILE_NAME "server_config.cfg"
#define MC_IP_KEY "MC_IP"
#define MC_PORT_KEY "MC_PORT"
