
#include <iostream>
#include <list>

class Observer
{
public:
	virtual void update() = 0;
};

class ConcreteObserver : public Observer
{
public:
	void update() override
	{
		cout<<this<<": update"<<endl;
	}
};

class Subject
{
public:
	virtual void change(void) = 0;
	
	void attach(Observer *c)
	{
		mOlist.push_back(c);
	}

	void detach(Observer *c)
	{
		
		mOlist.erase(mOlist.begin() + find(mOlist.begin(), mOlist.end(), c));
	}
protected:
	void notify()
	{
		auto iter = mOlist.begin();
		while(iter != nullptr)
		{
			mOlist[iter++]->update();
		}
	}
private:
	list<Observer *> mOlist;
};

class ConcreteSubject : public Subject
{
public:
	void change(void) override
	{
		notify();
	}
}

int main(void) 
{
	Subject *pSubject = new ConcreteSubject;

	Observer *pObserver1 = new ConcreteObserver;
	Observer *pObserver2 = new ConcreteObserver;
	Observer *pObserver3 = new ConcreteObserver;	

	pSubject->attach(pObserver1);
	pSubject->attach(pObserver2);
	pSubject->attach(pObserver3);

	pSubject->change();

	pSubject->detach(pObserver1);
	pSubject->detach(pObserver2);
	pSubject->detach(pObserver3);

	pSubject->change();

	delete pSubject;
	delete pObserver1;
	delete pObserver2;
	delete pObserver3;
	return 0;
}

///////////////////////
#include <iostream>
#include <list>
#include <algorithm>
using namespace std;


class Observer_Interface
{
public:
	virtual const char* GetName(void) const = 0;
	virtual void Watching(const char* news) = 0;

};

class audience : public Observer_Interface
{
public:
	audience(const char* name)
		:m_name(name){}

		void Watching(const char * news) override
		{
			cout<<"m_name"<<" : "<<news<< endl;	
		}
		const char* GetName(void) const override
		{
			return m_name.c_str();
		}
		
private:
	string m_name;
};
class Media_Interface
{
protected:
	void broadcasting(const char* news)
	{
		for(auto itr : mp_list)
		{
			itr->Watching(news);
		}
	}
public:
	virtual void News(const char* news) = 0;
	void Add_Observer(Observer_Interface* oi)
	{
		mp_list.push_back(oi);
		cout<<"방송 신청 : "<<oi->GetName()<<endl;
	}
	void Remove_Observer(Observer_Interface* oi)
	{
		mp_list.remove(oi);
	}
private:
	list<Observer_Interface*> mp_list;
};

class Korea_Media : public Media_Interface
{
public:
	void News(const char* news) override
	{
		broadcasting(news);
	}
};

int main(void)
{
	Media_Interface* pSub = new Korea_Media;

	Observer_Interface* pObserver1 = new audience("홍길동");
	Observer_Interface* pObserver2 = new audience("김지환");
	Observer_Interface* pObserver3 = new audience("이호호");

	pSub->Add_Observer(pObserver1);
	pSub->Add_Observer(pObserver2);
	pSub->Add_Observer(pObserver3);

	pSub->News("날씨는 맑음!");

	pSub->Remove_Observer(pObserver1);
	pSub->Remove_Observer(pObserver2);

	pSub->News("속보속보1");



	
	
}

