#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
/* run this program using the console pauser or add your own getch, system("pause") or input loop */
using namespace std;

int tc;
int N;

void normalize(vector<int>& num);
void addTo(vector<int>& a,const vector<int>& b, int k);
void subFrom(vector<int>& a, const vector<int>& b);
vector<int> multiply(const vector<int>& a, const vector<int>& b);
vector<int> karatsuba(const vector<int>& a, const vector<int>& b);

void addTo(vector<int>& a,const vector<int>& b, int k) {
	int length = b.size();
	a.resize(max(a.size(),b.size() + k));
	
	for(int i = 0 ; i < length; i++ ) {
		a[i+k] += b[i];	
	}
	return ;
}

void subFrom(vector<int>& a, const vector<int>& b) {
	int length = b.size();
	a.resize(max(a.size(),b.size()) + 1);	
		
	for(int i = 0 ; i < length; i++) {
		a[i] -= b[i];
	}
	return ;
}

vector<int> multiply(const vector<int>& a, const vector<int>& b) {
	vector<int> c(a.size() + b.size() + 1, 0);
	for(int i = 0; i < a.size(); i++) {
		for(int j = 0; j < b.size(); j++) {
			c[i+j] += (a[i] * b[j]);	
		}
	}
	//normalize(c);
	
	return c;
}

void normalize(vector<int>& num) {
	num.push_back(0);
	for(int i = 0; i + 1 < num.size(); i++) {
		if(num[i] < 0) {
			int borrow = (abs(num[i]) + 9) / 10;
			num[i+1] -= borrow;
			num[i] += borrow * 10;	
		}
		else{
			num[i+1] += num[i] / 10 ;
			num[i] %= 10;	
		}
	}
}

vector<int> karatsuba(const vector<int>& a, const vector<int>& b) {
	int an = a.size(); int bn = b.size();
	if(an < bn) {
		return karatsuba(b,a);	
	}
	if(an == 0 || bn == 0) {
		return vector<int> ();	
	}
	if(an <= 50) {
		return multiply(a,b);	
	}
	int half = an/2;
	
	vector<int> a0(a.begin(), a.begin() + half);
	vector<int> a1(a.begin() + half, a.end());
	vector<int> b0(b.begin(), b.begin() + min<int>(b.size(),half));
	vector<int> b1(b.begin() + min<int>(b.size(),half),b.end());

	vector<int> z2 = karatsuba(a1,b1);
	vector<int> z0 = karatsuba(a0,b0);
	
	addTo(a0,a1,0);
	addTo(b0,b1,0);
	
	vector<int> z1 = karatsuba(a0,b0);
	
	
	subFrom(z1,z0);
	subFrom(z1,z2);
	

	vector<int> ret;
	addTo(ret, z0, 0);
	addTo(ret, z1, half);
	addTo(ret, z2, half+half);
	return ret;
}

int hugs(const string& members, const string& fans) {
	int N = members.size(); int M = fans.size();
	vector<int> A(N); vector<int> B(M);
	for(int i = 0; i < N; i++) {
		A[i] = (members[i] == 'M');	
	}
	for(int j = 0; j < M; j++) {
		B[M-j-1] = (fans[j] == 'M');	
	}
	vector<int> C = karatsuba(A,B);
	int allHugs = 0;
	for(int i = N-1; i < M; ++i) {
		if(C[i] == 0) {
			++allHugs;
		}
	}
	return allHugs;
}



int main(int argc, char** argv) {
	cin>>tc;
	
	while(tc--) {
		string member;
		string fan;

		cin>>member>>fan;		
		
		
		cout<<hugs(member,fan)<<endl;
		
	}
	return 0;
}
