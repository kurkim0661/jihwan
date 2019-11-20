#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
 
int solve(vector<int> &fence, int left, int right)
{
        //기저 사례:판자가 하나밖에 없는 경우
        if (left == right)
               return fence[left];
        //[left, mid], [mid+1, right]의 두 구간으로 문제 분할
        int mid = (left + right) / 2;
        //분할한 문제를 각개격파
        int result = max(solve(fence, left, mid), solve(fence, mid + 1, right));
        //부분 문제 3:두 부분에 모두 걸치는 사각형 중 가장 큰 것
        int low = mid, high = mid + 1;
        int height = min(fence[low], fence[high]);
        //[mid, mid+1]만 포함하는 너비 2인 사각형 고려
        result = max(result, height * 2);
        //사각형이 입력 전체를 덮을 때까지 확장
        while (left < low || high < right)
        {
               //항상 높이가 더 높은쪽으로 확장
               if (high < right && (low == left || fence[low - 1] < fence[high + 1]))
               {
                       high++;
                       height = min(height, fence[high]);
               }
               else
               {
                       low--;
                       height = min(height, fence[low]);
               }
               //확장 후 사각형의 넓이
               result = max(result, height*(high - low + 1));
        }
        return result;
}
 
int main(void)
{
        int test_case, num;
        cin >> test_case;
        if (test_case < 0 || test_case > 50)
               exit(-1);
        for (int i = 0; i < test_case; i++)
        {
               cin >> num;
               vector<int> fence(num, 0);
               for (int j = 0; j < num; j++)
               {
                       cin >> fence[j];
                       if (fence[j] < 0 || fence[j]>20000)
                              exit(-1);
               }
               cout << solve(fence, 0, fence.size() - 1) << endl;
        }
        return 0;
}
