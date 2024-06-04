# Philosopheres

## 서브젝트
둥근 테이블에 앉아있는 한 명 이상의 철학자가 둥근 테이블에 앉아 먹거나 생각하거나 잠들거나, 이렇게 셋 중 하나의 행동을 한다.(한 번에 하나의 행동만을 한다)

 

둥근 테이블 한가운데에는 아주 큰 스파게티 그릇이 있으며, 철학자는 양쪽의 포크를 모두 사용하여 밥을 먹어야 한다.

 

모든 철학자는 서로 대화할 수 없으며(서로의 정보와 언제 죽는지를 알 수 없음), 수명 이상으로 굶는다면 철학자는 죽는다.

![image](https://github.com/Labin97/philo/assets/109407187/dd994ae0-0ab1-4111-b827-1c68e8698de0)

이 프로그램은 철학자의 수, 수명, 밥 먹는 시간, 잠자는 시간, [총 식사 횟수]를 인자로 받는다.

 

해당 옵션이 있다면 총 식사 횟수를 채우거나, 하나의 철학자라도 죽으면 10ms안에 프로그램이 종료되어야 한다.

 

철학자가 밥을 다 먹으면 포크를 내려놓고 잠들며, 잠을 다 자면 생각을 한다. 생각하는 도중에 밥을 먹을 수 있으면 밥을 먹는다.

 

철학자의 상태는 다음과 같은 형식으로 출력된다. 다른 철학자의 상태와 뒤엉키거나 섞인 상태로 출력이 되면 안 된다.

* timestamp_in_ms X has taken a fork
* timestamp_in_ms X is eating
* timestamp_in_ms X is sleeping
* timestamp_in_ms X is thinking
* timestamp_in_ms X died
철학자는 각각 한 개의 스레드로 구성이 되어있어야 하며 포크가 복제되지 않도록 포크를 뮤텍스로 보호해야 한다.


## 내용
프로세스 스레딩의 기본과 스레드를 만드는 방법을 익히고 뮤텍스가 무엇인가 배우는 프로젝트



- 쓰레드란 프로그램(프로세스) 실행의 단위이며하나의 프로세스는 **여러개의 쓰레드**로 구성이 가능하다.
- 하나의 프로세스를 구성하는 쓰레드들은 프로세스에 할당된 메모리, 자원 등을 공유한다.
- 프로세스와 같이 실행, 준비, 대기 등의 실행 상태를 가지며 실행 상태가 변할때마다 **쓰레드 문맥교환(context switching)**을 수행한다.
- 각 쓰레드별로 자신만의 **스택**과 **레지스터**를 가진다.
![image](https://github.com/Labin97/philo/assets/109407187/018c050e-b9fa-42ec-8b89-1b5de73692b9)


```
void	philo_eats(t_philo *philo, t_arg *arg)
{
	pthread_mutex_lock(&(arg->forks[philo->left]));
	action_print(arg, philo->id, "has taken a fork", 0);
	pthread_mutex_lock(&(arg->forks[philo->right]));
	action_print(arg, philo->id, "has taken a fork", 0);
	pthread_mutex_lock(&(arg->moniter));
	action_print(arg, philo->id, "is eating", 0);
	philo->last_eat_time = timestamp();
	(philo->eat_count)++;
	pthread_mutex_unlock(&(arg->moniter));
	smart_sleep(arg->time_to_eat, arg);
	pthread_mutex_unlock(&(arg->forks[philo->left]));
	pthread_mutex_unlock(&(arg->forks[philo->right]));
}
```

pthread_mutex_lock() 을 활용하여 쓰레드의 동시 접근을 막는다.


monitering 함수를 이용해서 전체적은 eat_count를 확인하고 조건 충족시 중지시킨다.
