snprintf는.. 

#include <stdio.h>

int main ()
{
  char buffer [100];
  int cx;

  cx = snprintf ( buffer, 100, "The half of %d is %d", 60, 60/2 );

  if (cx>=0 && cx<100)      // check returned value

    snprintf ( buffer+cx, 100-cx, ", and the half of that is %d.", 60/2/2 );

  puts (buffer);

  return 0;
}

다음과 같이 활용할 수 있다. sprintf와 다르게 오버플로를 방지하기 위해 원하는 길이만큼 buffer에 저장할 수 있게 한다.
좀 더 안전한 방법. 
