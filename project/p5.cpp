#include <iostream>
class Point {
int x;
int y;
public:
	Point(int a, int b) {}
	Point(const Point& src) :x(src.x), y(src.y) {

	}
	Point(Point&& src) : x(src.x), y(src.y) {
		
	}
	Point& operator=(const Point& src) {

	}

	Point& operator=(Point&&) {

	}
};

template<typename T> class Vector {
	T* buff;
	int sz;
	int capa;
public:	
	Vector(size_t _sz, T&& po) : sz(_sz), buff(static_cast<T*>(operator new(sizeof(T) * sz))), capa(_sz) {
		for(int i = 0; i < sz; i++) {
			new(&buff[i]) move(po);
		}
	}

	T& resize(size_t _sz, T&& po) {
		if(_sz > capa) {
			T* new_buff = static_cast<T*>(operator new(sizeof(T)*_sz));
			for(int i = 0; i < sz; i++) {
				new_buff[i] = move(buff[i]);
			}
			for(int i = sz; i < _sz; i++) {
				new(&new_buff[i]) T(0,0);
			}
		}
		else {
			if(sz > _sz) {
				for(int i = sz - 1; i >= sz - _sz; i--) {
					buff[i].~T();
				}				
			}
			else {
				skip...
			}

			sz = _sz;
		}
			
	}
};

int main() {
	Vector<Point> v(10, Point(1,1));

	v.resize(20, Point(0,0));

	v.resize(10, Point(0,0));

	cout<<v.size()<<endl;
	cout<<v.capacity()<<endl;
}
