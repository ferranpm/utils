#include "../client.h"
#include "../server.h"
#include <string.h>
#include <pthread.h>
#include <stdio.h>

#define SERVER_PORT 4321

void manage_connection(struct server *server, int fd) {
    char *buff = server_recv(server, fd);
    server_send(server, fd, buff);
}

void *server_routine(void *arg) {
    struct server *server = (struct server *)arg;
    server_accept(server);
    return NULL;
}

int clientserver() {
    struct server *server = server_new();

    if (server_init(server) != 0) {
        perror("server_init");
        return -1;
    }

    server_set_callback(server, manage_connection);

    if (server_bind(server, SERVER_PORT) != 0) {
        perror("server_bind");
        return -1;
    }

    pthread_t thread;
    if (pthread_create(&thread, NULL, server_routine, server) != 0) {
        perror("pthread_create");
        return -1;
    }

    struct client *client = client_new();

    if (client_init(client) != 0) {
        perror("client_init");
        return -1;
    }
    int connected = 0;
    while (client_connect(client, "127.0.0.1", SERVER_PORT) != 0 && connected < 10) connected++;
    if (connected >= 10)  {
        perror("client_connect");
        return -1;
    }

    client_send(client, "hello");
    char *buff = client_recv(client);

    return strcmp(buff, "hello");
}
