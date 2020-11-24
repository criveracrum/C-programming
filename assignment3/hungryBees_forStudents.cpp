/*-------------------------------------------------------------------------*
 *---									---*
 *---		hungryBees.cpp						---*
 *---									---*
 *---	    This file defines a C-ish C++ program that exercises	---*
 *---	knowledge ofPOSIX threads and linked list manipulation.		---*
 *---									---*
 *---	----	----	----	----	----	----	----	----	---*
 *---									---*
 *---	Version 1a		2020 February 17	Joseph Phillips	---*
 *---									---*
 *-------------------------------------------------------------------------*/
// $ g++ hungryBees.cpp -o hungryBees -lpthread

//---			Header file inclusion:				---//
 
#include	<stdlib.h>
#include	<stdio.h>
#include	<string.h>
#include	<pthread.h>
#include	<unistd.h>
#include	<string>


//---			Definition of constants:			---//
 
//  PURPOSE:  To tell how many flowers each bee hive must visit.
const int	NUM_FLOWERS_TO_COLLECT
				= 5;

//  PURPOSE:  To tell the number of bee hives that exist.
const int	NUM_BEE_HIVES	= 4;

//  PURPOSE:  To hold the names of the flowers:
const char*   	FLOWER_NAME_ARRAY[]
				= { "Jasmine",
				    "Daffodil",
				    "Daisy",
				    "Dandelion",
				    "Venus fly trap",
				    "Tumbleweed",
				    "Kudzu",
				    "Poison Ivy"
				  };

//  PURPOSE:  To tell how many flower names there are.
const size_t	NUM_FLOWER_NAMES= sizeof(FLOWER_NAME_ARRAY)/sizeof(const char*);


//---		    Definition of classes and structs:			---//

//  PURPOSE:  To represent a flower.
class		Flower
{
  //  I.  Member vars:
  //  PURPOSE:  To hold address of the name of the flower as a C-string.
  const char*			nameCPtr_;

  //  PURPOSE:  To hold the address of the Flower instance after '*this' one,
  //	or 'NULL' if there is no such Flower.
  Flower*			nextPtr_;

  //  II.  Disallowed auto-generated methods:
  //  No copy constructor:
  Flower			(const Flower&);

  //  No copy assignment op:
  Flower&	operator=	(const Flower&);

protected :
  //  III.  Protected methods:

public :
  //  IV.  Constructor(s), assignment op(s), factory(s) and destructor:
  //  PURPOSE:  To make '*this' a stand-alone Flower instance with a randomly-
  //  	chosen name.  No parameters.  No return value.
  Flower			() :
				nameCPtr_(FLOWER_NAME_ARRAY[rand() %
					  NUM_FLOWER_NAMES]
					 ),
				nextPtr_(NULL)
				{ }

  //  PURPOSE:  To release the resources of '*this'.  No parameters.  No
  //	return value.
  ~Flower			()
				{ }

  //  V.  Accessors:
  //  PURPOSE:  To return the name of the flower.  No parameters.
  const char*	getNameCPtr	()
				const
				{ return(nameCPtr_); }

  //  PURPOSE:  To return the address of the Flower instance after '*this' one,
  //	or 'NULL' if there is no such Flower.
  Flower*	getNextPtr	()
				const
				{ return(nextPtr_); }

  //  VI.  Mutators:
  //  PURPOSE:  To note that the next flower in the list has address
  //	'newNextPtr'.  No return value.
  void		setNextPtr	(Flower*	newNextPtr
  				)
				{ nextPtr_ = newNextPtr; }

  //  VII.  Methods that do main and misc work of class:

};

class		Garden
{
  //  I.  Member vars:
  //  YOUR MEMBER VARS HERE
  Flower* beginPtr_;
  Flower* endPtr_;
  int GARDEN_LIST_LEN;


  //  II.  Disallowed auto-created methods:
  //  No copy constructor:
  Garden			(const Garden&);

  //  No copy assignment op:
  Garden&	operator=	(const Garden&);

protected :
  //  III.  Protected methods:

public :
  //  IV.  Constructor(s), assignment op(s), factory(s) and destructor:
  //  PURPOSE:  To initialize '*this' to an empty garden.  No parameters.
  //	No return value.
  Garden			()
				{
				  //  INITIALIZE HERE
          beginPtr_=NULL;
          endPtr_=NULL;
          GARDEN_LIST_LEN=0;

				}

  //  PURPOSE:  To release the resources of '*this'.  No parameters.
  //  	No return value.
  ~Garden			()
				{
				  //  GET RID OF LIST HERE
				}

  //  V.  Accessor(s):
  //  PURPOSE:  To hold length of '*this' list.
  int		getNumFlowers	()
  				const
				{ return(GARDEN_LIST_LEN); /* CHANGE THAT 0 */}


  //  VI.  Mutator(s):

  //  VII.  Methods that do main and misc. work of class:
  //  PURPOSE:  To add the Flower with address 'flowerPtr' at the back of
  //	'*this' Garden of Flower instances.  No return value.
  void		store		(Flower*	flowerPtr
				)
				{
          if (GARDEN_LIST_LEN==0){
            beginPtr_=flowerPtr;
            endPtr_=nextPtr_;
            GARDEN_LIST_LEN++;
          } 

          else{
            endPtr_=flowerPtr;
            GARDEN_LIST_LEN++;
				}
          }

  //  PURPOSE:  To print this list of Flower instances in '*this' Garden.
  //	No parameters.  No return value.
  void		print		()
				{
				  stuct Flower* tmp=beginPtr_;

          for (int i=0 ; i<GARDEN_LIST_LEN; i++){
            printf("%s\n", tmp->getNameCPtr());
            tmp=tmp->nextPtr_;
          }
          
				}
 
};


struct		Hive
{
  std::string			name_;
  Garden*			gardenPtr_;

  Hive				() :
  				name_(""),
				gardenPtr_(NULL)
				{ }

  ~Hive				()
  				{
				  delete(gardenPtr_);
				}

  const char*	getNameCPtr	()
  				const
				{ return(name_.c_str()); }

};


//---			Definition of global vars:			---//

//  PURPOSE:  To hold the address of the flower offered by the farmer.
//	or to hold 'NULL' if there is no such Flower.
Flower*		availableFlowerPtr	= NULL;

//  PURPOSE:  To tell how much honey has been produced by the bee hives.
int		honey			= 0;

//  YOUR CODE HERE to add global vars to control access to availableFlowerPtr and honey:


//---			Definition of main functions:			---//

//  PURPOSE:  To be the function run by the bee hive threads.  'vPtr' points
//	to an instance of 'Hive'.  Returns 'NULL'.
void*		hive		(void*		vPtr
				)
{
  //  I.  Application validity check:

  //  II.  Get the flowers:
  //  II.A.  Initialize local vars:
  Hive*		hivePtr		= (Hive*) vPtr;  // CHANGE THAT NULL
  Garden*	gardenPtr	= gardenPtr_;  // CHANGE THAT NULL

  //  II.B.  Each iteration obtains another Flower instance for the graden
  //  	     of Hive '*hivePtr':
  while  (gardenPtr->getNumFlowers() < NUM_FLOWERS_TO_COLLECT)
  {
    //  YOUR CODE HERE: Make access to avaialbleFlowerPtr thread-safe

    while  (availableFlowerPtr == NULL)
    {
      printf("%s: \"Hey!  No flowers, no honey!\"\n",hivePtr->getNameCPtr());
    }

    printf("%s: \"A %s!  Sure we will take that!\"\n",
	   hivePtr->getNameCPtr(),availableFlowerPtr->getNameCPtr()
	  );
    gardenPtr->store(availableFlowerPtr);
    availableFlowerPtr	= NULL;


    //  Leave this outside critical section:
    sleep(rand() % 3);	// Please leave this OUT of the critical section
  }

  //  II.C.  Add to the honey when have enough flowers:
  printf("%s \"Finally, enough flowers to make some honey.\"\n",
  	 hivePtr->getNameCPtr()
	);

  //  YOUR CODE HERE: Make incrementing honey thread-save
  honey++;

  //  III.  Finished:
  return(NULL);
}


//  PURPOSE:  To be the function run by the farmer thread.  'vPtr' is ignored.
//	Returns 'NULL'.
void*		farmer		(void*	vPtr)
{
  //  I.  Application validity check:

  //  II.  Give flowers:
  //  II.A.  Each iteration creates and gives another Flower instance
  //  	     until there is sufficient honey:
  while  (true)
  {
    //  YOUR CODE HERE: Make access to honey thread-safe
    if  (honey >= NUM_BEE_HIVES)
    {
      break;
    }

    printf("Farmer: \"I have to gather *more* flowers?!?\"\n");

    //  YOUR CODE HERE: Make access to availableFlowerPtr thread-safe
    while  (availableFlowerPtr != NULL)
    {
      printf("Farmer: \"Hey, you said you wanted"
      	     " a flower, come and take it.\"\n"
	    );
    }

    availableFlowerPtr	= new Flower;
    printf("Farmer: \"Okay here is another flower: a %s\"\n",
	   availableFlowerPtr->getNameCPtr()
	  );


    //  Leave this outside critical section:
    sleep(rand() % 3);	// Please leave this OUT of the critical section
  }

  //  III.  Finished:
  printf("Farmer \"I *finally* got my honey!\"\n");
  return(NULL);
}


//  PURPOSE:  To run the program.  Ignores command line arguments.  Returns
//	'EXIT_SUCCESS' to OS.
int		main		()
{
  //  I.  Application validity check:

  //  II.  Have the farmer give Flower instances until sufficient honey
  //  	   has been obtained:
  //  II.A.  Randomize random number generator:
  srand(getpid());

  //  II.B.  Initialize global vars:
  Hive		hiveArray[NUM_BEE_HIVES];
  pthread_t farmerid;
  pthread_t hid[NUM_BEE_HIVES];


  //  II.C.  Make threads:
  //  II.C.1.  Make bee hive threads:
  for  (int i = 0;  i < NUM_BEE_HIVES;  i++)
  {
    hiveArray[i].name_		= std::string("Hive ") + (char)('A'+i);
    hiveArray[i].gardenPtr_	= new Garden;
    pthread_create(&hid[i],NULL, hive(), (void*)&hid[i]);
  }

  //  II.C.2.  Make farmer thread:
  pthread_create(&farmerid,NULL, farmer(),NULL);

  //  II.D.  Wait for child threads:
  //  II.D.1.  Wait for bee hive threads:
  for  (int i = 0;  i < NUM_BEE_HIVES;  i++)
  {
    pthread_join(hid[i], (void**)&hiveArray)
    printf("%s has:\n",hiveArray[i].getNameCPtr());
    hiveArray[i].gardenPtr_->print();
  }

  //  II.D.2.  Wait for farmer thread:
  //  Add something here?

  //  II.E.  Get rid of global vars:
  pthread_join(farmerid,NULL);

  //  III.  Finished:
  return(EXIT_SUCCESS);
}
