#include <iostream>
#include <cmath>
#include <cstring> //memset
using namespace std;
 
const int MAX = 10000000; //천만
 
//minFactor[i] -> i의 가장 작은 소인수(i가 소수인 경우 자기 자신)
int minFactor[MAX + 1];
//minFactorPower[i] -> i의 소인수 분해에는 minfactor[i]의 몇 승이 포함되어있는가
int minFactorPower[MAX + 1];
//factors[i] -> i가 가진 약수의 수
int factors[MAX + 1];
 
void erastothenes(void)
{

       //1은 항상 예외 처리
        minFactor[0] = minFactor[1] = -1;
        //모든 숫자를 처음에는 소수로 표시
        for (int i = 2; i <= MAX; i++)
               minFactor[i] = i;
        //에라토스테네스의 체를 수행
        int sqrtN = int(sqrt(MAX)); //루트 N
        for (int i = 2; i <= sqrtN; i++)
               if (minFactor[i] == i)
                       for (int j = i*i; j <= MAX; j += i)
                              //아직 약수를 본적 없는 숫자인 경우 i를 써 둔다
                              if (minFactor[j] == j)
                                      minFactor[j] = i;
}
 
void getFactorsSmart(void)
{
        factors[1] = 1;
        for (int num = 2; num <= MAX; num++)
        {
               //소수인 경우 약수가 두개 뿐
               if (minFactor[num] == num)
               {
                       minFactorPower[num] = 1; //1승
                       factors[num] = 2; //약수 두개
               }
               //소수가 아닌 경우, 가장 작은 소인수로 나눈 수의
               //약수의 수를 응용해 num의 약수의 수를 찾는다
               else
               {
                       int prime = minFactor[num];
                       int divisor = num / prime;
                       //divisor가 prime으로 더이상 나누어지지 않는다면
                       if (prime != minFactor[divisor])
                              minFactorPower[num] = 1;
                       else
                              minFactorPower[num] = minFactorPower[divisor] + 1;
                       int exponent = minFactorPower[num];
                       factors[num] = (factors[divisor] / exponent)*(exponent + 1);
               }
        }
}
 
//완전탐색법
void getFactorsBruteForce(void)
{
        memset(factors, 0, sizeof(factors));
        for (int div = 1; div <= MAX; div++)
               for (int multiple = div; multiple <= MAX; multiple += div)
                       factors[multiple]++;
}
 
int main(void)
{
        int test_case;
        cin >> test_case;
        if (test_case < 1 || test_case>50)
               exit(-1);
 
        erastothenes();
        getFactorsSmart();
        //getFactorsBruteForce();
        for (int i = 0; i < test_case; i++)
        {
               int divisorNum, low, high;
               cin >> divisorNum >> low >> high; //약수 갯수, 범위
               if(divisorNum > 400 || low<1 || low>MAX || high<1 || high>MAX)
                       exit(-1);
 
               int result = 0;
               for (int j = low; j <= high; j++)
                       if (factors[j] == divisorNum)
                              result++;
               cout << result << endl;
        }
        return 0;
}

