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
		cout << "ѡ�ֱ��:" << it->first
			<< "\tѡ������:" << it->second.name
			<< "\tѡ�ֳɼ�:" << it->second.score[0] << endl;
	}*/

	int select = 0;
	
	while (true) {
		sm.show_Menu();
		cout << "����������ѡ��:" << endl;
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
			cout << "�������" << endl;
			system("cls");
			break;
		}
	}
	system("pause");
	return 0;
}