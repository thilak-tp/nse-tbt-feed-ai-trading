// This source code contains code related to multicast setup and sending of packets
#include <arpa/inet.h>
#include <sys/socket.h>
#include <cstring>
#include <string>
#include <unistd.h>


// Setup multicast socket
int setupMulticastSender(const std::string& group, int port) {
    int sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock < 0) {
        perror("socket failed");
        return -1;
    }

    // Configure multicast TTL (time to live)
    unsigned char ttl = 1; // Limit to local network
    if (setsockopt(sock, IPPROTO_IP, IP_MULTICAST_TTL, &ttl, sizeof(ttl)) < 0) {
        perror("setsockopt TTL failed");
        close(sock);
        return -1;
    }

    return sock;
}

// Send multicast packet
void sendPacket(int sock, const std::string& group, int port, const char* data, size_t len) {
    struct sockaddr_in addr {};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = inet_addr(group.c_str());

    ssize_t sent = sendto(sock, data, len, 0, (struct sockaddr*)&addr, sizeof(addr));
    if (sent < 0) {
        perror("sendto failed");
    }
}


