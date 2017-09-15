#include "BinaryTree.h"



BiTNode::BiTNode()
{
	LTag = Link;
	RTag = Link;
	x_node = 0;
	y_node = 0;
	lchild = NULL;
	rchild = NULL;
	parent = NULL;
}


BinaryTree::BinaryTree()
{
	root = NULL;
	head = NULL;
	pre = NULL;
}

Status BinaryTree::CreateBinaryTree(BiTNode **p, SqQueue<int> &q)
{
	//'-1'作为空的标志
	//int data0;
	//cin >> data0;
	int data0;
	q.DeQueue(data0);
	if (data0 == -1)
		*p = NULL;
	else {
		if (!(*p = new BiTNode))
			exit(LOVERFLOW);
		(*p)->data = data0;
		CreateBinaryTree(&(*p)->lchild, q);
		CreateBinaryTree(&(*p)->rchild, q);
	}
	return OK;
}

Status BinaryTree::PreOrderTraverse(BiTNode *p, QString *display)
{
	if (p) {
		//		cout << p->data << " ";
		QString temp;
		*display = *display + temp.setNum(p->data) + " ";
		PreOrderTraverse(p->lchild, display);
		PreOrderTraverse(p->rchild, display);
	}
	else
		return OK;
}

Status BinaryTree::InOrderTraverse(BiTNode *p, QString *display)
{
	if (p) {
		InOrderTraverse(p->lchild,display);
		QString temp;
		*display = *display + temp.setNum(p->data) + " ";
//		cout << p->data << " ";
		InOrderTraverse(p->rchild,display);
	}
	else
		return OK;
}

Status BinaryTree::PostOrderTraverse(BiTNode *p,QString *display)
{
	if (p) {
		PostOrderTraverse(p->lchild,display);
		PostOrderTraverse(p->rchild,display);
		QString temp;
		*display = *display + temp.setNum(p->data) + " ";
//		cout << p->data << " ";
	}
	else
		return OK;
}

/*Status BinaryTree::LevelOrderTraverse()
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
}*/

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

int BinaryTree::NodeDepth(BiTNode *p)
{
	int current_depth = 0;
	Add_parent(root);
	while (p) {
		++current_depth;
		p = p->parent;
	}
	return current_depth;
}

/*int BinaryTree::Num_of_points(BiTNode *p)
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
}*/

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

/*Status BinaryTree::copy_BiTree(BiTNode *p,BiTNode **q)
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
}*/

Status BinaryTree::Add_parent(BiTNode *p)
{
	if (p) {
		if (p->lchild)
			p->lchild->parent = p;
		if (p->rchild)
			p->rchild->parent = p;

		Add_parent(p->lchild);
		Add_parent(p->rchild);
	}
	return OK;
}

Status BinaryTree::PreOrderThreading()
{
	if (!(head = new BiTNode))
		exit(OVERFLOW);
	(head)->LTag = Link;
	(head)->RTag = Thread;
	(head)->rchild = (head);
	if (!root)
		(head)->lchild = (head);
	else {
		(head)->lchild = root;
		pre = (head);
		PreThreading(root);
		pre->rchild = (head);
		pre->RTag = Thread;
	}
	return OK;
}

void BinaryTree::PreThreading(BiTNode *q)
{
	if (q) {
		if (!q->lchild) {
			q->LTag = Thread;
			q->lchild = pre;
		}
		if (!pre->rchild) {
			pre->RTag = Thread;
			pre->rchild = q;
		}
		pre = q;
		if (q->LTag == Link)
			PreThreading(q->lchild);
		if (q->RTag == Link)
			PreThreading(q->rchild);
	}
}

Status BinaryTree::InOrderThreading()
{
	if (!(head = new BiTNode))
		exit(OVERFLOW);
	(head)->LTag = Link;
	(head)->RTag = Thread;
	(head)->rchild = (head);
	if (!root)
		(head)->lchild = (head);
	else {
		(head)->lchild = root;
		pre = (head);
		InThreading(root);
		pre->rchild = (head);
		pre->RTag = Thread;
		(head)->rchild = pre;
	}
	return OK;
}

void BinaryTree::InThreading(BiTNode *q)
{
	if (q) {
		InThreading(q->lchild);
		if (!q->lchild) {
			q->LTag = Thread;
			q->lchild = pre;
		}
		if (!pre->rchild) {
			pre->RTag = Thread;
			pre->rchild = q;
		}
		pre = q;
		InThreading(q->rchild);
	}
}

Status BinaryTree::PostOrderThreading()
{
	Add_parent(root);//先给二叉树加上双亲域
	if (!(head = new BiTNode))
		exit(OVERFLOW);
	head->LTag = Link;
	head->RTag = Link;
	head->rchild = NULL;
	if (!root)
		head->lchild = head;
	else {
		head->lchild = root;
		pre = head;
		PostThreading(root);

		/*pre->rchild = head;
		pre->RTag = Thread;
		head->rchild = pre;*/
	}
	return OK;
}

void BinaryTree::PostThreading(BiTNode *q)
{
	if (q) {
		PostThreading(q->lchild);
		PostThreading(q->rchild);
		if (!q->lchild) {
			q->LTag = Thread;
			q->lchild = pre;
		}
		if (!pre->rchild) {
			pre->RTag = Thread;
			pre->rchild = q;
		}
		/*if (!q->rchild)
		{
		if (q == q->parent->rchild || q == q->parent->lchild&&!q->parent->rchild) {
		q->RTag = Thread;
		q->rchild = q->parent;
		}
		//q是其双亲的右孩子或q是其双亲的左孩子且其双亲没有右孩子
		if (q == q->parent->lchild&&!q->parent->rchild) {
		if (!pre->rchild)
		{
		pre->RTag = Thread;
		pre->rchild = q;
		}
		}//q是其双亲的左孩子且其双亲有右孩子
		}*/
		pre = q;
	}
}

Status BinaryTree::PreOrderTraverse_Thr(BiTNode *t,QString &display)
{
	BiTNode *p;
	p = t->lchild;
	while (p != t) {
		QString temp;
		display += temp.setNum(p->data) + " ";
		//cout << p->data << " ";
		while (p->LTag == Link) {
			p = p->lchild;
			display += temp.setNum(p->data) + " ";
			//cout << p->data << " ";
		}
		p = p->rchild;
	}
	return OK;
}

Status BinaryTree::InOrderTraverse_Thr(BiTNode *t,QString &display)
{
	BiTNode *p;
	p = t->lchild;
	while (p != t) {
		QString temp;
		while (p->LTag == Link)
			p = p->lchild;
		//cout << p->data << " ";
		display += temp.setNum(p->data) + " ";
		while (p->RTag == Thread&&p->rchild != t) {
			p = p->rchild;
			//cout << p->data << " ";
			display += temp.setNum(p->data) + " ";
		}
		p = p->rchild;
	}
	return OK;
}

Status BinaryTree::PostOrderTraverse_Thr(BiTNode *t,QString &display)
{
	BiTNode *p;
	p = t->rchild;
	if (p) {
		//cout << p->data << " ";//输出后序遍历根节点的第一个节点
		p = p->rchild;
		while (1) {
			if (p == t->lchild) {
				//cout << p->data << " ";//输出根节点
				break;
			}
			if (p->parent && (p == p->parent->rchild || p == p->parent->lchild&&p->parent->RTag == Thread)) {
				//cout << p->data << " ";
				p = p->parent;//其后继是其双亲
			}
			if (p->parent&&p == p->parent->lchild&&p->parent->RTag == Link) {
				//cout << p->data << " ";//其后继是其双亲右子树上按后序遍历列出的第一个节点
				if (p->RTag == Thread)
					p = p->rchild;
				else {
					if (p->parent->rchild)
						p = p->parent->rchild;
					else {
						//cout << p->parent->data << " ";
						break;//访问到根节点了
					}
					while (1) {
						if (p->LTag == Thread&&p->RTag == Thread) {
							//cout << p->data << " ";
							p = p->rchild;
							break;
						}
						else if (p->LTag == Link)
							p = p->lchild;
						else
							p = p->rchild;
					}
				}
			}
		}
	}
	return OK;
}