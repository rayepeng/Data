#pragma once
#define MaxSize 10
#include <iostream>
#include <cstdio>

typedef struct node
{
	int sonCount;
	char data;
	struct node *sons[MaxSize];
}TSonNode;
//������ͣ��б�Ҫ��ס�����������ж��ٸ����ӽ��


//����

typedef struct
{
	TSonNode *data[100];
	int front, rear;
}SqQueue;

void CreateTS(char *s, TSonNode *&tree)
{
	TSonNode *St[MaxSize], *p = NULL;
	tree = NULL;
	int top = -1, i = 0;
	char ch = *s++;
	while (ch != '\0')
	{
		if (ch == '(')
		{
			//ch==(, ��ջ
			top++;
			St[top] = p;
			i = 0;
		}
		else if (ch == ')')
		{
			top--;
			i = 0;
		}
		else if (ch == ',')
		{
			i++;
		}
		else
		{
			p = (TSonNode *)malloc(sizeof(TSonNode));
			p->data = ch;
			for (int k = 0; k < MaxSize; k++)
			{
				p->sons[k] = NULL;
			}
			if (tree == NULL)
			{
				tree = p;
			}
			else
			{
				St[top]->sons[i] = p;
			}
		}
		ch = *s++;
	}
}

void CountSons(TSonNode *&b)
{
	//��һ��ÿһ����������ɶ��ٸ�����
	TSonNode *p = b;
	for (int i = 0; i < MaxSize; i++)
	{
		TSonNode *q = p->sons[i];

	}
}
bool QueueEmpty(SqQueue *qu)
{
	return (qu->rear == qu->front);
}

void enQueue(SqQueue *qu, TSonNode *data)
{
	qu->rear++;
	qu->data[qu->rear] = data;
}
void InitQueue(SqQueue *&qu)
{
	qu = (SqQueue *)malloc(sizeof(SqQueue));
	qu->rear = qu->front = -1;
}
void deQueue(SqQueue *qu, TSonNode *&data)
{
	qu->front++;
	data = qu->data[qu->front];
}

#if 1
void SonsCount(TSonNode *&b)
{
	//b�еĺ����������
	SqQueue *qcount;
	InitQueue(qcount);
	enQueue(qcount, b);
	TSonNode *pTemp;
	while (!QueueEmpty(qcount)) {

		deQueue(qcount, pTemp);
		pTemp->sonCount = 0;
		for (int i = 0; i < MaxSize; i++)
		{
			if (pTemp->sons[i] != 0)
			{
				pTemp->sonCount++;
				enQueue(qcount, pTemp->sons[i]);
			}

		}

	}

}
#endif // 0

