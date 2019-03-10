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
	vector<int> m_Source;
	vector<int> m_Remain_Source;
	vector<int, vector<int> > m_Allocation;
//	vector<int, vector<int> > m_MAXRequest;//客户对资源的需求量
//	vector<int, vector<int> > m_Request;
//	vector<int, int> m_Duration;
	/*
	vector<map<int, string> > m_Release: string由用户编码+时间点构成。
	例如：m_Release[2]=<5,1_9>; 表明2号资源在第9时刻被1号客户释放，释放量为5
	*/
	/*
	vector<map<int, string> >  m_Release;//资源释放的时间点和量
	*/
public:
	void Sqe_Messageinit();
	void Sqe_Sourseinit();
	void Sqe_Allocationinit();
	void Sqe_RemainSourceinit();
	void Sqe_RequestAndDuration();
};

#endif