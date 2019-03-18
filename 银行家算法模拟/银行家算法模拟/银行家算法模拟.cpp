// banker_do.cpp : 定义控制台应用程序的入口点。
//
#include "stdafx.h"
#include "Init_Message.h"
#include"Safe_Sequence_Produce.h"
#include"Safe_Sequence_Sort.h"
#include<iostream>
#include<sstream>
#include<string>
#include<vector>
#include<map>
using namespace std;

int main()
{
	InitCls myInit(7, 7);
	myInit.Init();
	SqeCls mySafePro;
	mySafePro.SqeCls_Run();
	Sort_Sequence_SortCls mySort;
	mySort.Run();
	system("pause");
	return 0;
}