#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>
#define INF 987654321;
using namespace std;
/* run this program using the console pauser or add your own getch, system("pause") or input loop */
int sequence[101];
int cache[101][11];
//vector<int> sequence;
//vector<int> cache;
int qsum[101];
int qSqsum[101];
int n;
int tc;
int s;


int MinError(int lo, int hi) {
	
	int sum = qsum[hi] - (lo == 0 ? 0 : qsum[lo - 1]);
	int sqsum =  qSqsum[hi] - (lo == 0 ? 0 : qSqsum[lo - 1]);
	int m = int(0.5 + (double)sum/(hi-lo +1));
	int ret = sqsum - 2*m*sum + m*m*(hi-lo+1);
	return ret;
}
int quantize(int start,int idx) {
	//기저  1  길이가 다차면. 
	if(start == n) return 0;
	if(idx == 0) return INF;
	int& ret = cache[start][idx];
	if(ret != -1) return ret;
	ret = INF;
	
	for(int partsize = 1; start+partsize<=n; ++partsize) {
		ret = min(ret, MinError(start,start+partsize-1) + 
						quantize(start + partsize, idx -1));
	}
	return ret;
}

int main(int argc, char** argv) {
	cin>>tc;
	while(tc--) {
		cin>>n>>s;
		memset(cache,-1,sizeof(cache));
		for(int i = 0 ; i < n; i++) {
			cin>>sequence[i];
		}
		sort(sequence,sequence + n);
		qsum[0] = sequence[0];
		qSqsum[0] = sequence[0] * sequence[0];
		for(int i = 1; i < n ; i++) {
			qsum[i] = qsum[i-1] + sequence[i];
			qSqsum[i]  = qSqsum[i-1] + sequence[i] * sequence[i];
		}
		cout<<quantize(0,s)<<endl;
		memset(sequence,0,sizeof(sequence));
	}
	return 0;
}
