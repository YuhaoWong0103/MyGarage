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

#define LIST_INIT_SIZE	100	//��ʼ��С����Ϊ100���ɰ����޸ģ�
#define LISTINCREMENT	10	//���ռ䲻����ÿ������10���ɰ����޸ģ�

template <typename ElemType>
class sqlist {
public:
	ElemType *elem;	//��Ŷ�̬����ռ���׵�ַ
	int length;	//��¼��ǰ����
	int listsize;	//��ǰ�����Ԫ�صĸ���

	sqlist();	//���캯�������InitList
	~sqlist();	//�������������DestroyList
	Status	ClearList();
	int ListLength();
	Status	ListInsert(int i, ElemType e);
	Status	ListDelete(int i, ElemType &e);
	Status	OutputList();
	Status  ListOrder();//��Ӧ��������Ҫ�󣬰�˳�������
	Status  OrderListInsert(ElemType e);
	//������������֮ǰӦ���ȵ���һ��ListOrder��ȷ��˳�����Ϊ�����
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

	if (i<1 || i>length + 1)   //����Χ�� 1..length+1
		return ERROR;

	/* �ռ�����������ռ� */
	if (length >= listsize) {
		ElemType *newbase;
		newbase = new ElemType[listsize + LISTINCREMENT];
		if (!newbase)
			return OVERFLOW;

		/* ԭ����listsize��ElemType�ռ���и��� */
		memcpy(newbase, elem, listsize*sizeof(ElemType));

		delete elem;
		elem = newbase;
		listsize += LISTINCREMENT;
		//length��ʱ����
	}

	q = &(elem[i - 1]);  //��i��Ԫ�أ����µĲ���λ��

						 /* �����һ����length����[length-1]�С���ʼ����i��Ԫ�����κ���һ�� */
	for (p = &(elem[length - 1]); p >= q; --p)
		*(p + 1) = *p;

	/* ������Ԫ�أ�����+1 */
	*q = e;
	length++;

	return OK;
}

template <typename ElemType>
Status sqlist<ElemType>::ListDelete(int i, ElemType &e)
{
	ElemType *p, *q;

	if (i<1 || i>length) //����Χ�� 1..length
		return ERROR;

	p = &(elem[i - 1]); 		//ָ���i��Ԫ��
	e = *p; 				//ȡ��i��Ԫ�ص�ֵ����e��
	q = &(elem[length - 1]);	//ָ�����һ��Ԫ�أ�Ҳ���� q = L->elem+L->length-1

								/* �ӵ�i+1���������ǰ��һ�� */
	for (++p; p <= q; ++p)
		*(p - 1) = *p;

	length--;	//����-1
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
Status sqlist<ElemType>::ListOrder()//������
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
	sqlist<FriendsInformation> CondextOfFriends;//İ���˹����ȣ���ͬ�������������е�i��Ԫ�ص�ֵ��ʾ�ó�Ա���i��İ���˵Ĺ�����
	sqlist<PersonalInformation *> Friends;
	sqlist<PersonalInformation *> PeopleMightKnow;
	int x_of_screen;
	int y_of_screen;

	PersonalInformation(QString Name, QString Area, QString PrimarySchool, QString MiddleSchool, QString University, QString Company);
	void AddFriends(PersonalInformation *p);
	void AddGroups(QString Group);
};
