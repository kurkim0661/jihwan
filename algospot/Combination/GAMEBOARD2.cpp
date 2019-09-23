#include <iostream>

#include <string>

#include <vector>
#include <algorithm>
using namespace std;

//게임판 정보

int boardH, boardW; //board Height(세로), board Width(가로)

vector<string> board;

//블록의 크기

int blockSize;

//게임판의 각 칸이 덮였는지를 나타낸다

//1이면 #이거나 이미 덮은 칸, 0이면 .

int covered[10][10];

//블록의 회전된 형태를 계산하고 상대 좌표의 목록으로 저장

vector<vector<pair<int, int>>> rotations; //이차원 벡터

 

//2차원 배열 arr을 시계방향으로 90도 돌린 결과 반환

vector<string> rotate(const vector<string> &arr)

{

        vector<string> result(arr[0].size(), string(arr.size(), ' ')); //가로와 세로가 뒤바뀐 vector 생성
        for (int i = 0; i < arr.size(); i++)
               for (int j = 0; j < arr[0].size(); j++)
               result[j][arr.size() - i - 1] = arr[i][j]; //90도 회전
        return result;
}

//block의 네가지 회전 형태를 만들고 이들을 상대 좌표의 목록으로 변환
void generateRotations(vector<string> block)
{
        rotations.clear();
        rotations.resize(4); //네가지 회전
        for (int rot = 0; rot < 4; rot++)
        {
               int originY = -1, originX = -1;
               for (int i = 0; i < block.size(); i++)
                       for (int j = 0; j < block[i].size(); j++)
                              if (block[i][j] == '#')
                              {
                                      if (originY == -1)
                                      {
                                              //가장 윗줄 맨 왼쪽에 있는 칸이 '원점'이 된다
                                              originY = i;

                                              originX = j;
                                      }
                                      //각 칸의 위치를 원점으로부터의 상대좌표로 표현
                                      rotations[rot].push_back(make_pair(i - originY, j - originX));
	                          }
               //블록을 시계 방향으로 90도 회전

               block = rotate(block);

        }
        //네가지 회전 형태 중 중복이 있을 경우 이를 제거
        sort(rotations.begin(), rotations.end());
        rotations.erase(unique(rotations.begin(), rotations.end()), rotations.end());
        //블록이 몇 칸 짜리인지 저장
        blockSize = rotations[0].size();
}

 

//(y, x)를 왼쪽 위칸으로 해서 주어진 블록을 delta=1이면 놓고, -1이면 없앤다

//블록을 놓을 때 이미 놓인 블록이나 #과 겹치면 거짓을, 아니면 참을 반환

bool set(int y, int x, const vector<pair<int, int>> &block, int delta)

{
        //placed:지금까지 놓은 블록의 수
        bool result = true;
        for (int i = 0; i < block.size(); i++)
        {
               //범위 내에 있다면
               if (y + block[i].first >= 0 && y + block[i].first < boardH && x + block[i].second >= 0 && x + block[i].second < boardW)
               {
                       covered[y + block[i].first][x + block[i].second] += delta;
                       result = result && (covered[y + block[i].first][x + block[i].second] == 1);
               }
               else
                       result = false;
        }
        return result;
}

 

int best; //지금까지 찾은 최적해

 

//놓을 수 있는 블록의 수는 단순히 남은 빈 칸의 수를 블록의 크기로 나눈 것

//거기에 이미 놓은 수를 더했을 때 기존 최적해보다 작을 경우 최적해

int blockPrune(int placed) //가지치기

{

        int cnt = 0;

        for (int i = 0; i < boardH; i++)

               for (int j = 0; j < boardW; j++)

                       cnt += !(covered[i][j]) ? 1 : 0;

        return ((cnt / blockSize) + placed <= best);

}

 

void search(int placed) //placed:지금까지 놓은 블록의 수

{
        if (blockPrune(placed)) //가지치기
               return;
        //아직 채우지 못한 빈 칸 중 가장 윗줄 왼쪽에 있는 칸을 찾는다
        int y = -1, x = -1;
        for (int i = 0; i < boardH; i++)
        {
               for (int j = 0; j < boardW; j++)
               {
                       if (covered[i][j] == 0)
                       {
                              y = i;
                              x = j;
                              break;
                       }
               }
               if (y != -1)
                       break;
        }
        //기저 사례:게임판의 모든 칸을 처리한 경우
        if (y == -1)
        {
               best = max(best, placed);
               return;
        }
        //이 칸을 덮는다
        for (int i = 0; i < rotations.size(); i++)
        {
               if (set(y, x, rotations[i], 1))
                       search(placed + 1);
               //다시 없앤다
               set(y, x, rotations[i], -1);
        }
        //이 칸을 덮지 않고 막아둔다
        covered[y][x] = 1;
        search(placed);
        covered[y][x] = 0;

}

 

int solve(void)

{
        best = 0;
        //covered 배열 초기화
        for (int i = 0; i < boardH; i++)
               for (int j = 0; j < boardW; j++)
                       covered[i][j] = (board[i][j] == '#' ? 1 : 0);
        search(0);
        return best;
}

 

int main(void)

{
        int test_case;
        cin >> test_case;
        if (test_case < 1 || test_case>100)
               exit(-1);

        for (int i = 0; i < test_case; i++)
        {
               board.clear();
               vector<string> block;
               int blockH, blockW; //블록의 세로, 가로 크기
               cin >> boardH >> boardW >> blockH >> blockW;
               if (boardH < 1 || boardH>10 || boardW < 1 || boardW>10 || blockH < 1 || blockH>10 || blockW < 1 || blockW>10)
                       exit(-1);
              //보드판 입력
               for (int j = 0; j < boardH; j++)
               {
                       string temp;
                       cin >> temp;
                       board.push_back(temp);
               }
               //블록 입력
               for (int j = 0; j < blockH; j++)
               {
                       string temp;
                       cin >> temp;
                       if (temp.size() > blockW)
                              exit(-1);
                       block.push_back(temp);
               }

               generateRotations(block);
               cout << solve() << endl;

        }

        return 0;

}
