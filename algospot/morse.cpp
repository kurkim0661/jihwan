#include <iostream>
#include <algorithm>

using namespace std;

int tc;
int n;
int m;
int k;
int bino[201][201];
const int MAX = 1000000000 + 100;
void fill(void) {
	for(int i = 0; i < 101; i++) {
			bino[i][i] = 1;
			bino[i][0] = 1;
	}
	for(int i = 0; i < n; i++) {
		for(int j = 0; j < m; j++) {
			bino[i][j] = bino[i-1][j-1] + bino[i - 1][j];
		}	
	}
}

string morse(int a_n, int a_m, int skip) {
	if(a_n == 0) return string(a_m. "o");
	
	if(skip<bino[a_n + a_m - 1][a_n - 1]) {
		return "-" + morse(a_n - 1, a_m, skip);
	}
	else {
		skip -= bino[a_n + a_m - 1][a_n - 1];
		return "o" + morse(a_n, a_m - 1, skip);
	
	}
}

int main(void) {
	cin>>tc;
	while(tc--) {
		cin>>n>>m>>k;
		fill();
		
	}
	
}

