#include "server.hpp"

#include <cstdio>
#include <stdexcept>

namespace{

void DisplayErrorMsg(){
  printf("You need to give 2 arguments when starting the program\n");
  printf("First argument: ip number of server\n");
  printf("Second argument: server port number\n");
  printf("Example: ./program_name 127.200.200.15 54000\n");
}

int32_t ConvertPortNumberToInt32(char *port_num){
  int32_t port_number{};
  try{
    if(port_number = static_cast<int32_t>(std::stoi(port_num)) < 0){
      throw std::invalid_argument("");
    }    
  }
  catch(...){
    printf("Could not open up the server, port number argument is invalid\n");
    std::exit(3);
  }
  return port_number;
}

}// namespace


int main(int argc, char* argv[]){
  //----------------------------------------
  // if(argc != 3){
  //   DisplayErrorMsg();
  //   std::exit(2);
  // }
  argv[1] = "127.0.0.1";
  argv[2] = "54000";
  //---------------------------------------

  int32_t port_num{ConvertPortNumberToInt32(argv[2])};
  server::Server serv(argv[1], port_num);
  int return_value_main = serv.ServerInit();

  printf("Exiting program\n");

  return return_value_main;
}