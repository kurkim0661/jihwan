Mediator Pattern
모든 클래스간의 복잡한 로직을 캡슐화하여 하나의 클래스에 위임하여 처리하는 패턴
M:N의 관계에서 M:1의 관계로 복잡도를 떨어뜨려 유지 보수 및 재사용의 확장성에 유리하다.
하나의 클래스가 떠맡아 처리해야 하므로 God 클래스가 될 수 있으므로 주의해야한다.
비슷한 패턴으로 파사드 패턴과 옵저버 패턴이 있다.

#include <iostream>
#include <list>
#include <algorithm>
using namespace std;

class Colleague;
class Mediator
{
public:
	virtual void AddColleague(Colleague* colleague) = 0;
	virtual void Mediate(const char* message, Colleague* sender) = 0;
};


class Colleague
{
public:
	Colleague(Mediator* m)
		:m_Mediator(m)
	{
		m_Mediator->AddColleague(this);	
	}

	void SendMessages(const char* str)
	{
		m_Mediator->Mediate(str, this);
		cout<<"Message : "<<str<<", Sent by: "<<GetName()<<endl;
	}
	void ReceiveMessages(const char* str)
	{
		cout<<"Message : "<<str<<", recv by: "<<GetName()<<endl;
	}

	virtual const char* GetName() = 0;
private:
	Mediator* m_Mediator;
};

class ConcreteColleague1 : public Colleague
{
public:
	ConcreteColleague1(Mediator* m) : Colleague(m){}
	const char* GetName()
	{
		return typeid(this).name();
	}
};

class ConcreteColleague2 : public Colleague
{
public:
	ConcreteColleague1(Mediator* m) : Colleague(m){}
	const char* GetName()
	{
		return typeid(this).name();
	}
};

class ConcreteMediator : public Mediator
{
public:
	void AddColleague(Colleague* colleague)
	{
		m_list.push_back(colleague);
	}
	void Mediate(const char* message, Colleague* sender)
	{
		for(Colleague* object : m_list)
		{
			if(object != sender)
			{
				object->ReceiveMessages(message);
			}

		}
	}
private:
	list<Colleague*> m_list;
};

int main(void)
{
	ConcreteMediator mediator;

	ConcreteColleague1 colleague1(&mediator);
	ConcreteColleague2 colleague2(&mediator);

	colleague1.SendMessages("First Message");
	colleague2.SendMessages("Second Message");

	return 0;
	
}
