#include "server.h"



void printFrame(char* frame,int size)
{
	for(int i = 0;i<size;i++)
	{
		printf("i: %d %c - %x\n",i,frame[i],frame[i]);
	}
}

void serialize(struct container* input, char *output)
{
	for(int i = 0 ; i < TOTAL_SIZE; i++)
	{
		if(i < SENDER_SIZE)
			output[i] = input->sender[i];
		else if(i < SENDER_SIZE + TAG_SIZE)
			output[i] = input->tag[i - SENDER_SIZE];
		else
			output[i] = input->body[i - SENDER_SIZE-TAG_SIZE];
	}
}

void deserialize(char *input, struct container* output)
{
	for(int i = 0; i < TOTAL_SIZE; i++)
	{
		if(i < SENDER_SIZE)
			output->sender[i] = input[i];
		else if(i < SENDER_SIZE + TAG_SIZE)
			output->tag[i - SENDER_SIZE] = input[i];
		else
			output->body[i - SENDER_SIZE - TAG_SIZE] = input[i];
	}
}