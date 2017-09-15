#include "SocialNetworks.h"

void SocialNetworks::AddNewMember(PersonalInformation *p)
{
	People.ListInsert(1, p);
}

InputDialog::InputDialog(QWidget *parent)
	: QDialog(parent)
{
	Name_Dialog = new QLabel/*(this)*/;
	NameValue_Dialog = new QLineEdit/*(this)*/;
	Area_Dialog = new QLabel/*(this)*/;
	AreaValue_Dialog = new QLineEdit/*(this)*/;
	PrimarySchool_Dialog = new QLabel/*(this)*/;
	PrimarySchoolValue_Dialog = new QLineEdit/*(this)*/;
	MiddleSchool_Dialog = new QLabel/*(this)*/;
	MiddleSchoolValue_Dialog = new QLineEdit/*(this)*/;
	University_Dialog = new QLabel/*(this)*/;
	UniversityValue_Dialog = new QLineEdit/*(this)*/;
	Company_Dialog = new QLabel/*(this)*/;
	CompanyValue_Dialog = new QLineEdit/*(this)*/;
	//Friends_Dialog = new QLabel;
	//FriendsValue_Dialog = new QLineEdit;
	Groups_Dialog = new QLabel;
	GroupsValue_Dialog = new QLineEdit;
	OKButton = new QPushButton;
	CancelButton = new QPushButton;

	QLabel *Note = new QLabel;
	Note->setText(u8"注：群组的输入请用英文符“,”进行分隔");

	Name_Dialog->setText(u8"姓名：");
	Area_Dialog->setText(u8"地址：");
	PrimarySchool_Dialog->setText(u8"小学：");
	MiddleSchool_Dialog->setText(u8"中学：");
	University_Dialog->setText(u8"大学：");
	Company_Dialog->setText(u8"公司：");
	//Friends_Dialog->setText(u8"朋友：");
	Groups_Dialog->setText(u8"群组：");
	OKButton->setText(u8"确定");
	CancelButton->setText(u8"取消");

	QHBoxLayout * hlayout_name_dialog = new QHBoxLayout;
	QHBoxLayout * hlayout_area_dialog = new QHBoxLayout;
	QHBoxLayout * hlayout_primaryschool_dialog = new QHBoxLayout;
	QHBoxLayout * hlayout_middleschool_dialog = new QHBoxLayout;
	QHBoxLayout * hlayout_university_dialog = new QHBoxLayout;
	QHBoxLayout * hlayout_company_dialog = new QHBoxLayout;
	QHBoxLayout * hlayout_friends_dialog = new QHBoxLayout;
	QHBoxLayout * hlayout_groups_dialog = new QHBoxLayout;
	QVBoxLayout * vlayout_information = new QVBoxLayout;
	QHBoxLayout * hlayout_ok_and_cancel = new QHBoxLayout;
	QVBoxLayout * vlayout_main = new QVBoxLayout;

	hlayout_name_dialog->addWidget(Name_Dialog);
	hlayout_name_dialog->addWidget(NameValue_Dialog);
	hlayout_area_dialog->addWidget(Area_Dialog);
	hlayout_area_dialog->addWidget(AreaValue_Dialog);
	hlayout_primaryschool_dialog->addWidget(PrimarySchool_Dialog);
	hlayout_primaryschool_dialog->addWidget(PrimarySchoolValue_Dialog);
	hlayout_middleschool_dialog->addWidget(MiddleSchool_Dialog);
	hlayout_middleschool_dialog->addWidget(MiddleSchoolValue_Dialog);
	hlayout_university_dialog->addWidget(University_Dialog);
	hlayout_university_dialog->addWidget(UniversityValue_Dialog);
	hlayout_company_dialog->addWidget(Company_Dialog);
	hlayout_company_dialog->addWidget(CompanyValue_Dialog);
	//hlayout_friends_dialog->addWidget(Friends_Dialog);
	//hlayout_friends_dialog->addWidget(FriendsValue_Dialog);
	hlayout_groups_dialog->addWidget(Groups_Dialog);
	hlayout_groups_dialog->addWidget(GroupsValue_Dialog);
	vlayout_information->addLayout(hlayout_name_dialog);
	vlayout_information->addLayout(hlayout_area_dialog);
	vlayout_information->addLayout(hlayout_primaryschool_dialog);
	vlayout_information->addLayout(hlayout_middleschool_dialog);
	vlayout_information->addLayout(hlayout_university_dialog);
	vlayout_information->addLayout(hlayout_company_dialog);
	//vlayout_information->addLayout(hlayout_friends_dialog);
	vlayout_information->addLayout(hlayout_groups_dialog);
	vlayout_information->addWidget(Note);
	hlayout_ok_and_cancel->addWidget(OKButton);
	hlayout_ok_and_cancel->addWidget(CancelButton);
	vlayout_main->addLayout(vlayout_information);
	vlayout_main->addLayout(hlayout_ok_and_cancel);

	connect(OKButton, SIGNAL(clicked()), this, SLOT(OKClicked()));
	connect(CancelButton, SIGNAL(clicked()), this, SLOT(CancelClicked()));

	setLayout(vlayout_main);
	setWindowTitle(u8"添加新成员");
	setFixedHeight(sizeHint().height());
	
}

InputDialog::~InputDialog()
{

}

void InputDialog::OKClicked()
{
	QStringList INF;
	QString Temp;
	QStringList friends;
	QStringList groups;

	INF.append(NameValue_Dialog->text());
	INF.append(AreaValue_Dialog->text());
	INF.append(PrimarySchoolValue_Dialog->text());
	INF.append(MiddleSchoolValue_Dialog->text());
	INF.append(UniversityValue_Dialog->text());
	INF.append(CompanyValue_Dialog->text());

	Temp = GroupsValue_Dialog->text();
	groups = Temp.split(",");

	emit sendData(INF,groups);
	this->close();
}

void InputDialog::CancelClicked()
{
	this->close();
}

AddFriendsDialog::AddFriendsDialog(QWidget *parent)
	: QDialog(parent)
{
	StrangerList = new QListWidget;
	OKButton = new QPushButton;
	CancelButton = new QPushButton;
	newfriendspos = new int[MAX_NUMBER_OF_FRIENDS];
	for (int i = 0; i < 100; ++i)
		newfriendspos[i] = -1;
	//朋友位置数组赋初值
	currentperson = new QString;
	OKButton->setText(u8"添加好友");
	CancelButton->setText(u8"取消");

	QHBoxLayout *hlayout_pushbutton = new QHBoxLayout;
	QVBoxLayout *vlayout_main = new QVBoxLayout;

	hlayout_pushbutton->addWidget(OKButton);
	hlayout_pushbutton->addWidget(CancelButton);
	vlayout_main->addWidget(StrangerList);
	vlayout_main->addLayout(hlayout_pushbutton);

	connect(OKButton, SIGNAL(clicked()), this, SLOT(OKClicked()));
	connect(CancelButton, SIGNAL(clicked()), this, SLOT(CancelClicked()));
	//connect(StrangerList, SIGNAL(currentRowChanged(int)), this, SLOT(CurrentRowChangedHappens(int)));
	connect(StrangerList, SIGNAL(itemClicked(QListWidgetItem *)), this, SLOT(CurrentRowClickedHappens(QListWidgetItem *)));
	setLayout(vlayout_main);
	setWindowTitle(u8"添加好友");
	setFixedHeight(sizeHint().height());
}

AddFriendsDialog::~AddFriendsDialog()
{

}

void AddFriendsDialog::OKClicked()
{
	QStringList newfriends;
	QString temp;
	QListWidgetItem* p;
	int n = StrangerList->count();
	for (int i = 0; i < n; ++i) {
		if (newfriendspos[i] != -1) {
			p = StrangerList->item(i);
			temp = p->text();
			newfriends.append(temp);
		}
	}

	emit sendNewFriendData(newfriends);
	this->close();
}

void AddFriendsDialog::CancelClicked()
{
	this->close();
}

void AddFriendsDialog::CurrentRowClickedHappens(QListWidgetItem *item)
{
	if (item->checkState() == Qt::Checked) {
		int i;
		QString temp = item->text();
		for (i = 0; i < StrangerList->count(); ++i)
			if (temp == StrangerList->item(i)->text())
				break;
		newfriendspos[i] = i;
	}
}

DrawWidget::DrawWidget(QWidget *p) :QWidget(p)
{
	SN_Painter = NULL;
}

void DrawWidget::paintEvent(QPaintEvent *event)
{
	//显示该成员的社交网络
	//先将所有人排在一条圆弧上，是朋友就连线，可能认识则连虚线
	//n为社交成员总数，i为当前点击的成员
	if (SN_Painter)//已经得到值了
	{
		/*QPen pen;
		pen.setBrush(QBrush(Qt::red));
		QVector<qreal> dashes;
		qreal space = 3;
		dashes << 5 << space << 5 << space;
		pen.setDashPattern(dashes);
		pen.setWidth(2);*/

		QPainter painter(this);

		int BaseRadius = 200;//基础半径
		int MemberRadius = 50;//社交成员半径
		painter.setPen(Qt::white);
		painter.setBrush(Qt::blue);

		int n = SN_Painter->People.ListLength();

		double X_ITEM;
		double Y_ITEM;
		double X_ITEM_NAME;
		double Y_ITEM_NAME;

		int X_ZERO = Width_Of_Screen / 2;
		int Y_ZERO = Length_of_Screen / 2;

		for (int z = 0; z < n; ++z) {//画成员
			X_ITEM = BaseRadius*cos(2 * PI_OF_MINE * z / n);
			Y_ITEM = BaseRadius*sin(2 * PI_OF_MINE * z / n);
			X_ITEM_NAME = (BaseRadius /*- MemberRadius / 4*/)*cos(2 * PI_OF_MINE * z / n) + MemberRadius / 12;
			Y_ITEM_NAME = (BaseRadius /*- MemberRadius / 4*/)*sin(2 * PI_OF_MINE * z / n) + 3*MemberRadius / 5;
			int X_ITEM_REAL = (int)X_ITEM + X_ZERO;
			int Y_ITEM_REAL = (int)Y_ITEM + Y_ZERO;
			int X_ITEM_NAME_REAL = (int)X_ITEM_NAME + X_ZERO;
			int Y_ITEM_NAME_REAL = (int)Y_ITEM_NAME + Y_ZERO;
			SN_Painter->People.elem[z]->x_of_screen = X_ITEM_REAL + MemberRadius / 2;
			SN_Painter->People.elem[z]->y_of_screen = Y_ITEM_REAL + MemberRadius / 2;
			if (z == i)
			{
				painter.setBrush(Qt::yellow);
				painter.setPen(Qt::black);
			}
			else {
				painter.setPen(Qt::white);
				painter.setBrush(Qt::blue);
			}
			painter.drawEllipse(X_ITEM_REAL, Y_ITEM_REAL, MemberRadius, MemberRadius);
			painter.drawText(X_ITEM_NAME_REAL, Y_ITEM_NAME_REAL, SN_Painter->People.elem[z]->Name);
		}
		for (int k = 0; k < SN_Painter->People.elem[i]->Friends.ListLength(); ++k) {//朋友连线
			painter.setPen(Qt::red);
			painter.drawLine(SN_Painter->People.elem[i]->x_of_screen, SN_Painter->People.elem[i]->y_of_screen, SN_Painter->People.elem[i]->Friends.elem[k]->x_of_screen, SN_Painter->People.elem[i]->Friends.elem[k]->y_of_screen);
		}
		for (int k = 0; k < SN_Painter->People.elem[i]->CondextOfFriends.ListLength(); ++k) {//陌生人连线
			painter.setPen(Qt::green);
			for (int w = 0; w < n; ++w) {
				if (SN_Painter->People.elem[i]->CondextOfFriends.elem[k].Relevancy > 0 && (SN_Painter->People.elem[i]->CondextOfFriends.elem[k].Name == SN_Painter->People.elem[w]->Name))
				{
					painter.drawLine(SN_Painter->People.elem[i]->x_of_screen, SN_Painter->People.elem[i]->y_of_screen, SN_Painter->People.elem[w]->x_of_screen, SN_Painter->People.elem[w]->y_of_screen);
					break;
				}
			}
			//painter.drawLine(SN_Painter->People.elem[i]->x_of_screen, SN_Painter->People.elem[i]->y_of_screen,)
		}
	}
}