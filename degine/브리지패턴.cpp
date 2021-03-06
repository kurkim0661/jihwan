브리지패턴
구현부에서 추상층을 분리하여 각자 독립적으로 변형할 수 있게 하는 패턴이다.
즉, 기능과 구현을 별도의 클래스로 정의해서 서로를 분리하는 방법이다.
전형적인 상속을 이용한 패턴으로 확장 설계에 용이하다.

class Abstraction
{
public:
	virtual void operation(void) = 0;
};

class ConcreteAbstraction : public Abstraction
{
public:
	ConcreteAbstraction(Implementor* i) : mImplementor(i) {}
	void operation(void) override
	{
		mImplementor->operationimpl();
	}

private:
	Implementor* mImplementor;
};

class Implementor
{
public:
	virtual void operationimpl(void) = 0;
};

class ConcreteImplementorA : public Implementor
{
public:
	void operationimpl(void) override 
	{
		cout<<"A"<<endl;
	}
};

class ConcreteImplementorB : public Implementor
{
public:
	void operationimpl(void) override 
	{
		cout<<"B"<<endl;
	}
};

int main(void)
{
	ConcreteImplementorA A;
	ConcreteImplementorB B;

	ConcreteAbstraction mA(&A);
	ConcreteAbstraction mB(&B);

	mA.operation();
	mB.operation();
}

/////////////
#include <iostream>
using namespace std;

class process;
class person
{
public:
	virtual void operation(void) = 0;
};

class cooker : public person
{
public:
	cooker(process* p)
		: m_process(p){}
	~cooker()
	{
		if(m_process)
			delete m_process;
	}
	void operation(void) override
	{
		m_process->operation();
	}

private:
	process* m_process;
};

class cleaner : public person
{
public:

	cleaner(process* p)
		:m_process(p){}

	cleaner()
	{
		if(m_process)
			delete m_process;
	}
	void operation(void) override
	{
		m_process->operation();
	}

private:
	process* m_process;
};
class process
{
public:
	virtual void operation(void) = 0;

};

class cooking : public process
{
public:
	void operation(void) override
	{
		cout<<"요리를 한다."<<endl;
	}
};

class cleaning : public process
{
public:
	void operation(void) override
	{
		cout<<"청소를 한다."<<endl;
	}
};

int main(void)
{
	person* man1 = new cooker(new cooking());
	person* man2 = new cleaner(new cleaning());

	man1->operation();
	man2->operation();

	delete man2;
	delete man1;
}

이거 런 안되더라.
	
