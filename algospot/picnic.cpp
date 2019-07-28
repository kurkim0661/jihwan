#include <iostream>
#include <cstring>

using namespace std;

int tc; //Test case
int n; // 학생의 수 
int m; // 쌍의 수  
int frd[10][10];
int ans;
int check[10];
void DFS(int checked[10]);

void InputData(void) {
	int friend1;
	int friend2;
	
	cin>>tc;
	
	
	for(int i = 0; i < tc; i++) {
		cin>>n>>m;
		for(int j = 0; j < m; j++) {
			cin>>friend1>>friend2;
			if(friend1 > friend2) {
				frd[friend2][friend1] = 1;
				continue;	
			}
			frd[friend1][friend2] = 1;
		}
		
		DFS(check);
		
		cout<<ans<<endl;
		ans = 0;
		memset(frd,0,sizeof(frd));
	}
	
}

void DFS(int checked[10]) {
	int temp = 0;
	bool finished = true;
	

	for(int i = 0; i < n; i++) {
		if(checked[i] == 1) continue;
		temp = i;
		break;
	}
	
	for(int i = 0 ; i < n; i++) {
		if(checked[i] == 0) finished = false; 
	}
	
	if(finished == true) {
		ans++;
		return ;
	}
	

	for(int j = temp + 1 ; j < n ; j++) { 
		if(frd[temp][j] != 1) continue;
		if(checked[j] == 1) continue;
 
		checked[temp] = 1;
		checked[j] = 1; 
		DFS(checked);
		checked[temp] = 0;
		checked[j] = 0;		
	}
}


int main(void) {
	memset(check,0,sizeof(check));
	InputData();
}
