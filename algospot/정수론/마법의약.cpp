#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int TC;
int N;
int need[201];
int aleady[201];

int gcd(int a, int b) {
	if(b==0) {
		return a;
	}
	return gcd(b,a%b);
}

int ceil(int a, int b) {
	return (a + b - 1) / b;
}

vector<int> solve(void) {
	vector<int> result;
	int b=need[0];
	for(int i = 1; i < N; i ++) {
		b = gcd(b, need[i]);
	}
	int a = b;

	for(int i = 0; i < N; i ++) {
		a = max(a, ceil(aleady[i] * b, need[i]));
		
	}
	for(int i = 0; i < N; i++) {
		result.push_back(need[i]*a/b - aleady[i]);
	}
	return result;
}


nt main(void)

{
        int test_case;
        cin >> test_case;
        if (test_case < 1 || test_case>50)
               exit(-1);
 
        for (int i = 0; i < test_case; i++)
        {
               int ingredientNum;
               vector<int> recipe, put;
               cin >> ingredientNum;
               if (ingredientNum < 1 || ingredientNum>200)
                       exit(-1);
 
               for (int j = 0; j < ingredientNum; j++)
               {
                       int temp;
                       cin >> temp;
                       recipe.push_back(temp);
               }
               for (int j = 0; j < ingredientNum; j++)
               {
                       int temp;
                       cin >> temp;
                       put.push_back(temp);
               }
               //vector<int> result = solveSimulation(recipe, put);
               vector<int> result = solve(recipe, put);
               for (int j = 0; j < result.size(); j++)
                       cout << result[j] << " ";
               cout << endl;
        }
        return 0;
}
