
#include <arpa/inet.h>
#include <errno.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

int main() {
  // socket()
  // int sock_fd = socket(AF_LOCAL, SOCK_DGRAM, 0 );
  int sock_fd = socket(AF_INET, SOCK_STREAM, 0);
  if (sock_fd == -1) {
    perror("socket");
    // exit(errno);
    exit(EXIT_FAILURE);
  }
  //  bind() -> no bind
  // connect instead! (for tcp)
  struct sockaddr_in sock_addr;
  memset(&sock_addr, 0, sizeof(sock_addr));
  sock_addr.sin_family = AF_INET;
  sock_addr.sin_port = htons(8000);
  sock_addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
#if 0
  if (inet_pton(AF_INET, "127.0.0.1", &sock_addr.sin_addr.s_addr) == -1) {
    perror("inet_pton");
    exit(EXIT_FAILURE);
  }
#endif
  // sock_addr.sin_addr.s_addr = inet_pton(AF_INET, )
  if (connect(sock_fd, (struct sockaddr *)&sock_addr, sizeof(sock_addr)) == -1) {
    perror("connect");
    exit(EXIT_FAILURE);
  }

  // read from terminal()
  // for (;;){}-> keeps reading from the terminal...
  // read()
  for (;;) {
    char buf[1024];
    int size_read = read(STDIN_FILENO, buf, sizeof(buf));
    if (size_read > 0) {
      // write()
      if (write(sock_fd, buf, size_read) == -1) {
        perror("write");
        exit(EXIT_FAILURE);
      }
    } else {
      break; //  perror("read");
      // exit(EXIT_FAILURE);
    }
  }
  // 0 -> EOF, -1-> error, some other number ->
  // close()
  close(sock_fd);
  // tcp, uses af unix, local socket

  return 0;
}
