#pragma once

#include <QtWidgets/QMainWindow>
//#include "ui_SocialNetworks.h"
#include "SocialNetworks.h"

#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
//#include <QGraphicsView>
//#include <QGraphicsItem>
//#include <QGraphicsScene>
#include <QListWidget>
#include <QTableWidget>
#include <cmath>

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	SocialNetworks *SN;
	DrawWidget *Screen;
	//QGraphicsScene *scene;
	//QGraphicsView *View;
	QPushButton *AddNewMember;
	QLabel *Name;
	QLineEdit *NameValue;
	QLabel *Area;
	QLineEdit *AreaValue;
	QLabel *PrimarySchool;
	QLineEdit *PrimarySchoolValue;
	QLabel *MiddleSchool;
	QLineEdit *MiddleSchoolValue;
	QLabel *University;
	QLineEdit *UniversityValue;
	QLabel *Company;
	QLineEdit *CompanyValue;
	QLabel *PeopleLabel;
	QListWidget *People;
	QLabel *FriendsLabel;
	QListWidget *Friends;
	QLabel *GroupsLabel;
	QListWidget *Groups;
	QLabel *PeopleMightKnowLabel;
	QTableWidget *PeopleMightKnow;//����������ʶ���˺�����Щ�˵Ĺ�ͬ������
	AddFriendsDialog *AFD;

	MainWindow(QWidget *parent = Q_NULLPTR);

	private slots:
	void receiveData(QStringList data,QStringList groups);
	void receiveNewFriendsData(QStringList data);

	public slots:
	void AddNewMemberClicked();//����³�Ա
	void PeopleListItemClicked(QListWidgetItem *);//����罻��Ա����Ӧ
	void PeopleListItemDoubleClicked(QListWidgetItem *);//˫���罻��Ա����Ӧ

private:
	//Ui::SocialNetworksClass ui;
};
