#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

queue<int> que;
int TC;
int N;
int K;
vector<int> ret(2,0);

vector<int> solve(void) {
	vector<int> result(2,0);
	for(int i = 2; i <= N; i++) {
		que.push(i);
	}
	int temp;
	int cnt = 0;
	while(que.size() != 2) {
		temp = que.front();
		cnt++;
		que.pop();
		if(cnt == K) {
			continue;
		}
		que.push(temp);
	}
	while(que.empty() != true) {
		temp = que.front();
		que.pop();
		result.push_back(temp);
	}
	return result;
}

int main(void) {
	cin>>TC;
	while(TC--) {
		cin>>N>>K;
		ret = solve();
	}
	for(int i = 0; i < 2; i++) {
		cout<<ret[i]<<" ";
	}
	cout<<endl;
}
