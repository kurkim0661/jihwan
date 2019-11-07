#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <functional>
using namespace std;
 
const int MOD = 20090711;
 
//문제 조건을 만족하는 난수 생성기
struct RNG
{
        int seed, a, b;
        RNG(int _a, int _b) :a(_a), b(_b), seed(1983)
        {
        }
        int next()
        {
                 int result = seed;
                 seed = ((seed*(long long)a) + b) % MOD;
                 return result;
        }
};
 
//힙을 이용해 변화하는 중간 값 문제를 해결하는 함수
int runningMedian(int n, RNG rng)
{
        priority_queue<int, vector<int>, less<int>> maxHeap;
        priority_queue<int, vector<int>, greater<int>> minHeap;
        int result = 0;
 
        //반복문 불변식
        //1. maxHeap의 크기는 minHeap의 크기와 같거나 1보다 크다
        //2. maxHeap.top() <= minHeap.top()
        for (int cnt = 1; cnt <= n; cnt++)
        {
                 //우선 1번 불변식부터 만족시킨다
                 if (maxHeap.size() == minHeap.size())
                         maxHeap.push(rng.next());
                 else
                         minHeap.push(rng.next());
                 //2번 불변식이 깨졌을 경우 복구하자
                 if (!minHeap.empty() && !maxHeap.empty() && minHeap.top() < maxHeap.top())
                 {
                         int a = maxHeap.top(), b = minHeap.top();
                         maxHeap.pop();
                         minHeap.pop();
                         maxHeap.push(b);
                         minHeap.push(a);
                 }
                 result = (result + maxHeap.top()) % MOD;
        }
        return result;
}
 
int main(void)
{
        int test_case;
        cin >> test_case;
 
        for (int i = 0; i < test_case; i++)
        {
                 int N, a, b;
                 cin >> N >> a >> b;
 
                 RNG generator(a, b);
 
                 cout << runningMedian(N, generator) << endl;
        }
        return 0;
}
