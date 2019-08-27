기존 enum은 선언을 하고나면 다른 enum선언에서 선언했던 녀석들이랑 비교를 해도
ex 
enum color {
  RED,
  BLUE,
  GREEN
};

enum CAR //: int
{
  DOOR,
  HANDLE,
  MIRROR
};

RED == DOOR가 참으로 나온다. 
이러한 문제를 해결하기 위해서
enum class가 도입되었고 이를 통해 선언한 아이들은 서로와 비교가 되지만 다른 것들과는 비교가 안된다.
타입캐스팅을 하면 가능은 하지만 우리가 원하는 것은 그것이 아닐 수 있으니...
