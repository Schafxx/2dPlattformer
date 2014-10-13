#ifndef MESSAGE_H
#define MESSAGE_H

#include <stdio.h>
#include <string.h>

#define SENDER_SIZE 10
#define TAG_SIZE 10
#define BODY_SIZE 100
#define TOTAL_SIZE 120


struct container
{
	char sender[10];
	char tag[10];
	char body[100];
};


void printFrame(char*,int);
void serialize(struct container*, char*);
void deserialize(char*, struct container*);



#endif /* MESSAGE_H */