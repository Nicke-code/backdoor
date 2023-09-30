#ifndef EXPLOIT_DEV_INCLUDE_SERVER_HPP
#define EXPLOIT_DEV_INCLUDE_SERVER_HPP
#include <cstdint>
#include <netinet/in.h>
#include <string>

namespace server{

constexpr uint16_t kBufferLength{1024};
constexpr uint16_t kResponseLength{18384};
constexpr uint8_t kIpAddressLength{20};

class Server{
public:
  Server(char* ip_address, int32_t port_number);
  ~Server() = default;
  bool ServerInit();

private:
  int8_t BindListeningToSocket();
  int AcceptConnection(sockaddr_in &client);
  bool HandleConnection(const int &client_socket, const sockaddr_in &client);
  bool ReadInputCommand(std::string &input_str, char buffer[]);
  bool SendAndRecvData(const int &client_socket, char buffer[], const std::string &input_str, char response[]);

  int listening_socket_;
  int32_t port_number_;
  char ip_address_[kIpAddressLength];
};

}// namespace server
#endif// EXPLOIT_DEV_INCLUDE_SERVER_HPP