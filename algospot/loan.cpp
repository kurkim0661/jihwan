#include <iostream>
#include <algorithm> 
#include <cstdio>
using namespace std;
/* run this program using the console pauser or add your own getch, system("pause") or input loop */
int TC;
double N;
int M; 
double P;

bool calculate(double n, int m, double c) {
	if(m < 0) {
		if(n<=0) {
			return true;	
		}
		else {
			return false;	
		}
	}
	if(n <= 0) {
		return true;	
	}	
	n = n*(1 + P/1200) - c; 
	return calculate(n, m - 1, c);
	
}

double solve(void) {
	double left = 1;
	double right = N*(1+P/1200);
	double mid = (left + right)/2;
	double ret = 0;
	for(int i = 0 ; i < 100; i++) {
		mid = (left + right)/2;
		if(calculate(N, M, mid)) {
			right = mid;
		}
		else {
			left = mid;	
		}
		ret = left;
	}
	printf("%.10lf\n", mid);
	return ret;
		
}
int main(int argc, char** argv) {
	
	cin>>TC;
	while(TC--) {
		cin>>N>>M>>P;
		solve();
	}
	return 0;
}
