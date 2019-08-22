#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;
/* run this program using the console pauser or add your own getch, system("pause") or input loop */
int tc;
int n;
int arr[100][100];
int cashe[100][100];
 
 
int solve(int y, int x) {
	
	if(y == n-1) return arr[y][x];
	
	int& ret = cashe[y][x];
	if(ret != -1) return ret;	
	
	return ret = max(solve(y+1,x),solve(y+1,x+1)) + arr[y][x];
	
}
 
int main(int argc, char** argv) {
	cin>>tc;
	while(tc--) {
		memset(cashe,-1,sizeof(cashe));
		cin>>n;
		if(n < 2 || n > 100) exit(-1);
		
		for(int i = 0; i < n; i++) {
			for(int j = 0; j <= i; j++) {
				cin>>arr[i][j];
				if(arr[i][j] < 1 || arr[i][j] > 100000) exit(-1);
			}
		}
		cout<<solve(0,0)<<endl;
		memset(arr,0,sizeof(arr));
	}
	return 0;
}

왜 오답이 나올까...?
