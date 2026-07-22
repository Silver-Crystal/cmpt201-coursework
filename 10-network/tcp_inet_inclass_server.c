
#include <errno.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

// #include <sys/un.h>
int main() {
  // socket()
  // int sock_fd = socket(AF_LOCAL, SOCK_DGRAM, 0 );
  int sock_fd = socket(AF_INET, SOCK_STREAM, 0);
  if (sock_fd == -1) {
    perror("socket");
    // exit(errno);
    exit(EXIT_FAILURE);
  }

  //  bind()
  struct sockaddr_in sock_addr;
  memset(&sock_addr, 0, sizeof(sock_addr));
  sock_addr.sin_family = AF_INET;
  sock_addr.sin_port = htons(8000);
  sock_addr.sin_addr.s_addr = htonl(INADDR_ANY);

  // sock_addr.sun_path =
  if (bind(sock_fd, (struct sockaddr *)&sock_addr, sizeof(sock_addr)) == -1) {
    perror("bind");
    exit(EXIT_FAILURE);
  }

  // listen()
  if (listen(sock_fd, 10) == -1) {
    perror("listen");
    exit(EXIT_FAILURE);
  }
  // backlog-> might be several lcients connected to the same server, controls how many can be
  // connected to the server.
  // accept()
  // for(;;){}
  int recv_fd = 0;
  for (;;) {
    int addrlen = sizeof(sock_addr);
    // int recv_fd = accept(sock_fd, sock_addr
    recv_fd = accept(sock_fd, NULL, NULL);
    if (recv_fd == -1) {
      // int recv_fd = accept(sock_fd, NULL, NULL);
      //  recv_fd = accept(sock_fd, NULL, NULL);
      perror("accept");
      exit(EXIT_FAILURE);
    }

    // for(;;){}
    // read()
    for (;;) {
      char buf[1024];
      int size_read = read(recv_fd, buf, sizeof(buf));
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
    close(recv_fd);
  }
  // 0 -> EOF, -1-> error, some other number ->
  // close()
  close(sock_fd);
  // close(recv_fd);
  //  tcp, uses af unix, local socket

  return 0;
}
