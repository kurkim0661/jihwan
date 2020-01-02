Facade Pattern

통일된 인터페이스를 통해 복잡한 서브시스템들을 간단히 사용하도록 만든 패턴이다.

#include <iostream>
using namespace std;
class SubClassA
{
public:
	void operation(void)  
	{
		cout<<"SubClass A" << endl;
	}
};



class SubClassB
{
public:
	void operation(void)  
	{
		cout<<"SubClass B" << endl;
	}
};

class SubClassC
{
public:
	void operation(void)  
	{
		cout<<"SubClass C" << endl;
	}
};

class SubClassD
{
public:
	void operation(void)  
	{
		cout<<"SubClass D" << endl;
	}
};

class Facade
{
public:
	Facade(SubClassA *a, SubClassB *b, SubClassC *c, SubClassD *d)
		: mA(a), mB(b), mC(c), mD(d)
	{}
	void operation()
	{
		mA->operation();
		mB->operation();
		mC->operation();
		mD->operation();
	}
private:
	SubClassA* mA;
	SubClassB* mB;
	SubClassC* mC;
	SubClassD* mD;
};

int main(void)
{
	SubClassA A;
	SubClassB B;
	SubClassC C;
	SubClassD D;

	Facade facade(&A, &B, &C, &D);
	facade.operation();
	getchar();
	return 0;
}
