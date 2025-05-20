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
#include "simulate_mtbt_values.h"

int main() {

  // Bind thread to a single core and also set the application priority to max
  setRealtimeCPUPriorityAffinity();

  // Instances of structures used for populating and multicasting data
  OrderMessage omsg;
  SimulateMTBTValues simMTBTOrd;
  TradeMessage tmsg;
  SimulateMTBTValues simMTBTTrd;

  // Check if the environment script is sourced or not
  if(!isEnvScriptSourced())
  {
    std::cout<<"The environment script was not sourced!"<<std::endl;
    return FAILURE;
  }

  // Log Initialization
  std::string logDir = getenv("LOG_DIR");
  if(logDir.empty()) {
    std::cout<<"Log directory not set in the environment"<<std::endl;
    return FAILURE;
  }
  // Populating the current log file path along with its naming convention
  std::string logfilePath = logDir + "/log_" + getCurrentDate() + ".log";

  //Logger logger(LogLevel::DEBUG, logfilePath);
  Logger::setGlobalLogLevel(LogLevel::DEBUG);
  Logger::setGlobalFilename(logfilePath);

  Logger logger;

  
  // Config Initialization
  ConfigParser config;
  if(!config.load("server_config.cfg")) {
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

  logger.info("Inisde the main function");
  logger.debug("The value for the key MC_IP is {}", config.getValue("MC_IP"));
  logger.debug("The value for the key MC_PORT is {}", config.getValue("MC_PORT"));
  
  // Setting up multicast
  int sock = setupMulticastSender(multicastGroup, port); 
  if(sock == -1) {
    logger.error("Multicast setup failed.");
    return FAILURE;
  }

  // Setting the socket to non blocking mode so the system interrupts don't block the sock operations
  fcntl(sock, F_SETFL, O_NONBLOCK);



  int sequenceNumber = 1;

  std::string time1, time2, time3;

  //time1 =  getCurrentTimestampUs();
  time1 =  getCurrentMicroseconds();
  while(true) {
    

    if(sequenceNumber % 3 != 0) {
      
      time2 = getCurrentMicroseconds();
      //time2 = getCurrentTimestampUs();
      memset(&omsg,0,sizeof(omsg));
      memset(&simMTBTOrd,0,sizeof(simMTBTOrd));
      simMTBTOrd.populateOrderMessage(&omsg, sequenceNumber); 
      //simMTBTOrd.displayOrderMessage(&omsg); 
      
      StreamHeader header;
      header.msgLen = sizeof(StreamHeader) + sizeof(OrderMessage);
      header.streamID = 1;
      header.sequenceNo = sequenceNumber++;
      std::cout<<omsg.msgType<<" "<<omsg.timestamp<<" "<<omsg.orderID<<" "<<omsg.tokenID<<" "<<omsg.orderType<<" "<<omsg.price<<" "<<omsg.quantity<<std::endl;      
      // Create packet buffer
      char packet[sizeof(StreamHeader) + sizeof(OrderMessage)];
      memcpy(packet, &header, sizeof(StreamHeader));
      memcpy(packet + sizeof(StreamHeader), &omsg, sizeof(OrderMessage));
            
      sendPacket(sock, multicastGroup, port, packet, sizeof(packet));
      //logger.info("Order | Multicast Sent for Sequence No. {}", sequenceNumber);        

      //time3 = getCurrentTimestampUs();
      time3 = getCurrentMicroseconds();
  
      float f1, f2, f3, diff;
      f1 = stof(time1);
      f2 = stof(time2);
      f3 = stof(time3);
      diff = f3 - f2;
      
  
      //std::cout<<"The Start time is "<<time2<<" and the end time is "<<time3<<std::endl;
      std::cout<<"The difference is "<<diff<<" seconcds"<<std::endl;
    } 
    else {

      memset(&tmsg,0,sizeof(tmsg));
      memset(&simMTBTTrd,0,sizeof(simMTBTTrd));
      simMTBTTrd.populateTradeMessage(&tmsg, sequenceNumber); 
      //simMTBTTrd.displayTradeMessage(&tmsg); 
      
      StreamHeader header;
      header.msgLen = sizeof(StreamHeader) + sizeof(TradeMessage);
      header.streamID = 1;
      header.sequenceNo = sequenceNumber++;
       
      std::cout<<tmsg.msgType<<" "<<tmsg.timestamp<<" "<<tmsg.buyOrderID<<" "<<tmsg.sellOrderID<<" "<<tmsg.tokenID<<" "<<tmsg.tradePrice<<" "<<tmsg.tradeQuantity<<std::endl;      
      // Create packet buffer
      char packet[sizeof(StreamHeader) + sizeof(TradeMessage)];
      memcpy(packet, &header, sizeof(StreamHeader));
      memcpy(packet + sizeof(StreamHeader), &tmsg, sizeof(TradeMessage));
            
      sendPacket(sock, multicastGroup, port, packet, sizeof(packet));
      //logger.info("Trade | Multicast Sent for Sequence No. {}", sequenceNumber); 
    }
  
    // Sleep for a bit to simulate realistic feed
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
  } 

  close(sock); 
  return SUCCESS;
}
