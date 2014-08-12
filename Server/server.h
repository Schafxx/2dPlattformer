#ifndef SERVER_H
#define SERVER_H

#include "message.h"
#include "UI_ncurses.h"

#include <sys/socket.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

#include <unistd.h>
#include <arpa/inet.h>
#include <strings.h>

#include <errno.h>

#include <pthread.h>

#include <signal.h>

#define MAXPENDING 1
#define RCVBUFFSIZE 100

int log_server();

int chat_server();

int createSocket();
void destroySocket(int);


#endif /* SERVER_H */