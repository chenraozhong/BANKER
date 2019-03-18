#pragma once
#pragma once

#include "stdafx.h"
#ifndef _SAFESORT_H
#define _SAFESORT_H
#include<fstream>
#include<map>
#include<string>
#include<vector>
using namespace std;

class Sort_Sequence_SortCls {
public:
	void ReadOfSafeAndWeight();
	void SortOfWeight();
	void WriteOfSafeAndWeight();
	void Run();
private:
	vector<pair<string, int> > m_SafeAndWeight;
	ifstream m_ReadSafeSequencetxt;
	ofstream m_WriteSafeSequence;
};

#endif