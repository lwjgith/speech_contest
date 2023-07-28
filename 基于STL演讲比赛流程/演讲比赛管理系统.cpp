#include<iostream>
using namespace std;
#include"speechManager.h"
#include<string>

int main()
{
	srand((unsigned int)time(NULL));
	SpeechManager sm;

	/*for (map<int, Speaker>::iterator it = sm.m_speaker.begin(); it != sm.m_speaker.end(); it++)
	{
		cout << "选手编号:" << it->first
			<< "\t选手姓名:" << it->second.name
			<< "\t选手成绩:" << it->second.score[0] << endl;
	}*/

	int select = 0;
	
	while (true) {
		sm.show_Menu();
		cout << "请输入您的选择:" << endl;
		cin >> select;
		switch (select)
		{
		case 1:
			sm.startSpeeech();
			break;
		case 2:
			sm.showRecord();
			break;
		case 3:
			sm.clearRecord();
			break;
		case 0:
			sm.exitSystem();
			break;
		default:
			cout << "输入错误" << endl;
			system("cls");
			break;
		}
	}
	system("pause");
	return 0;
}