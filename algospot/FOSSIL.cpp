#include <iostream>
#include <algorithm>
#include <vector>
#include <iomanip>
using namespace std;
 
typedef struct
{
        double y, x;
}Point;
 
//입력에 주어진 보록 다각형
vector<Point> polygon1, polygon2;
//위 껍질에 속하는 선분들과 아래 껍질에 속하는 선분들
vector<pair<Point, Point>> upper, lower;
 
//polygon이 반시계 방향으로 주어지므로, 인접한 두 점에 대해
//x가 증가하는 방향이면 아래쪽 껍질, x가 감소하는 방향이면 위쪽 껍질
void decompose(const vector<Point> &polygon)
{
        int n = polygon.size();
        for (int i = 0; i < n; i++)
        {
               //선분 추가(점과 점을 이으면 선분)
               if (polygon[i].x < polygon[(i + 1) % n].x)
                       lower.push_back(make_pair(polygon[i], polygon[(i + 1) % n]));
               else
                       upper.push_back(make_pair(polygon[i], polygon[(i + 1) % n]));
        }
}
 
//[a.x, b.x] 구간 안에 x가 포함되나 확인
bool between(const Point &a, const Point &b, double x)
{
        return (a.x <= x && x <= b.x) || (b.x <= x && x <= a.x);
}
 
//(a, b) 선분과 주어진 위치의 수직선이 교차하는 위치를 반환
double at(const Point &a, const Point &b, double x)
{
        double dY = b.y - a.y;
        double dX = b.x - a.x;
        return a.y + (x - a.x) * dY / dX;
}
 
//두 다각형의 교집합을 수직선으로 잘랐을 때 단면의 길이를 반환
double vertical(double x)
{
        double minUp = 1e20, maxLow = -1e20;
        //위 껍질의 선분을 순회하며 최소 y좌표를 찾는다
        for (int i = 0; i < upper.size(); i++)
               if (between(upper[i].first, upper[i].second, x))
                       minUp = min(minUp, at(upper[i].first, upper[i].second, x));
        //아래 껍질의 선분을 순회하며 최대 y 좌표를 찾는다
        for (int i = 0; i < lower.size(); i++)
               if (between(lower[i].first, lower[i].second, x))
                       maxLow = max(maxLow, at(lower[i].first, lower[i].second, x));
        return minUp - maxLow;
}
 
double minX(vector<Point> &p)
{
        double result = p[0].x;
        for (int i = 1; i < p.size(); i++)
               result = min(result, p[i].x);
        return result;
}
 
double maxX(vector<Point> &p)
{
        double result = p[0].x;
        for (int i = 1; i < p.size(); i++)
               result = max(result, p[i].x);
        return result;
}
 
double solve(void)
{
        //수직선이 두 다각형을 모두 만나는 x 좌표의 범위를 구한다
        double low = max(minX(polygon1), minX(polygon2));
        double high = min(maxX(polygon1), maxX(polygon2));
        //예외 처리: 두 다각형이 아예 겹치지 않는 경우
        if (high < low)
               return 0;
        //삼분 검색
        for (int iter = 0; iter < 100; iter++)
        {
               double a = (low * 2 + high) / 3.0; // 1/3
               double b = (low + 2 * high) / 3.0; // 2/3
               if (vertical(a) < vertical(b))
                       low = a;
               else
                       high = b;
        }
        return max(0.0, vertical(high));
}
 
int main(void)
{
        int test_case;
        cin >> test_case;
        if (test_case < 1 || test_case>50)
               exit(-1);
 
        for (int i = 0; i < test_case; i++)
        {
               int num1, num2; //두 볼록 다각형에 포함된 점의 수
               cin >> num1 >> num2;
               if (num1 < 1 || num1>100 || num2 < 1 || num2>100)
                       exit(-1);
 
               polygon1.clear();
               polygon2.clear();
               //첫번째 다각형 꼭지점
               for (int j = 0; j < num1; j++)
               {
                       Point temp;
                       cin >> temp.x >> temp.y;
                       polygon1.push_back(temp);
               }
               //두번째 다각형 꼭지점
               for (int j = 0; j < num2; j++)
               {
                       Point temp;
                       cin >> temp.x >> temp.y;
                       polygon2.push_back(temp);
               }
               lower.clear();
               upper.clear();
               //위 아래 껍질로 분류
               decompose(polygon1);
               decompose(polygon2);
               double result = solve();
               if (result <= 0)
                       cout << "0.000000" << endl;
               else
               {
                       cout << fixed << setprecision(10);
                       cout << result << endl;
               }
        }
        return 0;
}
