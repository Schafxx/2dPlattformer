#include <stdio.h>
#include <string.h>

#include "server.h"

#define SENDER_SIZE 10
#define TAG_SIZE 10
#define BODY_SIZE 180

int makeMessage(char* sender, char* body, struct container* m)
{
	if(strlen(sender)>SENDER_SIZE || strlen(body)>BODY_SIZE)
		return -1;
	strncpy(m->sender, sender,SENDER_SIZE);
	strncpy(m->body, body,BODY_SIZE);
	return 0;
}

void printFrame(char* frame,int size)
{
	for(int i = 0;i<size;i++)
	{
		printf("i: %d %c - %x\n",i,frame[i],frame[i]);
	}
}

void serialize(char *frame, struct container* m)
{
	//printf("sender: %s, tag: %s, body: %s\n",m->sender,m->tag,m->body);
	memcpy(frame,m->sender,SENDER_SIZE);
	memcpy(frame+SENDER_SIZE,m->tag,TAG_SIZE);
	memcpy(frame+SENDER_SIZE+TAG_SIZE,m->body,BODY_SIZE);
}

void deserialize(char * frame, struct container* m)
{
	memcpy(m->sender,frame,SENDER_SIZE);
	memcpy(m->tag,frame+SENDER_SIZE,TAG_SIZE);
	memcpy(m->body,frame+SENDER_SIZE+TAG_SIZE,BODY_SIZE);
}