- [용어 정리](#용어-정리)
- [함수 호출 규약](#함수-호출-규약)
- [객체 지향 프로그래밍](#객체-지향-프로그래밍)
- [Enum, Enum class 차이](#enum-enum-class-차이)
- [const pointer](#const-pointer)
- [동적할당](#동적할당)
- [레퍼런스](#레퍼런스)
- [재귀함수](#재귀함수)
- [for 종류](#for-종류)
- [문자열](#문자열)
- [파일 입출력](#파일-입출력)
- [메모리](#메모리)
  - [프로그램 실행 순서](#프로그램-실행-순서)
  - [가상 메모리(virtual memory)](#가상-메모리virtual-memory)
  - [프로세스](#프로세스)
- [프로그램 실행](#프로그램-실행)
  - [컴파일러](#컴파일러)
  - [컴파일 과정](#컴파일-과정)
  - [헤더 파일](#헤더-파일)
  - [링커(Linker, Link Editor)](#링커linker-link-editor)
  - [로더(Loader)](#로더loader)
- [Value Categories](#value-categories)
  - [L-Value](#l-value)
  - [R-Value](#r-value)
- [구조체](#구조체)
- [클래스](#클래스)
  - [생성자와 소멸자](#생성자와-소멸자)
  - [Initialization](#initialization)
    - [Non-Static Data Member Initialization (NSDMI, 비정적 데이터 멤버 초기화)](#non-static-data-member-initialization-nsdmi-비정적-데이터-멤버-초기화)
  - [Uniform Initailizer](#uniform-initailizer)
  - [Member Access Control (접근 지정자)](#member-access-control-접근-지정자)
- [상속과 가상 함수](#상속과-가상-함수)
  - [상속 (Inheritance)](#상속-inheritance)
  - [가상 함수 (Virtual Function)](#가상-함수-virtual-function)
  - [Abstract class, Pure Virtual Function (추상클래스, 순수 가상 함수)](#abstract-class-pure-virtual-function-추상클래스-순수-가상-함수)
  - [Virtual Function Table (가상 함수 테이블)](#virtual-function-table-가상-함수-테이블)
  - [Virtual Inheritance (가상 상속)](#virtual-inheritance-가상-상속)
  - [Virtual Base Table (가상 베이스 테이블, vbtable)](#virtual-base-table-가상-베이스-테이블-vbtable)
- [변수 범위, 주기, 링크](#변수-범위-주기-링크)
- [리터럴 (Literal)](#리터럴-literal)
  - [문자열 리터럴](#문자열-리터럴)
- [키워드](#키워드)
  - [this 키워드](#this-키워드)
  - [static 키워드](#static-키워드)
  - [extern 키워드](#extern-키워드)
  - [virtual 키워드](#virtual-키워드)
  - [inline 키워드](#inline-키워드)
  - [const 키워드](#const-키워드)
  - [volatile 키워드](#volatile-키워드)
  - [constexpr 키워드](#constexpr-키워드)
  - [explicit 키워드](#explicit-키워드)
  - [\_\_declspec 키워드](#__declspec-키워드)
  - [noexcept 키워드](#noexcept-키워드)
- [연산자](#연산자)
  - [sizeof 연산자](#sizeof-연산자)
  - [캐스팅 연산자](#캐스팅-연산자)
  - [범위 지정 연산자](#범위-지정-연산자)
  - [연산자 오버로딩](#연산자-오버로딩)
- [함수](#함수)
  - [멤버 함수와 가상 함수 예제](#멤버-함수와-가상-함수-예제)
  - [함수 포인터](#함수-포인터)
  - [함수 바인딩](#함수-바인딩)
- [템플릿](#템플릿)
- [스레드](#스레드)
  - [atomic](#atomic)
  - [Coroutines (C++20)](#coroutines-c20)

---


## CPP Study
  - 몰랐거나 까먹기 쉬운 C++ 정보를 기록해놓는 문서

  - 알아야 할 것 : 프로그래밍 설계패턴 (컴포넌트 지향 프로그래밍, 데이터 지향 프로그래밍, 등등), 함수 호출 규약, 메모리 단편화

  - 공식 문서 참고
    - [cppreference](https://en.cppreference.com/w/cpp)
    - [Microsoft C++ Language documentation](https://docs.microsoft.com/en-us/cpp/cpp/?view=msvc-170)

---
# 용어 정리

  - 이름 : 무언가를 지칭하는 단어. 가장 큰 개념

  - 간단한 포함관계 
    - 실체가 없는 것 : 이름 > 식별자 > 키워드
      - 어휘적 표현 요소(lexical element), Lexical analysis 시 나오는 토큰이라 볼 수 있다.
  
    - 실체가 있는 것 : 엔터티 > 객체, 타입
      - 실재하는 메모리 내의 저장 공간(값)을 가진다.

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
    - 전처리기가 처리하는 매크로 지시자(`macro directive`, `#define`)는 엔터티가 아니다.
  
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
    - 둘의 가장 큰 차이점은 **메모리를 할당, 사용하는가** 이다.
 
    - 메모리를 할당하지 않고 식별자만 알려준다면 `선언`, 메모리가 할당된 식별자는 `정의`
    - 선언(`declaration`)
      - 엔터티의 타입과 기타 다른 특성에 대한 정보를 가지고 엔터티에 고유한 이름을 지정하는 것
      - 정의하기 전에 사용하기 위해 선언하는 것을 `전방 선언(forward declaration)` 이라고 한다.
      - 전방 선언은 여러번 가능하며, 컴파일 시점에서 구현부 확인이 되지 않으면 에러가 발생한다. (`.cpp` 파일에 `#include` 전처리 지시자를 통한 헤더 코드의 복사가 이루어져야 한다.)
    - 정의(`definition`)
      - 엔터티가 프로그램에서 사용될 때 컴파일러가 기계어 코드를 생성하는데 필요한 모든 정보를 제공하는 것
      - 클래스 작성은 선언과 동시에 정의를 하는 것과 같다. 몸체 부분이 없으면 `전방 선언`과 동일하게 취급한다.
      - 멤버 함수도 선언과 정의를 분리할 수 있다.

  - ### [Built-in(fundamental) Types](https://docs.microsoft.com/en-us/cpp/cpp/fundamental-types-cpp?view=msvc-170)
    - `C++` 언어 표준에서 지정되어 컴파일러에서 기본 제공되는 타입
  
    - 정수형(`integral`), 부동소수점, `void` 세 가지 메인 카테고리로 나뉜다.

  - ### [Trivial Type](https://docs.microsoft.com/en-us/cpp/cpp/trivial-standard-layout-and-pod-types?view=msvc-170#trivial-types)
    - `C++` 클래스 또는 구조체가 `compiler-provided` 또는 `기본 특수 멤버 함수(생성자 등)` 를 가질 때의 타입이다.
    
    - 연속된 메모리 영역을 가지며 컴파일러가 자유롭게 멤버의 순서를 결정할 수 있다.
  
  - ### [POD(Plain Old Data) type](https://docs.microsoft.com/en-us/cpp/cpp/trivial-standard-layout-and-pod-types?view=msvc-170#pod-types)
    - 클래스 또는 구조체가 `trivial`, `standard-layout` 속성을 모두 가질 때의 타입이다.
  
    - C언어와 호환이 가능하다.
    - `int` 와 같은 `스칼라 타입`도 포함된다.
    - [cppreference 링크](https://en.cppreference.com/w/cpp/named_req/PODType)
  
  - ### [Literal type](https://docs.microsoft.com/en-us/cpp/cpp/trivial-standard-layout-and-pod-types?view=msvc-170#literal_types)
    - `컴파일 타임`에 타입이 결정되는 레이아웃을 의미한다.
  
    - 아래의 타입들이 리터럴 타입이다.
      - `void`
      - `scalar type`
      - `reference`
      - 위의 세 타입으로 이루어진 `배열`
      - `기본 소멸자`, 하나 이상의 `constexpr 생성자 (복사, 이동 생성자 제외)`를 가지는 `클래스`. 모든 비정적 데이터 멤버들이 `리터럴 타입`이고 `volatile`이 아니어야 한다.
  
  - ### [cv type qualifiers](https://en.cppreference.com/w/cpp/language/cv)
    - [상수(`const`), 휘발성(`volatile`) 한정자](#const-키워드)를 의미한다.

  - ### [Translation(Compilation) Unit](https://docs.microsoft.com/en-us/cpp/cpp/program-and-linkage-cpp?view=msvc-170)
    - `C++` 에서 컴파일의 기본 단위(`basic unit`) 이다.
  
    - `C preprocessor`에 의해 전처리가 끝난 한 개의 `소스 파일`의 컨텐츠들로만 이루어져 있다.
      - 전처리가 끝난 후이기 때문에 직, 간접적으로 포함된(`#include`로 복사된) 헤더 파일의 코드도 포함되어 있다.
    - 한 개의 유닛은 `object file`, `library`, `exe` 파일로 컴파일 할 수 있다.


  - 참고 
    - [Basic Concept of C++ Language](https://en.cppreference.com/w/cpp/language/basic_concepts) 
    - [identifier vs keyword](https://stackoverflow.com/questions/7279227/c-what-is-the-difference-between-identifier-keyword-name-and-entity)
    - [entity vs identifier](https://stackoverflow.com/questions/13542905/whats-the-difference-between-entity-and-identifier)
    - [difference between object and instance](https://stackoverflow.com/questions/22206044/difference-between-object-and-instance-c)
    - [Class and Objects](https://isocpp.org/wiki/faq/classes-and-objects#overview-object)
    - [is_pod Class](https://docs.microsoft.com/en-us/cpp/standard-library/is-pod-class?view=msvc-170)
    - [Data Type Ranges](https://docs.microsoft.com/en-us/cpp/cpp/data-type-ranges?view=msvc-170)
    - [What is a "translation unit" in C++](https://stackoverflow.com/questions/1106149/what-is-a-translation-unit-in-c)


---
# 함수 호출 규약

  - TODO
  - 참고
    - https://blog.kimtae.xyz/7

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
# for 종류

  - TODO 정리
  - https://hycszero.tistory.com/81


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
# 메모리

  - TODO : 운영체제 문서로 옮기자
  - 사전적 의미 : 주기억장치, 1차 기억 장치와 동의어다.
  - 여기서 말하는 `메모리 구조`는 언어만의 메모리 구조가 아닌 **운영체제에서 나눈 개념**에 가깝다. 운영체제가 효율적으로 저장공간을 관리하기 위해서 도입한 것이다.
  - `언어의 표준 문서`에는 메모리에 관련된 개념이 **아예 없다**. (지역변수의 스택 개념 이런것도 없음)
  - 메모리 영역(Section)은 크게 4가지로 나뉜다 : 스택, 데이터, 힙, 코드

  - ## **텍스트 or 코드** : 유저가 작성한 코드가 저장되는 영역
    - 컴파일러가 작성한 코드를 바이너리코드(0, 1 로 구성된 코드)로 만든 뒤 실행파일을 생성한다.
  
    - 실행파일을 더블클릭해서 실행을 하게 되면 바이너리 코드가 메모리에 올라가는데(Load) 이 때 운영체제가 맨 처음 접근하는 곳이 코드 영역이다.
    - 읽기 전용이다.
  - ## **데이터** : `전역변수`, `정적(static)변수`들의 메모리가 할당되는 영역
    - `전역변수` : 함수의 외부에 선언된 변수
  
    - `rodata`, `data`, `bss` 로 영역이 나뉜다.
      - `rodata` : 상수 키워드(const)로 선언되는 영역, 시스템에 사용된 각종 문자열들을 저장한다. **읽기 전용이지만** 데이터 영역에 존재한다.
        - `지역 변수`는 `const` 키워드가 붙어도 `스택 영역`에 저장된다. 스코프 종료시 삭제되어야 하기 때문이다.
        - `문자열 리터럴`이 여기에 저장된다. `C++`에서 문자열 리터럴은 `const char*` 타입이다.
        - `char x[] = "hello"` 라는 문장에서 "hello"는 문자열 리터럴로 저장이 되는가? -> 기본 컴파일 옵션으로 진행 시 `저장된다.`
        - 아래 사진에서, 둘 모두 `std::_Sys_errtab` 이라는 곳에서 값을 가져오는 것을 볼 수 있다.
          ![](img/string_literal.png)
     
      - `data` : 읽기, 쓰기가 가능한, 0이 아닌 값으로 초기화된 전역변수 또는 정적변수를 저장한다.
      - `bss(block stated symbol)` : 초기화되지 않았거나 0으로 초기화하는 `전역변수` 또는 `정적변수`를 저장한다.
        - 실행 파일 내부에서 데이터 없이 `해당 섹션의 길이`만 저장해 놓는다.
        - `startup()` 함수가 메인 함수 실행 전 `Zero Initialization`를 진행한다.
    - 프로그램이 종료될 때 메모리에서 정리가 된다.
  - ## **힙** : 동적할당된 메모리가 할당되는 영역
    - 런타임 시 크기가 정해진다.
 
    - 선입선출(FIFO) 방식으로 가장 먼저 들어온 데이터가 가장 먼저 나간다.
    - 메모리의 낮은 주소에서 높은 주소로 할당된다.
    - 힙 영역이 스택 영역을 침범하는 경우를 `힙 오버플로우`라고 부른다.
  - ## **스택** : `매개변수` 혹은 `지역변수`들의 메모리가 할당되는 영역
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
    - [constant와 관련된 질문](https://kldp.org/node/155779)
    - [What is the difference between char s[] and char *s?](https://stackoverflow.com/questions/1704407/what-is-the-difference-between-char-s-and-char-s)


## 프로그램 실행 순서

![](img/execution.png)


## [가상 메모리(virtual memory)]()

  - TODO


## 프로세스

  - TODO 
  - https://www.qaupot.com/posts/d925b3d8f85a4857887b905ce22fdbce





---
# 프로그램 실행

## [컴파일러](https://en.wikipedia.org/wiki/Compiler)

  - 특정 프로그래밍 언어로 쓰여 있는 문서를 다른 프로그래밍 언어로 옮기는 언어 번역 프로그램
 
  - 좁은 의미로는 고수준 언어로 쓰인 소스 코드(원시 코드)를 저수준 언어(어셈블리어, 목적 코드, 기계어 코드)로 번역하는 프로그램이다.
  - 원래의 문서를 `소스 코드(원시 코드)`, 출력된 문서를 `목적 코드`라고 부른다.
  - 프로그램 컴파일 시 각 `.cpp` 파일들은 컴파일 단위(`translation unit`)로 독립적으로 컴파일된다.
  - 컴파일러는 다른 컴파일 단위에서 선언된 이름을 알지 못하기 때문에 각 `.cpp` 파일에서 사용하는 클래스, 함수, 전역 변수에 대한 선언을 제공해야 한다.
  - 때문에 해당하는 선언들을 한데 모아 `헤더`라는 하나의 파일로 만든 뒤 `#include` 전처리 지시자(`directive`)를 통해 한번에 복사 붙여넣기 하는 방법을 선택했다.
  - ### `목적 코드`에는 구현부에서 사용된 `엔터티들의 존재 유무`만 헤더를 통해 확인하고 생성한 것이기 때문에 실제 구현부 코드들의 주소는 연결되어 있지 않다.
    - 코드들이 하나의 파일에 모여있는 것이 아니기 때문이다.
 
    - `링커`가 코드들을 하나의 파일로 만들면 코드의 `위치`가 생기며, 구현부 코드의 심볼을 찾아 실제 주소를 매핑한다.
  - [인터프리터](https://ko.wikipedia.org/wiki/%EC%9D%B8%ED%84%B0%ED%94%84%EB%A6%AC%ED%84%B0)와는 구분되지만 최근에는 `JIT 컴파일` 등의 기술로 실시간 컴파일을 수행하기 때문에 기술적 구분은 사라지는 추세다.
  - `LLVM(Low Level Virtual Machine)`은 컴파일러의 기반구조이다. (TODO 자세히 알아볼 필요가 있다.)
  - 컴파일러를 컴파일 하고자 하는 프로그래밍 언어로 작성하는 과정을 [bootstrapping (부트스트래핑)](https://en.wikipedia.org/wiki/Bootstrapping_(compilers)) 이라고 한다.
  - 참고
    - [LLVM](https://ko.wikipedia.org/wiki/LLVM)
    - [헤더 파일과 소스코드 파일의 분리](https://www.qaupot.com/posts/3ded7e111b994e4c8ab04c0b8c636894)


## [컴파일 과정](https://en.wikipedia.org/wiki/Compiler)

  - 과정은 모든 컴파일러가 조금씩 다르지만 크게 사용하는 몇 가지로 분류한다.
  - 컴파일 디자인의 정확한 페이즈 수에 관계 없이 세 가지 단계 중 하나에 할당할 수 있다.
  - ### `front end` : 입력을 스캔하고 `소스 언어`에 따라 구문(`syntax`)과 의미론(`semantics`)을 검증한다. 결과물로 `intermediate representation(IR, 중간 표현)`이 나온다.
    - `Lexical analysis (어휘 분석, tokenization)`
      - 텍스트를 `lexical token` 이라 불리는 조각들로 나눈다. 토큰은 이름과 값으로 구성된 `pair` 이다.
  
      - 어휘소(`lexeme`) 단위로 카테고리를 나누는 `스캐닝`, 어휘소를 처리된 값으로 변환하는 `평가` 두 단계로 나뉘어서 토큰이 생성된다.
    - `Preprocessing (전처리)`
      - `매크로`를 치환하고 `조건부 컴파일 (#if 같은거)`을 지원한다.
  
      - 보통 구문 의미분석 전에 발생하지만 `scheme`같은 일부 언어는 통사적 형태(문법)에 기반한 매크로 치환을 지원한다.
    - `Syntax analysis (구문 분석, parsing)`
      - 구문 구조를 식별하기 위해 토큰의 선형 시퀀스로 `구문 분석 트리`를 생성한다.
    - `Semantics analysis (의미 분석)`
      - `분석 트리`에 의미 정보를 추가하고 `symbol table(심볼 테이블)`을 구축한다.
        - [심볼 테이블](https://ko.wikipedia.org/wiki/%EC%8B%AC%EB%B3%BC_%ED%85%8C%EC%9D%B4%EB%B8%94)은 이름, 타입, 스코프의 정보를 가지는 `해시 테이블`이다.
        
        - `링커`는 심볼 테이블을 이용해서 외부 참조들(목적 파일에 없는 변수나 함수들)을 연결한다.
  
      - 타입 에러 체크, 개체 바인딩(변수와 함수 참조를 정의와 연결), 정의 할당(지역 변수를 사용하기 전에 초기화)과 같은 의미론적 검사를 수행한다.

      ![](img/lexer_and_parser.gif)
  - ### `middle end (optimizer)` : 대상 CPU 아키텍쳐와 무관한 `IR`에 대한 최적화를 수행한다.
    - `Analysis (분석)`
      - `IR`에서 프로그램 정보를 수집한다.
  
      - `dependency analysis`, `alias analysis`, `pointer analysis`, `escape analysis` 등을 가지고 `사용 가능한 체인`을 구축한다.
      - `control-flow graph` (if, for, while같은 분기 흐름 그래프), [call graph](https://en.wikipedia.org/wiki/Call_graph) (노드들의 함수 호출 그래프) 또한 이 단계에서 작성된다.

      ![](img/call_graph.png)
    - `Optimization (최적화)`
      - 기능적으로는 동일하지만 더 빠른(더 작은) 형태로 변환한다.
    
      - `inline expansion`, `dead code elimination`, `constant propagation`(상수, 리터럴식을 미리 계산해버림), `loop transformation`, `automatic parallelization`(멀티스레드 및 벡터화된 코드로 변환하는 것) 등이 자주 쓰이는 최적화이다.
      - 해당 최적화의 활성화 여부를 알려주기 위해 컴파일 옵션을 사용해야 한다.
    - 가장 기능이 많고 다양하며 중요하기 때문에 자세히 알아보려면 각 옵션들을 따로 찾아보자. 
    - [컴파일러 최적화 위키](https://en.wikipedia.org/wiki/Optimizing_compiler)

  - ### `back end` : 최적화된 `IR`을 `middle end`에서 받아 대상 CPU 아키텍쳐에 특화한 분석, 변환 및 최적화를 수행한다.
    - `Machine Dependent Optimization (시스템 종속 최적화)`
      - CPU 아키텍쳐의 세부 사항에 따라 달라진다.
 
      - [peephole optimization](https://en.wikipedia.org/wiki/Peephole_optimization) (짧은 어셈블러 명령 시퀀스를 효율적인 명령으로 다시 쓰는 것)이 대표적이다.
    - `Code Generation (코드 생성)`
      - `IR` 을 출력 언어(보통 기계어)로 번역한다.
 
      - [addressing mode](https://en.wikipedia.org/wiki/Addressing_mode) (레지스터와 메모리에 어떤 변수를 넣을지 결정하는 것)와 함께 `리소스와 스토리지 결정`(적절한 기계어 명령의 선택과 스케줄링) 이 포함된다.
      - 디버깅을 쉽게 하기 위해 `디버그 데이터`를 생성할 때도 있다.
  
  - 참고
    - [Compile 과정](https://www.qaupot.com/posts/b91a4268bce74d4c90378059fe0aca3a)
    - [#ifndef, #pragma once and Unity Build](https://oojjrs.tistory.com/32)


## [헤더 파일](https://docs.microsoft.com/en-us/cpp/cpp/header-files-cpp?view=msvc-170)

  - 변수, 함수, 클래스 등과 같은 프로그램 요소의 이름을 사용하기 위해 선언해놓는 파일
 
  - ### `중복 참조`
    - 헤더 파일이 여러 번 포함되어 같은 이름의 엔터티들이 **여러번 정의 되는 상태**
 
    - 이것을 피하기 위해 `인클루드 가드(Include Guard, 헤더 가드)`라는 지시자를 사용한다.
    - `#ifndef __파일이름_H, #define __파일이름_H, #endif` 사이에 헤더 코드를 작성
    - `#pragma once` 지시자는 MSVC나 몇몇 다른 컴파일러에서 `#ifndef, #define, #endif` 지시자를 사용한 것과 동일하게 동작한다.
  
  - ### `순환 참조` 
    - **서로의 헤더 파일을 `include` 하는 상태**. 무조건 피해야 한다.
   
    - 이것을 피하기 위해 `전방 선언` 을 하고, 헤더는 선언한 엔터티의 정의가 있는 `.cpp` 파일에서 인클루드 한다.
      - 구현부에서 포함하여 헤더가 서로를 모르게 한다.
    - 전방 선언 시 구현부에서는 해당 엔터티가 정의된 헤더를 참조해야 한다.
  - 컴파일 시 [Name Mangling(name decoration)](https://en.wikipedia.org/wiki/Name_mangling) 기법이 적용된다.
    - 컴파일러가 같은 식별자를 가진 다른 엔터티들의 구분을 위해 임의로 함수나 변수의 이름을 변경하는 것
   
    - 함수 오버로딩의 동작을 위해 필요한 기능이며, 컴파일러마다 다른 mangling 규칙을 가지고 있다.
    - C와 C++은 mangling 규칙이 다르다. C는 함수 오버로딩 기능을 제공하지 않아서 한 바이너리 안에 하나의 심볼만이 존재하기 때문이다.
    - `.c` 파일과 `.cpp` 파일을 동시에 컴파일하면 둘의 `Naming Mangling` 이 다르기 때문에 링크 에러(LNK2019)가 발생한다.
    - `extern "C"` 지시어를 사용하면 C++로 짜여진 코드를 C와 호환되게 만들 수 있다. (C의 Mangling 규칙을 따라가며, `POD` 타입이어야 한다) 
  - 
  - 참고
    - [컴파일, 링킹, 헤더파일](https://code4human.tistory.com/110)
    - [C++상에서 발생하는 name mangling 에 관한 내용](https://spikez.tistory.com/19)
    - [헤더 파일과 소스코드 파일의 분리](https://www.qaupot.com/posts/3ded7e111b994e4c8ab04c0b8c636894)
    - [Link Error 발생시 확인해볼 것들](https://vaert.tistory.com/5)


TODO 질문 : 링커가 obj 파일들을 exe 파일로 만들 때 각 obj 파일마다 중복되는 헤더들도 다같이 복사되는가? 제거할 수있는 방법은 모든 코드를 한 파일에 쓰는방법 밖에 없는가?



## [링커(Linker, Link Editor)](https://ko.wikipedia.org/wiki/%EB%A7%81%EC%BB%A4_(%EC%BB%B4%ED%93%A8%ED%8C%85))

  - `컴파일러`가 만들어낸 하나 이상의 `목적 파일`을 가져와 이를 단일 실행 프로그램(`lib`, `dll`, `exe`)으로 병합하는 프로그램

  - `컴파일러`의 일부로 생각하는 사람도, 생각하지 않는 사람도 있다.
  - `링커`는 여러 `목적 파일`들을 통일된 실행 프로그램으로 결합하면서 `심볼`들을 해결한다.
    - 여러 개의 부품/모듈들은 `심볼`을 통해 다른 모듈로의 주소로 서로를 지칭한다.
  
    - `defined external symbol` (`public`, `entry symbol`, 다른 모듈에서 호출가능한 심볼),  `undefined external symbol` (정의된 심볼을 참조하는 심볼),  `local symbol` (한 목적 파일에 존재하는 심볼) 세 가지로 분류한다.
  - `링커`는 또한 프로그램의 주소 공간에 `객체를 재배치하는 역할`을 한다.
    - `컴파일러`는 **객체가 어디 위치할 지 거의 모르기 때문에** 종종 기본 위치(0)를 가정한다. -> 다른 객체의 주소를 요구하는 명령어는 최적화할 수 없다.
   
    - `링커`는 가장 `보수적인` 명령어 (플랫폼에 따라 가장 큰 변형)를 먼저 생성하고, `relaxation hint (완화 힌트)`를 추가하여 최종 링크동안 더 짧거나 더 효율적인 명령어로 대체한다. (`jump`, `load`, `store` 같은 것)
      - 명령어 완화는 대개 링크 시 발생하지만, `내부 모듈 완화`는 컴파일 타임에 최적화 프로세스의 일부로 발생할 수 있다.
 
      - `재배치 프로세스`의 일부로서 또는 `dynamic dead-code elimination` 기법과 결합되어 로드 시간에 발생할 수도 있다.
    - 이 단계는 모든 입력 객체를 읽고 임시 주소를 할당한 후에만 수행할 수 있다.
  - `라이브러리`, `런타임 라이브러리`라고 하는 모음에서 오브젝트를 가져올 수 있다.
    - 전체 라이브러리를 포함시키는 것이 아니라 다른 오브젝트 파일이나 라이브러리가 참조하는 파일들만 포함한다.
  - `Static Linking (정적 링크)`
    - 사용되는 모든 라이브러리 루틴을 **복사하여 실행파일을 생성하는 것**
   
    - **실행파일 하나만 생성**하기 때문에 동적 링크보다 용량은 크지만 휴대성이 좋다.
    - 각 프로그램이 필요한 라이브러리 루틴의 버전을 정확하게 포함하기 때문에 다른 프로그램과 충돌하지 않고 `의존성과 관련된 문제`를 방지한다.
  - `Dynamic Linking (동적 링크, late linking)`
    - 프로그램이 실행될 때까지 정의되지 않은 일부 `심볼`들을 해결하는 일을 미루는 것
   
    - **실행파일 따로, `DLL 파일` 따로 존재**한다.
    - 프로그램을 로드하면 오브젝트와 라이브러리를 로드하고 마지막 링크를 수행한다.
    - 동적 링크는 링커가 필요없다. (운영체제 안에 `동적 링커`라는 프로그램이 수행한다.)
    - 장점 
      - 자주 쓰이는 라이브러리(표준 시스템 라이브러리 같은거)는 한 위치에만 저장되어 있으며 이런 단일 라이브러리들의 중복이 사라진다.
   
      - 라이브러리 함수의 오류를 라이브러리만 수정하는 것으로 해결할 수 있다.
    - 단점
      - 비호환 DLL에 의존적인 실행파일이 만들어 질 수 있다.
   
      - 프로그램, 라이브러리 둘 다 검증해야 한다. (정확성, 문서 요구사항, 성능 등)
  - 참고
    - [What is external linkage and internal linkage?](https://stackoverflow.com/questions/1358400/what-is-external-linkage-and-internal-linkage)
    - [Struct with a value in a header file causing "duplicate symbol" linker error](https://stackoverflow.com/questions/2206853/struct-with-a-value-in-a-header-file-causing-duplicate-symbol-linker-error)
    - [헤더 파일 / Linking 과정](https://www.qaupot.com/posts/71b127e3138d472986757afaceb947c7)


## [로더(Loader)](https://ko.wikipedia.org/wiki/%EB%A1%9C%EB%8D%94_(%EC%BB%B4%ED%93%A8%ED%8C%85))

  - 하드디스크와 같은 오프라인 저장 장치에 있는 프로그램을 찾아서 주기억장치(메모리)에 적재하고, 프로그램이 실행되도록 하는 역할을 담당
 
  - `운영체제` 자체를 로드할 때는 특수한 `boot loader` 가 사용된다.
  - 많은 OS들은 로더를 메모리에 영구적으로 적재하지만, 가상 메모리를 지원하는 OS는 로더를 `호출 가능한 메모리 영역`에 위치시킬 수 있다.
  - 가상 메모리를 지원하는 OS는 실행파일의 내용을 **실제로 메모리에 복사하지 않고** 할당된 메모리 영역과 실행 파일의 내용 사이에 `매핑`이 있다고 `가상 메모리 하위 시스템`에 선언할 수 있다.
    - `가상 메모리 하위 시스템`은 프로그램 실행이 실제로 채워지지 않은 메모리의 해당 영역에 도달하는 경우, 해당 메모리 영역을 가진 페이지를 요청 시 채워야 한다.
  
    - 프로그램 코드가 실제로 사용될 때까지 실제로 메모리에 복사되지 않는다는 것을 의미한다.
    - 사용하지 않는 코드는 메모리에 전혀 로드되지 않을 수 있다.





---
# [Value Categories](https://en.cppreference.com/w/cpp/language/value_category#glvalue)

## L-Value

  - TODO

## R-Value

  - TODO





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
    - `상속` 관계가 있는 객체는 무조건 `베이스 클래스`의 생성자가 먼저 호출된다.

    - `다중 상속`의 경우, `베이스 클래스`들의 초기화 순서는 `base-list`의 순서대로 초기화가 진행된다. (정의순이 아님!)
    - `접근 지정자`에 따라 달라질 수 있다고 하는데(C++23까지만), MSVC컴파일러는 코드순으로 초기화한다.
    - [스칼라 타입](https://en.cppreference.com/w/cpp/types/is_scalar) 변수들은 초기화 구문이 없으면 정해지지 않은 값들이 들어간다. (`default initialization`)
    - [익명 유니온(anonymous union)과 변형 멤버(variant member)](https://en.cppreference.com/w/cpp/language/union#Union-like_class)는 `member initializer`가 없기 때문에 초기화가 안된다.
  - **`가상 베이스 클래스`가 포함된 `가상 상속`의 경우, 초기화 순서와 저장공간 주소 순서 모두 일반 상속과 다르다!** 자세한 내용은 [가상 상속](#virtual-inheritance-가상-상속) 을 참고
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
    - `생성자가 존재하는 타입의 변수`는 **안적어도 알아서 `기본 생성자`를 호출해준다.**(`Value Initialization`) 적을 필요 없음.
    - `상수 타입 변수`는 스칼라 타입이면 에러를, `기본 생성자`를 가진 클래스 타입이면 경고를 띄운다. (다른 초기화를 꼭 사용하자)
    - `정적 변수`는 `zero initalization`이 진행된다.
```cpp
  MyClass mc1;
  MyClass* mc3 = new MyClass;
```

  - ### Zero Initialization
    - 변수를 0값으로 설정하는것, 암묵적으로 타입에 맞게 변환된다.

    - 다음의 상황에 적용된다.
      - 전역 변수들
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

    - `public constructor` 를 가진 클래스는 `기본 생성자`가 호출된다.
    - `default` 키워드로 생성된 생성자가 아닌 사용자가 정의한 기본 생성자인 경우 **초기화 표현이 없는 모든 변수는 `기본 초기화`가 진행된다.** (중요)
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

  - 참고
    - [Uniform Initialization](http://egloos.zum.com/sweeper/v/3058356)

## [Member Access Control (접근 지정자)](https://docs.microsoft.com/en-us/cpp/cpp/member-access-control-cpp?view=msvc-170)

  - 클래스, 구조체, 공용체(유니온) 에서 멤버들의 접근성을 정의하는 `키워드`이다.
  
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
  - `private` 멤버는 다른 멤버들과 `friend`만 접근할 수 있지만, 클래스를 볼 수 있는 모든 코드가 볼 수 있기에, 컴파일 과정의 `함수 오버로드 해소` 과정이나 `모호한 함수 처리` 등의 호출 해소 과정에는 동일하게 참여한다.
    - 컴파일러가 함수 호출을 처리할 때, 아래 세 가지 조건을 순서대로 거친다.
      - 1. `Name Lookup (이름 조회)`
      - 2. `오버로드 해소`
      - 3. `접근성 점검`
  - 컴파일 시 해당 키워드를 처리하는 것이기 때문에 로우 레벨에서 동작하는 모든 기능들은 영향을 받지 않는다. (함수 포인터를 통한 함수 호출 등)
  - `static` 멤버들은 접근 지정자의 영향을 받지 않는다. -> private 변수들 지정자 영향 받더라. 함수만 안받는듯
    - 단, 포인터, 참조, 객체를 통한 접근은 지정자의 영향을 받기 때문에 전역으로 접근해야 한다. (`::CBase::Func()`)
 
    - 포인터, 참조, 객체를 통한 접근은 지정자에 영향을 받는 형식으로 멤버의 `형변환`이 필요하기 때문이다.
  - 파생 클래스의 가상 함수가 `private` 이면, `파생 클래스 객체를 참조`하는 베이스 클래스 포인터는 가상 함수에 접근이 블가능하다. (C2248 에러)
  - 참고
    - [Access specifiers](https://en.cppreference.com/w/cpp/language/access)
    - [private는 얼마나 비공개적인가?](https://wikidocs.net/469), [다른 사이트](http://egloos.zum.com/sweeper/v/2998794)





---
# 상속과 가상 함수

## [상속 (Inheritance)](https://docs.microsoft.com/en-us/cpp/cpp/inheritance-cpp?view=msvc-170)

  - 기존 클래스에서 파생된 새 클래스가 기존 클래스의 특성을 가지는 메커니즘
  
  - 데이터 상으로는 `파생 클래스`의 멤버 데이터 목록에 `베이스 클래스`의 객체를 추가한 것과 동일하다.
    - 일반 단일 상속의 경우, 파생 클래스 멤버 변수들의 앞에 위치한다. 낮은 주소를 가진다.
  
    - 초기화 순서 또한 `베이스 클래스`의 우선순위가 높다.
  - `부모-자식 관계`에서 부모 클래스는 자식 클래스의 `direct base class` 가 되고, `부모-자식-손자 관계`에서 부모 클래스는 손자 클래스의 `indirect base class` 가 된다.
  - `베이스 클래스`는 `파생 클래스` 앞에 선언해야 한다. **전방 선언도 안된다.**
  - 이름이 같은 멤버(변수, 함수)에 접근할 때 `범위 지정 연산자(::)`를 사용하여 베이스 클래스의 멤버로 접근할 수 있다.
    - **베이스 클래스의 가상함수를 호출하고 싶을 때** `obj->CBase::foo()` 이런 식으로 사용한다. 이 때, `가상 함수 메커니즘`은 진행하지 않는다.
  
    - 멤버 변수도 동일하게 접근이 가능한데, **이름이 같은 시점에서 이미 잘못된 코드다.**
  - `C++` 에서는 [다중 상속](https://docs.microsoft.com/en-us/cpp/cpp/multiple-base-classes?view=msvc-170)이 가능하다.
    - `다중 상속`의 경우, `베이스 클래스`들의 초기화 순서는 `base-list`의 순서대로 초기화가 진행된다. (선언순이 아님!)
 
    - 같은 `베이스 클래스`를 여러 번 상속받으면 클래스의 모호성이 발생하는데, 이를 해결하기 위해 `가상 상속`이 도입되었다.
    - 자세한 내용은 [가상 상속](#virtual-inheritance-가상-상속)을 참고하자.
  - `빈 베이스 클래스`를 상속받는 `빈 파생 클래스`의 `typeid` 는 베이스 클래스이다.
    - 파생 클래스를 특정할 수 있는 요인이 하나도 없기 때문이다.
  - [접근 지정자](#member-access-control-접근-지정자)를 사용하여 상속 시 멤버 변수, 함수에 권한을 지정할 수 있다. 
  - `final` 키워드를 사용하여 이후 현재 클래스 또는 가상 함수를 상속받지 못하도록 제한할 수 있다.


## [가상 함수 (Virtual Function)](https://docs.microsoft.com/en-us/cpp/cpp/virtual-functions?view=msvc-170)

  - `파생 클래스(derived class)`에서 재정의할 것이라 예상하는(`expected`)(약속하는?) 비정적 멤버 함수
  
  - `베이스 클래스(base class)`에 **참조 또는 포인터를 사용**하여 `파생 클래스 객체`를 참조할 때, 해당 객체에 대한 가상 함수를 호출하면 `파생 클래스`의 함수를 실행할 수 있다.
    - 이 때 `베이스 클래스`의 소멸자를 가상 함수로 만들지 않으면 **파생 클래스의 소멸자가 호출되지 않는다.** 식별자의 타입이 `베이스 클래스`라서 `파생 클래스`의 존재를 모르기 때문이다.
    
    - 물론 파생 클래스에서 정의한 **모든 멤버 변수들도 소멸되지 않는다.**
  - 가상 함수를 재정의 (`override`) 하는 모든 함수는 가상 함수이다. (`virtual` 키워드가 생략되어 있다.)
    - `override` 키워드를 명시적으로 사용하여 예기치 못한 에러를 방지할 수 있다. (`const` 등을 빼먹어서 다른 함수로 만든다든지..)
 
    - 재정의 시 `접근 지정자`의 영향을 받지 않는다.
    - 사람의 실수 체크를 위한 어휘적 요소일 뿐, 메모리와는 상관없기 때문이다.
  - **포인터, 레퍼런스 타입의 객체**에서 `가상 함수`는 **가상함수 테이블에서 주소를 찾아** 함수를 호출한다.
  - `주소 타입이 아닌 객체`에서의 함수는 `가상함수 테이블`을 사용하지 않는다. 
    - 테이블 자체는 존재한다. 객체 1개당 8바이트(주소 크기)가 추가로 소모되는 것이다.
  - 함수 처리 전에 `가상함수 테이블`에 들어가서 주소를 가져오는 작업이 추가되기 때문에 꼭 필요한 경우가 아니면 사용하지 말자.
  - `포인터, 레퍼런스 타입 객체`의 함수 호출 코드는 `객체 내 포인팅 하는 클래스의 시작 주소`, `가상함수 판단`의 정보를 가진다.
    - 함수가 가상 함수이면 `가상함수 오프셋(상대 위치값)` 정보를, 비가상 함수이면 `클래스::함수()의 주소`를 가진다.
   
    - 주소 타입이 아니면 비가상 함수와 동일한 정보를 가진다.
    ```cpp
      CDerived derived;
      CDerived& refDerived = derived;
      derived.foo();          // 일반 함수, 바로 호출
      refDerived.foo();       // 일반 함수, 바로 호출
      derived.vFoo();         // 가상 함수, 바로 호출
      refDerived.vFoo();      // 가상 함수, 테이블 경유
    ```
    ![](img/virtual_func_assembly.png)

  - 베이스 클래스를 참조하는 파생 클래스 객체에서, `베이스 클래스의 비가상 함수`를 호출했을 때, 베이스 클래스의 멤버 변수만 접근할 수 있다.
    - 당연하다. 베이스 클래스는 **파생 클래스의 존재를 모르기 때문**이다. 접근하려면 `다운 캐스팅`을 하면 된다.
  
    - 상속 메커니즘의 클래스 멤버 변수 앞에는 `this`포인터와 `범위 지정 연산자`가 생략되어 있다. `this->변수` 가 아니라 `this->클래스::변수` 이다. 
    - 메모리에서 해당 클래스의 위치로 이동한 다음 해당 클래스의 `멤버 변수 오프셋`을 통해 주소로 접근하는 것이다.
    ```cpp
      void foo() {               // CDerived 클래스의 비가상 함수
        char* tmp;               //
        tmp = mName;             // == CDerived::mName
        tmp = CBase::mName;
        tmp = CDerived::mName;
      }
    ```
    ![](img/inherit_member_scope.png)
    - 위 사진의 `CDerived` 객체 메모리는 `가상함수 테이블 (+0)`, `CBase::mName (+8)`, `CDerived::mName (+16)` 으로 구성되며, 크기는 24바이트이다.

  - 참고
    - [virtual function specifier](https://en.cppreference.com/w/cpp/language/virtual)
    - [가상함수와 상속](https://modoocode.com/211)
    - [가상함수와 가상함수테이블의 이해](https://cosyp.tistory.com/228)


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

## Virtual Function Table (가상 함수 테이블)

  - 클래스에 하나 이상의 `가상 함수`가 존재할 경우 생성되는 리스트
 
  - `컴파일 타임`에 클래스 정의를 바탕으로 `PE(Portable Executable, 실행 파일)`에 기록해 놓는다.
    - `데이터의 rodata 영역` 에 저장된다.
   
    - **상속 관계 상관없이 클래스 타입 마다 하나씩 생성된다.**
  - `가상 함수`가 선언된 클래스의 가장 앞에 배치한다. (객체 내 위치 기준)
  - `가상 함수 테이블` 저장 순서는 베이스 클래스 가상 함수 -> 파생 클래스 가상 함수 순이다.
    - `선언`한 순서대로 `함수 주소`를 테이블에 채워넣는 형태다.

  - 객체 내 `테이블의 개수`는 `상속 라인의 개수`와 동일하다. (`가상 상속`은 같을 수도, 다를 수도 있다. 밑에 서술함)
    - 라인이 같으면 `기존 테이블의 주소`에 현재 테이블의 주소를 덮어쓴다.
      - 그래서 `재정의`는 객체 내 테이블 생성에 영향을 주지 않는다.
  
    - 라인이 다르면 접근할 수 있는 `가상 함수의 종류`가 바뀌기 때문에 새로운 테이블 주소가 추가된다.
    - 같은 위상의 `베이스 클래스`들은 **서로의 가상 함수를 모르고** 각자의 `함수 오프셋`을 가지기 때문이다.
    ```cpp
      class CBase1 {
        public:
        char* mName{"CBase1"};
        CBase1() {}
        virtual ~CBase1() {}
        virtual void vFoo1() {}
      };
      class CBase2 {
        public:
        char* mName{"CBase2"};
        CBase2() {}
        virtual ~CBase2() {}
        virtual void vFoo2() {}
      };
      class CDerived : public CBase1, public CBase2 {
        public:
        char* mName{"CDerived"};
      };

      int main() {
        CDerived derived;
        CBase1& base1 = derived;               // derived 객체의 CBase1 부분을 포인팅
        CBase2& base2 = derived;               // derived 객체의 CBase2 부분을 포인팅
        base1.vFoo1();
        base2.vFoo2();
        std::cout << base1.mName << std::endl; // == base1.CBase1::mName == derived.CBase1::mName
        std::cout << base2.mName << std::endl; // == base2.CBase2::mName == derived.CBase2::mName

        return 0;
      }
    ```
    ![](img/multi_vftable.png)
    - 위의 코드에서, 서로 다른 `가상 함수`가 같은 오프셋(+8)로 호출되는 것을 볼 수 있다.

    - `베이스 클래스` 별로 각각의 테이블 주소를 갖고 있어, 해당 테이블에 맞는 함수를 가져오는 것이라고 판단할 수 있다.
    - 각각의 멤버 변수(mName) 에 접근하는 `오프셋`도 **포인터의 타입에 따라간다**는 것을 알 수 있다. (둘 다 +8의 오프셋을 가진다, 0의 자리에는 `가상함수 테이블 주소`가 있다)
    
      ![](img/multi_vftable_ctor.png)
    - 각 `베이스 클래스`의 생성자 호출 후 `가상 함수 테이블` 주소를 덮어쓰는 것을 볼 수 있다. (+0과, +16 두 번)
    - 두 개의 `가상 함수 테이블`은 주소가 다르다, 즉, `CBase1`에 대한 테이블과 `CBase2`에 대한 테이블이 따로 존재하는 것이다.
  
  - `순수 가상 함수`도 `가상 함수 테이블`에 포함된다!
    - **이론적으로 존재하지 않는 함수**지만, 실제론 컴파일러가 `__purecall` 이라는 함수로 채워넣는다.
 
    - 해당 가상 함수를 호출 시, `R6025 런타임 에러`가 발생한다.
    - `상속 구조`에서 생성자를 통해 뭔가를 하는 코드를 작성하는 경우, 함수 호출 순서를 잘 따져봐야 한다.
    - 제일 좋은 방법은 생성자에서 `가상 함수`를 호출하지 않는 것이다.
    - 아래 `참고` 부분에 자세한 설명 링크가 있다.
  
  - 참고
    - [C++의 가상함수 테이블은 언제 생성될까요?](https://www.sysnet.pe.kr/2/0/11167)
    - [__purecall이 무엇일까?](http://www.jiniya.net/tt/597)
    - [C++ vtable의 가상 함수 호출 가로채기](https://www.sysnet.pe.kr/2/0/11169?pageno=0)


## Virtual Inheritance (가상 상속)

  - `다중 상속` 시 여러 개의 `파생 클래스`가 동일한 `베이스 클래스`를 상속받는 경우, 어떤 `베이스 클래스`에 접근해야 할 지 모호해지는 상황이 발생한다.

  - 이러한 `모호성`을 해결하기 위해 `베이스 클래스`를 `가상화`해 객체에 한 번만 포함되도록 만드는 것을 `가상 상속` 이라고 한다.
  - 이 때 `virtual` 키워드를 붙여 `가상화` 하는 클래스를 `Virtual Base Class(가상 베이스 클래스)` 라고 한다. (너무 기니까 `VBClass`라고 줄여쓰겠다.)
  - **여러 번 등장하는 것을 막기 위해 따로 떼내서 특별 취급 하는 것이다.**
  - `VBClass`는 초기화 우선순위가 가장 높다. 순서는 다음과 같다.
    1. `상속 트리` 내의 모든 `VBClass`의 초기화를 진행한다. `VBClass` 간의 순서는 기본 상속의 초기화 순서와 같다. (`base-line` 기준 `DFS(Depth First Search)`)
 
    2. 이후 `base-list` 의 순서대로 클래스 초기화를 진행한다. 이 때, `VBClass`의 호출 코드는 **전부 건너뛴다.**
    3. 마지막으로 해당 객체의 초기화를 진행한다.
  - 객체 파괴 시, 소멸자의 우선순위가 가장 낮다. `일반 상속 클래스` 처리가 모두 끝난 뒤 `VBClass` 의 소멸자를 호출한다.
  - `VBClass`는 해당 객체의 `제일 높은 주소`에 저장된다. 즉, **초기화 순서와 저장되는 클래스의 주소 순서가 다르다.**
    - `베이스 클래스`가 가상화가 되면, `파생 클래스`에서 `베이스 클래스` 부분이 사라지기 때문에 전체적으로 저장공간의 순서가 바뀐다.
      - 일반 객체 구성 순서에서 `VBClass` 부분만 전부 빼내서 뒤(높은 주소)에 붙인 모양새이다.
  
    - `VBClass`가 `가상 함수`를 포함하는 경우(재정의x), **`가상 함수 테이블`의 개수 및 위치가 변경될 수 있다.**
    - 클래스의 주소 순서가 변경되기 때문에, `가상 베이스 테이블(virtual base table)`이라는 것을 도입했다.

  - 복잡하고 내부 계산이 많아 성능 저하가 있기 때문에 애초에 클래스 설계를 제대로 해서 `다중 상속` 상황을 안나오게 하는 것이 제일 효과적이다.
  - 참고
    - [virtual 상속의 원리](https://m.blog.naver.com/PostView.naver?isHttpsRedirect=true&blogId=kyed203&logNo=220207325648)
    - [가상 상속의 득과 실](https://dataonair.or.kr/db-tech-reference/d-lounge/technical-data/?mod=document&uid=235880)


## Virtual Base Table (가상 베이스 테이블, vbtable)

  - `가상 상속` 시 배치가 바뀐 `VBClass`의 위치를 찾기 위해 사용하는 테이블이다.
 
  - 내부에서만 사용하기 때문에 정확한 명칭은 없다. `GCC` 에서는 `Virtual Table Table (VTT)` 이라 부르는 듯?
  - `가상 함수 테이블`처럼 컴파일 중에 `데이터의 rodata 영역` 에 저장된다.
    - `VBClass`를 상속받는 클래스들은 전부 테이블을 하나씩 가진다.
 
  - 현재 클래스 기준 `VBClass`들의 `오프셋(상대 위치값)`을 가진다.
    - 배열의 한 요소가 `dword` 크기, 즉 `주소 크기의 절반` 밖에 사용하지 않는다.
  
    - `절대 경로`를 저장하는 것이 아니라 `오프셋(상대 경로)`만을 저장하기 때문이다.
    - 첫 번째 값에는 무조건 `vbtable`에서 `this`까지의 `오프셋`이 저장된다.
  - `해당 클래스가 원래 있어야 할 곳`에 생성된다. (대신 집어넣은 느낌)
 
  - `함수 호출` 시 다음과 같은 메커니즘을 따른다.
   
    ![](diagram/function_call.png)

  - `가상 함수 테이블`보다 먼저 접근하기 때문에 `vbtable`이 있는 클래스는 `가상 함수 테이블`의 위치가 이동한다.
    - 그래서 `VBClass`의 `가상 함수`를 호출 하면 `vbtable`을 거쳐서 `가상 함수 테이블`에 접근하게 된다.
  
    - 만약 현재 클래스가 새로운 `가상 함수`를 가진다면, 현재 클래스의 `가상 함수`를 가리키는 주소를 **추가한다.**
    - `VBClass`에서 정의된 `가상 함수`와 현재 클래스에서 정의된 `가상 함수`는 **호출 순서와 참조하는 테이블의 주소가 달라진다.**
    - 실제 데이터는 `vftable / vbtable / 현재 클래스의 멤버 / vftable / VBClass의 멤버` 순으로 구성될 것이다.
      - 위의 순서에서 첫번째 `vftable`이 가리키는 주소는 두번째 `vftable` + `VBClass의 가상 함수 개수`가 될 것이다.

  - 예제를 통해 메모리에 어떤 순서로 저장되는지 알아보자. (표에서 테이블 옆에 (+)는 같은 테이블 간 상대 위치 오프셋이다. 표기가 안되어있는건 붙어 있지 않은 것들이다.)
  - (1) `VBClass`가 없는 다중 상속 구조 (56 byte)
    ```cpp
      #include <iostream>
      class CBase {
        public:
          char* mName{"CBase"};
          CBase() {}
          virtual ~CBase() {}

          void foo() {}
          virtual void vFoo() {}
      };
      class CDerived1 : public CBase {
        public:
          char* mName{"CDerived1"};
          CDerived1() {}
          virtual ~CDerived1() {}

          virtual void vFoo1() {}
      };
      class CDerived2 : public CBase {
        public:
          char* mName{"CDerived2"};
          CDerived2() {}
          virtual ~CDerived2() {}

          virtual void vFoo2() {}
      };
      class CGrandson : public CDerived1, public CDerived2 {
        public:
          char* mName{"CGrandson"};
          CGrandson() {}
          virtual ~CGrandson() {}

          void vFoo() {}
      };
      int main() {
        CGrandson* gs = new CGrandson;
        delete gs;

        return 0;
      }
    ```
    | 주소  |    저장된 값     | 값 변경 순서 |   테이블 값(최종)   | 테이블 소유자 변경 과정         | 생성자 호출 순서 |
    | :---: | :--------------: | :----------: | :-----------------: | :------------------------------ | :--------------- |
    |   0   |     vftable      |   1, 3, 9    | dtor / vFoo / vFoo1 | CBase -> CDerived1 -> CGrandson | CBase            |
    |   8   |   CBase::mName   |      2       |                     |                                 | CDerived1        |
    |  10h  | CDerived1::mName |      4       |                     |                                 | CBase            |
    |  18h  |     vftable      |   5, 7, 10   | dtor / vFoo / vFoo2 | CBase -> CDerived2 -> CGrandson | CDerived2        |
    |  20h  |   CBase::mName   |      6       |                     |                                 | CGrandson        |
    |  28h  | CDerived2::mName |      8       |                     |                                 |
    |  30h  | CGrandson::mName |      11      |                     |                                 |
  

  - (2) 1번의 코드에서 `베이스 클래스`들이 각각 `VBClass`를 상속받는 구조 (80 byte)
    ```cpp
      ...
      class CDerived1 : public virtual CBase {
        ...
      };
      class CDerived2 : public virtual CBase {
        ...
      };
      class CGrandson : public CDerived1, public CDerived2 {
        ...
      };
      ...
    ```
    | 주소  |    저장된 값     | 값 변경 순서 | 테이블 값(최종) | 테이블 소유자 변경 과정          | 생성자 호출 순서 |
    | :---: | :--------------: | :----------: | :-------------: | :------------------------------- | :--------------- |
    |   0   |   vftable (+0)   |    5, 11     |     vFoo1 /     | CDerived1 -> CGrandson           | CBase            |
    |   8   |   vbtable (+0)   |      1       |   -8 / 38h /    | CGrandson                        | CDerived1        |
    |  10h  | CDerived1::mName |      7       |                 |                                  | CDerived2        |
    |  18h  |  vftable (+18h)  |    8, 12     |    / vFoo2 /    | CDerived2 -> CGrandson           | CGrandson        |
    |  20h  |  vbtable (+10h)  |      2       |  / -8 / 20h /   | CGrandson                        |                  |
    |  28h  | CDerived2::mName |      10      |                 |                                  |
    |  30h  | CGrandson::mName |      15      |                 |                                  |
    |  38h  |   ? / (34h) 0    |      14      |                 |                                  |
    |  40h  |  vftable (+30h)  | 3, 6, 9, 13  |  / dtor / vFoo  | CBase -> CDer1 -> CDer2 -> CGson |
    |  48h  |   CBase::mName   |      4       |                 |                                  |
  

  - (3) 1번의 코드에서 `베이스 클래스`들이 `VBClass` 인 구조 (80 byte)
    ```cpp
      ...
      class CDerived1 : public CBase {
        ...
      };
      class CDerived2 : public CBase {
        ...
      };
      class CGrandson : public virtual CDerived1, public virtual CDerived2 {
        ...
      };
      ...
    ```
    | 주소  |    저장된 값     | 값 변경 순서 |   테이블 값(최종)   | 테이블 소유자 변경 과정 | 생성자 호출 순서 |
    | :---: | :--------------: | :----------: | :-----------------: | :---------------------- | :--------------- |
    |   0   |     vbtable      |      1       |   0 / 18h / 38h /   | CGrandson               | CBase            |
    |   8   | CGrandson::mName |      14      |                     |                         | CDerived1        |
    |  10h  |   ? / (14h) 0    |      12      |                     |                         | CBase            |
    |  18h  |     vftable      |   2, 4, 10   | dtor / vFoo / vFoo1 | CBase -> CDer1 -> CGson | CDerived2        |
    |  20h  |   CBase::mName   |      3       |                     |                         | CGrandson        |
    |  28h  | CDerived1::mName |      5       |                     |                         |
    |  30h  |   ? / (34h) 0    |      13      |                     |                         |
    |  38h  |     vftable      |   6, 8, 11   | dtor / vFoo / vFoo2 | CBase -> CDer2 -> CGson |
    |  40h  |   CBase::mName   |      7       |                     |                         |
    |  48h  | CDerived2::mName |      9       |                     |                         |


  - (4) 1번의 코드에서 `베이스 클래스`들이 `VBClass`이며 `VBClass`를 상속받는 구조 (88 byte)
    ```cpp
      ...
      class CDerived1 : public virtual CBase {
        ...
      };
      class CDerived2 : public virtual CBase {
        ...
      };
      class CGrandson : public virtual CDerived1, public virtual CDerived2 {
        ...
      };
      ...
    ```
    | 주소  |    저장된 값     | 값 변경 순서 |   테이블 값(최종)   | 테이블 소유자 변경 과정          | 생성자 호출 순서 |
    | :---: | :--------------: | :----------: | :-----------------: | :------------------------------- | :--------------- |
    |   0   |     vbtable      |      1       | 0 / 18h / 28h / 40h | CGrandson                        | CBase            |
    |   8   | CGrandson::mName |      16      |                     |                                  | CDerived1        |
    |  10h  |   ? / (14h) 0    |      15      |                     |                                  | CDerived2        |
    |  18h  |     vftable      | 4, 7, 10, 12 | dtor / vFoo / vFoo1 | CBase -> CDer1 -> CDer2 -> CGson | CGrandson        |
    |  20h  |   CBase::mName   |      5       |                     |                                  |                  |
    |  28h  |     vftable      |    6, 13     |        vFoo1        | CDerived1 -> CGrandson           |
    |  30h  |     vbtable      |      2       |      -8 / -18h      | CGrandson                        |
    |  38h  | CDerived1::mName |      8       |                     |                                  |
    |  40h  |     vftable      |    9, 14     |        vFoo2        | CDerived2 -> CGrandson           |
    |  48h  |     vbtable      |      3       |      -8 / -30h      | CGrandson                        |
    |  50h  | CDerived2::mName |      11      |                     |                                  |


  - (5) 1번의 코드에서 `베이스 클래스` 하나가 `VBClass`이며 `VBClass`를 상속받는 구조 (88 byte)
    ```cpp
      ...
      class CDerived1 : public CBase {
        ...
      };
      class CDerived2 : public virtual CBase {
        ...
      };
      class CGrandson : public virtual CDerived1, public CDerived2 {
        ...
      };
      ...
    ```
    | 주소  |    저장된 값     | 값 변경 순서 |   테이블 값(최종)   | 테이블 소유자 변경 과정         | 생성자 호출 순서 |
    | :---: | :--------------: | :----------: | :-----------------: | :------------------------------ | :--------------- |
    |   0   |     vftable      |    8, 11     |        vFoo2        | CDerived2 -> CGrandson          | CBase            |
    |   8   |     vbtable      |      1       |   -8 / 40h / 20h    |                                 | CDerived1        |
    |  10h  | CDerived2::mName |      10      |                     |                                 | CBase            |
    |  18h  | CGrandson::mName |      16      |                     |                                 | CDerived2        |
    |  20h  |   ? / (24h) 0    |      14      |                     |                                 | CGrandson        |
    |  28h  |     vftable      |   2, 4, 12   | dtor / vFoo / vFoo1 | CBase -> CDerived1 -> CGrandson |
    |  30h  |   CBase::mName   |      3       |                     |                                 |
    |  38h  | CDerived1::mName |      5       |                     |                                 |
    |  40h  |   ? / (44h) 0    |      15      |                     |                                 |
    |  48h  |     vftable      |   6, 9, 13   |     dtor / vFoo     | CBase -> CDerived2 -> CGrandson |
    |  50h  |   CBase::mName   |      7       |                     |                                 |
 
  - 참고
    - [가상 상속의 득과 실](https://dataonair.or.kr/db-tech-reference/d-lounge/technical-data/?mod=document&uid=235880)
    - [VTable Notes on Multiple Inheritance in GCC](https://ww2.ii.uj.edu.pl/~kapela/pn/cpp_vtable.html)
    - [What is the VTT for a class](https://stackoverflow.com/questions/6258559/what-is-the-vtt-for-a-class) -> 위와 동일한 내용
    - [What is the virtual table table?](https://quuxplusone.github.io/blog/2019/09/30/what-is-the-vtt/)





---
# [변수 범위, 주기, 링크](https://www.learncpp.com/cpp-tutorial/scope-duration-and-linkage-summary/)
  - 참고
    - [Storage classes](https://docs.microsoft.com/en-us/cpp/cpp/storage-classes-cpp?view=msvc-170)
    - [Storage Duration](https://en.cppreference.com/w/cpp/language/storage_duration)

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
# 리터럴 (Literal)

  - `소스 코드` 상에서 고정된 `값`을 가지는 데이터. 숫자, 문자, 단어
  - `constant` 와는 범주가 다르다! 혼동하지 말자.
  - `constant` 는 변수에 붙는 속성이고, `literal`은 프로그램에 등장하는 데이터, `값`이다.
  - 보통 리터럴은 값을 의미하지만 메모리에 저장되진 않고, 레지스터에서 바로 계산된다. -> 문자열 제외하고 코드 영역에 같이 저장된다.
  - https://m.blog.naver.com/rhkdals1206/221519863419
  - https://kant0116.tistory.com/17
  - 흔히 코드에서 숫자나 문자 또는 문장으로 표현되는 이름과 타입이 특정되지 않은 변수들이 리터럴이다.
  - 리터럴 값을 가지는 변수 또는 객체를 [리터럴 형식](#용어-정리) 이라고 한다.

## 문자열 리터럴

  - TODO
  - https://docs.microsoft.com/ko-kr/cpp/cpp/string-and-character-literals-cpp?view=msvc-170
  - 컴파일러 옵션 중 `중복 문자열 제거`가 있다.
    - https://docs.microsoft.com/ko-kr/cpp/build/reference/gf-eliminate-duplicate-strings?view=msvc-170
  - 



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
  - 상속 관계에서 `this` 포인터는 항상 객체 주소의 시작점을 가리키는 것이 아닌, **객체 내 `현재 함수의 클래스` 시작점을 가리키게 된다.**
    - `다중 상속`에서 확인할 수 있는데, 첫 번째 `베이스 클래스`의 `this`값과 두 번째 `베이스 클래스`의 `this`값이 다르다.


## [static 키워드](https://docs.microsoft.com/en-us/cpp/cpp/storage-classes-cpp?view=msvc-170#static)

  - `static` 변수는 생성된 스코프가 종료된 이후에도 해당 값을 유지한다.

  - **단 한번만 초기화**되며, 프로그램 내내 수명이 지속된다.
  - 초기화를 하지 않고 어디에도 사용하지 않으면 메모리가 할당되지 않는다.
    - 전역변수는 초기화하면 `data`영역에, 초기화하지 않으면 `bss`영역에 올라간다.

    - `static` 객체는 초기화와 상관없이 `bss` 영역에 올라간다. 생성자를 통한 초기화는 해당 구문이 처음 수행되는 시점에 이루어진다.
      - `bss` 영역은 `dynamic initializer`를 진행하는 곳이다. (컴파일 시 값을 알 수 없는 경우 나중에 초기화를 해주는 것)

      - 이를 함수화하여 호출을 하면 생성자의 호출 시점을 조정하는게 가능해진다.
      - `singleton` 클래스를 생성할 때 주의해야 한다.
  - `static` 멤버 변수는 모든 객체가 공유해야 하기 때문에 프로그램 전체 영역에서 메모리 유지가 되어야 한다. **반드시 전역 범위에서 정의 및 초기화를 수행해야 한다.**
    - 선언하면서 초기화하면 `중복 초기화`가 이루어지기 때문에 `컴파일 에러`가 난다.
    - 클래스 내부에서는 선언만 하고 초기화를 cpp파일에서 하자.

    - `C++17` 에서는 `inline` 키워드로 **선언과 동시에 초기화**가 가능해졌다! (헤더에서만 가능)
    - 이 때, `inline` 의 의미는 `중복 정의를 허용함` 이다. (코드 붙여넣기의 의미가 아님)
  - `static` 멤버 함수는 고유의 객체를 두고 연산이 이루어지는 것이 아니기 때문에 `함수 포인터` 취급을 한다.
    - 함수 포인터에 대입을 할 때 주소연산자(&)를 붙이지 않아도 된다. (붙여도 된다.)

    - 함수 포인터 타입에 네임스페이스를 명시하지 않아야 된다.
      - 함수 포인터는 네임스페이스에 엄격하다.
      - 정적 멤버 함수 포인터와 일반 멤버 함수 포인터는 타입이 다르다.
    - `접근 지정자`의 영향을 받지 않는다 (전역 범위에서의 접근 시, (`::Class::func()`))
  - `internal linkage`이기 때문에 `컴파일 단위`에서만 공유가 된다. 상수 전역 변수(`const static`)는 헤더 파일에 사용 시 각 유닛마다 변수를 생성한다. 
    - 개념은 위와 같지만 현대의 컴파일러는 링크 시 `코드 최적화`를 통해 메모리의 소모량을 줄인다.

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


## [extern 키워드](https://docs.microsoft.com/en-us/cpp/cpp/extern-cpp?view=msvc-170)

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

  - `가상 베이스 클래스`는 `다중 상속` 시 부모를 하나의 베이스 객체로 놓고 모든 자식들이 멤버 변수들을 공유하도록 만든다.
    - `베이스 클래스`가 여러 `파생 클래스`를 가지고, 임의의 클래스가 파생 클래스들을 `다중 상속` 받을 경우에 사용한다.

    - `가상 상속`을 받지 않으면 **베이스 클래스의 생성자를 파생 클래스 개수만큼 호출**한다.
    - 자세한 내용은 [Virtual Table Table 섹션](#virtual-table-table) 에 정리했다.
  - 콜론(`:`) 뒤, 베이스 클래스의 이름 앞, `접근 지정자(access specifier)` 앞 뒤에 `virtual` 키워드를 붙여 가상 상속을 할 수 있다.
  - [가상 베이스 클래스의 예제](https://www.learncpp.com/cpp-tutorial/virtual-base-classes/)


## [inline 키워드](https://docs.microsoft.com/en-us/cpp/cpp/inline-functions-cpp?view=msvc-170)

  - 두 가지 기능을 가지고 있다.
    - 컴파일 시 해당 함수의 정의를 함수 호출 코드에 그대로 붙여넣는다.
   
    - `inline 엔터티`의 `중복 정의`를 허락하고 **모든 컴파일 유닛들에서 동일한 주소를 갖게**한다. (C++17)
 
  - ### **최신의 컴파일러는 함수를 정말 적절하게 인라인화 하기 때문에 `inline` 키워드는 거의 사용할 필요가 없다.**
  - 함수 호출 시 오버헤드를 제거하기 때문에 속도가 빨라질 수 있다.
  - 클래스 바디 내부에서 정의하는 멤버 함수 앞에는 `inline` 키워드가 생략되어 있다.
  - ` 인라인 함수`는 **선언과 동시에 정의**해야 한다. 선언만 해놓으면` 링크 에러`가 발생한다.
  - `인라인 확장 함수`는 일반 함수에 사용할 수 없는 코드 최적화가 적용된다.
  - 컴파일러가 재량껏 효율을 계산해서 적용한다. 무조건 변경되는 것은 아님
  - 두 가지 케이스는 인라인 적용이 안된다.
    - 재귀 함수
    - `다른 컴파일 유닛`에서 포인터 형태로 호출되는 함수
  - `__forceinline` 키워드(C 호환용, 거의 안씀)는 최적화를 프로그래머에게 맡기는 키워드다.
  - `dllexport`와 `dllimport` 키워드로 함수를 인라인으로 정의할 수 있다. 자세한 내용은 `라이브러리`를 참고하자.
  - ### `매크로 전처리(#define)`와의 비교
    - 매크로는 `front end`의 `Preprocessing` 단계에 적용되고 `inline expansion` 은 `middle end`의 `Optimization` 단계에 적용된다.

    - `인라인 함수`는 타입 안정성 프로토콜을 따른다.
    - 키워드를 사용하는 것을 제외하고는 다른 함수와 동일한 구문을 사용한다.
    - 함수의 파라미터가 단 한번 계산된다. 매크로는 여러번 계산할 가능성이 있다.
  - ### `C++17` 부터 사용가능한 `inline` 변수는 **다른 `컴파일 단위`에서 각각 `정의`를 할 수 있다.**
    - 여러 소스 파일이 사용하는 헤더 파일에 정의가 가능하다. 모든 정의는 동일해야 한다.
   
    - **모든 컴파일 유닛에서 동일한 주소를 가지게 된다.** (동기화가 된다)
    - 이 때는 모든 유닛에서 `inline` 으로 선언 되어 있어야 한다.
    - `C++17` 이상은 인라인 함수도 동일한 기능이 적용된다.
    - `인라인화가 선호됨`의 의미보다는 `중복 정의가 허용됨`을 의미하는데, 이것은 함수에서 비롯되었다. 이게 변수로 확장된 것이다.
    - `네임스페이스 범위`에서 `inline` 변수는 `비정적` 일 때만 효과가 있고, `클래스 범위`에서는 `정적` 변수만 인라인이 허용된다. `함수 범위` 에서는 인라인이 허용되지 않는다.
  - 참고
    - [inline specifier](https://en.cppreference.com/w/cpp/language/inline)
    - [C++17 inline variable vs inline static variable - HolyBlackCat의 답변](https://stackoverflow.com/questions/50515591/c17-inline-variable-vs-inline-static-variable)


## [const 키워드](https://docs.microsoft.com/en-us/cpp/cpp/const-cpp?view=msvc-170)

  - 프로그래머가 객체 또는 변수를 수정할 수 없음을 나타내는 키워드이다.
    - `상수`라는 표현은 일종의 `어휘적 요소(lexical element)`에 가깝다. 따로 실체(메모리)가 존재하는 것은 아니며, `컴파일러`가 코드를 자를 때 발생하는 토큰의 한 종류이다.
    - `상수` 라고 부르는 엔터티들은 모두 `상수의 특성을 가진~` 으로 해석하는게 맞다. 실제 상수 엔터티는 `리터럴` 이라 부른다.

  - 기본적으로 `internal linkage` 속성을 가지기 때문에 `컴파일 단위`마다 다른 주소를 갖는다.
  - `const 변수`는 선언과 동시에 초기화를 진행해야 한다. (멤버 변수는 생성자에서 초기화 가능)
  - `const 멤버 함수`는 호출되는 객체를 `읽기 전용` 으로 취급한다. (`const this*`)
    - `비정적 데이터 멤버`의 수정이 불가능하다. (`상수 포인터`는 값 변경이 불가능하다.)

    - `const` 객체에서 `const가 아닌 멤버 함수`의 호출이 불가능하다. (`this`를 인자로 넘겨야 하는데 `상수 타입`이라 `다른 함수 취급`한다.)
    - 단, 일반 객체에서 `상수 멤버 함수`는 호출이 가능하다. 하지만 우선순위는 `일반 멤버 함수`보다 낮다.
    - `this` 에 `const_cast` 를 사용하면 위의 두 제한을 없앨 수 있다.
    ```cpp
      class CTest {
        char* mName{"CTest"};
        public:
        void foo() {
          mName = "CTest";
          std::cout << mName << std::endl;
        }
        void cFoo() const {
          std::cout << mName << std::endl;
          const_cast<CTest*>(this)->mName = "cFoo"; // 값 변경 가능
          std::cout << mName << std::endl;
          const_cast<CTest*>(this)->foo();          // 함수 호출 가능
        }
      };
    ```
  - `const` 객체는 [제한 증가 순서 (order of increasing restrictions)](https://en.cppreference.com/w/cpp/language/cv#Conversions)가 높은 쪽이다.
    - 기본 타입에서 제공하는 기능이 제한된다는 뜻이다.

    - 높은 쪽에서 낮은 쪽으로는 `변환`이 불가능하다. (기능을 사용하지 못하기 때문)
      - `const int ` 변수는 `int` 변수에 대입이 불가능하지만, 반대는 가능하다.
    - 상속 관계에서 `부모 클래스`의 포지션과 비슷하다. (하지만 클래스는 `다운 캐스팅`으로 대입이 가능하다)
    - `type qualifier (타입 한정자)` 또는 `volatile` 키워드와 함께 `cv-qualifier (cv 한정자)` 로 표현한다.
 
  - `상수 포인터`는 [const pointer](#const-pointer) 에 정리되어 있다.
  - `비정적, 비상수 데이터 멤버`에 `mutable` 키워드를 붙일 수 있다.
    - 해당 멤버 변수는 클래스, 함수의 `const` 제한을 벗어난다.

    - `상수 객체`, `상수 함수`에서의 호출 및 수정이 가능해진다.
    ```cpp
      class C {
        mutable const int* p;         // OK (p는 상수가 아니기 때문)
        mutable int* const q;         // ill-formed
        mutable int&       r;         // ill-formed
      };
    ```
  - 참고
    - [cv (const and volatile) type qualifiers](https://en.cppreference.com/w/cpp/language/cv)
    - [constant와 관련된 질문](https://kldp.org/node/155779)

## [volatile 키워드](https://docs.microsoft.com/en-us/cpp/cpp/volatile-cpp?view=msvc-170)

  - 컴파일러의 `코드 최적화를 방지`하고, 레지스터에 값을 복사하여 연산하는 대신 `항상 메모리에 접근해서 값을 읽거나 쓰도록` 지시하는 키워드이다.

  - 불필요한 코드의 동작도 생략하지 않고 모두 실행할 것을 보장한다.
  - `Reordering (재배치)` 문제를 해결한다.
      - 재배치는 컴파일러가 `메모리 접근 속도 향상`, `파이프라인 활용` 등 최적화를 목적으로 제한된 범위 내에서 프로그램 명령의 위치를 바꾸는 것을 말한다.
    
      - `volatile` 키워드는 `쓰기` 시, 앞선 메모리 접근 즉 이전 코드들의 처리를 보장하고, `읽기` 시, 이후의 메모리 접근보다 먼저 처리함을 보장한다.
      - `volatile` 키워드의 처리는 어떤 상황에서도 코드 내의 순서를 따른다는 뜻이다.
  - 값을 주소에 덮어쓰는 작업 자체가 하나의 `지시 기능`의 수행을 의미하는 `임베디드 시스템` 에서 꼭 필요한 키워드이다.
  - 여러 프로세스에서 값의 변경을 확인해야 하기 때문에 `공유 메모리` 객체를 사용하는 `인터럽트 서비스 루틴` 에서도 사용한다.
  - `멀티 스레드` 환경에서는 **각 스레드 사이의 접근 순서를 보장할 수 없기 때문에** `volatile` 대신 [atomic](#atomic) 을 사용한다. TODO 안쓰는지 같이 쓰는지?
  - `const` 키워드와 마찬가지로 `제한 증가 순서`가 높은 쪽이다.
  - 참고
    - [cv (const and volatile) type qualifiers](https://en.cppreference.com/w/cpp/language/cv)
    - [임베디드 시스템에서 volatile 키워드를 사용하는 이유](https://luna-archive.tistory.com/2)
    - [c/c++ volatile 키워드](https://skyul.tistory.com/337)


## [constexpr 키워드](https://docs.microsoft.com/en-us/cpp/cpp/constexpr-cpp?view=msvc-170)

  - `const`와 동일한 역할을 하는 `상수 식 (constant expression)` 이다.

  - `const`와 다르게, 함수 자체를 `상수화`할 수 있다. 생성자에도 적용이 가능하다. (`C++20`부터 소멸자도 가능하다.)
  - `constexpr` 변수와 함수 선언 시, `constexpr 지정자`를 생략할 수 없다.
  - 키워드에 `inline` 기능이 포함되어 있다. 적용이 가능한 타이밍에 적용된다.
  - 상당히 많이 쓰이고 적용 가능한 부분이 많다. 버전이 올라갈수록 더 많이 쓰일 것이다.
  - ### 자잘하게 계속 스펙이 변경되니 레퍼런스를 자주 찾아보자. 여기 다 적기 힘들다.
  - `constexpr variables`
    - `const` 변수와 다르게 **무조건 `컴파일 타임`에 초기화**된다. `const` 변수는 런타임에 초기화될 수도 있다. (일반 변수의 값으로 초기화 할 때 등등..)
   
      - `컴파일 타임`에 초기화가 불가능하면, `컴파일 에러`가 발생한다.
   
      - `const` 키워드는 `제한을 더해준다`는 느낌이고 `constexpr` 키워드는 `애초에 다른 기능이 없는` 느낌이다.
        ```cpp
          int a = 10 + 1;
          const int b = a + 1;     // 가능
          constexpr int c = a + 1; // 불가능, 컴파일 에러
        ```
    - 때문에, 모든 `constexpr` 변수는 `const` 이다. 
    - 참조를 `constexpr` 으로 선언할 수 있다. 참조된 객체는 `상수 식`에 의해 초기화되며, 도중에 호출되는 모든 암시적 변환도 `상수 식`이다.
    - `C++17`부터 `정적 데이터 멤버`에도 적용이 가능해졌다. (`inline`이 적용 가능해졌기 때문에)
  - `constexpr functions`
    - 반환값이 `constexpr` 인 함수이며, **필요한 경우** `컴파일 타임`에 계산될 수 있다.
      - `상수 식`이 **`컴파일 타임`에 값을 모르거나** (`리터럴`이 아닌 경우) **알 필요가 없을 때**, `런타임`에 계산된다. (== 일반 함수와 동일하게 처리된다.)
        - 함수 내부에서는, 식별자 타입과 관계없이 `컴파일 타임`에 해당 객체를 알 수 있으면 컴파일 타임에 처리가 가능하다. (변수 선언은 `C++14`부터 가능하게 변경되었다.)
        - `constexpr` 멤버 함수가 컴파일 타임에 계산되려면, 해당 클래스의 객체가 `constexpr` 으로 정의되어야 하며, 생성자 또한 `constexpr` 함수여야 한다.

        - 해당 호출이 `컴파일 타임`에 발생하는 지 쉽게 알아보려면, 디버깅 시 함수 내부의 중단점이 호출되는지 확인하면 된다. 중단점이 호출되면 `상수`가 아닌 값이 사용되었다는 뜻이다.

        ```cpp
        // b는 타입이 상수가 아니지만 a가 상수이면 foo는 컴파일에 계산된다.
        constexpr int foo(int a)  {
          int b = a + 5;  
          return b;
        }
        
          int a = 1;                   // 런타임
          const int a2 = a + 2;        // 런타임
          const int b = 2;             // 컴파일 타임
          constexpr int c = 3;         // 컴파일 타임
          foo(a);                      // 런타임
          foo(b);                      // 런타임 (컴파일 타임에 처리할 필요가 없다)
          foo(c);                      // 런타임 (컴파일 타임에 처리할 필요가 없다)
          const int d = foo(a);        // 런타임
          const int e = foo(b);        // 런타임 (컴파일 타임에 처리할 필요가 없다)
          const int f = foo(c);        // 런타임 (컴파일 타임에 처리할 필요가 없다)
          constexpr int g = foo(b);    // 컴파일 타임 (함수 콜 없음)
          constexpr int h = foo(c);    // 컴파일 타임 (함수 콜 없음)
        ```
        ![](img/constexpr_func.png)
      - 이런 특성 때문에, 일각에서는 `모든 함수에 constexpr을 적용해야 한다`는 말도 나오고 있다.

    - `인자`와 `반환 값`은 무조건 `리터럴 타입` 이어야 한다.
    - 함수 내부에서 `상수 식`만을 사용해야 한다. 아니면 컴파일 에러가 난다.
    - `재귀 함수`에 적용 가능하다.
    - `가상 함수`는 `constexpr` 정의를 할 수 없다.
    - `goto`, `try` 구문의 사용이 불가능하다. (`C++20`까지)
    - 함수 바디를 기본값으로 지정할 수 있다. (`= default, = delete`)
    - `명시적 특수화 템플릿`에 적용 가능하다.

  - `other constexpr usage`
    - `if constexpr`
      - 해당 조건문의 거짓 부분을 `컴파일 타임`에 제거해버린다.
   
      - 템플릿 프로그래밍 시 포인터 타입을 확인하는 코드가 있으면, 적용이 가능하다.

      ```cpp
        template <typename T>
        void show_value(T t) {
          if constexpr (std::is_pointer<T>::value) {
            // constexpr 이 없으면 invalid type error가 발생한다.
            std::cout << "pointer : " << *t << std::endl;
          } else {
            std::cout << "not pointer : " << t << std::endl;
          }
        }
      ```

  - 참고
    - [constexpr specifier](https://en.cppreference.com/w/cpp/language/constexpr)
    - [씹어먹는 C++ constexpr](https://modoocode.com/293)


## explicit 키워드

  - TODO


## __declspec 키워드

  - TODO


## [noexcept 키워드](https://learn.microsoft.com/en-us/cpp/cpp/noexcept-cpp?view=msvc-170)

  - TODO
  - [한정자(specifier)](https://en.cppreference.com/w/cpp/language/noexcept_spec) 와 [연산자(operator)](https://en.cppreference.com/w/cpp/language/noexcept) 두 가지 종류가 있다.
  - 한정자 : 함수가 예외를 던질 수 있는지(false), 없는지(true)를 명시한다.
    - `noexcept` 또는 `noexcept(const-expression)` 으로 표현된다.
    - `noexcept` == `noexcept(true)`
    - `컴파일 타임에 처리되지 않는다!` 해당 함수가 예외를 던지면 바로 `std::terminated`를 호출한다.
  - 연산자 : 컴파일 타임에 인자로 받은 식을 확인해 예외를 던지지 않으면 true, 예외를 던지면 false를 리턴한다.
    - `noexcept(std::is_pod<T>)` -> `POD` 타입이면 예외를 던지지 않는다.
  - `noexcept(noexcept(T()))` 형태를 볼 수 있는데, 안쪽의 `noexcept(T())`는 연산자로, 바깥쪽은 한정자로 사용되었다.
    - `T()` 생성자가 예외를 던지느냐에 따라 해당 한정자를 사용한 함수의 예외 처리 여부가 결정된다.
  - 암시적으로 생성되는 모든 `생성자, 소멸자`, `대입/이동 연산자`, `할당해제 함수(delete)`는 기본적으로 `noexcept` 속성을 가진다.
    - 멤버 변수들의 생성자, 연산자가 `noexcept`여야 해당 클래스의 생성자, 연산자가 `noexcept`를 가질 수 있다.
 
  - 참고 : http://egloos.zum.com/sweeper/v/3148916


---
# 연산자

## sizeof 연산자

  - 타입 이름 또는 단항연산 표현(`unary-expression`)을 인자로 받는 연산자.

  - `size_t` 타입의 결과를 생성한다.
    - 인텔리센스로 연산 결과값을 바로 알 수 있다. (`4Ui64` : 64비트 운영체제 부호 없는 정수형(`unsigned integral`) 타입의 크기 4)
  - 타입 이름을 제외한 나머지 연산 시 괄호를 사용하지 않아도 된다(!)
  - 절대 0이 결과값으로 나오지 않는다. (나누기 같은 구문에서 에러를 발생시킬 수 있기 때문에 최소값을 1로 정해놓았다.)
  - 배열 식별자의 경우 배열의 총 바이트 수를 산출한다. 포인터 타입은 포인터 크기가 나온다.
  - 레퍼런스는 실제 객체의 크기가 아닌 `레퍼런스 타입`의 크기가 나온다. (`가상 상속` 내의 클래스도 잘 나온다!)
  - 클래스, 구조체, 유니온의 경우 컴파일러 옵션(`/Zp`) 또는 `pack pragma`에 따라 각각의 멤버 변수 크기의 합과 다를 수 있다. (바이트 패딩)
  - 컴파일 타임에 크기가 정해지지 않거나 텍스트 영역에 저장되는 함수(함수포인터는 가능)는 연산할 수 없다.
  - 참고
    - [클래스의 크기](https://blog.naver.com/tipsware/221090063784)

## 캐스팅 연산자

  - TODO


## 범위 지정 연산자

  - `::`
  - 질문 : 멤버변수의 주소에 `&객체.변수` 가 아닌 `&클래스::변수` 로 접근하면 어디를 참조하게 되는것인가? -> 상속 시 클래스 내부에서 식별자의 모호함을 제거하기 위해 사용한다. 외부에서는 static 제외하고는 사용할 일이 없음.
  - 대부분 생략되어 있다. 신경쓰자.
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
  CTest test;                   // 베이스 클래스
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

    - 함수의 주소가 대입, 사용될 때의 소속과 `this` 포인터의 자료형을 결정하기 위해 `범위 지정 연산자(::)`를 사용하여 어디 영역의 함수인지 정확히 지정해주어야 한다.
    - `&소속 클래스::함수명` 의 형태로 주소를 대입해야 한다.
    - 주소연산자 생략 시 `비표준 구문`으로 처리해서 컴파일 시 오류가 발생한다.
      - 함수 이름의 표현법을 다양한 문법에서 사용하기 때문에 구분을 명확히 하기 위해 비표준 처리
    - `&객체.함수명` 을 대입할 경우 `바인딩 오류`가 발생한다. (윗문단 코드의 주석에 설명있음)
    - 포인터 사용 시 `포인터-멤버 연산자 (.*, ->*)` 를 이용하여 객체와 연결한다.
 
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
  - 포인터 변수에 바인딩된 함수의 접근 제한자는 무시된다. `private` 멤버 함수도 맘대로 접근할 수 있다.
    - **주소를 바로 호출**하는 것이기 때문에 컴파일 단계에서 해결하는 `접근 지정자`는 적용되지 않는다.
  
    - 물론 함수 포인터 초기화 시에는 `접근 지정자`를 따른다. (문법이니까)
    - 캡슐화를 어기는 프로그래밍이지만 `콜백 함수`로 많이 쓴다.
    ```cpp
    #include <iostream>
    class CTest;            // forward declaration
    void (CTest::*func)();  // global function pointer
    class CTest {
      private:
      void foo() {
        std::cout << "test" << std::endl;
      }
    public:
      void InputFuncPointer(){
        ::func = &CTest::bar;
      }
    };

    int main() {
      CTest test;
      test.InputFuncPointer();
      (test.*func)();   // foo() 함수 호출

      return 0;
    }
    ```
    


## 함수 바인딩

  - TODO
  - `std::bind()` 의 기능?
  - C++14 이후부터 모든 기능을 람다가 대신할 수 있다.





---
# 템플릿

  - TODO
  - SFINAE(Substitution Failure Is Not An Error, 치환 실패는 오류가 아니다)
    - 템플릿 매개변수에 자료형이나 값을 넣을 수 없어도 컴파일 오류가 발생하지 않고 해당 템플릿에 대해서 `코드 생성을 무시`하는 현상
    - 템플릿의 매개변수에 제약을 걸고 프로그래머가 오버로딩될 함수를 제어할 수 있게 만든다.
    - `std::enable_if`가 주로 사용된다.
    ```cpp
    template<bool B, class T = void>
    struct enable_if {};
    
    template<class T>
    struct enable_if<true, T> { typedef T type; };
    ```
    - `C++20` 부터는 `concept` 이라는 `제약 조건`을 추가할 수 있다. 아래 `Constraints and concept` 참조
  
  - [std::enable_if](https://en.cppreference.com/w/cpp/types/enable_if)
    - 두 개의 변수를 받는 템플릿 구조체이다.
   
    - `bool` 타입인 첫 번째 인자가 `true` 여야만 `type` 변수를 가지는 템플릿 구조체가 생성된다.
    - `type` 변수의 생성 유무로 으로 해당 구조체를 사용하는 클래스 또는 함수의 타입을 한정지을 수 있다.
      - 두 번째 인자에 값을 넣을 수 있냐 없냐로 판단한다. 아래의 예시에서 `type`의 형식은 `bool`이 되고 `true` 값이 디폴트로 들어간다면 함수 `func<T>`를 오버로딩 한다.
      ```cpp
	    template<typename T, typename std::enable_if<std::is_class<T>::value, bool>::type = true>
        void func();
      ```
    - `C++14` 부터 `enable_if<>::type`의 별칭을 사용할 수 있다.
      - `enable_if_t` 에 `typename` 키워드가 붙어있다. 안써도 됨
      ```cpp
      template<bool B, class T = void>
      using enable_if_t = typename enable_if<B,T>::type;
      ```
  
  - [Constraints and concepts](https://en.cppreference.com/w/cpp/language/constraints)
    - `C++20` 부터 사용 가능한 템플릿 타입 제한 방법



  - [바튼-넥만 트릭](https://wikidocs.net/481)





---
# 스레드

  - CPU는 연산을 할 때 메모리(레지스터)에 값을 올려서 진행한다.
  - 메모리에 있는 값을 CPU(ALU)에서 연산하려고 할 때, `BUS`를 통해서 메모리에 있는 값이 레지스터로 이동한다.
  - `비디오 메모리`는 다른 메모리임 (메쉬 정보 등이 들어가 있어서 GPU가 가져다 씀)

## atomic

  - TODO
  - https://en.cppreference.com/w/cpp/atomic/atomic

## Coroutines (C++20)