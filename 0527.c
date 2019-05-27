#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#define MAXSIZE 100

typedef char DataType;
typedef struct BiTNode /* 二叉链表存储结构 */
{
	DataType data;
	struct BiTNode *lchild, *rchild;
}BiTree;

typedef BiTree* ElemType; /* 栈中数据元素类型，栈中保存结点指针 */
typedef struct
{
	ElemType data[MAXSIZE];
	int top;
}SeqStack; /* 栈的类型定义，顺序栈 */

typedef struct
{
	ElemType queue[MAXSIZE];
	int front, rear;
}SP;

SeqStack *initSeqStack() /* 初始化栈 */
{
	SeqStack *s; /* 首先建立栈空间，然后初始化栈顶指针 */
	s = (SeqStack*)malloc(sizeof(SeqStack));
	s->top = -1;
	return s;
}

int push(SeqStack *s, ElemType x)
{
	if (s->top == MAXSIZE - 1){ /* 栈满不能入栈 */
		printf("栈满");
		return 0;
	}
	s->top++;
	s->data[s->top] = x;
	return 1;
}

void pop(SeqStack *s) /* 出栈，假设栈不空 */
{
	s->top--;
}

int empty(SeqStack *s)
{
	if (s->top == -1) return 1;
	else return 0;
}

ElemType top(SeqStack *s) /* 设栈不空 */
{
	return (s->data[s->top]);
}

/* 递归算法创建二叉链表 */
BiTree *createBiTree()
{
	DataType ch;
	BiTree *T;
	ch = getchar();
	if (ch == '0')
		return NULL;
	else {
		T = (BiTree *)malloc(sizeof(BiTree));
		T->data = ch;
		T->lchild = createBiTree();
		T->rchild = createBiTree();
		return T;
	}
}

/* 中序遍历二叉树的递归算法 */
void InOrder(BiTree *T)
{
	if (T)
	{
		InOrder(T->lchild);
		printf(" %c", T->data);
		InOrder(T->rchild);
	}
}

/* 前序遍历二叉树的递归算法 */
void PreOrder(BiTree *T)
{
	if (T)
	{
		printf(" %c", T->data);
		PreOrder(T->lchild);
		PreOrder(T->rchild);
	}
}

/* 后序遍历二叉树的递归算法 */
void PostOrder(BiTree *T)
{
	if (T)
	{
		PostOrder(T->lchild);
		PostOrder(T->rchild);
		printf(" %c", T->data);
	}
}

/* 中序遍历二叉树的非递归算法 */
void InOrderFei(BiTree *p)
{
	SeqStack *s; s = initSeqStack();
	while (1)
	{
		while (p) {
			push(s, p); p = p->lchild;
		} /* 先将结点指针压栈，待出栈时再访问 */
		if (empty(s))
			break;
		p = top(s); pop(s); printf(" %c", p->data);
		p = p->rchild;
	}
}

void LevelOrder(BiTree *T)
{
	SP *p;
	p = (SP*)malloc(sizeof(SP));
	p->front = 0;
	p->rear = 0;
	if (T != NULL){
		p->queue[p->front] = T;
		p->front = p->front + 1;
	}
	while (p->front != p->rear){
		T = p->queue[p->rear];
		p->rear = p->rear + 1;
		printf("%c", T->data);
		if (T->lchild != NULL){
			p->queue[p->front] = T->lchild;/*左孩子进队列*/
			p->front = p->front + 1;
		}
		if (T->rchild != NULL){
			p->queue[p->front] = T->rchild;/*右孩子进队列*/
			p->front = p->front + 1;
		}
	}
}

/* 求二叉树的高度 */
int height(BiTree *T)
{
	int i, j;
	if (!T) return 0;
	i = height(T->lchild); /* 求左子树的高度 */
	j = height(T->rchild); /* 求右子树的高度 */
	return i>j ? i + 1 : j + 1; /* 二叉树的高度为左右子树中较高的高度加1 */
}

/* 求二叉树的所有结点个数 */
int Nodes(BiTree *T)
{
	int n1, n2;
	if (T == NULL) return 0;
	else if (T->lchild == NULL&&T->rchild == NULL)
		return 1;
	else {
		n1 = Nodes(T->lchild);
		n2 = Nodes(T->rchild);
		return n1 + n2 + 1;
	}
}

/* 求二叉树的叶子结点个数 */
int leafs(BiTree *T)
{
	int num1, num2;
	if (T == NULL)
		return 0;
	else{
		if (T->lchild == NULL&&T->rchild == NULL)
			return 1;
		num1 = leafs(T->lchild); /* 求左子树中叶子结点数 */
		num2 = leafs(T->rchild); /* 求右子树中叶子结点数 */
		return num1 + num2;
	}
}

/* 交换二叉树的所有左右子树 */
void exchange(BiTree *T)
{
	BiTree *temp = NULL;
	if (T->lchild == NULL&&T->rchild == NULL) return;
	else{
		temp = T->lchild;
		T->lchild = T->rchild;
		T->rchild = temp;
	}
	if (T->lchild)
		exchange(T->lchild);
	if (T->rchild)
		exchange(T->rchild);
}

/* 交换后二叉树的遍历 */
void Display(BiTree *T)
{
	printf("\n交换后二叉树按前序遍历输出:");
	PreOrder(T);
	printf("\n");
	printf("\n交换后二叉树按中序遍历输出:");
	InOrder(T);
	printf("\n");
	printf("\n交换后二叉树按后序遍历输出:");
	PostOrder(T);
	printf("\n");
}

void menu()
{
	printf("****************************************\n");
	printf("  1.建立二叉树的二叉链表                \n");
	printf("  2.二叉树的中序递归遍历算法            \n");
	printf("  3.二叉树的中序非递归遍历算法          \n");
	printf("  4.借助队列实现二叉树的层次遍历算法    \n");
	printf("  5.二叉树的高度                        \n");
	printf("  6.二叉树的结点个数                    \n");
	printf("  7.二叉树的叶子个数                    \n");
	printf("  8.交换二叉树每个结点的左子树和右子树  \n");
	printf("  0.退出系统                            \n");
	printf("****************************************\n");
	printf(" \n请选择:");
}

void main()
{
	BiTree *bt; bt = NULL;
	int n, m = 1;
	while (m){
		menu();
		scanf("%d", &n);
		getchar();
		switch (n){
		case 1:{
				   printf("\n请输入结点的前序序列创建二叉树:0表示空:");
				   bt = createBiTree();
				   break;
		}/* 生成二叉树 */

		case 2:{
				   printf("\n二叉树的中序递归遍历:");
				   InOrder(bt);
				   printf("\n");
				   break;
		}

		case 3:{
				   printf("\n二叉树的中序非递归遍历:");
				   InOrderFei(bt);
				   printf("\n");
				   break;
		}

		case 4:{
				   printf("\n二叉树的层次遍历:");
				   LevelOrder(bt);
				   printf("\n");
				   break;
		}
		case 5:{
				   printf("\n二叉树的高度为: %d\n", height(bt));
				   printf("\n");
				   break;
		}
		case 6:{
				   printf("\n二叉树的结点数为: %d\n", Nodes(bt));
				   printf("\n");
				   break;
		}
		case 7:{
				   printf("\n二叉树中叶子结点数为: %d\n", leafs(bt));
				   break;
		}
		case 8:{
				   printf("\n交换二叉树的左子树和右子树：");
				   printf("\n");
				   exchange(bt);
				   Display(bt);
				   break;
		}
		case 0:
			m = 0;
		}
	}
	system("pause");
}