#ifndef LAHHA_THREAD_H
#define LAHHA_THREAD_H

//Include interface
#include <Lahha\thread\thread_base.h>

//Choose api to use
#ifdef WIN32
#include <Lahha\thread\thread_winapi.h>
typedef ThreadWin32 Thread;

#else
#error Could not determine which thread api to use.

#endif

//Link binaries for VC.
#ifdef _DEBUG
#pragma comment(lib, "ThreadLib_d.lib")

#else
#pragma comment(lib, "ThreadLib.lib")

#endif

#endif //LAHHA_THREAD_H