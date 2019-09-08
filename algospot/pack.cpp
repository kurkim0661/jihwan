#include <iostream>
#include <algorithm>
#include <string>
#include <cstring>
#include <vector>
using namespace std; 
/* run this program using the console pauser or add your own getch, system("pause") or input loop */
int tc;
int N;
int W;
int cache[1001][101];
string name[101];
int value[101];
int weight[101];
vector<string> ans;
int pack(int item, int w) {

	if(item == N) return 0;
	int& ret = cache[w][item];
	if(ret != -1) return ret;
	ret = 0;
	ret = pack(item + 1, w);
	if(w >= weight[item]){
		ret = max(ret, pack(item + 1 , w - weight[item]) + value[item]) ;
	}
	return ret;
	
}

void reconstruct(int item,int w) {
	if(item == N) return ;
	if(pack(item + 1, w) == pack(item + 1, w-weight[item])) {
		reconstruct(item + 1, w);		
	}
	else {
		ans.push_back(name[item]);
		reconstruct(item + 1, w-weight[item]);
			
	}
}

int main(int argc, char** argv) {
	cin>>tc;
	while(tc--) {
		memset(cache,-1,sizeof(cache));
		memset(value,0,sizeof(value));
		memset(weight,0,sizeof(weight));
		
		cin>>N>>W;
		for(int i = 0; i < N; i++) {
			cin>>name[i]>>weight[i]>>value[i];
		}
		cout<<pack(0,W)<<" ";
		reconstruct(0,W);
		cout<<ans.size()<<endl;
		for(int i = 0; i < W; i++) {
			cout<<ans[i]<<endl;
		}
		ans.clear();
	}
	return 0;
}

// name 정리가 잘 안된다...
