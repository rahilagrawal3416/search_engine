/*
    queue.c ... simple Queue of Strings
    Written by John Shepherd, September 2015
    -------------------------------------------------------------
    UNSW COMP2521 17s2 Assignment 2 - Yaggle
    (http://www.cse.unsw.edu.au/~cs2521/17s2/ass/ass02/Ass2.html)
    ass2grp (Yaggle) members:
    - Rahil Agrawal (z5165505) rahil.agrawal@student.unsw.edu.au
    - Dennis Gann (z5164328) d.gann@unsw.edu.au
    - Kongwei Ying (z5014882) k.ying@student.unsw.edu.au
    -------------------------------------------------------------

 */

#include "queue.h"

typedef struct Node *Link;

typedef struct Node
{
	char *val;
	Link next;
} Node;

typedef struct QueueRep
{
	Link front;
	Link back;
} QueueRep;

static Link newNode(char *);
static void disposeNode(Link);

// newQueue()
// - create an initially empty Queue
Queue newQueue() {
	Queue new = malloc(sizeof(QueueRep));
	assert(new != NULL);
	new->front = NULL;
	new->back = NULL;
	return new;
}

// disposeQueue(Queue)
// - clean up memory associated with Queue
void disposeQueue(Queue q) {
	if (q == NULL){
		return;
	}
	Link next, curr = q->front;
	while (curr != NULL)
	{
		next = curr->next;
		disposeNode(curr);
		curr = next;
	}
	free(q);
}

// enterQueue(Queue,Str)
// - add Str to back of Queue
void enterQueue(Queue q, char *str) {
	Link new = newNode(str);
	if (q->front == NULL)
		q->front = q->back = new;
	else
	{
		// add into list of elems
		q->back->next = new;
		q->back = new;
	}
}

// leaveQueue(Queue)
// - return string at front of Queue
char *leaveQueue(Queue q) {
	assert(q->front != NULL);
	char *str = strdup(q->front->val);
	Link old = q->front;
	q->front = old->next;
	if (q->front == NULL)
		q->back = NULL;
	free(old->val);
	free(old);
	return str;
}

// emptyQueue(Queue)
// - check whether Queue is empty
int emptyQueue(Queue q) {
	return (q->front == NULL);
}

// showQueue(Queue)
// - display Queue (for debugging)
void showQueue(Queue q) {
	Link curr;
	if (q->front == NULL)
		printf("Queue is empty\n");
	else
	{
		printf("Queue (front-to-back):\n");
		int id = 0;
		curr = q->front;
		while (curr != NULL)
		{
			printf("[%03d] %s\n", id, curr->val);
			id++;
			curr = curr->next;
		}
	}
}

// Helper functions
static Link newNode(char *str) {
	Link new = malloc(sizeof(Node));
	assert(new != NULL);
	new->val = strdup(str);
	new->next = NULL;
	return new;
}

static void disposeNode(Link curr) {
	assert(curr != NULL);
	free(curr->val);
	free(curr);
}
