#include "thread_winapi.h"

ThreadWin32::ThreadWin32()
{
	hThread = NULL;
	threadAddress = 0;
}

ThreadWin32::~ThreadWin32()
{

}

void ThreadWin32::_start()
{
	hThread = (HANDLE) _beginthreadex(NULL, 0, ThreadBase::StaticEntryPoint, this, 1, &threadAddress);
}

void ThreadWin32::_suspend()
{
	SuspendThread(hThread);
}

void ThreadWin32::_resume()
{
	ResumeThread(hThread);
}

void ThreadWin32::_terminate()
{
	TerminateThread(hThread, 0);
}

bool ThreadWin32::_wait(unsigned timeout)
{
	if(WaitForSingleObject(hThread, timeout==0?INFINITE:timeout) == WAIT_OBJECT_0)
		return true;

	return false;
}