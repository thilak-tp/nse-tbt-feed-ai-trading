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
  setRealtimeCPUPriorityAffinity(3,90);
 
  // Instances of structures used for receiving multicast data
  OrderMessage omsg;
  TradeMessage tmsg;

  // Check if the environment script is sourced or not
  if(!isEnvScriptSourced("CAPP_ROOT"))
  {
    std::cout<<"The environment script was not sourced!"<<std::endl;
    return FAILURE;
  }
  
  // Log Initialization
  std::string logDir = getenv("CLOG_DIR");
  if(logDir.empty()) {
    std::cout<<"Log directory not set in the environment"<<std::endl;
    return FAILURE;
  }
  
  // Populating the current log file path along with its naming convention
  std::string logfilePath = logDir + "//" +LOG_FILE_START + getCurrentDate() + ".log";

  //Logger logger(LogLevel::DEBUG, logfilePath);
  Logger::setGlobalLogLevel(LogLevel::DEBUG);
  Logger::setGlobalFilename(logfilePath);

  Logger logger;

  
  // Config Initialization
  ConfigParser config;
  if(!config.load("client_config.cfg")) {
    logger.warning("The configuration file specified was not found!");
    return FAILURE;
  }
  
  // Read the config file for the debug mode value, if true, add debug logs else don't
  std::string debugValue = config.getValue("DEBUG_MODE"); 
  if(debugValue == "1")
    logger.enableDebug(true);
  else
    logger.enableDebug(false);
  
  const std::string multicastGroup = config.getValue("MC_IP");
  const int port = std::stoi(config.getValue("MC_PORT"));


  int sock = setupSocket(multicastGroup, port);
  char buffer[4096];
  struct sockaddr_in sender_addr {};
  socklen_t addr_len = sizeof(sender_addr);

  while (true) {

    //ssize_t bytes_received = recv(sock, buffer, sizeof(buffer), 0);
    ssize_t bytes_received = recvfrom(
            sock,                      // your socket
            buffer, sizeof(buffer),   // buffer and its size
            0,                        // flags (usually 0)
            (struct sockaddr*)&sender_addr, &addr_len);
    if (bytes_received > 0) {
      parsePacket(buffer, bytes_received);
    }
    else {
       std::cout<<"recvfrom failded!"<<endl;
       continue;
    }
  }
  char sender_ip[INET_ADDRSTRLEN];
  inet_ntop(AF_INET, &(sender_addr.sin_addr), sender_ip, INET_ADDRSTRLEN);
  std::cout << "Received packet from " << sender_ip << ":" << ntohs(sender_addr.sin_port) 
    << " (" << bytes_received << " bytes)" << std::endl;

  parsePacket(buffer, bytes_received);

  close(sock);

  return 0;
}
