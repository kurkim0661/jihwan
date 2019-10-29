언뜻 보기에는 트리 문제로 보이지 않지만, 성벽끼리의 접촉이 없다는 조건에 주목하면 성이 계층적 구조로 구성되어 있음을 알 수 있습니다.

이 문제에서 핵심은 트리 내에서 가장 긴 경로를 찾는 것이였습니다.



트리 내에서 가장 긴 경로는 다음과 두 가지 경로 중 최대인 경로입니다.

1. 가장 긴 root ~ leaf 경로의 길이

2. 가장 긴 leaf ~ leaf 경로의 길이



소스코드에서

 //root를 최상위 노드로 하는 경로를 고려하자

        if (heights.size() >= 2)

                 longest = max(longest, 2 + heights[heights.size() - 2] + heights[heights.size() - 1]);

 이 부분이 처음에는 잘 이해가 안 갔었는데 고심 끝에 아래와 같이 이해했습니다.



root의 자식들이 root인 서브트리의 높이를 오름차순으로 정렬했으므로,

제일 높은 서브트리 높이 

+ 두 번째로 높은 서브트리 높이 

+ root -> 제일 높은 서브트리의 root(1)

+ root -> 두 번째로 높은 서브트리의 root(1) 



#include <iostream>

#include <algorithm>

#include <vector>

using namespace std;

 

const int MAX = 100;

 

struct TreeNode

{

        vector<TreeNode *> children;

};

 

int N, y[MAX], x[MAX], radius[MAX];

//지금까지 찾은 가장 긴 leaf~leaf 경로의 길이를 저장

int longest;

 

//root를 루트로 하는 서브트리의 높이를 반환

int height(TreeNode *root)

{

        //각 자식을 루트로 하는 서브트리의 높이를 계산한다

        vector<int> heights;

        for (int i = 0; i < root->children.size(); i++)

                 heights.push_back(height(root->children[i]));

        //만약 자식이 하나도 없다면 0을 반환한다

        if (heights.empty())

                 return 0;

 

        sort(heights.begin(), heights.end());

        //root를 최상위 노드로 하는 경로를 고려하자

        if (heights.size() >= 2)

                 longest = max(longest, 2 + heights[heights.size() - 2] + heights[heights.size() - 1]);

        //트리의 높이는 서브트리 높이의 최대치에 1을 더해 계산

        return heights.back() + 1;

}

 

//두 노드 사이의 가장 긴 경로의 길이를 계산

int solve(TreeNode *root)

{

        longest = 0;

        //트리의 높이와 최대 leaf~leaf 경로 길이 중 큰 것을 선택

        int h = height(root);

        return max(longest, h);

}

 

int sqr(int x) //x * x 반환

{

        return x * x;

}

 

//두 성벽 a, b의 중심점 간의 거리의 제곱 반환

int sqrdist(int a, int b)

{

        return sqr(y[a] - y[b]) + sqr(x[a] - x[b]);

}

 

//성벽 a가 성벽 b를 포함하는지 확인

bool encloses(int a, int b)

{

        return radius[a] > radius[b] && sqrdist(a, b) < sqr(radius[a] - radius[b]);

}

 

//성벽 트리에서 parent가 child의 부모인지 확인

//parent는 child를 꼭 직접 포함해야 한다

bool isChild(int parent, int child)

{

        if (!encloses(parent, child))

                 return false;

 

        for (int i = 0; i < N; i++)

                 if (i != parent && i != child && encloses(parent, i) && encloses(i, child))

                         return false;

        return true;

}

 

//root 성벽을 루트로 하는 트리를 생성

TreeNode *getTree(int root)

{

        TreeNode *result = new TreeNode();

        for (int ch = 0; ch < N; ch++)

                 //ch 성벽이 root 성벽에 직접적으로 포함되어 있다면

                 //트리를 만들고 자손 목록에 추가한다

                 if (isChild(root, ch))

                         result->children.push_back(getTree(ch));

        return result;

}

 

int main(void)

{

        int test_case;

        cin >> test_case;

 

        for (int i = 0; i < test_case; i++)

        {

                 cin >> N;

                 for (int i = 0; i < N; i++)

                         cin >> x[i] >> y[i] >> radius[i];

 

                 TreeNode *T = getTree(0);

                 cout << solve(T) << endl;

        }

        return 0;

}
