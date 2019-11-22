#include <iostream>
#include <algorithm>
using namespace std;
 
const int EMPTY = -987654321; //답의 범위가 -50000~50000
int board[50], boardSize; //boardSize 최대 50
int cache[50][50];
 
int play(int left, int right)
{
        //기저 사례: 모든 수가 다 없어졌을 때
        if (left > right)
               return 0;
        int &result = cache[left][right];
        if (result != EMPTY)
               return result;
        //첫번째 경우
        result = max(board[left] - play(left + 1, right), board[right] - play(left, right - 1));
        //두번째 경우
        if (right - left + 1 >= 2)
        {
               result = max(result, -play(left + 2, right)); //왼쪽 두개 지우는 경우
               result = max(result, -play(left, right - 2)); //오른쪽 두개 지우는 경우
        }
        return result;

}


void initialize(void) //cache 초기화
{
        for (int i = 0; i < 50; i++)
               for (int j = 0; j < 50; j++)
                       cache[i][j] = EMPTY;
}
 
int main(void)
{
       int test_case;
        cin >> test_case;
        if (test_case < 0 || test_case>50)
               exit(-1);
 
        for (int i = 0; i < test_case; i++)
        {
               initialize();
               cin >> boardSize;
               if (boardSize < 1 || boardSize>50)
                       exit(-1);
              
               for (int j = 0; j < boardSize; j++)
                       cin >> board[j];
 
               cout << play(0, boardSize-1) << endl;
        }
        return 0;
}
