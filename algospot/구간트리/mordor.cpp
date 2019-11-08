#include <iostream>
#include <vector>
using namespace;


const int MAX = numeric_limits<int>::max();
struct RMQ{
	int n;
	vector<int> minvalue;

	RMQ(vector<int> &arr,int left, int right) {
		init(arr, 0, n-1);
	}

	int init(vector<int> &arr, int left, int right, int node = 1) {
		if(left == right) {
			minvalue[node] = arr[left];
			return arr[left];
		}
		int mid = (left + right)/2;
		int lmin = init(arr, left, mid, node * 2);
		int rmin = init(arr, mid + 1, right, node * 2 + 1);
		minvalue[node] = min(lmin, rmin);
		return minvalue[node];
	}

	int query(int left, int right,int node, int leftnode, int rightnode) {
		int mid = (left + right )/2;
		if(left > leftnode || right < rightnode) {
			return MAX;
		}
		if(left <= leftnode && right >= rightnode) {
			return minvalue[node];
		}

		return min(query(left, right, node*2, leftnode, mid), query(left, right, node*2 + 1, mid + 1, rightnode))
	}	

	int query(int left, int right) {
		query(left, right, 1, 0, n - 1);
	}

	
};


int main(void) {

}
