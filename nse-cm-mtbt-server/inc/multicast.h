// This header contains code related to multicast setup and sending of packets

// Setup multicast socket
int setupMulticastSender(const std::string& group, int port);

// Send multicast packet
void sendPacket(int sock, const std::string& group, int port, const char* data, size_t len);
