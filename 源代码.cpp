#pragma warning(disable:4996)

#include <stdio.h>
#include <stdlib.h>

#define MaxSize 20

typedef struct node               
{
	char data;                    //节点的值
	int ab=0;                     //横坐标，全部初始化为0
	int lay = 0;                  //层数，全部初始化为0
	struct node *xp;              //指向兄弟
	struct node *hp;              //指向孩子
}TSBNode;                         //孩子兄弟链存储结构中的节点类型 

typedef struct
{
	TSBNode * data[MaxSize];      //存放队中元素
	int front, rear;              //队头和队尾指针
}SqQueue;                         //环形队类型

void InitQueue(SqQueue * &q)                   //初始化队列
{
	q = (SqQueue *)malloc(sizeof(SqQueue));
	q->front = NULL;
	q->rear = NULL;
}

//函数
void DestroyQueue(SqQueue *&q)                 //销毁队列
{
	free(q);
}

bool enQueue(SqQueue *&q, TSBNode *e)          //进队列
{
	if ((q->rear + 1) % MaxSize == q->front)
		return false;
	q->rear = (q->rear + 1) % MaxSize;
	q->data[q->rear] = e;
	return true;
}

bool deQueue(SqQueue *&q, TSBNode *&e)          //出队列
{
	if (q->front == q->rear)
		return false;
	q->front = (q->front + 1) % MaxSize;
	e = q->data[q->front];
	return true;
}

bool Match(char *str)                           //检查输入字符串是否符合规范
{
	bool match=true;
	char ch,St[MaxSize];
	int top = -1;                               //top是顺序栈数组的下标，相当于栈顶指针
	int i= 0;                                   //i是字符串下标，相当于字符指针
	ch = str[i];
	while (ch != '\0')                          //循环遍历字符串中每个字符
	{
		switch (ch)
		{
		case '(':top++; St[top] = ch; break;     //当前字符为左括号，将其进栈
		case ')':                                //当前字符为右括号
			if (top != -1)                       //栈顶元素不为空
					{
						if (St[top] != '(')	     //栈顶元素不为左括号
							match = false;       //表示不匹配
						else top--;              //栈顶元素为左括号，将左括号出栈
					}
			else match = false;                  //栈顶元素为空表示不匹配
			break;                   
		default: break;
		}
		i++;
		ch = str[i];
	}
	if (top != -1)                                //栈中元素未取完
		match = false;                            //表示不匹配
	return match;
}

void CreateTree(TSBNode *&b, char *str)            //创建以孩子兄弟链存储的树
{
	TSBNode *St[80], *p;
	int top = -1;                                 //top是顺序栈数组的下标，相当于栈顶指针
	int k=0;                                      //k是哨兵，用于区分孩子结点和兄弟节点
	int j = 0;                                    //j是字符串下标，相当于字符指针
	char ch;
	b = NULL;
	p = NULL;
	ch = str[j];
	while (ch != '\0')                            //循环遍历字符串中每个字符
	{
		switch (ch)
		{
			case '(':k = 1; break;                    //置哨兵k为1，孩子节点
			case ')': top--; break;                   //出栈
			case ',':k = 2; break;                    //置哨兵k为2，兄弟结点
			default:p = (TSBNode *)malloc(sizeof(TSBNode));   //创建新节点
			p->data = ch;
			p->xp = p->hp = NULL;
			if (b == NULL)                        //根节点进栈
			{ 
				b = p; top++; St[top] = p;
			}
			else
			{
				switch (k)
				{
				case 1:St[top]->hp = p; top++; St[top] = p; break;   //孩子节点进栈
				case 2:St[top]->xp = p; St[top] = p; break;          //更换栈顶元素！
				}
			}
		}
		j++;
		ch = str[j];
	}
}

int Width(TSBNode *b)                  //各节点在输出时所占的宽度
{
	TSBNode *p;
	int n;                            //宽度
	if (b->hp == NULL)
		return 4;                     //每一个叶子节点宽度为4，即空格{data}
	else
	{
		p = b->hp;                    
		if (p->xp == NULL)            //递归计算没有兄弟节点的结点的宽度
			return Width(p);
		else
		{
			n = Width(p);
			while (p->xp != NULL)
			{
				n = n + Width(p->xp); //递归计算有兄弟节点的节点的宽度
				p = p->xp;
			}
			return n;
		}
	}
}

void Layer(TSBNode *b, int n)          //各节点在树中的层数，根节点为第1层
{
	TSBNode *p;
	b->lay = n;
	p = b->hp;
	while (p != NULL)
	{
		Layer(p, n + 1);               //递归计算各节点的层数
		p = p->xp;
	}
}

void Coordinate(TSBNode *&b, int x)               //给每个结点一个横坐标，根节点横坐标为1,左对齐输出
{
	TSBNode *p;
	b->ab = x;
	p = b->hp;
	if (p != NULL)                          
	{
		Coordinate(p, x);                         //递归计算b的第一个孩子结点的横坐标=b坐标
		while (p->xp != NULL)
		{
			Coordinate(p->xp, p->ab + Width(p));  //递归计算p的兄弟结点横坐标=p的横坐标+p的宽度
			p = p->xp;
		}
	}
}

void Center(TSBNode *&b)                  //重新计算横坐标使结点居中对齐
{
	TSBNode *p;
	int a;                                //计算双亲节点的横坐标，使其位于它的所有孩子结点正中间
	if (b->hp != NULL)                    //若b有孩子结点
	{
		p = b->hp;
		Center(p);                       //递归计算b的第一个孩子结点横坐标
		a = p->ab;                       //a是第一个孩子结点横坐标
		while (p->xp != NULL)
		{
			p = p->xp;
			Center(p);                   //递归得到p所有兄弟结点居中后的横坐标
		}                                //循环结束后p指向b的最后一个孩子结点
		b->ab = (a + p->ab)/ 2;          //b横坐标=（b第一个孩子横坐标+b最后一个孩子横坐标）/2
	}
}

void PrintTree(TSBNode *&b)              //按要求输出树
{
	SqQueue * q;                         //环形队列
	TSBNode * p;
	int a = 1;                           //a是初始输出的横坐标，初始值为1
	InitQueue(q);                        //初始化环形队列
    //q->data[q->front] = NULL;
	enQueue(q, b);
	do
	{
		deQueue(q, p);                   //出队
		if (p==b)                        //如果p为根结点
		{
			for (; a < (p->ab - 1); a++)
				printf(" ");
			printf("{%c}", p->data);
		}
		else
		{
			if (q->data[(q->front - 1 + MaxSize) % MaxSize]->xp == NULL) //若p为第一个孩子结点，则在队列中p的前一结点没有兄弟）
			{
				for (; a < (p->ab - 1); a++)
					printf(" ");
				printf("{%c", p->data);
				a = a + 2;                          //已经输出{和data两个字符，要将当前横坐标向后移两位
				if (p->xp == NULL)                  //若p是唯一的孩子
				{
					printf("}");
					a++;                            //已经输出}一个字符，要将当前横坐标向后移一位
				}
			}
			else if (p->xp != NULL)                 //若p是中间孩子
			{
				for (; a < p->ab; a++)
					printf(" ");
				printf("%c", p->data);
				a++;                                //已经输出data一个字符，要将当前横坐标向后移一位
			}
			else                                    //若p是最后一个孩子
			{
				for (; a < p->ab; a++)
					printf(" ");
				printf("%c}", p->data);
				a = a + 2;                          //已经输出data和}两个字符，要将当前横坐标向后移一位
			}
			
		}
		if ((q->front == q->rear) || (p->lay == q->data[(q->front + 1) % MaxSize]->lay - 1)) //如果队空或者某一层输出完毕
		{
			printf("\n");         //换行
			a = 1;                //将横坐标重新初始化为1
		}
		p = p->hp;                //处理p的孩子结点
		while (p != NULL)
		{
			enQueue(q, p);        //使p的所有兄弟结点入队
			p = p->xp;
		}
	} while (q->front != q->rear);//当队列为空时循环结束
	DestroyQueue(q);              //销毁队列
}

void DestroyTree(TSBNode *&b)    //销毁孩子兄弟链
{
	if (b == NULL)  
	{
		free(b);                //当b为空，释放b
		return;
	}
	DestroyTree(b->xp);         //递归销毁b的所有兄弟树
	DestroyTree(b->hp);         //递归销毁b的所有孩子树
	free(b);                    //释放b
}

int main()
{
	char s[80];
	printf("请用广义表格式输入一棵树：\n");
	scanf("%s",s);
	if (!Match(s))
	{
		printf("输入格式错误！\n\n");
		main();
	}
	else
	{
		printf("\n您输入的树展示为：\n\n");
		TSBNode *b;
		CreateTree(b, s);           //创建以孩子兄弟链存储的树
		Layer(b, 1);                //各节点在树中的层数
		Coordinate(b, 1);           //左对齐 
		Center(b);                  //居中对齐
		PrintTree(b);               //居中对齐格式输出一棵树
		DestroyTree(b);             //销毁一棵树
	}
	system("pause");
	return 0;
}