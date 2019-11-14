#include <iostream>
#include <utility>
//#include <initializer_list>
using namespace std;
class Point {
public:
	
	int x;
	int y;
public:
	Point(int a, int b) {}
	Point(const Point& src) :x(src.x), y(src.y) {

	}
	Point(Point&& src) : x(src.x), y(src.y) {
		
	}
	Point& operator=(const Point& src) {
		return *this;
	}

	Point& operator=(Point&& src) {
		return *this;
	}
};

template<typename T> class Vector {
	T* buff;
	int sz;
	int capa;
public:	
	Vector(int _sz, T&& po) : sz(_sz), buff(static_cast<T*>(operator new(sizeof(T) * sz))), capa(_sz) {
		for(int i = 0; i < sz; i++) {
			new(&buff[i]) Point(po.x, po.y);
		}
	}
	Vector(initializer_list<T> src) : buff(new T[src.size()]) {
			for(int i =0; i < src.size(); i++) {
				buff[i] = src[i];
			}
	}

	T* begin(Vector<T>& src) {
		return &(src->buff)[0];
	}
	T* end(Vector<T>& src) {
		return &(src->buff)[sz];
	}
	
	int size(void) {
		return sz;
	}
	
	int capacity(void) {
		return capa;
	}
	
	void resize(int _sz, T&& po) {
		if(_sz > capa) {
			T* new_buff = static_cast<T*>(operator new(sizeof(T)*_sz));
			for(int i = 0; i < sz; i++) {
				new_buff[i] = move(buff[i]);
			}
			for(int i = sz; i < _sz; i++) {
				new(&new_buff[i]) T(0,0);
			}
			buff = move(new_buff);
			capa = _sz;
		}
		else {
			if(sz > _sz) {
				for(int i = sz - 1; i >= sz - _sz; i--) {
					buff[i].~T();
				}				
			}
			else {
				//skip...
			}

			
		}
		sz = _sz;
		return ;
	}
};

int main() {
	Vector<Point> v(10, Point(1,1));
	v.resize(20, Point(0,0));
	v.resize(10, Point(0,0));

	cout<<v.size()<<endl;
	cout<<v.capacity()<<endl;
	Vector<int> v2{1,2,3,4,5,6,7,8,9,10};
	for(auto& n : v) {
		cout<<n<<endl;
	}
	return 0;
}
