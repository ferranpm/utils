#ifndef CLIENT_H
#define CLIENT_H

struct client;

int client_init(struct Client *);
int client_connect(struct Client *, const char *, int);
int client_send(struct Client *, const char *);
char* client_recv(struct Client *);

#endif // CLIENT_H
