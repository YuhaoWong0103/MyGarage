#include <iostream>

#define STACK_INIT_SIZE 100
#define STACKINCREMENT  10


#define TRUE		1
#define FALSE		0
#define OK		1
#define ERROR		0
#define INFEASIBLE	-1
#define OVERFLOW	-2


typedef  int  TElemType;
typedef  int  Status;

class BinaryTree;

class BiTNode {
protected:
	TElemType data;
	BiTNode *lchild;
	BiTNode *rchild;
public:
	friend class BinaryTree;
};

typedef BiTNode* QElemType;				//�ɸ�����Ҫ�޸�Ԫ�ص�����

#define MAXQSIZE 100				//�����г���
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

SqQueue::SqQueue()
{
	base = new QElemType[MAXQSIZE];
	if (!base)
		exit(OVERFLOW);
	front = rear = 0;
}

SqQueue::~SqQueue()
{
	if (base)
		delete base;
}

Status SqQueue::QueueEmpty()
{
	if (front == rear)
		return TRUE;
	else
		return FALSE;
}

Status SqQueue::GetHead(QElemType &e)
{
	if (front == rear)
		return ERROR;
	e = base[front];
	return OK;
}

Status SqQueue::EnQueue(QElemType e)
{
	if ((rear + 1) % MAXQSIZE == front)
		return ERROR;
	base[rear] = e;
	rear = (rear + 1) % MAXQSIZE;
	return OK;
}

Status SqQueue::DeQueue(QElemType &e)
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
	BinaryTree();
        Status CreateBinaryTree(BiTNode **p,int *data0,int i);		//������������ʾ�Ķ�����
	Status PreOrderTraverse(BiTNode *p);		//�������
	Status InOrderTraverse(BiTNode *p);			//�������
	Status PostOrderTraverse(BiTNode *p);		//�������
	Status LevelOrderTraverse();				//��α���
	int BiTreeDepth(BiTNode *p);				//���ض����������
	int Num_of_points(BiTNode *p);				//���ض������ܽ����
	int Num_of_leaves(BiTNode *p);				//���ض�����Ҷ�ӽڵ���
	Status copy_BiTree(BiTNode *p,BiTNode **q);	//�������ĸ���,pΪҪ���ƵĽڵ�ָ�룬qΪ���ܸ��ƵĽڵ�ָ��
};

BinaryTree::BinaryTree()
{
	root = NULL;
}

Status BinaryTree::CreateBinaryTree(BiTNode **p,int *data0,int i)
{
	//'-1'��Ϊ�յı�־
	/*int data0;
	cin >> data0;*/
	if (data0[i] == -1)
		*p = NULL;
	else {
		if (!(*p = new BiTNode))
			exit(OVERFLOW);
		(*p)->data = data0[i];
		CreateBinaryTree(&(*p)->lchild,data0,i+1);
		CreateBinaryTree(&(*p)->rchild,data0,i+1);
	}
	return OK;
}

Status BinaryTree::PreOrderTraverse(BiTNode *p)
{
	if (p) {
//		cout << p->data << " ";
		PreOrderTraverse(p->lchild);
		PreOrderTraverse(p->rchild);
	}
	else
		return OK;
}

Status BinaryTree::InOrderTraverse(BiTNode *p)
{
	if (p) {
		InOrderTraverse(p->lchild);
//		cout << p->data << " ";
		InOrderTraverse(p->rchild);
	}
	else
		return OK;
}

Status BinaryTree::PostOrderTraverse(BiTNode *p)
{
	if (p) {
		PostOrderTraverse(p->lchild);
		PostOrderTraverse(p->rchild);
//		cout << p->data << " ";
	}
	else
		return OK;
}

Status BinaryTree::LevelOrderTraverse()
{
	SqQueue sq;
	BiTNode *p;
	sq.EnQueue(root);
	while (!sq.QueueEmpty())
	{
		sq.DeQueue(p);
		if (p) {
			sq.EnQueue(p->lchild);
			sq.EnQueue(p->rchild);
//			cout << p->data << " ";
		}
	}
	return OK;
}

int BinaryTree::BiTreeDepth(BiTNode *p)
{
	int l_depth, r_depth, m_depth;
	l_depth = 0;
	r_depth = 0;
	if (p->lchild) {
		l_depth = BiTreeDepth(p->lchild);
	}
	if (p->rchild) {
		r_depth = BiTreeDepth(p->rchild);
	}
	m_depth = l_depth > r_depth ? l_depth : r_depth;
	return m_depth + 1;
}

int BinaryTree::Num_of_points(BiTNode *p)
{
	int num_of_lchild, num_of_rchild;
	num_of_lchild = 0;
	num_of_rchild = 0;
	if (p->lchild) {
		num_of_lchild = Num_of_points(p->lchild);
	}
	if (p->rchild) {
		num_of_rchild = Num_of_points(p->rchild);
	}
	return num_of_lchild + num_of_rchild + 1;
}

int BinaryTree::Num_of_leaves(BiTNode *p)
{
	int leaves_of_lchild, leaves_of_rchild;
	leaves_of_lchild = 0;
	leaves_of_rchild = 0;
	if (p->lchild) {
		leaves_of_lchild = Num_of_leaves(p->lchild);
	}
	if (p->rchild) {
		leaves_of_rchild = Num_of_leaves(p->rchild);
	}
	if (!p->lchild&&!p->rchild)
		return leaves_of_lchild + leaves_of_rchild + 1;
	else
		return leaves_of_lchild + leaves_of_rchild;
}

Status BinaryTree::copy_BiTree(BiTNode *p,BiTNode **q)
{
	if (p) {
		if (!(*q = new BiTNode))
			exit(OVERFLOW);
		(*q)->data = p->data;
		copy_BiTree(p->lchild, &(*q)->lchild);
		copy_BiTree(p->rchild, &(*q)->rchild);
	}
	else {
		*q = p;
	}
	return OK;
}
