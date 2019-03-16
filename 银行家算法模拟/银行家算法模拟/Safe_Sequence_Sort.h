#pragma once

#include "stdafx.h"
#ifndef _INITCLS_H
#define _INTTCLS_H
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
private:
	vector<pair<string, int> > m_SafeAndWeight;
	ifstream m_ReadSafeSequencetxt;
	ofstream m_WriteSafeSequence;
};

#endif