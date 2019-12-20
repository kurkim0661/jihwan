알고리즘.






서비스 구상 및 프로젝트 구성

1.	아이디어 정리
자신의 취미, 휴식을 위해서 사람들은 여가활동을 즐긴다. 
다양한 여가활동이 존재하는데. 많은 사람이 필요로 하지 않고 혼자 하거나 2~3 만 모여도 할 수 있는 여가활동도 있는 반면에 축구와 농구와 같은 활동을 할 때에는 더욱 많은 이들이 필요하다. 
뿐만 아니라 공연을 하고 싶은 사람들도 팀을 꾸려야 한다. 몇 가지 예를 들면 밴드 활동을 하 고 싶은데 나는 마땅히 들어있는 팀이 없다거나, 연극을 하고 싶은데 많은 인원들을 모을 수 있는 여력이 안 된다거나 말이다.
 이러한 사람들을 위해서 스포츠, 공연관련 플랫폼을 만들어 보면 어떨까 한다. 
좀 더 집중적으로 보려고 하는 것은 공연관련 플랫폼에 대한 부분이다. 현재 연극, 뮤지컬, 영화 같은 부분에서는 OTR, 필름메이커스 와 같은 오디션을 보거나 일자리를 구하는 등 직업적인 부분에서만 접근할 수 있는 사이트가 존재한다. 이러한 문제로 인해서 정말 취미로 하고 싶어하는 사람들은 쉽게 접하기가 어려운 부분이 있다. 따라서 직업적인 목적이 아닌 취미를 목적으로 하는 사람들이 자유롭게 사람들을 구하여 쉽게 공연에 접근할 수 있도록 만드는 것이다. 또한 몇 가지 조건만 걸어주면 빠르게 조건에 부합하는 사람이 모이면 바로 매칭을 해주기 때문에 좀 더 빠르게 모집할 수 있을 것으로 기대된다.


소개팅 앱과 같이 같이 공연을 하고자 하는 사람들을 랜덤 매칭을 해준다.
랜덤 매칭 뿐만 아니라 정해진 음악이라던가 극 또는 하고자하는 방향을 설정하여 
뜻이 맞는 사람들을 찾아서 할 수 도 있다.

사람들의 후기 관리를 통해서 그 사람의 평판등을 정할 수 있게 하여서 사후관리를 도입.
특정 평판 미만이거나 불순한 행동을 했을 경우 제재를 하여서 참여에 불이익을 가한다.

사람들은 간단한 프로필을 만들 수 있게 한다. (자기소개)


2. 시나리오 정리

3. 기능 리스트 작성

----------------------
앱 기획
1. 화면 플로우 차트 작성

앱 기획 단계에서는 사용자의 앱 사용 로직과 디자인을 결정하게 됩니다. 앞서 정리한 기능 리스트를 바탕으로 화면 플로우 차트를 작성합니다. 화면 플로우는 화면 이동에 대한 순서와 화면 별 기능을 간략하게 정리한 차트입니다. 직접 손으로 스케치하거나 PPT를 이용하여 간단하게 작성합니다.

2. 와이어 프레임 작성 (화면 정의서 포함)
와이어 프레임은 골격을 의미합니다. 아직 디자인이 입혀져 있지는 않지만 화면의 구조와 화면에 표시될 내용과 기능을 설명하는데 사용됩니다. 일종의 화면 정의서라고 할 수도 있죠.

와이어 프레임을 작성할 수 있는 툴에 대한 내용은 아래 글을 참고하시길 바랍니다.

와이어 프레임, 프로토타입 제작 툴 정리

개인적으로 이 중에서 카카오에서 개발한 온라인 프로토타입 툴인 Oven을 추천합니다.  Oven은 웹에서 바로 작업할 수 있으며 무료입니다.

3. 상세 기능 리스트 작성
화면 플로우와 와이어 프레임을 작성하였으면, 앞서 작성한 기능 리스트를 점검하여 상세 기능 리스트를 작성합니다. 정보의 생성, 조회, 수정, 삭제(=CRUD)는 각각 하나의 기능으로 따로 분리합니다.

기술 검토 및 견적
1. 서버 사용 여부 결정
먼저 데이터를 어떻게 관리할지 결정하여야 합니다. 데이터는 사용자의 스마트폰 기기에 저장할 수도 있고 별도의 서버를 두어 저장할 수도 있습니다. 사용자 개인정보, 비밀번호와 같은 민감한 데이터는 보안을 철저히 해야 합니다.

삭제 되어도 상관 없는 정보나 캐시는 사용자 스마트폰 로컬 DB에 저장할 수 있습니다. 하지만 중요한 정보는 서버에서 따로 관리하여야 합니다. 따라서 단순한 앱이 아니라면 대부분 서버를 두어 데이터의 저장과 처리를 담당합니다.

앱 제작에 서버 개발이 추가 되면 앱 개발 기간과 비용이 배 이상 증가할 수 있습니다. 따라서 우선 제공하고자 하는 기능을 검토하여 서버 개발이 필요한지 먼저 판단해야 합니다.

2. 서버 아키텍처 설계
만약 서버 개발을 하기로 했다면, 어떤 언어와 프레임워크로 개발할 지 정해야 합니다. 또한 서버 사양과 네트워크, DB 사양을 결정해야 합니다. 프로젝트 규모가 크다면 소스 형상 관리, 이슈 트래킹, 빌드 및 배포 시스템도 구성합니다. 아키텍처 설계는 앱과 서버 양 쪽 모두에 경험과 지식이 있는 리드 개발자를 통해 결정합니다. 만약 전문가가 필요하다면 서버 아키텍처 전문가에게 설계를 의뢰할 수도 있습니다.

3. 앱 아키텍처 설계
앱은 크게 네이티브 앱, 모바일 웹, 하이브리드 앱으로 구분할 수 있습니다.

네이티브 앱은 속도가 빠르며 스마트폰 기능을 다양하게 사용할 수 있으나 안드로이드, iOS와 같은 플랫폼에 종속됩니다. 따라서 네이티브 앱을 만들기로 했다면 안드로이드용 앱과 iOS용 앱을 따로 만들어야 합니다. 그만큼 개발 기간과 비용이 증가합니다.

모바일 웹은 스마트폰 브라우저로 구동 됩니다. 앱 패키지가 사용자의 스마트폰에 설치되는 것이 아니기 때문에 엄밀히 말하면 앱은 아닙니다. 모바일 웹의 장점은 웹 개발 방식으로 제작할 수 있다는 점과 수정할 때마다 앱 배포를 하지 않아도 된다는 점입니다. 단, 모바일 사이즈에 맞게 반응형으로 화면을 제작해야 합니다. 그리고 앱이 아니기 때문에 구글 플레이나 앱스토어 앱을 배포할 수 없으며, 사용자가 브라우저를 열고 사이트 주소를 입력해야 한다는 접근성의 문제가 있습니다. 또한 네이티브 앱에 비해 기능이 제한적이며, 속도가 느립니다.

하이브리드 앱은 네이티브 앱과 모바일 웹의 장점을 적절하게 섞은 앱 입니다. React Native, Ionic, Framework7, PhoneGap, Onsen UI 같은 하이브리드 앱 프레임워크로 개발합니다. 구글 플레이 같은 플랫폼에 앱을 배포할 수 있으며, 사진 촬영, 자이로센서 등 스마트폰의 네이티브 기능을 이용할 수 있습니다. 단, 그래도 네이티브 앱보다 느린 편이며, iOS 앱스토어 마켓에 등록하기 어렵다는 등의 단점이 있습니다.

위 3가지 앱의 장단점을 이해하고, 서비스 하고자 하는 기능과 앱 배포 방법, 개발 인력 등을 고려하여 어떤 형태의 앱으로 개발할지 결정합니다 .

4. 지원 플랫폼 결정 (안드로이드, iOS)
MS에서 윈도우폰 지원을 종료하면서 모바일 플랫폼은 안드로이드와 iOS로 양분되어 있습니다. 국내는 안드로이드 점유율이 70% 이상을 차지하는 반면 해외는 iOS 점유율이 더 높습니다. 모바일 플랫폼(OS)의 시장 점유율 자료는 아래 링크를 참고하시길 바랍니다.

한국, 일본, 미국 모바일 시장 비교
스마트폰 사용율 조사 – 한국갤럽조사연구소
지원 플랫폼을 결정하는 것은 앱 개발 기간과 비용에 큰 영향을 미칩니다. 국내에 출시하는 앱은 일반적으로 안드로이드를 우선 지원하고 이 후 iOS를 지원하는 형태로 진행하고 있습니다.

5. 지원 API 버전 결정
안드로이드 OS와 iOS는 각각 버전을 가지고 있습니다. 각 API 버전 별로 지원하는 네이티브 기능과 디자인 가이드가 있으니 어떤 버전으로 개발할지 결정해야 합니다. 지원 플랫폼이 결정되었다면 기능 리스트와 API 버전 별 지원 기능을 검토합니다.

안드로이드 버전 정보 – wikipeida
iOS 버전 정보 – wikipedia
6. 지원 디바이스 결정 (파편화 문제)
아이폰은 제조사가 Apple이며 종류가 다양하지 않습니다. 하지만 안드로이드 폰은 삼성, 엘지, 화웨이 등 여러 제조사가 있으며 기기 종류도 다양합니다. (스마트폰 제조사 목록)

이렇게 수많은 디바이스로 나눠져 있는 것을 파편화(Fragmentation)라고 합니다. 특히 전 세계 안드로이드 폰의 종류는 2만 개가 넘기 때문에 파편화 문제가 심각합니다. 제조사 별로 안드로이드 OS를 커스터마이징한 방식이 다르며, 화면 크기도 다양합니다.

일부 스마트폰에서 잘 동작하던 앱이 다른 스마트폰에서 에러가 나거나 화면이 깨지는 현상은 모두 파편화 문제 때문이라고 할 수 있습니다. 따라서 앱 개발을 진행한다면 (특히 안드로이드 앱) 반드시 지원 디바이스를 결정해야 합니다. 만약 외주 개발을 한다면 이 부분은 반드시 고객과 합의가 되어야 합니다. 그리고 지원 디바이스를 결정할 때 테블릿 지원 여부도 반드시 확인하시길 바랍니다.

지원 디바이스 종류는 스마트폰 시장 점유율 데이터를 기반으로 결정합니다. 그리고 디바이스 테스트 전에 테스트 용으로 확보할 수 있는 스마트폰 종류도 조사해두어야 합니다.

안드로이드 스마트폰 제품목록 – 나무위키
2018년 스마트폰 시장 점유율 자료
7. 프로젝트 기간 및 견적 도출 (앱 출시 후 운영 계획 및 비용까지 고려)
리드 개발자의 서버 아키텍처와 앱 아키텍처 설계와 지원 플랫폼, 지원 API 버전, 지원 디바이스 목록을 모두 문서화하여 정리합니다. 그리고 결정된 사항에 대해서는 고객 및 프로젝트 인원이 모두 합의해야 합니다. 앱 개발에 앞서 이런 부분들을 간과하면 프로젝트 비용이나 기간 이슈가 발생할 수 있습니다.

서버 개발은 서비스의 규모에 따라 천차 만별입니다. 따라서 전문가에 의해 자세한 견적을 도출해야 합니다. 앱 개발은 네이티브 앱의 경우 보통 1~3개월 정도 소요되며 모바일 웹으로 개발하는 경우에는 1개월 정도 개발 기간을 예상할 수 있습니다. 단, 기능이나 규모에 따라 이 부분 역시 달라질 수 있으므로 전문가에 의한 견적을 도출 하시길 바랍니다.

또한 프로젝트 기간 및 견적을 도출 할 때는 앱 출시 후 운영 인력과 계획도 미리 검토하여야 합니다. 프로젝트 기간과 비용 견적이 되었다면 본격적으로 앱 디자인을 진행합니다.

앱 디자인 
1. 디자인 가이드 검토
안드로이드와 iOS는 각각 디자인 가이드를 두고 있습니다. 디자인 가이드는 앱 디자인을 시작하기 전에 반드시 검토해야 합니다. 그리고 디자인 가이드를 준수해야 각 플랫폼에 맞는 앱 디자인을 할 수 있으며, 사용자의 익숙한 UX/UI 경험을 활용할 수 있습니다.

안드로이드 디자인 가이드

안드로이드 버전별 디자인 테마
안드로이드 버전 1.5 ~ 2.3 : 정의되지 않음
안드로이드 3.0 ~ 4.4 : Holo UI
안드로이드 5.0 ~ : Material Design (머터리얼 디자인)

iOS 디자인 가이드

2. 유사 어플리케이션의 UX/UI 사례 검토
유사한 기능을 제공하는 경쟁 어플리케이션의 UX/UI 사례를 검토하여야 합니다. 무에서 완전히 새로운 것을 창조하긴 어렵죠. 따라서 사례 조사를 통해 어떤 장점들을 가져오고 어떤 부분을 커스터 마이징 할 수 있는지 살펴봐야 합니다.

핀터레스트를 이용하면 쉽게 다양한 앱 UX/UI 사례를 찾아볼 수 있습니다.

3. 테마 선택
안드로이드와 iOS 에서는 스타일과 테마를 제공하고 있습니다. 기본으로 제공되는 스타일과 테마를 사용하면 사용자의 UX/UI 경험에 부합하면서도 빠르게 디자인을 진행할 수 있습니다.

그리고 테마 선택과 함께 앱의 주 색상과 보조 색상을 선택합니다. 주 색상을 파란색으로 했다면 중요한 부분에는 진한 파란색을 덜 중요한 부분에는 연한 파란색으로 표현할 수 있습니다.

4. 테마 커스텀 작업
테마 커스텀 작업을 통해 앱 만의 창의적인 디자인을 적용할 수 있습니다. 테마 커스텀 작업 역시 디자인 가이드 내에서 이루어져야 합니다.

참고로 안드로이드는 현재 Material Design을 적용하고 있습니다. 만약 안드로이드 5.0 미만 버전을 지원한다면 Support 라이브러리를 사용하여야 합니다. 하지만 라이브러리를 사용해도 완벽하게 호환되지는 않습니다. 이런 경우 http://romannurik.github.io/AndroidAssetStudio/ 를 이용하여 변화해보세요.

또한 안드로이드 테마 커스텀 작업을 할 때 다양한 GUI 컴포넌트 라이브러리를 활용할 수 있습니다. iOS 역시 커스텀 컨트롤 라이브러리가 오픈소스로 제공되고 있습니다. 단, 오픈 소스를 적용할 때는 꼭 라이센스를 확인하길 바랍니다.

API 서버 개발
1. 인터페이스 설계
API 서버를 사용하기로 했다면 서버와 앱이 주고 받을 데이터와 인터페이스를 설계해야 합니다. 앱 개발자와 서버 개발자가 별도로 있다면 협의를 통해 인터페이스를 정리합니다. 그리고 인터페이스 목록이 정리되면 서버 개발과 앱 개발을 진행합니다. 참고로 앱 개발을 클라이언트 개발 또는 프론트엔드 개발이라고 하며, 서버 개발을 백엔드 개발이라고도 합니다.

API 란 Application Programming Interface의 약자로 클라이언트 앱과 서버 간의 통신 규약입니다. API 방식에는 SOAP, RESTful이 있습니다. 요즘에는 대부분 RESTful로 개발합니다. RESTful은 REpresentational State Transfer + ful 을 의미합니다. 데이터 포맷은 JSON 이나 XML 을 사용할 수 있습니다.

RESTful API 연동정의서 샘플 참조

2. DB 설계
데이터를 저장하고 관리할  DB를 설계합니다. 참고로 DB에는 다양한 종류가 있습니다. 크게 RDB(=관계형 데이터베이스)와 NoSQL로 나뉘며 RDB에는 오라클, MySQL, MariaDB, PostgreSQL 등이 있습니다. NoSQL에는 Mongo DB, Couchbase, Cassandra, HBASE 등이 있습니다.

관리할 데이터에 맞게 테이블을 생성하고 정규화 작업을 합니다. 큰 규모의 프로젝트의 경우 DB 전문가인 DBA의 도움을 받을 수 있습니다.

3. 개발 환경 세팅 및 개발 진행
RESTful API 서버 프레임워크의 종류에는 구축형 솔루션인 Sinatra, Grape, Rails와 설치형 솔루션인 LoopBack, WordPress 가 있습니다. 클라우드 솔루션에는 Parse와 Firebase가 있습니다.

GraphQL, Falcor, JWT

앱 개발
개발 단계에서는 아이디어나 UX/UI의 큰 수정은 지양해야 합니다. 아이디어의 방향이 바뀌거나 UX/UI가 크게 바뀐다는 것은 거의 새로운 앱을 개발하는 수준이 될 수도 있기 때문입니다. 그리고 아주 작은 수정이라도 시스템을 크게 고쳐야 하는 경우 역시 지양해야 합니다. 마치 건물은 1cm 옆으로 옮기는 일과 같이 겉으로 보기엔 작은 수정이지만 실제로는 엄청난 공수가 들어갈 수도 있습니다. 따라서 본격적인 개발 단계에 들어가기 전에 기획과 디자인을 면밀히 하여야 합니다.

앱 개발은 최대한 빠르게 프로토타입을 만드는 것을 목표로 합니다. 프로토타입은 간단한 화면을 만들고 타겟 디바이스에 빌드된 앱을 올려 API 서버와 데이터를 주고 받는 모듈 하나를  빠르게 완성하고 테스트 합니다. 이를 통해 성능이나 다른 이슈가 있지는 확인해야 합니다.

앱 아키텍처에 따른 구체적인 개발 방법은 아래 링크를 확인하길 바랍니다.
