
미리 만들어진 개체를 복사하여 개체를 생성하는 패턴이다.
다수의 객체 생성시에 발생되는 객체의 생성 비용을 효과적으로 줄일 수 있다.

  class Client
{

};

class Prototype
{
public:
	virtual Prototype* clone(void) = 0;
};

class ConcretePrototype1 : public Prototype
{
public:
	ConcretePrototype1() {}
	ConcretePrototype1(const ConcretePrototype1& p)
	{
		
	}
	Prototype* clone(void) override final
	{
		return new ConcretePrototype1(*this);
	}
};

class ConcretePrototype2 : public Prototype
{
public:
	ConcretePrototype2() {}
	ConcretePrototype2(const ConcretePrototype2& p)
	{
		
	}
	Prototype* clone(void) override final
	{
		return new ConcretePrototype2(*this);
	}
};

int main(void)
{
	Prototype* pOriginal = new ConcretePrototype1();
	Prototype* pClone = pOriginal->clone();

	delete pClone;
	delete pOriginal;

	return 0;
}
