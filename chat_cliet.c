//
// Created by David Melesse on 1/31/25.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define SERVER_IP <vmwardrobe.westmont.edu>
#define SERVER_PORT 49153
#define BUFFER_SIZE 1024

int main() {
  int sock;
  struct sockaddr_in server_addr;
  char buffer[BUFFER_SIZE];
  char username[BUFFER_SIZE];

  // Socket Creation
  if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
    perror("Socket creation error");
    exit(EXIT_FAILURE);
  }

  // Configure server address
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(SERVER_PORT);
  if (inet_pton(AF_INET, SERVER_IP, &server_addr.sin_addr) <= 0) {
    perror("Invalid address/Address not supported");
    close(sock);
    exit(EXIT_FAILURE);
  }

  // Connect to the server
  if (connect(sock, (struct sockaddr *) &server_addr, sizeof(server_addr)) < 0) {
      perror("Connection failed");
      close(sock);
      exit(EXIT_FAILURE);
  }

  printf("Connected to the chat Sever");

  // Send Username
  printf("Enter your username");
  fgets(username, BUFFER_SIZE, stdin);
  username[strcspn(username, "\n")] = 0;
  send(sock, username, strlen(username), 0);
  send(sock, "\n", 1, 0);

  printf("You can start chatting. Type 'exit' to quit.\n");

  while(1) {
    //Read input from the user
    printf("> ");
    fgets(buffer, BUFFER_SIZE, stdin);
    buffer[strcspn(buffer, "\n")] = 0;

    // Send message to the server
    send(sock, buffer, strlen(buffer), 0);
    send(sock, "\n", 1, 0);

    // Check for exit command
    if (strcmp(buffer, "exit") == 0) {
      printf("Disconnecting from the server..\n");
      break;
    }

    // Receive and display messages from the server
    memset(buffer, 0, BUFFER_SIZE);
    if (recv(sock, buffer, BUFFER_SIZE, 0) <= 0) {
      perror("Server disconnected");
      break;
    }
    printf("Server: %s\n", buffer);

  }

  // Close the socket
  close(sock);
  return 0;
}