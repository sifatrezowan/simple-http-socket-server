#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>

#define PORT 8080

int main(int argc, char const *argv[])
{
  // Create server socket
  int server_socket = socket(AF_INET, SOCK_STREAM, 0);

  // Configure server address
  struct sockaddr_in server_address;
  server_address.sin_addr.s_addr = INADDR_ANY;
  server_address.sin_family = AF_INET;
  server_address.sin_port = htons(PORT);

  // Bind socket to local address
  bind(server_socket, (struct sockaddr *)&server_address, sizeof(server_address));

  // Mark socket to listen for incoming connectios, max of 10
  int listening = listen(server_socket, 10);
  if (listening < 0)
  {
    perror(("Socket not listening!"));
    exit(EXIT_FAILURE);
  }

  char header_200[8000] = "HTTP/1.1 200 OK\r\n\n";

  FILE *html_data = fopen("./pages/index.html", "r");

  char line[100];
  char response[8000];
  while (fgets(line, 100, html_data) != 0)
  {
    strcat(response, line);
  }
  strcat(header_200, response);

  int client_socket;
  int address_length = sizeof(server_address);
  long read_value;

  while (1)
  {
    client_socket = accept(server_socket, (struct sockaddr *)&server_address, (socklen_t *)&address_length);

    char buffer[30000] = {0};
    read_value = read(client_socket, buffer, sizeof(buffer));

    send(client_socket, header_200, sizeof(header_200), 0);

    printf("%s", buffer);
    // write(client_socket, header_200, strlen(header_200));

    close(client_socket);
  }

  return 0;
}