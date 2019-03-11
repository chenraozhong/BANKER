// banker_do.cpp : 定义控制台应用程序的入口点。
//
#include "stdafx.h"
//#include "Init_Message.h"
//#include"Safe_Sequence_Produce.h"
#include<iostream>
#include<sstream>
#include<string>
#include<vector>
#include<map>
using namespace std;

int main()
{
	/*
	InitCls my_AvaliableNumber(4, 4);
	my_AvaliableNumber.InitRandomOfAvailable();
	my_AvaliableNumber.InitRandomOfMax();
	my_AvaliableNumber.InitRandomOfAllocationAndTime();
	*/
	//SqeCls ss;
	//ss.SqeCls_Messageinit();
	/*
	vector<vector<int> > value;
	vector<int> value1;
	value.push_back(value1);
	value.push_back(value1);
	value.push_back(value1);
	value[1] = value1;
	map<int, int> mymap;
	mymap[2] = 3;
	map<int, int>::iterator item = mymap.find(2);
	if (item!=mymap.end()) cout << "能找到" << endl;
	mymap[2] += 5;
	cout << mymap[2];
	*/
	/*
	map<int, int> map1;
	map<int, int> map2;
	map1[1] = 2;
	map1[2] = 3;
	map2 = map1;
	map1[3] = 4;
	map<int, int>::iterator myitem = map1.begin();
	for (; myitem != map1.end(); myitem++)
		cout << myitem->second;
		*/
	vector<int> my;
	my.push_back(1);
	my.push_back(2);
	my.push_back(3);
	my.push_back(4);
	vector<int>::iterator item = my.begin();
	for (; item != my.end(); item++)
		if (*item == 2) break;
	my.erase(item);
	for (int i = 0; i < my.size(); i++)
		cout << my[i] << endl;
	system("pause");
	return 0;
}