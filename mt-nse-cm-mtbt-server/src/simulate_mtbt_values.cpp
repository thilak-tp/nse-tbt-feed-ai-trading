#include "simulate_mtbt_values.h"
#include<random>
#include <chrono>
#include "log.h"

  
SimulateMTBTValues::SimulateMTBTValues() : gen(rd()), priceDist(10000, 20000), qtyDist(1, 100), tokenDist(1000, 1100), msgTypeDis(0.0, 1.0) {} 

int SimulateMTBTValues::getTokenDist()
{
  return tokenDist(gen); 
}

int SimulateMTBTValues::getPriceDist()
{
  return priceDist(gen);
}

int SimulateMTBTValues::getQtyDist()
{
  return qtyDist(gen);
}

long SimulateMTBTValues::getCurrentTimestamp() {
    return std::chrono::duration_cast<std::chrono::milliseconds>(
        std::chrono::system_clock::now().time_since_epoch()).count();
}

// Probalistically generate message type to simulate realworld scenerio
char SimulateMTBTValues::getRandomizedMsgType()
{
  double r = msgTypeDis(gen);
  
  if(r < MAX_NEW_ORDER_PROB) {
    return 'N';
  }
  else if(r < MAX_NEW_ORDER_PROB + MAX_ORDER_MODIFICATION_PROB) {
    return 'M';
  } else {
    return 'X';
  }
}

// Probalistically generate order type to simulate realworld scenerio
char SimulateMTBTValues::getRandomizedOrderType()
{
  double r = msgTypeDis(gen);
  
  if(r < MAX_BUY_PROB) {
    return 'B';
  }
  else
    return 'S';
}

void SimulateMTBTValues::populateOrderMessage(OrderMessage *msg, int seqNo) 
{
    msg->msgType = getRandomizedMsgType();
    msg->timestamp = getCurrentTimestamp();
    msg->orderID = AVG_ORDERID_DIGITS + seqNo;
    msg->tokenID = getTokenDist();
    msg->orderType = getRandomizedOrderType();
    msg->price = getPriceDist();
    msg->quantity = getQtyDist(); 
}

void SimulateMTBTValues::populateTradeMessage(TradeMessage *msg, int seqNo)
{
    msg->msgType = 'T';
    msg->timestamp = getCurrentTimestamp();
    msg->buyOrderID = AVG_ORDERID_DIGITS + seqNo - 1;
    msg->sellOrderID = AVG_ORDERID_DIGITS + seqNo - 2;
    msg->tokenID = getTokenDist();
    msg->tradePrice = getPriceDist();
    msg->tradeQuantity = getQtyDist(); 
}

void SimulateMTBTValues::displayOrderMessage(OrderMessage *msg)
{/*
  Logger logger(LogLevel::DEBUG);
  logger.info("ORDER | {} | {} | {} | {} | {} | {} | {} |",
    msg->msgType, msg->timestamp, msg->orderID, msg->tokenID, msg->orderType,
    msg->price, msg->quantity);
*/
}

void SimulateMTBTValues::displayTradeMessage(TradeMessage *msg)
{
/*
  Logger logger(LogLevel::DEBUG);
  logger.info("TRADE | {} | {} | {} | {} | {} | {} | {} |", 
    msg->msgType, msg->timestamp, msg->buyOrderID, msg->sellOrderID, msg->tokenID, 
    msg->tradePrice, msg->tradeQuantity);
*/
}

  
 
