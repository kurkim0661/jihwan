#include <iostream>

#include <string>

#include <map>

#include <algorithm>

#include <vector>

#include <cstring> //memset

using namespace std;

 

int friendNum, foodNum;

//canEat[i]: i번 친구가 먹을 수 있는 음식의 집합

//eaters[i]= i번 음식을 먹을 수 있는 친구들의 번호

vector<int> canEat[50], eaters[50];

//친구가 먹을만한 음식이 있는가

int edible[50];

int best;

 

//아직 먹을 음식이 없는 사람 중

//선택폭이 제일 적은 사람

int minimum(void)

{

        int idx = friendNum, curCnt = 50;

        for(int i=0; i<friendNum; i++)

               if (edible[i]<=0)

               {

                       int cnt = canEat[i].size();

                       if (curCnt > cnt)

                       {

                              curCnt = cnt;

                              idx = i;

                       }

               }

        return idx;

}

 

//음식을 선택할 때, 선택폭이 제일 적은 사람부터 시도

void efficientSearch(int chosen)

{

        if (chosen >= best) //최적해가 아닐 경우

               return;

       

        int idx = minimum(); //선택폭이 제일 적은 친구 찾음

 

        if (idx < friendNum) //찾았다면

        {

               for (int i = 0; i < canEat[idx].size(); i++)

               {

                       int food = canEat[idx][i];

                       //idx번째 친구가 먹을 수 있는 음식을 선택

                       for (int j = 0; j < eaters[food].size(); j++)

                              edible[eaters[food][j]]++;

                       efficientSearch(chosen + 1);

                       //선택을 해제

                       for (int j = 0; j < eaters[food].size(); j++)

                              edible[eaters[food][j]]--;

               }

        }

        else //모든 사람이 먹을 수 있는 음식이 마련되었다면

               best = chosen;         

}

 

//배열 초기화

void clear(void)

{

        for (int j = 0; j < foodNum; j++)

               eaters[j].clear();

        for (int j = 0; j < friendNum; j++)

               canEat[j].clear();

}

 

int main(void)

{

        int test_case;

        cin >> test_case;

        if (test_case < 1 || test_case>50)

               exit(-1);

 

        for (int i = 0; i < test_case; i++)

        {

               cin >> friendNum >> foodNum;

               if (friendNum < 1 || friendNum>50 || foodNum < 1 || foodNum>50)

                       exit(-1);

 

               map<string, int> index; //canEat과 eaters 벡터에 추가할 때 필요

               for (int j = 0; j < friendNum; j++)

               {

                       string name;

                       cin >> name;

                       index[name] = j; //해당이름을 가진 사람은 j번째 인덱스이다

               }

 

               for (int j = 0; j < foodNum; j++)

               {

                       int people;

                       cin >> people;

                       for (int k = 0; k < people; k++)

                       {

                              string name;

                              cin >> name;

                              //j번 음식을 먹을 수 있는 사람들

                              eaters[j].push_back(index[name]);

                              //현재 이 사람이 먹을 수 있는 음식 목록에 j번 음식 추가

                              canEat[index[name]].push_back(j);

                       }

               }

               memset(edible, 0, sizeof(edible));

               best = foodNum; //처음에는 모든 음식을 만들어야한다고 가정

               efficientSearch(0);

               cout << best << endl;

               clear();

        }

        return 0;

}
