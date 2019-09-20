#include <iostream?
#include <algorithm>
#include <vector>
#include <cstring>

using namespace std;

int TC;
int N;
int korean[101];
int rusian[101];
int cnt;

int solve(int kidx, int ridx) {
	if(kidx == N || ridx == N) {
		return 0;
	}
	
	if(korean[kidx] >= rusian[ridx]) {
		cnt++;
		solve(kidx + 1, ridx + 1);
		
	}
	else {
		solve(kidx + 1, ridx);
	}
	return 0;
}

int main (Void) {
	cin>>TC;
	while(TC--) {
		cin>>N;
		for(int i = 0; i < N; i++) {
			cin>>rusian[i];
		}
		for(int i = 0; i < N; i++) {
			cin>>korean[i];
		}
		sort(rusian, rusian + N);
		sort(korean, korean + N);

		for(int i = 0; i < N; i++) {
			if(korean[i] >= rusian[i]) cnt++;
			
		}
	}
	
}
