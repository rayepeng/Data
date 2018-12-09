#include "demo.h"
#if 0
void OrderPrint(TSonNode *b)
{
	TSonNode *p = NULL;
	SqQueue *qu = NULL;
	int i = 0;
	InitQueue(qu);

	//���µ�˼·����,�ò�α����ķ�ʽ���������һ�����ڵ㣬�Ѹ��ڵ����
	//���Ӿ���ζ�����һ��Ԫ�أ�Ȼ������Ӹ��ڵ�������ӽڵ㣬�����ٳ���
	//
	enQueue(qu, b);
	printf("%c\n", b->data);
	while (!QueueEmpty(qu))
	{
		int i = 0;
		deQueue(qu, p);
		while (p->sons[i] != NULL)
		{
			enQueue(qu, p->sons[i]);
			printf("%c ", p->sons[i]->data);
			i++;
		}
		printf("\n");

	}
}
#endif // 0

#if 0
int checkQueue(TSonNode *p, SqQueue *&qu)
{
	int i = 0;
	while (p->sons[i] != NULL)
	{
		enQueue(qu, p->sons[i]);
		printf("%c ", p->sons[i]->data);
		i++;
	}
	return i;
}
bool isLeaf(TSonNode *b)
{
	for (int i = 0; i < MaxSize; i++)
	{
		if (b->sons[i] == NULL)
			continue;
		else
			return false;
	}
	return true;
}
void OrderPrint(TSonNode *b)
{
	TSonNode *p = NULL;
	SqQueue *qu = NULL;
	int i = 0;
	InitQueue(qu);
	enQueue(qu, b);
	printf("%c\n", b->data);
	int count = 0;
	while (!QueueEmpty(qu))
	{
		int i = 0;
		
		if (count == 0)
		{
			deQueue(qu, p);
			count = checkQueue(p, qu);
			printf("\n");
		}
		else
		{
			
			int Tempcount = count;//����
			while (Tempcount > 0)
			{
				count = 0;
				deQueue(qu, p);
				count += checkQueue(p, qu);
				Tempcount--;
			}
			printf("\n");
		}
		
		// int count = checkQueue(p, qu);
		// //count����p�м������ӣ���������ۼӣ�����ÿһ���ж��ٸ���㣬

		// printf("\n");

	}
}

#endif // 1

#if 1


SqQueue *qu = NULL;
int countnum[MaxSize];

int checkQueue(TSonNode *p, SqQueue *&qu)
{
	int i = 0;
	while (p->sons[i] != NULL)
	{
		enQueue(qu, p->sons[i]);
		printf("%c ", p->sons[i]->data);
		i++;
	}
	return i;
}
#if 1//��δ�������ȷ�ģ�ǧ���
void OrderPrint(TSonNode *b)
{
	TSonNode *p = NULL;
	int i = 0;
	InitQueue(qu);
	enQueue(qu, b);
	printf("%c\n", b->data);
	int count = 0;
	countnum[0] = 0;
	countnum[1] = 1;
	int j = 1;
	while (!QueueEmpty(qu))
	{
		int i = 0;

		if (count == 0)
		{
			deQueue(qu, p);
			count = checkQueue(p, qu);
			countnum[++j] = count;
			printf("\n");
		}
		else
		{

			int Tempcount = count;//����
			count = 0;
			while (Tempcount > 0)
			{

				deQueue(qu, p);
				count += checkQueue(p, qu);
				Tempcount--;
			}
			countnum[++j] = count;
			printf("\n");
		}
	}
}
#endif // 0


#endif // 1

#if 0
//��д��α����ĺ���
void MyOrderPrint(TSonNode *b)
{
	SqQueue *qb;
	TSonNode *p;
	InitQueue(qb);
	//�ø��ڵ����
	enQueue(qb, b);
	int i = 2;
	//��ӵ�ͬʱ�������Ԫ��
	printf("%c\n", b->data);
	while (!QueueEmpty(qb))
	{
		//�ڼ�����Ҫ���Ӽ���
		int tempCount = countnum[i-1];//��i��
		while (tempCount > 0)
		{
			deQueue(qb, p);
			for (int j = 0; j < countnum[i]-1; j++)
			{
				if (p->sons[j] == NULL)
				{
					printf("   ");
				}
				else
				{
					enQueue(qb, p->sons[j]);
					printf("%c ", p->sons[j]->data);
				}
			}
			tempCount--;
		}
		i++;
		printf("\n");
		/*deQueue(qb, p);
		for (int j = 0; j < countnum[i]; j++)
		{
			if (p->sons[j] == NULL)
			{
				printf("   ");
			}
			else
			{
				enQueue(qb, p->sons[j]);
				printf("%c ", p->sons[j]->data);
			}
		}
		i++;
		printf("\n");
*/
	}



}
#endif // 0

//��ȷ�İ汾
#if 0

void MyDebugOrderPrint(TSonNode *b)
{
	SqQueue *qu;
	TSonNode *p;
	InitQueue(qu);

	enQueue(qu, b);
	printf("%10c\n", b->data);
	int i = 2;
	while (!QueueEmpty(qu))
	{
		//������һ���ж��ٸ����
		int tempCount = countnum[i - 1];
		while (tempCount > 0)
		{
			deQueue(qu, p);
			if (p->sonCount == 0)
				printf("");
			//������һ��Ľ�㣬�������еĺ�����ӣ�����ӡ����ֵ
			else
			{
				printf("{");
				for (int j = 0; j < p->sonCount; j++)
				{
					printf(" %c ", p->sons[j]->data);
					enQueue(qu, p->sons[j]);

				}
				printf("}");
			}
			tempCount--;
		}
		printf("\n");
		i++;
	}
}

#endif // 1

#if 1
//debug�汾
void MyDebugOrderPrint(TSonNode *b)
{
	SqQueue *qu;
	TSonNode *p;
	InitQueue(qu);

	enQueue(qu, b);
	int spaceControl = 30;

	for (int i = 0; i < spaceControl / 2; i++)
	{
		printf(" ");
	}

	printf("%c\n", b->data);
	int i = 2;
	while (!QueueEmpty(qu))
	{
		//������һ���ж��ٸ����
		int tempCount = countnum[i - 1];
		//����֮����֪����һ���ж��ٸ���㣬Ȼ��ÿ������ڴ�ӡ֮ǰ��
		//���൱�ھ�����һ�οո�
		int spaceControlTemp = spaceControl / (countnum[i]+2);

		while (tempCount > 0)
		{
			deQueue(qu, p);
			if (p->sonCount == 0)
				printf(" ");
			//������һ��Ľ�㣬�������еĺ�����ӣ�����ӡ����ֵ
			else
			{
				printf("{");
				for (int j = 0; j < p->sonCount; j++)
				{
					if (countnum[i - 1] < countnum[i - 2])
					{
						for (int spaceTemp = countnum[i - 2] - countnum[i - 1]; spaceTemp >= 0; spaceTemp--)
							printf(" ");
					}
					else
					{
						for (int temp = 0; temp < spaceControlTemp; temp++)
						{
							printf(" ");
						}
					}
					printf(" %c ", p->sons[j]->data);
					enQueue(qu, p->sons[j]);

				}
				printf("}");
			}
			tempCount--;
		}
		printf("\n");
		i++;
	}
}

#endif // 1




int main(int argc, char const *argv[])
{
	TSonNode *b;
	char a[] = "A(B(D,C,F),F(G,H(1,2,3(4,5))))";
	CreateTS(a, b);
	SonsCount(b);
	OrderPrint(b);
	/*for (int i = 0; i < MaxSize; i++)
	{
		printf("%d\n", countnum[i]);
	}*/
	//MyOrderPrint(b);

	
	MyDebugOrderPrint(b);
	//int top = 0;
	//for (int i = 1; i < MaxSize; i++)
	//{
	//	//�����i��Ľ��
	//	int count = countnum[i];
	//	while (count > 0)
	//	{
	//		printf("%c ", qu->data[top++]->data);
	//		count--;
	//	}
	//	printf("\n");
	//}

	system("pause");
	return 0;
}