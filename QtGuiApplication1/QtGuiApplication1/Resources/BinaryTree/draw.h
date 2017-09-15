#ifndef DRAW_H
#define DRAW_H

#include <QWidget>
#include <QPaintEvent>
#include "BinaryTree.h"
//#include "DS\Queue.h"

#define MainWindow_Width 1300
#define MainWindow_Height 900
#define Screen_Width	 1000
#define Screen_Height     700

class DrawWidget:public QWidget
{
    Q_OBJECT
public:
    //BST<int> *bst;
    BinaryTree *MyTree;
	bool is_prethreaded;
	bool is_inthreaded;
	bool is_postthreaded;
	int depth;
	int NodeRadius;
	int height_everyline;

    DrawWidget (QWidget *p = 0);
    void paintEvent(QPaintEvent *event);
};

#endif // DRAW_H
