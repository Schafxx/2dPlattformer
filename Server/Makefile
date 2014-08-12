CC = gcc
COMMON_C_FLAGS = -Wall -std=gnu99 -g
BASE = /home/r0p/coding/projects/netPlay/CSERVER
DEBUG = -g

server.o: server.h server.c
	$(CC) $(COMMON_C_FLAGS) -c -o server.o server.c
message.o: message.h message.c
	$(CC) $(COMMON_C_FLAGS) -c -o message.o message.c
UI_ncurses.o: UI_ncurses.h UI_ncurses.c
	$(CC) $(COMMON_C_FLAGS) -c -o UI_ncurses.o UI_ncurses.c

chat_daemon.o: chat_daemon.h chat_daemon.c
	$(CC) $(COMMON_C_FLAGS) -c -o chat_daemon.o chat_daemon.c

chat_daemon:
	$(CC) $(COMMON_C_FLAGS) -o chat_daemon chat_daemon.o message.o -pthread

main:
	$(CC) $(COMMON_C_FLAGS) -o chatserv message.o server.o UI_ncurses.o main.c -lncurses

clean:
	rm -f *.o

clean_daemon:
	rm -f chat_daemon.o
	rm -f message.o
	rm -f chat_daemon
	rm -f core

all:
	make clean
	make server.o
	make message.o
	make UI_ncurses.o
	make main

daemon:
	make clean_daemon
	make chat_daemon.o
	make message.o
	make chat_daemon