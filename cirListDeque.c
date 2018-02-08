#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <float.h>
#include "cirListDeque.h"

/* Double Link Struture */
struct DLink {
	TYPE value;/* value of the link */
	struct DLink * next;/* pointer to the next link */
	struct DLink * prev;/* pointer to the previous link */
};

# define TYPE_SENTINEL_VALUE DBL_MAX 


/* ************************************************************************
 Deque ADT based on Circularly-Doubly-Linked List WITH Sentinel
 ************************************************************************ */

struct cirListDeque {
	int size;/* number of links in the deque */
	struct DLink *Sentinel;	/* pointer to the Sentinel */
};
/* internal functions prototypes */
struct DLink* _createLink (TYPE val);
void _addLinkAfter(struct cirListDeque *q, struct DLink *lnk, TYPE v);
void _removeLink(struct cirListDeque *q, struct DLink *lnk);

int _isInDeque(struct cirListDeque *q, struct DLink *lnk);

/* ************************************************************************
	Deque Functions
************************************************************************ */

/*
 create a new circular list deque
 
	pre:    none
 	post:	returns pointer to allocated deque q, q->Sentinel is allocated and q->size equals zero
 
 */

struct cirListDeque *createCirListDeque()
{
	struct cirListDeque *q = NULL;
	q = malloc(sizeof (struct cirListDeque));
	assert(q != NULL);
	q->size = 0;
	assert(q->size == 0);
	q->Sentinel = NULL;
	q->Sentinel = malloc(sizeof (struct DLink));
	assert(q->Sentinel != NULL);
	q->Sentinel->value = -1;
	q->Sentinel->next = q->Sentinel;
	q->Sentinel->prev = q->Sentinel;
	assert(q->Sentinel->next == q->Sentinel && q->Sentinel->prev == q->Sentinel);
	return q;
}


/* Create a link for a value.

	param: 	val		the value to create a link for
	pre:	none
	post:	a link to store the value
*/
struct DLink * _createLink (TYPE val)
{
	struct DLink *newLink = NULL;
	newLink = malloc(sizeof (struct DLink));
	assert(newLink != NULL);
	newLink->value = val;
	newLink->next = NULL;
	newLink->prev = NULL;
	return newLink;

	/*temporary return value..you may need to change it*/
	//return(0);	 

}

int _isInDeque(struct cirListDeque *q, struct DLink *lnk)
{
	assert(q != NULL);
	struct DLink *current = q->Sentinel; 
	do {
		if(current == lnk)
		 		return 1;
		 	current = current->next;
	} while(current != q->Sentinel); 
	return 0;
}

/* Adds a link after another link

	param: 	q		pointer to the deque
	param: 	lnk		pointer to the existing link in the deque
	param: 	v		value of the new link to be added after the existing link
	pre:	q is not null
	pre: 	lnk is not null
	pre:	lnk is in the deque 
	post:	the new link is added into the deque after the existing link
*/
void _addLinkAfter(struct cirListDeque *q, struct DLink *lnk, TYPE v)
{
	assert(q != NULL && lnk != NULL);
	assert(_isInDeque(q, lnk) == 1);
	struct DLink *newLink = NULL;
	newLink = _createLink(v);
	assert(newLink != NULL);
	newLink->next = lnk->next;
	newLink->prev = lnk;
	lnk->next->prev = newLink;
	lnk->next = newLink;
	q->size = q->size + 1;
}

/* Adds a link to the back of the deque

	param: 	q		pointer to the deque
	param: 	val		value for the link to be added
	pre:	q is not null
	post:	a link storing val is added to the back of the deque
*/
void addBackCirListDeque (struct cirListDeque *q, TYPE val) 
{
	assert(q != NULL);
	_addLinkAfter(q, q->Sentinel->prev, val);
}

/* Adds a link to the front of the deque

	param: 	q		pointer to the deque
	param: 	val		value for the link to be added
	pre:	q is not null
	post:	a link storing val is added to the front of the deque
*/
void addFrontCirListDeque(struct cirListDeque *q, TYPE val)
{
	assert(q != NULL);
	_addLinkAfter(q, q->Sentinel, val);
}

/* Get the value of the front of the deque

	param: 	q		pointer to the deque
	pre:	q is not null and q is not empty
	post:	none
	ret: 	value of the front of the deque
*/
TYPE frontCirListDeque(struct cirListDeque *q) 
{
	assert(q != NULL && isEmptyCirListDeque(q) != 1);
	return q->Sentinel->next->value;	 
	/*temporary return value..you may need to change it*/
	//return(1);
}

/* Get the value of the back of the deque

	param: 	q		pointer to the deque
	pre:	q is not null and q is not empty
	post:	none
	ret: 	value of the back of the deque
*/
TYPE backCirListDeque(struct cirListDeque *q)
{
	assert(q != NULL && isEmptyCirListDeque(q) != 1);
	return q->Sentinel->prev->value;	 
	/*temporary return value..you may need to change it*/
	//return(1);
}

/* Remove a link from the deque

	param: 	q		pointer to the deque
	param: 	lnk		pointer to the link to be removed
	pre:	q is not null and q is not empty
	post:	the link is removed from the deque
*/
void _removeLink(struct cirListDeque *q, struct DLink *lnk)
{
	assert(q != NULL && isEmptyCirListDeque(q) != 1);
	lnk->prev->next = lnk->next;
	lnk->next->prev = lnk->prev;
	free(lnk);
	q->size = q->size - 1; 

}

/* Remove the front of the deque

	param: 	q		pointer to the deque
	pre:	q is not null and q is not empty
	post:	the front is removed from the deque
*/
void removeFrontCirListDeque (struct cirListDeque *q) {
	assert(q != NULL && isEmptyCirListDeque(q) != 1);
	_removeLink(q, q->Sentinel->next);
}


/* Remove the back of the deque

	param: 	q		pointer to the deque
	pre:	q is not null and q is not empty
	post:	the back is removed from the deque
*/
void removeBackCirListDeque(struct cirListDeque *q)
{
  	assert(q != NULL && isEmptyCirListDeque(q) != 1);
  	_removeLink(q, q->Sentinel->prev);
}

/* De-allocate all links of the deque, and the deque itself

	param: 	q		pointer to the deque
	pre:	none
	post:	All links (including Sentinel) are de-allocated
*/
void freeCirListDeque(struct cirListDeque *q)
{
	while (q->Sentinel->next != q->Sentinel && q->Sentinel->prev != q->Sentinel)
		 {
		 	removeFrontCirListDeque(q);
		 }	
	free(q->Sentinel); 
	free(q);
}

/* Check whether the deque is empty

	param: 	q		pointer to the deque
	pre:	q is not null
	ret: 	1 if the deque is empty. Otherwise, 0.
*/
int isEmptyCirListDeque(struct cirListDeque *q) {
  	assert(q != NULL);
  	if (q->size == 0 || (q->Sentinel->next == q-> Sentinel && q->Sentinel->prev == q->Sentinel)) {
  		return 1;
  	} else {
  		return 0;
  	}
	/*temporary return value..you may need to change it*/
	//return(1);
}

/* Print the links in the deque from front to back

	param: 	q		pointer to the deque
	pre:	q is not null and q is not empty
	post: 	the links in the deque are printed from front to back
*/
void printCirListDeque(struct cirListDeque *q)
{
	assert(q != NULL && isEmptyCirListDeque(q) != 1);
	struct DLink *current = q->Sentinel->next;
	printf("Deque contains: \n"); 
	while(current != q->Sentinel)
		 {
		 	printf("%f, ", current->value);
		 	current = current->next;
		 }	 
	printf("\n");
}
