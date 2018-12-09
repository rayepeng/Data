##### 数据结构大作业

> 解决如何存储的问题

第一个想法是用孩子兄弟链存储，然而当我将输入真正地转化为孩子兄弟链存储的时候，却不知道该如何用递归的形式输出，所以这个想法中途流产了，不得已采用了多叉链表的形式，即每一个结点都分配MaxSize个孩子结点，虽然这样存储的利用率特别低，但是奈何，所以不得已采用了这中形式。

```C++
typedef struct node
{
	int sonCount;
	char data;
	struct node *sons[MaxSize];
}TSonNode;
```



> 存储之后就是如何输出的问题，输出的问题很大，肯定是采用层次遍历输出

这其中的问题折磨了很久，首先要知道每一层有多少结点，对每一层进行循环，然后对每一层进行循环的时候，这个时候需要知道每一个结点究竟有多少个孩子结点，这个是由结构体中的`sonCount`来确定的。



> 如何确认空格， 来打印一颗漂亮的树？

这个真的有点难，所以我最终只实现了一部分，使得输出的样式基本能够被接受。

具体的函数实现如下：

```C++
void MyDebugOrderPrint(TSonNode *b)
{
	SqQueue *qu;
	TSonNode *p;
	InitQueue(qu);

	enQueue(qu, b);
	int spaceControl = 44;

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
		//就相当于均分这一段空格
		int spaceControlTemp = spaceControl / (countnum[i]+2);

		while (tempCount > 0)
		{
			deQueue(qu, p);
			if (p->sonCount == 0)//3,无孩子节点的空格控制
			{
				for (int i = 2; i < spaceControlTemp / (i-1); i++)
				{
					printf(" ");
				}
			}
			//出队上一层的结点，让其所有的孩子入队，并打印孩子值
			else
			{
				for (int i = 1; i < spaceControlTemp; i++)//1,起始点的空格控制
				{
					printf(" ");
				}
				printf("{");
				for (int j = 0; j < p->sonCount; j++)
				{
					for (int temp = 0; temp < spaceControlTemp/i; temp++)//2,元素间空格的控制
					{
						if (j != 0)
							printf(" ");
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

```

> 最后的结果

![1543752233527](H:\数据结构\数据结构第二次作业\输出结果.png)



> 最后放一个[dalao的代码](""H:\数据结构\数据结构第二次作业\main.cpp"")

