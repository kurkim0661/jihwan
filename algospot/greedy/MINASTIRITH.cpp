#include <iostream>
#include <vector>
#include <math>
#include <algorithm>
#include <cstring>

using namespace std;
const int INF = 987654321;
const double pi = 2 * acos(0);
int TC;
int N;
double y[101];
double x[101];
double r[101];
pair<int, int> ranges[101];
int convertToLinear(int begin, int end);


void convertToRange(void) {
	for(int i = 0; i < N; i++) {
		int loc = fmod(2*pi + atan2(y[i],x[i]),2*pi);
		int angle = 2 * asin(r[i] / 16);
		ranges[i] = make_pair(loc - angle, loc + angle);
	}
	return ;
}

int convertToCircle(void) {
	int cnt = INF; 
	int idx = 0;
	sort(ranges,ranges + N);
	for(int i = 0; i < N; i++) {
		if(ranges[i].first <= 0 || ranges[i].second >= 2*pi) {
			int begin = fmod(ranges[i].second, 2*pi);
			int end = fmod(ranges[i].first + 2 * pi, 2 * pi);
			cnt = min(cnt, convertToLinear(begin, end));
			
		}
	}
	return cnt;
}

int convertToLinear(int begin, int end) {
	int idx = 0;
	int cnt = 0;
	
	while(begin < end) {
		double cntMax = -1;
		while(idx < N && begin >= ranges[idx].first) {
			cntMAX = max(cntMax,range[idx].second);
			idx++;

		}
		if(cntMax <= begin) {
			return INF;
		}
		begin = cntMax;
		cnt++;
		
	}
}

int main(void) {
	cin>>TC;
	while(TC--) {
		cin>>N;
		for(int i = 0; i < N;  i++) {
			cin>>y[i]>>x[i]>>r[i];
		}
		convertToRange();
		IF(convertToCircle() != INF) {
			cout<<convertToCircle()<<endl;
		}
		else {
			cout<<IMPOSIBLE<<endl;
		}
		
	}
}
