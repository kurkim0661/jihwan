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
