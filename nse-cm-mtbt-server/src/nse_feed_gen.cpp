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
#include "latency_benchmark.h"

int main() {
  // Bind thread to a single core and also set the application priority to max
  LatencyBenchmark bench;
  bench.start();
  //setRealtimeCPUPriorityAffinity(CORE_INDEX, SCHED_PRIORITY);

  // Instances of structures used for populating and multicasting data
  OrderMessage omsg = {0};
  TradeMessage tmsg = {0};

  StreamHeader header = {0}; 
  SimulateMTBTValues simMTBTOrd;
  SimulateMTBTValues simMTBTTrd;
  

   
  // Check if the environment script is sourced or not
  if(!isEnvScriptSourced(ROOT_DIR_ENV))
  {
    std::cout<<"The environment script was not sourced!"<<std::endl;
    return FAILURE;
  }

  // Getting the log directory from the environment
  const char* envVal = getenv(LOG_DIR_ENV);
  if (!envVal) {
    std::cout << "Log directory not set in the environment" << std::endl;
    return FAILURE;
  }

  std::string logDir(envVal);

  // Populating the current log file path along with its naming convention
  std::string logfilePath = logDir + DIRECTORY_SEPARATOR +LOG_FILE_START + getCurrentDate() + ".log";
  //std::cout<<"The logfile path is "<<logfilePath<<std::endl;
  
  Logger::setGlobalLogLevel(LogLevel::DEBUG);
  Logger::setGlobalFilename(logfilePath);
  Logger logger(LogLevel::DEBUG, logfilePath);

  // Config Initialization
  ConfigParser config;
  if(!config.load(CONFIG_FILE_NAME)) {
    logger.warning("The configuration file specified was not found!");
    return FAILURE;
  }
  
  // Read the config file for the debug mode value, if true, add debug logs else don't
  std::string debugValue = config.getValue("DEBUG_MODE"); 
  if(debugValue == "1") {
    logger.enableDebug(true);
    std::cout<<"Debug is on";
  }
  else
    logger.enableDebug(false);
  
  //std::cout<<"The debug value is "<<debugValue; 
  const std::string multicastGroup = config.getValue(MC_IP_KEY);
  const int port = std::stoi(config.getValue(MC_PORT_KEY));

  logger.info("Inisde the main function");
  logger.info("The value for the key MC_IP is {}", config.getValue(MC_IP_KEY));
  logger.info("The value for the key MC_PORT is {}", config.getValue(MC_PORT_KEY));
  
  // Setting up multicast
  int sock = setupMulticastSender(multicastGroup, port); 
  if(sock == -1) {
    logger.error("Multicast setup failed.");
    return FAILURE;
  }

  // Setting the socket to non blocking mode so the system interrupts don't block the sock operations
  fcntl(sock, F_SETFL, O_NONBLOCK);



  int sequenceNumber = 1;

  bench.stop();
  bench.report();
  bench.reset();
  while(true) {
    

    if(sequenceNumber % 3 != 0) {

      //time2 = getCurrentTimestampUs();
      memset(&omsg,0,sizeof(omsg));
      memset(&header,0,sizeof(header));
      simMTBTOrd.populateOrderMessage(&omsg, sequenceNumber); 
      //simMTBTOrd.displayOrderMessage(&omsg); 
      



      header.msgLen = sizeof(StreamHeader) + sizeof(OrderMessage);
      header.streamID = 1;
      header.sequenceNo = sequenceNumber++;
      //std::cout<<std::fixed<<omsg.msgType<<" "<<omsg.timestamp<<" "<<omsg.orderID<<" "<<omsg.tokenID<<" "<<omsg.orderType<<" "<<omsg.price<<" "<<omsg.quantity<<std::endl;      
      // Create packet buffer
      char packet[sizeof(StreamHeader) + sizeof(OrderMessage)];
      memcpy(packet, &header, sizeof(StreamHeader));
      memcpy(packet + sizeof(StreamHeader), &omsg, sizeof(OrderMessage));
            


      sendPacket(sock, multicastGroup, port, packet, sizeof(packet));
      //logger.info("Order | Multicast Sent for Sequence No. {}", sequenceNumber);        


      //if (sequenceNumber % 100 == 0)
      //  bench.report();



    } 
    else {

      memset(&tmsg,0,sizeof(tmsg));

      memset(&header,0,sizeof(header));
      simMTBTTrd.populateTradeMessage(&tmsg, sequenceNumber); 
      //simMTBTTrd.displayTradeMessage(&tmsg); 
      
      header.msgLen = sizeof(StreamHeader) + sizeof(TradeMessage);
      header.streamID = 1;
      header.sequenceNo = sequenceNumber++;
       
      //std::cout<<std::fixed<<tmsg.msgType<<" "<<tmsg.timestamp<<" "<<tmsg.buyOrderID<<" "<<tmsg.sellOrderID<<" "<<tmsg.tokenID<<" "<<tmsg.tradePrice<<" "<<tmsg.tradeQuantity<<std::endl;      
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

  bench.reset();
  close(sock); 
  return SUCCESS;
}
