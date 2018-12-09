#pragma warning(disable:4996)

#include <stdio.h>
#include <stdlib.h>

#define MaxSize 20

typedef struct node               
{
	char data;                    //�ڵ��ֵ
	int ab=0;                     //�����꣬ȫ����ʼ��Ϊ0
	int lay = 0;                  //������ȫ����ʼ��Ϊ0
	struct node *xp;              //ָ���ֵ�
	struct node *hp;              //ָ����
}TSBNode;                         //�����ֵ����洢�ṹ�еĽڵ����� 

typedef struct
{
	TSBNode * data[MaxSize];      //��Ŷ���Ԫ��
	int front, rear;              //��ͷ�Ͷ�βָ��
}SqQueue;                         //���ζ�����

void InitQueue(SqQueue * &q)                   //��ʼ������
{
	q = (SqQueue *)malloc(sizeof(SqQueue));
	q->front = NULL;
	q->rear = NULL;
}

//����
void DestroyQueue(SqQueue *&q)                 //���ٶ���
{
	free(q);
}

bool enQueue(SqQueue *&q, TSBNode *e)          //������
{
	if ((q->rear + 1) % MaxSize == q->front)
		return false;
	q->rear = (q->rear + 1) % MaxSize;
	q->data[q->rear] = e;
	return true;
}

bool deQueue(SqQueue *&q, TSBNode *&e)          //������
{
	if (q->front == q->rear)
		return false;
	q->front = (q->front + 1) % MaxSize;
	e = q->data[q->front];
	return true;
}

bool Match(char *str)                           //��������ַ����Ƿ���Ϲ淶
{
	bool match=true;
	char ch,St[MaxSize];
	int top = -1;                               //top��˳��ջ������±꣬�൱��ջ��ָ��
	int i= 0;                                   //i���ַ����±꣬�൱���ַ�ָ��
	ch = str[i];
	while (ch != '\0')                          //ѭ�������ַ�����ÿ���ַ�
	{
		switch (ch)
		{
		case '(':top++; St[top] = ch; break;     //��ǰ�ַ�Ϊ�����ţ������ջ
		case ')':                                //��ǰ�ַ�Ϊ������
			if (top != -1)                       //ջ��Ԫ�ز�Ϊ��
					{
						if (St[top] != '(')	     //ջ��Ԫ�ز�Ϊ������
							match = false;       //��ʾ��ƥ��
						else top--;              //ջ��Ԫ��Ϊ�����ţ��������ų�ջ
					}
			else match = false;                  //ջ��Ԫ��Ϊ�ձ�ʾ��ƥ��
			break;                   
		default: break;
		}
		i++;
		ch = str[i];
	}
	if (top != -1)                                //ջ��Ԫ��δȡ��
		match = false;                            //��ʾ��ƥ��
	return match;
}

void CreateTree(TSBNode *&b, char *str)            //�����Ժ����ֵ����洢����
{
	TSBNode *St[80], *p;
	int top = -1;                                 //top��˳��ջ������±꣬�൱��ջ��ָ��
	int k=0;                                      //k���ڱ����������ֺ��ӽ����ֵܽڵ�
	int j = 0;                                    //j���ַ����±꣬�൱���ַ�ָ��
	char ch;
	b = NULL;
	p = NULL;
	ch = str[j];
	while (ch != '\0')                            //ѭ�������ַ�����ÿ���ַ�
	{
		switch (ch)
		{
			case '(':k = 1; break;                    //���ڱ�kΪ1�����ӽڵ�
			case ')': top--; break;                   //��ջ
			case ',':k = 2; break;                    //���ڱ�kΪ2���ֵܽ��
			default:p = (TSBNode *)malloc(sizeof(TSBNode));   //�����½ڵ�
			p->data = ch;
			p->xp = p->hp = NULL;
			if (b == NULL)                        //���ڵ��ջ
			{ 
				b = p; top++; St[top] = p;
			}
			else
			{
				switch (k)
				{
				case 1:St[top]->hp = p; top++; St[top] = p; break;   //���ӽڵ��ջ
				case 2:St[top]->xp = p; St[top] = p; break;          //����ջ��Ԫ�أ�
				}
			}
		}
		j++;
		ch = str[j];
	}
}

int Width(TSBNode *b)                  //���ڵ������ʱ��ռ�Ŀ��
{
	TSBNode *p;
	int n;                            //���
	if (b->hp == NULL)
		return 4;                     //ÿһ��Ҷ�ӽڵ���Ϊ4�����ո�{data}
	else
	{
		p = b->hp;                    
		if (p->xp == NULL)            //�ݹ����û���ֵܽڵ�Ľ��Ŀ��
			return Width(p);
		else
		{
			n = Width(p);
			while (p->xp != NULL)
			{
				n = n + Width(p->xp); //�ݹ�������ֵܽڵ�Ľڵ�Ŀ��
				p = p->xp;
			}
			return n;
		}
	}
}

void Layer(TSBNode *b, int n)          //���ڵ������еĲ��������ڵ�Ϊ��1��
{
	TSBNode *p;
	b->lay = n;
	p = b->hp;
	while (p != NULL)
	{
		Layer(p, n + 1);               //�ݹ������ڵ�Ĳ���
		p = p->xp;
	}
}

void Coordinate(TSBNode *&b, int x)               //��ÿ�����һ�������꣬���ڵ������Ϊ1,��������
{
	TSBNode *p;
	b->ab = x;
	p = b->hp;
	if (p != NULL)                          
	{
		Coordinate(p, x);                         //�ݹ����b�ĵ�һ�����ӽ��ĺ�����=b����
		while (p->xp != NULL)
		{
			Coordinate(p->xp, p->ab + Width(p));  //�ݹ����p���ֵܽ�������=p�ĺ�����+p�Ŀ��
			p = p->xp;
		}
	}
}

void Center(TSBNode *&b)                  //���¼��������ʹ�����ж���
{
	TSBNode *p;
	int a;                                //����˫�׽ڵ�ĺ����꣬ʹ��λ���������к��ӽ�����м�
	if (b->hp != NULL)                    //��b�к��ӽ��
	{
		p = b->hp;
		Center(p);                       //�ݹ����b�ĵ�һ�����ӽ�������
		a = p->ab;                       //a�ǵ�һ�����ӽ�������
		while (p->xp != NULL)
		{
			p = p->xp;
			Center(p);                   //�ݹ�õ�p�����ֵܽ����к�ĺ�����
		}                                //ѭ��������pָ��b�����һ�����ӽ��
		b->ab = (a + p->ab)/ 2;          //b������=��b��һ�����Ӻ�����+b���һ�����Ӻ����꣩/2
	}
}

void PrintTree(TSBNode *&b)              //��Ҫ�������
{
	SqQueue * q;                         //���ζ���
	TSBNode * p;
	int a = 1;                           //a�ǳ�ʼ����ĺ����꣬��ʼֵΪ1
	InitQueue(q);                        //��ʼ�����ζ���
    //q->data[q->front] = NULL;
	enQueue(q, b);
	do
	{
		deQueue(q, p);                   //����
		if (p==b)                        //���pΪ�����
		{
			for (; a < (p->ab - 1); a++)
				printf(" ");
			printf("{%c}", p->data);
		}
		else
		{
			if (q->data[(q->front - 1 + MaxSize) % MaxSize]->xp == NULL) //��pΪ��һ�����ӽ�㣬���ڶ�����p��ǰһ���û���ֵܣ�
			{
				for (; a < (p->ab - 1); a++)
					printf(" ");
				printf("{%c", p->data);
				a = a + 2;                          //�Ѿ����{��data�����ַ���Ҫ����ǰ�������������λ
				if (p->xp == NULL)                  //��p��Ψһ�ĺ���
				{
					printf("}");
					a++;                            //�Ѿ����}һ���ַ���Ҫ����ǰ�����������һλ
				}
			}
			else if (p->xp != NULL)                 //��p���м亢��
			{
				for (; a < p->ab; a++)
					printf(" ");
				printf("%c", p->data);
				a++;                                //�Ѿ����dataһ���ַ���Ҫ����ǰ�����������һλ
			}
			else                                    //��p�����һ������
			{
				for (; a < p->ab; a++)
					printf(" ");
				printf("%c}", p->data);
				a = a + 2;                          //�Ѿ����data��}�����ַ���Ҫ����ǰ�����������һλ
			}
			
		}
		if ((q->front == q->rear) || (p->lay == q->data[(q->front + 1) % MaxSize]->lay - 1)) //����ӿջ���ĳһ��������
		{
			printf("\n");         //����
			a = 1;                //�����������³�ʼ��Ϊ1
		}
		p = p->hp;                //����p�ĺ��ӽ��
		while (p != NULL)
		{
			enQueue(q, p);        //ʹp�������ֵܽ�����
			p = p->xp;
		}
	} while (q->front != q->rear);//������Ϊ��ʱѭ������
	DestroyQueue(q);              //���ٶ���
}

void DestroyTree(TSBNode *&b)    //���ٺ����ֵ���
{
	if (b == NULL)  
	{
		free(b);                //��bΪ�գ��ͷ�b
		return;
	}
	DestroyTree(b->xp);         //�ݹ�����b�������ֵ���
	DestroyTree(b->hp);         //�ݹ�����b�����к�����
	free(b);                    //�ͷ�b
}

int main()
{
	char s[80];
	printf("���ù�����ʽ����һ������\n");
	scanf("%s",s);
	if (!Match(s))
	{
		printf("�����ʽ����\n\n");
		main();
	}
	else
	{
		printf("\n���������չʾΪ��\n\n");
		TSBNode *b;
		CreateTree(b, s);           //�����Ժ����ֵ����洢����
		Layer(b, 1);                //���ڵ������еĲ���
		Coordinate(b, 1);           //����� 
		Center(b);                  //���ж���
		PrintTree(b);               //���ж����ʽ���һ����
		DestroyTree(b);             //����һ����
	}
	system("pause");
	return 0;
}