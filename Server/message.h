#ifndef MESSAGE_H
#define MESSAGE_H

struct container
{
	char sender[10];
	char tag[10];
	char body[180];
};

int makeMessage(char*,char*, struct container*);

void printFrame(char*,int);
void serialize(char*, struct container*);
void deserialize(char*, struct container*);



#endif /* MESSAGE_H */