#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <cstring>
using namespace std;
int TC;

int m; // 2<= m <= 20
int cache[2][1<<14][20];
string e;
string digits;
const int MOD = 100000000007;

int solve(int idx, int mod, int less, int used) {
	if(index == N) {
		return (less && mod ==0) ? 1:0;
	}

	int& ret = cache[less][used][mod];
	if(ret != -1) return ret;
	ret = 0;
	for(int next = 0; next < e.size(); next++) {
		if((used & (1<<next)) == 0) {
			if(!less && e[idx] < digits[next]) {
				continue;
			}
		if(next > 0 && digits[next - 1] == digits[next] && (taken & (1<<next - 1) == 0)) {
			continue;
		}		
		int nextless = (less || e[idx] > digits[next]);
		int nextMod = (mod*10 + e[next] - '0')%m;
		int nextUsed = used | 1<<next;
		ret += solve(next, nextMod, nextless, nextUsed);
		ret %= MOD;
		
		}
	}
	return ret;
}



int main(void)
{
        int test_case;
        cin >> test_case;
        if (test_case < 0 || test_case>50)
               exit(-1);
 
        for (int i = 0; i < test_case; i++)
        {
               N = 0;
               vector<long long> candidate;
               memset(cache, -1, sizeof(cache));
               cin >> egg >> M;
               long long num = atoll(egg.c_str());
               candidate.clear();
               while (num > 0)
               {
                       candidate.push_back(num % 10);
                       num /= 10;
                       N++;
               }
               sort(candidate.begin(), candidate.end());
               for (int j = 0; j < N; j++)
                       digits += candidate[j]+'0';
               cout << price(0, 0, 0, 0) << endl;
        }
        return 0;
}

