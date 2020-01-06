//check 2
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;
 
const int ALPHABETS = 26;
 
int toNumber(char ch)
{
        return ch - 'A';
}
 
struct TrieNode
{
        TrieNode *children[ALPHABETS];
        //이 노드에서 종료하는 문자열의 번호, 없으면 -1
        int terminal;
        //이 노드를 루트로 하는 트라이에 가장 먼저 추가된 단어의 번호
        //-1로 초기화
        int first;
        TrieNode() : terminal(-1), first(-1)
        {
                 memset(children, 0, sizeof(children));
        }
        ~TrieNode()
        {
                 for (int i = 0; i < ALPHABETS; i++)
                         if (children[i])
                                 delete children[i];
        }
        //이 노드를 루트로 하는 트라이에 번호 id인 문자열 key를 추가한다
        void insert(const char *key, int id)
        {
                 //first를 우선 갱신
                 if (first == -1)
                         first = id;
                 //문자열이 끝났다면 terminal만 바꾸고 종료
                 if (*key == 0)
                         terminal = id;
                 else
                 {
                         int next = toNumber(*key);
                         //해당 자식 노드가 없다면 생성
                         if (children[next] == NULL)
                                 children[next] = new TrieNode();
                         //해당 자식 노드로 재귀 호출
                         children[next]->insert(key + 1, id);
                 }
        }
        //이 노드를 루트로 하는 트라이에 문자열 key와 대응되는 노드를 찾는다
        //없으면 NULL return
        TrieNode *find(const char *key)
        {
                 if (*key == 0)
                         return this;
                 int next = toNumber(*key);
                 if (children[next] == NULL)
                         return NULL;
                 return children[next]->find(key + 1);
        }
        //이 노드까지 타이핑해 왔을 떄, 번호 id인 key를 타이핑하기 위해
        //최소 몇 번의 키를 눌러야 하나
        int type(const char *key, int id)
        {
                 //문자열 종료시
                 if (*key == 0)
                         return 0;
                 //이 노드에서 추천되는 문자열이 이 문자열이면 탭 누르고 종료
                 if (first == id)
                         return 1;
                 //아니면 다음 문자를 타이핑한다
                 int next = toNumber(*key);
                 return 1 + children[next]->type(key + 1, id);
        }
};
 
//사전을 타나태는 트라이가 주어질 때, 단어 word를 타이핑하는 데
//몇 번이나 키를 눌러야하는지 계산한다
int countKeys(TrieNode *trie, const char *word)
{
        //이 문자열이 사전에 있는지 확인하고, 있다면 번호를 구한다
        TrieNode *node = trie->find(word);
        //사전에 없으면 직접 타이핑할 수 밖에 없다
        if (node == NULL || node->terminal == -1)
                 return strlen(word);
        //탐색하면서 타이핑할 방법을 찾는다
        return trie->type(word, node->terminal);
}
 
//입력에 주어지는 단어들을 정렬해서 트라이로 변환
TrieNode *readInput(int words)
{
        //단어들을 출현 빈도의 내림차순, 단어의 오름차순으로 정렬한다
        vector<pair<int, string>> input;
        for (int i = 0; i < words; i++)
        {
                 char buf[11];
                 int freq;
                 cin >> buf >> freq;
                 input.push_back(make_pair(-freq, buf));
        }
        sort(input.begin(), input.end());
        //이 때 앞에 있는 단어일수록 우선순위가 높다
        //배열의 인덱스를 각 단어의 번호로 쓰자
        TrieNode *trie = new TrieNode();
        for (int i = 0; i < input.size(); i++)
                 trie->insert(input[i].second.c_str(), i);
        trie->first = -1;
        return trie;
}
 
int main(void)
{
        ios_base::sync_with_stdio(0);
        cin.tie(0); //cin 실행속도 향상
        int test_case;
        cin >> test_case;
 
        for (int t = 0; t < test_case; t++)
        {
                 int N, M;
                 cin >> N >> M;
 
                 TrieNode *trie = readInput(N);
                 int result = M - 1; //space bar
                 for (int i = 0; i < M; i++)
                 {
                         char buf[11];
                         cin >> buf;
                         result += countKeys(trie, buf);
                 }
                 cout << result << "\n";
        }
        return 0;
}
