#include"stdafx.h"
#include"Init_Message.h"
#include<stdlib.h>

#ifndef _Message_Init_CPP
#define _Message_Init_CPP

void InitCls::InitSourse() {
	m = 3;
	m_fSourse.open("Sourse.txt");
	int myValue;
	for (int i = 0; i < m; i++) {
		myValue = rand() % 30;
		m_Sourse.push_back(myValue);
		m_fSourse << myValue;
		m_fSourse << " ";
	}
	m_fSourse.close();
}

#endif
