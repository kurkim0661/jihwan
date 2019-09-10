#include <algorithm>
#include <iostream>
#include <vector>
#include <cmath>

using naemspace std;

int tc;
int S[101];
int n;
int cachelen[101];
int cacheCnt[101];

int LISlen(int start) {
	if(start == n) return 0;
	int& ret = cachelen[start];
	if(ret != -1) return ret;
	ret = 1;
	for(int next = start + 1; next < n; ++next) {
			if(start == -1 || S[start] < S[next]) {
				ret = max(ret, LISlen(next) + 1);
		}
	}
	return ret;
}

int LIScount(int start) {
	if(start == n) return 0;
	int& ret = cacheCnt[start];
	if(ret != -1) return ret;
	ret = 0;
	for(int next = start + 1; next < n; ++next) {
			if((start == -1 ||S[start] < S[next]) 
			&&	LIS(start) == LIS(next) + 1 ) {
				ret = max(ret, LIScount(next) + 1);
		}
	}
	return ret;
}

int reconstruct(int start,int skip, vector<int>& lis) {
	if(start != -1) lis.push_back(S[start]);
	vector<pair<int, int> > followers;
	for(int next = start + 1; next < n; ++next) {
		if((start == -1 || S[start] < S[next])
			&&LISlen(start) == LISlen(next) + 1) {
			followers.push_back(make_pair(S[next],next));
			
		}
	}
	sort(followers.begin(), followers.end());
	for(int i = 0 ; i < followers.size(); i++){
		int idx = follower[i].second;
		int cnt = count(idx);
		if(cnt < skip) {
			skip -= cnt;
		}
		else {
			
			reconstruct(idx,skip,)
		}	
	}

}

int main(void) {
	cin>>tc;
	vector<int> lis2;
	while(tc--) {
		memset(cachelen,-1,sizeof(cachelen));
		memset(cacheCnt,-1,sizeof(cacheCnt));
		cin>>n>>k;
		for(int i = 0; i < n; i++) {
			cin>>S[i];
		}
		reconstruct(-1,k,lis2);
		for(int i = 0; i < lis2.size(); i++) {
			cout<<lis2[i]<<" ";		
		}
		cout<<endl;
	}	

}
