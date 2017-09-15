#include "mainwindow.h"

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent)/*,
					   ui(new Ui::MainWindow)*/
{
	elem = new QLineEdit(this);
	create = new QPushButton(this);
	create->setText("create");
	connect(create, SIGNAL(clicked()), this, SLOT(createclicked()));

	QHBoxLayout * hlayout1 = new QHBoxLayout;
	hlayout1->addWidget(elem);
	hlayout1->addWidget(create);

	QLabel *note = new QLabel;
	note->setText("note:please use PreOrder to create and use space to split them up,-1 means null");

	QVBoxLayout *vlayout0 = new QVBoxLayout;
	vlayout0->addLayout(hlayout1);
	vlayout0->addWidget(note);

	/*todelete = new QLineEdit(this);
	buttondelete = new QPushButton(this);
	buttondelete->setText("Delete");
	//connect(buttondelete,SIGNAL(clicked()),this,SLOT(deleteclicked()));

	QHBoxLayout *hlayout2 = new QHBoxLayout;
	hlayout2->addWidget(todelete);
	hlayout2->addWidget(buttondelete);*/

	LeavesNumber = new QLineEdit(this);
	CountLeaves = new QPushButton(this);
	CountLeaves->setText("CountLeaves");
	connect(CountLeaves, SIGNAL(clicked()), this, SLOT(countclicked()));

	QLabel *output = new QLabel;
	output->setText("output:");

	QHBoxLayout *hlayout3 = new QHBoxLayout;
	hlayout3->addWidget(output);
	hlayout3->addWidget(LeavesNumber);

	PreOrderTraverse = new QPushButton(this);
	PreOrderTraverse->setText("PreOrderTraverse");
	connect(PreOrderTraverse, SIGNAL(clicked()), this, SLOT(PreOTclicked()));
	InOrderTraverse = new QPushButton(this);
	InOrderTraverse->setText("InOrderTraverse");
	connect(InOrderTraverse,SIGNAL(clicked()),this,SLOT(InOTclicked()));
	PostOrderTraverse = new QPushButton(this);
	PostOrderTraverse->setText("PostOrderTraverse");
	connect(PostOrderTraverse,SIGNAL(clicked()),this,SLOT(PostOTclicked()));

	PreOrderThreading = new QPushButton(this);
	PreOrderThreading->setText("PreOrderThreading");
	connect(PreOrderThreading,SIGNAL(clicked()),this,SLOT(PreOThrclicked()));
	InOrderThreading = new QPushButton(this);
	InOrderThreading->setText("InOrderThreading");
	connect(InOrderThreading,SIGNAL(clicked()),this,SLOT(InOThrclicked()));
	PostOrderThreading = new QPushButton(this);
	PostOrderThreading->setText("PostOrderThreading");
	connect(PostOrderThreading,SIGNAL(clicked()),this,SLOT(PostOThrclicked()));

	PreOrderTraverse_Thr = new QPushButton(this);
	PreOrderTraverse_Thr->setText("PreOrderTraverse_Thr");
	connect(PreOrderTraverse_Thr,SIGNAL(clicked()),this,SLOT(PreOTThrclicked()));
	InOrderTraverse_Thr = new QPushButton(this);
	InOrderTraverse_Thr->setText("InOrderTraverse_Thr");
	connect(InOrderTraverse_Thr,SIGNAL(clicked()),this,SLOT(InOTThrclicked()));

	QVBoxLayout *vlayout1 = new QVBoxLayout;
	vlayout1->addWidget(CountLeaves);
	vlayout1->addWidget(PreOrderTraverse);
	vlayout1->addWidget(InOrderTraverse);
	vlayout1->addWidget(PostOrderTraverse);
	vlayout1->addWidget(PreOrderThreading);
	vlayout1->addWidget(InOrderThreading);
	vlayout1->addWidget(PostOrderThreading);
	vlayout1->addWidget(PreOrderTraverse_Thr);
	vlayout1->addWidget(InOrderTraverse_Thr);

	QHBoxLayout *hlayout4 = new QHBoxLayout;
	Screen = new DrawWidget(this);
	Screen->setFixedSize(Screen_Width, Screen_Height);
	hlayout4->addWidget(Screen);
	hlayout4->addLayout(vlayout1);
	//hlayout4->setStretchFactor(Screen,3);
	//hlayout4->setStretchFactor(vlayout1,1);

	QHBoxLayout *hlayout5 = new QHBoxLayout;
	//hlayout5->addStretch(1);
	hlayout5->addLayout(vlayout0);
	//hlayout5->addStretch(1);
	//hlayout5->addLayout(hlayout2);
	hlayout5->addLayout(hlayout3);
	//hlayout5->addStretch(1);

	QVBoxLayout *vlayout2 = new QVBoxLayout;
	vlayout2->addLayout(hlayout5);
	/*vlayout2->addLayout(hlayout1);
	vlayout2->addLayout(hlayout2);
	vlayout2->addLayout(hlayout3);*/
	vlayout2->addLayout(hlayout4);
	vlayout2->setStretchFactor(hlayout5, 1);
	vlayout2->setStretchFactor(hlayout4, 5);

	QWidget *widget = new QWidget(this);
	widget->setLayout(vlayout2);

	this->setCentralWidget(widget);

	LeavesNumber->setText("Please create a BinaryTree!");
	/*ui->setupUi(this);*/
}

MainWindow::~MainWindow()
{
	delete elem;
	delete create;
	/*delete todelete;
	delete buttondelete;*/
	delete LeavesNumber;
	delete CountLeaves;
	delete PreOrderTraverse;
	delete InOrderTraverse;
	delete PostOrderTraverse;
	delete PreOrderTraverse_Thr;
	delete InOrderTraverse_Thr;
	delete Screen;
	/*delete ui;*/
}

void MainWindow::createclicked()
{
	QString num = elem->text();
	QStringList list = num.split(" ");
	int n = 0;
	n = list.size();
	SqQueue<int> q;
	for (int i = 0; i<n; ++i) {
		QString temp = list[i];
		q.EnQueue(temp.toInt());
	}
	if (Screen->MyTree->CreateBinaryTree(&(Screen->MyTree->root), q))
		LeavesNumber->setText("The BinaryTree has been created!");
	Screen->update();
}

/*void MainWindow::deleteclicked()
{

}*/

void MainWindow::PreOTclicked()
{
	if (!flag_PreThrclicked&&!flag_InThrclicked&&!flag_PostThrclicked)
	{
		QString display;
		Screen->MyTree->PreOrderTraverse(Screen->MyTree->root, &display);
		LeavesNumber->setText("PreOrderTraverse:" + display);
	}
}

void MainWindow::InOTclicked()
{
	if (!flag_PreThrclicked&&!flag_InThrclicked&&!flag_PostThrclicked)
	{
		QString display;
		Screen->MyTree->InOrderTraverse(Screen->MyTree->root, &display);
		LeavesNumber->setText("InOrderTraverse:" + display);
	}
}

void MainWindow::PostOTclicked()
{
	if (!flag_PreThrclicked&&!flag_InThrclicked&&!flag_PostThrclicked)
	{
		QString display;
		Screen->MyTree->PostOrderTraverse(Screen->MyTree->root, &display);
		LeavesNumber->setText("PostOrderTraverse:" + display);
	}
}

void MainWindow::PreOThrclicked()
{
	if (!flag_InThrclicked&&!flag_PostThrclicked)
		if (Screen->MyTree->PreOrderThreading())
		{
			flag_PreThrclicked = true;
			Screen->is_prethreaded = true;
			LeavesNumber->setText("PreOrderThreading is done!Blue lines are threads.");
			Screen->update();
		}
}

void MainWindow::InOThrclicked()
{
	if (!flag_PreThrclicked&&!flag_PostThrclicked)
		if (Screen->MyTree->InOrderThreading())
		{
			flag_InThrclicked = true;
			Screen->is_inthreaded = true;
			LeavesNumber->setText("InOrderThreading is done!Blue lines are threads.");
			Screen->update();
		}
}

void MainWindow::PostOThrclicked()
{
	if (!flag_InThrclicked&&!flag_PreThrclicked)
		if (Screen->MyTree->PostOrderThreading())
		{
			flag_PostThrclicked = true;
			Screen->is_postthreaded = true;
			LeavesNumber->setText("PostOrderThreading is done!Blue lines are threads.");
			Screen->update();
		}
}

void MainWindow::PreOTThrclicked()
{
	if (flag_PreThrclicked) {
		QString display;
		Screen->MyTree->PreOrderTraverse_Thr(Screen->MyTree->head, display);
		LeavesNumber->setText("PreOrderTraverse_Thr:" + display);
	}
}

void MainWindow::InOTThrclicked()
{
	if (flag_InThrclicked) {
		QString display;
		Screen->MyTree->InOrderTraverse_Thr(Screen->MyTree->head, display);
		LeavesNumber->setText("InOrderTraverse_Thr:" + display);
	}
}

void MainWindow::countclicked()
{
	if (!flag_PreThrclicked&&!flag_InThrclicked&&!flag_PostThrclicked)
	{
		QString display;
		int n = Screen->MyTree->Num_of_leaves(Screen->MyTree->root);
		LeavesNumber->setText("The number of leaves is " + display.setNum(n));
	}
}
