// Mutex.h: interface for the Mutex class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MUTEX_H__D6FF9C7C_3CAE_4EB0_B163_08D5232C4CE2__INCLUDED_)
#define AFX_MUTEX_H__D6FF9C7C_3CAE_4EB0_B163_08D5232C4CE2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "comdefine.h" 

namespace plib
{

class Mutex  
{
public:
	bool Locked(int timeout=0);
	bool TryLock();
	void Unlock();
	void Lock();
	Mutex();
	virtual ~Mutex();
protected:
#ifdef WIN32
    CRITICAL_SECTION m_mutex;
#else
    pthread_mutex_t m_mutex;
#endif
};
//////////////////////////////////////////////////////////////////////////////
inline Mutex::Mutex()
{
#ifdef WIN32
	::InitializeCriticalSection(&m_mutex);
#else
	//RHEL4下编译、测试通过
// 	pthread_mutexattr_t a;
// 	a.__mutexkind = PTHREAD_MUTEX_RECURSIVE_NP;
// 	pthread_mutex_init(&m_mutex, &a);

	//
	pthread_mutexattr_t l_attributes;
	::pthread_mutexattr_init(&l_attributes);
	::pthread_mutexattr_settype(&l_attributes, PTHREAD_MUTEX_RECURSIVE);
	::pthread_mutex_init(&m_mutex, &l_attributes);
	::pthread_mutexattr_destroy(&l_attributes);
#endif
}

inline Mutex::~Mutex()
{
#ifdef WIN32
	::DeleteCriticalSection(&m_mutex);
#else
	pthread_mutex_destroy(&m_mutex);
#endif
}

inline void Mutex::Lock()
{
#ifdef WIN32
	::EnterCriticalSection(&m_mutex);
#else
	pthread_mutex_lock(&m_mutex);
#endif
}

inline void Mutex::Unlock()
{
#ifdef WIN32
	::LeaveCriticalSection(&m_mutex);
#else
	pthread_mutex_unlock(&m_mutex);
#endif
}

inline bool Mutex::TryLock()
{
#ifdef WIN32
	return (TRUE == ::TryEnterCriticalSection(&m_mutex));
#else
	return ( 0 == pthread_mutex_trylock(&m_mutex));
#endif
}

inline bool Mutex::Locked(int timeout)
{
#ifdef WIN32
	return  (WAIT_TIMEOUT == ::WaitForSingleObject(&m_mutex ,timeout) );
#else
	if (false == TryLock()) return true;

	Unlock();
	return false;
#endif
}
///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
class SingleMutex
{
public:
	SingleMutex(Mutex& lock);
	~SingleMutex();
	bool Release();
	bool Acquire();
protected:
	Mutex *m_Lock;
    bool m_Acquired;
};

inline SingleMutex::SingleMutex(Mutex& lock) 
: m_Lock(&lock),m_Acquired(false)
{
	this->Acquire();
}

inline SingleMutex::~SingleMutex()
{
	this->Release();
}

inline bool SingleMutex::Acquire()
{
	//assert(m_Lock != NULL);
	if (true == m_Acquired)
		return true;

	m_Acquired= true;
	m_Lock->Lock();
	return true;
}

inline bool SingleMutex::Release()
{
	//assert(m_Lock != NULL);
	if (false == m_Acquired)
		return true;

	m_Acquired= false;
	m_Lock->Unlock();
	return true;
}
///////////////////////////////////////////////////////////////////////
} //namespace comLib
#endif // !defined(AFX_MUTEX_H__D6FF9C7C_3CAE_4EB0_B163_08D5232C4CE2__INCLUDED_)

