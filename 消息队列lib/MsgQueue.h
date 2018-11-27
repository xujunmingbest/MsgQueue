#pragma once
#include <iostream>
using namespace std;
#include <windows.h>
#include <queue>


//�����ź���
class QueueSemaphore {
	HANDLE hMutex1;
public:
	bool Create(string &QueueName);
	void Decrease();
	void Increase();
	~QueueSemaphore();
	
};

//���л�����
class QueueMutex {
private:
	HANDLE hMutex1;

public:
	bool Create(string &QueueName);

	void Lock();

	void UnLock();

	~QueueMutex();
};

class MsgQueue {
private:
	queue<string> Queue;
	QueueSemaphore QS;
	QueueMutex QM;
	HANDLE ENT;
public:  //register
	bool Enable() {
		return QueueEnable;
	}
	bool QueueEnable = false;
	/************
	����ע��: ����  sem ע��

	*****/
	void QueueRegister(string &name);

	void Publish(string &data);
	string Consume();
};


