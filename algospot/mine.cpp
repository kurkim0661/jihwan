#include <algorithm>
#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
#define REP(i,n) for(int i=0; i<(n); ++i)
#define N 1000
int backup[32][N+5];
int dt[32][N+5],dp[32][N+5];
int hy[4]={-1,1,0,0};
int hx[4]={0,0,-1,1};
int val[4],U,D,L,R;
int n,m;
bool remove(int y,int x)
{
    int py,px;
    REP(i,4) {
        py=y+hy[i];
        px=x+hx[i];
        if (py<0 || py>=n || px<0 || px>=m) continue;
        dt[py][px]-=val[i];
        if (dt[py][px]<0) return false;
    }
    dp[y][x]=1;
    return true;
}
bool isallzero()
{
    REP(i,n) REP(j,m) if (dt[i][j]!=0) return false;
    return true;
}
bool solve()
{
    REP(i,n) REP(j,m) {
        if (dt[i][j]==L)
            if (!remove(i,j+1))
                return false;
        if (dt[i][j]==U)
            if (!remove(i+1,j))
                return false;
        if (dt[i][j]==L+U)
            if (!remove(i,j+1) || !remove(i+1,j))
                return false;
    }
    return true;
}
int main()
{
    int tn;
    cin>>tn;
    while (tn--) {
        cin>>n>>m;
        cin>>U>>D>>L>>R;
        val[0]=U; val[1]=D;
        val[2]=L; val[3]=R;
        REP(i,n) REP(j,m) cin>>dt[i][j];
        memcpy(backup,dt,sizeof(dt));
        int cnt=0;
        REP(qq,2) {
            memcpy(dt,backup,sizeof(dt));
            memset(dp,0,sizeof(dp));
            if (qq)
                if (!remove(0,0))
                    continue;
            if (solve() && isallzero()) {
                REP(i,n) {
                    REP(j,m) {
                        if (j) cout<<" ";
                        cout<<dp[i][j];
                    }
                    cout<<endl;
                }
            }
        }
    }
    return 0;
}
