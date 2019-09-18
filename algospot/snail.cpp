#include <iostream>
#include <algorithm>
#include <math>
using namespace std;
int TC;
int N; // 1000
int M; // 1000
double cache[1001][2*1000];

double solve(int n, int days) {
	if(days == M) {
		(n>0) ? 0 : 1;
	}
	double& ret = cache[n][days];
	if(ret > -0.5) {
		return ret;
	}
	ret = 0.75*solve(n - 1, days + 1) + 0.25*solve(n - 2, days + 1);

	return ret;
}

int main(void) {
	cin>>TC;


	
	while(TC--){
		cin>>N>>M;
		for(int i = 0; i < 1000; i++) {
			for(int j = 0; j < 2*1000; j++) {
				cache[i][j] = -1.0;
			}
		}
		cout.precision(11);
		cout<<solve(N,0)<<endl;
		
	}
}
