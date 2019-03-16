#include "stdafx.h"
#include "Init_Message.h"
#include<iostream>
#include<cstdlib>
#include<sstream>
#include<string>
#include<vector>
#include<time.h>


InitCls::InitCls(int m, int n) {
	m_client = m;
	m_resource = n;
}
void InitCls::InitRandomOfAvailable() {
	int my_number;
	srand((unsigned)time(NULL));
	m_Available.open("Available.txt");
	if (!m_Available.is_open()) {
		cerr << "The m_Available don't open! error1!" << endl;
	}
	for (int i = 0; i < m_resource; i++) {
		my_number = rand() % 50 + 50;  //进行最大各资源量的随机生成（50~100)
		m_Available << my_number;
		if (i < m_resource - 1) {   //最后一个不加入空格符
			m_Available << " ";
		}
	}//for (int i = 0; i < m_resource; i++)
	m_Available.close();
}
void InitCls::InitRandomOfMax() {
	string c;
	int my_number1;
	vector<int> my_AvailableFinally;//存储提取的数字

	ifstream my_readofAvailable("Available.txt");
	if (!my_readofAvailable.is_open()) {
		cerr << "The m_Available don't open! error2!" << endl;
	}
	while (getline(my_readofAvailable, c)) {
		int x;
		stringstream s(c);
		while (s >> x) {
			my_AvailableFinally.push_back(x);
		}//while (s >> x)
	}//while (getline(my_readofAvailable, c))
	my_readofAvailable.close();

	m_Max.open("Max.txt");
	if (!m_Max.is_open()) {
		cerr << "The max don't open! error3！" << endl;
	}
	srand((unsigned)time(NULL));
	for (int i = 0; i < m_client; i++) {
		for (int j = 0; j < m_resource; j++) {
			my_number1 = rand() % my_AvailableFinally[j];//生成的资源数可能为零
			m_Max << my_number1;
			if (j < m_resource - 1) {
				m_Max << " ";
			}
		}//for (int j = 0; j < m_resource; j++)
		m_Max << endl;
	}//for (int i = 0; i < m_client; i++)
	m_Max.close();
}
void InitCls::InitRandomOfAllocation() {
	string c1;
	int my_number2, my_time;
	vector<int> my_MaxFinally;//存储Max其中的数字
	vector<int> my_AvailableFina;//存储系统资源量

	ifstream my_ReadOfMax("Max.txt");
	if (!my_ReadOfMax.is_open()) {
		cerr << "The max don't open! error4 !" << endl;
	}
	while (getline(my_ReadOfMax, c1)) {//进行其中数字的提取
		int x1;
		stringstream s1(c1);
		while (s1 >> x1) {
			my_MaxFinally.push_back(x1);
		}//while (s1 >> x1)
	}//while (getline(my_ReadOfMax, c1))
	my_ReadOfMax.close();

	ifstream my_ReadOfAvailable("Available.txt");
	if (!my_ReadOfAvailable.is_open()) {
		cerr << "The avilable don't open! error4 !" << endl;
	}
	while (getline(my_ReadOfAvailable, c1)) {//进行其中数字的提取
		int x2;
		stringstream s1(c1);
		while (s1 >> x2) {
			my_AvailableFina.push_back(x2);
		}//while (s1 >> x1)
	}//while (getline(my_ReadOfMax, c1))
	my_ReadOfAvailable.close();

	m_Allocation.open("Allocation.txt");
	srand((unsigned)time(NULL));
	if (!m_Allocation.is_open()) {
		cerr << "The Allocation don't open! error5 ! " << endl;
	}
	for (int i = 0; i < m_client; i++) {
		for (int j = 0; j < m_resource; j++) {//上一个函数由于生成的资源数可能为零，所以进行处理。
			if (my_MaxFinally[i * m_resource + j] == 0) {
				my_number2 = 0;
			}
			else {
				my_number2 = rand() % (my_MaxFinally[i * m_resource + j]);
				while (my_number2 >(my_AvailableFina[j] / 4)) {
					my_number2 = rand() % (my_MaxFinally[i * m_resource + j]);
				}
			}
			m_Allocation << my_number2;
			if (j < m_resource - 1) {
				m_Allocation << " ";
			}
		}//for (int j = 0; j < m_resource; j++)
		m_Allocation << endl;
	}//for (int i = 0; i < m_client; i++)
	m_Allocation.close();
}
void InitCls::InitRandomOfTime() {
	int i, j;
	int my_numberoftime;

	m_Time.open("Duration.txt");
	if (!m_Time.is_open()) {
		cerr << "The duration doon't open! error6 ! " << endl;
	}
	srand((unsigned)time(NULL));
	for (i = 0; i < m_client; i++) {
		for (j = 0; j < m_resource; j++) {
			my_numberoftime = rand() % 9 + 1;//占有时间为（1~9）
			m_Time << my_numberoftime;
			if (j < m_resource - 1) {
				m_Time << " ";
			}
		}//for (j = 0; j < m_resource; j++)
		m_Time << endl;
	}//for (i = 0; i < m_client; i++) 
	m_Time.close();
}