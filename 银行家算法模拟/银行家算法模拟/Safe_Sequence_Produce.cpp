#include "stdafx.h"
#include"Safe_Sequence_Produce.h"
#include<fstream>
#include<string>
#include<sstream>
using namespace std;
#ifndef _SAFE_SEQUENCE_PRODUCE_CPP
#define _SAFE_SEQUENCE_PRODUCE_CPP

int StrToNum(string str) {
	stringstream ss(str);
	int myvalue = 0;
	ss >> myvalue;
	return myvalue;
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
	string mydigal = "";
	char myletter = ' ';
	int myvalue = 0;
	for (int i = 0; i < mystr.size(); i++) {
		myletter = mystr[i];
		if (myletter == ' ') {
			myvalue = StrToNum(mydigal);
			m_Source.push_back(myvalue);
			mydigal = "";
			continue;
		}
		else {
			mydigal += myletter;
		}
	}
	if (!mydigal.empty()) {
		myvalue = StrToNum(mydigal);
		m_Source.push_back(myvalue);
	}
	in.close();
}

void SqeCls::SqeCls_Messageinit() {
	SqeCls_Sourseinit();
	for (int i = 0; i < m_Source.size(); i++)
		cout << m_Source[i] << " ";
	cout << endl;
}

#endif // !_SAFE_SEQUENCE_PRODUCE_CPP
