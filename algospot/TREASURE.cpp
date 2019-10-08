#include <iostream>
#include <vector>
#include <iomanip>
#include <cassert>
#include <cmath>
using namespace std;
 
const double EPSILON = 1e-9;
const double INFTY = 1e200;
const double PI = 2.0*acos(0.0);
//2차원 벡터를 표현한다
 
struct vector2
{
        double x, y;
        //생성자를 explicit으로 지정하면 vector2를 넣을 곳에 잘못해
        //실수가 들어가는 일을 방지
        explicit vector2(double x_ = 0, double y_ = 0) :x(x_), y(y_)
        {
        }
        //두 벡터의 비교
        bool operator==(const vector2 &rhs) const
        {
               return x == rhs.x&&y == rhs.y;
        }
        bool operator<(const vector2 &rhs) const
        {
               return x != rhs.x ? x < rhs.x : y < rhs.y;
        }
        //벡터의 덧셈과 뺄셈
        vector2 operator+(const vector2 &rhs) const
        {
               return vector2(x + rhs.x, y + rhs.y);
        }
        vector2 operator-(const vector2 &rhs) const
        {
               return vector2(x - rhs.x, y - rhs.y);
        }
        //실수로 곱셈
        vector2 operator*(double rhs) const
        {
               return vector2(x*rhs, y*rhs);
        }
        //벡터의 길이를 반환
        double norm() const
        {
               return hypot(x, y);
        }
        //방향이 같은 단위 벡터를 반환
        //영벡터에 대해 호출한 경우 반환 값은 정의되지 않는다
        vector2 normalize() const
        {
               return vector2(x / norm(), y / norm());
        }
        //x축의 양의 방ㅎ향으로부터 이 벡터까지 반시계 방향으로 잰 각도
        double polar() const
        {
               return fmod(atan2(y, x) + 2 * PI, 2 * PI);
        }
        //내적/외적의 구현
        double dot(const vector2 &rhs) const
        {
               return x * rhs.x + y * rhs.y;
        }
        double cross(const vector2 &rhs) const
        {
               return x * rhs.y - rhs.x*y;
        }
        //이 벡터를 rhs에 사영한 결과
        vector2 project(const vector2 &rhs) const
        {
               vector2 r = rhs.normalize();
               return r * r.dot(*this);
        }
};
 
double howMuchCloser(vector2 p, vector2 a, vector2 b) //a가 b보다 얼마나 가까운가
{
        return (b - p).norm() - (a - p).norm();
}
 
//두 벡터의 방향성을 판단하는 ccw() 함수 구현
//원점에서 벡터 b가 벡터 a의 반시계 방향이면 양수, 시계 방향이면 음수
//평행이면 0을 반환
double ccw(vector2 a, vector2 b)
{
        return a.cross(b);
}
 
//점 p를 기준으로 벡터 b가 벡터 a의 반시계 방향이면 양수, 시계 방향이면 음수
//평행이면 0을 반환
double ccw(vector2 p, vector2 a, vector2 b)
{
        return ccw(a - p, b - p);
}
 
//두 직선의 교차점을 계산하는 liineIntersection() 함수의 구현
//(a, b)를 포함하는 선과 (c, d)를 포함하는 선의 교점을 x에 반환
//두 선이 평행이면 (겹치는 경우를 포함) 거짓을, 아니면 참을 반환
bool lineIntersection(vector2 a, vector2 b, vector2 c, vector2 d, vector2 &x)
{
        double det = (b - a).cross(d - c);
        //두 선이 평행인 경우
        if (fabs(det) < EPSILON)
               return false;
        x = a + (b - a)*((c - a).cross(d - c) / det);
        return true;
}
 
//(a, b)와 (c, d)가 평행한 두 선분일 때 이들이 한점에서 겹치는지 확인
bool parallelSegments(vector2 a, vector2 b, vector2 c, vector2 d, vector2 &p)
{
        if (b < a)
               swap(a, b);
        if (d < c)
               swap(c, d);
        //한 직선 위에 없거나 두 선분이 겹치지 않는 경우를 우선 걸러낸다
        if (ccw(a, b, c) != 0 || b < c || d < a)
               return false;
        //두 선분은 확실히 겹친다. 교차점을 하나 찾자
        if (a < c)
               p = c;
        else
               p = a;
        return true;
}
 
//p가 (a, b)를 감싸면서 각 변이 x, y축에 평행한 최소 사각형 내부에 있는지 확인
//a, b, p는 일직선 상에 있다고 가정
bool inBoundingRectangle(vector2 p, vector2 a, vector2 b)
{
        if (b < a)
               swap(a, b);
        return p == a || p == b || (a < p &&p < b);
}
 
//(a, b) 선분과 (c, d) 선분의 교점을 p에 반환
//교점이 여러개일 경우 아무 점이나 반환
//두 선분이 교차하지 않을 경우 false 반환
bool segmentIntersection(vector2 a, vector2 b, vector2 c, vector2 d, vector2 &p)
{
        //두 직선이 평행인 경우를 우선 예외 처리
        if (!lineIntersection(a, b, c, d, p))
               return parallelSegments(a, b, c, d, p);
        //p가 두 선분에 포함되어 있는 경우에만 참을 반환
        return inBoundingRectangle(p, a, b) && inBoundingRectangle(p, c, d);
}
 
//두 선분의 교차 여부를 좀 더 간단하게 확인
bool segmentIntersects(vector2 a, vector2 b, vector2 c, vector2 d)
{
        double ab = ccw(a, b, c)*ccw(a, b, d);
        double cd = ccw(c, d, a)*ccw(c, d, b);
        //두 선분이 한 직선 위에 있거나 끝점이 겹치는 경우
        if (ab == 0 && cd == 0)
        {
               if (b < a)
                       swap(a, b);
               if (d < c)
                       swap(c, d);
               return !(b < c || d < a);
        }
        return ab <= 0 && cd <= 0;
}
 
//점과 선 사이의 거리를 계산하는 함수 pointToLine()의 구현
//점 p에서 (a, b) 직선에 내린 수선의 발을 구한다
vector2 perpendicularFoot(vector2 p, vector2 a, vector2 b)
{
        return a + (p - a).project(b - a);
}
 
//점 p와 (a, b) 직선 사이의 거리를 구한다
double pointToLine(vector2 p, vector2 a, vector2 b)
{
        return (p - perpendicularFoot(p, a, b)).norm();
}
 
//단순 다각형의 넓이를 구하는 area() 함수
//주어진 단순 다각형 p의 넓이를 구한다
//p는 각 꼭지점의 위치 벡터의 집합으로 주어진다
double area(const vector<vector2> &p)
{
        double result = 0;
        for (int i = 0; i < p.size(); i++)
        {
               int j = (i + 1) % p.size();
               result += p[i].x*p[j].y - p[j].x*p[i].y;
        }
        return fabs(result) / 2.0; //오목 다각형 고려하여 절대값
}
 
//주어진 점이 단순 다각형 내부에 포함되어 있는지 확인하는 isInside() 함수
//점 q가 다각형 p 안에 포함되어 있을 경우 참, 아닌 경우 거짓 반환
//q가 다각형의 경계 위에 있는 경우의 반환값은 정의되어 있지 않다
bool isInside(vector2 q, const vector<vector2> &p)
{
        int crosses = 0;
        for (int i = 0; i < p.size(); i++)
        {
               int j = (i + 1) % p.size();
               //(p[i], p[j])가 반직선을 세로로 가로지르는가?
               if ((p[i].y > q.y) != (p[j].y > q.y))
               {
                       //가로지르는 x 좌표를 계산
                       double atX = (p[j].x - p[i].x)*(q.y - p[i].y) / (p[j].y - p[i].y) + p[i].x;
                       if (q.x < atX) //q보다 오른쪽에 있는가
                              crosses++;
               }
        }
        //내부에 있는 점이라면 오른쪽으로 반직선을 그릴 경우 다각형과 홀수번 겹침
        //외부라면 짝수번 겹침
        return crosses % 2 > 0;
}
//여기까지 vector2.h
 
//여기서부터 TREASURE.cpp
typedef vector<vector2> polygon;
 
//반평면과 단순 다각형의 교집합 구함
//(a,b)를 포함하는 직선으로 다각형 p를 자른 뒤, (a, b)의 왼쪽에 있는 부분들을 반환
polygon cutPoly(const polygon &p, const vector2 &a, const vector2 &b)
{
        int N = p.size();
        //각 점이 반평면 내에 있는지 여부를 우선 확인
        vector<bool> inside(N);
        for (int i = 0; i < N; i++)
               inside[i] = ccw(a, b, p[i]) >= 0;
        polygon result;
        //다각형의 각 변을 순회하면서 결과 다각형의 각 점을 발견
        for (int i = 0; i < N; i++)
        {
               int j = (i + 1) % N;
               //반평면 내에 있는 점 p[i]는 항상 결과 다각형에 포함
               if (inside[i])
                       result.push_back(p[i]);
               //변 p[i]-p[j]가 직선과 교차하면 교차점을 결과 다각형에 포함시킴
               if (inside[i] != inside[j])
               {
                       vector2 cross;
                       assert(lineIntersection(p[i], p[j], a, b, cross));;
                       result.push_back(cross);
               }
        }
        return result;
}
 
//서덜랜드-호지맨(Sutherland-Hodgman) 알고리즘을 이용한 다각형 클리핑
polygon intersection(const polygon &p, double x1, double y1, double x2, double y2)
{
        vector2 a(x1, y1), b(x2, y1), c(x2, y2), d(x1, y2); //시계 반대방향 순서
        polygon result = cutPoly(p, a, b);
        result = cutPoly(result, b, c);
        result = cutPoly(result, c, d);
        result = cutPoly(result, d, a);
        return result;
}
 
int main(void)
{
        int test_case;
        cin >> test_case;
        if (test_case > 50 || test_case < 1)
               exit(-1);
 
        cout << fixed << setprecision(10);
        for (int i = 0; i < test_case; i++)
        {
               int x1, y1, x2, y2, vertexNum;
               cin >> x1 >> y1 >> x2 >> y2 >> vertexNum;
               if (x1 < 0 || x2 < 0 || x1>100 || x2>100)
                       exit(-1);
              
               polygon Island(vertexNum);
               for (int j = 0; j < vertexNum; j++)
                       cin >> Island[j].x >> Island[j].y;
 
               cout << area(intersection(Island, x1, y1, x2, y2)) << endl;
        }
        return 0;
}

