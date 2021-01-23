#include<time.h>
#include<stdio.h>
#include<error.h>
#include<errno.h>
#include<fcntl.h>
#include<netdb.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<signal.h>
#include<sys/sem.h>
#include<sys/wait.h>
#include<sys/time.h>
#include<sys/stat.h>
#include<arpa/inet.h>
#include<sys/types.h>
#include<sys/socket.h>


char IP[100];
int PID;


int PORTS[1024], CHILD_PIDS[1024], PORT, SOCKS[1024], COUNT;
char SERVICES [1024][10];





void populate()	// To get all service names and store in variablle " SERVICES "  (see main())
{
	struct servent *s;

	COUNT=0;
	for(int i=1; i<=1024; i++)
	{
		s= getservbyport(htons(i), "tcp" );
		if(s==NULL)
			continue;

		else
		{
			PORTS[COUNT] = i;
			strcpy(SERVICES[COUNT],s->s_name);
			COUNT = COUNT + 1;
		}

	}

}


void end(int SIG)    // Signal handler for parent - SIGNAL : SIGINT called by user to terminate program
{
	if(getpid()!=PID)
	{	
		kill(getppid(),SIGINT);
		return;
	}
	printf("\nCOMMAND: THANK YOU\n\n");
	for(int aa=0; aa<1024; aa++)
		kill(CHILD_PIDS[aa],SIGUSR1);
}

void closer(int SIG) // Signal handler for child - SIGNAL : SIGUSR1 called by parent to make child close port and exit
{
	close(SOCKS[PORT-1]);
	exit(0);
}




void lookup_webpage(char * webpage)
{
	struct addrinfo hints, *result;
	void *ptr;
	printf("DNS:\t Fetching data..\n");

	memset (&hints, 0, sizeof (hints));
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags |= AI_CANONNAME;
	
	if(getaddrinfo (webpage, NULL , &hints , &result)!=0)					// Get data and store in variable " result "
	{ printf("DNS:\t Domain does not exist\n"); return; }
  	
	
	printf("DNS:\t Domain exists\n");

 	while (result)										// Loop through all IPs
    	{

	switch (result->ai_family)								// Identify if IPv4 or IPv6
        {
         case AF_INET:
          	ptr  = &((struct sockaddr_in *) result->ai_addr)->sin_addr;
          	break;
         case AF_INET6:
         	 ptr  = &((struct sockaddr_in6 *) result->ai_addr)->sin6_addr;
          	 break;
        }
        inet_ntop (result->ai_family, ptr,  IP ,  100);
	
	printf ("DNS:\t IPv%d Address: %s\n", result->ai_family == PF_INET6 ? 6 : 4, IP);


	for( int c=1; c<=COUNT; c++)
	{


		for(int x=0; (x< 100)&&(c<=COUNT); x++, c++)					// Conncet only 100 ports at a time
		{


		PORT= PORTS[c-1];
		int sock;
		
		if(result-> ai_family == PF_INET6)
			sock = socket(PF_INET6, SOCK_STREAM, 0);

		else
			sock = socket(PF_INET , SOCK_STREAM, 0);
		
		SOCKS[c-1] = sock;

		
		CHILD_PIDS[c-1]= fork();							// FORK () and assign work to children to connect to ports instead of 
		if(CHILD_PIDS[c-1]==0)								// doing iterativelyas that takes a long time for unresponsive ports
		{
			
			if(sock<0) 
			{
				printf("SOCKET: Error at port %d\n", PORT);
				perror("Reason");
				exit(0);
			}


			if(result-> ai_family == PF_INET6)
				((struct sockaddr_in6 *) result->ai_addr)->sin6_port = htons(PORT);

			else
				((struct sockaddr_in *) result->ai_addr)->sin_port = htons(PORT);
			
			int conn = connect(sock, result->ai_addr, result->ai_addrlen);
			
			if(conn==0)
				printf("CONNECT: Open   -  PORT <-> %d   -   SERVICE <-> %s\n", PORTS[c-1], SERVICES[c-1]);
		
			exit(0);
		}
		}

	sleep(10);										// Give MAXIMUM 10 seconds for connect to suceed, then move on to next 100 ports			
	
	for(int i=0; i<1024; i++)
		if(CHILD_PIDS[i]!=0)
		{
			kill(CHILD_PIDS[i], SIGUSR1);
			close(SOCKS[i-1]);
		}

	}	
        
	result = result->ai_next;								// Do for all the IPs (IPv4 and IPv6 also) iteratively
 
    }
  
	free(result);
  	return;


}




void getweb( char* pages, char* webpage)							// Get the next webpage (see main() )
{
	int i;

	for(i=0; (pages[i]!='\0')&&(pages[i]!='\n'); i++) 
		webpage[i]=pages[i];
	
	webpage[i]='\0';
}




void domainparse(char * webpage)								// Parser (see main() )
{
	int c=0;
	
	for(int i=0, check=0; i<strlen(webpage); i++)
	{
		if((check==1)&&(webpage[i]=='/'))
		{ 
			webpage[i] = '\0'; 
			c=1; 
			break; 
		}

		if((webpage[i-1]=='/')&&(webpage[i-2]=='/'))
			check=1;
	}

	
	for(int i=0; (i<strlen(webpage))&&(c!=1); i++) 
		if(webpage[i]=='/') 
			webpage[i]='\0';
	

	c=0;
	for(int i=2; i<strlen(webpage); i++)
		if((webpage[i-1]=='/')&&(webpage[i-2]=='/')) 
			c=i;

	if(c==0) 
		return;
	
	for(int i=0; i<strlen(webpage)-c; i++) 
		webpage[i]=webpage[i+c];

	webpage[strlen(webpage)-c]='\0';

}

void main()
{
	PID = getpid();
	signal(SIGUSR1,closer);	
	signal(SIGINT ,end   );	
	populate();										// Find and store ports and service names in " SERVICES " and " PORTS " array

	printf("COMMAND: Opening file....\n");

	int webfile = open("webpages.txt", S_IRUSR | S_IRGRP );					// Open " Webpage.txt "
	
	if(webfile==-1) 
	{
		printf("COMMAND: Error Opening webpages.txt\n");
		perror("COMMAND");
		exit(0);
	}

	else	
		printf("COMMAND: File found and opened\n");

	lseek(webfile,0,SEEK_END);
	int filelen= lseek(webfile,0,SEEK_CUR), i=0;						// Calculate length to store contents of file in a string


	char * webpages = (char *)malloc(2+filelen);
	printf("COMMAND: Total charachters in file are: %d\n",filelen);				
	lseek(webfile,0,SEEK_SET);


	read(webfile,webpages,filelen+2);							// Store contents of file in " webfile " variable
	char webpage[100];

	for( char* pages= webpages ; (pages[0]!=EOF);i++ )
	{
		getweb(pages,webpage);								// Get the next website from " webfile " and store in " webpage " variable
		
		while((*pages!='\n')&&(*pages!='\0'))	
			pages++;
		

		if(*pages=='\0') 
			break;
		
		else 
			pages++;
		
		
		if(strlen(webpage)==0) 
			continue;

		printf("\n--------------------- WEBSITE %d -----------------------\n\n",i+1);
		printf("PARSER:\t Input   -> %s\n",webpage);
		
		domainparse(webpage);								// Parser to remove path and irrelevant part from " webpage " variable
		
		printf("PARSER:\t Result  -> %s\n",webpage);

		lookup_webpage(webpage);							// Function " lookup_webpage " to do all getaddrinfo, DNS, connect calls

	}

	        printf("\n-------------------- SCAN COMPLETE ----------------------\n\n",i+1);

	return;
}
