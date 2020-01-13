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
--------------------
	#include <iostream>
#include <string>
#include <list>
#include <algorithm>
using namespace std;
class Collegue;


class Mediator
{
public:
	virtual void AppendUser(Collegue* c) = 0;
	virtual void RemoveUser(Collegue* c) = 0;
	virtual void SendMessages(string m, Collegue* sender) = 0;
};


class Collegue
{
protected:
	string m_name;
	Mediator* m_mediator;

public:
	Collegue(Mediator* m, string str)
		:m_mediator(m), m_name(str){}
	virtual void ReceiveMessages(string m) = 0;
	virtual void SendMessages(string m) = 0;
};

class User : public Collegue
{
public:
	User(Mediator* m, string str)
		:Collegue(m, str){}
	void ReceiveMessages(string m)
	{
		cout<<"Receive : "<<m<<endl;
	}

	void SendMessages(string m)
	{
		cout<<"Send : "<<m<<endl;
		m_mediator->SendMessages(m, this);
	}
};
class ChatMediator : public Mediator
{
private:
	list<Collegue*> m_list;
public:
	void AppendUser(Collegue * c)
	{
		m_list.push_back(c);
	}
	void RemoveUser(Collegue * c)
	{
		m_list.remove(c);
	}
	void SendMessages(string m, Collegue* sender)
	{
		for(auto itr : m_list)
		{
			if(itr != sender)
			{
				itr->ReceiveMessages(m);
			}
		}
	}
};
int main(void)
{
	ChatMediator p_mediator;
	User usr1(&p_mediator, "홍길동");
	User usr2(&p_mediator, "심청이");
	User usr3(&p_mediator, "르브론 제임스");
	p_mediator.AppendUser(&usr1);
	p_mediator.AppendUser(&usr2);
	p_mediator.AppendUser(&usr3);

	usr1.SendMessages("나는 홍길동.");
	usr2.SendMessages("나는 심청이.");
	
}
정의의 순서가 굉장히 중요하다.

