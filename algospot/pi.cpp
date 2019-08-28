#include <iostream>
#include <algorithm> 
#include <string>
#define INF 987654321

using namespace std;

int tc;
int cache[10000];

int calculate(int a, int b) {
	string M = N.substr(a, b-a+1);
	// 난이도 1에 해당하는 것
	bool same = true;
	for(int i = 1; i < M.size(); i++) {
		if(M[0] != M[i]) same ==false;
	}
	if(same == ture) return 1;
	//난이도 2
	bool progresive = true	
	for(int i = 2; i < M.size(); i++) {
		if(M[i]-M[i-1] != M[i-1] - M[i-2]) {
			progresive = false;
		}
	}
	if(progresive == true && abs(M[1]-M[0]) == 1) return 2;
	bool alternating = true;
	for(int i =2; i < M.size(); i++) {
		if(M[i] != M[i%2]) alternating = false;
	}
	if(alternating == true) return 4;
	if(progresive == true) return 5;
	return 10;
	//난이도 5 
	
}

int memorize(int start) {
	if(start == N.size()) return 0;
	int& ret = cache[start];
	if(ret != -1) return ret;
	ret = INF;
	
	for(int length = 3; length<=5; length++) {
		if(start+length <= N.size()) {
			ret = min(ret,calculate(start,start + length) + memorize(start+length-1));
		}
	}	
	return ret;
}


int main(int argc, char** argv) {
	cin>>tc;
	
	while(tc--) {
		memset(cache,-1,sizeof(cache));
		string pi;
		cin>>pi;
				
	}
	
	return 0;
}
