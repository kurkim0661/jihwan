#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
const int 987654321;
int TC;
int N;
int arr[101];
int temp;
priority_queue<int, vector<int>, greater<int>) pq;


int solve(void) {
	int ret = 0;
	while(pq.size() != 0) {
		int min1 = pq.top; pq.pop;
		int min2 = pq.top; pq.pop;
		int sum = min1 + min2;
		pq.insert(sum);
		ret += sum;
		
	}
	return ret;
}

int main(void) {
	cin>>TC;
	while(TC--) {
		cin>>N;
		for(int i = 0; i < N; i++) {
			cin>>temp;
			pq.insert(temp);
		}
		cout<<solve()<<endl;
	}
}
