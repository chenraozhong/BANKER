#pragma once
#include"stdafx.h"
#include<fstream>
#include<vector>
#include<string>
#include<iostream>
#include<map>
using namespace std;

#ifndef _SAFE_SEQUENCE_PRODUCE_H
#define _SAFE_SEQUENCE_PRODECE_H

class SqeCls {
private:
	vector<int> m_Source;//系统资源
	vector<int> m_Remain_Source;//系统剩余资源
	vector<int, vector<int> > m_Allocation;//客户已分配资源
	vector<int, vector<int> > m_MAX;//客户资源需求量
	vector<int, vector<int> > m_Request;//客户还需要的资源量
	vector<int, int> m_Duration;//客户对资源的占有时间
	/*
	vector<map<int, string> > m_Release: string由用户编码+时间点构成。
	例如：m_Release[2]=<5,1_9>; 表明2号资源在第9时刻被1号客户释放，释放量为5
	*/
	vector<map<int, string> >  m_Release;//资源释放的时间点和量
public:
	void Sqe_Messageinit();//对基本信息进行初始化
	void Sqe_Sourseinit();//对系统资源进行初始化
	void Sqe_Allocationinit();//已分配资源初始化
	void Sqe_Remaininit();//系统剩余资源初始化
	void Sqe_RequestAndDuration();//客户还需的资源和对资源占有时间初始化

};

#endif