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

///////////////예제
#include <iostream>
#include <string>
using namespace std;

class Image
{
public:
	virtual void ShowImage() = 0;
};

class RealImage : public Image
{
public:
	RealImage(const char* name)
		:mFile(name){}
	void LoadImage()
	{
		cout<<"disk from loading file: "<<mFile.c_str()<<endl;
	}
	void ShowImage()
	{
		cout<<"Show image : "<<mFile.c_str()<<endl;
	}
private:
	string mFile;
};

class ProxyImage : public Image
{
public:
	ProxyImage(const char* name)
		:mFile(name), m_Image(nullptr)
	{}
	~ProxyImage()
	{
		if(m_Image)
		{
			delete m_Image;
		}
	}
	void ShowImage()
	{
		if(!m_Image)
		{
			m_Image = new RealImage(mFile.c_str());
			m_Image->LoadImage();
		}
		m_Image->ShowImage();
	}
private:
	RealImage* m_Image;
	string mFile;
};

int main(void)
{
	Image* p_Image = new ProxyImage("image.png");
	p_Image->ShowImage();
	p_Image->ShowImage();
	p_Image->ShowImage();
	delete p_Image;

	return 0;
}
