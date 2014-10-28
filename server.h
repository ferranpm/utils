#ifndef SERVER_H
#define SERVER_H

struct server;

int server_init(struct server *);
int server_bind(struct server *, int);
void server_set_callback(struct server *, void (*callback)(struct server *, int));
void server_accept(struct server *);
int server_send(struct server *, int, const char *);
char* server_recv(struct server *, int);

#endif // SERVER_H
