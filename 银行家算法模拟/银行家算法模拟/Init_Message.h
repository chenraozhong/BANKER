#pragma once
#include "stdafx.h"
#ifndef _INITCLS_H
#define _INTTCLS_H
#include<fstream>
using namespace std;

class InitCls {
public:
	InitCls(int m, int n);
	void InitRandomOfAvailable();
	void InitRandomOfMax();
	void InitRandomOfAllocation();
	void InitRandomOfTime();
private:
	int m_client;
	int m_resource;
	ofstream m_Available;
	ofstream m_Max;
	ofstream m_Allocation;
	ofstream m_Time;
};

#endif
