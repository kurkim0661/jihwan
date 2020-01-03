Visitor Pattern - 방문자 패턴 Type : Behavioral
객체의 구조와 기능을 분리시키는 패턴
구조는 변하지 않으며 기능 만을 따로 추가되거나 확장되어야 할 경우에 사용되는 패턴이다.
컴포지트 패턴과 연동되어 사용되는 경우가 많다.

#include <iostream>

using namespace std;
class Element;
class Visitor
{
public:
	virtual void visitElementA(Element* a) = 0;
	virtual void visitElementB(Element* b) = 0;
	
};

class Element 
{
public:
    virtual	void accept(Visitor* v) = 0;
};


class ConcreteElementA : public Element
{
public:
	void accept(Visitor * v) override
	{
		v->visitElementA(this);
	}
};

class ConcreteElementB : public Element
{
public:
	void accept(Visitor * v) override
	{
		v->visitElementB(this);
	}
};

	



class ConcreteVisitor : public Visitor
{
public:
	 void visitElementA(Element* a) override
	 {
		cout<<"visitElementA"<<endl;
	 }
	 void visitElementB(Element* b) override
 	 {
		cout<<"visitElementB"<<endl;
	 }

};

int main(void)
{
	Element* pElementA = new ConcreteElementA();
	Element* pElementB = new ConcreteElementB();
	Visitor* pVisitor = new ConcreteVisitor;
	pElementA->accept(pVisitor);
	pElementB->accept(pVisitor);
}
