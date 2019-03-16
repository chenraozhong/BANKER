#include "stdafx.h"
#include "Safe_Sequence_Sort.h"
#include<iostream>
#include<algorithm>
#include<sstream>
#include<string>


void Sort_Sequence_SortCls::ReadOfSafeAndWeight() {
	int i = 0;
	string my_txtline;
	vector<string> my_SafeSequenceSave;//临时存储安全序列
	vector<int> my_WeightNumSave;//存储加权数

	m_ReadSafeSequencetxt.open("Safe_Weight.txt");
	if (!m_ReadSafeSequencetxt.is_open()) {
		cerr << "the safe_aequence don't open! error 21 ! " << endl;
	}
	while (getline(m_ReadSafeSequencetxt, my_txtline)) {
		int my_chartonum;
		stringstream ch(my_txtline);
		if (i % 2 == 0)
			my_SafeSequenceSave.push_back(my_txtline);
		while (ch >> my_chartonum) {
			if (i % 2 != 0)
				my_WeightNumSave.push_back(my_chartonum);
		}//while (ch >> my_chartonum)
		i++;
	}//while (getline(m_ReadSafeSequencetxt, my_txtline)) 
	m_ReadSafeSequencetxt.close();

	if (my_SafeSequenceSave.size() != my_WeightNumSave.size())//两个数组长度一定相等
		cout << "input error!" << endl;
	else {
		for (int i = 0; i < my_WeightNumSave.size(); i++) {
			m_SafeAndWeight.push_back(make_pair(my_SafeSequenceSave[i], my_WeightNumSave[i]));
		}//for (int i = 0; i < my_WeightNumSave.size(); i++)
	}
}
bool cmp(const pair<string, int>& a1, const pair<string, int>& a2) {
	return a1.second > a2.second;
}
void Sort_Sequence_SortCls::SortOfWeight() {
	sort(m_SafeAndWeight.begin(), m_SafeAndWeight.end(), cmp);
}
void Sort_Sequence_SortCls::WriteOfSafeAndWeight() {
	int my_number;
	m_WriteSafeSequence.open("Sort_Safe_Weight.txt");
	if (!m_WriteSafeSequence.is_open()) {
		cerr << "the sort_safe_weight don't open! error 22 !" << endl;
	}
	for (int i = 0; i < m_SafeAndWeight.size(); i++) {
		m_WriteSafeSequence << m_SafeAndWeight[i].first << endl << m_SafeAndWeight[i].second ;
		if (i < m_SafeAndWeight.size() - 1)
			m_WriteSafeSequence << endl;
	}//for (int i = 0; i < m_SafeAndWeight.size(); i++)
	m_WriteSafeSequence.close();
}