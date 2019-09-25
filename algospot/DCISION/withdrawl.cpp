
#include <iostream>

#include <vector>

#include <algorithm>

#include <iomanip>

using namespace std;

 

const int MAX = 1000;

 

int N, K; //수업 갯수, 장학금 타기 위한 최소 수업 갯수

int classmate[MAX], rating[MAX]; //수업 인원, 등수

 

//결정 문제: 누적 등수 average가 되도록할 수 있나?

bool decision(double average)

{

        //sum(classmate[i]/rating[i]) <= x

        //sum(classmate[i])/sum(rating[i]) <= x

        //sum(classmate[i]) <= x*sum(rating[i])

        //0 <= x*sum(rating[i])-sum(classmate[i])

        //0 <= sum(x*rating[i]-classmate[i])

        //v[i]=x*rating[i]-classmate[i] 계산

        vector<double> v;

        for (int i = 0; i < N; i++)

               v.push_back(average*classmate[i] - rating[i]);

        sort(v.begin(), v.end());

        //이 문제는 v 중 k개의 합이 0 이상이 될 수 있는지로 바뀐다(greedy method)

        double sum = 0;

        for (int i = N - K; i < N; i++)

               sum += v[i];

        return sum >= 0;

}

 

//최적화 문제: 얻을 수 있는 최소의 누적 등수 계산

double optimize(void)

{

        //누적 등수는 [0, 1] 범위의 실수

        //반복문 불변식: !decision(low) && decision(high)

        double low = -1e-9, high = 1;

        for (int iter = 0; iter < 100; iter++)

        {

               double mid = (low + high) / 2;

               //누적 등수 mid를 달성 가능?

               if (decision(mid))

                       high = mid;

               else

                       low = mid;

        }

        return high;

}

 

int main(void)

{

        int test_case;

        cin >> test_case;

        if (test_case < 1 || test_case>50)

               exit(-1);

       

        for (int i = 0; i < test_case; i++)

        {

               cin >> N >> K;

               if (N<1 || N>MAX || K<1 || K>N)

                       exit(-1);

 

               for (int i = 0; i < N; i++)

                       cin >> rating[i] >> classmate[i];

 

               cout << fixed << setprecision(10);

               cout << optimize() << endl;

        }

        return 0;

}
