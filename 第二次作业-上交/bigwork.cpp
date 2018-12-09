#include "demo.h"
#if 0
void OrderPrint(TSonNode *b)
{
	TSonNode *p = NULL;
	SqQueue *qu = NULL;
	int i = 0;
	InitQueue(qu);

	//大致的思路就是,用层次遍历的方式，首先入队一个根节点，把根节点出队
	//出队就意味着输出一个元素，然后再入队根节点的所有子节点，接着再出队
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
			
			int Tempcount = count;//备份
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
		// //count表明p有几个孩子，可以逐层累加，计算每一层有多少个结点，

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
#if 1//这段代码是正确的，千万别动
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

			int Tempcount = count;//备份
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
//重写层次遍历的函数
void MyOrderPrint(TSonNode *b)
{
	SqQueue *qb;
	TSonNode *p;
	InitQueue(qb);
	//让根节点入队
	enQueue(qb, b);
	int i = 2;
	//入队的同时可以输出元素
	printf("%c\n", b->data);
	while (!QueueEmpty(qb))
	{
		//第几层需要出队几次
		int tempCount = countnum[i-1];//第i层
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

//正确的版本
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
		//计算上一层有多少个结点
		int tempCount = countnum[i - 1];
		while (tempCount > 0)
		{
			deQueue(qu, p);
			if (p->sonCount == 0)
				printf("");
			//出队上一层的结点，让其所有的孩子入队，并打印孩子值
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
//debug版本
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
		//计算上一层有多少个结点
		int tempCount = countnum[i - 1];
		//进入之后我知道这一层有多少个结点，然后每个结点在打印之前，
		//就相当于均分这一段空格
		int spaceControlTemp = spaceControl / (countnum[i]+2);

		while (tempCount > 0)
		{
			deQueue(qu, p);
			if (p->sonCount == 0)
				printf(" ");
			//出队上一层的结点，让其所有的孩子入队，并打印孩子值
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
	//	//输出第i层的结点
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