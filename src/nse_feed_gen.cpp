// Implicit header files
#include <iostream>
#include <cstring>
#include <string>
#include <unistd.h>
#include <thread>

// Explicit header files
#include "app_structs.h"
#include "config_parser.h"
#include "app_defs.h"
#include "log.h"
#include "common.h"
#include "multicast.h"
#include "simulate_mtbt_values.h"

int main() {

  if(!isEnvScriptSourced())
  {
    std::cout<<"The environment script was not sourced!"<<std::endl;
    return FAILURE;
  }
  // Log Initialization
  std::string logDir = getenv("LOG_DIR");

  // Populating the current log file path along with its naming convention
  std::string logfilePath = logDir + "/log_" + getCurrentDate() + ".log";
  Logger logger(LogLevel::DEBUG, logfilePath);
  //Logger::setGlobalLogLevel(LogLevel::DEBUG);
  //Logger::setGlobalFilename(logfilePath);   
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
  
  std::string multicastGroup = config.getValue("MC_IP");
  int port = std::stoi(config.getValue("MC_PORT"));

  logger.info("Inisde the main function");
  logger.debug("The value for the key MC_IP is {}", config.getValue("MC_IP"));
  logger.debug("The value for the key MC_PORT is {}", config.getValue("MC_PORT"));
  
  // Setting up multicast
  int sock = setupMulticastSender(multicastGroup, port); 
  if(sock == -1) {
    logger.error("Multicast setup failed.");
    return FAILURE;
  }

  int sequenceNumber = 1;
  while(true) {
   
    if(sequenceNumber % 3 != 0) 
    {
      OrderMessage msg;
      SimulateMTBTValues simMTBTOrd;
      simMTBTOrd.populateOrderMessage(&msg, sequenceNumber); 
      simMTBTOrd.displayOrderMessage(&msg); 
      
      StreamHeader header;
      header.msgLen = sizeof(StreamHeader) + sizeof(OrderMessage);
      header.streamID = 1;
      header.sequenceNo = sequenceNumber++;
            
      // Create packet buffer
      char packet[sizeof(StreamHeader) + sizeof(OrderMessage)];
      memcpy(packet, &header, sizeof(StreamHeader));
      memcpy(packet + sizeof(StreamHeader), &msg, sizeof(OrderMessage));
            
      sendPacket(sock, multicastGroup, port, packet, sizeof(packet));
      logger.info("Order | Multicast Sent for Sequence No. {}", sequenceNumber);        
    } 
    else
    {
      TradeMessage msg;
      SimulateMTBTValues simMTBTTrd;
      simMTBTTrd.populateTradeMessage(&msg, sequenceNumber); 
      simMTBTTrd.displayTradeMessage(&msg); 
      
      StreamHeader header;
      header.msgLen = sizeof(StreamHeader) + sizeof(TradeMessage);
      header.streamID = 1;
      header.sequenceNo = sequenceNumber++;
            
      // Create packet buffer
      char packet[sizeof(StreamHeader) + sizeof(TradeMessage)];
      memcpy(packet, &header, sizeof(StreamHeader));
      memcpy(packet + sizeof(StreamHeader), &msg, sizeof(TradeMessage));
            
      sendPacket(sock, multicastGroup, port, packet, sizeof(packet));
      logger.info("Trade | Multicast Sent for Sequence No. {}", sequenceNumber); 
    }
  
    // Sleep for a bit to simulate realistic feed
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
  } 
  close(sock); 
  return SUCCESS;
}
