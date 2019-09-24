#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>


using namespace std;
const int MAX = 20;

int TC;
int N;
int M;
int map[MAX + 1][MAX + 1];
int value[MAX + 1][MAX + 1];
int sum[MAX * MAX]; //힌트의 합.
int length[MAXX * MAX]; //힌트의 길이.
int known[MAX*MAX];
int hint[MAX + 1][MAX + 1][2]; //좌표에 따른 해당 위치의 힌트 의 번호.
int candidate[10][46][1024];
void put(int y, int x, int val) {
	
	for(int i = 0; i < 2; i++) {
		known[hint[y][x][i]] |= 1<<val;
	}
	value[y][x] = val;
	return ;
}

void remove(int y, int x, int val) {
	
	for(int i = 0; i < 2; i++) {
		known[hint[y][x][i]] -= 1<<val;
	}
	value[y][x] = 0;
	return ;
}

int getSize(int bit) {
	int length = 0;
	for(int i = 1; i <=9; i++) {
		if(1<<i & bit) {
			length++;
		}
	}
	return i;
}

int getSum(int bit) {
	int sum = 0;
	for(int i = 1; i <= 9; i++) {
		if(1<<i & bit) {
			sum+=i;
		}
	}
	return i;
}
void printSolution(void) {
        for (int i = 0; i < N; i++)
        {
               for (int j = 0; j < N; j++)
                       cout << value[i][j] << " ";
               cout << endl;
        }
}

int getCandHint(int hint) {
	return candidate[length[hint]][sum[hint]][known[hint]];
}

int getCandidate(int y,int x) {
	return getCandHint(hint[y][x][0]) & getCandHint(hint[y][x][1]);
}


void generateCandidate(void) {

	memset(candidate,0,sizeof(candidate));
	int len;
	int sum;
	for(int i = 0; i < 1024; i+=2) {
		len = getSize(i); sum = getSum(i);

		int subset = i;

		while(1) {
			candidate[len][sum][subset] |= (i & ~subset);

			if(subset == 0) {
				break;
			}
			subset = (subset - 1) & i;
		}

	}
}

bool serch(void) {
	int y = -1; int x = -1; int mincandidate = 1023;
	for(int i = 0; i < N; i++) {
		for(int j = 0; j < N; j++) {
			if(map != 0 && value == 0) {
				int candidate = getCandidate(i, j);
				if(mincandidate > candidate) {
					mincandidate = candidate;
					y = i;
					x = j;
				}
			}
		}
	}
	if(mincandidate == 0) {
		return false;
	}
	if(y == -1) {
		return true;
	}

	for(int i = 1; i <= 9; i++) {
		if(mincandidate & 1<<i) {
			put(y,x,i);
			if(serch()) {
				return true;
			}
			remove(y,x,i);
		}
	}
	return false;
	
}

int main(void) {
	cin>>TC;
	while(TC--) {
		
		cin>>N;
		for(int i = 1; i <= N; i++) {
			for(int j = 1; j <= N; j++) {
				cin>>map[i][j];
			}
		}
		cin>>M; //힌트의 갯수.
		for(int i = 0 ; i < M; i++) {
			int y;
			int x;
			int dir;
			int total;
			int movey;
			int movex;
			int nextx;
			int nexty;
			int a_len = 0;;
			cin>>y>>x>>dir>>total;
			
			
			
			if(dir) {
				movex = 0;
				movey = 1;
			
			}
			else {
				movex = 1;
				movey = 0;
			
			}
			
			nexty = y + movey;
			nextx = x + movex;
			while(map[nexty][nexty] != 0) {
				hint[nexty][nextx][dir[i]] = i; 
				nexty+=movey;
				nextx+=movex;
				a_len++;
			}
			length[i] = a_len;
			sum[i] = total;
		}

		
	}
}
