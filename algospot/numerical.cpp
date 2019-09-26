#include <iostream>
#include <algorithm>
#include <vector>
#include <iomanip>
#include <cmath>
using namespace std;
 
//방정식의 해의 절대 값은 L 이하여야만 한다
const double L = 10;
 
int N; //차수
 
//단일 변수 다항식 p의 계수가 주어질 때 미분한 결과 p`의 계수를 반환
vector<double> differentiate(const vector<double> &poly)
{
        int n = poly.size() - 1;
        vector<double> result;
        //미분
        for (int i = 0; i < n; i++)
                result.push_back((n - i)*poly[i]);
        return result;
}
//1차 혹은 2차 방정식을 푼다
vector<double> solveNaive(const vector<double> &poly)
{
        int n = poly.size() - 1;
        vector<double> result;
        switch (n)
        {
        case 1:
               result.push_back(-poly[1] / poly[0]);
               break;
        case 2:
               double a = poly[0], b = poly[1], c = poly[2];
               //근의 공식
               result.push_back((-b + sqrt(pow(b, 2) - 4 * a*c)) / (2 * a));
               result.push_back((-b - sqrt(pow(b, 2) - 4 * a*c)) / (2 * a));
               break;
        }
        sort(result.begin(), result.end());
        return result;
}
//다항식 f(x)의 계수 poly가 주어질 때 f(x0)를 반환
double evaluate(const vector<double> &poly, double x0)
{
        int n = poly.size() - 1;
        double result = 0;
        //대입
        for (int i = 0; i <= n; i++)
               result += pow(x0, n - i)*poly[i];
        return result;
}
 
//방정식 sum(poly[i]*x^i)=0의 근을 반환
vector<double> solve(const vector<double> &poly)
{
        int n = poly.size() - 1;
        //기저 사례: 2차 이하의 방정식들은 풀 수 있다
        if (n <= 2)
               return solveNaive(poly);
        //방정식을 미분해서 n-1차 방정식을 얻는다
        vector<double> derivative = differentiate(poly);
        vector<double> sols = solve(derivative);
        //이 극점들 사이를 하나하나 검사하며 근이 있나 확인한다
        //초기 극점과 마지막 극점은 비교대상이 없으므로 ±L과 비교
        sols.insert(sols.begin(), -L - 1);
        sols.insert(sols.end(), L + 1);
        vector<double> result;
 
        for (int i = 0; i + 1 < sols.size(); i++)
        {
               //인접하는 극점
               double x1 = sols[i], x2 = sols[i + 1];
               double y1 = evaluate(poly, x1), y2 = evaluate(poly, x2);
               //f(x1)과 f(x2)의 부호가 같은 경우 답은 없다
               if (y1*y2 > 0)
                       continue;
               //불변 조건:f(x1) <= 0 < f(x2)
               if (y1 > y2)
               {
                       swap(y1, y2);
                       swap(x1, x2);
               }
               //이분법을 사용하자
               for (int iter = 0; iter < 100; iter++)
               {
                       double midX = (x1 + x2) / 2;
                       //y는 x를 대입하여 계산
                       double midY = evaluate(poly, midX);
                       if (y1*midY > 0)
                       {
                              y1 = midY;
                              x1 = midX;
                       }
                       else
                       {
                              y2 = midY;
                              x2 = midX;
                       }
               }
               result.push_back((x1 + x2) / 2);
        }
        sort(result.begin(), result.end());
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
               vector<double> poly;
               cin >> N;
               if (N < 2 || N>5)
                       exit(-1);
               for (int i = 0; i <= N; i++)
               {
                       double coef; //계수 입력 받는다
                       cin >> coef;
                       poly.push_back(coef);
               }
               vector<double> result = solve(poly);
               cout << fixed << setprecision(12);
               for (int i = 0; i < result.size(); i++)
                       cout << result[i] << " ";
               cout << endl;
        }
        return 0;
}

