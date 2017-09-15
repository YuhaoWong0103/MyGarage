#include "PersonalInformation.h"

PersonalInformation::PersonalInformation(QString Name_Input, QString Area_Input, QString PrimarySchool_Input, QString MiddleSchool_Input, QString University_Input, QString Company_Input)
{
	Name = Name_Input;
	Area = Area_Input;
	PrimarySchool = PrimarySchool_Input;
	MiddleSchool = MiddleSchool_Input;
	University = University_Input;
	Company = Company_Input;
	x_of_screen = 0;
	y_of_screen = 0;
}

void PersonalInformation::AddFriends(PersonalInformation *p)
{
	Friends.ListInsert(1, p);//新增的朋友固定插在第一位
}

void PersonalInformation::AddGroups(QString Group_Input)
{
	Groups.append(Group_Input);
}