// banker_do.cpp : 定义控制台应用程序的入口点。
//
#include "stdafx.h"
#include "InitCls.h"
int main()
{
	InitCls my_AvaliableNumber(4, 4);
	my_AvaliableNumber.InitRandomOfAvailable();
	my_AvaliableNumber.InitRandomOfMax();
	my_AvaliableNumber.InitRandomOfAllocationAndTime();
	system("pause");
	return 0;
}