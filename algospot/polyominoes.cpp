#include <iostream>
#include <algorithm>
#include <cstring>
/* run this program using the console pauser or add your own getch, system("pause") or input loop */
using namespace std;
const int MOD = 10000000;
int cache[101][101];
int tc;
int N;

int polyominoes(int n, int first) {
	if(n == first) return 1;
	int& ret = cache[n][first];
	if(ret != -1) return ret;
	ret = 0;
	for(int second = 1; second <= (n-first); ++second) {
		int place = first + second - 1;
		place *= polyominoes(n-first, second);
		place %= MOD;
		ret += place;
		ret %= MOD;	 
	}
	
	return ret;
}

int main(int argc, char** argv) {
	cin>>tc;
	int add = 0;
	while(tc--) {
		memset(cache,-1,sizeof(cache));
		int add = 0;
		cin>>N;	
		for(int i = 1 ; i<=N; ++i) {
			add += polyominoes(N,i);
		}
		add %= MOD;
		cout<<add<<endl;
	}
	return 0;
}
