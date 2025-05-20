// This header contains code related to multicast setup and sending of packets
#include <app_structs.h>
#include <iostream>
// Handle a parsed Order Message
void handleOrderMessage(const OrderMessage& msg);
// Handdle a parsed Trade Message
void handleTradeMessage(const TradeMessage& msg);

// Setup UDP Multicast socket
int setupSocket(const std::string& group, int port);

// Parses raw buffer
void parsePacket(const char* buffer, size_t size);
