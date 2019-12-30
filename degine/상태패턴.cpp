객체의 상태에 따라 각각의 행위를 변경할 수 있게 캡슐화한다.
  동적으로 행동을 교체 할 수 있다.
전략 패턴과 유사하나 그 의미가 다르다.

 #include <iostream>

class State
{
public:
	virtual void handle() = 0;
};


class ConcreteState1 : State
{
public:
	void handle(void) override 
	{
		cout<< "ConcreteState1"<<endl;
	}
};

class ConcreteState2 : State
{
public:
	void handle(void) override 
	{
		cout<< "ConcreteState2"<<endl;
	}
};

class Context
{
public:
	Context(State* c) : mState(c) {}
	~Context()
	{
		if(mState)
		{
			delete mState;
		}
	}

	void SetState(State* state)
	{
		if(mState)
		{
			delete mState;
			mState = state;
		}
	}

	void request()
	{
		mState->handle();
	}
private:
	State* mState;
};

int main(void)
{
	Context* pContext = new Context(new ConcreteState1());
	pContext->request();

	pContext->SetState(new ConcreteState2);
	pContext->request();

	delete pContext;
	return 0;
}

