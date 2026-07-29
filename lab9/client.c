// 1. What is the address of the server it is trying to connect to (IP address nad port number)
// address is loopback address or 127.0.0.1
// 2. Is it UDP or TCP? How do you know?
// TCP, we can see from the second variable that is inputted in a call to make a new socket/ socket(
// SOCK_STREAM -> we use this i.e it is tcp, would be udp if we instead used dgramM
// 3> The client is going to send some data to the servr. Where does it get this data from ? How can
// you tell in the code ?
// the client reads from the user input to get this data
// 4. How does the client program end ? How can you tell that in the code ?
// the line looping while the input is greater then 1
// i.e, if we press enter, the only input sent will be \n\0, and read will not count \0 and \n will
// be counted as '1' character, therefore the program will end gracefully(another method is ofc just
// pressing ctrl + d ig )
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#define PORT 8000
#define BUF_SIZE 64
#define ADDR "127.0.0.1"

#define handle_error(msg)                                                                          \
  do {                                                                                             \
    perror(msg);                                                                                   \
    exit(EXIT_FAILURE);                                                                            \
  } while (0)

int main() {
  struct sockaddr_in addr;
  int sfd;
  ssize_t num_read;
  char buf[BUF_SIZE];

  sfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sfd == -1) {
    handle_error("socket");
  }

  memset(&addr, 0, sizeof(struct sockaddr_in));
  addr.sin_family = AF_INET;
  addr.sin_port = htons(PORT);
  if (inet_pton(AF_INET, ADDR, &addr.sin_addr) <= 0) {
    handle_error("inet_pton");
  }

  int res = connect(sfd, (struct sockaddr *)&addr, sizeof(struct sockaddr_in));
  if (res == -1) {
    handle_error("connect");
  }

  while ((num_read = read(STDIN_FILENO, buf, BUF_SIZE)) > 1) {
    if (write(sfd, buf, num_read) != num_read) {
      handle_error("write");
    }
    printf("Just sent %zd bytes.\n", num_read);
  }

  if (num_read == -1) {
    handle_error("read");
  }

  close(sfd);
  exit(EXIT_SUCCESS);
}
