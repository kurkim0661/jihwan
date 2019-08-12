#include <iostream>
#include <string>
#include <cstring>
using namespace std;
/* run this program using the console pauser or add your own getch, system("pause") or input loop */
int tc;
int n;
int map[100][100];
int cache [100][100];

int jump(int y, int x) {
	
	
	
	if(y>=n || x>=n) {
		return 0;
	}
	if(y==n-1 && x==n-1) {
		return 1;
	}
	int& ret = cache[y][x];
	
	if(ret != -1) {
		return ret;
	}
	
	int jumpsize = map[y][x];
	return ret = (jump(y+jumpsize,x) || jump(y,x+jumpsize));
	
	
	
}

int main(int argc, char** argv) {
	cin>>tc;
	string ans;
	
	while(tc--) {
		cin>>n;
		memset(cache,-1, sizeof(cache));
		for(int i = 0 ; i < n; i++) {
			for(int j = 0; j < n; j++) {
				cin>>map[i][j];	
			}
		}
		int result = jump(0,0);
		
		if(result == 1) {
			printf("YES\n");
		}
		else {
			printf("NO\n");
		}
//		(result == 1) ? ans = "YES" : ans = "NO";
		cout<<ans<<endl;
		ans.clear();
			
	}	
	return 0;
}

cache를 초기화 안해서 애먹음... 생각보다 쉽다... 
