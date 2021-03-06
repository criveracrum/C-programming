/*-------------------------------------------------------------------------*
 *---									---*
 *---		decoderServer3.cpp					---*
 *---									---*
 *---	    This file declares and defines:				---*
 *---	'struct Node': a C struct that holds text and a next ptr.	---*
 *---	'class Message': a C++ class that uses 'Node' that manages	---*
 *---	       		 a linked list of Node instances.		---*
 *---									---*
 *---	----	----	----	----	----	----	----	----	---*
 *---									---*
 *---	Version 1a		2020 March 15		Joseph Phillips	---*
 *---									---*
 *-------------------------------------------------------------------------*/

#include	"decoderServer.h"

//  PURPOSE:  To initialize '*this' to hold an empty message for the
//	client reachable by socket file descriptor 'newClientFd'.  No
//	return value.
Message::Message		(int		newClientFd
  				)
{
  firstPtr_	= NULL;
  lastPtr_	= NULL;
  clientFd_	= newClientFd;
}


//  PURPOSE:  To release the resources of '*this'.  No parameters.
//	No return value.
Message::~Message		()
{
  Node*	run;
  Node*	next;

  //  YOUR CODE HERE
  for  (run  = firstPtr_; run != NULL; run  = run->nextPtr_){
    next=run->nextPtr_;
    delete(run); 
  }


}


//  PURPOSE:  To add the text 'textPtr' in a new Node at the end of '*this'
//		list.  No return value.
void		Message::append	(const char*	textPtr
				)
{
  //  I already made the Node instance for you, 'nodePtr' points to it:
  Node*	nodePtr;

  nodePtr	= (Node*)malloc(sizeof(Node));

  memcpy(nodePtr->text_,textPtr,BUFFER_LEN);
  nodePtr->nextPtr_	= NULL;
  if (firstPtr_==NULL)
  {
    firstPtr_=nodePtr;
  }
  else
  {
    lastPtr_->nextPtr_=nodePtr;
  }
  lastPtr_=nodePtr;

  //  YOUR CODE HERE
}


//  PURPOSE:  To send the contents of '*this' message list to the the client.
//		Each Node of text is exactly 'BUFFER_LEN' characters long.
//		No parameters.  No return value.
void		Message::send	()
				const
{
  const Node*	run;


  for  (run  = firstPtr_; run != NULL; run  = run->nextPtr_){
    write(clientFd_, run->text_, BUFFER_LEN);
  }

  //  YOUR CODE HERE
}
