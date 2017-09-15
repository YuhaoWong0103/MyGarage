#pragma once

#include <QString>
#include <QStringList>

#define TRUE		1
#define FALSE		0
#define OK		1
#define ERROR		0
#define INFEASIBLE	-1
#define LOVERFLOW	-2

#define PI_OF_MINE 3.1415

typedef int Status;

#define LIST_INIT_SIZE	100	//初始大小定义为100（可按需修改）
#define LISTINCREMENT	10	//若空间不够，每次增长10（可按需修改）

template <typename ElemType>
class sqlist {
public:
	ElemType *elem;	//存放动态申请空间的首地址
	int length;	//记录当前长度
	int listsize;	//当前分配的元素的个数

	sqlist();	//构造函数，替代InitList
	~sqlist();	//析构函数，替代DestroyList
	Status	ClearList();
	int ListLength();
	Status	ListInsert(int i, ElemType e);
	Status	ListDelete(int i, ElemType &e);
	Status	OutputList();
	Status  ListOrder();//对应于有序表的要求，把顺序表排序
	Status  OrderListInsert(ElemType e);
	//用这两个函数之前应该先调用一次ListOrder以确保顺序表已为有序表
};

template <typename ElemType>
sqlist<ElemType>::sqlist()
{
	elem = new ElemType[LIST_INIT_SIZE];
	if (elem == NULL)
		exit(OVERFLOW);
	length = 0;
	listsize = LIST_INIT_SIZE;
}

template <typename ElemType>
sqlist<ElemType>::~sqlist()
{
	if (elem)
		delete elem;
	length = 0;
	listsize = 0;
}

template <typename ElemType>
Status sqlist<ElemType>::ClearList()
{
	length = 0;
	return OK;
}

template <typename ElemType>
int sqlist<ElemType>::ListLength()
{
	return length;
}

template <typename ElemType>
Status sqlist<ElemType>::ListInsert(int i, ElemType e)
{
	ElemType *p, *q;

	if (i<1 || i>length + 1)   //合理范围是 1..length+1
		return ERROR;

	/* 空间已满则扩大空间 */
	if (length >= listsize) {
		ElemType *newbase;
		newbase = new ElemType[listsize + LISTINCREMENT];
		if (!newbase)
			return OVERFLOW;

		/* 原来的listsize个ElemType空间进行复制 */
		memcpy(newbase, elem, listsize*sizeof(ElemType));

		delete elem;
		elem = newbase;
		listsize += LISTINCREMENT;
		//length暂时不变
	}

	q = &(elem[i - 1]);  //第i个元素，即新的插入位置

						 /* 从最后一个【length放在[length-1]中】开始到第i个元素依次后移一格 */
	for (p = &(elem[length - 1]); p >= q; --p)
		*(p + 1) = *p;

	/* 插入新元素，长度+1 */
	*q = e;
	length++;

	return OK;
}

template <typename ElemType>
Status sqlist<ElemType>::ListDelete(int i, ElemType &e)
{
	ElemType *p, *q;

	if (i<1 || i>length) //合理范围是 1..length
		return ERROR;

	p = &(elem[i - 1]); 		//指向第i个元素
	e = *p; 				//取第i个元素的值放入e中
	q = &(elem[length - 1]);	//指向最后一个元素，也可以 q = L->elem+L->length-1

								/* 从第i+1到最后，依次前移一格 */
	for (++p; p <= q; ++p)
		*(p - 1) = *p;

	length--;	//长度-1
	return OK;
}

template <typename ElemType>
Status sqlist<ElemType>::OutputList()
{
	for (int i = 1; i <= length; ++i) {
		cout << elem[i - 1] << "--->";
		if (i % 10 == 0)
			cout << endl;
	}
	cout << endl;
	return OK;
}

template <typename ElemType>
Status sqlist<ElemType>::ListOrder()//排序函数
{
	ElemType t;
	for (int i = 1; i <= length; ++i)
		for (int j = 1; j <= length - i; ++j) {
			if (elem[j - 1]>elem[j]) {
				t = elem[j];
				elem[j] = elem[j - 1];
				elem[j - 1] = t;
			}
		}
	return OK;
}

class FriendsInformation {
public:
	QString Name;
	int Relevancy;
	FriendsInformation() {
		Relevancy = 0;
	}
	//friend bool operator >(const FriendsInformation &a, const FriendsInformation &b);
};

class PersonalInformation {
public:
	QString Name;
	QString Area;
	QString PrimarySchool;
	QString MiddleSchool;
	QString University;
	QString Company;
	QStringList Groups;
	sqlist<FriendsInformation> CondextOfFriends;//陌生人关联度（共同好友数），其中第i个元素的值表示该成员与第i个陌生人的关联度
	sqlist<PersonalInformation *> Friends;
	sqlist<PersonalInformation *> PeopleMightKnow;
	int x_of_screen;
	int y_of_screen;

	PersonalInformation(QString Name, QString Area, QString PrimarySchool, QString MiddleSchool, QString University, QString Company);
	void AddFriends(PersonalInformation *p);
	void AddGroups(QString Group);
};
