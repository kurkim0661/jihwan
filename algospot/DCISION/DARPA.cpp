#include <iostream>

#include <vector>

#include <algorithm>

#include <iomanip>

using namespace std;

 

int cameraNum, installNum; //카메라 갯수와 설치 가능 갯수

 

//결정 문제: 정렬되어 있는 locations 중 cameras를 선택해 모든 카메라 간의 간격이

//gap 이상이 되는 방법이 있는지 반환

bool decision(const vector<double> &location, int cameras, double gap)

{

        //카메라를 설치할 수 있을 때마다 설치하는 탐욕적 알고리즘

        double limit = -1;

        int installed = 0;

        for (int i = 0; i < location.size(); i++)

        {

               if (limit <= location[i])

               {

                       ++installed;

                       //location[i]+gap 이후는 되어야 카메라 설치 가능

                       limit = location[i] + gap;

               }

        }

        //결과적으로 cameras대 이상을 설치할 수 있었으면 성공

        return installed >= cameras;

}

 

//최적화 문제: 정렬되어 있는 locations 중 cameras를 선택해 최소 간격을 최대화

double optimize(const vector<double> &location, int cameras)

{

        double low = 0, high = 241;

        //반복문 불변식:decision(low) && !decision(high)

        for (int i = 0; i < 100; i++)

        {

               double mid = (low + high) / 2.0;

               //간격이 mid 이상이 되도록 할 수 있으면 답은 [mid, hi]에 있다

               if (decision(location, cameras, mid))

                       low = mid;

               else

                       high = mid;

        }

        return low;

}

 

int main(void)

{

        int test_case;

        cin >> test_case;

        if (test_case < 1 || test_case>50)

               exit(-1);

 

        for (int i = 0; i < test_case; i++)

        {

               vector<double> location;

               cin >> cameraNum >> installNum;

 

               for (int j = 0; j < installNum; j++)

               {

                       double coord;

                       cin >> coord;

                       location.push_back(coord);

               }

               sort(location.begin(), location.end());

               cout << fixed << setprecision(2);

               cout << optimize(location, cameraNum) << endl;

        }

        return 0;

}


/////////////////////////
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int TC;
int N;
int M;
double pos[201]; //중계소의 위치.

double ret;
int main (void) {
	cin>>TC;
	while(TC--) {
		cin>>N>>M;
		for(int i = 0; i < N; i++) {
			cin>>pos[i];
		}
		double low = 0; double high = 241;
		while(low <= high) {
			int cnt = 1;
			double mid = (low + high)/2;
			double temp = 0;
			for(int i = 1 ; i < M; i++) {
				temp += pos[i] - pos[i - 1];
				if(temp >= mid) {
					cnt++;
					base = 0;
				}
			}
				
			if(cnt >= N) {
				ret = low;
				low = mid + 1;
			}
			else {
				high = mid - 1;
			}
			
		}
		cout.precision(2);
		cout<<ret<<endl;
	}
}
