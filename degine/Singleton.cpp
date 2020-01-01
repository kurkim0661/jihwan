Singleton Pattern 
무분별한 객체생성을 방지하고, 1개의 객체만 생성하여 이용하는 프로그램 코딩에 유용하게 적용할 수 있다.

#include <iostream>
#include <algorithm>
#include <memory>
#include <cstdio>
#include <mutex>
using namespace std;

#if 0 // 동적 싱클턴  destroy 해서 main 종료 전에 메모리 누수를 방지해야함. 
class Singleton
{
private:
	Singleton() {cout<<"Singleton make"<<endl;}
	~Singleton() {cout<<"Singleton delete"<<endl;}
	Singleton(const Singleton& s) {}
	
public:
	static Singleton* GetInstance()
	{
		if(mp_instance == nullptr)
		{
			mp_instance = new Singleton;
	
		}
		return mp_instance;
	}
	
private:
	static Singleton* mp_instance;
};

Singleton* Singleton::mp_instance = nullptr;
int main(void)
{
	Singleton* m_Singleton = Singleton::GetInstance();	

	return 0;
}
#endif

#if 0 //정적 객체 관리. 
class Singleton
{
private:
	Singleton() {cout<<"Singleton make"<<endl;}
	~Singleton() {cout<<"Singleton delete"<<endl;}
	Singleton(const Singleton& s) {}
	
public:
	static Singleton* GetInstance()
	{
		if(mp_instance == nullptr)
		{
			mp_instance = new Singleton;
	
		}
		return &mp_instance;
	}
	
private:
	static Singleton mp_instance;
};

int main(void)
{
	Singleton* m_Singleton = Singleton::GetInstance();	

	return 0;
}
#endif 

#if 0 //템플릿 기반의 싱글턴.
template<typename T> 
class Singleton
{
protected:
	Singleton() {cout<<"Singleton make"<<endl;}
	virtual ~Singleton() {cout<<"Singleton delete"<<endl;}
	Singleton(const Singleton& s) {}
	
public:
	static T* GetInstance()
	{
		if(mp_instance == nullptr)
		{
			mp_instance = new T();
	
		}
		return mp_instance;
	}
	
private:
	static void destroy()
	{
		if(mp_instance)
		{
			delete mp_instance;
		}
	}
	static T* mp_instance;
};

template<typename T>
T* Singleton <T>::mp_instance;

class Point : public Singleton<Point>
{
public:
	void print(void)
	{
		cout<<x<<" "<<y<<endl;
	}
private:
	int x;
	int y;
};
int main(void)
{
	Point::GetInstance()->print();	

	return 0;
} 

#endif 

#if 1 //스마트 포인터 shared ptr을 활용한 싱글턴 패턴.
std::call_once()는 std::once_flag()와 함께 사용하여 복수의 Thread환경에서 특정 함수를 단 한 번만 구동되도록 할 수 있습니다.
이러한 호출을 'Effective Call Once Invocation'라고 합니다.

template<typename T>
class Singleton
{
public:
	static T* GetInstance()
	{
		call_once(m_onceFlag, []() {
			mp_instance.reset(new T);	
		});

		return mp_instance;
	}
private:
	static shared_ptr<T> mp_instance;
	static once_flag m_onceFlag;
	
};

template<typename T>
shared_ptr<T> Singleton<T>::mp_instance = nullptr;
template<typename T>
once_flag Singleton<T>::m_onceFlag;


#endif
