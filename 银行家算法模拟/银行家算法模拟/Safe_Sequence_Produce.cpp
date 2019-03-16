#include "stdafx.h"
#include"Safe_Sequence_Produce.h"
#include<fstream>
#include<string>
#include<sstream>
#include<map>
#include"gobal.h"
using namespace std;
#ifndef _SAFE_SEQUENCE_PRODUCE_CPP
#define _SAFE_SEQUENCE_PRODUCE_CPP

int _SystemTime = 0;
int _ThreholdValue = 30;

void Eraser(vector<int> &sequence, int value) {
	vector<int>::iterator myitem = sequence.begin();
	for (; myitem != sequence.end(); myitem++) {
		if (*myitem == value) break;
	}
	if (myitem == sequence.end()) {
		cerr << "队列中无此数值，出错";
		exit(1);
	}
	else sequence.erase(myitem);
}

void Push_Back(vector<int> &sequence, int value) {
	vector<int>::iterator myitem = sequence.begin();
	for (; myitem != sequence.end(); myitem++) {
		if (*myitem == value) break;
	}
	if (myitem != sequence.end()) {
		cerr << "队列已存在数值，出错";
		exit(1);
	}
	else sequence.push_back(value);
}

int StrToNum(string str) {
	stringstream ss(str);
	int myvalue = 0;
	ss >> myvalue;
	return myvalue;
}

/*
将字符串str转换成数字并存储到value中
*/
void StrToVector(string str, vector<int> &value) {
	char myletter = ' ';
	int myvalue = 0;
	string mydigal = "";
	for (int i = 0; i < str.size(); i++) {
		myletter = str[i];
		if (myletter == ' ') {
			myvalue = StrToNum(mydigal);
			value.push_back(myvalue);
			mydigal = "";
			continue;
		}
		else {
			mydigal += myletter;
		}
	}
	if (!mydigal.empty()) {
		myvalue = StrToNum(mydigal);
		value.push_back(myvalue);
	}
}

/*
将从file文档中读取的信息存储到value中
*/
void FileToVector(string file, vector<vector<int> > &value) {
	ifstream in;
	in.open(file);
	if (!in) {
		cerr << file << "文件打开失败";
	}
	string mystr;
	getline(in, mystr);
	while (!in.eof()) {
		vector<int> myvalue;
		StrToVector(mystr, myvalue);
		value.push_back(myvalue);
		getline(in, mystr);
	}
	in.close();
}

SqeCls::SqeCls() {
	m_SafeAndScore.open("SafeAndScore.txt");
}

SqeCls::~SqeCls() {
	m_SafeAndScore.close();
}

void SqeCls::SqeCls_Sourseinit() {//对系统资源进行更新
	ifstream in;
	string myfile = "Available.txt";
	in.open(myfile);
	if (!in) {
		cerr << myfile << "文件打开失败";
	}
	string mystr = "";
	getline(in, mystr);
	StrToVector(mystr, m_Source);
	in.close();
}

void SqeCls::SqeCls_Remaininit() {
	for (int i = 0; i < m_Source.size(); i++) {
		int sum = 0;
		for (int j = 0; j < m_Allocation.size(); j++) {
			sum += m_Allocation[j][i];
		}
		m_Remain.push_back(m_Source[i] - sum);
	}
}

void SqeCls::SqeCls_Allocationinit() {
	FileToVector("Allocation.txt", m_Allocation);//将从文件中读取的字符串转换成vector数据
}

void SqeCls::SqeCls_Durationinit() {
	FileToVector("Duration.txt", m_Duration);
}

void SqeCls::SqeCls_MAXRequestinit() {
	FileToVector("Max.txt", m_MAXRequest);
}

void SqeCls::SqeCls_Requestinit() {
	for (int i = 0; i < m_Allocation.size(); i++) {
		vector<int> value;
		for (int j = 0; j < m_Source.size(); j++) {
			value.push_back(m_MAXRequest[i][j] - m_Allocation[i][j]);
		}
		m_Request.push_back(value);
	}
}

void SqeCls::SqeCls_Releaseinit() {
	for (int i = 0; i < m_Source.size(); i++) {
		map<int, int> myvalue;
		m_Release.push_back(myvalue);
	}
}

void SqeCls::SqeCls_Messageinit() {
	SqeCls_Sourseinit();//初始化系统资源
	SqeCls_Allocationinit();//初始化已分配资源
	SqeCls_Durationinit();//初始化客户占用资源时间
	SqeCls_Remaininit();//初始化系统剩余资源
	SqeCls_MAXRequestinit();//初始化客户最大需求量
	SqeCls_Requestinit();//初始化客户还需资源
	SqeCls_Releaseinit();//初始化各资源释放信息
	m_clientnum = m_Allocation.size();
	m_sourcenum = m_Source.size();
}

/*
更新系统剩余资源信息，并将currtime之前的资源该释放的资源全部释放掉
*/
void SqeCls::SqeCls_UpdateRemain(vector<int> remain,vector<map<int,int> > release,int currtime) {
	for (int i = 0; i < remain.size(); i++) {
		map<int, int>::iterator myitem = release[i].find(currtime);
		if (myitem == release[i].end()) continue;//表示在currtime,资源i不释放
		else {
			remain[i] += release[i][currtime];
			release[i].erase(currtime);
		}
	}
}

int SqeCls::SqeCls_CacluApplyTime(int num,int currtime,vector<int> Remain,vector<map<int,int> > release) {
	vector<int> myremain = Remain;
	int mycount = 0;//记录已经生成的资源种类数
	vector<int> myAllocation;
	for (int i = 0; i < m_Source.size(); i++)
		myAllocation.push_back(0);
	while (mycount < m_Source.size()) {
		int mynum;
		int i = 0;
		for (; i < myAllocation.size(); i++) {
			if (myAllocation[i] != 0) continue;
			else if (myremain[i] >= m_Request[num][i]) {
				myAllocation[i] = 1;
				mycount++;
			}
		}//end of for
		currtime++;
		SqeCls_UpdateRemain(myremain,release, currtime);//更新系统剩余资源
	}//end of while
	return currtime;
}

/*
更新资源在未来释放信息
*/
void SqeCls::SqeCls_UpdateRelease(vector<map<int, int> > release, int num,int currtime) {
	int myrelease = 0;
	for (int i = 0; i < m_Source.size(); i++) {
		myrelease = currtime + m_Duration[num][i];
		map<int, int>::iterator myitem = release[i].find(myrelease);
		if (myitem != release[i].end()) release[i][myrelease] += m_MAXRequest[num][i];
		else release[i][myrelease] = m_MAXRequest[num][i];
	}
}

void SqeCls::SqeCls_UpdateMessage(vector<int> remain, vector<map<int, int> > release, int &currtime, int applytime, int num) {
	_SystemTime += (applytime - currtime);//更新全局系统时间
	while (currtime <= applytime) {
		currtime ++;
		SqeCls_UpdateRemain(remain, release, currtime);
		SqeCls_UpdateRelease(release, num, currtime);
	}
}

/*
判别客户num能不能插入安全序列中，能则返回true,否则返回false
*/
bool SqeCls::SqeCls_Client_Is_Safe(int num, vector<map<int, int> > release, vector<int> remain) {
	vector<int> myremain = remain;
	for (int i = 0; i < remain.size(); i++) {
		if (release[i].empty()) continue;
		map<int, int>::iterator myitem = release[i].begin();
		remain[i] += myitem->second;
	}//end of for
	for (int i = 0; i < m_Request[num].size(); i++) {
		if (m_Request[num][i] > myremain[i]) return false;
	}//end of for
	return true;
}

int SqeCls::SqeCls_FindClient(vector<int> safe, vector<int> pendsearch, vector<map<int, int> > release, vector<int> remain) {
	for (int i = 0; i < pendsearch.size(); i++) {
		if (SqeCls_Client_Is_Safe(pendsearch[i], release, remain))  return pendsearch[i];//如果客户pendsearch[i]能插入安全序列中，则返回pendserach[i]
	}
	return -1;
}

/*
计算全部资源释放时间
*/
int SqeCls::SqeCls_CacluTotalReleaseTime(int currtime,vector<map<int,int> > release ) {
	int mymaxtime = 0;
	for (int i = 0; i < release.size(); i++) {
		map<int, int>::iterator myitem = release[i].begin();
		for (; myitem != release[i].end(); myitem++) {
			if (mymaxtime < myitem->first) mymaxtime = myitem->first;
		}
	}//end of for
	return currtime + mymaxtime;
}

/*
计算资源利用率
*/
double SqeCls::SqeCls_CacluSourceRation(vector<int> remain) {
	double myratio = 0.0;
	for (int i = 0; i < remain.size(); i++) {
		myratio += (double(remain[i]) /double( m_Source[i]));
	}
	return myratio;
}

/*
对全部资源申请时间、全部资源释放时间、资源利用率进行加权计算，得到得分
*/
double SqeCls::SqeCls_Cacluate(int totalApplytime, int totalReleaseTime, double sourceration) {
	double myscore = double(_SystemTime)/double(totalApplytime)*0.6+double(_SystemTime)/double(totalReleaseTime)*0.4+sourceration;//权值还有待商榷
	return myscore;
}

/*
得分计算模块，计算得分，并将安全序列和得分输出到SafeAndScore.txt中
*/
void SqeCls::SqeCls_CacluScore(vector<int> safe,int currtime,vector<map<int,int> > release,vector<int> remain) {
	int mytotalApplyTime = currtime;
	int mytotalReleaseTime = SqeCls_CacluTotalReleaseTime(currtime, release);
	double mySourceRation = SqeCls_CacluSourceRation(remain);
	double myScore = SqeCls_Cacluate(mytotalApplyTime, mytotalReleaseTime, mySourceRation);
	for (int i = 0; i < safe.size(); i++)
		m_SafeAndScore << safe[i] << " ";
	m_SafeAndScore << endl;
	m_SafeAndScore << myScore;
	m_SafeAndScore << endl;
}

void SqeCls::SqeCls_Allocation(int num, int currtime, vector<map<int, int> > release, vector<int> remain, vector<int> safe, vector<int> pendsearch) {
	if (_SystemTime <= _ThreholdValue) {
		int myclientnum = 0;
		Push_Back(safe, num);
		//Eraser(pendsearch, num);
		while (myclientnum != -1) {
			myclientnum = SqeCls_FindClient(safe, pendsearch, release, remain);
			if (myclientnum == -1) {//表示已找不到可插入序列的用户
				if (safe.size() == m_clientnum)//表示该序列是安全序列
					SqeCls_CacluScore(safe,currtime,release,remain);//end of if
				else {
					cout << "该序列不是安全序列" << endl;
				}
			}
			else {
				Eraser(pendsearch, myclientnum);
				int myapplytime = SqeCls_CacluApplyTime(num, currtime, remain, release);
				int mycurrtime = currtime;
				vector<int> myremain = remain;
				vector<map<int, int> > myrelease = release;
				vector<int> mysafe = safe;
				vector<int> mypendsearch = pendsearch;
				SqeCls_UpdateMessage(myremain, myrelease, mycurrtime, myapplytime, num);
				SqeCls_Allocation(myclientnum, currtime, myrelease, myremain, mysafe, mypendsearch);
			}
		}//end of while
	}//end of if 
}

void SqeCls::SqeCls_Run() {
	SqeCls_Messageinit();
	int mycurrtime = 0;
	vector<int> myremain = m_Remain;
	vector<map<int, int> > myrelease=m_Release;
	vector<int> mysafe;
	vector<int> mypendsearch;
	for (int i = 0; i < m_clientnum; i++) mypendsearch.push_back(i);
	int num=SqeCls_FindClient(mysafe, mypendsearch, m_Release, m_Remain);
	if (num == -1) {
		cerr << "随机生成的信息无安全序列，请重新生成";
		exit(1);
	}
	//mysafe.push_back(num);
	Eraser(mypendsearch, num);
	int myapplytime = SqeCls_CacluApplyTime(num, mycurrtime, myremain, myrelease);
	SqeCls_UpdateMessage(myremain, myrelease, mycurrtime, myapplytime, num);
	SqeCls_Allocation(num, mycurrtime, myrelease, myremain, mysafe, mypendsearch);
}

#endif // !_SAFE_SEQUENCE_PRODUCE_CPP
