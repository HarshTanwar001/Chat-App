#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main(){

  char *ip = "127.0.0.1";
  int port = 5566;

  int sock;
  struct sockaddr_in addr;
  socklen_t addr_size;
  char buffer[1024];

  sock = socket(AF_INET, SOCK_STREAM, 0);
  if (sock < 0){
    perror("Socket error");
    exit(1);
  }
  printf("TCP server socket created.\n");

  memset(&addr, '\0', sizeof(addr));
  addr.sin_family = AF_INET;
  addr.sin_port = port;
  addr.sin_addr.s_addr = inet_addr(ip);

  connect(sock, (struct sockaddr*)&addr, sizeof(addr));
  printf("Connected to the server.\n\n");

  while(1){
    bzero(buffer, 1024);
    char client_text[1024];
    printf("Client: ");
    fgets(client_text, sizeof(client_text), stdin);

    if (client_text[0] == '\n'){
      close(sock);
      printf("\nDisconnected from the server.\n");
      return 0;
    }

    else {
      strcpy(buffer, client_text);
      send(sock, buffer, strlen(buffer), 0);

      bzero(buffer, 1024);
      recv(sock, buffer, sizeof(buffer), 0);

      if (strlen(buffer) == 0){
        close(sock);
        printf("\nServer has broken the connection.\n");
        return 0;
      }
      
      else {
        printf("Server: %s\n", buffer);
      }
    }
  }
}
