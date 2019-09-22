#include <iostream>
#include <algorithm>
#include <functional>
#include <vector>
#include <queue>
using namespace std;
 
#define INF 2100000000
priority_queue <pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>> pq;    // priority queue 선언
 
vector<pair<int,int>> graph[8];                            // 각 노드에서 갈 수 있는 노드와 cost를 기록해주기 위함
                                                        // first : cost, second : node 번호
int fromnode, tonode, cost, startnode,n_cost,n_node;
int cost_arr[8];                                        // start node에서 각 node로 갈 수 있는 최소 비용을 기록할 array
 
int main() {
    for (int i = 0; i < 9; i++) {                // 무방향 그래프이므로 노드,노드,cost 입력받은 후 양 방향에서 갈 수 있게 넣어줌
        cin >> fromnode >> tonode >> cost;
        graph[fromnode].push_back(make_pair(cost, tonode));
        graph[tonode].push_back(make_pair(cost, fromnode));
    }
 
    for (int i = 1; i < 8; i++) {                // 처음에 모두 무한대 값으로 초기화해줌
        cost_arr[i] = INF;
    }
    cin >> startnode;
    cost_arr[startnode] = 0;                    // 시작 노드로 가는 cost 0으로 초기화
    
    pq.push(make_pair(cost_arr[startnode], startnode));        // startnode로 가는 cost와 startnode 번호를 priority queue에 넣어줌
 
    while (!pq.empty()) {
        n_cost = pq.top().first;        // 가장 작은 cost를 가진 top을 꺼내옴
        n_node = pq.top().second;        // 가장 작은 cost를 가진 노드의 번호를 꺼내옴
 
        pq.pop();                        // queue에서 제거
        if (n_cost > cost_arr[n_node]) {    // 새로 꺼내온 것보다 기존 것이 더 작을 경우 넘어감
            continue;
        }
        for (int j = 0; j < graph[n_node].size(); j++)        // 꺼내온 노드에서 갈수 있는 모든 node를 탐색
        {
            if (n_cost + graph[n_node][j].first < cost_arr[graph[n_node][j].second])        // startnode에서 현재 node까지의 거리+ 현재 node에서 다른 node로 가는 cost
            {                                                                                // 가 현재까지 기록된 최소 비용보다 작을 경우
                cost_arr[graph[n_node][j].second] = n_cost + graph[n_node][j].first;            // cost array에 최소 비용 기록
                pq.push(make_pair(n_cost + graph[n_node][j].first, graph[n_node][j].second));    // priority queue에 넣어줌
            }
        }
    }
    for (int i = 1; i < 8; i++) {
        cout << (char)(startnode + 64) << "->" << (char)(i + 64) << " cost : " << cost_arr[i] << endl;
    }
    return 0;
}
