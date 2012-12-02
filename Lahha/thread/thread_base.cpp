#include "thread_base.h"

ThreadBase::ThreadBase()
{
	param = NULL;
	active = false;
	suspended = false;
}

ThreadBase::~ThreadBase()
{
	Terminate();
}

unsigned _stdcall ThreadBase::StaticEntryPoint(void * pThis)
{
	ThreadBase * pThread = (ThreadBase*)pThis;

	pThread->active = true;
	pThread->suspended = false;

	pThread->EntryPoint(pThread->param);

	pThread->active = false;
	pThread->suspended = false;

	pThread->Terminate();

	return 1;
}
//void ThreadBase::EntryPoint(void * param)
//{
//	return;
//}
void ThreadBase::Start(void * _param)
{
	boost::lock_guard<boost::mutex> lock(controlMutex);

	if(active)
		return;

	param = _param;

	active = true;
	_start();
	
}
void ThreadBase::Suspend()
{
	controlMutex.lock();
	suspended = true;
	controlMutex.unlock(); //TODO: Need to do it like this so the thread wont deadlock if it suspends itself. There prolly is some better solution for this but too lazy to think atm.
	_suspend();
}
void ThreadBase::Resume()
{
	boost::lock_guard<boost::mutex> lock(controlMutex);
	
	suspended = false;
	_resume();
}
void ThreadBase::Terminate()
{
	boost::lock_guard<boost::mutex> lock(controlMutex);

	if(!active)
		return;

	_terminate();
	active = false;
	suspended = false;
}
bool ThreadBase::IsThreadActive()
{
	boost::lock_guard<boost::mutex> lock(controlMutex);
	return active;
}
bool ThreadBase::IsThreadSuspended()
{
	boost::lock_guard<boost::mutex> lock(controlMutex);
	return suspended;
}
bool ThreadBase::Wait(unsigned timeout)
{
	if(active)
		return _wait(timeout);

	return true;
}