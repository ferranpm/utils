#ifndef SERVER_H
#define SERVER_H

struct Server {
    void (*callback)(struct Server *, int);
    int socket;
};

int server_init(struct Server *);
int server_bind(struct Server *, int);
void server_set_callback(struct Server *, void (*callback)(struct Server *, int));
void server_accept(struct Server *);
int server_send(struct Server *, int, const char *);
char* server_recv(struct Server *, int);

#endif // SERVER_H
