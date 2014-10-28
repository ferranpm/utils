#ifndef SERVER_H
#define SERVER_H

struct server;

/**
 * \brief Initialize the server structure
 * 
 * \param s the server to initialize
 * \return 0 on success
 */
int server_init(struct server *);

/**
 * \brief Bind the port to the server structure
 *
 * \param s the servert to bind the port to
 * \param port the port to bind
 * \return 0 on success
 */
int server_bind(struct server *, int);

/**
 * \brief Set the function to call when a connection to the server is made
 *
 * When the server receives a new connection, a threadd to that callback will be made
 *
 * \param s the server to assign the callback to
 * \param callback the function to call
 */
void server_set_callback(struct server *, void (*callback)(struct server *, int));

/**
 * \brief Blocks the program waiting for a new connection and calls the callback when received
 *
 * \param s the server structure
 */
void server_accept(struct server *);

/**
 * \brief Sends data to the connection made to the specified server and file descriptor
 *
 * \param s the server struccture
 * \param fd the file descriptor to which the data must be sent
 * \param data the data to send
 * \return the number of bytes written
 */
int server_send(struct server *, int, const char *);

/**
 * \brief Receives a message from the specified server and file descriptor
 *
 * \param s the server structure from which to receive the message
 * \param fd the file descriptor that sends the message
 * \return an string containing the received data
 */
char* server_recv(struct server *, int);

#endif // SERVER_H
