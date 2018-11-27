#pragma once
#include <iostream>
using namespace std;
#include <windows.h>
#include <queue>


//队列信号量
class QueueSemaphore {
	HANDLE hMutex1;
public:
	bool Create(string &QueueName);
	void Decrease();
	void Increase();
	~QueueSemaphore();
	
};

//队列互斥锁
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
	队列注册: 包括  sem 注册

	*****/
	void QueueRegister(string &name);

	void Publish(string &data);
	string Consume();
};


