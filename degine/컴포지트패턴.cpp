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
