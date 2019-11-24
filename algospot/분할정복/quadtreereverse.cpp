#include <iostream>
#include <vector>
#include <string>
using namespace std;

int tc;
string quad;

void InputData(void) {
	cin>>quad;
}

string solve(string::iterator& it) {
	char head = *it;
	++it;
	if(head == 'b' || head == 'w') {
		return string(1,head);
	}
	
	string upleft = solve(it);
	string upright = solve(it);
	string downleft = solve(it);
	string downright = solve(it);
	return string("x") + downleft + downright + upleft + upright;
}

int main(void) {
	cin>>tc;
	while(tc--) {
		InputData();
		string::iterator itr;
		itr = quad.begin();
		cout<<solve(itr)<<endl;
		
	}
	return 0;
} 
