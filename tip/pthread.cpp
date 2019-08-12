int pthread_create(pthread_t *thread, const pthread_attr_t *attr,
                   void *(*start_routine)(void *), void *arg);
 첫 번째 아규먼트인 thread 는 쓰레드가 성공적으로 생성되었을때 생성된 쓰레드를 식별하기 위해서 사용되는 쓰레드 식별자이다. 
 두 번째 아규먼트인 attr 은 쓰레드 특성을 지정하기 위해서 사용하며, 기본 쓰레드 특성을 이용하고자 할경우에 NULL 을 사용한다. 
 세 번째 아규먼트인 start_routine는 분기시켜서 실행할 쓰레드 함수이며, 
 네 번째 아규먼는인 arg는 쓰레드 함수의 인자이다.

성공적으로 생성될경우 0을 리턴한다.                   

int pthread_join(pthread_t th, void **thread_return);
    
첫 번째 아규먼트 th는 기다릴(join)할 쓰레드 식별자이다. 
두 번째 아규먼트 thread_return은 쓰레드의 리턴(return) 값이다. 
thread_return 이 NULL 이 아닐경우 해다 포인터로 쓰레드 리턴 값을 받아올수 있다.

int pthread_mutex_init(pthread_mutex_t * mutex, 
           const pthread_mutex_attr *attr); 
    
mutex 는 여러개의 쓰레드가 공유하는 데이타를 보호하기 위해서 사용되는 도구로써, 
보호하고자 하는 데이타를 다루는 코드영역을 단지 한번에 하나의 쓰레드만 실행가능 하도록 하는 방법으로 공유되는 데이타를 보호한다. 
이러한 코드영역(하나의 쓰레드만 점유가능한)을 critical section 이라고 하며, mutex 관련 API 를 이용해서 관리할수 있다.

pthread_mutex_init 는 mutex 객체를 초기화 시키기 위해서 사용한다. 
첫번째 인자로 주어지는 mutex 객체 mutex를 초기화시킨다. 
두번째 인자인 attr 를 이용해서 mutex 특성을 변경할수 있다. 
기본 mutex 특성을 이용하기 원한다면 NULL 을 사용하면 된다.

mutex 특성(종류) 에는 "fast", "recurisev", "error checking" 의 종류가 있으며, 기본으로 "fast" 가 사용된다.

int pthread_mutex_lock(pthread_mutex_t *mutex);


pthread_mutex_lock 는 critcal section 에 들어가기 위해서 mutex lock 을 요청한다. 
만약 이미 다른 쓰레드에서 mutex lock 를 얻어서 사용하고 있다면 다른 쓰레드에서 mutex lock(뮤텍스 잠금) 을 해제할때까지(사용할수 있을때까지) 
블럭 된다.

만약 다른 어떤 쓰레드에서도 mutex lock 을 사용하고 있지 않다면, 즉시 mutex lock 을 얻을수 있게 되고 critcal section 에 진입하게 된다. 
critcal section 에서의 모든 작업을 마쳐서 사용하고 있는 mutex lock 이 더이상 필요 없다면 pthread_mutex_unlock 를 호출해서 mtuex lock 를 되돌려준다.

int pthread_mutex_unlock(pthread_mutex_t *mutex); 
    
critical section 에서의 모든 작업을 마치고 mutex lock 을 돌려주기 위해서 사용한다. 
pthread_mutex_unlock 를 이용해서 mutex lock 를 되돌려주면 다른 쓰레드에서 mutex lock 를 얻을수 있는 상태가 된다.

int pthread_cond_init(pthread_cond_t *cond, 
                    const pthread_cond_attr *attr);
    
pthread_cond_init는 조견변수 (condition variable)cond를 초기화하기 위해서 사용한다.
attr 를 이용해서 조건변수의 특성을 변경할수 있으며, NULL 을 줄경우 기본특성으로 초기화된다.

조건변수 cond는 상수 PTHREAD_COND_INITIALIZER 을 이용해서도 초기화 할수 있다. 즉 다음과 같은 2가지 초기화 방법이 존재한다.

pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
or
pthread_cond_init(&cond, NULL);

int pthread_cond_signal(pthread_cond_t *cond);
    
조건변수 cond에 시그날을 보낸다. 시그날을 보낼경우 cond에서 기다리는(wait) 쓰레드가 있다면 쓰레드를 깨우게 된다(봉쇄가 풀림). 
만약 조건변수 cond를 기다리는 쓰레드가 없다면, 아무런 일도 일어나지 않게되며, 여러개의 쓰레드가 기다리고 있다면 그중 하나의 쓰레드에게만 전달된다.
이때 어떤 쓰레드에게 신호가 전달될지는 알수 없다.

int pthread_cond_broadcast(pthread_cond_t *cond);
    
조건변수 cond에서 기다리는(wait) 모든 쓰레드에게 신호를 보내서, 깨운다는 점을 제외하고는 pthread_cond_signal과 동일하게 작동한다.

int pthread_cond_wait(pthread_cond_t cond, pthread_mutex_t *mutex); 
    
조건변수 cond를 통해서 신호가 전달될때까지 블럭된다. 만약 신호가 전달되지 않는다면 영원히 블럭될수도 있다. 
pthread_cond_wait는 블럭되기 전에 mutex 잠금을 자동으로 되돌려준다.



