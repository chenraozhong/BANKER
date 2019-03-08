#pragma once
#include "stdafx.h"
#ifndef _INITCLS_H
#define _INTTCLS_H
#include<fstream>
using namespace std;

class InitCls {
public:
	InitCls(int m, int n);//构造函数
	void InitRandomOfAvailable();//生成系统各资源量
	void InitRandomOfMax();//生成客户最大资源数
	void InitRandomOfAllocationAndTime();//生成客户已占资源数以及占有时间数
private:
	int m_people;//客户数
	int m_resource;//资源数
	ofstream m_Available;//存储随机生成的系统资源量
	ofstream m_Max;//存储客户最大资源量
	ofstream m_AllocationAndTime;//存储客户已占资源量以及时间占有量
};

#endif

