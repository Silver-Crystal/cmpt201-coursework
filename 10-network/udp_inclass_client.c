
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>

int main() {
  // socket()
  // int sock_fd = socket(AF_LOCAL, SOCK_DGRAM, 0 );
  int sock_fd = socket(AF_LOCAL, SOCK_DGRAM, 0);
  if (sock_fd == -1) {
    perror("socket");
    // exit(errno);
    exit(EXIT_FAILURE);
  }
  //  bind() -> no bind
  // connect instead! (for tcp)
  struct sockaddr_un sock_addr;
  memset(&sock_addr, 0, sizeof(sock_addr));
  sock_addr.sun_family = AF_UNIX;
  // sock_addr.sun_path =

  // read from terminal()
  // for (;;){}-> keeps reading from the terminal...
  // read()
  for (;;) {
    char buf[1024];
    int size_read = read(STDIN_FILENO, buf, sizeof(buf));
    if (size_read > 0) {
      // write()

      // if (write(sock_fd, buf, size_read) == -1) {
      if (sendto(sock_fd, buf, size_read, 0, (struct sockaddr *)&sock_addr, sizeof(sock_addr)) ==
          -1) {
        perror("write");
        exit(EXIT_FAILURE);
      }
    } else {
      break;
      //  perror("read");
      // exit(EXIT_FAILURE);
    }
  }
  // 0 -> EOF, -1-> error, some other number ->
  // close()
  close(sock_fd);
  // tcp, uses af unix, local socket

  return 0;
}
