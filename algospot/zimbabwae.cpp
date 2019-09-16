#include <iostream>
#include <cstring>
#include <string>
#include <algorithm> 
/* run this program using the console pauser or add your own getch, system("pause") or input loop */
using namespace std;

const int MAX = 1000000007;
int tc;
int n;
string e;
string digit;
int m;
int cache[2][20][1<<14];

int solve(int mod, int less, int index, int taken) {
	if(index == n) {
		return (less && mod == 0) ? 1:0;	
	}
	int& ret = cache[less][mod][taken];
	if(ret  != -1) {
		return ret;	
	}
	ret = 0;
	for(int next = 0; next<n; next++) {
		if(taken & 1<<next == 0) {
			if(!less && e[index] < digit[next])	{
				continue;
			}
			if(next>0 && digit[next-1] == digit[next]
				&& (taken & (1<<(next-1))) == 0) {
				continue;	
			}
			int nexttaken = taken | (1<<next); 
			int nextmod = (mod * 10 + digit[next] - '0') % m;
			int nextless = less || e[index] > digit[next];
			ret += solve(nextmod, nextless, index + 1, nexttaken);
			ret %= MAX;
		}
	}
	return ret;
}

int main(int argc, char** argv) {
	cin>>tc;
	
	while(tc--) {
		cin>>e>>m;
		n = e.size();
		e=digit;
		sort(digit.begin(),digit.end());			
	}
	return 0;
}
