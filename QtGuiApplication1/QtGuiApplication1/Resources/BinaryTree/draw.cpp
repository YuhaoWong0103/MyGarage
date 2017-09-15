#include "draw.h"

#include <Qpainter>

DrawWidget::DrawWidget(QWidget *p):QWidget(p)
{
    //bst=new BST<int>;
    MyTree = new BinaryTree;
	is_prethreaded = false;
	is_inthreaded = false;
	is_postthreaded = false;
	depth = 0;
	NodeRadius = 0;
}

void DrawWidget::paintEvent(QPaintEvent *event)
{
	/*int depth = 0;
	if (MyTree->root&&!is_prethreaded&&!is_inthreaded&&!is_postthreaded)
		depth = MyTree->BiTreeDepth(MyTree->root);
	int height_everyline = 0;
	if(MyTree->root)
		height_everyline = Screen_Height / depth;//层次遍历每一行的高度
	int NoteRadius = 0;
	NoteRadius = height_everyline / 4;//结点半径*/
	if (MyTree->root&&!is_prethreaded&&!is_inthreaded&&!is_postthreaded)
	{
		depth = MyTree->BiTreeDepth(MyTree->root);
		height_everyline = Screen_Height / depth;
		NodeRadius = height_everyline / 4;
	}
	int num = 0;//目前结点编号（层次遍历顺序）
	QPainter painter(this);

	if (MyTree->root) {
		if (!is_prethreaded&&!is_inthreaded&&!is_postthreaded)//正常画树
		{
			SqQueue<BiTNode *> q;
			BiTNode *x = MyTree->root;
			q.EnQueue(x);
			while (!q.QueueEmpty()) {//画结点
				q.DeQueue(x);
				if (x)
				{
					++num;
					int CurrentLevel = MyTree->NodeDepth(x);/*depth + 1 - MyTree->BiTreeDepth(x);*/
					x->x_node = Screen_Width*(num + 1 - (1 << (CurrentLevel - 1))) / ((1 << (CurrentLevel - 1)) + 1);
					x->y_node = (CurrentLevel - 1)*height_everyline + /*(double)*/(height_everyline / 2);
					painter.setBrush(Qt::green);
					painter.drawEllipse(x->x_node, /*MainWindow_Height - Screen_Height + */x->y_node, NodeRadius, NodeRadius);
					painter.drawText(x->x_node + NodeRadius / 2, /*MainWindow_Height - Screen_Height + */x->y_node + NodeRadius / 2, QString::number(x->data));
				}
				else ++num;
				if(x) q.EnQueue(x->lchild);
				if(x) q.EnQueue(x->rchild);
			}
			x = MyTree->root;
			q.EnQueue(x);
			while (!q.QueueEmpty()) {//画连线
				q.DeQueue(x);
				if (x)
				{
					if (x->lchild)
						painter.drawLine(x->x_node + NodeRadius / 2, x->y_node + NodeRadius /*/ 2*/, x->lchild->x_node + NodeRadius / 2, x->lchild->y_node /*+ NoteRadius / 2*/);
					if (x->rchild)
						painter.drawLine(x->x_node + NodeRadius / 2, x->y_node + NodeRadius /*/ 2*/, x->rchild->x_node + NodeRadius / 2, x->rchild->y_node /*+ NoteRadius / 2*/);
					q.EnQueue(x->lchild);
					q.EnQueue(x->rchild);
				}
			}
		}
		else if (is_prethreaded)//画先序线索化后的树
		{
			BiTNode *p;
			p = MyTree->head->lchild;
			while (p != MyTree->head) {
				painter.setBrush(Qt::green);
				painter.drawEllipse(p->x_node, /*MainWindow_Height - Screen_Height + */p->y_node, NodeRadius, NodeRadius);
				painter.setPen(Qt::red);
				painter.drawText(p->x_node + NodeRadius / 2, /*MainWindow_Height - Screen_Height + */p->y_node + NodeRadius / 2, QString::number(p->data));
				if (p->LTag == Link) {
					painter.setPen(Qt::black);
					painter.drawLine(p->x_node + NodeRadius / 2, p->y_node + NodeRadius / 2, p->lchild->x_node + NodeRadius / 2, p->lchild->y_node + NodeRadius / 2);
				}
				if (p->RTag == Link) {
					painter.setPen(Qt::black);
					painter.drawLine(p->x_node + NodeRadius / 2, p->y_node + NodeRadius / 2, p->rchild->x_node + NodeRadius / 2, p->rchild->y_node + NodeRadius / 2);
				}
				if (p->RTag == Thread) {
					if (p->rchild != MyTree->head)
					{
						painter.setPen(Qt::blue);
						painter.drawLine(p->x_node + NodeRadius / 2, p->y_node + NodeRadius / 2, p->rchild->x_node + NodeRadius / 2, p->rchild->y_node + NodeRadius / 2);
					}
				}
				if (p->LTag == Thread) {
					if (p->parent)
					{
						painter.setPen(Qt::black);
						painter.drawLine(p->parent->x_node + NodeRadius / 2, p->parent->y_node + NodeRadius / 2, p->x_node + NodeRadius / 2, p->y_node + NodeRadius / 2);
					}
				}
				while (p->LTag == Link) {
					p = p->lchild;
					painter.setBrush(Qt::green);
					painter.drawEllipse(p->x_node, /*MainWindow_Height - Screen_Height + */p->y_node, NodeRadius, NodeRadius);
					painter.setPen(Qt::red);
					painter.drawText(p->x_node + NodeRadius / 2, /*MainWindow_Height - Screen_Height + */p->y_node + NodeRadius / 2, QString::number(p->data));
					if (p->parent)
					{
						painter.setPen(Qt::black);
						painter.drawLine(p->parent->x_node + NodeRadius / 2, p->parent->y_node + NodeRadius / 2, p->x_node + NodeRadius / 2, p->y_node + NodeRadius / 2);
					}
				}
				p = p->rchild;
			}
		}
		else if (is_inthreaded)//画中序线索化后的树
		{
			BiTNode *p;
			p = MyTree->head->lchild;
			while (p != MyTree->head) {
				if (p->LTag == Link) {
					painter.setPen(Qt::black);
					painter.drawLine(p->x_node + NodeRadius / 2, p->y_node + NodeRadius / 2, p->lchild->x_node + NodeRadius / 2, p->lchild->y_node + NodeRadius / 2);
				}
				if (p->RTag == Link) {
					painter.setPen(Qt::black);
					painter.drawLine(p->x_node + NodeRadius / 2, p->y_node + NodeRadius / 2, p->rchild->x_node + NodeRadius / 2, p->rchild->y_node + NodeRadius / 2);
				}
				while (p->LTag == Link)
					p = p->lchild;
				painter.setBrush(Qt::green);
				painter.drawEllipse(p->x_node, /*MainWindow_Height - Screen_Height + */p->y_node, NodeRadius, NodeRadius);
				painter.setPen(Qt::red);
				painter.drawText(p->x_node + NodeRadius / 2, /*MainWindow_Height - Screen_Height + */p->y_node + NodeRadius / 2, QString::number(p->data));
				if (p->LTag == Thread) {
					painter.setPen(Qt::black);
					painter.drawLine(p->parent->x_node + NodeRadius / 2, p->parent->y_node + NodeRadius / 2, p->x_node + NodeRadius / 2, p->y_node + NodeRadius / 2);
				}
				if (p->RTag == Thread&&p->rchild != MyTree->head) {
					painter.setPen(Qt::blue);
					painter.drawLine(p->x_node + NodeRadius / 2, p->y_node + NodeRadius / 2, p->rchild->x_node + NodeRadius / 2, p->rchild->y_node + NodeRadius / 2);
				}
				while (p->RTag == Thread&&p->rchild != MyTree->head) {
					p = p->rchild;
					painter.setBrush(Qt::green);
					painter.drawEllipse(p->x_node, /*MainWindow_Height - Screen_Height + */p->y_node, NodeRadius, NodeRadius);
					painter.setPen(Qt::red);
					painter.drawText(p->x_node + NodeRadius / 2, /*MainWindow_Height - Screen_Height + */p->y_node + NodeRadius / 2, QString::number(p->data));
					if (p->LTag == Thread) {
						painter.setPen(Qt::black);
						painter.drawLine(p->parent->x_node + NodeRadius / 2, p->parent->y_node + NodeRadius / 2, p->x_node + NodeRadius / 2, p->y_node + NodeRadius / 2);
					}
					if (p->RTag == Thread&&p->rchild != MyTree->head) {
						painter.setPen(Qt::blue);
						painter.drawLine(p->x_node + NodeRadius / 2, p->y_node + NodeRadius / 2, p->rchild->x_node + NodeRadius / 2, p->rchild->y_node + NodeRadius / 2);
					}
				}
				p=p->rchild;
			}
		}
		else if (is_postthreaded)//画后序线索化后的树
		{
			BiTNode *p;
			p = MyTree->head->rchild;
			if (p) {
				painter.setBrush(Qt::green);
				painter.drawEllipse(p->x_node,p->y_node, NodeRadius, NodeRadius);
				painter.setPen(Qt::red);
				painter.drawText(p->x_node + NodeRadius / 2, p->y_node + NodeRadius / 2, QString::number(p->data));
				if (p->LTag == Link) {
					painter.setPen(Qt::black);
					painter.drawLine(p->x_node + NodeRadius / 2, p->y_node + NodeRadius / 2, p->lchild->x_node + NodeRadius / 2, p->lchild->y_node + NodeRadius / 2);
				}
				if (p->RTag == Link) {
					painter.setPen(Qt::black);
					painter.drawLine(p->x_node + NodeRadius / 2, p->y_node + NodeRadius / 2, p->rchild->x_node + NodeRadius / 2, p->rchild->y_node + NodeRadius / 2);
				}
				p = p->rchild;
				while (1) {
					painter.setBrush(Qt::green);
					painter.drawEllipse(p->x_node, p->y_node, NodeRadius, NodeRadius);
					painter.setPen(Qt::red);
					painter.drawText(p->x_node + NodeRadius / 2, p->y_node + NodeRadius / 2, QString::number(p->data));
					if (p->LTag == Link) {
						painter.setPen(Qt::black);
						painter.drawLine(p->x_node + NodeRadius / 2, p->y_node + NodeRadius / 2, p->lchild->x_node + NodeRadius / 2, p->lchild->y_node + NodeRadius / 2);
					}
					if (p->RTag == Link) {
						painter.setPen(Qt::black);
						painter.drawLine(p->x_node + NodeRadius / 2, p->y_node + NodeRadius / 2, p->rchild->x_node + NodeRadius / 2, p->rchild->y_node + NodeRadius / 2);
					}
					if (p->RTag == Thread&&p->rchild != MyTree->head) {
						painter.setPen(Qt::blue);
						painter.drawLine(p->x_node + NodeRadius / 2, p->y_node + NodeRadius / 2, p->rchild->x_node + NodeRadius / 2, p->rchild->y_node + NodeRadius / 2);
					}
					if (p == MyTree->head->lchild) {
						painter.setBrush(Qt::green);
						painter.drawEllipse(p->x_node, p->y_node, NodeRadius, NodeRadius);
						painter.setPen(Qt::red);
						painter.drawText(p->x_node + NodeRadius / 2, p->y_node + NodeRadius / 2, QString::number(p->data));
						if (p->LTag == Link) {
							painter.setPen(Qt::black);
							painter.drawLine(p->x_node + NodeRadius / 2, p->y_node + NodeRadius / 2, p->lchild->x_node + NodeRadius / 2, p->lchild->y_node + NodeRadius / 2);
						}
						if (p->RTag == Thread&&p->rchild != MyTree->head) {
							painter.setPen(Qt::blue);
							painter.drawLine(p->x_node + NodeRadius / 2, p->y_node + NodeRadius / 2, p->rchild->x_node + NodeRadius / 2, p->rchild->y_node + NodeRadius / 2);
						}
						if (p->RTag == Link) {
							painter.setPen(Qt::black);
							painter.drawLine(p->x_node + NodeRadius / 2, p->y_node + NodeRadius / 2, p->rchild->x_node + NodeRadius / 2, p->rchild->y_node + NodeRadius / 2);
						}
						break;
					}
					if (p->parent && (p == p->parent->rchild || p == p->parent->lchild&&p->parent->RTag == Thread)) {
						//cout << p->data << " ";
						painter.setBrush(Qt::green);
						painter.drawEllipse(p->x_node, p->y_node, NodeRadius, NodeRadius);
						painter.setPen(Qt::red);
						painter.drawText(p->x_node + NodeRadius / 2, p->y_node + NodeRadius / 2, QString::number(p->data));
						if (p->LTag == Link) {
							painter.setPen(Qt::black);
							painter.drawLine(p->x_node + NodeRadius / 2, p->y_node + NodeRadius / 2, p->lchild->x_node + NodeRadius / 2, p->lchild->y_node + NodeRadius / 2);
						}
						if (p->RTag == Link) {
							painter.setPen(Qt::black);
							painter.drawLine(p->x_node + NodeRadius / 2, p->y_node + NodeRadius / 2, p->rchild->x_node + NodeRadius / 2, p->rchild->y_node + NodeRadius / 2);
						}
						if (p->RTag == Thread&&p->rchild != MyTree->head) {
							painter.setPen(Qt::blue);
							painter.drawLine(p->x_node + NodeRadius / 2, p->y_node + NodeRadius / 2, p->rchild->x_node + NodeRadius / 2, p->rchild->y_node + NodeRadius / 2);
						}
						p = p->parent;//其后继是其双亲
					}
					if (p->parent&&p == p->parent->lchild&&p->parent->RTag == Link) {
						//cout << p->data << " ";//其后继是其双亲右子树上按后序遍历列出的第一个节点
						painter.setBrush(Qt::green);
						painter.drawEllipse(p->x_node, p->y_node, NodeRadius, NodeRadius);
						painter.setPen(Qt::red);
						painter.drawText(p->x_node + NodeRadius / 2, p->y_node + NodeRadius / 2, QString::number(p->data));
						if (p->LTag == Link) {
							painter.setPen(Qt::black);
							painter.drawLine(p->x_node + NodeRadius / 2, p->y_node + NodeRadius / 2, p->lchild->x_node + NodeRadius / 2, p->lchild->y_node + NodeRadius / 2);
						}
						if (p->RTag == Link) {
							painter.setPen(Qt::black);
							painter.drawLine(p->x_node + NodeRadius / 2, p->y_node + NodeRadius / 2, p->rchild->x_node + NodeRadius / 2, p->rchild->y_node + NodeRadius / 2);
						}
						if (p->RTag == Thread&&p->rchild != MyTree->head) {
							painter.setPen(Qt::blue);
							painter.drawLine(p->x_node + NodeRadius / 2, p->y_node + NodeRadius / 2, p->rchild->x_node + NodeRadius / 2, p->rchild->y_node + NodeRadius / 2);
						}
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
								painter.setBrush(Qt::green);
								painter.drawEllipse(p->x_node, p->y_node, NodeRadius, NodeRadius);
								painter.setPen(Qt::red);
								painter.drawText(p->x_node + NodeRadius / 2, p->y_node + NodeRadius / 2, QString::number(p->data));
								if (p->LTag == Link) {
									painter.setPen(Qt::black);
									painter.drawLine(p->x_node + NodeRadius / 2, p->y_node + NodeRadius / 2, p->lchild->x_node + NodeRadius / 2, p->lchild->y_node + NodeRadius / 2);
								}
								if (p->RTag == Link) {
									painter.setPen(Qt::black);
									painter.drawLine(p->x_node + NodeRadius / 2, p->y_node + NodeRadius / 2, p->rchild->x_node + NodeRadius / 2, p->rchild->y_node + NodeRadius / 2);
								}
								if (p->RTag == Thread&&p->rchild != MyTree->head) {
									painter.setPen(Qt::blue);
									painter.drawLine(p->x_node + NodeRadius / 2, p->y_node + NodeRadius / 2, p->rchild->x_node + NodeRadius / 2, p->rchild->y_node + NodeRadius / 2);
								}
								if (p->LTag == Thread&&p->RTag == Thread) {
									//cout << p->data << " ";
									painter.setBrush(Qt::green);
									painter.drawEllipse(p->x_node, p->y_node, NodeRadius, NodeRadius);
									painter.setPen(Qt::red);
									painter.drawText(p->x_node + NodeRadius / 2, p->y_node + NodeRadius / 2, QString::number(p->data));
									if (p->LTag == Link) {
										painter.setPen(Qt::black);
										painter.drawLine(p->x_node + NodeRadius / 2, p->y_node + NodeRadius / 2, p->lchild->x_node + NodeRadius / 2, p->lchild->y_node + NodeRadius / 2);
									}
									if (p->RTag == Link) {
										painter.setPen(Qt::black);
										painter.drawLine(p->x_node + NodeRadius / 2, p->y_node + NodeRadius / 2, p->rchild->x_node + NodeRadius / 2, p->rchild->y_node + NodeRadius / 2);
									}
									if (p->RTag == Thread&&p->rchild != MyTree->head) {
										painter.setPen(Qt::blue);
										painter.drawLine(p->x_node + NodeRadius / 2, p->y_node + NodeRadius / 2, p->rchild->x_node + NodeRadius / 2, p->rchild->y_node + NodeRadius / 2);
									}
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
		}
		else;
	}
}


