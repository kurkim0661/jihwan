type cast를 사용할 때 주로 c-type casting을 했다. 

예를 들면

#include <iostream>
char arr[300];
char* ptr = arr;
char ch;
int num;

void main(void) {

  ch = 'h'
  num = 10;
  ptr = ch;
  ptr += sizeof(ch);
  (int*)ptr = num;
  (int*)ptr++;
}

다음과 같이 arr 에 데이터를 저장했었다. 

그러나 c-type casting은 타입체크를 하지 않아서 버그가 생길 위험이 있다.

따라서 이제는 c++용 type casting을 활용할 예정.

1.static_cast<>()
: 명시적인 type casting 방법이다. 주로 이걸 가장 많이 쓸 것 같음.
무시적 변환에는 문법적인 키워드가 없지만 명시적인 변환에는 컴파일러에 의해 값변환이 생기게 됩니다. 이를 통해서 컴파일러
단에서 문제를 해결 할 수 있게 된다는 것!

2.const_cast<>()
: const를 제거할 때 사용 
3.dynamic_cast<>()
: 자식 클래스를 부모클래스로 리타입 할 때는 static_cast를 사용해도 문제가 없지만 
반대로 부모클래스를 자식클래스로 타입캐스팅 할 때는 예기치못한 오류가 생길 수 있다. 따라서 
이럴 때는 dynamic_cast를 사용!
4.reinterpret_cast<>()
: 연관성이 없는 포인터를 캐스팅 할 때 활용한다. 
char ch = 'A';
char* p_ch = &c;
int* p_num = pc; // int* p_num = static_cast<int*>(p_ch); (X)

되지 않는다.  전 에 C-type casting에 사용했던 ()와 같은 것으로 보면 된다. 위험성이 많이 있음!

