#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int TC;
int N;
int need[201];
int aleady[201];

int gcd(int a, int b) {
	if(b==0) {
		return a;
	}
	return gcd(b,a%b);
}

int ceil(int a, int b) {
	return (a + b - 1) / b;
}

vector<int> solve(void) {
	vector<int> result;
	int b=need[0];
	for(int i = 1; i < N; i ++) {
		b = gcd(b, need[i]);
	}
	int a = b;

	for(int i = 0; i < N; i ++) {
		a = max(a, ceil(aleady[i] * b, need[i]));
		
	}
	for(int i = 0; i < N; i++) {
		result.push_back(need[i]*a/b - aleady[i]);
	}
	return result;
}


int main(void) {
	vector<int> ret;
	cin>>TC;
	while(TC--) {
		cin>>N;
		for(int i = 0; i < N; i ++) {
			cin>>need[i];
		}
		for(int i = 0; i < N; i ++) {
			cin>>aleady[i];
		}
		base = maxpill();
		for(int i = 0; i < N; i++) {
			if(aleady[i]/need[i] == maxratio)
		}
		ret = solve();
		for(int i = 0; i < ret.size(); i++) {
			printf("%d ",ret[i]);
		}
		cout<<endl;
		
	}
}
