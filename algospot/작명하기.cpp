#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
using namespace std;


int TC;
string father;
string mother;
string child;

vector<int> makename(void) {
	string suffix;
	string prefix;
	int len;
	vector<int> result;
	for(int i = 0; i < child.size() - 1; i++) {
		prefix = child.substr(0,i);
		suffix = child.substr(child.size() - 1 - i,child.size() - 1);
		if(prefix.compare(suffix) == true) {
			len = i + 1;
			result.push_back(len);
		}
	}

int main(void) {
	cin>>TC;
	vector<int> ret;
	while(TC--) {
		cin>>father>>mother;
		child = father + mother;
		ret = makename();
		sort(ret.begin(), ret.end());
		for(int i = 0; i < ret.size(); i++) {
			cout<<ret[i]<<" ";
		}
		cout<<endl;
	}
}
