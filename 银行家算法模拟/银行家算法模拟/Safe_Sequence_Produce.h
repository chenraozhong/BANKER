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

int _SystemTime = 0;
int _ThreholdValue = 500;

class SqeCls {
private:
	int m_sourcenum;
	int m_clientnum;
	vector<int> m_Source;
	vector<int> m_Remain;
	vector<vector<int> > m_Allocation;
	vector<vector<int> > m_MAXRequest;//客户对资源的需求量
	vector<vector<int> > m_Request;
	vector<vector<int> > m_Duration;

	vector<vector<int> > m_Apply;
	/*
	vector<map<int, string> > m_Release: string由用户编码+时间点构成。
	例如：m_Release[2]=<5,1>; 表明2号资源在第5时刻释放，释放量为1
	*/
	vector<map<int, int>>  m_Release;//资源释放的时间点和量

	void SqeCls_Sourseinit();
	void SqeCls_Remaininit();
	void SqeCls_Requestinit();
	void SqeCls_Durationinit();
	void SqeCls_Allocationinit();
	void SqeCls_MAXRequestinit();
	void SqeCls_Releaseinit();
	void SqeCls_UpdateRemain(vector<int> remain,vector<map<int,int> > release,int currtime);
	void SqeCls_UpdateRelease(vector<map<int, int> > release, int num, int currtime);
public:
	void SqeCls_Messageinit();
	int SqeCls_CacluApplyTime(int num,int currtime,vector<int> remain,vector<map<int,int> > release);
	void SqeCls_UpdateMessage(vector<int> remain,vector<map<int,int> > release,int &currtime,int applytime,int num);
	int SqeCls_FindClient(vector<int> safe, vector<int> pendsearch, vector<map<int, int> > release, vector<int> remain);
	bool SqeCls_Client_Is_Safe(int num, vector<map<int, int> > release, vector<int> remain);
	void SqeCls_Allocation(int num, int currtime, vector<map<int, int> > release, vector<int> remain, vector<int> safe, vector<int> pendsearch);
	void SqeCls_Run(int num=1);
};

#endif