#include <iostream>
using namespace std;
int TC;
int N;
int Q;
int tree[100001];
int deapth[100001];
int flag1;
int flag2;
int temp1;
int temp2;
int temp;
int minn = 1;
int maxx = 0;
int cnt;
int d;
int main(void) {
	cin>>TC;
	while(TC--) {
		cin>>N>>Q;
		tree[0] = -1;
		for(int i = 1; i < N; i++) {
			scanf("%d", &tree[i]);
		}

		for(int i = 1; i < N; i++) {
			temp = tree[i];
			while(temp != tree[0]) {
				temp = tree[temp];
				d++;
			}
			deapth[i] = d;
		}
		deapth[0] = 0;
		for(int i = 0; i < Q; i++) {
			cin>>temp1>>temp2;
			if(temp1 == 0 && temp2 != 0) {
				temp1 = -1;
				while(temp1 != temp2) {
					if(temp2 != -1) {
						temp2 = tree[temp2];
					}
	 				++cnt;
					
				}
				cnt--;
				cout<<cnt<<endl;
				cnt = 0;
				continue;
			}
			if(temp1 != 0 && temp2 == 0) {
				temp2 = -1;
				while(temp1 != temp2) {
					if(temp1 != -1) {
						temp1 = tree[temp1];	
					}
					++cnt;
				}
				cnt--;
				cout<<cnt<<endl;
				cnt = 0;
				continue;
			}
			
			if(deapth[temp1] == deapth[temp2]) {
				minn = temp1;
				maxx = temp2;
			}
			else {
				minn = deapth[temp1] < deapth[temp2] ? temp1 : temp2;
				maxx = deapth[temp1] < deapth[temp2] ? temp2 : temp1;
			}


			while(deapth[minn] != deapth[maxx]) {
				maxx = tree[maxx];
				++cnt;
			}
			
			while(minn != maxx) {
				
				
				if(minn != -1) {
					minn = tree[minn];
				}
				if(maxx != -1) {
					maxx = tree[maxx];
				}
				if((minn != -1) && (maxx != -1)) {
					cnt += 2;
					continue;
				}
 				++cnt;
			}
			cout<<cnt<<endl;
			cnt = 0;
		}
	}
}
