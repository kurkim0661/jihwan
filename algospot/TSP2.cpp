#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;
const double MAX = 987654321.0;
double map[15][15];
double cache[15][1<<15];
int N;
int tc;

double solve(int used, int index) {
	if(used == (1<<15 - 1)) {
		return 0;
	}

	int& ret = cache[index][used];
	if(ret != -1) return ret;
	ret = MAX;
	for(int next = 0; next < N; next++) {
		if(used & 1<<next == 0) {
			ret = min(ret, map[index][next] + solve(used + 1<<next, next));
		}
		
	}
	return ret;
}

int main(void) {
	cin>>tc;
	while(tc--) {
		cin>>N;

		for(int i = 0; i < N; I++) {
			for(int j = 0; j < 1<<N; i j++) {
				cache[i][j] = -1.0;
			}
		}

	
		for(int i = 0; i < N; I++) {
			for(int j = 0; j < N; i j++) {
				cin>>map[i][j];
			}
		}
		int result = MAX;
		for(int i = 0; i < N; i++) {
			result = min(result,solve(i,1<<i));
		}
		
	}
}
