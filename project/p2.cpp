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
	template<typename T, typename ...Args> 
	void print(T A, Args...) {
		cout<<A<<endl;	
	}
	template<typename ... Types>
	static Type& getInstance(Types&& ...args) {
		static Type instance(forward<Types>(args)...);
		cout<<"템플릿 instance"<<endl;
		print(args...);
		//cout<<args<<endl;
		return instance;
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
	Cursor(int x, int y) {}	
};

class Mouse : public Singleton<Mouse>
{
public:
	Mouse() {}	
};

int main() {
	//Mouse& c1 = Mouse::getInstance();
	Cursor& c2	= Cursor::getInstance(1,2);
	cout<<c2.x<<" "<<c2.y<<endl;
	cout<<"ji"<<endl;
}
