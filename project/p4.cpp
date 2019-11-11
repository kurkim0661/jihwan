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
		cout<<copy<<endl;
	}
	People(People&& src) noexcept :   name(move(src.name)), addr(move(src.addr)), age(a) { 
		cout<<move<<endl;
	}
	People& operator=(const People& src) {
		cout<<copy=<<endl;
		name = src.name;
		addr = src.addr;
		age = src.age;
		return *this;
	}
	People& operator=(People&& src) {
		cout<<move=<<endl;
		name = move(src.name);
		addr = move(src.addr);
		age = move(src.age);
	}
};

int main() {
	People* p1 = static_cast<People *>(operator new(sizeof(People) * 10));
	for(int i = 0; i < 10; i++) {
		new(&p1[i]) People("홍길동", "서울", 20);
	}

	People* p2 = static_cast<People *>(operator new(sizeof(People) * 20));
	for(int i = 0; i < 10; i++) {
		new(&p2[i]) People(move_if_noexcept(p1[i]));
	}
	for(int i = 10; i < 20; i++) {
		new(&p2[i]) People("unknown", "unknown", 0);
	}
	for(int i = 9; i >= 0; i--) {
		p1[i].~People();
	}
	operator delete p1;
	for(int i = 0; i < 20; i++) {
		cout<<p2[i].name<<" "<<p2[i].addr<<" "<<p2[i].age<<endl;
	}
	
	for(int i = 19; i >= 17; i--) {
		p2[i].~People();
	}
}
