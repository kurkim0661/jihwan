#include <iostream>

#include <vector>

#include <algorithm>

#include <cstring> //memset

using namespace std;

 

const int MAX = 100000;

 

//D[]의 부분 합 배열 psum[]과 k가 주어질 때, 몇 가지 방법으로 살 수 있는지 반환

//psum[]의 첫 번째 원소 전에 0을 삽입했다고 가정

int waysToBuy(const vector<int> &psum, int K)

{

        const int MOD = 20091101;

        int result = 0;

        //psum[]의 각 값을 몇 번이나 본 적 있는지 기록

        vector<long long> count(K, 0);

        for (int i = 0; i < psum.size(); i++)

               count[psum[i]]++;

        //두 번 이상 본 적 있다면 이 값 중 두 개를 선택하는 방법의 수를 더한다

        //count[i]개 중 2개를 고를 경우의 수

        //nC2를 더한다 (n=count[i])

        for (int i = 0; i < K; i++)

               if (count[i] >= 2)

                       result = (result + ((count[i] * (count[i] - 1)) / 2)) % MOD;

        return result;

}

 

//D[]의 부분 합 배열 psum[]과 K가 주어질 때, 겹치지 않게 몇번이나 살 수 있는지 반환

//psum[]의 첫 번째 원소 전에 0을 삽입했다고 가정

int maxBuys(const vector<int> &psum, int K)

{

        //result[i]=첫 번째 상자부터 i번째 상자까지 고려했을 때 살 수 있는 최대 횟수

        vector<int> result(psum.size(), 0);

        //previous[s]=psum[]이 s였던 마지막 위치

        vector<int> previous(K, -1);

        for (int i = 0; i < psum.size(); i++)

        {

               //i번째 상자를 아예 고려하지 않는 경우

               if (i > 0)

                       result[i] = result[i - 1];

               else

                       result[i] = 0;

               //psum[i]를 전에도 본 적이 있다면, prev[psum[i]]+1부터 여기까지 쭉 구매

               int loc = previous[psum[i]];

               if (loc != -1)

                       //i번째 상자를 사지 않는 경우 vs 사는 경우

                       result[i] = max(result[i], result[loc] + 1);

               //previous[]에 현재 위치 기록

               previous[psum[i]] = i;

        }

        return result.back();

}

 

int main(void)

{

        int test_case;

        cin >> test_case;

        if (test_case < 1 || test_case>60)

               exit(-1);

 

        for (int i = 0; i < test_case; i++)

        {

               int N, K;

               cin >> N >> K;

               if (N<1 || N>MAX || K<1 || K>MAX)

                       exit(-1);

 

               vector<int> v(N);

               for (int i = 0; i < N; i++)

                       cin >> v[i];

 

               vector<int> psum(N + 1);

               psum[0] = 0;

               //어린이들에게 인형을 모두 나눠주려면 인형의 총 수가 K의 배수여야함

               //즉, K로 나눈 나머지가 중요함

               for (int i = 1; i <= N; i++)

                       psum[i] = (psum[i - 1] + v[i - 1]) % K;

 

               cout << waysToBuy(psum, K) << " " << maxBuys(psum, K) << endl;

        }

        return 0;

}
