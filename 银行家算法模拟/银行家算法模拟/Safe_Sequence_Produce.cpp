#include "stdafx.h"
#include"Safe_Sequence_Produce.h"
#include<fstream>
#include<string>
#include<sstream>
#include<map>
using namespace std;
#ifndef _SAFE_SEQUENCE_PRODUCE_CPP
#define _SAFE_SEQUENCE_PRODUCE_CPP

int StrToNum(string str) {
	stringstream ss(str);
	int myvalue = 0;
	ss >> myvalue;
	return myvalue;
}

void StrToVector(string str, vector<int> value) {
	char myletter = ' ';
	int myvalue = 0;
	string mydigal = "";
	for (int i = 0; i < str.size(); i++) {
		myletter = str[i];
		if (myletter == ' ') {
			myvalue = StrToNum(mydigal);
			value.push_back(myvalue);
			mydigal = "";
			continue;
		}
		else {
			mydigal += myletter;
		}
	}
	if (!mydigal.empty()) {
		myvalue = StrToNum(mydigal);
		value.push_back(myvalue);
	}
}

void FileToVector(string file, vector<vector<int> > value) {
	ifstream in;
	in.open(file);
	if (!in) {
		cerr << file << "文件打开失败";
	}
	string mystr;
	getline(in, mystr);
	while (!in.eof()) {
		vector<int> myvalue;
		StrToVector(mystr, myvalue);
		value.push_back(myvalue);
	}
	in.close();
}

void SqeCls::SqeCls_Sourseinit() {
	ifstream in;
	string myfile = "Available.txt";
	in.open(myfile);
	if (!in) {
		cerr << myfile << "文件打开失败";
	}
	string mystr = "";
	getline(in, mystr);
	StrToVector(mystr, m_Source);
	in.close();
}

void SqeCls::SqeCls_Remaininit() {
	for (int i = 0; i < m_Source.size(); i++) {
		int sum = 0;
		for (int j = 0; j < m_Allocation.size(); j++) {
			sum += m_Allocation[j][i];
		}
		m_Remain.push_back(m_Source[i] - sum);
	}
}

void SqeCls::SqeCls_Allocationinit() {
	FileToVector("Allocation.txt", m_Allocation);
}

void SqeCls::SqeCls_Durationinit() {
	FileToVector("Duration.txt", m_Duration);
}

void SqeCls::SqeCls_MAXRequestinit() {
	FileToVector("Max.txt", m_MAXRequest);
}

void SqeCls::SqeCls_Requestinit() {
	for (int i = 0; i < m_Source.size(); i++) {
		vector<int> value;
		for (int j = 0; j < m_MAXRequest.size(); j++) {
			value.push_back(m_MAXRequest[i][j] - m_Allocation[i][j]);
		}
		m_Request.push_back(value);
	}
}

void SqeCls::SqeCls_Releaseinit() {
	for (int i = 0; i < m_Source.size(); i++) {
		map<int, int> myvalue;
		m_Release.push_back(myvalue);
	}
}

void SqeCls::SqeCls_Messageinit() {
	SqeCls_Sourseinit();
	SqeCls_Allocationinit();
	SqeCls_Durationinit();
	SqeCls_Remaininit();
	SqeCls_MAXRequestinit();
	SqeCls_Requestinit();
	SqeCls_Releaseinit();
}

void SqeCls::SqeCls_UpdateRemain(vector<int> remain,int currtime) {
	for (int i = 0; i < remain.size(); i++) {
		map<int, int>::iterator myitem = m_Release[i].find(currtime);
		if (myitem == m_Release[i].end()) continue;
		else {
			remain[i] += m_Release[i][currtime];
		}
	}
}

int SqeCls::SqeCls_CacluApplyTime(int num,int currtime,vector<int> Remain) {
	vector<int> myremain = Remain;
	int mycount = 0;//记录已经生成的资源种类数
	vector<int> myAllocation;
	for (int i = 0; i < m_Source.size(); i++)
		myAllocation.push_back(0);
	while (mycount < m_Source.size()) {
		int mynum;
		int i = 0;
		for (; i < myAllocation.size(); i++) {
			if (myAllocation[i] != 0) continue;
			else if (myremain[i] >= m_Request[num][i]) {
				myAllocation[i] = 1;
				mycount++;
			}
		}//end of for
		currtime++;
		SqeCls_UpdateRemain(myremain, currtime);
	}//end of while
	return currtime;
}

void SqeCls::SqeCls_UpdateRelease(vector<map<int, int> > release, int num,int currtime) {
	int myrelease = 0;
	for (int i = 0; i < m_Source.size(); i++) {
		myrelease = currtime + m_Duration[num][i];
		map<int, int>::iterator myitem = release[i].find(myrelease);
		if (myitem != release[i].end()) release[i][myrelease] += m_MAXRequest[num][i];
		else release[i][myrelease] = m_MAXRequest[num][i];
	}
}

void SqeCls::SqeCls_UpdateMessage(vector<int> remain, vector<map<int, int> > release, int &currtime, int applytime, int num) {
	_SystemTime += (applytime - currtime);
	currtime += applytime;
	SqeCls_UpdateRemain(remain, currtime);
	SqeCls_UpdateRelease(release, num, currtime);
}

#endif // !_SAFE_SEQUENCE_PRODUCE_CPP
