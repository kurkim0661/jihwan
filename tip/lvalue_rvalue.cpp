lvalue 와 rvalue는 left 와 right의 의미가 아니다. ( c++ 에서)

c++ 표준에서 lvalue의 의미는 표현식을 거치고 나서도 지속적으로 존재하는 객체 이름이 있는 객체를 의미한다.
이에 반해서 rvalue는 휘발성 객체를 의미한다. 예를 들자면 함수를 통해서 return 되어진 값 은 어딘가에 저장이 되지 않는다면 바로 사라지게 되는데 
이 같은 값을  rvalue라고 한다.

우리가 기존에 사용하던 참조자인 &는 lvalue에서만 사용이 가능하다. 그렇다면 rvalue는 어떤 방식을 써야할까?
rvalue는 &&를 사용하여 참조할 수 있다. 

  
  https://spikez.tistory.com/305 참조 사이트. 
rvalue 참조의 활용 및 단점.
