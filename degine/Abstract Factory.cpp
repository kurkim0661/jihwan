Abstract Factory Pattern Type : Creational
객체를 생성해주는 팩토리 관점은 동일하다.
다양한 구성 요소 별로 '객체의 집합'을 생성해야 할 때 유용하다. 즉 서로 다른 객체들을 하나의
팩토리에서 생성 관리한다고 보면 된다.
하나의 인터페이스에서 객체의 생성을 처리하고, 다양한 성격의 객체를 하나의 군으로 형성 그것을
객체단위로 취급하여 생성을 해야할 때 유용한 패턴이다.
#include <iostream>

using namespace std;

class AbstractProductA
{
public:
	virtual void print(void) = 0;
};

class AbstractProductB
{
public:
	virtual void print(void) = 0;
};


class ConcreteProductA1 : public AbstractProductA
{
public:
	void print(void) override
	{
		cout<<"ConcreteProductA1"<<endl;
	}
};

class ConcreteProductA2 : public AbstractProductA
{
public:
	void print(void) override
	{
		cout<<"ConcreteProductA2"<<endl;
	}
};

class ConcreteProductB1 : public AbstractProductB
{
public:
	void print(void) override
	{
		cout<<"ConcreteProductB1"<<endl;
	}
};

class ConcreteProductB2 : public AbstractProductB
{
public:
	void print(void) override
	{
		cout<<"ConcreteProductB2"<<endl;
	}
};


class AbstractFactory
{
public:
	virtual AbstractProductA* createProductA(void) = 0;
	virtual AbstractProductB* createProductB(void) = 0;
};

class ConcreteFactory1 : public AbstractFactory
{
public:
	AbstractProductA* createProductA(void) override
	{
		return new ConcreteProductA1;
	}
	AbstractProductB* createProductB(void) override
	{
		return new ConcreteProductB1;
	}
};

class ConcreteFactory2 : public AbstractFactory
{
public:
	AbstractProductA* createProductA(void) override
	{
		return new ConcreteProductA2;
	}
	AbstractProductB* createProductB(void) override
	{
		return new ConcreteProductB2;
	}
};


int main(void)
{
	AbstractFactory* p_factory = new ConcreteFactory;
	AbstractProductA* a = p_factory->createProductA();
	AbstractProductB* b = p_factory->createProductB();

	a->print();
	b->print();

	delete a;
	delete b;
	delete p_factory;

	return 0;
}
