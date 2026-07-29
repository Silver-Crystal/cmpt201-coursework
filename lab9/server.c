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
