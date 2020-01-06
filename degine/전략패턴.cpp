동적으로 알고리즘을 교체할 수 있는 구조
알고리즘 인터페이스를 정의하고, 각각의 알고리즘 클래스별로 캡슐화하여 각각의 알고리즘을 교체 사용 가능하게 한다.
즉, 하나의 결과를 만드는 목적(메소드)은 동일하나, 그 목적을 달성할 수 있는 방법(전략, 알고리즘)이 여러가지가 존재
할 경우 기본이 되는 템플릿 메서드패턴과 함께 가장 많이 사용되는 패턴 중에 하나이다.

 #include <iostream>
using namespace std;

class Strategy
{
public:
	virtual void Algotithminterface() = 0;
};

class ConcreteStrategyA : public Strategy
{
public:
	void Algotithminterface() override
	{
		cout<<"ConcreteStrategyA"<<endl;
	}
};

class ConcreteStrategyB : public Strategy
{
public:
	void Algotithminterface() override
	{
		cout<<"ConcreteStrategyB"<<endl;
	}
};

class ConcreteStrategyC : public Strategy
{
public:
	void Algotithminterface() override
	{
		cout<<"ConcreteStrategyC"<<endl;
	}
};

class Context
{
public:
	Context() : m_strategy(nullptr){}
	~Context()
	{
		if(m_strategy)
		{
			delete m_strategy;
		}
	}
	void ChangeStrategy(Strategy* pStrategy)
	{
		if(m_strategy)
		{
			delete m_strategy;
			m_strategy = pStrategy;
		}
	};
	void Contextinterface()
	{
		m_strategy->Algotithminterface();
	}
private:
	Strategy* m_strategy;
};

int main(void)
{
	Context* pContext = new Context();
	pContext->ChangeStrategy(new ConcreteStrategyA());
	pContext->Contextinterface();

	pContext->ChangeStrategy(new ConcreteStrategyB());
	pContext->Contextinterface();

	pContext->ChangeStrategy(new ConcreteStrategyC());
	pContext->Contextinterface();

	delete pContext;

	return 0;
}

