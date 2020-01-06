Template Method Pattern
상위 클래스에서 처리의 흐름을 제어하며, 하위클래스에서 처리의 내용을 구체화한다.
여러 클래스에 공통되는 사항은 상위 추상 클래스에서 구현하고, 각각의 상세부분은 하위클래스에서 구현하나.
코드의 중복을 줄이고, Refactorring에 유리한 패턴으로 상속을 통한 확장 개발 방법으로써 전략패턴과 함께
가장 많이 사용되는 패턴중에 하나이다.

#include <iostream>
using namespace std;

class Beverage
{
public:
	virtual void make(void) = 0;
	void boiling(void) {}
	void processing(void){}
	virtual void add(void) = 0;
	void pour(void)
	{
		cout<<"물을 컵에 따른다."<<endl;
	};
};

class Blacktea : public Beverage
{
public:
	void make(void) override 
	{
		cout<<"홍차를 만들자!"<<endl;
	}
	void add(void) override
	{
		cout<<"홍차가루를 넣는다."<<endl;
	}
};

class Coffee : public Beverage
{
public:
	void make(void) override 
	{
		cout<<"커피를 만들자!"<<endl;
	}
	void add(void) override
	{
		cout<<"커피가루를 넣는다."<<endl;
	}
};

int main(void)
{
	Beverage* tea = new Blacktea();
	Beverage* coffee = new Coffee();

	tea->make();
	coffee->make();
	tea->add();
	coffee->add();
	
}
