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
