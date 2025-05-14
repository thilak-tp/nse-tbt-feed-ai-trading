#include "simulate_mtbt_values.h"

  

int SimuluteMTBTValues::getTokenDist()
{
  return tokenDist(gen); 
}

int SimuluteMTBTValues::getPriceDist()
{
  return priceDist(gen);
}

int SimuluteMTBTValues::getQtyDist()
{
  return qtyDist(gen);
}

long getCurrentTimestamp() {
    return std::chrono::duration_cast<std::chrono::milliseconds>(
        std::chrono::system_clock::now().time_since_epoch()).count();
}

// Probalistically generate message type to simulate realworld scenerio
char getRandomizedMsgType()
{
  double r = dis(gen);
  
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
char getRandomizedOrderType()
{
  double r = dis(gen);
  
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
    msg->tokenID = getTokenDist(gen);
    msg->orderType = getRandomizedOrderType();
    msg->price = getPriceDist(gen);
    msg->quantity = getQtyDist(gen); 
}

void SimulateMTBTValues::populateTradeMessage(TradeMessage *msg, int seqNo)
{
    msg->msgType = 'T';
    msg->timestamp = getCurrentTimestamp();
    msg->buyOrderID = AVG_ORDERID_DIGITS + seqNo - 1;
    msg->sellOrderID = AVG_ORDERID_DIGITS + seqNo - 2;
    msg->tokenID = getTokenDist(gen);
    msg->tradePrice = getPriceDist(gen);
    msg->tradeQuantity = getQtyDist(gen); 
}

void displayOrderMessage(OrderMessage &msg)
{
  logger.info("ORDER | {} | {} | {} | {} | {} | {} | {} | {} |",
    msg->msgType, msg->timestamp, msg->orderID, msg->tokenID, msg->orderType,
    msg->price, msg->quantity);
}

void displayTradeMessage(OrderMessage &msg)
{
  logger.info("TRADE | {} | {} | {} | {} | {} | {} | {} | {} |", 
    msg->msgType, msg->timestamp, msg->buyOrderID, msg->sellOrderID, msg->tokenID, 
    msg->tradePrice, msg->tradeQuantity);
}

  
 
