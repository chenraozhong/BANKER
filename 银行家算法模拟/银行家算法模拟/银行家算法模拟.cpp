// 银行家算法模拟.cpp : 定义控制台应用程序的入口点。

#include "stdafx.h"
#include "Init_Message.h"
#include "Safe_Sequence_Sort.h"
#include<iostream>
using namespace std;

int main()
{
	int m, n;
	cout << "input client is : ";
	cin >> m;
	cout << "input resource is : " ;
	cin >> n;
	cout << "input end!" << endl;

	InitCls my_AvaliableNumber(m, n);
	my_AvaliableNumber.InitRandomOfAvailable();
	my_AvaliableNumber.InitRandomOfMax();
	my_AvaliableNumber.InitRandomOfAllocation();
	my_AvaliableNumber.InitRandomOfTime();

	Sort_Sequence_SortCls my_SafeAndWeight;
	my_SafeAndWeight.ReadOfSafeAndWeight();
	my_SafeAndWeight.SortOfWeight();
	my_SafeAndWeight.WriteOfSafeAndWeight();

	system("pause");
	return 0;
}

