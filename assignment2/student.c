#include	"sleepyProfHeaders.h"

int		isStillClassTime	= 1;
int complainAtProfCount=0;
int snoredAtCount=0;
pid_t		deanPid;
pid_t 		prof_Id;







void		classDismissedHandler
				(int		sigNum
				)
{
    
    
    printf("Student \"Time for lunch!\"\n");
    isStillClassTime=0;
   
}

void		profTeachHandler
				(int		sigNum
				)
{
    
    
    printf("(Student scribbles notes.)\n");
}

void		snoreHandler
				(int		sigNum
				)
{
    snoredAtCount++;

    if (snoredAtCount< NUM_SNORES_BEFORE_STUDENT_COMPLAINS){
    	printf("Student \"%s?\"\n",PROFS_NAME);
    }
    else {
    	snoredAtCount=0;
    	complainAtProfCount++;
    	if (complainAtProfCount<NUM_COMPLAINTS_TO_PROF_BEFORE_COMPLAIN_TO_DEAN){
    		
    		kill(prof_Id, COMPLAIN_SIGNAL);
    		printf("Student \"%s!\"\n",PROFS_NAME);

    	}
    	else {
    		complainAtProfCount=0;
    		kill(deanPid, COMPLAIN_SIGNAL);
    		printf("Student \"I have had enough!  I'm calling the Dean.\"\n");
    	}

    }
   
}




void		installSignalHandlers
				()
{
  struct sigaction	act;

  memset(&act,'\0',sizeof(act));
  act.sa_handler	= classDismissedHandler;
  sigaction(CLASS_DISMISSED_SIGNAL,&act,NULL);
  
  act.sa_handler	= profTeachHandler;
  sigaction(PROF_TEACH_SIGNAL,&act,NULL);

  act.sa_handler	= snoreHandler;
  sigaction(PROF_SNORE_SIGNAL,&act,NULL);

}









int		main		(int		argc,
	char*		argv[]
				){

if   (argc < 1){
	printf("Student \"Hey!  You did not tell me the Dean's number so I can complain if I need to\"\n");
    exit(EXIT_FAILURE);
}
deanPid=atoi(argv[1]); 

prof_Id=getppid();


installSignalHandlers();

 while  (isStillClassTime)
  {
    sleep(1);
  }

  return(EXIT_SUCCESS);

				}
