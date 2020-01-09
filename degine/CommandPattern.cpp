Command Pattern Type : Behavioral
메소드를 객체의 형태로 캡슐화하는 것이 가장 큰 목적이다.
특정한 일을 하는 기능들을 따로따로 객체화하여 요청의 종류와는 무관하게 프로그램 작성이 가능하게 만들어준다.

#include <iostream>
using namespace std;

class Receiver
{
public:
	void action(void)
	{
		cout<<"Receiver : To do something..."<<endl;
	}
};

class Command
{
public:
	virtual void execute() = 0;
};

class ConcreteCommand : public Command
{
public:
	void setReceiver(Receiver* r)
	{
		m_Receiver = r;
	}
	void execute(void) override
	{
		m_Receiver->action();
	}
private:
	Receiver* m_Receiver;
};

class Invoker
{
public:
	void SetCommand(Command* command)
	{
		m_Command = command;
	}
	void Execute()
	{
		m_Command->execute();
	}
private:
	Command* m_Command;
};

int main(void)
{
	Invoker pInvoker;
	Receiver preceiver;
	ConcreteCommand pcommand;

	pcommand.setReceiver(&preceiver);
	pInvoker.SetCommand(&pcommand);
	pInvoker.Execute();

	return 0;
}

////////////////// 예제코드
#include <iostream>
using namespace std;


class Receiver
{
public:
	virtual void Execute(void) = 0;
};

class SaveFile : public Receiver
{
public:
	void Execute(void) override
	{
		cout<<"Save file"<<endl;
	}
};

class MakeFile : public Receiver
{
public:
	void Execute(void) override
	{
		cout<<"Make file"<<endl;
	}
};


class CloseFile : public Receiver
{
public:
	void Execute(void) override
	{
		cout<<"Close file"<<endl;
	}
};

class Command
{
public:
	virtual void Execute(void) = 0;	
};

class CloseCommand : public Command
{
public:
	void Execute(void) override
	{
		m_receiver->Execute();
	}

private:
	Receiver* m_receiver;
};

class SaveCommand : public Command
{
public:
	void Execute(void) override
	{
		m_receiver->Execute();
	}
private:
	Receiver* m_receiver;
};

class MakeCommand : public Command
{
public:
	void Execute(void) override
	{
		m_receiver->Execute();
	}
	void SetReceiver(Receiver* r) 
	{
		m_receiver = r;
	}
private:
	Receiver* m_receiver;
};

class Processer
{
public:
	void Set_Command(Command* c)
	{
		m_command = c;
	}
	void Command_Execute(void)
	{
		m_command->Execute();
	}
private:
	Command* m_command;
};

int main(void)
{
	Processer processor;
	MakeCommand make;
	SaveCommand save;
	CloseCommand close;
	MakeFile receiver1;
	CloseFile receiver2;
	SaveFile receiver3;

	make.SetReceiver(&receiver1);
	processor.Set_Command(&make);
	processor.Command_Execute();
}
