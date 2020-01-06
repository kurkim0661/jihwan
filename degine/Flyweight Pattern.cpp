Flyweight Type : Structural
데이터를 공유 사용하여 메모리를 절약할 수 있는 패턴이다.
일반적으로 공통으로 사용되는 객체는 새로 생성해서 사용하지 않고 공유를 통해 효율적으로
자원을 활용한다.
한 번 생성된 객체는 두번 생성되지 않고, 풀(Pool)에 의해서 관리 및 사용된다.
실제로 가장 많이 사용되는 패턴 중에 하나이다.

샘플 코드.

#include <iostream>

class Flyweight
{
public:
	virtual void operation(void) = 0;
};

class ConcreteFlyweight : public Flyweight
{

public:
	void operation(void) override 
	{
		cout<<"ConcreteFlyweight"<<endl;
	}
};

class UnsharedConcreteFlyweight : public Flyweight
{

public:
		void operation(void) override 
	{
		cout<<"UnsharedConcreteFlyweight"<<endl;
	}
};

class FlyweightFactory
{
public:
	~FlyweightFactory(){}
	Flyweight* getFlyweight(int key)
	{
		if(mList.find(key) == mList.end())
		{
			mList[key] = new ConcreteFlyweight;
		}
		return mList[key];		
	}
private:
	map<int, Flyweight*> mList;
};

int main(void) 
{
	FlyweightFactory flyFactory;
	Flyweight* flyweight = flyFactory.getFlyweight(1);
	flyweight->operation();

	getchar();

	return 0;
}
////////////
예제 코드... 

#include <iostream>
#include <map>
#include <algorithm>
using namespace std;

template<typename T>
class Singleton
{
public:
	Singleton(){}
	Singleton(const Singleton& s){}
	virtual ~Singleton()
	{
		if(mp_instance)
		{
			delete mp_instance;
		}
	}

	static T* GetInstance(void)
	{
		if(mp_instance == nullptr)
		{
			mp_instance = new T();
			atexit(destroy);
			return mp_instance;
			
		}
		else 
		{
			return mp_instance;
		}
	}
private:
	static T* mp_instance;
	
	static void destroy(void) 
	{
		if(mp_instance)
		{
			delete mp_instance;
		}
	}
};

template<typename T> 
T* Singleton<T>::mp_instance;

class Item
{
public:
	virtual void operation() = 0;
};

class Potion : public Item
{
public:
	void operation(void) override 
	{
		cout<<"Potion"<<endl;
	}
};

class Axe : public Item
{
public:
	void operation(void) override 
	{
		cout<<"Axe"<<endl;
	}
};

class Map : public Item
{
public:
	void operation(void) override 
	{
		cout<<"Map"<<endl;
	}
};

	
class ItemFactory : public Singleton<ItemFactory>
{
public:
	~ItemFactory(){}
	template<typename T>
	Item* GetItem(int key)
	{
		if(m_list.find(key)==m_list.end())
		{
			m_list[key] = new T;
		}
		return m_list[key];
	}

private:
	map<int, Item*> m_list;
};

int main(void)
{
	Item* potion = ItemFactory::GetInstance()->GetItem<Potion>(1);
	Item* axe = ItemFactory::GetInstance()->GetItem<Axe>(2);
	Item* map = ItemFactory::GetInstance()->GetItem<Map>(3);

	potion->operation();
	axe->operation();
	map->operation();

	return 0;
}



