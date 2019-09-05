#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std; 
/* run this program using the console pauser or add your own getch, system("pause") or input loop */
int tc;
int n; //마을 갯수. 
int d; //일수 
int p; //교도소가 있는 마을. 
int t; // 확률을 구하고싶은 마을의 수. 
int numofline[51] = {0,}; 
int tt[51]; 
int map[51][51];
double cache[51][101];

int detect(int here, int days) {
	if(days == 0) {
		return (here == p ? 1.0 : 0.0);
	}
	double & ret = cache[here][days];
	if(ret > -0.5) return ret;
	ret=0.0;
	for(int i = 0 ; i < n; i++) {
		if(map[i][here] == 1) {
			ret += detect(i,days - 1) / numofline[i];
		}
	}
	return ret;
}	

int main(int argc, char** argv) {
	cin>>tc;
    for (int j = 0; j < 50; j++)
        for (int k = 0; k < 100; k++)
            cache[j][k] = -1;
            
	while(tc--) {
		memset(map,0,sizeof(map));
		cin>>n>>d>>p;
		for(int i = 0 ; i < n; i++) {
			for(int j = 0 ; j < n; j++) {
				cin>>map[i][j];
				numofline[j] += map[i][j];
			}
		}
		cin>>t;
		for(int i = 0 ; i<t; i++) {
			cin>>tt[i];
		}
		for(int i = 0; i < t; i++) {
			cout<<detect(tt[i],d)<<" ";
		}
		cout<<endl;
	}
	return 0;
}

왜 안될까...?

	
	
#include <iostream>

#include <vector>

#include <cstring> //memset

using namespace std;

 

int villageNum, day, jail, searchNum; //마을의 수, 탈출 후 일 수, 교도소 있는 번호, 찾고 싶은 마을의 수

int village[50][50]; //최대 50개 마을

int adjacent[50]; //adjacent[i]는 마을 i와 인접한 마을의 수

double cache[50][100]; //최대 50개 마을, 최대 100일

/*

//완전 탐색 알고리즘

double search(vector<int> &path)

{

        //기저 사례:day일이 지난 경우

        if (path.size() == day + 1)

        {

               //이 시나리오가 searchNum에서 끝나지 않는다면 무효

               if (path.back() != searchNum)

                       return 0.0;

               //path의 출현 확률 계산

               double result = 1.0;

               for (int i = 0; i < path.size(); i++)

                       result /= adjacent[path[i]]; //인접한 마을의 갯수만큼 나눠준다

               return result;

        }

        double result = 0.0;

        //경로의 다음 위치를 결정한다

        for (int there = 0; there < villageNum; there++)

        {

               if (village[path.back()][there])//인접했다면 추가

               {

                       path.push_back(there);

                       result += search(path);

                       path.pop_back();

               }

               return result;

        }

}

*/

 

//동적 계획법

double search(int here, int days) //here 해당 마을, days: 지난 일 수

{

        //기저 사례

        if (days == 0)

               return (here == jail ? 1.0 : 0.0); //시작은 감옥

        //메모이제이션

        double &result = cache[here][days];

        if (result != -1.0)

               return result;

        result = 0.0;

        //거꾸로 확률을 계산한다. 즉 해당 마을부터 시작(정방향이라면 감옥부터 시작)

        for (int there = 0; there < villageNum; there++)

               if (village[here][there]) //there와 인접해있다면

                       result += search(there, days - 1) / adjacent[there]; //∑(1/adjacent(there) * search(there, days-1));

        return result;

}

 

int main(void)

{

        int test_case;

        cin >> test_case;

        if (test_case < 1 || test_case>50)

               exit(-1);

       

        for (int i = 0; i < test_case; i++)

        {

               cin >> villageNum >> day >> jail;

               if (villageNum < 2 || villageNum>50 || day < 1 || day>100 || jail < 0 || jail >= villageNum)

                       exit(-1);

               for (int j = 0; j < villageNum; j++)

                       for (int k = 0; k < villageNum; k++)

                              cin >> village[j][k];

               for (int j = 0; j < 50; j++)

                       for (int k = 0; k < 100; k++)

                              cache[j][k] = -1;

               memset(adjacent, 0, sizeof(adjacent));

               for (int j = 0; j < villageNum; j++)

                       for (int k = 0; k < villageNum; k++)

                              adjacent[j] += village[j][k]; //인접한 마을 갯수 초기화

 

               cin >> searchNum;

               if (searchNum > villageNum || searchNum < 1)

                       exit(-1);

               vector<int> v;

               for (int j = 0; j < searchNum; j++)

               {

                       int there;

                       cin >> there;

                       if (there<0 || there>villageNum-1)

                              exit(-1);

                       v.push_back(there);

               }

               for (int j = 0; j < searchNum; j++)

               {

                       cout.precision(8);

                       cout << search(v[j], day) << " ";

               }

               cout << endl << endl;

        }

        return 0;

}
