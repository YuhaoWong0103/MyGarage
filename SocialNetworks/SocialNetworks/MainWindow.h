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
	QTableWidget *PeopleMightKnow;//包含可能认识的人和与这些人的共同好友数
	AddFriendsDialog *AFD;

	MainWindow(QWidget *parent = Q_NULLPTR);

	private slots:
	void receiveData(QStringList data,QStringList groups);
	void receiveNewFriendsData(QStringList data);

	public slots:
	void AddNewMemberClicked();//添加新成员
	void PeopleListItemClicked(QListWidgetItem *);//点击社交成员的响应
	void PeopleListItemDoubleClicked(QListWidgetItem *);//双击社交成员的响应

private:
	//Ui::SocialNetworksClass ui;
};
