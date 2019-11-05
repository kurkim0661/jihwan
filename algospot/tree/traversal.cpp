#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
using namespace std;
 
vector<int> slice(const vector<int> &v, int a, int b)
{
        return vector<int>(v.begin() + a, v.begin() + b);
}
 
//트리의 전위탐색 결과와 중위탐색 결과가 주어질 때 후위 탐색 결과를 출력한다
void printPostOrder(const vector<int> &preorder, const vector<int> &inorder)
{
        //트리에 포함된 노드의 수
        const int N = preorder.size();
        //기저 사례: 텅 빈 트리면 곧장 종료
        if (preorder.empty())
                 return;
        //이 트리의 루트는 전위 탐색 결과로부터 곧장 알 수 있다
        const int root = preorder[0];
        //이 트리의 왼쪽 서브트리의 크기는 중위 탐색 결과에서 루트의 위치를 찾아서 알 수 있다
        const int L = find(inorder.begin(), inorder.end(), root) - inorder.begin();
        //오른쪽 서브트리의 크기는 N에서 왼쪽 서브트리와 루트를 빼면 알 수 있다
        const int R = N - L - 1;
        //왼쪽 서브트리의 순회 결과를 출력
        printPostOrder(slice(preorder, 1, L + 1), slice(inorder, 0, L));
        //오른쪽 서브트리의 순회 결과를 출력
        printPostOrder(slice(preorder, L + 1, N), slice(inorder, L + 1, N));
        //후위 순회이므로 루트를 가장 마지막에 출력
        cout << root << " ";
}
 
int main(void)
{
        int test_case;
        cin >> test_case;
 
        for (int i = 0; i < test_case; i++)
        {
                 int N;
                 cin >> N;
 
                 vector<int> preorder, inorder;
 
                 for (int i = 0; i < N; i++)
                 {
                         int node;
                         cin >> node;
                         preorder.push_back(node);
                 }
                 for (int i = 0; i < N; i++)
                 {
                         int node;
                         cin >> node;
                         inorder.push_back(node);
                 }
 
                 printPostOrder(preorder, inorder);
                 cout << endl;
        }
        return 0;
}


#include <iostream>
#include <vector>
#include <algorithm>

int TC;
int N;

vector<int> slice(vector<int>& v, int a, int b) {
	return vector<int>(v.begin() + a, v.begin + b); 
}

vector<int> solve(vector<int>& pre, vector<int>& in) {
	const int n = pre.size();

	if(pre.empty()) {
		return;
	}
	int root = pre[0];
	int L_len = find(in.begin(), in.end(), root) - in.begin();
	int R_len = n - L_len - 1;

	solve(slice(pre, 1, L_len + 1), slice(in, 0, L));
	solve(slice(pre, L+len + 1 , n), slice(in, L + 1, n));
	cout<<root<<" ";
}
int main(void) {
	inc>>TC;
	while(TC--) {
		cin>>N;
		vector<int> preorder;
		vector<int> inorder;
		int temp;
		for(int i = 0; i < N; i++) {
			cin>>temp;
			preorder.push_back(temp);
		}
		for(int i = 0; i < N; i++) {
			cin>>temp;
			inorder.push_back(temp);
		}
		solve(preoder, inorder);
		cout<<endl;
	}
}
