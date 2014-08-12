#ifndef CHAT_DAEMON_H
#define CHAT_DAEMON_H

#include <unistd.h>
#include <sys/types.h>
#include <pthread.h>
#include <syslog.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <arpa/inet.h>
#include <signal.h>
#include <errno.h>
#include <string.h>

#include <stdlib.h>
#include <stdio.h>

#include "message.h"

#define SERVERPORT 11000
#define BACKLOG	3

#define MAXTHREADS 4

void start_daemon(const char*, int);

int CreateSocket(int);
void CloseSocket(int, int);

void Bind(int, const struct sockaddr*, socklen_t, int);
void Listen(int, int, int);

int Pthread_create(pthread_t *, const pthread_attr_t *, void*(*) (void *), void *arg, int);

void *connection_handler(void*);

int saveFD(int*, int);
int delClientFD(int*, int);

void sendToAllClients(int*, char*, void*);


#endif // CHAT_DAEMON_H