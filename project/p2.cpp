#include <iostream>
#include <type_traits>
using namespace std;
template<typename Type> class Singleton {
protected:
	Singleton() = default;
private:
	Singleton(const Singleton&) = delete;
	Singleton& operator=(const Singleton&) = delete;
	Singleton(Singleton&& src) {
			
	}
public:
	void print() {
		
	}
	template<typename ...Types> 
	static Type& getInstance(Types&& ...args) {
		static Type instance(forward<Types>(args)...);
		return instance;
	}

	static Type& construct() {

	}
	/*
	static Type& getInstance(int x, int y) {
		static Type instance(x,y);
		return instance;
	}
	*/
};

class Cursor : public Singleton<Cursor> {
public:	
	int x;
	int y;
public:
	Cursor(int _x, int _y) : x(_x), y(_y) {
		cout<<"create"<<endl;
	}
	Cursor(const Cursor&   src) : x(src.x), y(src.y) {
		cout<<"copy"<<endl;
	}
	Cursor(Cursor&& src) : x(src.x), y(src.y) {
		cout<<"move"<<endl;
	}
	Cursor& operator=(const Cursor& src) {
		x = src.x;
		y = src.y;
		cout<<"copy="<<endl;
	}
	Cursor& operator=(Cursor&& src) {
		x = src.x;
		y = src.y;
		cout<<"move="<<endl;
	}
};

class Mouse : public Singleton<Mouse>
{
public:
	Mouse() {}	
};

int main() {
	Mouse& c1 = Mouse::getInstance();
	Cursor& c2	= Cursor::getInstance(1,2);
	cout<<c2.x<<" "<<c2.y<<endl;
}

