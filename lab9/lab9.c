/* client */
/* 1. What is the address of the server it is trying to connect to (IP address nad port number)
 address is loopback address or 127.0.0.1
 2. Is it UDP or TCP? How do you know?
 TCP, we can see from the second variable that is inputted in a call to make a new socket/ socket(
 SOCK_STREAM -> we use this i.e it is tcp, would be udp if we instead used dgramM
 3> The client is going to send some data to the servr. Where does it get this data from ? How can
 you tell in the code ?
 the client reads from the user input to get this data
 4. How does the client program end ? How can you tell that in the code ?
 the line looping while the input is greater then 1
 i.e, if we press enter, the only input sent will be \n\0, and read will not count \0 and \n will
 be counted as '1' character, therefore the program will end gracefully(another method is ofc just
 pressing ctrl + d ig )
*/
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

/*server*/
#include <arpa/inet.h>
#include <errno.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#define BUF_SIZE 64
#define PORT 8000
#define LISTEN_BACKLOG 32

#define handle_error(msg)                                                                          \
  do {                                                                                             \
    perror(msg);                                                                                   \
    exit(EXIT_FAILURE);                                                                            \
  } while (0)

// Shared counters for: total # messages, and counter of clients (used for
// assigning client IDs)
int total_message_count = 0;
int client_id_counter = 1;

// Mutexs to protect above global state.
pthread_mutex_t count_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t client_id_mutex = PTHREAD_MUTEX_INITIALIZER;

struct client_info {
  int cfd; /* client file descriptor and client id ig ?*/
  int client_id;
};

void *handle_client(void *arg) {
  struct client_info *client = (struct client_info *)arg;
  int cfd = client->cfd;
  int client_id = client->client_id;
  /* printf("Client file descriptor/socket is: %d\n Client id is: %d\n", cfd, client_id); */
  /*  TODO: print the message received from client */
  printf("New client created! ID %d on scoket FD %d\n", client_id, cfd);
  for (;;) {
    // char buf[BUF_SIZE];
    char buf[BUF_SIZE + 1];
    int size_read = read(cfd, buf, BUF_SIZE);
    if (size_read > 0) {
      buf[BUF_SIZE] = '\0';
      // write()
      // TODO: increase total_message_count per message

      // char temp[BUF_SIZE + size_read];
      // char *temp = malloc(BUF_SIZE + size_read);
      char *temp = malloc(BUF_SIZE + size_read + 2);
      pthread_mutex_lock(&count_mutex);
      total_message_count++;
      int temp_count = total_message_count;
      pthread_mutex_unlock(&count_mutex);
      int retVal = snprintf(temp, BUF_SIZE, "Msg #\t%d; Client ID %d: ", temp_count, client_id);

      if (retVal < 0) {
        handle_error("snprintf");
      } else {
        free(temp);
        temp = malloc(retVal + 1);
        int retVal2 =
            snprintf(temp, retVal + 1, "Msg #\t%d; Client ID %d: ", temp_count, client_id);
        if (retVal2 != retVal) {
          handle_error("huh retVal");
        }
        temp[retVal] = '\0';
      }
      if (write(STDOUT_FILENO, temp, retVal) == -1) {
        handle_error("write");
      }
      if (write(STDOUT_FILENO, buf, size_read) == -1) {
        handle_error("write 2");
      }
      free(temp);
    } else {
      printf("Ending thread for client %d\n", client_id);
      break;
    }
  }
  close(cfd);
  client->cfd = 0;
  client->client_id = 0;
  free(client);

  return NULL;
}

int main() {
  struct sockaddr_in addr;
  int sfd;

  sfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sfd == -1) {
    handle_error("socket");
  }

  memset(&addr, 0, sizeof(struct sockaddr_in));
  addr.sin_family = AF_INET;
  addr.sin_port = htons(PORT);
  addr.sin_addr.s_addr = htonl(INADDR_ANY);

  if (bind(sfd, (struct sockaddr *)&addr, sizeof(struct sockaddr_in)) == -1) {
    handle_error("bind");
  }

  if (listen(sfd, LISTEN_BACKLOG) == -1) {
    handle_error("listen");
  }
  // int addrlen = sizeof(struct sockaddr_in);
  int recv_fd = 0;
  for (;;) {
    recv_fd = accept(sfd, NULL, NULL);
    if (recv_fd == -1) {
      handle_error("accept");
    }
    struct client_info *temp = malloc(sizeof(struct client_info));
    pthread_mutex_lock(&client_id_mutex);
    temp->client_id = client_id_counter;
    client_id_counter++;
    pthread_mutex_unlock(&client_id_mutex);
    temp->cfd = recv_fd;
    recv_fd = 0;

    /* TODO: create a new thread when a new connection is encountered */
    pthread_t a_i;

    void *arg = (void *)temp;
    // handle_client(arg);
    /* TODO: call handle_client() when launching a new thread, and provide client_info */
    /*printf("Trying to initialise thread.\n");*/
    int initialiseThread = pthread_create(&a_i, NULL, (void *)(&handle_client), arg);
    if (initialiseThread != 0) {
      handle_error("thread");
    }
    int detachThread = pthread_detach(initialiseThread);
    /* printf("DetachThread is: %d\n", detachThread);*/
#if 0
    if (detachThread != 0) {
      handle_error("detach");
    }
#endif
  }

  if (close(sfd) == -1) {
    handle_error("close");
  }

  return 0;
}
