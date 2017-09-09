#include <stdio.h>
#include <stdlib.h>

typedef enum {false=0, true=1} bool;

typedef char graphElementT;
typedef struct vertexTag
{
	graphElementT element;
	bool visited;
	struct  edgeTag *edges;
	struct vertexTag *next;
}vertexT;





typedef struct Queue
{
	int size;
	int capacity;
	int front;
	int rear;
	vertexT* *elements;
}queue;
queue* createQueue(int maxsize)
{
	queue *q=(queue*)malloc(sizeof(queue));

	q->elements = (vertexT**)malloc(sizeof(vertexT*)*maxsize);
	q->size = 0;
	q->capacity=maxsize;
	q->front=0;
	q->rear=-1;
	return q;
}
void enqueue(queue *q,vertexT* element)
{
	if(q->size==q->capacity)
	{
		printf("Queue is full\n");
		return;
	}
		q->size +=1;
		q->rear +=1;
		if(q->rear==q->capacity)
		{
			q->rear %=q->capacity;
		}
		q->elements[q->rear]= element;

	return;
}

void dequeue(queue *q)
{
	if(q->size==0)
	{
		printf("Queue is enpty\n");
		return;
	}
		q->elements[q->front] = NULL;
		q->size -=1;
		q->front +=1;
		if(q->front==q->capacity)
		{
			q->front=0;
		}
	
	return;
}
int isEmpty(queue *q)
{
	if(q->size==0)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

vertexT* front(queue *q)
{
	if(q->size==0)
	{
		printf("Queue is empty\n");
		return;
	}
	return q->elements[q->front];
}