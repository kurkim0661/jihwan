STL Containers



STL(Standard Template Libary)

c++의 템플릿을 사용해 표준으로 정리된 착하고 편리한 칭구들

반복자 / 컨테이너 / 알고리즘 / 함수객체등의 라이브러리로 구성



컨테이너 : 기본자료형(int등)과 유저 정의 자료형(struct / class)을 담는 일종의 자료구조



컨테이너 종류 : 자료의 구조로 구분

1. 시퀀스 컨테이너

일반적인 자료구조와 동일형태 (vector / list / string / deque 등..)

자료를 입력한 순서대로 저장하기 떄문에 저장, 검색, 알고리즘에 불리

 -> 많지않은양의 자료 / 검색속도 중요하지 않은경우 사용



2. 연관 컨테이너

일정규칙에 따라 자료를 조직화하여 저장(set / map / multiset / multimap 등)

자료를 정렬하여 저장하기 떄문에 검색 유리

 -> 많은양의 자료 / 빠른검색



3. 어댑터 컨테이너

시퀀스 컨테이너를 변형시켜 스택 큐 우선순위 큐 형태로 저장(queue, stack 등)





컨테이너 분류 : 메모리상에 자료를 구성하는 형태로 구분

1. Contiquius-Memory(연속 메모리) : 동적할당된 하나의 메모리단위에 데이터 요소 저장

2. Node-Based(노드 기반) : 동적할당된 하나의 메모리 단위에 하나의 요소만 저장, 포인터로 이들을 연결

(자료 추가 삭제에 유리 / 순차적 접근만 가능해 랜덤접근 불가)



<array> : 배열

<vector> : 가변배열

<queue> : FIFO(First In First Out) 선입선출 자료구조    // priority_queue(우선순위 큐) 도 있음(정렬)

<deque> : 덱(앞뒤로 넣고빼는 큐)                     // Double-Ended Queue

<list> : 양방향 연결리스트

<forward_list> : 단방향 연결리스트

<stack> : FILO(First In Last Out) 선입후출 자료구조

<map> : 이진탐색트리 기반 / 자동정렬 / key - value pair로 구성

<set> : 이진탐색트리 기반 / 자동정렬 / key 만 저장함

<unordered_map> : 정렬되지않은 map

<unordered_set> : 정렬되지 않은 set







각 자료구조별 특징



1. 적은양의 자료일경우 사용할 컨테이너들

array

배열 자료구조

장점

단점 

적은양의 자료에 유리

크기 변경 불가 



vector

가변배열 자료구조

장점 

단점 

적은양의 자료에 유리

크기변경가능

순차 접근 가능

랜덤 엑세스 가능

중간삽입삭제

검색느림

많은양의 자료에 불리 



list / forward_list

연결리스트

장점 

단점 

중간삽입삭제

크기변경가능

적은양의 자료에 유리

순차 접근 가능

많은양의 자료에 불리

랜덤 엑세스 불가

검색느림

기능적으로는 list가 / 성능적으로는 forward_list가 가볍고 좋다고함



* 중간삽입삭제가 없고 랜덤접근이 많다 : vector

* 중간삽입삭제가 있고 랜덤접근이 없다 : list

* 하지만 데이터 개수가 적은경우는 vector사용하는편이 더 좋다(성능상)



* 랜덤 엑세스(임의접근/랜덤접근/비순차적 접근 / 직접접근)

데이터의 어느 위치에 접근해도 시간이 같게 걸리는 방식





2. 많은양의 데이터 + 검색활발

map

이진탐색트리기반

균형이진트리 (레드-블랙 트리 : 작은값이 부모 , 왼쪽은 그다음큰값, 오른쪽은 가장 큰 값)

key와 value가 pair로 구성

장점 

단점 

많은양의 자료에 유리

검색속도 빠름

key와 value 따로 저장

자동정렬

적은양엔 오버헤드로인해 손해



set

이진탐색트리기반(레드 -블랙 트리)

게임쪽에서는 많이안쓴다고함

장점 

단점 

많은양의 자료에 유리

검색속도빠름

key가 곧 value. key만저장

자동정렬

적은양엔 오버헤드로인해 손해 



정렬되지않은 map,set : unordered_map / unordered_set

key의 중복허용 : multimap / mulitset







etc..

// http://www.gpgstudy.com/forum/viewtopic.php?t=20337 참고



vector

- reserve제대로 안하고 실시간 push_back하면 안된다 // 관련 커스텀fix 관련 링크

- clear가 제대로된claer는 아님

- 범위외 참조하지 말것



map

- 집어넣을때 최대한 insert(::value_type())을 애용할것





effective stl을 보게되면 추가해서 더 적을 수 있을 것 같음



출처: https://code-algalon.tistory.com/188 [code-algalon]
