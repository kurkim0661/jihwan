#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std; 
/* run this program using the console pauser or add your own getch, system("pause") or input loop */
int tc;
int n; //마을 갯수. 
int d; //일수 
int p; //교도소가 있는 마을. 
int t; // 확률을 구하고싶은 마을의 수. 
int numofline[51] = {0,}; 
int tt[51]; 
int map[51][51];
double cache[51][101];

int detect(int here, int days) {
	if(days == 0) {
		return (here == p ? 1.0 : 0.0);
	}
	double & ret = cache[here][days];
	if(ret > -0.5) return ret;
	ret=0.0;
	for(int i = 0 ; i < n; i++) {
		if(map[i][here] == 1) {
			ret += detect(i,days - 1) / numofline[i];
		}
	}
	return ret;
}	

int main(int argc, char** argv) {
	cin>>tc;
    for (int j = 0; j < 50; j++)
        for (int k = 0; k < 100; k++)
            cache[j][k] = -1;
            
	while(tc--) {
		memset(map,0,sizeof(map));
		cin>>n>>d>>p;
		for(int i = 0 ; i < n; i++) {
			for(int j = 0 ; j < n; j++) {
				cin>>map[i][j];
				numofline[j] += map[i][j];
			}
		}
		cin>>t;
		for(int i = 0 ; i<t; i++) {
			cin>>tt[i];
		}
		for(int i = 0; i < t; i++) {
			cout<<detect(tt[i],d)<<" ";
		}
		cout<<endl;
	}
	return 0;
}

왜 안될까...?
