#include <iostream>
#include <queue>
#include <vector>
#include <cmath>
#include <iomanip>
using namespace std;
int N;
double dist[101][101];
double X[101], Y[101];
void precalc()
{
	for (int i = 0; i < N; ++i)
	{
		for (int j = 0; j < N; ++j)
		{
			if (i == j) continue;
			dist[i][j] = sqrt(pow((X[j] - X[i]), 2) + pow((Y[j] - Y[i]), 2));
		}
	}
}
bool decision(double d)
{
	vector<bool> visited(N, false);
	visited[0] = true;
	queue<int> q;
	q.push(0);
	int seen = 0;
	while (!q.empty())
	{
		int here = q.front();
		q.pop();
		++seen;
		for (int i = 0; i < N; ++i)
		{
			if (!visited[i] && dist[here][i] <= d)
			{
				visited[i] = true;
				q.push(i);
			}
		}
	}
	return seen == N;
}
// 모든 기지를 연결할 수 있는 최소의 d를 반환한다.
double optimize()
{
	double lo = 0, hi = 1416.00;
	for (int it = 0; it < 100; ++it)
	{
		double mid = (lo + hi) / 2;
// mid가 가능하다면, 더 좋은 (작은) 답을 찾는다.
		if (decision(mid))
			hi = mid;
// mid가 불가능하다면, 더 나쁜 (큰) 답을 찾는다.
		else
			lo = mid;
	}
	return hi;
}
int main()
{
	int C;
	cin >> C;
	while (C--)
	{
		cin >> N;
		for (int i = 0; i < N; ++i)
		{
		cin >> X[i] >> Y[i];
		}
		precalc();
		cout << showpoint << fixed << setprecision(2) << optimize() << "\n";
	}
	return 0;
}
