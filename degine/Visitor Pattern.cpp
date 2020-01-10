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
{ㄷ
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
//////////////////////////예제 코드
#include <iostream>
#include <algorithm>
#include <list>
using namespace std;

class Visitor;
class Element
{
public:
	virtual void accept(Visitor* v) = 0;
};

class Wheel : public Element
{
public:
	Wheel(const char* name)
		:m_name(name){}
	void accept(Visitor* v) override;
	const char* GetName(void) const
	{
		return m_name.c_str();
	}
private:
	string m_name;
};

class Body : public Element
{
public:
	void accept(Visitor* v) override;
};

class Engine : public Element
{
public:
	void accept(Visitor* v) override;
};



class Car : public Element
{
public:
	void append(Element* e)
	{
		m_list.push_back(e);
	}
	void accept(Visitor* v) override;
private:
	list<Element*> m_list;
};

class Visitor
{
public:
	virtual void visit(Body* e) = 0;
	virtual	void visit(Car* e) = 0;
	virtual	void visit(Wheel* e) = 0;
	virtual void visit(Engine* e) = 0;
};
class CarStartVisitor : public Visitor
{
public:
	void visit(Body* e) override
	{
		cout<<"Moving my Body"<<endl;
	}
	void visit(Car* e)
	{
		cout<<"Starting my engine"<<endl;
	}
	void visit(Wheel* e)
	{
		cout<<"Kicking my "<<e->GetName()<<"Wheel"<<endl;
	}
	void visit(Engine* e)
	{
		cout<<"Starting my engine"<<endl;
	}
};
	
void Body::accept(Visitor * v)
{
	v->visit(this);
}
void Engine::accept(Visitor * v)
{
	v->visit(this);
}
void Wheel::accept(Visitor * v)
{
	v->visit(this);
}
void Car::accept(Visitor * v)
{
	for(auto itr : m_list)
	{
		itr->accept(v);
	}
	v->visit(this);
}



int main(void)
{
	Wheel pwheel[4] = {"front left", "front right", "back right", "back left"};
	Engine pengine;
	Body pbody;
	Car pcar;

	pcar.append(&pwheel[0]);
	pcar.append(&pwheel[1]);
	pcar.append(&pwheel[2]);
	pcar.append(&pwheel[3]);
	pcar.append(&pengine);
	pcar.append(&pbody);

	CarStartVisitor start;
	pcar.accept(&start);

	return 0;
}


전방 선언 및 하단 구현을 할 때 전방선언을 한 클래스에 순수가상함수가 있다면 파생클래스 또한
정의를 해준 다음에 하단 구현을 해주어야한다.  string 으로 되어 있으면 "blah blah"와 같은 것으로 
선언이 안된다.
