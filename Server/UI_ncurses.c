#include "UI_ncurses.h"

WINDOW *console_win;
WINDOW *log_win;
WINDOW *client_win;

void init_ncurses()
{
	pid_t server_pid;
	pid_t logp_pid;

	int tot_height, tot_width;

	char console_input[20];

	initscr();
	//raw();
	cbreak();
	keypad(stdscr, TRUE);
	//noecho();

	getmaxyx(stdscr,tot_height,tot_width);
	printw("height: %d - width: %d",tot_height,tot_width);
	refresh();


	// Console stuff: the window/box at bottom
	console_win = newwin(3,tot_width,tot_height-3,0);
	box(console_win,0,0);
	wrefresh(console_win);
	// log stuff: the main central window/box
	log_win = newwin(tot_height-3,tot_width-tot_width/3,0,0);
	box(log_win,0,0);
	scrollok(log_win,TRUE);
	wrefresh(log_win);
	//Client stuff: the window/box right
	client_win = newwin(tot_height-3,tot_width/3,0,tot_width - tot_width/3);
	box(client_win,0,0);
	wrefresh(client_win);

	wmove(console_win,1,1);
	while(1)
	{
		wgetstr(console_win,console_input);
		wmove(console_win,1,1);
		wclrtoeol(console_win);
		box(console_win,0,0);
		wrefresh(console_win);
		if(strcmp(console_input,"q")==0 || strcmp(console_input,"quit")==0)
		{	
			delwin(console_win);
			delwin(log_win);
			destroyAndClear();
			return;
		}
		
		else if(strcmp(console_input, "start server")==0)
		{
			server_pid = fork();
			if(server_pid < 0)	// FEHLER
			{
				writeInLog("Fehler bei fork()ing server\n");
			}
			else if(server_pid>0)	// ELTERN
			{
				if(waitpid(server_pid,NULL,WNOHANG) != 0)
				{
					writeInLog("Error: waitpid()\n");
				}
				writeInLog("Elternprozess(non-blocking): %d\n",getpid());
				//exit(0);
			}
			else // KIND
			{	
				writeInLog("Kindprozess: %d\n",getpid());

				sleep(2);
	
				writeInLog("Kindprozess ende\n");
				exit(0);
			}
			readLog();
		}
		/*
		else if(strcmp(console_input, "stop server")==0)
		{
			
		}*/
		else if(strcmp(console_input, "start log")==0)
		{
			logp_pid = fork();
			if(logp_pid<0)	// FEHLER
				writeInLog("Fehler bei fork()ing log-reader\n");
			else if(server_pid>0)	// ELTERN
			{
				if(waitpid(logp_pid,NULL,WNOHANG) != 0)
					writeInLog("ERROR: waitpid() log-reader\n");
			}
			else
			{
				writeInLog("Start logging:\n");
				readLog();
			}
		}

		wmove(console_win,1,1);
		wclrtoeol(console_win);
		box(console_win,0,0);
		refresh();
	}
}

void destroyAndClear()
{
	endwin();
}

void writeInLog(const char *log_entry, ...)
{
	time_t tnow;
	va_list arg;
	FILE * p;
	p = fopen("main.log","a");
	char buffer[30];

	time(&tnow);
	tmnow = localtime(&tnow);
	strftime(buffer,30,"* %T: ",tmnow);
	fprintf(p, buffer);
	va_start(arg,log_entry);
	vfprintf(p,log_entry,arg);
	va_end(arg);

	fclose(p);
}

void readLog()
{
	int size = 100;
	char line[size];
	FILE * file;
	
	file = fopen("main.log","r");
	if(file==NULL)
		writeInLog("Error: fopen(main.log)");

	int i = 1;
	//lseek(fd,-10,SEEK_END);
	while(fgets(line,size,file))
	{
		mvwprintw(log_win,i,1,line);
		i++;
	}
	//if(i<20)
	//	i=0;
	
	box(log_win,0,0);
	wrefresh(log_win);

	fclose(file);
}