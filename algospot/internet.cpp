#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>

using namespace std;
int TC;
int N;
int M;

vecotr<pair<int,int> > data[100];

bool cond(const pair<int,int>& a, const pair<int,int>& b) {
	return a.second>b.second;
}

int main(void) {
	cin>>TC;
	cin>>N>>M;
	int price;
	int point;
	while(TC--) {
		for(int i = 0; i < M; i++) {
			data[i].clear();
		}

		for(int i = 0; i < N; i++) {
			for(int j = 0; j < M; j++) {
				cin>>priche>>point;
				data[j].push_back(make_pair(price, point));
			}
		}
		for(int j = 0; j < M; j++) { 
			sort(data[j].begin(), data[j].end(), cond);
		}
		
		for(int i = 1; i < N; i++) {
			for(int j = 0; j < M; j++) {
				if(data[j][i - 1].second >= data[j][i].first) {
					data[j][i].second += data[j][i - 1].second - data[j][i].first;
					data[j][i].first = data[j][i - 1].first;
				}
				else {
					data[j][i].first += data[j][i - 1].frist - data[j][i - 1].second;
				}
			}
		}

		int minVal = data[0][N-1].first;

		for(int i = 1; i < M; i++) {
			minVal = min(minVal, data[i][N-1]);
		}

		cout<<minVal<<endl;
		
	}
	
	
}
