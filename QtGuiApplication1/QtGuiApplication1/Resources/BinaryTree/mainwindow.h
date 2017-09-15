#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QLineEdit>
#include <QPushButton>

#include "draw.h"

/*namespace Ui {
class MainWindow;
}*/

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    QLineEdit *elem;
    QPushButton *create;

    /*QLineEdit *todelete;
    QPushButton *buttondelete;*/

    QLineEdit *LeavesNumber;
    QPushButton *CountLeaves;

    QPushButton *PreOrderTraverse;
    QPushButton *InOrderTraverse;
    QPushButton *PostOrderTraverse;

    QPushButton *PreOrderThreading;
    QPushButton *InOrderThreading;
    QPushButton *PostOrderThreading;

    QPushButton *PreOrderTraverse_Thr;
    QPushButton *InOrderTraverse_Thr;

    DrawWidget *Screen;

	bool flag_PreThrclicked = false;
	bool flag_InThrclicked = false;
	bool flag_PostThrclicked = false;

    /*explicit */MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void createclicked();//插入结点
    //void deleteclicked();
    void countclicked();//统计叶子节点
    void PreOTclicked();//先序遍历
    void InOTclicked();//中序遍历
    void PostOTclicked();//后序遍历
    void PreOThrclicked();//先序线索化
    void InOThrclicked();//中序线索化
    void PostOThrclicked();//后序线索化
    void PreOTThrclicked();//先序线索化遍历
    void InOTThrclicked();//中序线索化遍历
/*private:
    Ui::MainWindow *ui;*/
};

#endif // MAINWINDOW_H
