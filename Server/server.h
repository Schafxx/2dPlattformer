#ifndef SERVER_H
#define SERVER_H

#include "message.h"

#include <sys/socket.h>
#include <netinet/in.h>

void server();

void createSocket();
void destroySocket();


#endif /* SERVER_H */