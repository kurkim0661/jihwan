#include <iostream>
#include <vector>
#include <algorithm>
#include <math>

using namespace std;

int TC;
int N;
int prepare[10001];
int eat[10001];
int pre_time;
int eat_time;
vector<pair<int, int> > p_e;

bool cmp(pair<int, int> a, pair<int, int> b) {
	return a.second > b.second;
}
int main(void) {
	cin>>TC;
	while(TC--) {
		cin>>N;
		for(int i = 0 ; i < N; i++) {
			cin>>prepare[i];
		}
		for(int i = 0 ; i < N; i++) {
			cin>>eat[i];
			p_e [i]= make_pair(prepare[i], eat[i]);
		}

		sort(p_e.begin(), p_e.end(), cmp);
		pre_time = p_e[0].first;
		eat_time = p_e[0].second;
		for(int i = 1; i < N; i++) {
			pre_time += p_e[i].first;
			eat_time = eat_time - p_e[i].first;
			if(eat_time < 0) {
				eat_time = 0;
			}
			if(eat_time < p_e[i].second) {
				eat_time = p_e[i].second;
			}
		}
		cout<<pre_time + eat_time<<endl;
	}
}
