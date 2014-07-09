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

struct tm *tmnow;

void init_ncurses();

void destroyAndClear();

void writeInLog(const char*, ...);
void readLog();

#endif /* UI_NCURSES_H */