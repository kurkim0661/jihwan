멀티 스레드 프로그래밍 중에서 클래스 내부의 매서드 호출로 발생되는 셀프 데드락 현상 방지를 위한 패턴이다.
동기화에 필요한 공개함수와 내부에서 사용될 내부 함수를 분리하고, 외부에서 접근하는 공개함수들에 
대해서만 동기화하고 내부 함수를 세분화하여 접근하도록 한다.
#include <list>

class CTest
{
public:
	CTest(int i) : m_id(i){}
	int GetId() const(return m_id;)
private:
	int m_id;
};

class CTestManager : public CMultiThreadSync<CTestManager>
{
public:
	CTestManager() {}
	~CTestManager()
	{
		for each(CTest* var in mList)
			delete var;
		mList.clear();
	}

	void insert(CTest* i)
	{
		CThreadSync cs;
		insert_i(i);
	}

	bool search(CTest* i)
	{
		CThreadSync cs;
		return search_i(i);
	}
private:
	void insert_i(CTest* i)
	{
		if(!search_i(i))
		{
			mList.push_back(i);
		}
	}
	void search_i(CTest* i)
	{
		for each(CTest* var in mList)
		{
			if(var->GetId() == i->GetId())
			{
				return true;
			}
		}
		return false;
	}
	list<CTest*> mList;


};

int main(void)
{
	CTestManager mTestManager;
	mTestManager.insert(new CTest(1024));
	return 0;
}
