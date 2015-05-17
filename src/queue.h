/*************************************************************************
	> File Name: queue.h
	> Author: Will Yu
	> Mail: ysr103109@163.com 
	> Created Time: 日  4/19 11:30:26 2015
 ************************************************************************/

#ifndef Queue_H  
#define Queue_H  
#define QUEUE_DATA_LENGTH 1024
  
typedef int Item;  
typedef struct node *PNode;  
typedef struct node  
{
	char data[QUEUE_DATA_LENGTH];  
	PNode next;  
}Node;  
  
typedef struct  
{
	PNode front;  
	PNode rear;  
	int size;  
}Queue;  
  
/*init an empty queue*/  
Queue *InitQueue();  
  
/*destroy a queue*/  
void DestroyQueue(Queue *pqueue);  
  
/*empty an queue*/  
void ClearQueue(Queue *pqueue);  
    
int IsEmpty(Queue *pqueue);  
  
/*get length of the queue*/  
int GetSize(Queue *pqueue);  
  
/*get the first node in queue*/  
PNode GetFront(Queue *pqueue,char *pitem);  
  
/*get the last node in queue*/  
PNode GetRear(Queue *pqueue,char *pitem);  
  
/*push into the queue*/  
PNode EnQueue(Queue *pqueue,char *item);  
  
/*pop the first node*/  
PNode DeQueue(Queue *pqueue,char *pitem);  

char *lpopQueue(Queue *pqueue);
  
/*遍历队列并对各数据项调用visit函数*/  
void QueueTraverse(Queue *pqueue,void (*visit)());  
  
#endif  
