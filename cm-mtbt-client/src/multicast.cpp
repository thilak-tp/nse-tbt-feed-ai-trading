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

    if (size < header->msg_len) return; // Invalid packet

    char msg_type = *payload;

    if (msg_type == 'N' || msg_type == 'M' || msg_type == 'X') {
        const OrderMessage* order_msg = reinterpret_cast<const OrderMessage*>(payload);
        handleOrderMessage(*order_msg);
    } 
    else if (msg_type == 'T') {
        const TradeMessage* trade_msg = reinterpret_cast<const TradeMessage*>(payload);
        handleTradeMessage(*trade_msg);
    }
    else if (msg_type == 'H') {
        const HeartbeatMessage* heart_beat_msg = reinterpret_cast<const HeartbeatMessage*>(payload);
        handleHeartBeatMessage(*heart_beat_msg);       
    }
    else {
        // Ignore other message types for now
    }
}

