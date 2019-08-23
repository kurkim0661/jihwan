suffix array는 문자열을 탐색할 때 사용하는 수단인데...

말그대로 접미사배열이다. 예를들어 apple 이라는 녀석이 있다면 
앞에서 하나씩 때보면서 접미사들을 만들어보면
idx string

[0] apple 
[1] pple
[2] ple
[3] le
[4] e
다음과 같이 알 수 있고 사전 순으로 정렬을 하게되면
idx string

[0] apple
[1] e
[2] le
[3] ple
[4] pple  

와 같이 정렬이 될 것이다. 이를 suffix array라고 한다. 
이를 구하는 방법은 여러가지가 있을 수 있는데 O(nlognlogn) 의 방법인 맨버-마이어스 알고리즘을 사용한다.
참고로 SORTING을 일반 sorting 이 아닌 counting sort로 하면 O(nlogn)으로 수행이 가능하다.

간단하게 방법을 설명하면 크게 3개의 vector<int>를 만든다. g(group에 대한 정보), ng(새로운 그룹저장할 버퍼), sfx(suffix array 정보)

sfx배열은 순차적으로 0~n 까지 수를 넣어주고 g에는 정렬할 string을 매칭시켜 저장한다. g[0] = s[0], g[1] = s[1] ... 
그후 g를 기준으로 compare를 실행하여서 sfx를 정렬한다. 그 후 정렬된 sfx를 다시 g를 기준으로 순차적으로 비교를 하면서 
sfx의 값을 ng 의 idx로 하여서 ng의 순서를 매겨간다.

참고 소스코드

vector<int> getsfx(string &s) {
    int n = s.size();
    sfx.resize(n); g.resize(n+1); ng.resize(n+1);
    for(int i=0; i<n; i++) sfx[i]=i, g[i]=s[i];
 
    g[n]=-1;
    for(int t=1; t<n; t<<=1) {
        auto cmp = [&](int i, int j) {
            if(g[i]==g[j]) return g[i+t]<g[j+t];
            else return g[i]<g[j];
        };
        sort(sfx.begin(), sfx.end(), cmp);
        ng[sfx[0]]=0;
        ng[n]=-1;
        for(int i=1; i<n; i++) {
            if(cmp(sfx[i-1],sfx[i])) ng[sfx[i]]=ng[sfx[i-1]]+1;
            else ng[sfx[i]]=ng[sfx[i-1]];
        }
        g=ng;
    }
    return sfx;
}


출처: https://plzrun.tistory.com/entry/Suffix-Array-ONlogNlgN과-ONlogN-구현-및-설명 [plzrun's algorithm]

