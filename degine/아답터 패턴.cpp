서로 다르게 구현된 인터페이스를 사용하고자 하는 다른 인터페이스로 변환한다.
즉, A와B의 인터페이스가 다를 경우 A에 맞추던가 B에 맞추던가 두 개의 인터페이스를 통일시켜
사용하게 하는 구조이다. 서로 다르게 구현된 것을 하나의 패턴으로 일치시켜주는 것 뿐이다.
아담터 패턴은 객체를 내부에 선언 사용하는 개체 아답터 패턴과 인터페이스를 상속받아 사용하는
클래스 아답터 패턴으로 나뉜다.

  class Adaptee
{
public:
	void adaptedOperation(void)
	{

	}
};

class Adapter
{
public:
	virtual void operation(void) = 0;
};

class ConcreteAdapterA : public Adapter
{
public:
	void operation(void) override
	{
		mAdaptee.adaptedOperation();
	}
private:
	Adaptee mAdaptee;
};

class ConcreteAdapterB : public Adapter, public Adaptee
{
public:
	void operation(void) override
	{
		adaptedOperation();
	}
};

int main(void)
{
	ConcreteAdapterA pObjectAdapter;
	pObjectAdapter.operation();
	
	ConcreteAdapterB pClassAdapter;
	pClassAdapter.operation();
}
