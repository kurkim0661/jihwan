처음에 보고 뭔가 했었는데 찾다가 알게되었다. 람다함수
처음 보게된건 

auto cmp = [&](int i, int j) {
            if(g[i]==g[j]) return g[i+t]<g[j+t];
            else return g[i]<g[j];
        };
출처: https://plzrun.tistory.com/entry/Suffix-Array-ONlogNlgN과-ONlogN-구현-및-설명 [plzrun's algorithm]

에서 보게되었다. 참고로 suffix-array를 구하는 과정에서 sorting 을 하는 조건이다.

람다함수란
[]() -> type {}; 의 형태로 구성이 되어있다.
[] : 개시자 () : 인자 -> type : 반환형 {} : 함수의 몸통이라 할 수 있다.
개시자는 외부의 변수를 캡처해서 사용한다고 생각하면된다. 참고로 캡처해 올때 const를 붙여서 오기 때문에 변경은 불가핟.
바꾸기 위해서는 [&]() {} 의 형태로 개시자에 &를 붙여주면 가능하다.
