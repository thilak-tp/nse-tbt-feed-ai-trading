
#include "app_structs.h"
#include<random>

// Fixed probabilistic weights for new order, order modification and order cancellation
// packets to closely simulate real world scenerio
#define MAX_NEW_ORDER_PROB 0.1
#define MAX_ORDER_MODIFICATION_PROB 0.35
#define MAX_ORDER_CANCELLATION_PROB 0.55

//Fixed weight for order type : Buy or Sell
#define MAX_BUY_PROB  0.5
#define MAX_SELL_PROB 0.5

#define AVG_ORDERID_DIGITS 1000000

class SimulateMTBTValues {
  
  public:

  SimulateMTBTValues();
  int getTokenDist();
  int getPriceDist();
  int getQtyDist();
  char getRandomizedOrderType();
  char getRandomizedMsgType();
  long getCurrentTimestamp();
  void populateOrderMessage(OrderMessage *msg, int seqNo);
  void populateTradeMessage(TradeMessage *msg, int seqNo);
  void displayOrderMessage(OrderMessage *msg);
  void displayTradeMessage(TradeMessage *msg);

  private:
  
  std::random_device rd;
  std::mt19937 gen;
  std::uniform_int_distribution<> tokenDist;
  std::uniform_int_distribution<> priceDist;
  std::uniform_int_distribution<> qtyDist;
  std::uniform_real_distribution<> msgTypeDis;
 
};
