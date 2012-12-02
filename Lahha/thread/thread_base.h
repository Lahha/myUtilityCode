#ifndef LAHHA_THREAD_BASE_H
#define LAHHA_THREAD_BASE_H

#include <boost\thread\mutex.hpp>

class ThreadBase
{
private:
	bool active, suspended;
	boost::mutex controlMutex;

protected:
	void * param;

	virtual void _start() = 0;
	virtual void _suspend() = 0;
	virtual void _resume() = 0;
	virtual void _terminate() = 0;
	virtual bool _wait(unsigned timeout) = 0;

public:
	ThreadBase();
	virtual ~ThreadBase();
	
	static unsigned _stdcall StaticEntryPoint(void * pThis);
	virtual void EntryPoint(void * param) = 0;

	void Start(void * param);
    void Suspend();
    void Resume();
    void Terminate();

    bool IsThreadActive();
	bool IsThreadSuspended();

	bool Wait(unsigned timeout = 0);
};

#endif //LAHHA_THREAD_BASE_H