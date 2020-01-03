자주사용되는 리소스에 대해 Provider에서 사용할때마다 생성, 반환시 성능상의 문제가 있다.
최초 정해진 갯수의 리소스를 초기화하여 Pool에 미리 만들어 놓고 필요할때마다 사용하여 성능을 높일 수 있다.
캐시와의 차이점은 같은 종류의 리소스를 사용하므로 Identified가 필요하지 않다.

//Pool.h
#pragma once

class CResource;
class CPool
{
public:
	virtual CResource* aquire() = 0;
	virtual void release(CResource* res) = 0;
};
////////////
//Resource.h
#pragma once
class CResource
{
public:
	virtual void* getConnection() = 0;
};

/////////
//ConnectionPool.h
#pragma once
#include <list>
class CConnectionPool : public CPool
{
public:
	CConnectionPool(unsigned int poolSize);
	virtual ~CConnectionPool();

	CResouce* aquire();
	void release(CResource* res);

protected:
	CResource* findNewConnection();

private:
	list<CResource*> m_pool;
};
//////////////
//ConnectionPool.cpp
#include "stdeafx.h"
#include "ConnectionPool.h"

CConnectionPool::CConnectionPool(unsigned int poolSize)
{
	for(int i = 0; i < poolSize; i++)
	{
		CResource* resouce = new CConnection;
		m_pool.push_back(resouce);
	}
}

CConnectionPool::~CConnectionPool()
{
	for each(CResouce* entry in m_pool)
	{
		delete entry;
	}

	m_pool.clear();
}

CResource* CConnectionPool::aquire()
{
	CResource *resource = nullptr;
	if(nullptr == (resource = findNewConnection9()))
	{
		resource = new CConnection;
		m_pool.push_back(resource);
	}

}

void CCOnnectionPool::release(CResource* res)
{
	for each(CResource* entry in m_pool)
	{
		if(entry == res)
		{
			static_cast<CConnection*>(entry)->setInUse(true);
			break;
		}
	}
}

CResource* CConnectionPool::findNewConnection()
{
	for each(CResource* entry in m_pool)
	{
		if(!static_cast<CConnection*>(entry->getInUse()))
		{
			static_cast<CConnection*>(entry)->setInUse(true);
			return entry;
		}
	}

	return nullptr;
}

/////////////////
//Connection.h
#pragma once

typedef struct
{
	long ticks;
	int hour;
	int minutes;
	int seconds;
	int month;
	int day;
	int year;
} DATETIME;

class CConnection : public CResource
{
public:
	CConnection();
	virtual ~CConnection();

	void* getConnection();
	void setInUse(bool value);
	bool getInUse();

private:
	bool m_currentlyUsed;
	DATETIME mlastUsage;
	_ConnectionPtr m_connection;
};
////////////
//Connection.cpp
#include "stdafx.h"
#include <time.h>

CConnection::CConnection() : m_currentlyUsed(false)
{
	m_connection.CreateInstance(__uuidof(Connection));
	m_connection->CursorLocation = adUseServer;
	m_connection->Open(L"연결 프로바이더 설정", L"", L"",adConnectUnspecified);
}

CConnection::~CConnection()
{
	if(m_connection)
	{
		m_connection->Close();
		m_connection = null;
	}
}

void* CConnection::getConnection()
{
	return m_connection;
}
void CConnection::setInUse(bool value)
{
	if(value)
	{
		time_t seconds = time(NULL);
		struct tm* timeinfo = localtime(&seconds);

		mlastUsage.ticks = seconds;
		mlastUsage.hour = timeinfo->tm_hour;
		mlastUsage.minutes = timeinfo->tm_min;
		mlastUsage.seconds = timeinfo->tm_sec;
		mlastUsage.month = timeinfo->tm_mon;
		mlastUsage.year = timeinfo->tm_year;
		mlastUsage.day = timeinfo->tm_mday;
	}

	m_currentlyUsed = value;
}

bool CConnection::getInUse()
{
	return m_currentlyUsed;
}

///////////
//Main
int main(void)
{
	CoInitialize(NULL);
	//풀 갯수 지정 풀생성.
	CPool* mPool = new CConnectionPool(5);
	//리소스 요청.
	CResource* pResource = mPool->aquire();
	//리소스 사용.
	//리소스 반환.
	mPool->release(pResource);
	delete mPool;

	CoUninitialize();
	return 0;
}
