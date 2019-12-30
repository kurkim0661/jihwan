
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
