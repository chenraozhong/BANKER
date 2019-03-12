// 银行家算法模拟.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "Init_Message.h"
#include "Safe_Sequence_Sort.h"

int main()
{
	InitCls my_AvaliableNumber(4, 4);
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

