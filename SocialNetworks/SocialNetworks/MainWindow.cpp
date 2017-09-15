#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
{
	SN = new SocialNetworks;//社交网络对象，所有数据的获取源
	//ui.setupUi(this);
	AddNewMember = new QPushButton(this);
	//scene = new QGraphicsScene(this);
	//View = new QGraphicsView(scene,this);
	Screen = new DrawWidget(this);
	Name = new QLabel(this);
	NameValue = new QLineEdit(this);
	Area = new QLabel(this);
	AreaValue = new QLineEdit(this);
	PrimarySchool = new QLabel(this);
	PrimarySchoolValue = new QLineEdit(this);
	MiddleSchool = new QLabel(this);
	MiddleSchoolValue = new QLineEdit(this);
	University = new QLabel(this);
	UniversityValue = new QLineEdit(this);
	Company = new QLabel(this);
	CompanyValue = new QLineEdit(this);
	PeopleLabel = new QLabel(this);
	People = new QListWidget(this);
	FriendsLabel = new QLabel(this);
	Friends = new QListWidget(this);
	GroupsLabel = new QLabel(this);
	Groups = new QListWidget(this);
	PeopleMightKnowLabel = new QLabel(this);
	PeopleMightKnow = new QTableWidget(this);

	AddNewMember->setText(u8"添加新成员");
	Name->setText(u8"姓名");
	Area->setText(u8"地址");
	PrimarySchool->setText(u8"小学");
	MiddleSchool->setText(u8"中学");
	University->setText(u8"大学");
	Company->setText(u8"公司");
	PeopleLabel->setText(u8"社交网络成员(双击某项为其添加好友)");
	FriendsLabel->setText(u8"该成员认识的朋友");
	GroupsLabel->setText(u8"该成员加入的群组");
	PeopleMightKnowLabel->setText(u8"该成员可能认识的人");

	QHBoxLayout * hlayout_name = new QHBoxLayout;
	QHBoxLayout * hlayout_area = new QHBoxLayout;
	QHBoxLayout * hlayout_primaryschool = new QHBoxLayout;
	QHBoxLayout * hlayout_middleschool = new QHBoxLayout;
	QHBoxLayout * hlayout_university = new QHBoxLayout;
	QHBoxLayout * hlayout_company = new QHBoxLayout;
	QHBoxLayout * hlayout_inf1 = new QHBoxLayout;
	QHBoxLayout * hlayout_inf2 = new QHBoxLayout;
	QVBoxLayout * vlayout_inf = new QVBoxLayout;
	QVBoxLayout * vlayout_view_and_inf = new QVBoxLayout;
	QVBoxLayout * vlayout_people = new QVBoxLayout;
	QVBoxLayout * vlayout_friends = new QVBoxLayout;
	QHBoxLayout * hlayout_people_and_friends = new QHBoxLayout;
	QVBoxLayout * vlayout_groups = new QVBoxLayout;
	QVBoxLayout * vlayout_peoplemightknow = new QVBoxLayout;
	QHBoxLayout * hlayout_groups_and_peoplemightknow = new QHBoxLayout;
	QVBoxLayout * vlayout_list = new QVBoxLayout;
	QHBoxLayout * hlayout_main = new QHBoxLayout;

	hlayout_name->addWidget(Name);
	hlayout_name->addWidget(NameValue);
	hlayout_area->addWidget(Area);
	hlayout_area->addWidget(AreaValue);
	hlayout_primaryschool->addWidget(PrimarySchool);
	hlayout_primaryschool->addWidget(PrimarySchoolValue);
	hlayout_middleschool->addWidget(MiddleSchool);
	hlayout_middleschool->addWidget(MiddleSchoolValue);
	hlayout_university->addWidget(University);
	hlayout_university->addWidget(UniversityValue);
	hlayout_company->addWidget(Company);
	hlayout_company->addWidget(CompanyValue);
	hlayout_inf1->addLayout(hlayout_name);
	hlayout_inf1->addLayout(hlayout_area);
	hlayout_inf1->addLayout(hlayout_primaryschool);
	hlayout_inf2->addLayout(hlayout_middleschool);
	hlayout_inf2->addLayout(hlayout_university);
	hlayout_inf2->addLayout(hlayout_company);
	vlayout_inf->addLayout(hlayout_inf1);
	vlayout_inf->addLayout(hlayout_inf2);
	vlayout_view_and_inf->addWidget(AddNewMember);
	vlayout_view_and_inf->addWidget(Screen);
	vlayout_view_and_inf->addLayout(vlayout_inf);
	vlayout_people->addWidget(PeopleLabel);
	vlayout_people->addWidget(People);
	vlayout_friends->addWidget(FriendsLabel);
	vlayout_friends->addWidget(Friends);
	vlayout_groups->addWidget(GroupsLabel);
	vlayout_groups->addWidget(Groups);
	vlayout_peoplemightknow->addWidget(PeopleMightKnowLabel);
	vlayout_peoplemightknow->addWidget(PeopleMightKnow);
	hlayout_people_and_friends->addLayout(vlayout_people);
	hlayout_people_and_friends->addLayout(vlayout_friends);
	hlayout_groups_and_peoplemightknow->addLayout(vlayout_groups);
	hlayout_groups_and_peoplemightknow->addLayout(vlayout_peoplemightknow);
	vlayout_list->addLayout(hlayout_people_and_friends);
	vlayout_list->addLayout(hlayout_groups_and_peoplemightknow);
	hlayout_main->addLayout(vlayout_view_and_inf);
	hlayout_main->addLayout(vlayout_list);

	//写connect函数
	connect(AddNewMember, SIGNAL(clicked()), this, SLOT(AddNewMemberClicked()));
	connect(People, SIGNAL(itemClicked(QListWidgetItem *)), this, SLOT(PeopleListItemClicked(QListWidgetItem *)));
	connect(People, SIGNAL(itemDoubleClicked(QListWidgetItem *)), this, SLOT(PeopleListItemDoubleClicked(QListWidgetItem *)));
	//connect(AFD, SIGNAL(sendNewFriendData(QStringList)), this, SLOT(receiveNewFriendsData(QStringList)));


	//scene->setSceneRect(0, 0, Width_Of_Scene, Length_of_Scene);
	//View->resize(Width_Of_Scene, Length_of_Scene);
	Screen->setFixedSize(Width_Of_Screen, Length_of_Screen);

	QWidget *widget = new QWidget(this);
	widget->setLayout(hlayout_main);
	this->setCentralWidget(widget);
}

void MainWindow::receiveData(QStringList Data,QStringList groups)
{
	PersonalInformation *p;
	p = new PersonalInformation(Data.at(0), Data.at(1), Data.at(2), Data.at(3), Data.at(4), Data.at(5));
	int n = groups.size();
	for (int i = 0; i < n; ++i)
		p->AddGroups(groups.at(i));
	SN->AddNewMember(p);
	People->addItem(new QListWidgetItem(p->Name));
}

void MainWindow::receiveNewFriendsData(QStringList newfriends)
{
	int n;
	int m;
	int i;
	n = SN->People.ListLength();
	for (i = 0; i < n; ++i) {
		if (AFD->currentperson == SN->People.elem[i]->Name)
			break;
	}

	m = newfriends.size();
	for (int j = 0; j < m; ++j) {
		int k;
		for (k = 0; k < n; ++k) {
			if (newfriends.at(j) == SN->People.elem[k]->Name)
				break;
		}
		SN->People.elem[i]->AddFriends(SN->People.elem[k]);
		SN->People.elem[k]->AddFriends(SN->People.elem[i]);
		Friends->addItem(newfriends.at(j));
		//加完朋友立即显示
	}
}

void MainWindow::AddNewMemberClicked()
{
	InputDialog *dialog = new InputDialog;
	connect(dialog, SIGNAL(sendData(QStringList, QStringList)), this, SLOT(receiveData(QStringList,QStringList)));
	//利用对话框获取newmember的数据
	dialog->show();
}

void MainWindow::PeopleListItemClicked(QListWidgetItem *item)
{
	//显示该成员的朋友及加入的群组
	QString TempName;
	TempName = item->text();
	int n = SN->People.ListLength();
	int i;//定位到底是哪个成员
	for (i = 0; i < n; ++i) {
		if (TempName == SN->People.elem[i]->Name)
			break;
	}

	Groups->clear();
	Friends->clear();
	PeopleMightKnow->clear();
	SN->People.elem[i]->CondextOfFriends.ClearList();

	NameValue->setText(SN->People.elem[i]->Name);
	AreaValue->setText(SN->People.elem[i]->Area);
	PrimarySchoolValue->setText(SN->People.elem[i]->PrimarySchool);
	MiddleSchoolValue->setText(SN->People.elem[i]->MiddleSchool);
	UniversityValue->setText(SN->People.elem[i]->University);
	CompanyValue->setText(SN->People.elem[i]->Company);
	if (i != n) {
		int m = SN->People.elem[i]->Groups.size();
		for (int j = 0; j < m; ++j) {
			Groups->addItem(new QListWidgetItem(SN->People.elem[i]->Groups.at(j)));
		}
		m = SN->People.elem[i]->Friends.ListLength();
		for (int j = 0; j < m; ++j) {
			Friends->addItem(new QListWidgetItem(SN->People.elem[i]->Friends.elem[j]->Name));
		}
	}

	//计算陌生人关联度
	for (int j = 0; j < n; ++j) {
		if (TempName != SN->People.elem[j]->Name) {//自己不计算在内
			int k;
			int m = SN->People.elem[i]->Friends.ListLength();
			for (k = 0; k < m; ++k) {//朋友不算在内
				if (SN->People.elem[j]->Name == SN->People.elem[i]->Friends.elem[k]->Name)
					break;
			}
			if (k == m) {//此人不是朋友
				int TempCondext = 0;
				for (int z = 0; z < SN->People.elem[i]->Friends.ListLength(); ++z) {
					for (int p = 0; p < SN->People.elem[j]->Friends.ListLength(); ++p) {
						if (SN->People.elem[i]->Friends.elem[z]->Name == SN->People.elem[j]->Friends.elem[p]->Name)
							++TempCondext;
					}
				}
				FriendsInformation FI;
				FI.Name = SN->People.elem[j]->Name;
				FI.Relevancy = TempCondext;
				//更新朋友关联度信息
				for (int x = 0; x < SN->People.elem[i]->CondextOfFriends.ListLength(); ++x)
				{
					if (FI.Name == SN->People.elem[i]->CondextOfFriends.elem[x].Name) {
						FriendsInformation FI_TEMP;
						SN->People.elem[i]->CondextOfFriends.ListDelete(x + 1, FI_TEMP);
						//删除掉重复的好友信息
					}
				}
				
				SN->People.elem[i]->CondextOfFriends.ListInsert(1, FI);
			}
			else {//将朋友从陌生人列表中删掉
				for (int y = 0; y < SN->People.elem[i]->CondextOfFriends.ListLength(); ++y) {
					if (SN->People.elem[j]->Name == SN->People.elem[i]->CondextOfFriends.elem[y].Name)
					{
						FriendsInformation FI_TEMP;
						SN->People.elem[i]->CondextOfFriends.ListDelete(y + 1, FI_TEMP);
					}
				}
			}
		}
	}

	//SN->People.elem[i]->CondextOfFriends.ListOrder();//根据相关度对陌生人进行排序
	for (int a = 1; a <= SN->People.elem[i]->CondextOfFriends.ListLength(); ++a)
		for (int b = 1; b <= SN->People.elem[i]->CondextOfFriends.ListLength() - a;++b)
			if (SN->People.elem[i]->CondextOfFriends.elem[b - 1].Relevancy<SN->People.elem[i]->CondextOfFriends.elem[b].Relevancy) {
				FriendsInformation FI_T;
				FI_T = SN->People.elem[i]->CondextOfFriends.elem[b];
				SN->People.elem[i]->CondextOfFriends.elem[b] = SN->People.elem[i]->CondextOfFriends.elem[b - 1];
				SN->People.elem[i]->CondextOfFriends.elem[b - 1] = FI_T;
			}

	//显示可能认识的人
	PeopleMightKnow->setEditTriggers(QAbstractItemView::NoEditTriggers);//设置为只读
	PeopleMightKnow->setRowCount(n);//设置行数为n
	PeopleMightKnow->setColumnCount(2);//设置列数为2
	QStringList header;
	header << u8"陌生人" << u8"关联度";
	PeopleMightKnow->setHorizontalHeaderLabels(header);
	int x = 0;
	for (int q = 0; q < SN->People.elem[i]->CondextOfFriends.ListLength(); ++q) {
		if (SN->People.elem[i]->CondextOfFriends.elem[q].Relevancy)
		{
			QString num;
			num.setNum(SN->People.elem[i]->CondextOfFriends.elem[q].Relevancy);
			PeopleMightKnow->setItem(x, 0, new QTableWidgetItem(SN->People.elem[i]->CondextOfFriends.elem[q].Name));
			PeopleMightKnow->setItem(x, 1, new QTableWidgetItem(num));
			++x;
		}
	}

	Screen->SN_Painter = SN;
	Screen->i = i;
	Screen->update();
}

void MainWindow::PeopleListItemDoubleClicked(QListWidgetItem *item)
{
	AFD = new AddFriendsDialog;
	connect(AFD, SIGNAL(sendNewFriendData(QStringList)), this, SLOT(receiveNewFriendsData(QStringList)));
	QString TempName;
	TempName = item->text();
	int n = SN->People.ListLength();
	int i;//定位到底是哪个成员
	for (i = 0; i < n; ++i) {
		if (TempName == SN->People.elem[i]->Name)
			break;
	}
	*(AFD->currentperson) = TempName;
	int friendslist_length = SN->People.elem[i]->Friends.ListLength();
	if (!friendslist_length)//该成员还没有朋友
		for (int j = 0; j < n; ++j) {
			if (SN->People.elem[j]->Name != TempName) {
				QListWidgetItem *tempelem = new QListWidgetItem(SN->People.elem[j]->Name, AFD->StrangerList);
				tempelem->setFlags(Qt::ItemIsEnabled | Qt::ItemIsUserCheckable);
				tempelem->setCheckState(Qt::Unchecked);
			}
		}
	else
		for (int j = 0; j < n; ++j) {
			if (SN->People.elem[j]->Name != TempName) {
				int k;
				for (k = 0; k < friendslist_length; ++k) {
					if (SN->People.elem[j]->Name == SN->People.elem[i]->Friends.elem[k]->Name)
						break;
				}
				if (k == friendslist_length) {//该成员的朋友中没有此人
					QListWidgetItem *tempelem = new QListWidgetItem(SN->People.elem[j]->Name, AFD->StrangerList);
					tempelem->setFlags(Qt::ItemIsEnabled | Qt::ItemIsUserCheckable);
					tempelem->setCheckState(Qt::Unchecked);
				}
			}
		}
	AFD->show();
}