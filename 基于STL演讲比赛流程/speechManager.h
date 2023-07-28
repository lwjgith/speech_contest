#pragma once
#include<iostream>
using namespace std;
#include<vector>
#include"speaker.h"
#include<map>
#include<string>
#include<algorithm>
#include<ctime>
#include<deque>
#include<functional>
#include<numeric>
#include<fstream>

class SpeechManager
{
public:
	SpeechManager();

	~SpeechManager();

	void show_Menu();

	void exitSystem();

	void initSpeech();

	void createSpeaker();

	void startSpeeech();

	void speechDraw();

	void speechContest();

	void showScore();

	void saveRecord();

	void readRecord();

	void showRecord();

	void clearRecord();

	bool fileIsEmpty;

	map<int, vector<string>>record;

	vector<int>v1;//��һ��

	vector<int>v2;//�ڶ���
	
	vector<int>victory;//ʤ����

	map<int, Speaker>m_speaker;

	int index=1;//����
};