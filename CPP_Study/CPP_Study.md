- [CPP Study](#cpp-study)
  - [Enum, Enum class 차이](#enum-enum-class-차이)
  - [const pointer](#const-pointer)
  - [동적할당](#동적할당)
  - [레퍼런스](#레퍼런스)
  - [구조체](#구조체)
  - [메모리](#메모리)
    - [프로그램 실행 순서](#프로그램-실행-순서)
  - [재귀함수](#재귀함수)
  - [문자열](#문자열)
  - [파일 입출력](#파일-입출력)
  - [클래스](#클래스)
    - [Uniform Initailizer](#uniform-initailizer)
  - [헤더 파일](#헤더-파일)
  - [변수 범위, 주기, 링크](#변수-범위-주기-링크)
  - [static 키워드](#static-키워드)
    - [](#)
  - [extern 키워드](#extern-키워드)

# CPP Study

* 몰랐거나 까먹기 쉬운 정보를 기록해놓는 문서

* 알아야 할 것 : 프로그래밍 설계패턴 컴포넌트 지향 프로그래밍, 함수 호출 규약, 메모리 단편화, 전처리기 동작, static 변수, 함수 메모리 접근방식
* 생성자 디폴트 매개변수는 선언, 정의부가 구분되었을 경우 선언시에 해준다. 정의할 때는 디폴트 매개변수를 적어주지 않아도 된다.
  * 생성자 제한으로 특정 객체에서만 생성가능하게 제한하는 방법?


## Enum, Enum class 차이

* `enum`은 옛날 cpp 버전 지원용

* `int` 형의 `enum` 변수를 자유롭게 사용하기 때문에 가독성 문제, 범위 지정문제가 발생하고, 개발자가 실수를 할 확률도 있기 때문에 좀 더 제약을 준 `enum class`가 나왔다.
* `enum`은 스코프 지정을 하지 않고 변수명을 그대로 상수마냥 사용할 수 있지만 `enum class`는 반드시 스코프를 사용해야 한다.
* `enum class` 는 클래스이기 때문에 선언 후 정의가 가능하다.
* 이제는 `enum class`를 사용하는 것이 맞다


## const pointer

* `const type*`, `type* const`, `const type* const` 세 가지가 있다.
  * `const type*` : 값 변경 불가능, 주소 변경 가능, 상수 참조 가능
  * `type* const` : 값 변경 가능, 주소 변경 불가능, 상수 참조 불가능
  * `const type* const` : 값 변경 불가능, 주소 변경 불가능
* `const type&` 를 생각하면 쉬움 (함수 파라미터로 자주 사용 -> 왜? -> 읽기 전용으로 쓰기 때문)
* 상수는 일반 포인터로 참조 불가능, `const pointer`를 사용해야 한다.

```cpp
	const int constNumber = 999;
	int	normalNumber = 1010;
	const int* pLeftConst = &constNumber;    // 상수 참조 가능
	pLeftConst = &normalNumber;              // 주소 변경(참조) 가능
	//*pLeftConst = 500;                     //! 값 변경(역참조) 불가능

	int* const pRightConst = &normalNumber;
	//int* const pRightConst = &constNumber; //! 상수 참조 불가능
	//pRightConst = &Number2;                //! 주소 변경 불가능
	*pRightConst = 9090;                     // 값 변경 가능

	const int* const pAllConst = &Number1;
	//pAllConst = &normalNumber;            //! 주소 변경 불가능
```


## 동적할당

* `crtdbg.h` 헤더 안의 매크로로 디버그 모드 시 메모리 릭을 확인할 수 있다.

```cpp
#include <crtdbg.h>
// 할당된 메모리 체크(alloc memory define) | 릭 체크 (leak check define)
_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
```


## 레퍼런스

* 포인터와 기능은 동일 -> c++ 버전의 포인터, 사용하기 쉬운 포인터

* 역참조 필요없음, 일종의 대리자 역할
* 참조 변경 불가능 -> `type* const`와 동일
  * `const type&`을 사용하면 읽기 전용 변수가 된다.
* 일반적인 객체가 아니기 때문에 저장공간을 반드시 필요로 하는 것은 아니다.
  * 컴파일러가 구현 중에 필요할 경우 알아서 공간을 만든다.
  * 메모리가 할당될 경우 포인터와 같은 크기이다.
  * `sizeof()`연산자 사용 불가


## 구조체

* `프로젝트 속성 -> 코드 생성 -> 구조체 멤버 맞춤` 옵션이 `기본값`으로 설정되어 있을 경우 구조체 내에서 용량이 가장 큰 변수의 크기를 기본값으로 잡아서 메모리를 할당하게 된다.
  * 왜 `1byte`로 설정하지 않는가? -> 컴퓨터 입장에서는 `4의 배수` 또는 `2^n` 단위로 메모리를 할당하는 것이 더 효율적이다.
* 멤버가 없더라도 최소바이트인 1바이트가 할당된다.
  * 변수를 선언하게 되면 메모리에 공간이 잡혀야 하므로 최소 바이트 수인 1바이트 공간을 차지하게 하여 변수를 잡아주는 것이다.
* 이제와서는 클래스와 구조체의 차이는 접근 제한자의 적용유무 밖에 없다.
  * 구조체 내에서도 함수를 선언할 수 있다.

```cpp
// 이 구조체의 크기는 24바이트이다. -> |A B       |    Number    | intNum C   | -> 8바이트가 기본단위가 되었다.
struct Test {
	char	A;
	char	B;
	double	doubleNum;
	int		intNum;
	char	C;
};

// 이 구조체의 크기는 1바이트이다.
struct Test1 {
};
```


## 메모리

* cpp의 메모리 영역은 크게 4가지로 나뉜다 : 스택, 데이터, 힙, 코드

  * 코드 : 유저가 작성한 코드가 저장되는 영역
    * 컴파일러가 작성한 코드를 바이너리코드(0, 1 로 구성된 코드)로 만든 뒤 실행파일을 생성한다.

    * 실행파일을 더블클릭해서 실행을 하게 되면 바이너리 코드가 메모리에 올라가는데(Load) 이 때 운영체제가 맨 처음 접근하는 곳이 코드 영역이다.
  * 데이터 : `전역변수`, `정적(static)변수`들의 메모리가 할당되는 영역
    * `전역변수` : 함수의 외부에 선언된 변수
  
    * `rodata`, `data`, `bss` 로 영역이 나뉜다.
      * `rodata` : 상수 키워드(const)로 선언되는 영역, 시스템에 사용된 각종 문자열들을 포함
      * `data` : 읽기, 쓰기가 가능한, 초기화된 전역변수들을 포함
      * `bss` : 초기화되지 않은 전역변수 또는 정적변수를 포함
    * 프로그램이 종료될 때 메모리에서 정리가 된다.
  * 힙 : 동적할당된 메모리가 할당되는 영역
    * 런타임 시 크기가 정해진다.
 
    * 선입선출(FIFO) 방식으로 가장 먼저 들어온 데이터가 가장 먼저 나간다.
    * 메모리의 낮은 주소에서 높은 주소로 할당된다.
    * 힙 영역이 스택 영역을 침범하는 경우를 `힙 오버플로우`라고 부른다.
  * 스택 : `매개변수` 혹은 `지역변수`들의 메모리가 할당되는 영역
    * `매개변수` : 함수의 인자

    * `지역변수` : 함수의 내부에서 선언된 변수
    * 컴파일 시 크기가 정해진다.
    * 후입선출(LIFO) 방식으로 가장 늦게 들어온 데이터가 가장 먼저 나간다.
    * 메모리의 높은 주소에서 낮은 주소로 할당된다.
    * 왜 스택이 쌓일수록 메모리 주소값이 낮아지도록 설계했나?
      * 스택메모리가 커널 영역의 반대방향으로 쌓이기 때문에 커널의 영역을 침범하지 않는다.

      * 힙 영역과 공유 라이브러리 영역을 가운데 두고 마주보는 형태이기 때문에 메모리를 최대한 활용할 수 있다.
    * 스택 영역이 힙 영역을 침범하는 경우를 `스택 오버플로우`라고 부른다.

![32bit 운영체제 메모리 구조](img/memory.jpg)

  
### 프로그램 실행 순서

![](img/execution.png)


## 재귀함수

* 특징
  * 무한 루프에 빠지지 않기 위해 일정한 탈출 조건이 있어야 한다.(base case)
  
  * 코드를 단순화할 수 있다.
  * 호출 시마다 스택 공간을 이용하므로 무리하게 호출하면 스택 오버플로우가 발생한다.
  * 호출 횟수가 스택의 남은 공간과 재귀 함수의 지역 변수 사이즈에 따라 달라진다.
  * 디버깅 및 실행 흐름을 파악하기 힘들다.
* 함수의 인자로 결과값만을 넘겨주는 `꼬리재귀` 함수가 있다.
  * 재귀 호출 이후 추가적인 연산을 하지 않아야 한다.

  * 컴파일러 최적화 옵션을 사용하면 컴파일러가 재귀함수를 선형으로 처리한다.
  * 최적화를 사용하려면 `프로젝트 속성 -> 최적화 -> 속도 우선 최적화` 를 체크해야 한다. (`Tail Call Optimization`이 포함된 최적화)
    * 컴파일러가 자체적으로 `do while`로 해석하게 된다.
* 읽기 좋은 글 : [하노이의 탑](https://shoark7.github.io/programming/algorithm/tower-of-hanoi)

```cpp
// 일반 재귀 함수
int factorial(int number) {
  if (number == 1)
    return 1;

  return number * factorial(number - 1);
}

// 꼬리 재귀 함수
int factorialTail(int number, int result = 1) {
  if (number == 1)
    return result;

  return factorialTail(number - 1, result * number);
}


// 컴파일러가 해석하는 꼬리 재귀 함수
int factorialTail(int number) {
  int result = 1;
  do {
    if (number == 1)
      return result;
    result = result * number;
    number = number - 1;
  } while(true);
}
```

## 문자열

* `memset` 함수는 1바이트 단위로 값을 채워넣기 때문에 주의해서 사용해야 한다.

```cpp
	// 1번인자 : 메모리 주소
	// 2번인자 : 채워줄 값
	// 3번인자 : 채워줄 메모리 크기
	memset(NumberArray, 1, sizeof(int) * 10);
  // -> 각 배열엔 1이 아닌 16,843,009가 들어가게 된다 (2^24 + 2^16 + 2^8 + 1)
```

* `memcpy` 함수와 `std::copy` 함수의 비교 시 미묘하게 `memcpy` 가 빠르지만 iterator 등을 생각했을 때 유연한 적용은 `std::copy`가 좋다.
* `C pointer` 타입은 `memcpy`, 나머지는 `std::copy` 를 사용하자.

## 파일 입출력

* 모드의 종류
	* `w, r, a, wt, rt, at, wb, rb, ab, r+, w+, a+`
    * w : 쓰기, 이미 있으면 덮어씀
  
    * r : 읽기, 파일이 없으면 에러가 발생. File스트림이 nullptr로 들어오게 된다.
    * a : 파일이 있으면 해당 파일을 연다. 파일이 있다면 해당파일의 가장 뒤에 새로 추가해서 넣어준다. 파일이 없으면 새로 만들어준다.
    * t, b : 텍스트 파일, 바이너리 파일을 만들어준다.
    * r+ : 파일이 있으면 읽기 쓰기 둘다 가능하게 열어준다. 파일이 없으면 에러를 발생한다.
    * w+ : 파일이 있으면 읽기 쓰기 둘다 가능하게 열어준다. 파일이 없으면 새로 만들어준다.
    * a+ : 파일이 있으면 맨 끝부터 읽고 쓰기가 가능하다. 파일이 없으면 새로 만들어준다.

```cpp
	FILE* File = nullptr;
	fopen_s(&File, "Test.txt", "rt");

	if (File) {
		char	Line[256] = {};

		// 문자열을 읽어온다. 한줄을 읽어오는 기능인데 개행문자까지 읽는다.
    // 읽은 뒤 뒤에 `\0`을 넣는다. 즉 문자는 255개(n - 1개) 까지만 읽을 수 있다.
    // `test\nstring` 이라는 문자열을 파일에 넣고 읽으면 첫번째 Line값은 `test\n`이 되고 strlen() 함수 사용 시 5가 나온다.
		fgets(Line, 256, File);

		std::cout << Line;

		while (true) {
			fgets(Line, 256, File);

			if (feof(File))
				break;

			std::cout << Line;
		}

		fclose(File);
	}
```

## 클래스

* 구조체처럼 여러 변수를 모아두고 하나로 묶어서 사용할 수 있는 기능을 제공한다.
  
* C++에서는 객체를 만들기 위한 수단으로 클래스를 제공한다.
* 캡슐화 : 여러 변수와 함수를 모아서 하나의 클래스 혹은 구조체로 만들어주는 것을 말한다.
* 은닉화 : 클래스에서 제공하는 멤버를 외부에 공개하는 수준을 정하는 것을 말한다.
* `friend CTestClass` : `CTestClass` 에게 접근허가를 내어준다. `CTestClass` 는 이 클래스의 `private` 데이터에 `public` 처럼 접근이 가능하다.
  * 현재 클래스에서는 `CTestClass`의 `private` 데이터에 접근할 수 없다. 단방향임.

### [Uniform Initailizer](https://modoocode.com/286)

* `class A` 가 있고 인자를 받지 않는 생성자를 가지고 있을 때, `A a();` 라인은 객체 `a`를 만드는 것이 아닌 `A`를 리턴하고 인자를 받지 않는 함수 `a` 를 정의한 것으로 간주한다.
  * CPP 컴파일러는 함수의 정의처럼 보이는 것들을 모두 함수의 정의로 해석한다.

* ()가 함수를 정의하는 데에도 사용되고, 객체의 생성자를 호출하는 데에도 사용되기 때문에 `c++11`부터 도입되었다.
* 생성자 호출에 () 대신 {} 를 사용하면 된다.
* 암시적 타입 변환을 사용하지 못한다.
* 함수 리턴 시 생성자의 객체 타입을 적지 않아도 된다. (리턴 타입을 보고 추론해준다)
* 생성자에 배열처럼 리스트를 집어넣을 수 있다.(`initalizer_list`)
  * 생성자 오버로딩 시 해당 함수가 최우선이 되어 예기치 못한 에러가 발생할 수 있다.

  * `auto`로 타입을 지정한다면 아래와 같은 상황에서 전부 `std::initializer_list<int>` 타입으로 추론되기 때문에 `c++17`부터 두 가지 형태로 구분해서 추론하도록 변경되었다.
    * `auto x = {arg1, arg2...}` 형태의 경우 arg1, arg2 ... 들이 모두 같은 타입이라면 x 는 `std::initializer_list<T>` 로 추론

    * `auto x {arg1, arg2, ...}` 형태의 경우 만일 인자가 단 1 개라면 인자의 타입으로 추론되고, 여러 개일 경우 오류를 발생
  * 문자열 `auto` 사용 시 `initializer_list<const char*>`로 추론되는 상황을 방지하기 위해 `c++14`에서 추가된 리터럴 연산자를 사용하는게 좋다.
  
```cpp
auto a = {1};     // 첫 번째 형태이므로 std::initializer_list<int>
auto b{1};        // 두 번째 형태 이므로 그냥 int
auto c = {1, 2};  // 첫 번째 형태이므로 std::initializer_list<int>
auto d{1, 2};     // 두 번째 형태 인데 인자가 2개 이상이므로 컴파일 오류

using namespace std::literals;  // 문자열 리터럴 연산자를 사용하기 위해 추가해줘야함.
auto list = {"a", "b", "cc"};   // initializer_list<const char*>
auto list = {"a"s, "b"s, "c"s}; // initializer_list<std::string>
```

## 헤더 파일

* 순환 참조 : 서로의 헤더 파일을 `include` 하는 상태. 무조건 피해야 한다.
* 이것을 피하기 위해 `전방 선언` 을 한다.


## [변수 범위, 주기, 링크](https://www.learncpp.com/cpp-tutorial/scope-duration-and-linkage-summary/)

* `Scope` : 식별자의 `scope`는 소스 파일 내에서 어디까지 접근할 수 있는가를 결정한다.
  * `block(local) scope` 

    * 선언된 블록 내에서만 접근 가능하다.

    * 지역변수 (`local variables`), 매개변수 (`function parameter`), 블록 내 유저 정의 자료형 (`user-defined type definitions declared inside a block`)
  * `global(file) scope`
    * 소스 파일의 모든 위치에서 접근 가능하다.

    * 전역변수 (`global variables`), 일반함수 (`normal function`), 유저 정의 자료형 (`user-defined type definitions declared inside a namespace or in the global scope`)

* `Duration` : 변수의 `duration`은 언제 생성되고 소멸되는지를 결정한다.
  * `automatic duration`
    * 선언(`definition`) 시점에 생성, 해당 변수가 포함된 블록이 끝날 때 파괴된다.

    * 지역변수 (`local variables`), 매개변수 (`function parameter`)
  * `static duration`
    * 프로그램 시작 시 생성, 프로그램이 끝날 때 파괴된다.
  
    * 전역변수 (`global variables`), 정적지역변수 (`static local variables`)
  * `dynamic duration`
  
    * 프로그래머가 요청 시 생성 혹은 파괴된다.
  
    * 동적 할당 변수 (`dynamically allocated variables`)

* `Linkage` : 식별자의 `linkage`는 같은 이름의 식별자가 여러 개 선언되었을 때 같은 식별자를 참조하는가 다른 식별자로 인식하는가를 결정한다.
  * `no linkage`
    * 자기 자신만을 참조한다.

    * 지역변수 (`local variables`), 블록 내 유저 정의 자료형 (`user-defined type definitions declared inside a block`)
  * `internal linkage`

    * 선언된 소스 파일 어디에서나 접근이 가능하다.

    * 정적전역변수 (`static global variables`), 상수전역변수 (`const global variables`), 정적함수 (`static function`), 유저 정의 자료형
      
  * `external linkage`
    * 선언된 소스 파일 + 다른 파일에서도 접근이 가능하다.

    * 일반함수 (`normal function`), 비상수 전역변수 (`non-const global variables`), 외부전역변수 (`extern global variable`), 인라인 상수전역변수 (`inline const global variables`)

* 식별자(identifier) : 변수(variable), 함수(function), 클래스(class)를 지칭할 때 사용되는 이름

## static 키워드

### 

* 참고 : https://ansohxxn.github.io/cpp/chapter8-10/

## extern 키워드

* 