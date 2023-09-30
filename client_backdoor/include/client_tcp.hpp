#ifndef XPLOIT_DEV_INCLUDE_CLIENT_TCP_HPP
#define XPLOIT_DEV_INCLUDE_CLIENT_TCP_HPP


namespace client_tcp{


class ClientTcp{
public:
  ClientTcp();
  ~ClientTcp() = default;
  void ClientInit();

private:
  int socket;


};

}// namespace clentTcp
#endif