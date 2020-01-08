Decorator Pattern 
주어진 상황 및 용도에 따라 어떤 객체에 책임을 덧붙이는 패턴으로, 기능 확장이 필요할 때 서브 클래싱 대신 쓸 수 있는 유연한 대안이 될 수 있다.
동적으로 객체의 추가적인 기능들을 가진 객체를 덧붙여 꾸밀 수 있다.


#include <iostream>
using namespace std;

class ICoffeeComponent
{
public:
	virtual int GetCost(void) = 0;
	virtual string GetIngredients(void) = 0;
};

class Coffee : public ICoffeeComponent
{
public:
	int GetCost(void) override
	{
		return 1000;
	}
	string GetIngredients() override
	{
		return "coffee\n";
	}
};

class CoffeeDecorator : public ICoffeeComponent
{
public:
	CoffeeDecorator(ICoffeeComponent* c)
		: m_Component(c){}
	~CoffeeDecorator()
	{
		if(m_Component)
			delete m_Component;
	}
	int GetCost(void) override
	{
		return m_Component->GetCost();
	}
	string GetIngredients(void) override 
	{
		return m_Component->GetIngredients();
	}
private:
	ICoffeeComponent* m_Component;
};

class MilkDecorator : public CoffeeDecorator
{
public:
	MilkDecorator(ICoffeeComponent* d)
		: CoffeeDecorator(d){}
	int GetCost(void) 
	{
		return 400 + CoffeeDecorator::GetCost();
	}
	string GetIngredients(void)
	{
		return "Milk " + CoffeeDecorator::GetIngredients() ;
	}
	
};

class WhipDecorator : public CoffeeDecorator
{
public:
	WhipDecorator(ICoffeeComponent* d)
		: CoffeeDecorator(d){}
	int GetCost(void) 
	{
		return 200 + CoffeeDecorator::GetCost();
	}
	string GetIngredients(void)
	{
		return "Whip " + CoffeeDecorator::GetIngredients();
	}
	
};

int main(void)
{
	ICoffeeComponent* p_coffee = new MilkDecorator(new WhipDecorator(new CoffeeDecorator(new Coffee())));
	cout<<p_coffee->GetCost();
	cout<<endl;
	cout<<p_coffee->GetIngredients()<<endl;

	delete p_coffee;
	return 0;
}
