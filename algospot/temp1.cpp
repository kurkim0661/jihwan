#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;
const int MOD = 1000000007;
int K;
int M;
int tc;
string word[15];
int sum[15][15];
int cache[15][1<15]

int solve(int last, int used) {
	if(used == (1<<K - 1)) {
		return 0;
	}
	int& ret = cache[last][used];
	if(ret != -1) {
		return ret;
	}
	ret = 0;
	for(int next = 0; next < K; next++) {
		if(used & 1<<next == 0) {
			ret = max(ret, sum[last][next] + solve(next, used + 1<<next));
		}
	}
	return ret;
}

string reconstruct(int last, int used) {
	if(used == (i<<K - 1)) {
		return ""; 
	}
	int maxsum = solve(last,used);
	for(int next = 0; next < K; next++) {
		if(maxsum == solve(next,used)) {
			return word[next].substr(sum[last][next]) + reconstruct(next, used + 1<<next);
		}
	}
}

int wordsum(const string s1, const string s2) {
	for(int len = min(s1.size(),s2.size()); len > 0; len--) {
		if(s1.substr(s1.size() - len) == s2.substr(0,len)) {
			return len;
		}
	}
}
int main(void) {
	cin>>tc;
	while(tc--) {
		cin>>K;
		for(int i = 0; i < K; i++) {
			cin>>word[i];
		}

		for(int i = 0; i < K; i++) {
			for(int j = i + 1; j < K; j++) {
				if(word[i].find(word[j]) != -1) {
					word[j] = word[K];
				}
				K--;
			}
		}
		word[K] = "";
		for(int i = 0; i < K; i++) {
			for(int j = 0; j < K; j++) {
				sum[i][j] = wordsum(word[i],word[j]);
			}
			
		}

		
		
	}
	
}
