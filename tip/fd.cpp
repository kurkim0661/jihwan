파일 입출력에 대한 간단한 팁..

우선 FILE* fd = fopen(path, 타입);
을 선언해준다. 
첫 번째 파라미터에는 내가 열고자하는 파일의 path를 넣어주면된다.
ex) "/system/devices/"
와 같은 방식으로
두 번째 파라미터는 읽기전용,쓰기전용,읽기쓰기 어느것으로 열지에 대한 정보이다.

읽기 전용은 "r", 쓰기는 "w" ,"a"는 추가쓰기 뒤에서부터 쓰는것. w는 새로 쓴다.
fopen을 했으면 끝에 stream을 닫아줘야함으로 fclose(stream name)을 써주면 된다..

파일에서 읽어오기 위해서는
fscanf, fgets를 사용할 수 있다.
fsanf(fd,자료타입, 위치); // 띄어쓰기도 끊어진다. 
fgets(위치, 문자열크기, fd);

fscanf나 fgets를 사용하면 위치 지정자가 계속 이동한다! 

위치 지정자는 
fseek(fd,offset, 기준점)을 표시하면 된다

offset은 거리를 나타낸다.
파일의 시작은 SEEK_SET
현재 위치는 SEEK_CUR
파일의 끝은 SEEK_END로 표시한다.
