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

enum PointerTag{Link,Thread};//Link==0:ָ�룬Thread==1:����

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

//typedef int QElemType;				//�ɸ�����Ҫ�޸�Ԫ�ص�����

#define MAXQSIZE 100				//�����г���
template <typename QElemType>
class SqQueue
{
protected:
	QElemType *base;				//��ʼ���Ķ�̬����洢�ռ�
	int front;						//ͷָ�룬�����в��գ�ָ�����ͷԪ��
	int rear;						//βָ�룬�����в��գ�ָ�����βԪ�ص���һ��λ��
public:
	SqQueue();						//���캯��������һ���ն���
	~SqQueue();						//��������������һ������
	Status QueueEmpty();			//������QΪ�ն��У��򷵻�TRUE�����򷵻�FALSE
	Status GetHead(QElemType &e);	//�����в��գ�����e����Q�Ķ�ͷԪ�أ�������OK�����򷵻�ERROR
	Status EnQueue(QElemType e);	//����Ԫ��eΪQ���µĶ�βԪ��
	Status DeQueue(QElemType &e);	//�����в��գ���ɾ��Q�Ķ�ͷԪ�أ���e������ֵ��������OK�����򷵻�ERROR
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
	Status CreateBinaryTree(BiTNode **p, SqQueue<int> &q);		//������������ʾ�Ķ�����
	Status PreOrderTraverse(BiTNode *p, QString *display);		//�������
	Status InOrderTraverse(BiTNode *p, QString *display);		//�������
	Status PostOrderTraverse(BiTNode *p,QString *display);	    //�������
	//Status LevelOrderTraverse();								//��α���
	int BiTreeDepth(BiTNode *p);								//���ض����������
	int NodeDepth(BiTNode *p);									//���ص�ǰ������
	//int Num_of_points(BiTNode *p);							//���ض������ܽ����
	int Num_of_leaves(BiTNode *p);								//���ض�����Ҷ�ӽڵ���
	//Status copy_BiTree(BiTNode *p,BiTNode **q);				//�������ĸ���,pΪҪ���ƵĽڵ�ָ�룬qΪ���ܸ��ƵĽڵ�ָ��
	Status Add_parent(BiTNode *p);								//������������˫����
	Status PreOrderThreading();									//����ͷ���������
	void PreThreading(BiTNode *q);								//������ڵ�������
	Status InOrderThreading();									//����ͷ���������
	void InThreading(BiTNode *q);								//������ڵ�������
	Status PostOrderThreading();								//����ͷ���������
	void PostThreading(BiTNode *q);								//������ڵ�������
	Status PreOrderTraverse_Thr(BiTNode *t,QString &display);	//��������������tָ��ͷ���
	Status InOrderTraverse_Thr(BiTNode *t,QString &display);	//��������������tָ��ͷ���
	Status PostOrderTraverse_Thr(BiTNode *t,QString &display);	//��������������tָ��ͷ���
};

#endif // BINARYTREE_H
