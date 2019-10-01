#include <iostream>
#include <algorithm>
#include <cstring> //memset
using namespace std;
 
const int MAX = 12; //majorNum<=12
const int INF = 987654321;
 
int majorNum, required; //전공 수, 전공필수
int semesterNum, semesterMax; //학기 수, 한 학기 최대
 
//prerequiiste[i] = i번째 과목의 선수과목의 집합
int prerequisite[MAX];
//classes[i] = i번째 학기에 개설되는 과목의 집합
int classes[10];
int cache[10][1 << MAX];
 
//N의 이진수 표현에서 켜진 비트의 수 반환
int bitCount(int N)
{
        if (N == 0)
               return 0;
        return N % 2 + bitCount(N / 2);
}
 
//이번 학기가 semester이고, 지금까지 들은 과목의 집합이 taken일 때
//required 이상의 과목을 모두 들으려면 몇 학기나 더 있어야 하는가?
//불가능한 경우 INF 반환
int graduate(int semester, int taken)
{
        //기저 사례: required개 이상의 과목을 이미 들은 경우
        if (bitCount(taken) >= required)

               retun 0;
        //기저 사례: semesterNum 학기가 전부 지난 경우
        if (semester == semesterNum)
               return INF;
       
        int &result = cache[semester][taken];
        if (result != -1)
               return result;
 
        result = INF;
        //이번 학기에 들을 수 있는 과목 중 아직 듣지 않은 과목들을 찾는다
        int canTake = (classes[semester] & ~taken);
        //선수 과목을 다 듣지 않은 과목들을 걸러낸다
        for (int i = 0; i < majorNum; i++)
               if ((canTake & (1 << i)) && (taken & prerequisite[i]) != prerequisite[i])
                       canTake &= ~(1 << i);
        //이 집합의 모든 부분집합 순회
        for (int take = canTake; take > 0; take = ((take - 1) & canTake))
        {
               //한 학기에 semesterMax까지만 들을 수 있다
               if (bitCount(take) > semesterMax)
                       continue;
               result = min(result, graduate(semester + 1, taken | take) + 1); //최소학기수 비교
        }
        //이번 학기에 아무 것도 듣지 않을 경우
        result = min(result, graduate(semester + 1, taken));
        return result;
}
 
int main(void)
{
        int test_case;
        cin >> test_case;
        if (test_case < 1 || test_case>50)
               exit(-1);
 
        for (int j = 0; j < test_case; j++)
        {
               memset(prerequisite, 0, sizeof(prerequisite));
               memset(classes, 0, sizeof(classes));
               memset(cache, -1, sizeof(cache));
               cin >> majorNum >> required >> semesterNum >> semesterMax;
              
               for (int j = 0; j < majorNum; j++)
               {
                       int preNum; //선수 과목 수
                       cin >> preNum;
 
                       for (int k = 0; k < preNum; k++)
                       {
                              int subject; //과목 입력
                              cin >> subject;
                              prerequisite[j] |= (1 << subject);
                       }
               }
 
               for (int j = 0; j < semesterNum; j++)
               {
                       int classNum; //학기에 열린 강의 갯수
                       cin >> classNum;
                      
                       for (int k = 0; k < classNum; k++)
                       {
                              int subject; //과목 입력
                              cin >> subject;
                              classes[j] |= (1 << subject);
                       }
               }
 
               int result = graduate(0, 0);
               if (result == INF)
                       cout << "IMPOSSIBLE" << endl;
               else
                       cout << result << endl;
        }
        return 0;
}
