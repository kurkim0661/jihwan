#include <iostream>

#include <vector>

#include <algorithm>

#include <map>

#include <bitset>

using namespace std;

 

const double INF = 1e200;

const int MAX = 20;

//남은 도시의 수가 CACHED_DEPTH 이하면 동적계획법으로 전환

const int CACHED_DEPTH = 5;

 

//각 정점마다 다른 정점들을 가까운 순서대로 정렬

vector<int> nearest[MAX];

//모든 도시간의 도로를 길이 순으로 정렬해 저장

vector<pair<double, pair<int, int>>> edges;

//도시들간의 거리 저장

double dist[MAX][MAX];

//각 도시에 인접한 간선 중 가장 짧은 것을 미리 찾아 둔다

double minEdge[MAX];

int N; //마을의 수

double best; //지금까지 찾은 최적의 해

 

//MST 휴리스틱 구현 위해 필요

//상호 배타적 집합 자료 구조 구현

struct DisjointSet

{

        int villageNum, components; //마을 수, 독립적인 집합

        vector<int> parent, rank; //부모, 랭크(랭크가 높을수록 높은 부모)

        //n개의 원소로 구성된 집합 자료구조

        DisjointSet(int num) :villageNum(num), components(num), parent(num), rank(num)

        {

               for (int i = 0; i < villageNum; i++)

               {

                       parent[i] = i;

                       rank[i] = 0;

               }

        }

        //here가 포함된 집합의 대표를 반환

        int find(int here)

        {

               if (here == parent[here])

                       return here;

               return parent[here] = find(parent[here]);

        }

        //a가 포함된 집합과 b가 포함된 집합을 합친다

        bool merge(int a, int b)

        {

               a = find(a);

               b = find(b);

               if (a == b)

                       return false;

               if (rank[a] > rank[b])

                       swap(a, b);

               parent[a] = b;

               if (rank[a] == rank[b])

                       rank[b]++;

               components--;

               return true;

        }

};

 

//path의 마지막 4개의 정점 중 가운데 2개의 순서를 바꿨을 때 경로가 짧아지는지 판별

bool pathSwapPruning(const vector<int> &path)

{

        if (path.size() < 4)

               return false;

        int p = path[path.size() - 4]; //시작

        //사이에 있는 도시 a와 b

        int a = path[path.size() - 3];

        int b = path[path.size() - 2];

        int q = path[path.size() - 1]; //끝

 

        //p<->a + q<->b가 가까운지 p<->b + q<->a가 가까운지 판별

        return dist[p][a] + dist[b][q] > dist[p][b] + dist[a][q];

}

 

//시작 도시와 현재 도시를 제외한 path의 부분 경로를

//뒤집어 보고 더 짧아지는지 확인

bool pathReversePruning(const vector<int> &path)

{

        if (path.size() < 3)

               return false;

        int b = path[path.size() - 2];

        int q = path[path.size() - 1];

       

        for (int i = 0; i + 2 < path.size(); i++)

        {

               int p = path[i];

               int a = path[i + 1];

               //[.., p, a, ..., b, q] 를 [.., p, b, ..., a, q]로 바꿔본다

               if (dist[p][a] + dist[b][q] > dist[p][b] + dist[a][q])

                       return true;

        }

        return false;

}

 

//here와 시작점, 아직 방문하지 않은 도시들을 모두 연결하는 MST(스패닝트리)

double mstHeuristic(int here, const vector<bool> &visited)

{

        DisjointSet ds(N);

        double taken = 0;

       

        for (int i = 0; i < edges.size(); i++)

        {

               int a = edges[i].second.first;

               int b = edges[i].second.second;

               if (a != here && visited[a])

                       continue;

               if (b != here && visited[b])

                       continue;

               if (ds.merge(a, b)) //a와 b를 합칠 수 있다면

                       taken += edges[i].first;

        }

        return taken;

}

 

//dp(here, visited)=cache[here][남은 도시의 수][visited]

map<int, double> cache[MAX][CACHED_DEPTH + 1];

 

int countTrue(int bit) //비트로 visited가 표현되어있음

{

        if (bit == 0)

               return 0;

        return (bit % 2) + countTrue(bit/2);

}

 

//here: 현재 위치

//visited:각 도시의 방문 여부

//일 때, 나머지 도시를 모두 방문하고 시작점으로 돌아가는 최단 경로의 길이 반환

double dp(int here, int visited)

{

        //기저 사례: 더 방문할 도시가 없음

        if (visited == (1 << N) - 1)

               return 0.0;

 

        int remaining = N - countTrue(visited);

        double &result = cache[here][remaining][visited];

        if (result > 0)

               return result;

 

        result = INF;

        //다음 도시를 하나씩 시도

        for (int next = 0; next < N; next++)

        {

               //이미 방문했다면

               if (visited & (1 << next))

                       continue;

               result = min(result, dp(next, visited + (1 << next)) + dist[here][next]);

        }

        return result;

}

 

//path: 지금까지 만든 경로

//visited: 각 도시의 방문 여부

//currentLength: 지금까지 만든 경로의 길이

//나머지 도시들을 모두 방문하는 경로들을 만들어보고 최적해 갱신

void search(vector<int> &path, vector<bool> &visited, double currentLength)

{

        int here = path.back();

        //뒤집었을 때 더 짧다면

        if (pathReversePruning(path))

               return; //가지치기

        //현재의 최적해가 여태까지 연결했던 길이 + 스패닝트리 길이보다 짧다면

        if (best <= currentLength + mstHeuristic(here, visited))

               return; //가지치기

 

        //기저 사례:남은 도시 수가 CACHED_DEPTH 이하면 동적계획법으로 바꾼다

        if (path.size() + CACHED_DEPTH >= N)

        {

               int mask = 0; //비트 마스크

               for (int i = 0; i < N; i++)

                       if (visited[i])

                              mask += (1 << i); //방문한 곳 표시

               double candidate = currentLength + dp(here, mask);

               best = (best > candidate) ? candidate : best;

               return;

        }

       

        double result = INF;

 

        //다음 방문할 도시를 전부 시도

        for (int i = 0; i < nearest[here].size(); i++)

        {

               int next = nearest[here][i];

               if (visited[next])

                       continue;

 

               path.push_back(next);

               visited[next] = true;

               //나머지 경로를 재귀 호출을 통해 완성

               search(path, visited, currentLength + dist[here][next]);

               visited[next] = false;

               path.pop_back();

        }

}

 

double solve(void)

{

        //nearest 초기화

        for (int i = 0; i < N; i++)

        {

               vector<pair<double, int>> order;

               for (int j = 0; j < N; j++)

                       if (i != j)

                              order.push_back(make_pair(dist[i][j], j));

               sort(order.begin(), order.end());

               nearest[i].clear();

               for (int j = 0; j < N - 1; j++)

                       nearest[i].push_back(order[j].second);

        }

 

        //edges 초기화

        edges.clear();

        for (int i = 0; i < N; i++)

               for (int j = 0; j < i; j++)

                       edges.push_back(make_pair(dist[i][j], make_pair(i, j)));

        sort(edges.begin(), edges.end());

 

        //캐시 초기화

        for (int i = 0; i < MAX; i++)

               for (int j = 0; j <= CACHED_DEPTH; j++)

                       cache[i][j].clear();

 

        best = INF;

 

        //모든 도시를 시작점으로 해서 출발시켜봄

        for (int i = 0; i < N; i++)

        {

               vector<bool> visited(N, false);

               vector<int> path(1, i);

               visited[i] = true;

               search(path, visited, 0);

        }

        //최적해 반환

        return best;

}

 

int main(void)

{

        int test_case;

        cin >> test_case;

        if (test_case < 1 || test_case>50)

               exit(-1);

 

        for (int i = 0; i < test_case; i++)

        {

               cin >> N;

               if (N < 3 || N>MAX)

                       exit(-1);

              

               for (int j = 0; j < N; j++)

                       for (int k = 0; k < N; k++)

                              cin >> dist[j][k];

 

               cout.precision(10);

               cout.setf(ios::fixed, ios::floatfield);

               cout << solve() << endl;

        }

        return 0;

}
