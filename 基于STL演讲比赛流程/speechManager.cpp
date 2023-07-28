#include "speechManager.h"

SpeechManager:: SpeechManager()
{
	this->initSpeech();

	this->createSpeaker();

	this->readRecord();
}

SpeechManager:: ~SpeechManager()
{

}



void SpeechManager:: show_Menu()
{
	cout << "*************************" << endl;
	cout << "*****��ӭ�μ��ݽ�����****" << endl;
	cout << "******1.��ʼ�ݽ�����*****" << endl;
	cout << "******2.�鿴�����¼*****" << endl;
	cout << "******3.��ձ�����¼*****" << endl;
	cout << "******0.�˳���������*****" << endl;
	cout << endl;
}

void SpeechManager::initSpeech()
{
	this->v1.clear();
	this->v2.clear();
	this->victory.clear();
	this->m_speaker.clear();
	this->index = 1;
	this->record.clear();
}

void SpeechManager::createSpeaker()
{
	string nameSeed = "ABCDEFGHIJKL";
	for (int i = 0; i < nameSeed.size(); i++)
	{
		string name = "ѡ��";
		name += nameSeed[i];

		Speaker sp;
		sp.name = name;
		for (int j = 0; j < 2; j++)
		{
			sp.score[j] = 0;
		}
		this->v1.push_back(i + 1001);

		this->m_speaker.insert(make_pair(i + 1001, sp));
	}
}

void SpeechManager::startSpeeech()
{
	this->speechDraw();

	this->speechContest();

	this->showScore();

	this->index++;
	//����
	this->speechContest();

	this->showScore();

	this->saveRecord();

	//����
	this->initSpeech();

	this->createSpeaker();
	
	this->readRecord();

	cout << "-----�����������----" << endl;
	system("pause");
	system("cls");
}

void SpeechManager::speechDraw()
{
	cout << "��" << this->index << "�ֱ���ѡ�����ڳ�ǩ" << endl;
	cout << "-------------" << endl;
	cout << "��ǩ���ݽ�˳������" << endl;
	if (this->index == 1)
	{
		random_shuffle(v1.begin(), v1.end());
		for (vector<int>::iterator it = v1.begin(); it != v1.end(); it++)
		{
			cout << *it << " ";
		}
		cout << endl;
	}
	else
	{
		random_shuffle(v2.begin(), v2.end());
		for (vector<int>::iterator it = v2.begin(); it != v2.end(); it++)
		{
			cout << *it << " ";
		}
		cout << endl;
	}
	cout << "--------" << endl;
	system("pause");
	cout << endl;
}

void SpeechManager::speechContest()
{
	cout << "--------��" << this->index << "�ֱ���-------" << endl;

	multimap<double, int, greater<int>>groupScore;

	int num = 0;

	vector<int>v_Src;

	if (this->index == 1)
	{
		v_Src = this->v1;
	}
	else
	{
		v_Src = this->v2;
	}
	for (vector<int>::iterator it = v_Src.begin(); it != v_Src.end(); it++)
	{
		num++;

		deque<double>d;
		for (int j = 0; j < 10; j++)
		{
			double sc = (rand() % 401 + 600) / 10.f;
			d.push_back(sc);
		}
		sort(d.begin(), d.end(),greater<double>());
		d.pop_back();
		d.pop_front();

		double sum = accumulate(d.begin(), d.end(), 0.0f);
		double avg = sum / (double)d.size();

		//cout << "���" << *it << "ѡ��" << this->m_speaker[*it].name << "���ƽ����" << avg << endl;

		this->m_speaker[*it].score[this->index - 1] = avg;

		groupScore.insert(make_pair(avg, *it));
		if (num % 6 == 0)
		{
			cout << "��" << num / 6 << "С���������" << endl;
			for (multimap<double, int, greater<double>>::iterator it2 = groupScore.begin(); it2 != groupScore.end(); it2++)
			{
				cout << "���:" << it2->second << "\t����:" << this->m_speaker[it2->second].name << "\t�ɼ�:" << it2->first << endl;
			}

			int count = 3;
			for (multimap<double, int, greater<double>>::iterator it3 = groupScore.begin(); it3 != groupScore.end()&&count>0; it3++,count--)
			{
				if (this->index == 1)
				{
					this->v2.push_back(it3->second);
				}
				else
				{
					this->victory.push_back(it3->second);
				}
			}
			groupScore.clear();
			cout << endl;
		}
	}
	cout << "-------��" << this->index << "�ֱ�������" << endl;
	system("pause");
}

void SpeechManager::showScore()
{
	cout << "-------��" << this->index << "�ֽ���ѡ������" << endl;
	vector<int>v;
	if (this->index == 1)
	{
		v = this->v2;
	}
	else
	{
		v = this->victory;
	}
	for (vector<int>::iterator it = v.begin(); it != v.end(); it++)
	{
		cout << "���:" << *it << "\t\t����:" << this->m_speaker[*it].name << "\t\tѡ�ֵ÷�:" << this->m_speaker[*it].score[this->index - 1] << endl;
	}
	cout << endl;
	system("pause");
	system("cls");
	this->show_Menu();
}

void SpeechManager::saveRecord()
{
	ofstream ofs;
	ofs.open("test.csv", ios::out | ios::app);

	for (vector<int>::iterator it = this->victory.begin(); it != this->victory.end(); it++)
	{
		ofs << *it << ","
			<< this->m_speaker[*it].score[1] << ",";
	}
	ofs << endl;

	ofs.close();
	cout << "��¼����ɹ�" << endl;

	fileIsEmpty = false;
}

void SpeechManager::readRecord()
{
	ifstream ifs;
	ifs.open("test.csv", ios::in);

	if (!ifs.is_open())
	{
		this->fileIsEmpty = true;
		ifs.close();
		return;
	}
	
	char ch;
	ifs >> ch;
	if (ifs.eof())
	{
		this->fileIsEmpty = true;
		ifs.close();
		return;
	}

	this->fileIsEmpty = false;

	ifs.putback(ch);

	string data;
	int index = 0;
	while (ifs >> data)
	{
		vector<string>v;
		int pos = -1;
		int start = 0;
		while (true)
		{
			pos = data.find(",", start);
			if (pos == -1)
			{
				break;
			}
			string tmp = data.substr(start, pos - start);

			v.push_back(tmp);
			start = pos + 1;
		}
		this->record.insert(make_pair(index, v));
		index++;
	}
	ifs.close();
}

void SpeechManager::showRecord()
{
	if (this->fileIsEmpty == true)
	{
		cout << "�ļ�Ϊ��" << endl;
	}
	for (map<int, vector<string>>::iterator it = record.begin(); it != record.end(); it++)
	{
		cout << "��" << it->first + 1 << "��"
			<< "\t�ھ����" << it->second[0] << "\t�÷�" << it->second[1]
			<< "\t�Ǿ����" << it->second[2] << "\t�÷�" << it->second[3]
			<< "\t�������" << it->second[4] << "\t�÷�" << it->second[5]
			<< endl;
	}
}

void SpeechManager::clearRecord()
{
	cout << "ȷ�����?" << endl;
	cout << "1.ȷ��" << endl;
	cout << "2.����" << endl;
	int select = 0;
	cin >> select;
	if (select == 1)
	{
		ofstream ofs("test.csv", ios::trunc);
		ofs.close();
		this->initSpeech();
		this->createSpeaker();
		this->readRecord();
		this->fileIsEmpty = true;
		cout << "��ճɹ�" << endl;
	}
	system("pause");
	system("cls");
}

void SpeechManager:: exitSystem()
{
	cout << "��ӭ�´�ʹ��" << endl;
	system("pause");
	exit(0);
}

