#include <stdio.h>
#include <string.h>

#include "UI_ncurses.h"
#include "server.h"

int main(int argc, char** argv)
{
	if(argc>1)
	{
		init_ncurses();
		return 0;
	}

	struct container m;
	struct container n;
	char frame[200];

	char name[10];
	char nachricht[180];
	printf("Name: ");
	fgets(name,10,stdin);
	/* Remove trailing newline, if there. */
    if ((strlen(name)>0) && (name[strlen (name) - 1] == '\n'))
        name[strlen (name) - 1] = '\0';
	printf("Nachricht: ");

	fgets(nachricht,180,stdin);
	/* Remove trailing newline, if there. */
    if ((strlen(nachricht)>0) && (nachricht[strlen (nachricht) - 1] == '\n'))
        nachricht[strlen (nachricht) - 1] = '\0';
	//printf("%s",nachricht);

	makeMessage(name,nachricht,&m);

	printf("%s: %s\n",m.sender,m.body);

	//printf("%lu\n",sizeof(frame));
	serialize(frame,&m);
	//clearOutNullBytes(frame,200);
	printf("Using serialize: %s\n", frame);
	deserialize(frame,&n);
	printf("After deserialization: %s: %s\n",n.sender,n.body);
	return 0;
}