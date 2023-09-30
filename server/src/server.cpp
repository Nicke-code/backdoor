#include "server.hpp"
#include "return_values.hpp"

extern "C"{
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netdb.h>
}
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <string>
#include <iostream>

namespace server{

Server::Server(char *ip_address, int32_t port_number)
  :port_number_{port_number}, listening_socket_{0}{
  snprintf(ip_address_, sizeof(ip_address_), "%s",ip_address);
  }


bool Server::ServerInit(){
  listening_socket_ = socket(AF_INET, SOCK_STREAM, 0);
  if(listening_socket_ == return_value::kFailure){
    printf("Could not initiate socket\n");
    return EXIT_FAILURE;
  }

  if(BindListeningToSocket() == return_value::kFailure){
    printf("Could not bind to socket\n");
    return EXIT_FAILURE;
  }

  const uint8_t kMaxNumQue{2};//SOMAXCONN   increase later and add threads or processes
  listen(listening_socket_, kMaxNumQue);

  bool keep_connection{true};
  std::string wait_for_a_new_connection{"no"};

  while(keep_connection){
    sockaddr_in client;
    int client_socket = AcceptConnection(client);
    keep_connection = HandleConnection(client_socket, client);
    //printf("wait for a new connection, state yes or no:> ");
    // std::getline(std::cin, wait_for_a_new_connection);
    // if(wait_for_a_new_connection == "yes")//{ === tolower()===
    //   keep_connection = true;
    // }
  }

  return EXIT_SUCCESS;
}


int8_t Server::BindListeningToSocket(){
  sockaddr_in hint;
  hint.sin_family = AF_INET;
  hint.sin_port = htons(port_number_);
  inet_pton(AF_INET, ip_address_, &hint.sin_addr);
  return bind(listening_socket_, reinterpret_cast<sockaddr*>(&hint), sizeof(hint));
}


int Server::AcceptConnection(sockaddr_in &client){
  socklen_t client_size{sizeof(client)};
  char host[NI_MAXHOST];
  char svc[NI_MAXSERV];
  memset(host, 0, sizeof(host));
  memset(svc, 0, sizeof(svc));

  int client_socket = accept(listening_socket_, reinterpret_cast<sockaddr*>(&client), &client_size);
  if(getnameinfo(reinterpret_cast<sockaddr*>(&client), sizeof(client), host, NI_MAXHOST, svc, NI_MAXSERV, 0) == 0){
    printf("%s connected on %s\n", host, svc);
  }
  return client_socket;
}


bool Server::HandleConnection(const int &client_socket, const sockaddr_in &client){
  char buffer[kBufferLength];
  char response[kResponseLength];
  std::string input_str{};
  bool keep_connection{true};

  while(keep_connection){
    memset(buffer, 0, sizeof(buffer));
    memset(response, 0, sizeof(response));
    printf("shell#%s~$: ", inet_ntoa(client.sin_addr));

    if(ReadInputCommand(input_str, buffer)){
      keep_connection = SendAndRecvData(client_socket, buffer, input_str, response);
    }
  }
  return keep_connection;
}


bool Server::ReadInputCommand(std::string &input_str, char buffer[]){
  bool string_is_ok{true};
  std::getline(std::cin, input_str);
  if(input_str.size() < kBufferLength){
    std::strncpy(buffer, input_str.c_str(), input_str.size());
    buffer[input_str.size()] =  '\0';
  }
  else{
    std::cerr << "input command was to long for buffer" << std::endl;
    string_is_ok = false;
  }
  return string_is_ok;
}


bool Server::SendAndRecvData(const int &client_socket, char buffer[], const std::string &input_str, char response[]){
  bool keep_connection{true};
  int8_t bytes_revc{};
  send(client_socket, buffer, input_str.size(), 0);
  if(input_str == "exit"){
    keep_connection = false;
  }
  bytes_revc = recv(client_socket, response, kResponseLength, MSG_WAITALL);
  if(bytes_revc = return_value::kConnectionIssue){
    printf("There was a connection issue, disconnecting...");
    keep_connection = false;
  }
  else if(bytes_revc == return_value::kClientDisconnected){
    printf("Client disconnect");
    keep_connection = false;
  }
  else{
    printf("%s\n", response);
  }
  return keep_connection;
}


}// namespace server