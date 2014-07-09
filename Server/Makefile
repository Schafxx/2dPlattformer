CC = gcc
COMMON_C_FLAGS = -Wall -std=c99 -g
BASE = /home/r0p/coding/projects/netPlay/CSERVER
DEBUG = -g

server.o: server.h server.c
	$(CC) $(COMMON_C_FLAGS) -c -o server.o server.c
message.o: message.h message.c
	$(CC) $(COMMON_C_FLAGS) -c -o message.o message.c
ui_ncurses.o: UI_ncurese.h UI_ncurese.c
	$(CC) $(COMMON_C_FLAGS) -c -o UI_ncurses.o UI_ncurese.c

main:
	$(CC) $(COMMON_C_FLAGS) -o chatserv message.o server.o UI_ncurses.o main.c -lncurses

clean:
	rm -f *.o

all:
	make clean
	make server.o
	make message.o
	make UI_ncurses.o
	make main