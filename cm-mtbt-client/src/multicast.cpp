// This source code contains code related to multicast setup and sending of packets
#include <sys/socket.h>
#include <sys/types.h>
#include <string>
#include <unistd.h>
#include <multicast.h>
#include <cstring>
#include <map>
#include <arpa/inet.h>  // For htons, ntohs, etc.
#include <netinet/in.h> // For sockaddr_in
//#include<app_structs.h>

// Handle a parsed Order Message
void handleOrderMessage(const OrderMessage& msg) {
    auto& book = order_books[msg.tokenID];
    if (msg.msgType == 'N' || msg.msgType == 'M') {
        Order order { msg.orderID, msg.price, msg.quantity, msg.orderType };
        if (msg.orderType == 'B')
            book.buy_orders.insert({msg.price, order});
        else
            book.sell_orders.insert({msg.price, order});
    } 
    else if (msg.msgType == 'X') {
        // Cancel - real systems match by OrderID, simplified here
        // TODO: Handle correct order cancel by ID
    }
}

// Handle a parsed Trade Message
void handleTradeMessage(const TradeMessage& msg) {
    auto& book = order_books[msg.tokenID];
    MarketSnapshot snapshot;

    snapshot.token = msg.tokenID;
    snapshot.timestamp = msg.timestamp;
    snapshot.last_traded_price = msg.tradePrice;
    snapshot.last_traded_qty = msg.tradeQuantity;

    if (!book.buy_orders.empty()) {
        snapshot.best_buy_price = book.buy_orders.begin()->first;
        snapshot.best_buy_qty = book.buy_orders.begin()->second.quantity;
    }

    if (!book.sell_orders.empty()) {
        snapshot.best_sell_price = book.sell_orders.begin()->first;
        snapshot.best_sell_qty = book.sell_orders.begin()->second.quantity;
    }

    // Here you would normally pass this snapshot to your AI model
    std::cout << "Market Snapshot: Token " << snapshot.token 
              << " BestBuy " << snapshot.best_buy_price 
              << " BestSell " << snapshot.best_sell_price 
              << " LTP " << snapshot.last_traded_price << std::endl;
}



// Setup UDP Multicast socket
int setupSocket(const std::string& group, int port) {
    int sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock < 0) {
        perror("socket failed");
        exit(1);
    }

    int reuse = 1;
    setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, (char*)&reuse, sizeof(reuse));

    struct sockaddr_in addr {};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = htonl(INADDR_ANY);

    if (bind(sock, (struct sockaddr*)&addr, sizeof(addr)) < 0) {
        perror("bind failed");
        close(sock);
        exit(1);
    }

    struct ip_mreq mreq {};
    mreq.imr_multiaddr.s_addr = inet_addr(group.c_str());
    mreq.imr_interface.s_addr = htonl(INADDR_ANY);

    if (setsockopt(sock, IPPROTO_IP, IP_ADD_MEMBERSHIP, (char*)&mreq, sizeof(mreq)) < 0) {
        perror("setsockopt failed");
        close(sock);
        exit(1);
    }

    return sock;
}

// Parses raw buffer
void parsePacket(const char* buffer, size_t size) {
    if (size < sizeof(StreamHeader)) return;

    const StreamHeader* header = reinterpret_cast<const StreamHeader*>(buffer);
    const char* payload = buffer + sizeof(StreamHeader);

    if (size < header->msgLen) return; // Invalid packet

    char msg_type = *payload;

    if (msg_type == 'N' || msg_type == 'M' || msg_type == 'X') {
        const OrderMessage* order_msg = reinterpret_cast<const OrderMessage*>(payload);
        handleOrderMessage(*order_msg);
    } 
    else if (msg_type == 'T') {
        const TradeMessage* trade_msg = reinterpret_cast<const TradeMessage*>(payload);
        handleTradeMessage(*trade_msg);
    }
    else {
        // Ignore other message types for now
    }
}

