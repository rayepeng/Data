#include <stdio.h>
#include <stdlib.h>

struct Tree
{
	int count_leaf;  //子代结点中叶子结点的数目
	char data;
	int level;       //当前结点在多叉树中的层数
	Tree* lchild;
	Tree* rchild;
};
int get_level(char* input)
{
	int level = 1;
	int level_max = 1;
	while(('0'<=*input && *input<='9') || *input == '(' || *input == ')' || *input == ',')
	{
		if(*input == '(')
		{
			level++;
			if(level>level_max)
			{
				level_max = level;
			}
		}
		else if(*input == ')')
		{
			level--;
		}
		input++;
	}
	return level_max;
}
int get_node_leaf(Tree* head)
{
	if(head->lchild == NULL)
	{
		head->count_leaf = 1;
	}
	else if(head->lchild->data == '!')
		head->count_leaf = 1;
	else
	{
		Tree* node = (Tree*)calloc(1,sizeof(Tree));
		node = head->lchild;
		head->count_leaf += node->count_leaf;
		while(node->rchild)
		{
			node = node->rchild;
			head->count_leaf += node->count_leaf;
		}
	}
	return 1;
}
int get_space_node(Tree* head, int level_max)
{
	head->count_leaf = 1;
	int little_brother = 0;
	if(!head->rchild)
		little_brother = 1;
	while(head->level != level_max)
	{
		Tree* empty = (Tree*)calloc(1,sizeof(Tree));
		empty->count_leaf = 1;
		head->lchild = empty;
		empty->lchild = NULL;
		empty->rchild = NULL;
		empty->level = head->level + 1;
		empty->data = '!';
		head = head->lchild;
	}
	return 1;
}
char* analyse(char* input,Tree* head, int level_max)
{
	while(*input != ')')
	{
		Tree* child = (Tree*)calloc(1,sizeof(Tree));
		child->lchild = NULL;
		child->rchild = NULL;
		if(*input == '(')
		{
			input++;
			child->level = head->level+1;
			head->lchild = child;
			child->data = *input;
			input++;
			input = analyse(input,child,level_max); 
		}
		if(*input == ',')
		{
			Tree* brother = (Tree*)calloc(1,sizeof(Tree));
			brother->lchild = NULL;
			brother->rchild = NULL;
			brother->count_leaf = 0;
			input++;
			brother->level = head->level;
			head->rchild = brother;
			brother->data = *input;
			input++;
			while(*input>='0' && *input<='9')
			{
				brother->data = brother->data*10 + *input;
				input++;
			}
			if(head->lchild == NULL)
				get_space_node(head,level_max);
			get_node_leaf(head);
			head = brother;
		}
	}
	get_node_leaf(head);
	if(*input == ')' && head->lchild == NULL)
		get_space_node(head,level_max);
	input++;
	return input;
}
int print(Tree* head)
{
	Tree** nex = (Tree**)calloc(1,sizeof(Tree*));
	int skip_head = 1;  //跳过头结点的输出过程
	int i = 0;
	int flag = 0;
	Tree** front = (Tree**)calloc(1,sizeof(Tree*));
	Tree** rear = front;
	*front = head;
	*rear++;
	Tree* node = (Tree*)calloc(1,sizeof(Tree));
	do
	{
		if((*front)->data == '{')
		{
			flag = 1;
			front++;
		}
		if((*front)->lchild)
		{
			node = (*front)->lchild;
			int level = node->level;
			if((*front)->lchild->data != '!' && (*front)->lchild->data != '#')
			{
				Tree* pro = (Tree*)calloc(1,sizeof(Tree));
				pro->lchild = NULL;
				pro->rchild = NULL;
				pro->data = '{';
				pro->count_leaf = -1;
				*rear = pro;
				rear++;
				pro->level = level;
			}
			*rear = node;
			rear++;
			while(node->rchild)
			{
				node = node->rchild;
				*rear = node;
				rear++;
			}
			if((*front)->lchild->data != '!' && (*front)->lchild->data != '#')
			{
				Tree* nex = (Tree*)calloc(1,sizeof(Tree));
				nex->rchild = NULL;
				nex->lchild = NULL;
				nex->data = '}';
				nex->level = level;
				nex->count_leaf = -1;
				*rear = nex;
				rear++;
			}
		}
		if(skip_head)
		{
			front++;
			skip_head=0;
			continue;
		}
		if((*front)->count_leaf > 1)
		{
			i = 3*((*front)->count_leaf)/2 - 1;
			while(i)
			{
				printf(" ");
				i--;
			}
		}
		if((*front)->data == '!')
			printf("   ");
		else
		{
			if(flag)
			{
				flag = 0;
				printf("{");
			}
			if((*front)->count_leaf != -1)
				printf("%c",(*front)->data);
			nex = front+1;
			if((*nex)->data == '}')
				printf("}");
			else if((*nex)->data != '{' && (*nex)->data != '!' && (*nex)->data != '#')		
			{			
				printf("  ");
			}
		}
		if((*front)->count_leaf >1)
		{
			if((*front)->count_leaf%2)
				i = 3*((*front)->count_leaf)/2 - 1;
			else
				i = 3*((*front)->count_leaf)/2 - 2;
			while(i)
			{
				printf(" ");
				i--;
			}
		}
		node = *front;
		front++;
		if(rear != front)
		{
			if((*front)->level != node->level)
			{
				printf("\n");
			}
		}
		else
			break;
	}while(1);
	return 1;
}
int free_node(Tree* head)
{
	if(!head)
		return 1;
	if(head->lchild)
		free_node(head->lchild);
	if(head->rchild)
		free_node(head->rchild);
	free(head);
	return 1;
}
int main()
{
	Tree* head = (Tree*)calloc(1,sizeof(Tree));
	int size_input = 100;
	char* input = (char*)calloc(size_input,sizeof(char));
	char* base = input;
	int count = 0;
	printf("please input the Tree:\n");
	scanf("%c",&*input);
	while(1)
	{
		input++;
		count++;
		scanf("%c",&*input);
		if(*input == 10)
			break;
		if(count == 100)
		{
			base = (char*)realloc(base,(size_input + 100) * sizeof(char));
			input = base + size_input;
			size_input += 100;
			count = 0;
		}
	}
	input = base;
	int level = get_level(input);
	input = base;
	head->level = 1;
	head->data = *input;
	input ++;
	head->lchild = NULL;
	if(*input == '(')
	{
		input++;
		Tree* child = (Tree*)calloc(1,sizeof(Tree));
		head->lchild = child;
		child->rchild = NULL;
		child->lchild = NULL;
		child->level = 2;
		child->data = *input;
		input++;
		analyse(input,child,level);
		get_node_leaf(head);
	}
	printf("\n\n");
	int i = 3*head->count_leaf/2 - 1;
	while(i>0)
	{
		printf(" ");
		i--;
	}
	printf("{%c}\n",head->data);
	print(head);
	printf("\n\n");
	free_node(head);
	system("pause");
	return 0;
}
//9(2(1,1(1)),4(1,3(2(2(1,1)),1)),3(1,1,1(1)))