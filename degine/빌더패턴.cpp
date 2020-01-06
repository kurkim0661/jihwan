복합 객체의 생성과정과 표현 방법을 분리하여 동일한 생성 절차에서 서로 다른 표현 결과를 만들 수 있게 하는 패턴이다.
쉽게 말해서 하나의 객체를 생성할때 객체를 이루는 구성요소들을 분리하여 객체의 세부 구성요소 클래스들을 별도로 만들고 그 구성요소 클래스들을 조합 하여 하나의 객체를 만드는 것이다.
  자동차를 만든다고 한다면 자동차의 부품들을 모아서 하나의 자동차를 만드는 것을 예로 들 수 있다.

  class Product
{

};

class Builder
{
	virtual Product* GetResult() = 0;
	virtual void buildPart() = 0;
};

class ConcreteBuilder : public Builder
{
public:
	void buildPart(void) override
	{
		mProduct = new Product;
	}
	Product* GetResult() override
	{
		return mProduct;
	}
private:
	Product* mProduct;
};

class Director
{
public:
	Director(Builder* builder) : mBuilder(builder) {}
	~Director()
	{
		if(mBuilder)
		{
			delete mBuilder;
		}
	}

	Product* constuct(void)
	{
		mBuilder->buildPart();
		return mBuilder->GetResult();
	}

	
private:
	Builder* mBuilder;
};

int main(void)
{
	Director* pDirector = new Director(new ConcreteBuilder());
	Product* pProduct = pDirector->constuct();
	delete pProduct;
	delete pDirector;
	return 0;
}
///////////////////
예제
#include <iostream>
#include <string>
using namespace std;
class CEngine
{
public:
	CEngine(int mph) : mMPH(mph){}
	int GetMPH() const
	{
		return mMPH;
	}
private:
	int mMPH;
};

class CWheel
{
public:
	CEWheel(int size) : mSize(size){}
	int GetSize() const
	{
		return mSize;
	}
private:
	int mSize;

};

class CBody
{
public:
	CBody(string shape) : mShape(shape) {}
	string GetShape() const
	{
		return mShape;
	}
private:
	string mShape:
};

class Car
{
public:
	Car() : mEngine(nullptr), mWheel(nullptr), mBody(nullptr){}
	~Car()
	{
		if(mEngine)
			delete mEngine;
		if(mWheel)
			delete mWheel;
		if(mBody)
			delete mBody;
	}
	void SetEngine(CEngine* engine)
	{
		mEngine = engine;
	}
	void SetWheel(CWheel* wheel)
	{
		mWheel = wheel;
	}
	void SetBody(CBody* body)
	{
		mBody = body;
	}
	void SetManufacture(string m)
	{
		mManufacture = m;
	}
	void print() const
	{
		cout<<"제조 회사 : "<<mManufacture<<endl;
		cout<<"엔진 마력 : "<<mEngine->GetMPH()<<endl;
		cout<<"휠 사이즈 : "<<mWheel->GetSize()<<endl;
		cout<<"외형 타입 : "<<mBody->GetShape()<<endl;
		
	}
private:
	CEngine* mEngine;
	CWheel* mWheel;
	CBody* mBody;
	string mManufacture;
};

class Builder
{
public:
	virtual CEngine* GetEngine() = 0;
	virtual CWheel* GetWheel() = 0;
	virtual CBody* GetBody() = 0;
	virtual string GetManufacture() = 0;
};

class FordBuilder : public Builder
{
public:
	CEngine* GetEngine() override
	{
		return new CEngine(150);
	}
	CWheel* GetWheel() override
	{
		return new CWheel(18);
	}
	CBody* GetBody() override 
	{
		return new CBody("hatch back");
	}
	string GetManufacture() override
	{
		return "Ford";
	}
};

class JeepBuilder : public Builder
{
public:
	CEngine* GetEngine() override
	{
		return new CEngine(120);
	}
	CWheel* GetWheel() override
	{
		return new CWheel(29);
	}
	CBody* GetBody() override 
	{
		return new CBody("SUV");
	}
	string GetManufacture() override
	{
		return "Jeep";
	}
};

class Director
{
public:
	Director(Builder* builder) : m_builder(builder) {}
	~Director()
	{
		if(m_builder)
		{
			delete m_builder;
		}
	}
	Car* construct(void)
	{
		Car* car = new Car;
		car->SetBody(m_builder->GetBody());
		Car->SetEngine(m_builder->GetEngine());
		Car->SetManufacture(m_builder->GetManufacture());
		Car->SetWheel(m_builder->GetWheel());

		return car;
	}
private:
	Builder* m_builder;
};

int main(void)
{
	Director* a_director = new Director(FordBuilder());
	Car* car = a_director->construct();
	car->print();

	delete car;
	delete a_director;
	return 0;
}
