#include <iostream>
#include <vector>
#include <string>
#include <algoritm>
using namespace std;
 
//3^9=19682(모든 판이 x인 경우)
int cache[19683]; //cache[]는 -2로 초기화한다
 
//turn이 한 줄을 만들었는지 반환
bool isFinished(const vector<string> &board, char turn)
{
        //가로
        for (int i = 0; i < 3; i++)
        {
               for (int j = 0; j < 3; j++)
               {
                       if (board[i][j] != turn)
                              break;
                       if (j == 2)
                              return true;
               }
        }
        //세로
        for (int i = 0; i < 3; i++)
        {
               for (int j = 0; j < 3; j++)
               {
                       if (board[j][i] != turn)
                              break;
                       if (j == 2)
                              return true;
               }
        }
        //대가선 ↘
        for (int i = 0; i < 3; i++)
        {
               if (board[i][i] != turn)
                       break;
               if (i == 2)
                       return true;
        }
        //대각선 ↙
        for (int i = 0; i < 3; i++)
        {
               if (board[i][2 - i] != turn)
                       break;
               if (i == 2)
                       return true;
        }
        return false;
}
 
//틱택토 게임판이 주어질 때 [0, 19682]의 정수로 변환
int bijection(const vector<string> &board) //모든 경우의 수를 계산
{
        int result = 0;
        for (int y = 0; y < 3; y++)
               for (int x = 0; x < 3; x++)
               {
                       result *= 3;
                       if (board[y][x] == 'o')
                              result++;
                       else if (board[y][x] == 'x')
                              result += 2;
               }
        return result;
}
 
//내가 이길 수 있으면 1을, 비길 수 있으면 0을, 지면 -1을 리턴
int canWin(vector<string> &board, char turn)
{
        //기저 사례: 마지막에 상대가 둬서 한 줄이 만들어진 경우
        if (isFinished(board, 'o' + 'x' - turn))
               return -1;
        int &result = cache[bijection(board)];
        if (result != -2)
               return result;
        //모든 반환 값의 min을 취하자
        int minValue = 2;
        for(int y=0; y<3; y++)
               for (int x = 0; x < 3; x++)
                       if (board[y][x] == '.')
                       {
                              board[y][x] = turn;
                              minValue = min(minValue, canWin(board, 'o' + 'x' - turn));
                              board[y][x] = '.';
                       }
        //플레이할 수 없거나 어떻게 해도 비기는 것이 최선인 경우
        if (minValue == 2)
               return result = 0;
        //최선인 상대가 이기는 거라면 난 무조건 지고, 상대가 지는 거라면 난 이긴다
        return result = -minValue;
}
 
int main(void)
{
        int test_case;
        cin >> test_case;
       
        vector<string> board;
        for (int j = 0; j < 19683; j++)
               cache[j] = -2; //캐시 초기화(-2로는 memset X)
 
        for (int i = 0; i < test_case; i++)
        {
               board.clear();
               int placed = 0; //다음 순서 계산을 위해
               for (int j = 0; j < 3; j++)
               {
                       string cell;
                       cin >> cell;
                       for (int k = 0; k < 3; k++)
                              if (cell[k] != '.')
                                      placed++;
                       board.push_back(cell);
               }
 
               char start = 'x';
               if (placed % 2 == 1) //x부터 시작하므로
                       start = 'o';
 
               switch (canWin(board, start))
               {
               case -1:
                       cout << (char)('x' + 'o' - start) << endl;
                       break;
               case 0:
                       cout << "TIE" << endl;
                       break;
               case 1:
                       cout << start << endl;
                       break;
               }
        }
        return 0;
}
