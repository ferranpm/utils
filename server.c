#include "server.h"

#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/ip.h>
#include <string.h>

int server_init(struct Server *s) {
    s->socket = socket(AF_INET, SOCK_STREAM, 0);
    return s->socket >= 0;
}

int server_bind(struct Server *s, int port) {
    struct sockaddr_in serv_addr;

    memset(&serv_addr, 0, sizeof(serv_addr));

    serv_addr.sin_family      = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port        = htons(port);

    if (bind(s->socket, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) != 0) return 0;

    return listen(s->socket, 10) == 0;
}

void server_set_callback(struct Server *s, void (*callback)(struct Server *, int)) {
    s->callback = callback;
}

void server_accept(struct Server *s) {
    int fd = accept(s->socket, (struct sockaddr*)NULL, NULL);
    s->callback(s, fd);
}

int server_send(struct Server *s, int fd, const char *msg) {
    return send(fd, msg, strlen(msg), 0);
}

char* server_recv(struct Server *s, int fd) {
    int buff_size = sizeof(char) * 1024;
    char *buff = malloc(buff_size);
    memset(buff, 0, buff_size);
    if (read(fd, buff, buff_size) <= 0) return "\0";
    return buff;
}

