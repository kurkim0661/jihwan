#include <iostream>
#include <algorithm>
#include <cstring>
int tc;
int n;
int triangle[101][101];
int cache[101][101];
int cnt;
using namespace std;
 
 
int solve(int y, int x) {
	//기저사례.
	int& ret = cache[y][x];
	if(y == n-1) return ret = triangle[y][x];
	if(ret != -1) return ret;
	return ret = (max(solve(y+1,x),solve(y+1,x+1)) + triangle[y][x]); 
}

int count(int y, int x) {
	if(y == n - 1) return 0;
	if(cache[y+1][x] < cache[y+1][x+1]) {
		count(y+1,x+1);	
	}
	else if(cache[y+1][x] > cache[y+1][x+1]) {
		count(y+1,x);	
	}A
	else {
		cnt++;
		count(y+1,x+1);
		count(y+1,x);	
	}
	
}
 
int main(int argc, char** argv) {
	
	cin>>tc;
	while(tc--) {
		cnt = 1;
		memset(cache,-1,sizeof(cache));
		cin>>n;
		for(int i = 0 ; i < n; i++) {
			for(int j = 0; j<=i; j++) {
				cin>>triangle[i][j];
			}
		}
		
//		cout<<solve(0,0)<<endl;
		solve(0,0);
		count(0,0);
		cout<<cnt<<endl;
//		for(int i = 0 ; i < n; i++) {
//			for(int j = 0; j<=i; j++) {
//				cout<<cache[i][j]<<" ";
//			}
//			cout<<endl;
//		}	
		memset(triangle,0,sizeof(triangle));
	}
	
	return 0;
}
