// This header contains code related to multicast setup and sending of packets
// Setup UDP Multicast socket
int setupSocket(const std::string& group, int port);

// Parses raw buffer
void parsePacket(const char* buffer, size_t size);
