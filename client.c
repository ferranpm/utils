#include "client.h"

#include <arpa/inet.h>
#include <netinet/ip.h>
#include <sys/socket.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

struct client {
    int socket;
};

int client_init(struct client *c) {
    return (c->socket = socket(AF_INET, SOCK_STREAM, 0)) <= 0;
}

int client_connect(struct client *c, const char *ip, int port) {
    struct sockaddr_in serv_addr;
    memset(&serv_addr, '0', sizeof(serv_addr));

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port);

    if (inet_pton(AF_INET, ip, &serv_addr.sin_addr) <= 0) return 1;

    return connect(c->socket, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
}

int client_send(struct client *c, const char *msg) {
    return send(c->socket, msg, strlen(msg), 0);
}

char* client_recv(struct client *c) {
    int buff_size = sizeof(char) * 1024;
    char *buff = malloc(buff_size);
    memset(buff, 0, buff_size);
    if (recv(c->socket, buff, buff_size, 0) <= 0) return "\0";
    return buff;
}

