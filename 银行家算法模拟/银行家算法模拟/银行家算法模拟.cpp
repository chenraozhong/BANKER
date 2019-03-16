// banker_do.cpp : 定义控制台应用程序的入口点。
//
#include "stdafx.h"
#include "Init_Message.h"
#include"Safe_Sequence_Produce.h"
#include<iostream>
#include<sstream>
#include<string>
#include<vector>
#include<map>
using namespace std;

int main()
{
	InitCls myInit(10, 9);
	myInit.Init();
	SqeCls mySafePro;
	mySafePro.SqeCls_Run();
	system("pause");
	return 0;
}