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

#include <iostream>

#include <vector>

#include <algorithm>

using namespace std;

 

const int MAX = numeric_limits<int>::max();

 

//배열의 구간 최소 쿼리를 해결하기 위한 구간 트리의 구현

struct RMQ

{

        //배열의 길이

        int n;

        //각 구간의 최소치

        vector<int> rangeMin;

        RMQ(const vector<int> &array)

        {

                 n = array.size();

                 rangeMin.resize(n * 4);

                 init(array, 0, n - 1, 1);

        }

        //node 노드가 array[left...right] 배열을 표현할 때

        //node를 루트로 하는 서브트리를 초기화하고, 이 구간의 최소치를 반환한다

        int init(const vector<int> &array, int left, int right, int node)

        {

                 if (left == right)

                         return rangeMin[node] = array[left];

                 int mid = (left + right) / 2;

                 int leftMin = init(array, left, mid, node * 2);

                 int rightMin = init(array, mid + 1, right, node * 2 + 1);

                 return rangeMin[node] = min(leftMin, rightMin);

        }

        //node가 표현하는 범위 array[nodeLeft..nodeRight]가 주어질 때

        //이 범위와 array[left..right]의 교집합의 최소치를 구한다

        int query(int left, int right, int node, int nodeLeft, int nodeRight)

        {

                 //두 구간이 겹치지 않으면 아주 큰 값을 반환한다: 무시 됨

                 if (right < nodeLeft || nodeRight < left)

                         return MAX;

                 //node가 표현하는 범위가 array[left..right]에 완전히 포함되는 경우

                 if (left <= nodeLeft && nodeRight <= right)

                         return rangeMin[node];

                 //양쪽 구간을 나눠서 푼 뒤 결과를 합친다

                 int mid = (nodeLeft + nodeRight) / 2;

                 return min(query(left, right, node * 2, nodeLeft, mid), query(left, right, node * 2 + 1, mid + 1, nodeRight));

        }

        //query()를 외부에서 호출하기 위한 인터페이스

        int query(int left, int right)

        {

                 return query(left, right, 1, 0, n - 1);

        }

        //array[index]=newValue로 바뀌었을 떄 node를 루트로 하는

        //구간 트리를 갱신하고 노드가 표현하는 구간의 최소치를 반환한다

        int update(int index, int newValue, int node, int nodeLeft, int nodeRight)

        {

                 //index가 노드가 표현하는 구간과 상관없는 경우엔 무시한다

                 if (index < nodeLeft || nodeRight < index)

                         return rangeMin[node];

                 //트리의 리프까지 내려온 경우

                 if (nodeLeft == nodeRight)

                         return rangeMin[node] = newValue;

                 int mid = (nodeLeft + nodeRight) / 2;

                 return rangeMin[node] = min(update(index, newValue, node * 2, nodeLeft, mid), update(index, newValue, node * 2 + 1, mid + 1, nodeRight));

        }

        //update()를 외부에서 호출하기 위한 인터페이스

        int update(int index, int newValue)

        {

                 return update(index, newValue, 1, 0, n - 1);

        }

};

 

int main(void)

{

        int test_case;

        cin >> test_case;

 

        for (int i = 0; i < test_case; i++)

        {

                 int N, Q; //표지판의 수와 개방을 고려하고 있는 표지판의 수

                 cin >> N >> Q;

 

                 vector<int> height;

                 //최소치 구하는 RMQ 클래스 재활용하여 최대치 구함

                 vector<int> minusHeight;

 

                 for (int j = 0; j < N; j++)

                 {

                         int h;

                         cin >> h;

                         height.push_back(h);

                         minusHeight.push_back(-h); //음수로 넣으면

                 }

 

                 RMQ rmq(height);

                 RMQ minusRmq(minusHeight);

 

                 for (int i = 0; i < Q; i++)

                 {

                         int start, finish;

                         cin >> start >> finish;

 

                         int low = rmq.query(start, finish);

                         //최대치를 구할 수 있다

                         int high = abs(minusRmq.query(start, finish));

                        

                         cout << high - low << endl;

                 }

        }

        return 0;

}
