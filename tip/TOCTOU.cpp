TOCTOU란 
Time of check to time of use
어떤 리소스를 체크하고 사용하는 사이에 발생할 수 있는 RACE CONDITION을 말한다.
예를들어 
if(access(path,F_OK != 0) {
  mkdir(path, 0755);
}
라고 하면 path가 존재하는 지 확인을 하고 mkdir과정을 하게 되는데
이 때 둘 사이에 문제가 생길 수 있다.
