#ifndef BINARYTREE_H
#define BINARYTREE_H

#include <iostream>
#include <QString>

#define STACK_INIT_SIZE 100
#define STACKINCREMENT  10


#define TRUE		1
#define FALSE		0
#define OK		1
#define ERROR		0
#define INFEASIBLE	-1
#define LOVERFLOW	-2


typedef  int  TElemType;
typedef  int  Status;

enum PointerTag{Link,Thread};//Link==0:指针，Thread==1:线索

class BinaryTree;

class BiTNode {
public:
	TElemType data;
	BiTNode *lchild;
	BiTNode *rchild;
	BiTNode *parent;
	PointerTag LTag;
	PointerTag RTag;
	//int CurrentLevel;
	/*int*/double x_node;
	/*int*/double y_node;

	BiTNode();
	friend class BinaryTree;
};

//typedef int QElemType;				//可根据需要修改元素的类型

#define MAXQSIZE 100				//最大队列长度
template <typename QElemType>
class SqQueue
{
protected:
	QElemType *base;				//初始化的动态分配存储空间
	int front;						//头指针，若队列不空，指向队列头元素
	int rear;						//尾指针，若队列不空，指向队列尾元素的下一个位置
public:
	SqQueue();						//构造函数，构造一个空队列
	~SqQueue();						//析构函数，销毁一个队列
	Status QueueEmpty();			//若队列Q为空队列，则返回TRUE，否则返回FALSE
	Status GetHead(QElemType &e);	//若队列不空，则用e返回Q的队头元素，并返回OK，否则返回ERROR
	Status EnQueue(QElemType e);	//插入元素e为Q的新的队尾元素
	Status DeQueue(QElemType &e);	//若队列不空，则删除Q的队头元素，用e返回其值，并返回OK，否则返回ERROR
};

template<typename QElemType>
SqQueue<QElemType>::SqQueue()
{
	base = new QElemType[MAXQSIZE];
	if (!base)
		exit(OVERFLOW);
	front = rear = 0;
}

template<typename QElemType>
SqQueue<QElemType>::~SqQueue()
{
	if (base)
		delete base;
}

template<typename QElemType>
Status SqQueue<QElemType>::QueueEmpty()
{
	if (front == rear)
		return TRUE;
	else
		return FALSE;
}

template<typename QElemType>
Status SqQueue<QElemType>::GetHead(QElemType &e)
{
	if (front == rear)
		return ERROR;
	e = base[front];
	return OK;
}

template<typename QElemType>
Status SqQueue<QElemType>::EnQueue(QElemType e)
{
	if ((rear + 1) % MAXQSIZE == front)
		return ERROR;
	base[rear] = e;
	rear = (rear + 1) % MAXQSIZE;
	return OK;
}

template<typename QElemType>
Status SqQueue<QElemType>::DeQueue(QElemType &e)
{
	if (front == rear)
		return ERROR;
	e = base[front];
	front = (front + 1) % MAXQSIZE;
	return OK;
}

class BinaryTree {
public:
	BiTNode *root;
	BiTNode *head;
	BiTNode *pre;
	BinaryTree();
	Status CreateBinaryTree(BiTNode **p, SqQueue<int> &q);		//构造二叉链表表示的二叉树
	Status PreOrderTraverse(BiTNode *p, QString *display);		//先序遍历
	Status InOrderTraverse(BiTNode *p, QString *display);		//中序遍历
	Status PostOrderTraverse(BiTNode *p,QString *display);	    //后序遍历
	//Status LevelOrderTraverse();								//层次遍历
	int BiTreeDepth(BiTNode *p);								//返回二叉树的深度
	int NodeDepth(BiTNode *p);									//返回当前结点深度
	//int Num_of_points(BiTNode *p);							//返回二叉树总结点数
	int Num_of_leaves(BiTNode *p);								//返回二叉树叶子节点数
	//Status copy_BiTree(BiTNode *p,BiTNode **q);				//二叉树的复制,p为要复制的节点指针，q为接受复制的节点指针
	Status Add_parent(BiTNode *p);								//给二叉树加入双亲域
	Status PreOrderThreading();									//先序头结点线索化
	void PreThreading(BiTNode *q);								//先序根节点线索化
	Status InOrderThreading();									//中序头结点线索化
	void InThreading(BiTNode *q);								//中序根节点线索化
	Status PostOrderThreading();								//后序头结点线索化
	void PostThreading(BiTNode *q);								//后序根节点线索化
	Status PreOrderTraverse_Thr(BiTNode *t,QString &display);	//先序线索遍历，t指向头结点
	Status InOrderTraverse_Thr(BiTNode *t,QString &display);	//中序线索遍历，t指向头结点
	Status PostOrderTraverse_Thr(BiTNode *t,QString &display);	//后序线索遍历，t指向头结点
};

#endif // BINARYTREE_H
