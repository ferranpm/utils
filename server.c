#include "server.h"

#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/ip.h>
#include <string.h>
#include <pthread.h>

struct server {
    void (*callback)(struct server *, int);
    int socket;
};

int server_init(struct server *s) {
    return (s->socket = socket(AF_INET, SOCK_STREAM, 0)) <= 0;
}

int server_bind(struct server *s, int port) {
    struct sockaddr_in serv_addr;

    memset(&serv_addr, 0, sizeof(serv_addr));

    serv_addr.sin_family      = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port        = htons(port);

    if (bind(s->socket, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) != 0) return 1;

    return listen(s->socket, 10);
}

void server_set_callback(struct server *s, void (*callback)(struct server *, int)) {
    s->callback = callback;
}

struct callback_params {
    struct server *s;
    int fd;
};

void *call_callback(void *parms) {
    struct callback_params *params = (struct callback_params *)parms;
    params->s->callback(params->s, params->fd);
    return NULL;
}

void server_accept(struct server *s) {
    int fd = accept(s->socket, (struct sockaddr*)NULL, NULL);
    struct callback_params params = {s, fd};
    pthread_t pthread;
    pthread_create(&pthread, NULL, call_callback, &params);
}

int server_send(struct server *s, int fd, const char *msg) {
    return send(fd, msg, strlen(msg), 0);
}

char* server_recv(struct server *s, int fd) {
    int buff_size = sizeof(char) * 1024;
    char *buff = malloc(buff_size);
    memset(buff, 0, buff_size);
    if (recv(fd, buff, buff_size, 0) <= 0) return "\0";
    return buff;
}

