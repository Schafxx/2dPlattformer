#ifndef UI_NCURSES_H
#define UI_NCURSES_H

#include <ncurses.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <limits.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <time.h>
#include <signal.h>

#include "server.h"

#define MAIN 0
#define CONSOLE 1
#define LOG 2
#define CHAT 3

struct tm *tmnow;

void init_ncurses();

void destroyAndClear();

void init_process_win();
void update_process_win();

void console();	// the console process

void writeInLog(const char*, ...);
void readLog();

#endif /* UI_NCURSES_H */