#ifndef CLIENT_H
#define CLIENT_H

struct client;

/**
 * \brief Initializes the client structure asigning a file descriptor to it
 */
int client_init(struct client *);

/**
 * \brief Connects the client structure to the specified IP and port
 *
 * \param client the client structure to connect
 * \param ip the server IP to connect to
 * \param port the server port to connect to
 */
int client_connect(struct client *, const char *, int);

/**
 * \brief Send data to the server connected to
 *
 * \param client the client structure from which to send the data
 * \param data the data to send
 */
int client_send(struct client *, const char *);

/**
 * \breif Receive data from the connection made with the client structure
 *
 * Blocks the program on a recv until some data is received
 *
 * \pram client the client from which to receive data
 */
char* client_recv(struct client *);

#endif // CLIENT_H
