#ifndef LAHHA_THREAD_WINT32_H
#define LAHHA_THREAD_WINT32_H

#define WIN32_MEAN_AND_LEAN

#include <Windows.h>
#include <process.h>

#include "thread_base.h"

class ThreadWin32 : public ThreadBase
{
	
private:
	HANDLE hThread;
	unsigned __int32 threadAddress;

	virtual void _start();
	virtual void _suspend();
	virtual void _resume();
	virtual void _terminate();
	virtual bool _wait(unsigned timeout);

public:
	ThreadWin32();
	virtual ~ThreadWin32();

	virtual void EntryPoint(void * param) = 0;
};

#endif //LAHHA_THREAD_WINT32_H