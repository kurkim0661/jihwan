Memento Pattern - 메멘토 패턴
객체의 상태 정보를 저장 및 복원 하는 패턴
객체의 내부 상태정보마 가지는 클래스를 따로 생성하여 관리하는 구조로써, 저장할 상태정보가 많을 경우 문제가 도리 수 있다.
대표적인 예로 바둑, 장기 등 기보 되돌리기, 바둑이 물리기 기능 등을 꼽을 수 있다.

#include <iostream>
#include <stack>
#include <string>
using namespace std;

class Memento
{
public:
	Memento(string _state)
	{
		m_state = _state;	
	}
	string getState(void) const
	{
		return m_state;	
	}
private:
	string m_state;
};

class Originator
{
public:
	void setState(string s)
	{
		m_state = s;
		cout<<"Originator : Setting state to "<<m_state<<endl;
	}
	
	void setMemento(Memento* m)
	{
		if(m)
		{
			m_state = m->getState();
			delete m;
			cout<<"Originator : State after restoring form Memento "<<m_state<<endl;
		}
	}
	
	Memento* createMemento()
	{
		cout<<"Originator : Create to Memento "<<m_state<<endl;	
		return new Memento(m_state); // 상태정보를 이용해서 새로운 Memento를 생성한다. 
	}
	
private:
	string m_state; //상태정보.
};

class Caretaker
{
public:
	void pushMemento(Memento* m) 
	{
		m_Stack.push(m);
	}
	Memento* popMemento()
	{
		Memento* m = m_Stack.top();
		m_Stack.pop();
		return m;	
	}
private:
	stack<Memento *> m_Stack;
};

int main(void)
{
	Caretaker m_Caretaker;
	Originator *originator = new Originator();
	
	originator->setState(string("state1"));
	m_Caretaker.pushMemento(originator->createMemento());	
	
	originator->setState(string("state2"));
	m_Caretaker.pushMemento(originator->createMemento());
	
	originator->setMemento(m_Caretaker.popMemento());
	originator->setMemento(m_Caretaker.popMemento());
	
	delete originator;
	return 0;
}
