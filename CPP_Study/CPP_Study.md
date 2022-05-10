- [용어 정리](#용어-정리)
- [객체 지향 프로그래밍](#객체-지향-프로그래밍)
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
  - [생성자와 소멸자](#생성자와-소멸자)
  - [Initialization](#initialization)
    - [Non-Static Data Member Initialization (NSDMI, 비정적 데이터 멤버 초기화)](#non-static-data-member-initialization-nsdmi-비정적-데이터-멤버-초기화)
  - [Uniform Initailizer](#uniform-initailizer)
  - [Member Access Control (접근 지정자)](#member-access-control-접근-지정자)
  - [헤더 파일](#헤더-파일)
- [상속과 [가상 함수](https://docs.microsoft.com/en-us/cpp/cpp/virtual-functions?view=msvc-170)](#상속과-가상-함수)
  - [상속 (`Inheritance`)](#상속-inheritance)
  - [가상 함수 (`Virtual Function`)](#가상-함수-virtual-function)
  - [Abstract class, Pure Virtual Function (추상클래스, 순수 가상 함수)](#abstract-class-pure-virtual-function-추상클래스-순수-가상-함수)
  - [Virtual Function Table (가상함수 테이블)](#virtual-function-table-가상함수-테이블)
  - [Virtual Table Table](#virtual-table-table)
- [변수 범위, 주기, 링크](#변수-범위-주기-링크)
- [키워드](#키워드)
  - [this 키워드](#this-키워드)
  - [static 키워드](#static-키워드)
  - [extern 키워드](#extern-키워드)
  - [virtual 키워드](#virtual-키워드)
  - [inline 키워드](#inline-키워드)
  - [constexpr 키워드](#constexpr-키워드)
- [연산자](#연산자)
  - [sizeof 연산자](#sizeof-연산자)
  - [캐스팅 연산자](#캐스팅-연산자)
  - [범위 지정 연산자](#범위-지정-연산자)
  - [연산자 오버로딩](#연산자-오버로딩)
- [함수](#함수)
  - [멤버 함수와 가상 함수 예제](#멤버-함수와-가상-함수-예제)
  - [함수 포인터](#함수-포인터)
- [템플릿](#템플릿)

---


## CPP Study
  - 몰랐거나 까먹기 쉬운 정보를 기록해놓는 문서

  - 알아야 할 것 : 프로그래밍 설계패턴 (컴포넌트 지향 프로그래밍, 데이터 지향 프로그래밍, 등등), 함수 호출 규약, 메모리 단편화, 전처리기 동작, static 변수, 함수 메모리 접근방식
  - 생성자 디폴트 매개변수는 선언, 정의부가 구분되었을 경우 선언시에 해준다. 정의할 때는 디폴트 매개변수를 적어주지 않아도 된다.
    - 생성자 제한으로 특정 객체에서만 생성가능하게 제한하는 방법?
  - 접근제한자는 컴파일 타임에만 고려되나? 코드작성을 위해서 만들어진건가?

---
# 용어 정리

  - 이름 : 무언가를 지칭하는 단어. 가장 큰 개념

  - 간단한 포함관계 
    - 실체가 없는 것 : 이름 > 식별자 > 키워드
  
    - 실체가 있는 것 : 엔터티 > 객체, 타입

  - ### [`identifier` (식별자)](https://docs.microsoft.com/en-us/cpp/cpp/identifiers-cpp?view=msvc-170)
    - 이름들을 지칭하는 일련의 문자열
  
    - 코드에 적힌 예약되지 않은 이름들은 전부 식별자
  
  - ### [`keyword` (키워드)](https://docs.microsoft.com/en-us/cpp/cpp/keywords-cpp?view=msvc-170)
    - 특별한 의미로 사용하기 위해 언어가 예약한 식별자. 식별자로 사용할 수 없다.
  
    - 두 개의 연속된 밑줄을 포함하는 식별자(ex, `__stdcall`)는 컴파일러 구현을 위해 예약된 것이다.
      - `__cdecl` 키워드는 밑줄 없이 사용이 가능하다.
  - ### `entity` (엔터티, 개체)
    - 데이터 또는 정보들의 집합을 포함하는 어떤 메모리 (또는 레지스터)
 
    - 식별자로 네이밍 한다. (identifier is just a name for some entity)
    - 종류 : `values`, `objects`, `references`, `enumerators`, `types`, `functions`, `class members`, `namespaces`, `templates(specializations 포함)`, `structured bindings(C++17)`, `parameter packs`
    - 전처리기인 매크로 (`macro`)는 엔터티가 아니다.
  
  - ### [`types` (타입, 유형)](https://en.cppreference.com/w/cpp/language/type)
    - 무언가의 종류를 나타내기 위해 사용하는 엔터티
  
    - `객체, 참조, 함수 및 식`이 가지는 **속성**이며, 엔터티에 허용되는 연산을 제한하고 비트 시퀀스에 의미를 부여한다.
  
  - ### [`object` (객체)](https://en.cppreference.com/w/cpp/language/object)
    - 공식적인 정의는 **어떠한 저장 영역(`any region of storage`)** 이다.
  
    - `C++` 에서 `object` 와 `instance` 는 동의어다.
      - `instance` 는 공식적으로 정의된 용어가 아니지만 `instance of type X` 이런식으로 객체를 표현한다.
    - `변수(variable)` 는 선언을 완료한 [정적 데이터 멤버](https://en.cppreference.com/w/cpp/language/data_members#Member_initialization)인 객체 또는 참조를 의미한다.
      - 여기서 정적 데이터는 키워드인 `static`의 의미가 아닌 정해진(`fixed`)을 뜻한다.
    - 아래의 속성들을 가진다.
      - 크기 (sizeof)
      - [정렬 필요조건 (alignment requirement)](https://en.cppreference.com/w/cpp/language/object#Alignment)
        - 객체를 생성할 수 있는 연속된 주소들 사이의 바이트 수 (배열은 타입크기만 확인)
  
        - 스칼라 타입 중 가장 크기가 큰 타입의 바이트 수와 동일하다.
        - `바이트 패딩(byte padding)` 시의 기준 크기보다 작거나 같다.
      - [저장 기간 (storage duration)](https://en.cppreference.com/w/cpp/language/storage_duration)
      - [수명 (lifetime)](https://en.cppreference.com/w/cpp/language/lifetime)
      - 타입
      - 값
      - 이름 (optional)

  - ### [선언(declaration)과 정의(definition)](https://docs.microsoft.com/en-us/cpp/cpp/declarations-and-definitions-cpp?redirectedfrom=MSDN&view=msvc-170)
    - 둘의 가장 큰 차이점은 **메모리를 할당하는가** 이다.
 
    - 메모리를 할당하지 않고 식별자만 알려준다면 `선언`, 메모리가 할당된 식별자는 `정의`
    - 선언(`declaration`)
      - 엔터티의 타입과 기타 다른 특성에 대한 정보를 가지고 엔터티에 고유한 이름을 지정하는 것
      - 정의하기 전에 사용하기 위해 선언하는 것을 `전방 선언(forward declaration)` 이라고 한다.
      - 전방 선언은 여러번 가능하며, 컴파일 시점에서 구현부 확인이 되지 않으면 에러가 발생한다. (`.cpp` 파일에 `#include` 전처리기를 통한 헤더 코드의 복사가 이루어져야 한다.)
    - 정의(`definition`)
      - 엔터티가 프로그램에서 사용될 때 컴파일러가 기계어 코드를 생성하는데 필요한 모든 정보를 제공하는 것
      - 클래스 작성은 선언과 동시에 정의를 하는 것과 같다. (멤버함수는 선언과 정의를 분리할 수 있다)

  - ### [Built-in(fundamental) Types](https://docs.microsoft.com/en-us/cpp/cpp/fundamental-types-cpp?view=msvc-170)
    - `C++` 언어 표준에서 지정되어 컴파일러에서 기본 제공되는 타입
  
    - 정수형(`integral`), 부동소수점, `void` 세 가지 메인 카테고리로 나뉜다.

  - ### [POD(Plain Old Data) type](https://en.cppreference.com/w/cpp/named_req/PODType)
    - C언어와 호환이 가능한 타입을 의미한다.
  
    - `C++20`부터 좀 더 정교한 타입 요구사항들로 대체되었다.(`Trivial Type` 등등)
  - ### [cv type qualifiers](https://en.cppreference.com/w/cpp/language/cv)
    - 상수(`const`), 휘발성(`volatile`) 한정자를 의미한다.
  - 참고 
    - [Basic Concept of C++ Language](https://en.cppreference.com/w/cpp/language/basic_concepts) 
    - [identifier vs keyword](https://stackoverflow.com/questions/7279227/c-what-is-the-difference-between-identifier-keyword-name-and-entity)
    - [entity vs identifier](https://stackoverflow.com/questions/13542905/whats-the-difference-between-entity-and-identifier)
    - [difference between object and instance](https://stackoverflow.com/questions/22206044/difference-between-object-and-instance-c)
    - [Class and Objects](https://isocpp.org/wiki/faq/classes-and-objects#overview-object)
    - [is_pod Class](https://docs.microsoft.com/en-us/cpp/standard-library/is-pod-class?view=msvc-170)
    - [Data Type Ranges](https://docs.microsoft.com/en-us/cpp/cpp/data-type-ranges?view=msvc-170)

---
# 객체 지향 프로그래밍

  - TODO
  - 추상화 : 
  - 캡슐화 : 부품이 너무 많아. 하나로 묶어야겠어. 하지만 어떻게 만드는지는 안보여줄거야.(모양은 대충 알수있지)
    - `private` 멤버함수의 함수 포인터 접근은 캡슐화에 위배된다.
  - 은닉화(캡슐화보다 구체적인 개념) : 넌 이 로직의 결과값만 알 수 있어. 필요한 부분만 주니 얼마나 좋아?
  - 상속성 : 니 기능 나도 좀 쓰자
  - 다형성 : 같은 종류이지만 하는 일이 달라

---
# Enum, Enum class 차이

  - `enum`은 옛날 cpp 버전 지원용

  - `int` 형의 `enum` 변수를 자유롭게 사용하기 때문에 가독성 문제, 범위 지정문제가 발생하고, 개발자가 실수를 할 확률도 있기 때문에 좀 더 제약을 준 `enum class`가 나왔다.
  - `enum`은 스코프 지정을 하지 않고 변수명을 그대로 상수마냥 사용할 수 있지만 `enum class`는 반드시 스코프를 사용해야 한다.
  - `enum class` 는 클래스이기 때문에 선언 후 정의가 가능하다.
  - 이제는 `enum class`를 사용하는 것이 맞다


---
# const pointer

  - `const type*`, `type* const`, `const type* const` 세 가지가 있다.
    - `const type*` : 값 변경 불가능, 주소 변경 가능, 상수 참조 가능
    - `type* const` : 값 변경 가능, 주소 변경 불가능, 상수 참조 불가능
    - `const type* const` : 값 변경 불가능, 주소 변경 불가능
  - `const type&` 를 생각하면 쉬움 (함수 파라미터로 자주 사용 -> 왜? -> 읽기 전용으로 쓰기 때문)

  - 상수는 일반 포인터로 참조 불가능, `const pointer`를 사용해야 한다.
  
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


---
# 동적할당

  - `crtdbg.h` 헤더 안의 매크로로 디버그 모드 시 메모리 릭을 확인할 수 있다.

```cpp
  #include <crtdbg.h>
  // 할당된 메모리 체크(alloc memory define) | 릭 체크 (leak check define)
  _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
```


---
# 레퍼런스

  - 포인터와 기능은 동일 -> c++ 버전의 포인터, 사용하기 쉬운 포인터
    - 초기화 시 필요로 하는 값은 다름. 포인터는 주소값을 사용하고, 레퍼런스는 해당 객체를 사용함 

  - 역참조 필요없음, 일종의 대리자 역할, 일반 변수랑 동일하게 사용하면 됨
  - 참조 변경 불가능 -> `type* const`와 동일
    - `const type&`을 사용하면 읽기 전용 변수가 된다.
  - 일반적인 객체가 아니기 때문에 저장공간을 반드시 필요로 하는 것은 아니다.
    - 컴파일러가 구현 중에 필요할 경우 알아서 공간을 만든다.
    - 메모리가 할당될 경우 포인터와 같은 크기이다.
    - `sizeof()`연산자 사용 불가


---
# 구조체

  - 바이트 패딩(`byte padding`)이라는 기법을 사용한다. (컴파일러마다 있을수도, 없을수도 있지만 MSVC에는 있다.)
    - 클래스(구조체)에 바이트를 추가해 CPU 접근에 부하를 덜어주는 기법
      - 같은 변수에 두 번 접근하는 것을 방지해준다.
 
    - `프로젝트 속성 -> 코드 생성 -> 구조체 멤버 맞춤` 옵션이 `기본값`으로 설정되어 있을 경우 구조체 내에서 용량이 가장 큰 변수의 크기를 기본값으로 잡아서 메모리를 할당하게 된다.
    - `스칼라 타입` 변수만 고려한다. 구조체, 클래스 타입 변수는 고려대상이 아님.
    - 왜 `1byte`로 설정하지 않는가? -> 컴퓨터 입장에서는 `4의 배수` 또는 `2^n` 단위로 메모리를 할당하는 것이 더 효율적이다.
 
  - 멤버가 없더라도 최소바이트인 1바이트가 할당된다.
    - 변수를 정의하게 되면 메모리에 공간이 잡혀야 하므로 최소 바이트 수인 1바이트 공간을 차지하게 하여 변수를 잡아주는 것이다. (객체를 구분하기 위해)
  - 이제와서는 클래스와 구조체의 차이는 접근 제한자의 적용유무 밖에 없다.
    - 구조체 내에서도 함수를 선언할 수 있다.
  - 참고
    - [바이트 패딩](https://supercoding.tistory.com/37)
    - [align](https://docs.microsoft.com/ko-kr/previous-versions/visualstudio/visual-studio-2010/83ythb65(v=vs.100)?redirectedfrom=MSDN)

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


---
# 메모리

  - cpp의 메모리 영역은 크게 4가지로 나뉜다 : 스택, 데이터, 힙, 코드

  - **텍스트 or 코드** : 유저가 작성한 코드가 저장되는 영역
    - 
    - 컴파일러가 작성한 코드를 바이너리코드(0, 1 로 구성된 코드)로 만든 뒤 실행파일을 생성한다.
  
    - 실행파일을 더블클릭해서 실행을 하게 되면 바이너리 코드가 메모리에 올라가는데(Load) 이 때 운영체제가 맨 처음 접근하는 곳이 코드 영역이다.
    - 읽기 전용이다.
  - **데이터** : `전역변수`, `정적(static)변수`들의 메모리가 할당되는 영역
    - 
    - `전역변수` : 함수의 외부에 선언된 변수
  
    - `rodata`, `data`, `bss` 로 영역이 나뉜다.
      - `rodata` : 상수 키워드(const)로 선언되는 영역, 시스템에 사용된 각종 문자열들을 포함. 읽기 전용이지만 데이터 영역에 존재한다.
      - `data` : 읽기, 쓰기가 가능한, 초기화된 전역변수 또는 정적변수를 포함
      - `bss(block stated symbol)` : 초기화되지 않았거나 0으로 초기화하는 전역변수 또는 정적변수를 포함
    - 프로그램이 종료될 때 메모리에서 정리가 된다.
  - **힙** : 동적할당된 메모리가 할당되는 영역
    - 
    - 런타임 시 크기가 정해진다.
 
    - 선입선출(FIFO) 방식으로 가장 먼저 들어온 데이터가 가장 먼저 나간다.
    - 메모리의 낮은 주소에서 높은 주소로 할당된다.
    - 힙 영역이 스택 영역을 침범하는 경우를 `힙 오버플로우`라고 부른다.
  - **스택** : `매개변수` 혹은 `지역변수`들의 메모리가 할당되는 영역
    - 
    - `매개변수` : 함수의 인자
    
    - `지역변수` : 함수의 내부에서 선언된 변수
    - 컴파일 시 크기가 정해진다.
    - 후입선출(LIFO) 방식으로 가장 늦게 들어온 데이터가 가장 먼저 나간다.
    - 메모리의 높은 주소에서 낮은 주소로 할당된다.
    - 왜 스택이 쌓일수록 메모리 주소값이 낮아지도록 설계했나?
      - 스택메모리가 커널 영역의 반대방향으로 쌓이기 때문에 커널의 영역을 침범하지 않는다.

      - 힙 영역과 공유 라이브러리 영역을 가운데 두고 마주보는 형태이기 때문에 메모리를 최대한 활용할 수 있다.
    - 스택 영역이 힙 영역을 침범하는 경우를 `스택 오버플로우`라고 부른다.


![32bit 운영체제 메모리 구조](img/memory.jpg)

  - 참고
    - [SPARC Assembler Memory Map](https://shinluckyarchive.tistory.com/159)
    - [데이터 영역과 .bss 영역의 차이](https://kldp.org/node/122255)
    - [정적 지역 변수 원리](https://dataonair.or.kr/db-tech-reference/d-lounge/technical-data/?mod=document&uid=235959)

## 프로그램 실행 순서

![](img/execution.png)



---
# 재귀함수

  - 특징
    - 무한 루프에 빠지지 않기 위해 일정한 탈출 조건이 있어야 한다.(base case)
    
    - 코드를 단순화할 수 있다.
    - 호출 시마다 스택 공간을 이용하므로 무리하게 호출하면 스택 오버플로우가 발생한다.
    - 호출 횟수가 스택의 남은 공간과 재귀 함수의 지역 변수 사이즈에 따라 달라진다.
    - 디버깅 및 실행 흐름을 파악하기 힘들다.
  - 함수의 인자로 결과값만을 넘겨주는 `꼬리재귀` 함수가 있다.
    - 재귀 호출 이후 추가적인 연산을 하지 않아야 한다.

    - 컴파일러 최적화 옵션을 사용하면 컴파일러가 재귀함수를 선형으로 처리한다.
    - 최적화를 사용하려면 `프로젝트 속성 -> 최적화 -> 속도 우선 최적화` 를 체크해야 한다. (`Tail Call Optimization`이 포함된 최적화)
      - 컴파일러가 자체적으로 `do while`로 해석하게 된다.
  - 읽기 좋은 글 : [하노이의 탑](https://shoark7.github.io/programming/algorithm/tower-of-hanoi)

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


---
# 문자열

  - `memset` 함수는 1바이트 단위로 값을 채워넣기 때문에 주의해서 사용해야 한다.

```cpp
  // 1번인자 : 메모리 주소
  // 2번인자 : 채워줄 값
  // 3번인자 : 채워줄 메모리 크기
  memset(NumberArray, 1, sizeof(int) * 10);
  // -> 각 배열엔 1이 아닌 16,843,009가 들어가게 된다 (2^24 + 2^16 + 2^8 + 1)
```

  - `memcpy` 함수와 `std::copy` 함수의 비교 시 미묘하게 `memcpy` 가 빠르지만 iterator 등을 생각했을 때 유연한 적용은 `std::copy`가 좋다.
  - `C pointer` 타입은 `memcpy`, 나머지는 `std::copy` 를 사용하자.


---
# 파일 입출력

  - 모드의 종류
    - `w, r, a, wt, rt, at, wb, rb, ab, r+, w+, a+`
    - w : 쓰기, 이미 있으면 덮어씀
  
    - r : 읽기, 파일이 없으면 에러가 발생. File스트림이 nullptr로 들어오게 된다.
    - a : 파일이 있으면 해당 파일을 연다. 파일이 있다면 해당파일의 가장 뒤에 새로 추가해서 넣어준다. 파일이 없으면 새로 만들어준다.
    - t, b : 텍스트 파일, 바이너리 파일을 만들어준다.
    - r+ : 파일이 있으면 읽기 쓰기 둘다 가능하게 열어준다. 파일이 없으면 에러를 발생한다.
    - w+ : 파일이 있으면 읽기 쓰기 둘다 가능하게 열어준다. 파일이 없으면 새로 만들어준다.
    - a+ : 파일이 있으면 맨 끝부터 읽고 쓰기가 가능하다. 파일이 없으면 새로 만들어준다.

```cpp
  FILE* File = nullptr;
  fopen_s(&File, "Test.txt", "rt");

  if (File) {
    char Line[256] = {};

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


---
# 클래스

  - 객체의 사용설명서 (객체는 단순한 저장 공간)
  - 구조체처럼 여러 변수를 모아두고 하나로 묶어서 사용할 수 있는 기능을 제공한다.
    
  - C++에서는 객체를 만들기 위한 수단으로 클래스를 제공한다. (코드 내에서의 객체 식별자는 저장공간의 주소를 의미한다.)
  - 사용자 정의형 (`user-defined type`) 이다.
  - **캡슐화** : 여러 변수와 함수를 모아서 하나의 클래스 혹은 구조체로 만들어주는 것을 말한다.
  - **은닉화** : 클래스에서 제공하는 멤버를 외부에 공개하는 수준을 정하는 것을 말한다.
  - `friend class CTestClass` : `CTestClass` 에게 접근허가를 내어준다. `CTestClass` 는 이 클래스의 `private` 데이터에 `public` 처럼 접근이 가능하다.
    - 현재 클래스에서는 `CTestClass`의 `private` 데이터에 접근할 수 없다. 단방향임.
    - 전방 선언의 역할도 겸한다. `CTestClass`를 몰라도 된다.

## 생성자와 소멸자

  - 객체의 초기화가 발생할 때 생성자가 호출되고, 저장공간 해제 시 소멸자가 호출된다.

  - 한 객체당 생성자와 소멸자는 단 한번 호출된다.
    - 모든 객체의 초기화는 한번만 가능하다. 이후에 값이 변경되는 것은 `대입(assignment)` 이다.
  - 초기화 순서는 `멤버가 정의된 순서`, 즉 메모리 상의 주소 순서와 같다. (낮은 주소 -> 높은 주소)
    - `상속` 관계가 있는 객체는 무조건 `기본 클래스`의 생성자가 먼저 호출된다.

      - `다중 상속`의 경우, `기본 클래스`들의 초기화 순서는 `base-list`의 순서대로 초기화가 진행된다. (선언순이 아님!)
   
      - `가상 베이스 클래스`가 포함된 상속의 경우, 가상 베이스 클래스의 멤버는 저장공간의 끝(높은 주소)에 저장된다. **초기화 순서와 저장공간 주소 순서가 다름!**
    - 접근 지정자에 따라 달라질 수 있다고 하는데(C++23까지만), MSVC컴파일러는 코드순으로 초기화한다.
    - [스칼라 타입](https://en.cppreference.com/w/cpp/types/is_scalar) 변수들은 초기화 구문이 없으면 정해지지 않은 값들이 들어간다.(`default initialization`)
    - [익명 유니온(anonymous union)과 변형 멤버(variant member)](https://en.cppreference.com/w/cpp/language/union#Union-like_class)는 `member initializer`가 없기 때문에 초기화가 안된다.
  - **다른 생성자를 선언하지 않는 경우에** 컴파일러는 인수를 사용하지 않는 `기본 생성자`를 생성한다.
    - 이 때, 멤버 변수들은 `Default Initialization` 가 아닌 `Zero Initialization`이 진행된다.
    - 그렇지만 초기화는 꼭 해줘야 한다. MSVC만 지원해주는 것일수도 있다.
  - 간단한 예제를 통해 생성자와 소멸자, 초기화의 순서를 알아보자.
    - `64비트 환경`이며, 포인터 연산 기준은 `1바이트` 이다.
    - `qword` == `8byte`, `dword` == `4byte`, `byte` == `1byte`

```cpp
  #include <iostream>
  class CTest {
    public:
    int mNum = 99;
    char mChar = 'x';
    
    CTest() {
      std::cout << "CTest Constructor" << '\n';
    }
    CTest(int mNum)
      : mNum{mNum} {
      std::cout << "CTest int Constructor" << '\n';
    }
    CTest(char w)
      : mChar{w} {
      std::cout << "CTest char Constructor" << '\n';
    }
    ~CTest() {
      std::cout << mNum << " CTest Destructor" << '\n';
    }
  };

  class CBase {
    public:
    char* mName{"CBase"};

    CBase() {
      std::cout << mName << " Constructor" << '\n';
    }
    CBase(int i)
      : mName{"CBase Int"} {
      std::cout << mName << " Constructor" << '\n';
    }
    virtual ~CBase() {
      std::cout << "CBase Destructor" << '\n';
    }
  };

  class CDerived : public CBase {
    public:
    int mNum{100};
    CTest mObj1{};
    CTest mObj2;
    char mChar;

    CDerived() : mObj1(1), mObj2('a'), CBase(1) {
      mName = "CDerived";
      std::cout << mName << " Constructor" << '\n';
    }
    ~CDerived() {
      std::cout << mName << " Destructor" << '\n';
    }

  };

  int main() {
    CBase* derived = new CDerived;
    delete derived;

    return 0;
  }
```
  - `derived` 객체의 초기화 순서
    - `new` 연산자 호출 (40byte 메모리 공간 확보 + 주소 확정)

    - `CDerived` 클래스의 인자가 없는 생성자 호출
    - `CBase` 클래스의 `int` 인자 1개를 받는 생성자 호출
      - (가상함수가 존재하기 때문에) `this`의 값에 `CBase` 클래스의 가상함수 테이블(`VFTable`) 주소를 입력 (`qword`)
      - `this + 8` 의 값을 `"CBase Int"` 의 주소로 초기화 (`mName`, `qword`)
    - `this`에 `CDerived` 클래스의 가상함수 테이블(`VFTable`) 주소를 입력 (덮어씀)
    - `this + 16` 의 값을 `64h` 로 초기화 (`mNum`, `dword`)
    - `this + 20` 과 인자 `1` 을 저장 후 `CTest` 클래스의 `int` 인자 1개를 받는 생성자 호출 (`mObj1(1)`)
      - `this` 의 값을 `1` 로 초기화 (`mNum`, `dword`)
      - `this + 4` 의 값을 `78h(ascii code의 'x')` 로 초기화 (`mChar`, `byte`)
      - 생성자의 함수 바디 부분 실행
    - `this + 28` 과 인자 `61h` 를 저장 후 `CTest` 클래스의 `char` 인자 1개를 받는 생성자 호출 (`mObj2('a')`)
      - `this` 의 값을 `63h` 로 초기화 (`mNum`, `dword`)
      - `this + 4` 의 값을 `61h` 로 초기화 (`mChar`, `byte`)
      - `CTest` 생성자의 함수 바디 부분 실행
    - `CDerived` 생성자의 함수 바디 부분 실행
  - `derived` 객체의 소멸 순서
    - 가상함수 테이블에서 소멸자 주소를 찾은 뒤 호출 (어셈블리에 단계가 한개 더 있음. 찾아볼 것)
 
    - `this` 설정 후 `CDerived` 클래스의 소멸자 호출
    - `CDerived` 소멸자의 함수 바디 부분 실행
    - `this + 28` 을 저장한 후 (`mObj2`) 및 함수 바디 부분 실행
    - `this + 20` 을 저장한 후 (`mObj1`) 및 함수 바디 부분 실행
    - `CBase` 클래스의 소멸자 호출 및 함수 바디 부분 실행
    - `delete` 연산자 호출 (메모리 공간 제거)

  - 참고
    - [Constructor](https://docs.microsoft.com/en-us/cpp/cpp/constructors-cpp?view=msvc-170)
    - [Non Static Data Members](https://en.cppreference.com/w/cpp/language/data_members)

<p align="center"> <img src="img/constructor_result.png"> </p>

## [Initialization](https://docs.microsoft.com/en-us/cpp/cpp/initializers?view=msvc-170)

  - ### Default Initialization
    - `기본 생성자 (==인자가 없는 생성자)`로 클래스, 구조체, 공용체를 초기화하는 것

    - 식별자 뒤에 아무런 표현을 하지 않는것이다.
    - `스칼라 타입 변수`는 정해지지 않은 값들이 들어간다.
    - `상수 타입 변수`는 스칼라 타입이면 에러를, 기본 생성자를 가진 클래스 타입이면 경고를 띄운다. (다른 초기화를 꼭 사용하자)
    - `정적 변수`는 `zero initalization`이 진행된다.
```cpp
  MyClass mc1;
  MyClass* mc3 = new MyClass;
```

  - ### Zero Initialization
    - 변수를 0값으로 설정하는것, 암묵적으로 타입에 맞게 변환된다.

    - 다음의 상황에 적용된다.
      - `정적 주기` 를 가진 변수들. 특별하게 생성자를 통해 한번 더 초기화 될 수 있다.
  
      - `value initaializagion` 중 `스칼라 타입`과 `POD클래스 타입`에 빈 중괄호로 초기화 한 경우
      - 배열의 특정 멤버가 초기화될 경우 나머지 멤버들은 0으로 초기화된다.
```cpp
  static float f1;
  double d{};
  int* ptr{};                       // nullptr로 초기화된다.
  int int_array[5] = { 8, 9, 10 };  // 4, 5번 배열의 int 값은 0으로 초기화된다.
```

  - ### Value Initialization
    - 빈 소괄호 또는 중괄호로 초기화하는 모든 초기화(약간 큰 개념)

    - `public constructor` 를 가진 클래스는 기본 생성자가 호출된다.
    - `default` 키워드로 생성된 생성자가 아닌 사용자가 정의한 기본 생성자인 경우 초기화 표현이 없는 모든 변수는 `기본 초기화`가 진행된다. (중요)
    - 생성자가 존재하는 타입일 경우, 생성자 호출 전에 크기만큼 메모리를 정리한다.
      - 일반 생성자 호출

        ![](img/default_initialize.png)
      - `default` 키워드로 생성한 기본 생성자 호출 (1D8h bytes에 XOR 결과값(0)을 넣는다.)

        ![](img/zero_initialize.png)

  - ### Copy Initialization (복사 초기화)
    - 다른 객체를 사용하여 한 객체를 초기화 하는 것

    - 다음의 상황에 적용된다.
      - `equal 기호(=)` 사용 시(`비정적 데이터 멤버` 초기화 포함)
      - 함수 인자로 전달 시
      - 함수에서 객체를 리턴할 시
      - 예외를 던질 시(`throw, catch`)
      - 클래스 멤버를 `aggregate initialization` 로 초기화 할 시 
    - 복사 생성자를 제거하거나 접근할 수 없게 만들 경우 컴파일 에러가 발생한다.
```cpp

  int i = 5;                 // i를 복사 초기화
  MyClass mc1{ i };
  MyClass mc2 = mc1;         // mc1 값으로 mc2를 복사 초기화
  MyClass mc1.set_int(i);    // i 값으로 함수 인자를 복사 초기화
  int i2 = mc2.get_int();    // get_int()의 리턴값으로 i2를 복사 초기화
  try {
      throw MyException();
  } catch (MyException ex){  // 예외 발생 시 ex를 복사 초기화
      cout << ex.what();
  }
```
  - ### Direct Initialization (직접 초기화)
    - 비어있지 않은 소괄호 또는 중괄호를 사용하여 초기화 하는 것

    - 복사 초기화와 달리 사용자 정의 생성자를 호출할 수 있다.
    - `static_cast` 를 사용한 초기화에도 적용된다.
    - `lambda` 식 내부에 복사된(`captured`) 변수들의 초기화에도 적용된다.
    - [예제](https://docs.microsoft.com/en-us/cpp/cpp/initializers?view=msvc-170#direct-initialization)
  
  - ### List Initialization (목록 초기화)
    - 중괄호로 묶여있는 `initializer list`를 사용하여 초기화 하는 것

    - [예제](https://docs.microsoft.com/en-us/cpp/cpp/initializers?view=msvc-170#list-initialization)
  
  - ### Aggregate Initialization (집합체 초기화)
    - 특수한 상황에서 사용하는 `목록 초기화`의 일종. 배열아니면 거의 볼 일이 없다.
    - `Aggregate` 는 `생성자`를 정의하지 않고, `접근 지정자` 를 사용하지 않으면서, 상속 관계와 가상 함수가 없는 배열 또는 클래스를 의미한다. (C++03 8.5.1)

    - [예제](https://docs.microsoft.com/en-us/cpp/cpp/initializers?view=msvc-170#agginit)
  
  - ### Reference Initialization (참조 초기화)
    - 변환될 수 있는 타입으로만 초기화가 가능하다.
    - 함수 호출식에서 인자에 참조 유형이 있거나 참조 유형을 반환하는 경우에 초기화가 진행된다.

    - TODO : 자세한 내용은 r-value 공부한 뒤에..
    - https://en.cppreference.com/w/cpp/language/reference_initialization
    - [예제](https://docs.microsoft.com/en-us/cpp/cpp/initializers?view=msvc-170#reference-initialization)


  - 참고
    - [cppreference](https://en.cppreference.com/w/cpp/language/initialization)
    - [What are Aggregates and PODs](https://stackoverflow.com/questions/4178175/what-are-aggregates-and-pods-and-how-why-are-they-special)

### Non-Static Data Member Initialization (NSDMI, 비정적 데이터 멤버 초기화)

  - 클래스, 구조체 내부에서 멤버 변수 선언 시 값을 지정해 주는 초기화 방법
  
  - `C++11`에서 추가됨 (왜 없었지)
  - `member initializer lists` 의 초기화 내용과 겹치면 무시한다. (생성자 쪽이 우선순위가 높음)
  - 소괄호를 통한 초기화는 지원하지 않는다. (`전방선언`과 혼동되어서 그런듯?)
```cpp
class CTest {
  public:
  int mNum = 99;      // 비정적 데이터 멤버 초기화
  char mChar = 'x';   // 비정적 데이터 멤버 초기화
  
  CTest() {
    std::cout << "CTest Constructor" << '\n';
  }
  CTest(int num) : mNum{num} {  // 99는 사라진다.
    std::cout << "CTest int Constructor" << '\n';
  }
  CTest(char c) : mChar{c} {    // 'x'는 사라진다.
    std::cout << "CTest char Constructor" << '\n';
  }
  ~CTest() {
    std::cout << mNum << " CTest Destructor" << '\n';
  }
};
```

  - 참고
    - [Constructor and member initializer lists](https://en.cppreference.com/w/cpp/language/constructor)
    - [Non Static Data Members](https://en.cppreference.com/w/cpp/language/data_members)
    - [Non Static Data Members Initialization](https://www.cppstories.com/2015/02/non-static-data-members-initialization/)

## [Uniform Initailizer](https://modoocode.com/286)

  - `class A` 가 있고 인자를 받지 않는 생성자를 가지고 있을 때, `A a();` 라인은 객체 `a`를 만드는 것이 아닌 `A`를 리턴하고 인자를 받지 않는 함수 `a` 를 선언한 것으로 간주한다.
    - CPP 컴파일러는 함수의 선언처럼 보이는 것들을 모두 함수의 선언로 해석한다.

  - ()가 함수를 선언하는 데에도 사용되고, 객체의 생성자를 호출하는 데에도 사용되기 때문에 `c++11`부터 도입되었다.
  - 생성자 호출에 `소괄호()` 대신 `중괄호{}` 를 사용하면 된다.
  - 암시적 타입 변환을 사용하지 못한다.
  - 함수 리턴 시 생성자의 객체 타입을 적지 않아도 된다. (리턴 타입을 보고 추론해준다)
  - 생성자에 배열처럼 리스트를 집어넣을 수 있다.(`initalizer_list`)
    - 생성자 오버로딩 시 해당 함수가 최우선이 되어 예기치 못한 에러가 발생할 수 있다.

    - `auto`로 타입을 지정한다면 아래와 같은 상황에서 전부 `std::initializer_list<int>` 타입으로 추론되기 때문에 `c++17`부터 두 가지 형태로 구분해서 추론하도록 변경되었다.
      - `auto x = {arg1, arg2...}` 형태의 경우 arg1, arg2 ... 들이 모두 같은 타입이라면 x 는 `std::initializer_list<T>` 로 추론

      - `auto x {arg1, arg2, ...}` 형태의 경우 만일 인자가 단 1 개라면 인자의 타입으로 추론되고, 여러 개일 경우 오류를 발생
    - 문자열 `auto` 사용 시 `initializer_list<const char*>`로 추론되는 상황을 방지하기 위해 `c++14`에서 추가된 리터럴 연산자를 사용하는게 좋다.
  
```cpp
auto a = {1};     // 첫 번째 형태이므로 std::initializer_list<int>
auto b{1};        // 두 번째 형태 이므로 그냥 int
auto c = {1, 2};  // 첫 번째 형태이므로 std::initializer_list<int>
auto d{1, 2};     // 두 번째 형태 인데 인자가 2개 이상이므로 컴파일 오류

using namespace std::literals;  // 문자열 리터럴 연산자의 네임스페이스
auto list = {"a", "b", "cc"};   // initializer_list<const char*>
auto list = {"a"s, "b"s, "c"s}; // initializer_list<std::string>
```

## Member Access Control (접근 지정자)

  - 클래스, 구조체, 공용체(유니온) 에서 멤버들의 접근성을 정의하는 키워드이다.
  
  - 상속 시, 베이스 클래스 접근 지정자에 따라 접근성이 달라진다. 
    - 접근성이 낮은(`private`) 쪽으로 덮어쓴다.
   
    - 예를 들면, 베이스 클래스 접근 지정자가 `protected`이면, 상속받은 `public` 멤버들은 전부 `protected`로 **접근 지정자가 변경**된다.
    - **아무것도 안적으면 기본 멤버 접근 지정자를 사용한다. (클래스는 `private`로, 구조체는 `public`으로 선언된다.**)
    - 웬만해서는 `public` 지정자를 사용한다.
  - ### `public`
    - 어느 함수에서나 접근이 가능하다.
  - ### `private`
    - 클래스 멤버 함수 또는 친구 클래스의 멤버 함수에서 접근이 가능하다.
  - ### `protected`
    - 클래스 멤버 함수 또는 친구 클래스의 멤버 함수, 파생 클래스에서 접근이 가능하다.
  - `private` 멤버는 다른 멤버들과 `friend`만 접근할 수 있지만, 클래스를 볼 수 있는 모든 코드가 볼 수 있기에, 컴파일 과정의 함수 오버로드 해소 과정이나 모호한 함수 처리 등의 호출 해소 과정에는 동일하게 참여한다.
    - 컴파일러가 함수 호출을 처리할 때, 아래 세 가지 조건을 순서대로 거친다.
      - 1. `Name Lookup (이름 조회)`
      - 2. `오버로드 해소`
      - 3. `접근성 점검`
  - 컴파일 시 해당 키워드를 처리하는 것이기 때문에 로우 레벨에서 동작하는 모든 기능들은 영향을 받지 않는다. (함수 포인터를 통한 함수 호출 등)
  - `static` 멤버들은 접근 지정자의 영향을 받지 않는다. 
    - 단, 포인터, 참조, 객체를 통한 접근은 지정자의 영향을 받기 때문에 전역으로 접근해야 한다. (`::CBase::Func()`)
    - 포인터, 참조, 객체를 통한 접근은 지정자에 영향을 받는 형식으로 형변환이 필요하기 때문이다.
  - 파생 클래스의 가상 함수가 `private` 이면, `파생 클래스 객체를 참조`하는 베이스 클래스 포인터는 가상 함수에 접근이 블가능하다. (C2248 에러)
  - 참고
    - [Member Access Control](https://docs.microsoft.com/en-us/cpp/cpp/member-access-control-cpp?view=msvc-170)
    - [Access specifiers](https://en.cppreference.com/w/cpp/language/access)
    - [private는 얼마나 비공개적인가?](https://wikidocs.net/469), [다른 사이트](http://egloos.zum.com/sweeper/v/2998794)

## 헤더 파일

  - 변수, 함수, 클래스 등과 같은 프로그램 요소의 이름을 사용하기 위해 선언해놓는 파일
 
  - 프로그램 컴파일 시 각 `.cpp` 파일들은 컴파일 단위로 독립적으로 컴파일된다.
  - 컴파일러는 다른 컴파일 단위에서 선언된 이름을 알지 못하기 때문에 각 `.cpp` 파일에서 사용하는 클래스, 함수, 전역 변수에 대한 선언을 제공해야 한다.
  - 
  - 순환 참조 : 서로의 헤더 파일을 `include` 하는 상태. 무조건 피해야 한다.
  - 이것을 피하기 위해 `전방 선언` 을 한다.
  - 전방 선언 시 구현부에서는 해당 엔터티가 정의된 헤더를 참조해야 한다.
  - `#pragma once` 지시문은 `#ifndef, #define, #endif` 지시문(C style)을 사용한 것과 동일하다.(MSVC는 이렇게 동작함. 다른 컴파일러는 모름.)

질문 : 링커가 obj 파일들을 exe 파일로 만들 때 각 obj 파일마다 중복되는 헤더들도 다같이 복사되는가? 제거할 수있는 방법은 모든 코드를 한 파일에 쓰는방법 밖에 없는가?
예전에 카트라이더인지 버블파이터인지가 코드들은 하나로 묶어 빌드해서 성능을 올렸다는 기사를 본 것 같다.

  - 참고
    - [What is external linkage and internal linkage?](https://stackoverflow.com/questions/1358400/what-is-external-linkage-and-internal-linkage)
    - [Struct with a value in a header file causing "duplicate symbol" linker error](https://stackoverflow.com/questions/2206853/struct-with-a-value-in-a-header-file-causing-duplicate-symbol-linker-error)
    - [컴파일, 링킹, 헤더파일](https://code4human.tistory.com/110)

---
# [상속](https://docs.microsoft.com/en-us/cpp/cpp/inheritance-cpp?view=msvc-170)과 [가상 함수](https://docs.microsoft.com/en-us/cpp/cpp/virtual-functions?view=msvc-170)

## 상속 (`Inheritance`)

  - 기존 클래스에서 파생된 새 클래스가 기존 클래스의 특성을 가지는 메커니즘
  
  - 데이터 상으로는 `파생 클래스`의 멤버 데이터 목록에 `기본 클래스`의 객체를 추가한 것과 동일하다.
    - 일반 단일 상속의 경우, 파생 클래스 멤버 변수들의 앞에 위치한다. 낮은 주소를 가진다.
  
    - 초기화 순서 또한 기본 클래스의 우선순위가 높다.
  - `부모-자식 관계`에서 부모 클래스는 자식 클래스의 `direct base class` 가 되고, `부모-자식-손자 관계`에서 부모 클래스는 손자 클래스의 `indirect base class` 가 된다.
  - 기본 클래스는 파생 클래스 앞에 선언해야 한다. 전방 선언도 안된다.
  - 이름이 같은 멤버(변수, 함수)에 접근할 때 `범위 지정 연산자(::)`를 사용하여 베이스 클래스의 멤버로 접근할 수 있다.
    - **베이스 클래스의 가상함수를 호출하고 싶을 때** `obj->CBase::foo()` 이런 식으로 사용한다. 이 때, 가상 함수 메커니즘은 진행하지 않는다.
  
    - 멤버 변수도 동일하게 접근이 가능한데, 이름이 같은 시점에서 잘못된 코드다.
  - `C++` 에서는 [다중 상속](https://docs.microsoft.com/en-us/cpp/cpp/multiple-base-classes?view=msvc-170)이 가능하다.
    - 두 개의 파생 클래스를 상속받는 클래스는 기본 클래스를 2개 포함하게 되는데, 생성자가 두 번 호출되는 불상사를 막기 위해 기본 클래스를 상속받을 때 `virtual` 키워드를 붙여 `virtual base class(가상 기본 클래스)`로 만든다.
    
    - 가상 기본 클래스는 공간을 절약하고 여러 개의 다중 상속을 사용하는 클래스 계층에 모호성이 발생하지 않는 방법을 제공한다.
    - 가상 기본 클래스가 생성되면 데이터 멤버들의 순서와 `sizeof` 결과값이 변경된다. (단일 상속과 다르다)
    - 자세한 내용은 [Virtual Table Table 섹션](#virtual-table-table) 에 정리했다.

  - `빈 베이스 클래스`를 상속받는 `빈 파생 클래스`의 `typeid` 는 베이스 클래스이다.
    - 파생 클래스를 특정할 수 있는 요인이 하나도 없기 때문이다.
  - [접근 지정자](#member-access-control-접근-지정자)를 사용하여 상속 시 멤버 변수, 함수에 권한을 지정할 수 있다. 
  - `final` 키워드를 사용하여 이후 현재 클래스 또는 가상 함수를 상속받지 못하도록 제한할 수 있다.


## 가상 함수 (`Virtual Function`)

  - `파생 클래스(derived class)`에서 재정의할 것이라 예상하는(`expected`)(약속하는?) 비정적 멤버 함수
  
  - `기본 클래스(base class)`에 **참조 또는 포인터를 사용**하여 파생 클래스 객체를 참조할 때, 해당 객체에 대한 가상 함수를 호출하면 파생 클래스의 함수를 실행할 수 있다.
    - 이 때 기본 클래스의 소멸자를 가상 함수로 만들지 않으면 **파생 클래스의 소멸자가 호출되지 않는다.** 식별자의 타입이 기본 클래스라서 파생 클래스의 존재를 모르기 때문이다.
    
    - 물론 파생 클래스에서 정의한 **모든 멤버 변수들도 소멸되지 않는다.**
  - 가상 함수를 재정의(`override`) 하는 모든 함수는 가상 함수이다. (`virtual` 키워드가 생략되어 있다.)
  - 재정의 시 `접근 지정자`의 영향을 받지 않는다.
    - 코드 짜기 편하라고 만든것이지 메모리와는 상관없기 때문이다.
  - **참조 또는 포인터 타입의 객체**에서 가상 함수는 **가상함수 테이블에서 주소를 찾아** 함수를 호출한다.
  - `주소 타입이 아닌 객체`에서의 함수는 가상함수 테이블을 사용하지 않는다.
  - 함수 처리 전에 가상함수 테이블에 들어가서 주소를 가져오는 작업이 추가되기 때문에 꼭 필요한 경우가 아니면 사용하지 말자.
  - `override` 키워드를 사용하여 예기치 못한 에러를 방지할 수 있다. (`const` 등을 빼먹어서 다른 함수로 만든다든지..)
```cpp
  CDerived derived;
  CDerived& refDerived = derived;
  derived.foo();
  refDerived.foo();
  derived.vFoo();
  refDerived.vFoo();
```
![](img/virtual_func_assembly.png)

  - 베이스 클래스를 참조하는 파생 클래스 객체에서, `베이스 클래스의 비가상 함수`를 호출했을 때, 베이스 클래스의 멤버 변수만 접근할 수 있다.
    - 당연하다. 베이스 클래스는 파생 클래스의 존재를 모르기 때문이다. 접근하려면 `다운 캐스팅`을 하면 된다.
  
    - 상속 메커니즘의 클래스 멤버 변수 앞에는 `this`포인터와 `범위 지정 연산자`가 생략되어 있다. `this->변수` 가 아니라 `this->클래스::변수`가 옳은 표현이다. 
    - 메모리에서 해당 클래스의 위치로 이동한 다음 해당 클래스의 `멤버 변수 오프셋`을 통해 주소로 접근하는 것이다.
  - 함수 호출 코드(`객체->함수();`)는 `객체의 주소`, `가상함수 판단`의 정보를 가진다.
    - 함수가 가상 함수이면 `가상함수 오프셋(상대주소)` 정보를, 비가상 함수이면 `클래스::함수()`의 주소 정보를 가진다.

  - 참고
    - [virtual function specifier](https://en.cppreference.com/w/cpp/language/virtual)
    - [가상함수와 가상함수테이블의 이해](https://cosyp.tistory.com/228)
    - [가상함수와 상속](https://modoocode.com/211)


## Abstract class, Pure Virtual Function (추상클래스, 순수 가상 함수)

  - 함수 이름 뒤에 `Pure Specifier(순수 지정자)`(`= 0`) 를 붙여 선언한 가상 함수를 `순수 가상 함수`라고 한다.

    - 구현부분이 없어도 된다. 보통 인터페이스 용도로 사용하기 때문에 구현부에 어떤 용도로 사용하면 되는지 적어놓는다.
  - 파생 클래스에서 반드시 재정의를 해야 한다는 표시이다.
  - 순수 가상 함수를 1개 이상 가지고 있는 클래스를 `추상 클래스`라고 한다.
  - 추상 클래스는 객체를 생성할 수 없다.
  - 주로 인터페이스를 만드는 데 사용한다.
```cpp
  class CAbstract {           // 추상 클래스
    public:
    CAbstract() {}
    virtual ~CAbstract() {}
    virtual void vPure() = 0; // 순수 가상 함수
  };
```

## Virtual Function Table (가상함수 테이블)

  - 클래스에 하나 이상의 가상 함수가 존재할 경우 생성되는 리스트
 
  - 일반적인 경우 객체의 가장 낮은 주소에 배치한다. (`this`와 동일한 주소)
  - 가상함수 테이블 저장 순서는 기본 클래스 가상함수 -> 파생 클래스 가상함수 순이다.
    - `선언`한 순서대로 함수 `정의` 부분 주소를 테이블에 채워넣는 형태다.
   
    - `다중 상속`의 경우 `base-list` 순서를 따른다. (주소 상의 순서다. 어차피 테이블이 달라서 의미는 없다.)
  - `다중 상속`의 경우, 가상함수 테이블의 개수는 기본 클래스들의 개수와 같다.
    - 기본 클래스들은 서로의 가상함수 테이블을 모르고 고유의 오프셋을 가진다.
  
    - 때문에 해당 클래스의 테이블에 접근해서 오프셋을 통해 주소를 가져오는 것이다.
  - 예제를 통해 저장되는 순서를 알아보자.


## Virtual Table Table

  - `베이스 클래스 멤버`의 위치를 찾기 위한 메타데이터 리스트
  - 일반 상속의 경우 참조하는 멤버에 대한 상대적 주소(오프셋)가 일정하다.
  - 가상 상속의 경우 베이스 클래스의 멤버의 주소가 상속 관계에 따라 변경된다.

  - 참고 (고마워요 `Morgan Deters`!)
    - [VTable Notes on Multiple Inheritance in GCC](https://ww2.ii.uj.edu.pl/~kapela/pn/cpp_vtable.html)
    - [What si the VTT for a class](https://stackoverflow.com/questions/6258559/what-is-the-vtt-for-a-class) -> 위와 동일한 내용
    - [virtual 상속의 원리](https://m.blog.naver.com/PostView.naver?isHttpsRedirect=true&blogId=kyed203&logNo=220207325648)



---
# [변수 범위, 주기, 링크](https://www.learncpp.com/cpp-tutorial/scope-duration-and-linkage-summary/)
  - 참고 : [Storage class specifiers](https://en.cppreference.com/w/cpp/language/storage_duration)

  - `Scope`
    - 
    - 식별자의 `scope`는 소스파일 내에서 어디까지 접근할 수 있는가를 결정한다.

    - ### `block(local) scope` : 선언된 블록 내에서만 접근 가능하다.
      - 지역변수 (`local variables`)
      - 매개변수 (`function parameter`)
      - 블록 내 유저 정의 자료형 (`user-defined type definitions declared inside a block`)
    - ### `global(file) scope` : 소스파일의 모든 위치에서 접근 가능하다.
      - 전역변수 (`global variables`)
      - 일반함수 (`normal function`)
      - 유저 정의 자료형 (`user-defined type definitions declared inside a namespace or in the global scope`)

  - `Duration`
    - 
    - 변수의 `duration`은 언제 생성되고 소멸되는지를 결정한다.

    - ### `automatic duration` : 선언(`definition`) 시점에 생성, 해당 변수가 포함된 블록이 끝날 때 파괴된다.
      - 지역변수 (`local variables`)
      - 매개변수 (`function parameter`)
    - ### `static duration` : 프로그램 시작 시 생성, 프로그램이 끝날 때 파괴된다.
      - 전역변수 (`global variables`)
      - 정적지역변수 (`static local variables`)
    - ### `dynamic duration` : 프로그래머가 요청 시 생성 혹은 파괴된다.
    
      - 동적 할당 변수 (`dynamically allocated variables`)

  - `Linkage`
    - 
    - 식별자의 `linkage`는 같은 이름의 식별자가 여러 개 선언되었을 때 같은 식별자를 참조하는가 다른 식별자로 인식하는가를 결정한다.

    - ### `no linkage` : 자기 자신만을 참조한다.
      - 지역변수 (`local variables`)
      - 블록 내 유저 정의 자료형 (`user-defined type definitions declared inside a block`)
    - ### `internal linkage` : 내부 링크, 선언된 소스파일 어디에서나 접근이 가능하다.
      - 정적전역변수 (`static global variables`)
      - 상수전역변수 (`const global variables`)
      - 정적함수 (`static function`)
      - 네임스페이스 내 유저 정의 자료형 (`user-defined type definitions declared inside an unnamed namespace`)
    - ### `external linkage` : 외부 링크, 선언된 소스파일 + 다른 파일에서도 접근이 가능하다.
      - 일반함수 (`normal function`)
      - 비상수 전역변수 (`non-const global variables`)
      - 외부전역변수 (`extern global variable`)
      - 인라인 상수전역변수 (`inline const global variables`), (`C++17`)

![](img/scope%2Cduration%2Clinkage.PNG)


---
# [키워드](https://docs.microsoft.com/en-us/cpp/cpp/keywords-cpp?view=msvc-170)

## [this 키워드](https://docs.microsoft.com/en-us/cpp/cpp/this-pointer?view=msvc-170)

  - 클래스, 구조체, 유니온 안의 `비정적(nonstatic) 멤버 함수`에서만 접근할 수 있는 포인터

  - 객체의 한 부분이 아니기 때문에 `sizeof` 연산자의 결과에 반영되지 않는다.
    - 객체 이름이 해당 객체의 주소값이기 때문에 함수 주소와 같이 코드 영역에 포함된다.
    - 때문에 `this` 는 **객체가 아닌 엔터티**이다.
  - 객체를 통해 비정적 멤버 함수가 호출되었을 때, 컴파일러는 객체의 주소를 숨겨진 인자로 전달한다.
    - 객체가 `nullptr` 이어도 해당 멤버 함수 내에서 멤버 변수를 사용하지 않으면 정상동작 한다(!)

```cpp
  myDate.setMonth(3);    // 소스 코드의 형태
  setMonth(&myDate, 3);  // 컴파일러가 해석한 형태

  class CNull {
    public:
    void foo(){
      std::cout << "nullptr test : " << this << std::endl;
    }
  };
  
  CNull obj = nullptr;
  obj->foo();    // 정상동작 한다.
```
  - 객체의 멤버 함수에서 접근하는 멤버 변수의 앞에는 `this->` 또는 `(*this).` 구문이 생략되어 있다.
  - 자기 자신을 참조하는 것을 방지할 때도 사용한다. (`&object != this`)


## static 키워드

  - `static` 변수는 생성된 스코프가 종료된 이후에도 해당 값을 유지한다.

  - **단 한번만 초기화**되며, 프로그램 내내 수명이 지속된다.
  - 초기화를 하지 않고 어디에도 사용하지 않으면 메모리가 할당되지 않는다.
    - 전역변수는 초기화하면 `data`영역에, 초기화하지 않으면 `bss`영역에 올라간다.

    - `static` 객체는 초기화와 상관없이 `bss` 영역에 올라간다. 생성자를 통한 초기화는 해당 구문이 처음 수행되는 시점에 이루어진다.
      - `bss` 영역은 `dynamic initializer`를 진행하는 곳이다. (컴파일 시 값을 알 수 없는 경우 나중에 초기화를 해주는 것)

      - 이를 함수화하여 호출을 하면 생성자의 호출 시점을 조정하는게 가능해진다.
      - `singleton` 클래스를 생성할 때 주의해야 한다.
  - `static` 멤버 변수는 모든 객체가 공유해야 하기 때문에 프로그램 전체 영역에서 메모리 유지가 되어야 한다. **반드시 전역 범위에서 정의 및 초기화를 수행해야 한다.**
    - 함수 내부에서는 선언만 하고 초기화를 cpp파일에서 하자.

    - `C++17` 에서는 `inline variables`를 통해 `inline` 키워드로 **선언과 동시에 초기화**가 가능해졌다! (헤더에서만 가능)
  - `static` 멤버 함수는 고유의 객체를 두고 연산이 이루어지는 것이 아니기 때문에 `함수 포인터` 취급을 한다.
    - 함수 포인터에 대입을 할 때 주소연산자(&)를 붙이지 않아도 된다. (붙여도 된다.)

    - 함수 포인터 타입에 네임스페이스를 명시하지 않아야 된다.
      - 함수 포인터는 네임스페이스에 엄격하다.
      - 정적 멤버 함수 포인터와 일반 멤버 함수 포인터는 타입이 다르다.

```cpp
CTest test; // static void foo() 멤버 함수를 가지고 있다.
void (*func)() = test.foo;            // ok 
void (*func2)() = CTest::foo;         // ok
void (*func3)() = &CTest::foo;        // ok 
// void (*)()" 형식의 값을 사용하여 "void (CTest::*)()" 형식의 엔터티를 초기화할 수 없습니다.C/C++(144)
// void (CTest::*func4)() = &CTest::foo; // 오류
```

  - 참고
    - [전역변수와 정적변수](https://chfhrqnfrhc.tistory.com/entry/%EC%A0%84%EC%97%AD%EB%B3%80%EC%88%98%EC%99%80-%EC%A0%84%EC%A0%81%EB%B3%80%EC%88%98)
    - [Inline Variables 정보](http://egloos.zum.com/sweeper/v/3213741)
    - [Non Static Data Members Initialization](https://www.cppstories.com/2015/02/non-static-data-members-initialization/)
    - [what is dynamic initailization](https://stackoverflow.com/questions/5945897/what-is-dynamic-initialization-of-object-in-c)
    - https://ansohxxn.github.io/cpp/chapter8-10/


## extern 키워드

  - `extern` 변수는 정의된 소스파일과 다른 소스파일에도 접근이 가능하다.

  - 기본적으로 전역변수(`global variable`)는 `extern` 변수로 간주한다. (키워드가 생략되어 있음)
    - 다른 파일에서 `extern` 키워드를 사용해서 접근할 수 있다.

    - 정의한 전역변수에는 `extern` 키워드를 붙이지 않는다. 내가 원본이기 때문.
      - 붙여도 무시된다. 헷갈리니까 붙이지 말자.
  - 다른 소스파일에서 선언된 외부전역변수를 사용하려면 변수 전방선언 (`variable forward declarations`)을 해야한다.
    - 전방선언이 함수 외부에서 선언되면 소스파일 전체에 적용되고, 함수 내에서 선언되면 해당 블록 내에서만 적용된다.

    - **키워드를 생략할 수 없다.** 생략하면 일반 변수 정의와 동일해진다.
    - 변수에 `static` 키워드가 붙어 있으면 전방선언을 해도 적용되지 않는다.
    - 함수는 기본적으로 외부 링크 속성이다. `static` 키워드를 사용하면 내부 링크로 설정이 가능하다.
  - 상수전역변수(`const global variables`)는 `static` 변수로 간주한다. 외부에서 사용하면 새로운 변수를 선언하는것과 동일함.
    - 상수를 외부 전역변수로 사용하려면 해당 변수에 `extern` 키워드를 꼭 붙여야 한다.
  - 헤더파일에서 정의할 경우 해당 헤더를 여러군데에서 쓸 경우 초기화를 여러번 수행하게 되어서 링킹 에러가 발생한다.
    - **헤더파일에는 선언만 하고 초기화를 cpp파일에서 하자.**

    - `C++17` 에서는 `inline variables`를 통해 `inline` 키워드로 **선언과 동시에 초기화**가 가능해졌다! (헤더에서만 가능)
  - 어디서 값이 바뀔 지 모르고 찾기도 힘들기 때문에 왠만해선 전역변수를 사용하지 말자.
  - 의문 : 상수전역변수는 일반 상수를 여러번 사용하는 것보다 이득인데 왜 많이 안쓰나?
    - 컴파일러가 코드 최적화를 알아서 진행한다.
    - 자세한건 컴파일러 최적화 종류와 기법을 찾아보자.
  - 참고
    - [전역 변수와 링크](https://boycoding.tistory.com/167?category=1007833)
  
```cpp
  /* 초기화 X */
  int g_x;              // external. 다른 파일에서 사본으로 쓰인다. 
  static int g_x;       // internal. 다른 파일에서 쓰일 수 없다. 이 코드 내에서만 쓰일 수 있음
  const int g_x;        // external. 에러! const는 꼭 초기화를 해주어야함
  extern int g_z;       // 이 파일을 include 하는 다른 파일에서 이 변수와 메모리를 공유하게 될 것.
  extern const int g_z; // 에러 아님! 이 변수와 메모리를  공유하는 다른 파일에서 초기화 꼭 해주면 됨.

  /* 초기화 O */
  int g_y(1);           // external. 
  static int g_y(1);    // internal. 
  const int g_y(1);     // external. 
  extern int g_w(1);    // 이제 다른 파일에서 정의가 불가능하다. 
  extern const int g_w(1); 
```

## [virtual 키워드](https://docs.microsoft.com/en-us/cpp/cpp/virtual-cpp?view=msvc-170)

  - [가상 함수](#가상-함수-virtual-function) 또는 가상 베이스 클래스(`virtual base class`)를 선언할 때 사용

  - 가상 베이스 클래스는 `다중 상속` 시 부모를 하나의 베이스 객체로 놓고 모든 자식들이 멤버 변수들을 공유하도록 만든다.
    - `기본 클래스(base class)`가 여러 `파생 클래스(derived class)`를 가지고, 임의의 클래스가 파생 클래스들을 다중상속 받을 경우에 사용한다.

    - `가상 상속`을 받지 않으면 생성자를 파생 클래스 개수만큼 호출한다.
    - 자세한 내용은 [Virtual Table Table 섹션](#virtual-table-table) 에 정리했다.
  - 콜론(`:`) 뒤, 기본 클래스의 이름 앞, `접근 지정자(access specifier)` 앞 뒤에 `virtual` 키워드를 붙여 가상 상속을 할 수 있다.
  - [가상 베이스 클래스의 예제](https://www.learncpp.com/cpp-tutorial/virtual-base-classes/)


## inline 키워드

  - TODO


## constexpr 키워드

  - TODO


---
# 연산자

## sizeof 연산자

  - 타입 이름 또는 단항연산 표현(`unary-expression`)을 인자로 받는 연산자.

  - `size_t` 타입의 결과를 생성한다.
    - 인텔리센스로 연산 결과값을 바로 알 수 있다. (`4Ui64` : 64비트 운영체제 부호 없는 정수형(`unsigned integral`) 타입의 크기 4)
  - 타입 이름을 제외한 나머지 연산 시 괄호를 사용하지 않아도 된다(!)
  - 절대 0이 결과값으로 나오지 않는다. (나누기 같은 구문에서 에러를 발생시킬 수 있기 때문에 최소값을 1로 정해놓았다.)
  - 배열 식별자의 경우 배열의 총 바이트 수를 산출한다. 포인터 타입은 포인터 크기가 나온다.
  - 클래스, 구조체, 유니온의 경우 컴파일러 옵션(`/Zp`) 또는 `pack pragma`에 따라 각각의 멤버 변수 크기의 합과 다를 수 있다. (바이트 패딩)
  - 컴파일 타임에 크기가 정해지지 않거나 텍스트 영역에 저장되는 함수(함수포인터는 가능)는 연산할 수 없다.
  - 참고
    - [클래스의 크기](https://blog.naver.com/tipsware/221090063784)

## 캐스팅 연산자

  - TODO


## 범위 지정 연산자

- `::`
- 질문 : 멤버변수의 주소에 `&객체.변수` 가 아닌 `&클래스::변수` 로 접근하면 어디를 참조하게 되는것인가? -> 상속 시 클래스 내부에서 식별자의 모호함을 제거하기 위해 사용한다. 외부에서는 사용할 일이 없음.(static 제외)
- TODO


## 연산자 오버로딩

  - 포인터의 연산자는 연산자 오버로딩이 안된다.
    - 그래서 `shared_ptr`과 같은 포인터를 관리하는 래핑 함수를 만들어서 사용한다. (추가로 복사, 이동생성자도 호출이 안된다)


---
# 함수

## 멤버 함수와 가상 함수 예제

  - TODO : `std::addressof() (C++17)` 를 확인해보자.

```cpp
#include <iostream>
#include <conio.h>   // _getch() 함수 사용

class CEmpty {};
  class CTest {
  public:
    char a;
    void foo(){}
    void bar(){}
  };
  class CTestStatic {
  public:
    char a;
    static char b, c, d;
    void foo(){}
    static void bar(){}
  };
  class CTestVirtual {
    public:
    char a;
    void foo(){}
    virtual void bar(){}
  };
  class CTestParent {
    public:
    char a;
    virtual void foo(){}
    virtual void bar(){}
  };
  class CTestChild : public CTestParent {};
  class CTestChildOverride : public CTestParent {
    public:
    void bar(){}
  };

int main() {
  CEmpty empty;                 // 빈 클래스
  CTest test;                   // 기본 클래스
  CTestStatic stat;             // 정적변수, 함수가 포함된 클래스
  CTestVirtual virt;            // 한 개의 가상함수를 포함하는 클래스
  CTestParent parent, parent2;  // 두 개의 가상함수를 포함하는 클래스
  CTestChild child;             // 상속받지만 가상함수를 재정의하지 않은 클래스
  CTestChildOverride overrided; // 상속받은 가상함수를 재정의한 클래스
  
  //  크기 비교
  // 1. empty 클래스도 스택 영역에 메모리가 올라간다.
  // 2. static 멤버 변수는 클래스의 크기에 영향을 주지 않는다. (bss 영역에 올라감)
  // 3. 가상함수를 포함하는 클래스는 주소 크기만큼 크기가 커진다. 주소값이 8바이트이기 때문에 16바이트(바이트 패딩)의 결과가 나온다.
  // 4. 가상함수의 개수는 크기와 상관없다. -> 가상함수 테이블은 배열? 리스트? 로 생성되며 클래스들은 테이블의 주소를 가진다.
  std::cout << typeid(empty).name() << " size : " << sizeof empty << " byte\n";   // 1 byte
  std::cout << typeid(test).name() << " size : " << sizeof test << " byte\n";     // 1 byte
  std::cout << typeid(stat).name() << " size : " << sizeof stat << " byte\n";     // 1 byte
  std::cout << typeid(virt).name() << " size : " << sizeof virt << " byte\n";     // 16 byte
  std::cout << typeid(parent).name() << " size : " << sizeof parent << " byte\n"; // 16 byte
  
  // cout에 멤버 변수의 주소를 인자로 받는 오버로딩 함수가 없기 때문에 캐스팅 없이 출력하면 가장 적합하게 처리할 수 있는 함수를 고른다.
  // 멤버 변수의 주소를 그냥 출력하면 아무 값도 안나온다. (클래스이름::* 타입이다.)
  // reinterpret_cast 연산자는 임의의 포인터 타입끼리 변환을 허용하는 캐스트 연산자다.
  // 오버로딩 함수 중 void* 형의 인자를 받는 함수가 있기 때문에 캐스팅 후 출력한다.
  // printf를 사용하면 캐스팅을 하지 않아도 되는데, printf는 가변 인자를 통해 처리하는 방식이기 때문이다.
  //
  //  가상함수 테이블 주소 위치 확인
  // 1. 가상함수 테이블의 주소는 객체 메모리의 가장 앞부분에 추가된다.
  std::cout << std::hex;
  std::cout << &test << " : " << typeid(test).name() << " address" << '\n';        // &test == &test.a
  std::cout << reinterpret_cast<void *>(&test.a) << " : " << typeid(test).name() << " member address" << '\n';
  std::cout << &parent << " : " << typeid(parent).name() << " address" << '\n';    // &parent + 8 == &parent.a
  std::cout << reinterpret_cast<void *>(&parent.a) << " : " << typeid(parent).name() << " member address" << '\n';
  //printf("%p\n", &test.a); // 캐스팅을 하지 않아도 된다.
  //printf("%p\n", &parent.a);
  std::cout << std::endl;

  //  가상함수 테이블 주소값 비교
  // 1. 클래스 별 가상함수 테이블의 주소값은 멤버 함수와 관계없이 전부 다르다.
  // 2. 동일 클래스의 객체들은 가상함수 테이블을 공유한다.
  size_t parentVTAddr = 0;
  size_t parent2VTAddr = 0;
  size_t childVTAddr = 0;
  size_t overridedVTAddr = 0;
  memcpy(&parentVTAddr, &parent, sizeof size_t);
  memcpy(&parent2VTAddr, &parent2, sizeof size_t);
  memcpy(&childVTAddr, &child, sizeof size_t);
  memcpy(&overridedVTAddr, &overrided, sizeof size_t);
  std::cout << parentVTAddr << " : " << typeid(parent).name() << " VTable address" << '\n';       // 7ff7f0976830  
  std::cout << parent2VTAddr << " : " << typeid(parent2).name() << " VTable address" << '\n';     // 7ff7f0976830  
  std::cout << childVTAddr << " : " << typeid(child).name() << " VTable address" << '\n';         // 7ff7f0976850  
  std::cout << overridedVTAddr << " : " << typeid(overrided).name() << " VTable address" << '\n'; // 7ff7f0976870
  std::cout << std::endl;

  // 객체에서 멤버 함수에 접근해 주소를 얻으려하면 오류가 발생한다.(&test.bar -> C/C++(300)오류)
  // 함수 호출 코드에서 실제 호출할 함수를 결정하는 것을 함수 바인딩이라 하는데, 객체를 동적할당하지 않으면 컴파일 시점에 해당 객체가 호출할 함수를 결정한다. (static binding)
  // 이 바인딩 된 객체의 함수 포인터는 호출 외에 다른 용도로 사용할 수 없기 때문에 오류가 발생하는 것이다.
  // 멤버 함수 이름(&CTest::foo)을 통해 주소를 구하려고 하면 캐스팅 타입이 맞지 않다고 오류가 발생한다. (C/C++(171)) (static 멤버 함수는 전역 함수와 동일한 함수 포인터 타입이기 때문에 캐스팅을 안해도 된다.)
  // void * 는 유저가 원하는 타입으로 형변환이 가능하지만 멤버 함수를 나타내는 함수 포인터로는 변환이 불가능하다. 참고 : http://www.cplusplus.com/forum/general/38453/
  // TODO : 그래서 참조자(&)를 사용해서 우회 접근한다. (자세한 이유를 알아보자)
  // 참조자는 r-value를 허용하지 않기 때문에 멤버 함수 포인터 변수를 생성하여 출력한다.
  // printf는 캐스팅 할 필요가 없으니 함수 이름을 그대로 사용 가능하다.
  //
  //  멤버 함수 주소값 비교
  // 1. 재정의 하지 않은 상속 관계의 클래스들의 멤버 함수는 같은 주소값을 가진다.
  // 2. 재정의한 멤버 함수는 다른 주소값을 가진다.
  // 3. 멤버 함수 포인터는 묵시적 형변환을 허용하지 않는다. this 포인터 때문에 네임스페이스가 굉장히 중요하기 때문이다.
  // std::cout << CTestStatic::bar << '\n'; // static 멤버 함수는 주소연산자(&)를 붙이지 않아도 된다.
  void (CTestParent::*pParentBar)() = &CTestParent::bar;
  void (CTestParent::*pChildBar)() = &CTestChild::bar;
  void (CTestChildOverride::*pOverrideBar)() = &CTestChildOverride::bar;
//   void (CTestParent::*pOverrideBar)() = &CTestChildOverride::bar;
  
  std::cout << reinterpret_cast<void *&>(pParentBar) << " : " << typeid(parent).name() << " bar func address" << '\n';      // 00007FF7F08A4FD9
  std::cout << reinterpret_cast<void *&>(pChildBar) << " : " << typeid(child).name() << " bar func address" << '\n';        // 00007FF7F08A4FD9
  std::cout << reinterpret_cast<void *&>(pOverrideBar) << " : " << typeid(overrided).name() << " bar func address" << '\n'; // 00007FF7F08A5FE2
  // printf("%p\n", &CTestParent::foo); // 캐스팅을 하지 않아도 된다.
  std::cout << std::endl;

  std::cout << "계속하려면 아무 키나 누르십시오..." << '\n';
  _getch();
  //system("pause");

  return 0;
}
```
<p align="center"> <img src="img/vfunc.png"> </p>

  - 참고
    - [함수의 주소 출력](https://bigpel66.oopy.io/library/cpp/etc/1) 
    - [C++에서 함수 포인터 사용하기](https://blog.naver.com/tipsware/221619466275)


## 함수 포인터

  - `리턴 타입 (*포인터 이름)(매개변수)` 의 형태를 가진 포인터 타입이다. (`C`와 동일한 형태)
    - 이름에 괄호를 넣은 이유는 `포인터 변수를 리턴하는 함수의 전방선언` 으로 해석될 여지가 있기 때문이다. 괄호의 추가로 우선순위가 높아졌다.

```cpp
  int *Func();   // Func 함수의 전방 선언(forward declaration)
  int (*pFunc)(); // int(*)() 형의 함수 포인터 정의
```
  - 함수의 이름 앞에 `주소연산자(Address-of operator, &)`를 붙여 주소를 대입할 수 있다.
 
  - 주소연산자의 생략이 가능하다.
  - 포인터로 함수 호출 시, 암시적 역참조를 허용하여 일반 함수 호출과 동일한 형태로 사용이 가능하다.
  
```cpp
  (*Func)(); // 원래 형태
  Func();    // 암시적 추론을 통한 역참조
```
  - 멤버 함수는 위의 전역 함수, 정적 멤버 함수가 사용하는 타입과 형태가 다르다.
    - `리턴 타입 (소속 클래스::*포인터 이름)(매개변수)`

    - 함수의 주소가 대입, 사용될 때의 소속과 this 포인터의 자료형을 결정하기 위해 `범위 지정 연산자(::)`를 사용하여 어디 영역의 함수인지 정확히 지정해주어야 한다.
    - `&소속 클래스::함수명` 의 형태로 주소를 대입해야 한다.
    - 주소연산자 생략 시 `비표준 구문`으로 처리해서 컴파일 시 오류가 발생한다.
      - 함수 이름의 표현법을 다양한 문법에서 사용하기 때문에 구분을 명확히 하기 위해 비표준 처리
    - `&객체.함수명` 을 대입할 경우 `바인딩 오류`가 발생한다. (윗문단 코드의 주석에 설명있음)
    - 포인터 사용 시 `포인터-멤버 연산자 (.*, ->*)` 를 이용하여 객체와 연결한다.
  - 포인터 변수에 바인딩된 함수의 접근 제한자는 무시된다. `private` 멤버 함수도 맘대로 접근할 수 있다.
    - **주소를 바로 호출**하는 것이기 때문에 로우 레벨에서 기능이 존재하지 않는 접근 지정자는 적용되지 않는다.
    - 물론 함수 포인터 초기화 시에는 접근 지정자를 따른다.
    - 캡슐화를 어기는 프로그래밍이지만 콜백 함수로 많이 쓴다.
    
```cpp
  // typedef void(CTest::*CTestFuncPointer)();
  using CTestFuncPointer = void(CTest::*)(); // C++11
  CTestFuncPointer pMemFunc = &CTest::foo;
  //void(CTest::*pMemFunc) = &CTest::foo; // alias를 사용 하지 않는 경우
  
  CTest test;
  CTest pTest = new pTest;
  (test.*pMemFunc)();
  (pTest->*pMemFunc)();
```


---
# 템플릿

  - TODO
  - [바튼-넥만 트릭](https://wikidocs.net/481)