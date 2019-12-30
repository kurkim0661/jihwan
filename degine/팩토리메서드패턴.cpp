객체를 생서하는 일을 전담하도록 한다.
인터페이스를 바탕으로 유연성과 확장성이 뛰어난 코드 제작이 가능하다.
인터페이스에서 객체 생성을 요청하지만, 어떤 클래스의 인스턴스를 만들지는 서브클래스에서 결정한다.
이는 곧 템플릿 메소드 패턴을 활용한 패턴이라고 할 수 있다.

  class Product
{
public:
	virtual void print() = 0;
};

class ConcreteProduct : public Product
{
public:
	void print() override
	{
		cout<<"ConcreteProduct"<<endl;
	}
};

class Creator
{
protected:
	virtual Product* FactorMethod(void) = 0;
public:
	Product* anOperation(void)
	{
		return FactorMethod();
	}
};

class ConcreteCreator : public Creator
{
public:
	void FactorMethod(void)
	{
		return new ConcreteProduct;
	}
};

int main(void)
{
	ConcreteCreator pCreator;

	Product* pProduct = pCreator.anOperation();
	pProduct->print();

	delete pProduct;
	return 0;
}
