#include <iotream>
#include <map>
#include <vector>
#include <algorithm>
#include <cstring>
#include <string>
using namespace std;

int TC;
int N;
int M;
int num;
string name[51];
string temp;
vector<int> food[51];
vector<int> people[51];
map<string, int> peopleidx;

int edible[51];

void clear(void) {
	for(int i = 0; i < 51; i++) {
		food[i].clear();
		people[i].clear();
	}
	return ;
}

int minimum(void) {
	int idx = N;
	int cntMax = 50;
	for(int i = 0; i < N; i++) {
		if(edible[i] <= 0) {
			int cnt = people[i].size();
			if(cntMax > cnt) {
				cntMax = cnt;
				idx = i;
			}
		}
	}
	return idx;	
}

void serch(int cnt) {
	int idx = 0;
	if(cnt >= best) {
		return;
	}
	idx = minimum();
	if(idx < N) {
		for(int i = 0; i < people[idx].size(); i++) {
			for(int j = 0; food[people[idx][i].size(); j++) {
				edible[food[people[idx][i]][j]++;
			}
				serch(cnt + 1);				
			for(int j = 0; food[people[idx][i].size(); j++) {
				edible[food[people[idx][i]][j]--;			
			}

		}

	}
	else {
		best = cnt;
	}
	
}

int main(void) {
	cin>>TC;
	while(TC--) {
		cin>>N>>M;
		for(int i = 0; i < N; i++) {
			cin>>name[i];
			peopleidx[name[i]] = i;
		}
		for(int i = 0; i < M; i++) {
			cin>>num;
			for(int j = 0; j < num; j++) {
				cin>>temp;
				food[j].push_back(peopleidx[temp]);
				people[peopleidx[temp]].push_back(i);
			}
		}
		memset(edible, 0, sizeof(edible));
		best = M;
		serch(0);
		cout<<best<<endl;
		clear();
		
	}
}
