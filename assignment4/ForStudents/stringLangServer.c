/*-------------------------------------------------------------------------*
 *---									---*
 *---		stringLangServer.c			Chadwick Rivera-Crum		---*
 *---									---*
 *---	    This file defines a C program that gets file-sys commands	---*
 *---	from client via a socket, executes those commands in their own	---*
 *---	threads, and returns the corresponding output back to the	---*
 *---	client.								---*
 *---									---*
 *---	----	----	----	----	----	----	----	----	---*
 *---									---*
 *---	Version 1a					Joseph Phillips	---*
 *---									---*
 *-------------------------------------------------------------------------*/

//	Compile with:
//	$ gcc stringLangServer.c -o stringLangServer -lpthread

//---		Header file inclusion					---//

#include	"clientServer.h"
#include	<pthread.h>	// For pthread_create()


//---		Definition of constants:				---//

#define		STD_OKAY_MSG		"Okay"

#define		STD_ERROR_MSG		"Error doing operation"

#define		STD_BYE_MSG		"Good bye!"

#define		THIS_PROGRAM_NAME	"stringLangServer"

const int	ERROR_FD		= -1;


//---		Definition of global vars:				---//

//  PURPOSE:  To be non-zero for as long as this program should run, or '0'
//	otherwise.


//---		Definition of functions:				---//

//  PURPOSE:  To:
//	(1) create a pipe
//	(2) fork() a child process.  This child process will:
//	  (2a) close() its file descriptor to stdout,
// dup2(myPipe[1], STDOUT_FILENO);
//	  (2b) send its output from the pipe to the close stdout file descriptor
//	  (2c) Run the program STRING_LANG_PROGNAME with cPtr on the cmd line
//	  (2d) Send an error message back to the client on file descriptor 'fd'
//		if the execl() failed. using write(FD, string, strLength+1)
//	(3) close()s the output end of pipe, get input from the pipe, put the '\0' char at the end
//	(4) wait() for the child process to end
//	(5) send the input back to the client using file descriptor 'fd'
void		stringLangFile	(int		socketFd,
				 const char*	cPtr
				) //socketFd is from talking with client, cPtr is expression to actually run
{
  //  I.  Application validity check:

  //  II.  Apply string language file:
  //  YOUR CODE HERE
	int myPipe[2];
	int pid;
	int stdout=1;
	int stdin=0;

	if (pipe(myPipe) < 0)
	{
		write(socketFd,STD_ERROR_MSG,strlen(STD_ERROR_MSG));
	}

	if (pipe(myPipe)==0){

	pid=fork();

	if (pid==0){
		dup2(myPipe[stdout], STDOUT_FILENO);
		execl(STRING_LANG_PROGNAME, STRING_LANG_PROGNAME, cPtr);
		fprintf(stderr, "%s\n", STD_ERROR_MSG);
		write(socketFd,STD_ERROR_MSG,strlen(STD_ERROR_MSG));
		exit(EXIT_FAILURE);
		}
		
	}
	int numBytes;	
	
	close(myPipe[stdout]);
	wait(NULL);
	if (pid > 0){
		
		while  ( (numBytes = read(myPipe[stdin],(char*)cPtr,BUFFER_LEN)) > 0){
   		write(socketFd,(char*)cPtr,numBytes);
   	}

    //wait(NULL);
    //close(myPipe[stdin]);
    //close(myPipe[stdin]);
   	}
   close(myPipe[stdin]);
   }
  


  //return(EXIT_SUCCESS);




  //  III.  Finished:





//  PURPOSE:  To cast 'vPtr' to the pointer type coming from 'doServer()'
//	that points to two integers.  Then, to use those two integers,
//	one as a file descriptor, the other as a thread number, to fulfill
//	requests coming from the client over the file descriptor socket.
//	Returns 'NULL'.
void*		handleClient	(void*		vPtr
				)
{
  //  I.  Application validity check:

  //  II.  Handle client:
  //  YOUR CODE HERE
	int* intArray=(int*)vPtr;
  int 	   fd		= intArray[0];	// <-- CHANGE THAT 0!
  int	   threadNum	= intArray[1];	// <-- CHANGE THAT 0!
	free(intArray);
  //  YOUR CODE HERE
  //  II.B.  Read command:
  char	buffer[BUFFER_LEN];
  char	command;
  char* textPtr;
  int 	shouldContinue	= 1;
  threadNum++;
  while  (shouldContinue)
  {
    read(fd,buffer,BUFFER_LEN);//read client's input
    printf("Thread %d received: %s\n",threadNum,buffer);
    command	= buffer[0];
    textPtr	= buffer + 2;

    // YOUR CODE HERE
    //if quit command =='q' then quit loop by setting shouldContinue to 0
    if ( command == QUIT_CMD_CHAR){
    write(fd, STD_BYE_MSG,sizeof(STD_BYE_MSG));
	shouldContinue=0;

}
    //if string lang command is 's' from textPtr then run stringLangFile
    if (command == STRING_LANG_CMD_CHAR){
    	stringLangFile(fd, textPtr);
    }

	}
  //  III.  Finished:
  printf("Thread %d quitting.\n",threadNum);
  return(NULL);

}


//  PURPOSE:  To run the server by 'accept()'-ing client requests from
//	'listenFd' and doing them.
void		doServer	(int		listenFd 
				)//listenFd is file descriptor for listening to OS
{
  //  I.  Application validity check:

  //  II.  Server clients:
  pthread_t		threadId;
  pthread_attr_t	threadAttr;
  int			threadCount	= 0; //increments everytime we have a new client
    pthread_attr_init(&threadAttr);//detached thread create(lecture 5)
    pthread_attr_setdetachstate(&threadAttr, PTHREAD_CREATE_DETACHED);
  while  (1)
  {
    //  YOUR CODE HERE
    //allocate enough memory for 2 ints (threadCount and fileDescriptor for client)
    

    int* intArray = (int*)calloc(2, sizeof(int));
    intArray[0] = accept(listenFd, NULL, NULL);
    intArray[1] = threadCount++;

    pthread_create(&threadId, &threadAttr, handleClient, (void*)intArray);
    
  }

  //  YOUR CODE HERE
    //pthread_join(threadId, NULL);
	pthread_attr_destroy(&threadAttr);
  //  III.  Finished:
}


//  PURPOSE:  To decide a port number, either from the command line arguments
//	'argc' and 'argv[]', or by asking the user.  Returns port number.
int		getPortNum	(int	argc,
				 char*	argv[]
				)
{
  //  I.  Application validity check:

  //  II.  Get listening socket:
  int	portNum;

  if  (argc >= 2)
    portNum	= strtol(argv[1],NULL,0); //if not given enough command line arguments
  else
  {
    char	buffer[BUFFER_LEN];

    printf("Port number to monopolize? ");
    fgets(buffer,BUFFER_LEN,stdin);
    portNum	= strtol(buffer,NULL,0);
  }

  //  III.  Finished:  
  return(portNum);
}


//  PURPOSE:  To attempt to create and return a file-descriptor for listening
//	to the OS telling this server when a client process has connect()-ed
//	to 'port'.  Returns that file-descriptor, or 'ERROR_FD' on failure.
int		getServerFileDescriptor
				(int		port
				)
{
  //  I.  Application validity check:

  //  II.  Attempt to get socket file descriptor and bind it to 'port':
  //  II.A.  Create a socket
  int socketDescriptor = socket(AF_INET, // AF_INET domain
			        SOCK_STREAM, // Reliable TCP
			        0);

  if  (socketDescriptor < 0)
  {
    perror(THIS_PROGRAM_NAME);
    return(ERROR_FD);
  }

  //  II.B.  Attempt to bind 'socketDescriptor' to 'port':
  //  II.B.1.  We'll fill in this datastruct
  struct sockaddr_in socketInfo;

  //  II.B.2.  Fill socketInfo with 0's
  memset(&socketInfo,'\0' ,sizeof(socketInfo));

  //  II.B.3.  Use TCP/IP:
  socketInfo.sin_family = AF_INET;

  //  II.B.4.  Tell port in network endian with htons()
  socketInfo.sin_port = htons(port);

  //  II.B.5.  Allow machine to connect to this service
  socketInfo.sin_addr.s_addr = INADDR_ANY; //allows any address to connect

  //  II.B.6.  Try to bind socket with port and other specifications
  int status = bind(socketDescriptor, // from socket()
		    (struct sockaddr*)&socketInfo,
		    sizeof(socketInfo)
		   );

  if  (status < 0)
  {
    perror(THIS_PROGRAM_NAME);
    return(ERROR_FD);
  }

  //  II.B.6.  Set OS queue length:
  listen(socketDescriptor,5);

  //  III.  Finished:
  return(socketDescriptor);
}


int		main		(int	argc,
				 char*	argv[]
				)
{
  //  I.  Application validity check:

  //  II.  Do server:
  int 	      port	= getPortNum(argc,argv); //gotten from command line
  int	      listenFd	= getServerFileDescriptor(port); //
  int	      status	= EXIT_FAILURE;

  if  (listenFd >= 0)
  {
    doServer(listenFd);
    close(listenFd);
    status	= EXIT_SUCCESS;
  }

  //  III.  Finished:
  return(status);
}
