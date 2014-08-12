#include "server.h"

// ONLY TESTING SERVER .... real server will be implemented later

int log_server()
{
	int logp_pid = fork();
	if(logp_pid<0)	// FEHLER
		writeInLog("Fehler bei fork()ing log-reader\n");
	else if(logp_pid>0) // parent
	{
		/*if(waitpid(logp_pid,NULL,WNOHANG) != logp_pid)
		{
			writeInLog("ERROR: Waiting for log child\n");
			return 0;
		}
		else*/
		return logp_pid;
	}
	else	// this process
	{
		while(1)
			sleep(2);
	}
	return 0;
}


int chat_server()
{
	int chatp_pid = fork();
	if(chatp_pid<0)	// Fehler
		writeInLog("Fehler bei fork()ing chat-server\n");
	else if(chatp_pid>0)	// parent
	{
		//return chatp_pid;
		exit(EXIT_FAILURE);
	}
	else
	{
		int chatSocket;
		chatSocket = createSocket();

		destroySocket(chatSocket);
	}
	return 0;
}

int createSocket()
{
	int sockID = 0;
	sockID = socket(PF_INET,SOCK_STREAM,0);
	if(sockID < 0)
		writeInLog("Error: %s\n",strerror(errno));
	else
		writeInLog("Socket created\n");
	return sockID;
}

void destroySocket(int sockID)
{
	if(close(sockID) < 0)
		writeInLog("Error: %s\n",strerror(errno));
	else
		writeInLog("Socket closed .. \n");
}