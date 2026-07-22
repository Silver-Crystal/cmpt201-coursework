
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>

#define PATH "tmp_sock"

int main() {
  // socket()
  // int sock_fd = socket(AF_LOCAL, SOCK_DGRAM, 0 );
  int sock_fd = socket(AF_LOCAL, SOCK_DGRAM, 0);
  if (sock_fd == -1) {
    perror("socket");
    // exit(errno);
    exit(EXIT_FAILURE);
  }
  //  delete socket
  //  remove
  if (remove(PATH) == -1 && errno != ENOENT) {
    perror("remove");
    exit(EXIT_FAILURE);
  }
  //  bind()
  struct sockaddr_un sock_addr;
  memset(&sock_addr, 0, sizeof(sock_addr));
  sock_addr.sun_family = AF_UNIX;
  // sock_addr.sun_path =
  strncpy(sock_addr.sun_path, PATH, sizeof(sock_addr.sun_path) - 1);
  if (bind(sock_fd, (struct sockaddr *)&sock_addr, sizeof(sock_addr)) == -1) {
    perror("bind");
    exit(EXIT_FAILURE);
  }

  // listen()
  // backlog-> might be several clients connected to the same server, controls how many can be
  // connected to the server.
  // accept()
  // for(;;){}
  // read()
  for (;;) {
    char buf[1024];
    int size_read = recvfrom(sock_fd, buf, sizeof(buf), 0, NULL, NULL);
    if (size_read > 0) {
      // write()
      if (write(STDOUT_FILENO, buf, size_read) == -1) {
        perror("write");
        exit(EXIT_FAILURE);
      }
    } else {
      break;
    }
  }
  // 0 -> EOF, -1-> error, some other number ->
  // close()
  close(sock_fd);
  // tcp, uses af unix, local socket

  return 0;
}
