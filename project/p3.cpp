#include <string>
#include <iostream>
using namespace std;

class People {
	string name;
	string addr;
	int age;
public:
	People(string n, string add, int a) : name(n), addr(add), age(a) {}
	People(const People& src) : name(src.name), addr(src.addr), age(src.age) {
		cout<<"copy"<<endl;
	}
	People(People&& src) : name(move(src.name)), addr(move(src.addr)), age(src.age) { 
		cout<<"move"<<endl;
	}
	People& operator=(const People& src) {
		cout<<"copy="<<endl;
		name = src.name;
		addr = src.addr;
		age = src.age;
		return *this;
	}
	People& operator=(People&& src) {
		cout<<"move="<<endl;
		name = move(src.name);
		addr = move(src.addr);
		age = move(src.age);
	}
};

int main() {
	People p1{"홍길동", "서울", 20};
	People p2 = p1;
	People p3 = move(p1);
}
