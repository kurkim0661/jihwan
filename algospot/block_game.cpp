#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
int tc;
string arr[5];
int used;
int cache[1<<25];
vector<int> move;
inline int cell(int y, int x) {return 1<<(y*5 + x)};

void precalc(void) {
	vector<int> temp;
	for(int y = 0; y < 4; y++) {
		for(int x = 0; x < 4; x++) {
			for(int dy = 0; dy < 2;  dy++) {
				for(int dx = 0; dx < 2; dx++) {
					temp.push_back(cell(y+dy,x+dx));
				}
			}
			int sum = temp[0] + temp[1] + temp[2] + temp[3];
			for(int k = 0; k < 4; k++) {
				sum -= temp[i];
				move.push_back(sum);
			}
		}
	}

	for(int y = 0; y < 5; y++) {
		for(int x = 0; x <4; x++) {
			move.push_back(cell(y,x) | cell(y,x+1));
			move.push_back(cell(x,y) | cell(x+1,y));
		}
	}
}

char solve(int used) {
	if(used == (1<<25 - 1)) {
		return 0;
	}

	int& ret = cache[used];
	if(ret != -1) return ret;
	ret = 0;
	for(int next = 0; next < move.size(); next++) {
		if(used & move[next] == 0) {
			if(!solve(used | move[next])) {
				ret = 1;
				break;
			}
		}
	}
	return ret;
}

int main(Void) {
	cin>>tc;

	while(tc--) {
		for(int i = 0; i < 5; i++) {
			cin>>arr[i];
			for(int j = 0; j < 5; j++) {
				if(arr[i][j] == "#") {
					used |= cell(i,j);
				}
			}
		}
		
		
	}
}
