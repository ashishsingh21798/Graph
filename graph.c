#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

/*
typedef struct vertexTag
{
	graphElementT element;
	bool visited;
	struct  edgeTag *edges;
	struct vertexTag *next;
}vertexT;
*/
typedef struct edgeTag
{
	struct vertexTag *connectsTo;
	struct edgeTag *next;
}edgeT;

vertexT *graph=NULL;

vertexT* createVertex(graphElementT Vname)
{
	vertexT *temp=(vertexT*)malloc(sizeof(vertexT));
	temp->element = Vname;
	temp->visited = false;
	temp->edges = NULL;
	temp->next = NULL; 
	return temp;
}

edgeT* createEdge()
{
	edgeT *t=(edgeT*)malloc(sizeof(edgeT));
	t->connectsTo = NULL;
	t->next = NULL;
	return t;
}

void addVertex(graphElementT Vname)
{
	vertexT *l=graph;
	bool b=false;
	while(l!=NULL)
	{
		if(l->element==Vname)
		{
			b=true;
			break;
		}
		l=l->next;
	}
	if(!b)
	{
		vertexT *t=createVertex(Vname);
		t->next=graph;
		graph=t;
	}
}

void addEdge(graphElementT start,graphElementT end)
{
	if(graph==NULL)
	{
		vertexT *t=createVertex(start);
		vertexT *l=createVertex(end);
		edgeT *e=createEdge();
		t->next=l;
		e->connectsTo=l;
		t->edges=e;
		graph=t;
	}
	else
	{
		vertexT *t=graph;
		vertexT *l=graph;

		while(t!=NULL)
		{
			if(t->element==start)
			{
				break;
			}
			t=t->next;
		}
		if(t==NULL)
		{
			vertexT *a=createVertex(start);
			a->next=graph;
			graph=a;
			t=a;
		}
		
		while(l!=NULL)
		{
			if(l->element==end)
			{
				break;
			}
			l=l->next;
		}
		if(l==NULL)
		{
			vertexT *a=createVertex(end);
			a->next=graph;
			graph=a;
			l=a;
		}
		
		edgeT *e=createEdge();
		e->connectsTo=l;
		e->next=t->edges;
		t->edges=e;
	}
}


void print()
{
	vertexT *t=graph;
	edgeT *e=NULL;
	while(t!=NULL)
	{
		printf("%c ==",t->element);
		e=t->edges;
		while(e!=NULL)
		{
			printf("%c ->",e->connectsTo->element);
			e=e->next;
		}
		t=t->next;
		printf("\n");
	}
}

void findEdge(graphElementT start,graphElementT end)
{
	vertexT *t=graph;
	while(t!=NULL)
	{
		if(t->element==start)
		{
			break;
		}
		t=t->next;
	}
	if(t==NULL)
	{
		printf("Edge not found in the graph\n");
		return;
	}
	edgeT *e=t->edges;
	while(e!=NULL)
	{
		if(e->connectsTo->element==end)
		{
			printf("Edge found in the graph\n");
			return;
		}
		e=e->next;
	}
	if(e==NULL)
	{
		printf("Edge not found in the graph\n");
		return;
	}
}

void findVertex(graphElementT Vname)
{
	vertexT *t=graph;
	while(t!=NULL)
	{
		if(t->element==Vname)
		{
			printf("Vertex found in the graph\n");
			return;
		}
		t=t->next;
	}
	if(t==NULL)
	{
		printf("Vertex not found in the graph\n");
		return;
	}
}

void bfs(graphElementT c)
{
	queue *q=createQueue(100);
	vertexT *t = graph;
	while(t != NULL)
	{
		if(t->element == c)
		{
			break;
		}
		t = t->next;
	}
	vertexT *z;
	edgeT *e;
	enqueue(q,t);
	
	while(!isEmpty(q))
	{
		z = front(q);
		z->visited = true;
		printf("%c ",z->element);
		e = z->edges;
		dequeue(q);
		while(e != NULL && !e->connectsTo->visited)
		{
			enqueue(q,e->connectsTo);
			e = e->next;
		}
	}
	
	while(t!= NULL)
	{
		t->visited = false;
		t = t->next;
	}
	printf("\nhacked\n");
}

int main()
{
	printf("In %s\n",__func__);
	
	graphElementT st,ed;
	//queue *q=createQueue(100);
	
	while(1)
	{
		printf("=======================================================================\n");
		printf("1 --> If you want to add edge.\n");
		printf("2 --> If you want to add vertex.\n");
		printf("3 --> If you want to print graph.\n");
		printf("4 --> If you want to search vertex in the graph.\n");
		printf("5 --> If you want to search edge in the graph\n");
		printf("6 --> breath first search\n");
		printf("0 --> If you want to exit.\n");
		printf("=======================================================================\n");
		printf("enter your choice\n\n");
		int choice;
		scanf("%d",&choice);
		if(choice==1)
		{
			printf("enter starting node\n");
			scanf(" %c",&st);
			printf("enter ending node\n");
			scanf(" %c",&ed);
			addEdge(st,ed);
		}
		else if(choice==2)
		{
			printf("enter vertex name\n");
			scanf(" %c",&st);
			addVertex(st);
		}
		else if(choice==3)
		{
			print(graph);
		}
		else if(choice==4)
		{
			printf("Enter vertex name that you want to find\n");
			scanf(" %c",&st);
			findVertex(st);
		}
		else if(choice==5)
		{
			printf("Enter starting node of edge that you want to find\n");
			scanf(" %c",&st);
			printf("Enter ending node of edge that you want to find\n");
			scanf(" %c",&ed);
			findEdge(st,ed);
		}
		else if(choice==6)
		{
			printf("Enter source element\n");
			scanf(" %c",&st);
			bfs(st);
		}
		else if(choice==0)
		{
			exit(EXIT_SUCCESS);
		}
		else
		{
			printf("Invalid choice please choice right no\n");
		}
	}
	return 0;
}