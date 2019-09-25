#include <iostream>

#include <algorithm>

using namespace std;

 

const int MAX = 5000;

const int drive = 8030000; //총 주행 거리

 

int N, K; //도시의 수, K번째 표지판

//도시까지의 거리, markStart미터 전부터 표지판 시작, interval미터마다 표지판

int length[MAX], markStart[MAX], interval[MAX];

 

//결정문제:dist지점까지 가면서 K개 이상의 표지판을 만날 수 있는가?

bool decision(int distance)

{

        int result = 0;

        //i번째 도시 표지판을 하나 이상보게 되는가?

        //[length[i]-markStart[i], length[i]] 구간 내에 있으면 표지판과 겹침

        //length[i]-markStart[i]=length[i]라 하더라도 표지판은 하나 겹치므로 끝에 +1

        for (int i = 0; i < N; i++)

               if (distance >= length[i] - markStart[i])

                       result += (min(distance, length[i]) - (length[i] - markStart[i])) / interval[i] + 1;

        return result >= K;

}

 

//K번째 표지판을 만나는 지점의 위치를 계산

int optimize(void)

{

        //반복문 불변식: !decision(low) && decision(high)

        int low = -1, high = drive + 1;

        while(low + 1 < high)

        {

               int mid = (low + high) / 2;

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

               if (N<1 || N>MAX)

                       exit(-1);

 

               for (int j = 0; j < N; j++)

                       cin >> length[j] >> markStart[j] >> interval[j];

 

               cout << optimize() << endl;

        }

        return 0;

}
