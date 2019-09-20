#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <functional>

using namespace std;

bool sort_pred(const pair<int,int>& left, const pair<int,int>& right)
{
    return left.first > right.first;
}

int main(){
    int C;
    cin >> C;

    vector< pair<int,int> > data[100];

    while ( C-- )    {
        int N, M ;
        cin >> N >> M;

        for ( int i = 0; i < M; i++ )
            data[i].clear();

        for ( int i = 0; i < N; i++ )        {
            for ( int j = 0; j < M; j++ )            {
                int price, point;
                cin >> price >> point;
                data[j].push_back( make_pair(point,price));
            }
        }

        for ( int i = 0; i < M; i++ )
            sort(data[i].begin(), data[i].end(), sort_pred);

        for ( int i =1; i < N; i++ )        {
            for ( int m = 0; m < M; m++)            {
                if ( data[m][i].second < data[m][i-1].first )                {
                    data[m][i].first += data[m][i-1].first - data[m][i].second;
                    data[m][i].second = data[m][i-1].second;
                }
                else {
                    data[m][i].second += data[m][i-1].second - data[m][i-1].first;

                }
            }
        }

        int minVal = data[0][N-1].second;
        for ( int i = 1; i < M; i++ )        {
            if ( data[i][N-1].second < minVal )
                minVal = data[i][N-1].second;
        }

        cout << minVal << endl;

    }
}
