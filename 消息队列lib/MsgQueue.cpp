#include "stdafx.h"
/**********c语言实现县消息队列***********/
#include "MsgQueue.h"
bool QueueSemaphore::Create(string &QueueName) {
	string QN = QueueName + "Semaphore";
	hMutex1 = NULL;
	hMutex1 = CreateSemaphoreA(NULL, 0, 100, QN.c_str());
	if (GetLastError() == ERROR_ALREADY_EXISTS)
	{
		return false;
	}
	if (NULL == OpenSemaphoreA(SEMAPHORE_MODIFY_STATE, FALSE, QN.c_str()))
	{
		return false;
	}
	return true;
}

void QueueSemaphore::Decrease() {
	WaitForSingleObject(hMutex1, INFINITE);
}

void QueueSemaphore::Increase() {
	long dwSem = 0;
	ReleaseSemaphore(hMutex1, 1, &dwSem);
}

QueueSemaphore::~QueueSemaphore() {
	CloseHandle(hMutex1);
	hMutex1 = NULL;
}


bool QueueMutex::Create(string &QueueName) {
	hMutex1 = CreateMutex(NULL, FALSE, (QueueName + "MUTEX").c_str());
	if (GetLastError() == ERROR_ALREADY_EXISTS)
	{
		return false;
	}
	return true;
}

void QueueMutex::Lock() {
	WaitForSingleObject(hMutex1, INFINITE);
}
void QueueMutex::UnLock() {
	ReleaseMutex(hMutex1);
}

QueueMutex::~QueueMutex() {
	CloseHandle(hMutex1);
	hMutex1 = NULL;
}

string MsgQueue::Consume() {
	if (!Enable()) return "";
	QS.Decrease();
	QM.Lock();
	string t;
	if (!Queue.empty()) {
		t = Queue.front();
		Queue.pop();
	}
	else {
		t = "";
	}
	QM.UnLock();
	return t;
}
void MsgQueue::Publish(string &data) {
	if (!Enable()) return;
	QM.Lock();
	Queue.push(data);
	QM.UnLock();
	QS.Increase();
}

void MsgQueue::QueueRegister(string &name) {
	QueueEnable = QM.Create(name);
	if (!QueueEnable) {
		return;
	}
	QueueEnable = QS.Create(name);
	if (!QueueEnable) {
		return;
	}
	QueueEnable = true;
}