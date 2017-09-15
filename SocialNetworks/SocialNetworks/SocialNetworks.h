#pragma once

#include "PersonalInformation.h"
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QDialog>
#include <QListWidget>
#include <QWidget>
#include <QPainter>
#include <QPaintEvent>

#define MAX_NUMBER_OF_FRIENDS 100
#define Width_Of_Screen 500
#define Length_of_Screen 500

class SocialNetworks {
public:
	sqlist<PersonalInformation *> People;
	void AddNewMember(PersonalInformation *p);
};

class InputDialog :public QDialog {
	Q_OBJECT

public:
	InputDialog(QWidget *parent = 0);
	~InputDialog();
signals:
	void sendData(QStringList,QStringList);
private slots:
	void OKClicked();
	void CancelClicked();
private:
	QLabel *Name_Dialog;
	QLineEdit *NameValue_Dialog;
	QLabel *Area_Dialog;
	QLineEdit *AreaValue_Dialog;
	QLabel *PrimarySchool_Dialog;
	QLineEdit *PrimarySchoolValue_Dialog;
	QLabel *MiddleSchool_Dialog;
	QLineEdit *MiddleSchoolValue_Dialog;
	QLabel *University_Dialog;
	QLineEdit *UniversityValue_Dialog;
	QLabel *Company_Dialog;
	QLineEdit *CompanyValue_Dialog;
	//QLabel *Friends_Dialog;
	//QLineEdit *FriendsValue_Dialog;
	QLabel *Groups_Dialog;
	QLineEdit *GroupsValue_Dialog;
	QPushButton *OKButton;
	QPushButton *CancelButton;
};

class AddFriendsDialog:public QDialog {
	Q_OBJECT
public:
	int *newfriendspos;
	QString *currentperson;
	QListWidget *StrangerList;
	//QStringList *StrangerSelect;
	AddFriendsDialog(QWidget *parent = 0);
	~AddFriendsDialog();
signals:
	void sendNewFriendData(QStringList);
private slots:
	void OKClicked();
	void CancelClicked();
	void CurrentRowClickedHappens(QListWidgetItem *);
private:
	QPushButton *OKButton;
	QPushButton *CancelButton;
};

class DrawWidget :public QWidget {
	Q_OBJECT
public:
	SocialNetworks *SN_Painter;
	int i;//某个特定的社交网络成员
	DrawWidget(QWidget *p = 0);
	void paintEvent(QPaintEvent *event);
};