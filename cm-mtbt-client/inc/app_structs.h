//This header contains the commonly used structures in the program
#ifndef APP_STRUCT_H
#define APP_STRUCT_H


#include<cstdint>
#include<map>



// Internal OrderBook Structures
struct Order {
    double order_id;
    int price;    // in paise
    int quantity;
    char side;    // 'B' or 'S'
};

struct OrderBook {
    std::multimap<int, Order, std::greater<int>> buy_orders;  // Highest price first
    std::multimap<int, Order, std::less<int>> sell_orders;    // Lowest price first
};

struct MarketSnapshot {
    int best_buy_price = 0;
    int best_sell_price = 0;
    int best_buy_qty = 0;
    int best_sell_qty = 0;
    double last_traded_price = 0;
    int last_traded_qty = 0;
    int token = 0;
    int64_t timestamp = 0;
};

// Global OrderBooks per token
inline std::map<int, OrderBook> order_books;

// Structure for NSE CM Feed Header
struct StreamHeader {
  
  int16_t msgLen;     //Total packet size including header and payload     
  int16_t streamID;   //This identifies a particular stream
  int32_t sequenceNo; //This is the seq. no. of a packet for a particular stream ID

}; 

// Structure for NSE CM Order Message
struct OrderMessage {
  
  char msgType;      //'N':New Order, 'M':Order Modification, 'X':Order Cancelled
  long timestamp;    //Time in nanoseconds from 1st Jan 1980
  double orderID;    //Day Unique Order Reference number
  int tokenID;       //Unique Contact Identifier
  char orderType;    //'B':Buy Order, 'S':Sell Order
  int price;         //Price of the order (In Paise):To be divided by 100 for Rupee
  int quantity;      //Quantity of the order

};

// Structure for NSE CM Trade Message
struct TradeMessage {
  
  char msgType;      //'N':New Order, 'M':Order Modification, 'X':Order Cancelled
  long timestamp;    //Time in nanoseconds from 1st Jan 1980
  double buyOrderID; //Day Unique Order Reference Number for Buy-Side order
  double sellOrderID;//Day Unique Order Reference Number for Sell-Side order
  int tokenID;       //Unique Contract Identifier
  int tradePrice;    //Trade Price (In Paise):To be divided by 100 for Rupee
  int tradeQuantity; //Quantity of the order
  
};
#endif
