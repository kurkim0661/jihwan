class Aggregate
{
public:
	Aggregate() : mTotalCount(0) {}
	friend class iterator;
	virtual	iterator* createiterator(void) = 0;
	virtual void AddNext(Element* pNewElement, Element* pElement = 0) = 0;
	virtual void Remove(Element* pElement) = 0;
	virtual Element* GetItem(int pos) = 0;

	int GetCount() const
	{
		return mTotalCount;
	}

private:
	int mTotalCount;
};

class LinkList : public Aggregate
{
public:
	LinkList() : pFirst(nullptr) {}

	struct LinkedElement
	{
		LinkedElement(Element* pitem = 0;, LinkedElement* pNext_ = 0)
			: pData(pitem), pNext(pNext_)
		{
			Element* pData;
			LinkedElement* pNext;
		};
	};
	
	iterator* createiterator(void);
	void AddNext(Element * pNewElement, Element * pElement = 0)
	{
		if(pFirst ==0)
		{
			pFirst = new LinkedElement(pNewElement);
		}
		else if(pElement == 0 || pElement == pFirst->pData)
		{
			LinkedElement* pTmp = pFirst->pNext;
			pFirst->pNext = new LinkedElement(pNewElement, pTmp);
		}
		else 
		{
			LinkedElement* pPrev = 0;
			LinkedElement* pTmp = pFirst;
			while(pTmp != 0 && pTmp->pData != pElement)
			{
				pPrev = pTmp;
				pTmp = pTmp->pNext;
			}
			if(pTmp!=0)
			{
				LinkedElement* pTmp2 = pTmp->pNext;
				pTmp->pNext = new LinkedElement(pNewElement, pTmp2);
			}
			else
			{
				pPrev->pNext = new LinkedElement(pNewElement, 0);
			}

			
				
		}
		mTotalCount++;
	}

	void Remove(Element* pElement)
	{
		if(pElement == 0)
		{
			return;
		}

		LinkedElement* pPrev = 0;
		LinkedElement* pTmp = pFirst;
		while(pTmp != 0 && pTmp->pData != pElement)
		{
			pPrev = pTmp;
			pTmp = pTmp->pNext;
		}

		if(pTmp != 0)
		{
			if(pTmp == pFirst)
			{
				delete pTmp;
				pFirst = 0;
			}
			else
			{
				pPrev->pNext = pTmp->pNext;
				delete pTmp;
			}
			mTotalCount--;
		}

		Element* GetItem(int pos) 
		{
			int cnt = 0;
			LinkedElement* pTmp = pFirst;
			while(pTmp != 0 && cnt != pos)
			{
				pTmp = pTmp->pNext;
				cnt++;
			}
			if(pTmp != 0)
			{
				return pTmp->pData;
			}
			else 
			{
				return 0;
			}
		}
	}
private:
	LinkedElement* pFirst;
};

class iterator
{
public:
	virtual void first() = 0;
	virtual void next() = 0;
	virtual void isDone() = 0;
	virtual Element* GetItem() = 0;
};

class Listiterator :public iterator
{
public:
	Listiterator(Aggregate* a) 
		:pAggregate(a), curPos(0)
	{}
	~Listiterator() 
	{
		if(pAggregate)
		{
			delete pAggregate;
		}
	}
	void first() override
	{
		curPos = 0;
	}
	void next() override
	{
		curPos++;
	}
	bool isDone() override
	{
		return curPos >= pAggregate->GetCount();
	}
	Element* GetItem() override
	{
		return pAggregate->GetItem(curPos);
	}
private:
	Aggregate* pAggregate;
	int curPos;
};

iterator* LinkList::createiterator(void)
{
	return new Listiterator(this);
}

class iteratorPtr
{
public:
	iteratorPtr(iterator* it) : piter(it)
	{}
	~iteratorPtr() 
	{
		delete piter;
	}
	iterator* operator->()
	{
		return piter;
	}
	iterator& operator*()
	{
		return *piter;
	}
protected:
	iteratorPtr(const iteratorPtr& rhs);
	iteratorPtr& operator=(const iteratorPtr& rhs);

private:
	iterator* piter;

int main(void)
{
	Element a("a");
	LinkList list;
	list.AddNext(&a);
	iteratorPtr it(Listiterator*)list.createiterator());

	for(it->first() !it->isDone(); it->next()_)
	{
		cout<<it->GetItem()->data<<endl;
	}
	return 0;
}
};

------------------예제 코드
#include <iostream>
#include <string>
using namespace std;

class Iterator;
class Element
{
public:
	Element(string str) : data(str){}
	string data;
};

class Aggregate
{
public:
	Aggregate()
		:mStackPoint(-1){}

	friend class Iterator;
	virtual Iterator* CreateIterator(void) = 0;
	virtual void push(Element* p_element) = 0;
	virtual Element* pop(void) = 0;
	virtual Element* GetElement(int idx) = 0;
	bool IsEmpty(void) 
	{
		return mStackPoint == -1;
	}
	int GetStackpoint(void)
	{
		return mStackPoint;
	}
protected:
	int mStackPoint;
};


const int STACK_SIZE = 10;
class Stack : public Aggregate
{
public:
	Iterator* CreateIterator(void);
	void push(Element* pElement)
	{
		if(mStackPoint + 1 < STACK_SIZE)
		{
			m_item[++mStackPoint] = pElement;
		}
		else
		{
			cout<<"Stack  is Full"<<endl;
		}
	}
	Element* pop(void)
	{
		if(!IsEmpty())
		{
			return m_item[mStackPoint--];
		}
		else
		{
			cout<<"Stack is Empty"<<endl;
		}
		return nullptr;
	}

	Element* GetElement(int idx)
	{
		return m_item[idx];
	}
private:
	Element* m_item[STACK_SIZE];
};

class Iterator
{
public:
	virtual	void first(void) = 0;
	virtual Element* GetItem(void) = 0;
	virtual bool IsDone(void) = 0;
	virtual void next(void) = 0;
};

class StackIterator : public Iterator
{
public:
	StackIterator(Aggregate* a)
		: m_Aggreagte(a), mIdx(0){}
	~StackIterator()
	{
		if(m_Aggreagte)
			delete m_Aggreagte;
	}
	void first(void) override
	{
		mIdx = 0;
	}
	void next(void ) override
	{
		mIdx++;
	}
	bool IsDone(void) override
	{
		return mIdx == (m_Aggreagte->GetStackpoint() + 1);
	}
	Element* GetItem(void) override
	{
		return m_Aggreagte->GetElement(mIdx);
	}
private:
	Aggregate* m_Aggreagte;
	int mIdx = 0;
};

Iterator* Stack::CreateIterator(void)
{
	return new StackIterator(this);
}

class IteratorPtr
{
public:
	IteratorPtr(Iterator* it)
		:m_itr(it){}
	~IteratorPtr()
	{
		delete m_itr;
	}

	Iterator* operator->()
	{
		return m_itr;
	}
	Iterator& operator*()
	{
		return *m_itr;
	}

protected:
	IteratorPtr(const IteratorPtr& rhs);
	IteratorPtr& operator=(const IteratorPtr& rhs);
private:
	Iterator* m_itr;
};
void PrintData(IteratorPtr& it)
{
	cout<<"~~~~~~~~<Print Stack>~~~~~~~~~~~~"<<endl;
	for(it->first(); !it->IsDone(); it->next())
	{
		cout<<it->GetItem()->data<<endl;
	}
	cout<<"~~~~~~~~end~~~~~~~~~"<<endl;
}

int main(void)
{
	Element a("a"), b("b"), c("c"), d("d"), e("e");

	Stack stack;
	stack.push(&a);
	stack.push(&b);
	stack.push(&c);
	stack.push(&d);
	stack.push(&e);

	IteratorPtr it((StackIterator*)stack.CreateIterator());
	PrintData(it);

	Element* p1 = stack.pop();
	Element* p2 = stack.pop();
	cout<<"pop 1 : "<<p1->data<<endl;
	cout<<"pop 2 : "<<p2->data<<endl;

}



