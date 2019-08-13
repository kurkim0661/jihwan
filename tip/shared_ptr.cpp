c++에서 메모리 누수로 부터 프로그램의 안정성을 보장받기 위해서 스마트 포인터개념을 도입한 것.

shared_ptr
shared_ptr은 하나의 특정 객체를 참조하는 스마트 포인터가 총 몇 개인지를 참조하는 스마트 포인터입니다.

이렇게 참조하고 있는 스마트 포인터의 개수를 참조 횟수(reference count)라고 합니다.

참조 횟수는 특정 객체에 새로운 shared_ptr이 추가될 때마다 1씩 증가하며, 수명이 다할 때마다 1씩 감소합니다.

따라서 마지막 shared_ptr의 수명이 다하여, 참조 횟수가 0이 되면 delete 키워드를 사용하여 메모리를 자동으로 해제합니다.

 

예제
shared_ptr<int> ptr01(new int(5)); // int형 shared_ptr인 ptr01을 선언하고 초기화함.

cout << ptr01.use_count() << endl; // 1

auto ptr02(ptr01);                 // 복사 생성자를 이용한 초기화

cout << ptr01.use_count() << endl; // 2

auto ptr03 = ptr01;                // 대입을 통한 초기화

cout << ptr01.use_count() << endl; // 3  

 

위의 예제에서 사용된 use_count() 멤버 함수는 shared_ptr 객체가 현재 가리키고 있는 리소스를 참조 중인 소유자의 수를 반환해 줍니다.

 

위와 같은 방법 이외에도 make_shared() 함수를 사용하면 shared_ptr 인스턴스를 안전하게 생성할 수 있습니다.

make_shared() 함수는 전달받은 인수를 사용해 지정된 타입의 객체를 생성하고, 생성된 객체를 가리키는 shared_ptr을 반환합니다.

이 함수를 사용하면, 예외 발생에 대해 안전하게 대처할 수 있습니다.

 

다음 예제는 Person 객체를 가리키는 hong이라는 shared_ptr를 make_shared() 함수를 통해 생성하는 예제입니다.

예제
shared_ptr<Person> hong = make_shared<Person>("길동", 29);

cout << "현재 소유자 수 : " << hong.use_count() << endl; // 1

auto han = hong;

cout << "현재 소유자 수 : " << hong.use_count() << endl; // 2

han.reset(); // shared_ptr인 han을 해제함.

cout << "현재 소유자 수 : " << hong.use_count() << endl; // 1

