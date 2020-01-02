Synchronization Patterns
선언된 스코프의 범위 내에섬나 적용되는 동기화 디자인 패턴
생성자, 소멸자 기능을 시용한 패턴으로써 동기화가 적용되는 범위를 스코프 에서 사용되도록 한다.

#pragma once
// Lock_interface.h
class Lock_interface
{
public:
	Lock_interface(){}
	~Lock_interface(){}

	inline virtual bool try_acquire(long timeOut = 0) = 0;
	inline virtual void acquire() = 0;
	inline virtual void release() = 0;
};

//Mutex.h
#pragma once

class Mutex : public Lock_interface
{
public:
	Mutex() : m_hMutex(::CreateMutex(nullptr, false, nullptr)) {}
	~Mutex()
	{
		if(m_hMutex)
		{
			CloseHandle(m_hMutex);
		}
	}

	inline void acquire()
	{
		WaitForSingleObject(m_hMutex, 0);
	}
	inline void release()
	{
		ReleaseMutex(m_hMutex);
	}
	inline bool try_acquire(long timeOut = 0)
	{
		return WaitForSingleObject(m_hMutex, timeOut) == WAIT_OBJECT_0;
	}
private:
	Handle m_hMutex;
};

//CGuard.h
#pragma once

template<typename T = CriticalSection>
class CGuard
{
public:
	CGuard(T* i) :mLock(i), bLocked(false)
	{
		mLock->acquire();
		bLocked = true;
	}
	~CGuard()
	{
		if(bLocked)
		{
			mLock->release();
		}
	}

private:
	T* mLock;
	bool bLocked;
};
