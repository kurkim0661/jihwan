#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

int N, M;
 
struct BipartiteUnionFind
{
        //parent[i] = i의 부모 노드, 루트라면 i
        //rank[i] = i가 루트인 경우, i를 루트로 하는 트리의 랭크
        //enemy[i] = i가 루트인 경우, 해당 집합과 적대 관계인 집합의 루트의 번호 (없으면 -1)
        //size[i] = i가 루트인 경우, 해당 집합의 크기
        vector<int> parent, rank, enemy, size;
        BipartiteUnionFind(int n) :parent(n), rank(n, 0), enemy(n, -1), size(n, 1)
        {
                 for (int i = 0; i < n; i++)
                         parent[i] = i;
        }
        int find(int u)
        {
                 if (parent[u] == u)
                         return u;
                 return parent[u] = find(parent[u]);
        }
        int merge(int u, int v)
        {
                 //u나 v가 공집합인 경우 나머지 하나를 반환
                 if (u == -1 || v == -1)
                         return max(u, v);
                 u = find(u);
                 v = find(v);
                 //이미 둘이 같은 트리에 속한 경우
                 if (u == v)
                         return u;
                 if (rank[u] > rank[v])
                         swap(u, v);
                 //이제 항상 rank[v]가 더 크므로 u를 v의 자식으로 넣는다
                 if (rank[u] == rank[v])
                         rank[v]++;
                 parent[u] = v;
                 size[v] += size[u];
                 return v;
        }
        //u와 v가 서로 적이다. 모순이 일어났다면 false, 아니면 true
        bool dis(int u, int v)
        {
                 //우선 루트를 찾는다
                 u = find(u);
                 v = find(v);
                 //같은 집합에 속해 있으면 모순
                 if (u == v)
                         return false;
                 //적의 적은 나의 동지
                 int a = merge(u, enemy[v]);
                 int b = merge(v, enemy[u]);
                 enemy[a] = b;
                 enemy[b] = a;
                 return true;
        }
        //u와 v가 서로 동지다. 모순이 일어났다면 false, 아니면 true
        bool ack(int u, int v)
        {
                 //우선 루트를 찾는다
                 u = find(u);
                 v = find(v);
                 //두 집합이 서로 적대 관계라면 모순
                 if (enemy[u] == v)
                         return false;
                 //동지의 적은 나의 적
                 int a = merge(u, v);
                 int b = merge(enemy[u], enemy[v]);
                 enemy[a] = b;
                 //두 집합 다 적대하는 집합이 없으면 b는 -1일 수 있다
                 if (b != -1)
                         enemy[b] = a;
                 return true;
        }
};
 
//BipartiteUnionFind 인스턴스가 주어질 때
//한 파티에 올 가능성이 있는 최대 인원을 구한다
int maxParty(const BipartiteUnionFind &buf)
{
        int result = 0;
        for(int node=0; node < N; node++)
                 if (buf.parent[node] == node) //루트인 경우만
                 {
                         int enemy = buf.enemy[node];
                         //같은 모임 쌍을 두번 세지 않기 위해, enemy < node인 경우만 센다
                         //enemy==-1인 경우도 정확히 한 번씩 세게 된다
                         if (enemy > node)
                                 continue;
                         int mySize = buf.size[node];
                         int enemySize = (enemy == -1 ? 0 : buf.size[enemy]);
                         //두 집합 중 큰 집합을 더한다
                         result += max(mySize, enemySize);
                 }
        return result;
}
 
int main(void)
{
        ios_base::sync_with_stdio(0);
        cin.tie(0); //실행속도 향상
        int test_case;
        cin >> test_case;
 
        for (int t = 0; t < test_case; t++)
        {
                 cin >> N >> M;
 
                 BipartiteUnionFind buf(N);
 
                 bool contradict = false; //모순
                 int num = -1;
 
                 for (int i = 0; i < M; i++)
                 {
                         string s;
                         int node1, node2;
 
                         cin >> s >> node1 >> node2;
                         if (contradict)
                                 continue;
 
                         if (s == "ACK")
                         {
                                 if (!buf.ack(node1, node2)) //모순 발생할 경우
                                 {
                                          contradict = true;
                                          num = i + 1;
                                 }
                         }
                         else
                         {
                                 if (!buf.dis(node1, node2)) //모순 발생할 경우
                                 {
                                          contradict = true;
                                          num = i + 1;
                                 }
                         }
                 }
 
                 if (contradict)
                         cout << "CONTRADICTION AT " << num << "\n";
                 else
                         cout << "MAX PARTY SIZE IS " << maxParty(buf) << "\n";
        }
        return 0;
}
