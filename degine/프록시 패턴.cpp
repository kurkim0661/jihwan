대리자로서 일을 맡기면 그 일을 처리하고 완료되면 그 결과를 알려주는 패턴입니다.
프록시 패턴의 잘 알려진 예로는 참조 횟수 스마트 포인터가 있다.

  
  class Subject
{
public:
	virtual void request() = 0;
};

class RealSubject : public Subject
{
	void request(void) override
	{
		cout<<"RealSubject"<<endl;
	}
};

class Proxy : public Subject
{
public:
	Proxy() : mRealSubject(nullptr)
	{}
	~Proxy()
	{
		if(mRealSubject)
		{
			delete mRealSubject;
		}
	}
	void request(void) override
	{
		if(mRealSubject)
		{
			mRealSubject = new RealSubject;
		}
		mRealSubject->request();
	}
private:
	RealSubject* mRealSubject;
};
