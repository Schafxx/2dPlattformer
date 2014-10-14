#include "chat_daemon.h"

int clients[10];

int main()
{

	memset(clients,'\0', 10);

	int listenFD, clientFD;
	struct sockaddr_in cliaddr, servaddr;
	socklen_t clilen=sizeof(struct sockaddr);

	printf("Daemon is here\n");

	/* One has to specify LOG_LOCAL0 in /etc/ before seeing output */
	//start_daemon("chat_daemon", LOG_LOCAL0);	
	openlog("chat_daemon", LOG_PID | LOG_CONS | LOG_NDELAY, LOG_LOCAL0);

	syslog(LOG_NOTICE, "Chat_Daemon start\n");

	listenFD = CreateSocket(LOG_NOTICE);

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(SERVERPORT);

	Bind(listenFD,(void *) &servaddr,sizeof(servaddr),LOG_NOTICE);
	Listen(listenFD,BACKLOG,LOG_NOTICE);

	while( (clientFD = accept(listenFD,(void*) &cliaddr, &clilen)) )
	{
		if(clientFD < 0)
		{
			syslog(LOG_NOTICE, "Error: %s\n",strerror(errno));
			continue;
		}

		saveFD(clients,clientFD);

		char clientIP[INET_ADDRSTRLEN];
		syslog(LOG_NOTICE, "connection from %s:%d\n", inet_ntop(AF_INET, &cliaddr.sin_addr,clientIP,sizeof(clientIP)), ntohs(cliaddr.sin_port));

		pthread_t connection_thread;

		//clientFDPointer = malloc(1);
		//*clientFDPointer = clientFD;
		if(Pthread_create(&connection_thread, NULL, connection_handler, &clientFD, LOG_NOTICE)<0)
			continue;

		//syslog(LOG_NOTICE, "Before sleep\n");
		//sleep(2);
		//syslog(LOG_NOTICE, "After sleep\n");
		//break;
	}
	syslog(LOG_NOTICE,"Out of Accept Loop\n");
	//sleep(10);


	CloseSocket(listenFD, LOG_NOTICE);

	syslog(LOG_NOTICE, "Chat_Daemon end\n");

	closelog();
	exit(EXIT_SUCCESS);
}


void start_daemon(const char* logname, int facility)
{
	int i;
	pid_t pid;

	if((pid = fork()) != 0)
		exit(EXIT_FAILURE);
	if(setsid() < 0)
	{
		printf("%s kann nicht Sessionführer werden\n", logname);
		exit(EXIT_FAILURE);
	}
	signal(SIGHUP, SIG_IGN);

	if(( pid = fork()) != 0)
		exit(EXIT_FAILURE);

	chdir("/");
	umask(0);
	for( i = sysconf(_SC_OPEN_MAX);i>0;i--)
	{
		close(i);
	}
	openlog(logname, LOG_PID | LOG_CONS | LOG_NDELAY, facility);
}

int CreateSocket(int facility)
{
	int sockID = 0;
	sockID = socket(PF_INET,SOCK_STREAM,0);
	if(sockID < 0)
	{
		syslog(facility, "Error: %s\n",strerror(errno));
		exit(EXIT_FAILURE);
	}
	else
		syslog(facility, "Socket created\n");
	return sockID;
}

void CloseSocket(int sockID, int facility)
{
	if(close(sockID) < 0)
	{
		syslog(facility, "Error: %s\n",strerror(errno));
		exit(EXIT_FAILURE);
	}
	else
		syslog(facility, "Socket closed .. \n");
}

void Bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen, int facility)
{
	if(bind(sockfd,addr,addrlen)!=0)
	{
		syslog(facility, "Error: %s\n",strerror(errno));
		exit(EXIT_FAILURE);
	}
	else
		syslog(facility, "Bind successful\n");
}

void Listen(int sockfd, int backlog, int facility)
{
	if(listen(sockfd,backlog)!=0)
	{
		syslog(facility, "Error: %s\n",strerror(errno));
		exit(EXIT_FAILURE);
	}
	else
		syslog(facility, "Listening started\n");
}

int Pthread_create(pthread_t *thread, const pthread_attr_t *attr, void*(*start_routine) (void *), void *arg, int facility)
{
	if(pthread_create(thread, attr, start_routine, arg) < 0)
	{
		syslog(facility, "Error: %s\n",strerror(errno));
		return -1;
	}
	else
		syslog(facility, "Thread created for last connection\n");
	return 0;
}

void *connection_handler(void *clientFD)
{
	//struct file *fptr;
	//fptr = (struct file *) clientFD;

	pthread_detach(pthread_self());
	syslog(LOG_NOTICE, "Connection_handler starts here(FD:%d)\n",*(int*) clientFD);

	char out[120];
	memset(out,'\0',120);

	char client_message[120];
	memset(client_message, '\0',120);
	int readsize;

	struct container message;
	strncpy(message.sender, "SERVER",10);
	strncpy(message.tag, "0000000000",10);
	strncpy(message.body, "Welcome to 2D Plattformer!",26);
	serialize(&message,out);
	//syslog(LOG_NOTICE, "OUT: %s",out);


	write(*(int*)clientFD,out,sizeof(out));

	while( (readsize = recv(*(int*)clientFD,client_message,120,0))>0)
	{
		deserialize(client_message, &message);
		/*printf("RAW: ");
		for(int i = 0; i <sizeof(client_message);i++)
		{
			if(client_message[i] == '\0')
				printf("0");
			else
				printf("%x|",client_message[i]);
		}
		printf("\n");
		*/
		syslog(LOG_NOTICE, "Bytes: %d, From: %s Message: %s\n",readsize, message.sender,message.body);
		sendToAllClients(clients, client_message,clientFD);
	}
	if(readsize==0)
		syslog(LOG_NOTICE, "client with fd: %d disconnected.\n",*(int*)clientFD);
	else if(readsize==-1)
		syslog(LOG_NOTICE, "recv failed: %s\n",strerror(errno));

	CloseSocket(*(int*)clientFD,LOG_NOTICE);

	delClientFD(clients,*(int*)clientFD);
	syslog(LOG_NOTICE, "END of connection_handler\n");
	//exit(EXIT_SUCCESS);
	//pthread_exit(NULL);
	//return 0;
	
	return NULL;
	//pthread_exit(NULL);
}

int saveFD(int *clients, int fd)
{
	for(int i = 0;i< sizeof(clients);i++)
	{
		if(clients[i] ==  '\0')
		{
			clients[i] = fd;
			return i;
		}
	}
	return -1;
}
int delClientFD(int *clients, int fd)
{
	for(int i = 0;i< sizeof(clients);i++)
	{
		if(clients[i] ==  fd)
		{
			clients[i] = '\0';
			return i;
		}
	}
	return -1;
}

void sendToAllClients(int *clients, char* message,void* thisFD)
{
	for(int i = 0;i<sizeof(clients);i++)
	{
		if(clients[i] == *(int*)thisFD)
			continue;
		printf("FD: %d", clients[i]);
		write(*(int*)thisFD,message,sizeof(message));

	}
}