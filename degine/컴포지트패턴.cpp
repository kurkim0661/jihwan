Composite pattern Type : Structural
객체와 객체의 그룹을 구분없이 하나의 인터페이스로 다룰 수 있게 한다.
객체와 구성을 트리로 구성하여 하나의 인터페이스에서 사용하도록 고려한 패턴이다.

	
	
#include <iostream>
#include <list>
#include <algorithm>
using namespace std;
class component
{
public:
	bool operator==(const component& rhs)
	{
		if(this->id == rhs.id)
		{
			return true;
		}
		else false;
	}

	virtual void operation() = 0;
	virtual void add(component* c) {};
	virtual void remove(component* c) {};
	virtual component* getChild(component* num) {};
private:
	int id;
};

class Leaf : public component
{
public:
	void operation(void) override 
	{
		cout<<"Leaf"<<endl;
	}
};

class Composite : public component
{
public:
	void operation(void) override
	{
		
	}

	void add(component* c) override
	{
		mlist.push_back(c);
	}
	void remove(component* c) override
	{
		
		auto iter = find(mlist.begin(), mlist.end(), c);
		//int num = iter - mlist.begin();
		mlist.erase(iter);
	}

	component* getChild(component* num) override
	{
		int it = 0;
		for(auto it : mlist)
		{
			if(it == num)
			{
				return it;
			}
		}
		return nullptr;
	}
private:
	list<component*> mlist;
};

int main(void)
{
	Leaf LeafA;
	Leaf LeafB;
	Composite mComposite;

	mComposite.add(&LeafA);
	mComposite.add(&LeafB);

	mComposite.operation();
	return 0;
	
}
/////////////예제 코드
#include <iostream>
#include <algorithm>
#include <list>

using namespace std;

class Unit
{
public:
	virtual void attack(void) = 0;
	virtual void DeleteUnit(void) {}
	virtual Unit* GetUnit(int num){return 0;}
	virtual void MoveUnit(void) = 0;
	virtual void AddUnit(Unit* u){}
	
};

class marin : public Unit
{
public:
	void attack(void) override
	{
		cout<<"마린 공격!"<<endl;
	}
	void MoveUnit(void) override
	{
		cout<<"마린 이동!"<<endl;
	}
};

class firebat : public Unit
{
public:
	void attack(void) override
	{
		cout<<"파뱃 공격!"<<endl;
	}
	void MoveUnit(void) override
	{
		cout<<"파뱃 이동!"<<endl;
	}
};

class tank : public Unit
{
public:
	void attack(void) override
	{
		cout<<"탱크 공격!"<<endl;
	}
	void MoveUnit(void) override
	{
		cout<<"탱크 이동!"<<endl;
	}
};

class Designation : public Unit
{
public:
	void attack(void) override
	{
		for(auto itr : m_list)
		{
			itr->attack();
		}
	}
	void MoveUnit(void) override
	{
		for(auto itr : m_list)
		{
			itr->MoveUnit();
		}
	}
	Unit* GetUnit(int num) override
	{
		int cnt = 0;
		for(auto& itr : m_list)
		{
			if(num == cnt)
			{
				return itr;
			}
			++cnt;
			
		}
		return nullptr;
	}
	void AddUnit(Unit* u) override
	{
		m_list.push_back(u);
	}
private:
	list<Unit*> m_list;
};

int main(void)
{
	marin p_marin;
	firebat p_firebat;
	tank p_tank;
	Unit* p_random;
	Designation p_designation;

	p_designation.AddUnit(&p_marin);
	p_designation.AddUnit(&p_firebat);
	p_designation.AddUnit(&p_tank);

	p_random = p_designation.GetUnit(1);
	p_random->attack();
	p_designation.attack();
	p_designation.MoveUnit();

	return 0;
}
