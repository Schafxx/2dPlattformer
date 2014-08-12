#include <stdio.h>
#include <string.h>

#include "UI_ncurses.h"
#include "server.h"

int main(int argc, char** argv)
{
	if(argc>1)
	{
		return 0;
	}
	else
		init_ncurses();
	return 0;
}