#include "UI_ncurses.h"

WINDOW *console_win;
WINDOW *log_win;
WINDOW *process_win;
WINDOW *client_win;

int processes[4];


void init_ncurses()
{
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
	/*client_win = newwin(tot_height-3,tot_width/3,0,tot_width - tot_width/3);
	box(client_win,0,0);
	wrefresh(client_win);
	*/
	process_win = newwin(10,tot_width/3,0,tot_width - tot_width/3);
	box(process_win,0,0);
	wrefresh(process_win);
	client_win = newwin(tot_height-13,tot_width/3,10,tot_width - tot_width/3);
	box(client_win,0,0);
	wrefresh(client_win);

	init_process_win();

	wmove(console_win,1,1);
	while(1)
	{
		update_process_win();

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
			processes[LOG] = log_server();
			if(processes[LOG]>0)
			{
				writeInLog("Log PID: %d\n", processes[LOG]);
				//update_process_win();

				processes[CHAT] = chat_server();
				if(processes[CHAT]>0)
				{
					writeInLog("Chat PID: %d\n", processes[CHAT]);
					//update_process_win();
				}
				else if(processes[CHAT]==0)
				{
					writeInLog("ChatServer stopped\n");
					processes[3] = 0;				// wont change anything: its the processes[] in child, that gets changed
					return;
				}
			}
			else if(processes[LOG]==0)
			{
				writeInLog("Log reading stopped\n");
				processes[2] = 0;					// wont change anything: its the processes[] in child, that gets changed
				return;
			}
			
		}
		
		else if(strcmp(console_input, "stop")==0)
		{
			if(kill(processes[LOG], 9)==0)
			{
				writeInLog("LogServer killed\n");
				processes[2] = 0;
			}
			else
			{
				writeInLog("killing of LogServer failed\n");
			}
			
		}

		fflush(stdin);
		//console_input[0] = '\0';		// clear it: setting first byte to NULL
		void *ptr;
		ptr = (char*) console_input;
		memset(ptr,0,sizeof(console_input));

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

void init_processes()	// set processes array to 0
{
	void *mem;
	mem = (char*) processes;
	memset(mem,0,sizeof(processes));
	processes[0] = getpid();
}

void init_process_win()	// print initial stuff on process_win
{
	init_processes();

	char thisp_line[6];
	sprintf(thisp_line,"THIS:      %d",processes[0]);

	mvwprintw(process_win,1,1,thisp_line);
	mvwprintw(process_win,2,1,"CONSOLE P: ");
	mvwprintw(process_win,3,1,"LOGP:      ");
	mvwprintw(process_win,4,1,"CHATP:     ");
	box(process_win,0,0);
	wrefresh(process_win);
}

void update_process_win()		// update process_win, if something changes in processes array
{
	//werase(process_win);

	char output[3][6];
	void * mem;
	mem = (char*) output;
	memset(mem,0,sizeof(output));

	if(processes[1]!=0)
	{
		wmove(process_win,2,12);					// set curser position
		wclrtoeol(process_win);						// and clear to end of line
		sprintf(output[0],"%d",processes[1]);
		mvwprintw(process_win,2,12,output[0]);
	}
	else
	{
		mvwprintw(process_win,2,12,"NOT running");
	}
	if(processes[2]!=0)
	{
		wmove(process_win,3,12);
		wclrtoeol(process_win);
		sprintf(output[1],"%d",processes[2]);
		mvwprintw(process_win,3,12,output[1]);
	}
	else
	{
		mvwprintw(process_win,3,12,"NOT running");
	}
	if(processes[3]!=0)
	{
		wmove(process_win,4,12);
		wclrtoeol(process_win);
		sprintf(output[2],"%d",processes[3]);
		mvwprintw(process_win,4,12,output[2]);
	}
	else
	{
		mvwprintw(process_win,4,12,"NOT running");
	}

	box(process_win,0,0);
	wrefresh(process_win);
}


int console()
{
	//int status;

	int console_pid = fork();
	if(console_pid<0)
	{
		writeInLog("Fehler bei fork(ing) console\n");
	}
	else if(console_pid>0)
	{
		//waitpid(pid,NULL)
	}
	return 0;
}

void writeInLog(const char *log_entry, ...)
{
	time_t tnow;
	va_list arg;
	FILE * p;
	p = fopen("main.log","a");
	char buffer[300];

	time(&tnow);
	tmnow = localtime(&tnow);
	strftime(buffer,300,"* %T: ",tmnow);
	fprintf(p, buffer);
	va_start(arg,log_entry);
	vfprintf(p,log_entry,arg);
	va_end(arg);

	fclose(p);
}

void readLog()
{


	/*int size = 100;
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
	
	
	box(log_win,0,0);
	wrefresh(log_win);

	fclose(file);
	*/
}