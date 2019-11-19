#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
int main(void) {
	//vector<int> x{1,2,3,4,5,6,7,8,9,10};
	int x[10]{1,2,3,4,5,6,7,8,9,10};
	int y[10];
	//vector<int> y(10,0);
	int v1 = 10;

	auto transform = [v1](auto& _x, auto& _y){
			int i = 0;
			for(auto& n : _y) {
				n = _x[i++] + v1;
			}
		};
	transform(x,y);
	for(auto n : y) {
		cout<<n<<endl;
	}
}
