#pragma pack(push, 1)

// Structure for NSE CM Feed Header
struct StreamHeader {
  
  int16_t msgLen;     //Total packet size including header and payload     
  int16_t streamID;   //This identifies a particular stream
  int32_t sequenceNo; //This is the seq. no. of a packet for a particular stream ID

}; 

struct OrderMessage {
  
  char msgType;      //'N':New Order, 'M':Order Modification, 'X':Order Cancelled
  long timestamp;    //Time in nanoseconds from 1st Jan 1980
  double orderID;    //Day Unique Order Reference number
  int tokenID;       //Unique Contact Identifier
  char orderType;    //'B':Buy Order, 'S':Sell Order
  int price;         //Price of the order (In Paise):To be divided by 100 for Rupee
  int quantity;      //Quantity of the order

};

struct TradeMessage {
  
  char msgType;      //'N':New Order, 'M':Order Modification, 'X':Order Cancelled
  long timestamp;    //Time in nanoseconds from 1st Jan 1980
  double buyOrderID; //Day Unique Order Reference Number for Buy-Side order
  double sellOrderID;//Day Unique Order Reference Number for Sell-Side order
  int tokenID;       //Unique Contract Identifier
  int tradePrice;    //Trade Price (In Paise):To be divided by 100 for Rupee
  int tradeQuantity; //Quantity of the order
  
};

#pragma pack(pop)
