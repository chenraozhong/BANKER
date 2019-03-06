#pragma once
#pragma once
#include"stdafx.h"
#include<fstream>
#include<vector>
using namespace std;
#ifndef _Message_Init_H
#define _Message_Init_H

class InitCls {
private:
	ofstream m_fSourse;//用于存储系统资源
	ofstream m_fAllocation;//用于存储用户已占有资源情况
						   //ofstream m_fRequest;//用于存储用户还需的资源量和占有时间
	int m;//系统资源种类数(因为还没有界面，所以初始化为3)
		  //int n;//客户数(因为还没有界面，所以初始化)
	vector<int> m_Sourse;

public:
	void InitSourse();//初始化系统资源
					  //void InitAllocation();//初始化用户已占有资源
					  //void InitRequest();//初始化用户还需的资源量和占有时间
};

#endif