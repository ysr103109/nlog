/*************************************************************************
	> File Name: queue.c
	> Author: Will Yu
	> Mail: ysr103109@163.com 
	> Created Time: 日  4/19 11:34:20 2015
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include"Queue.h"  
  
Queue *InitQueue()  
{  
	Queue *pqueue = (Queue *)malloc(sizeof(Queue));  
	if(pqueue != NULL)  
	{  
		pqueue->front = NULL;  
		pqueue->rear = NULL;  
		pqueue->size = 0;  
	}  
	return pqueue;  
}  
  
void DestroyQueue(Queue *pqueue)  
{  
	if(IsEmpty(pqueue)!=1)  
		ClearQueue(pqueue);  
	free(pqueue);  
}  
  
void ClearQueue(Queue *pqueue)  
{  
	while(IsEmpty(pqueue) != 1)  
	{  
		DeQueue(pqueue,NULL);  
	}  
}  
  
int IsEmpty(Queue *pqueue)  
{  
	if(pqueue->front == NULL && pqueue->rear == NULL && pqueue->size == 0)  
		return 1;  
	else  
		return 0;  
}  
  
int GetSize(Queue *pqueue)  
{  
	return pqueue->size;  
}  
  
PNode GetFront(Queue *pqueue,char *pitem)  
{  
	if(IsEmpty(pqueue) != 1 && pitem != NULL){  
		pitem = pqueue->front->data;  
	}  
	return pqueue->front;  
}  
  
PNode GetRear(Queue *pqueue,char *pitem)  
{  
	if(IsEmpty(pqueue) != 1 && pitem != NULL){  
		pitem = pqueue->rear->data;  
	}  
	return pqueue->rear;  
}  
  
PNode EnQueue(Queue *pqueue,char *item)  
{  
	PNode pnode = (PNode)malloc(sizeof(Node));  
	if(pnode != NULL){  
		strcpy(pnode->data, item);
		//pnode->data = item;  
		pnode->next = NULL;  
										          
		if(IsEmpty(pqueue)){  
			pqueue->front = pnode;  
		}  
		else{  
			pqueue->rear->next = pnode;  
		}  
		pqueue->rear = pnode;  
		pqueue->size++;  
	}  
	return pnode;  
}  
  
PNode DeQueue(Queue *pqueue,char *pitem)  
{  
	PNode pnode = pqueue->front;  
	if(IsEmpty(pqueue) != 1 && pnode != NULL){  
		if(pitem != NULL)  
			pitem = pnode->data;  
		pqueue->size--;  
		pqueue->front = pnode->next;  
		free(pnode);  
		if(pqueue->size == 0)  
			pqueue->rear = NULL;  
	}  
	return pqueue->front;
}  

char *lpopQueue(Queue *pqueue){
	PNode pnode = pqueue->front;
	char *data;
	if(1 != IsEmpty(pqueue) && NULL != pnode){
		data = (char*)malloc(strlen(pnode->data)*sizeof(char));
		strcpy(data, pnode->data);
		pqueue->size--;
		pqueue->front = pnode->next;
		free(pnode);
		if(0 == pqueue->size)
			pqueue->rear = NULL;
	}
	else
		data = NULL;
	return data;
}
  
void QueueTraverse(Queue *pqueue,void (*visit)()){  
	PNode pnode = pqueue->front;  
	int i = pqueue->size;  
	while(i--){  
		visit(pnode->data);  
		pnode = pnode->next;  
	}         
}
