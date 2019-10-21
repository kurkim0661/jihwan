#include <iostream>
#include <string>
 
#include <vector>
#include <algorithm>
#include <cstring>
 
using namespace std;
 
int TC;
string single;
char lefts[] = "({[";
char rights[] = ")}]";
vector<int> lastone;
 
bool solve(void) {
	int idx = 0;
	bool ret = true;
	for(int i = 0; single.size(); i++) {
		for(int j = 0; j <3; j++) {
			if(single[i] == rights[j]) {
				if(lastone.back() != j && lastone.empty() != true) {
					ret = false;
					return ret;
				}
				lastone.pop_back();
			}
			if(single[i] == lefts[j]) {
				lastone.push_back(j);
				break;
			}
		}
 
 
	}
	return ret;
}
 
int main(void) {
	cin>>TC;
	bool ret = true;
	while(TC--) {
		single.clear();
		cin>>single;
 
		ret = solve();
		if(ret) {
			cout<<"YES"<<endl;
		}
		else {
			cout<<"NO"<<endl;
		}
	}
}
