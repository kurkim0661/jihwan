Chain of Responsibility Type : Behavioral

요청을 처리할 수 있는 기회를 하나 이상의 객체에게 부여함으로써 요청하는 객체와 처리하는 객체 사이의 결합도를 없애는 패턴
요청을 해결할 객체를 만날 때까지 객체 고려를 따라서 요청을 전달한다.
일반적으로 처리할 수 있는 모든 객체들을 그리고 묶고 맨 처음 객체에게 요청을 전달하여 처리하지 못하면
다음 객체로 넘기는 방식(선처리 후 책임 전가)으로 진행된다.
연결리스트라고 생각하면 이해가 쉽다.

#include <iostream>
#include <list>
#include <algorithm>
using namespace std;

class Handler
{
public:
	Handler(Handler* h)
		: next(p) {}
	~Handler()
	{
		if(next)
			delete next;
	}
	virtual void HandleRequest(int i) 
	{
		if(next != nullptr)
		{
			next->HandleRequest(i);
		}
	}
private:
	Handler* next;
};

class ConcreteHandler1 : public Handler
{
public:
	ConcreteHandler1(Handler* h)
		:Handler(h){}
	void HandleRequest(int i) override
	{
		if(i%2 != 0)
		{
			cout<<"짝수 "<<endl;
		}
		else
		{
			Handler::HandleRequest(i);		
		}
	}
};

class ConcreteHandler2 : public Handler
{
public:
	ConcreteHandler2(Handler* h)
		:Handler(h){}
	void HandleRequest(int i) override
	{
		if(i%2 == 0)
		{
			cout<<"홀수 "<<endl;
		}
		else
		{
			Handler::HandleRequest(i);		
		}
	}
};

int main(void)
{
	Handler* p_handler = new ConcreteHandler1(new ConcreteHandler2(nullptr));
	p_handler->HandleRequest(25);
	delete p_handler;
	return 0;
}

////////////예제
#include <iostream>
#include <list>
#include <string>
#include <algorithm>
using namespace std;

class Requester
{
public:
	virtual const char* class1(void) = 0;

};

class Elementry : public Requester
{
public:
	const char* class1(void) override
	{
		return "초등학생입니다.";
	}
};

class Middle : public Requester
{
public:
	const char* class1(void) override
	{
		return "중학생입니다.";
	}
};

class High : public Requester
{
public:
	const char* class1(void) override
	{
		return "고등학생입니다.";
	}
};

class Consultant
{
public:
	Consultant(Consultant* r)
		:m_next(r){}
	~Consultant()
	{
		if(m_next)
			delete m_next;
	}
	virtual void consult(Requester* user)
	{
		if(m_next != nullptr)
		{
			m_next->consult(user);
		}
		else
		{
			cout<<"상담 불가"<<endl;
		}
	}

private:
	Consultant* m_next;
};

class ElementryConsult : public Consultant
{
public:
	ElementryConsult(Consultant* c)
		:Consultant(c){}
	void consult(Requester* user) override
	{
		if(dynamic_cast<Elementry*>(user) != nullptr)
			cout<<"초등학생 상담입니다."<<endl;
		else
			Consultant::consult(user);
	}
};

class MiddleConsult : public Consultant
{
public:
	MiddleConsult(Consultant* c)
		:Consultant(c){}
	void consult(Requester* user) override
	{
		if(dynamic_cast<Middle*>(user) != nullptr)
			cout<<"중학생 상담입니다."<<endl;
		else
			Consultant::consult(user);
	}
};

class HighConsult : public Consultant
{
public:
	HighConsult(Consultant* c)
		:Consultant(c){}
	void consult(Requester* user) override
	{
		if(dynamic_cast<High*>(user) != nullptr)
			cout<<"고등학생 상담입니다."<<endl;
		else
			Consultant::consult(user);
	}
};

int main(void)
{
	Middle p_req;
	Consultant* p_con = new ElementryConsult(new HighConsult(new MiddleConsult(nullptr)));
	p_con->consult(&p_req);
	delete p_con;
	return 0;
}
