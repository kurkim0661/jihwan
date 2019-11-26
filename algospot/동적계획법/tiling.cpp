#include <iostream>
#include <algorithm>
#include <cstring>
const int MOD = 1000000007;
/* run this program using the console pauser or add your own getch, system("pause") or input loop */
using namespace std;

int tc;
int n;
int cache[101];
int tile[101];
int tiling(int x) {
	if(x == 0) return 1;
	if(x < 0) return 0;
	int& ret = cache[x];
	if(ret != -1) return ret;
	
	return ret = (tiling(x-1) + tiling(x-2)) % MOD;
}

int count(int x) {
	int ret = cache[n];
	if(n%2 == 1) {
		ret = ret - tiling(n/2);
	}
	else {
		ret = ((ret - tiling(n/2)) + MOD) % MOD;
		ret = (ret - tiling(n/2 - 1) + MOD) % MOD;
		
	}
	return ret;
}
int main(int argc, char** argv) {
	cin>>tc;
	while(tc--) {
		memset(cache,-1,sizeof(cache));
		cin>>n;
		tiling(n);
		cout<<count(n)<<endl;
		
	}
	return 0;
}
