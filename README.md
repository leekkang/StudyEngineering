- [Document Link](#document-link)
- [노션 링크](#노션-링크)
- [VSCode Setting](#vscode-setting)
- [Visual Studio Setting](#visual-studio-setting)
- [Unicode, ANSI, UTF](#unicode-ansi-utf)

---
## StudyEngineering

  - This repository is for personal study.


---
# Document Link

  - ## [CPP Study](docs/CPP_Study.md)
  - ## [Algorithm](docs/Algorithm.md)

  - ## [자료구조](docs/DataStructure.md)
  - ## [운영 체제](docs/OperatingSystem.md)
  - ## [API Study](docs/API_Study.md)
  - ## [그래픽스](docs/Graphics.md)
  - ## [게임 수학](docs/GameMath.md)

---
# 노션 링크

  - public : https://leekkang.notion.site/3bf90ccd169648fcab6017649de78a4b
  - private : https://www.notion.so/leekkang/88e549597c844a69bdf65ea9e77543db

---
# VSCode Setting

  - [VS code shortcut](https://code.visualstudio.com/docs/editor/codebasics)
  - 쓸 것 같은 단축키
    - `ctrl + shift + l` : 현재 커서의 단어를 모두 선택 (`ctrl + f2`와 비슷함)
    - `ctrl + shift + k` : 현재 줄 삭제 (`shift + delete`와 동일)
    - `ctrl + shift + b` : `task.json`의 설정으로 빌드
    - `ctrl + shift + t` : 방금 종료한 파일 다시 열기
    - `ctrl + shift + d` : 왼쪽 `실행 탭` 열기
    - `ctrl + shift + x` : 왼쪽 `마켓 플레이스 탭` 열기
    - `ctrl + shift + y` : 디버그 콘솔 열기
    - `ctrl + shift + g` : `Shell launcher` 실행
    - `ctrl + shift + c` : 외부 콘솔 프로그램 열기(`WT powershell`로 되어있음)
    - `ctrl + k  v` : 우측에 미리보기 창 출력
    - `ctrl + k ctrl + s` : 키 바인딩 창 출력
    - `alt + shift + up or down` : 위/아래에 현재 줄 복사
    - `ctrl + alt + up or down` : 위/아래의 동일한 위치에 커서 복사
    - `ctrl + page up or page down` : 편집기 탭 이동
    - `ctrl + w` : 현재 편집기 닫기
    - `ctrl + j` : 문제 출력 콘솔 열기
    - `ctrl + enter` : 아래에 신규 행 삽입, 커서도 이동
    - `alt + left, right` : 구문 단위로 앞,뒤로 이동. 선언 찾기 시(f12) 다시 되돌아갈 때 사용할 수 있다.
  - [참고](https://maeryo88.tistory.com/210)
  - [참고](https://m.blog.naver.com/PostView.naver?isHttpsRedirect=true&blogId=akilia&logNo=221991147511)


  - `MSVC compiler`를 사용하기 위해서는 `task.json`과 `launcher.json`을 잘 수정해야 한다.

  - 현재 `VS Code`에서 사용하는 확장 프로그램 목록 (MS에서 나온 것 제외)
    - `Markdown All in One`
    - `PlantUML`
    - `Project Manager`
    - `ShaderlabVSCode`
    - `Shell launcher`
    - `Better Comments`
    - `Auto Comment Blocks`

  - [Clang-Format Style Documentation](https://clang.llvm.org/docs/ClangFormatStyleOptions.html)

  - `VS Code` 전역 세팅 백업
    - [settings.json](backup/settings.json)
    - [keybindings.json](backup/keybindings.json)

  - `VS Code` 지역 세팅 설명
    - [c_cpp_properties.json](.vscode/c_cpp_properties.json)
      - `C/C++ Extention`의 설정파일
      - 컴파일러, cpp 버전, intelliSence 모드 등을 설정할 수 있다.
      - `C/C++:구성 편집(UI)` 에서 수정할 수 있다.


---
# Visual Studio Setting

  - VSCode의 단축키를 불러서 적용할 수 있다.
  - `도구 -> 옵션 -> 환경 -> 키보드 -> 키보드 매핑 구성표 적용(Visual Studio Code)`
  - 덮어씌우는 것이기 때문에 기능이 없으면 기존 VS의 단축키를 사용한다.
  - 줄 복사(`alt + shift + up,downarrow`)는 바뀌지 않아서 직접 할당했다. -> `편집.중복됨`에 할당
  - 이전, 다음 탭 이동(`ctrl + pgup, down`)은 텍스트 편집기에 적용이 안되서 다시 할당했다. -> `창.이전탭, 창.다음탭`의 텍스트 편집기에 할당
  - [단축키 참고](https://docs.microsoft.com/ko-kr/visualstudio/ide/default-keyboard-shortcuts-in-visual-studio?view=vs-2019)
  - [단축키 참고](https://najsulman.tistory.com/996)


---
# Unicode, ANSI, UTF

  - ### Unicode : 문자 집합을 가진 테이블
    - 비슷한 개념으로 `ASCII Code Table`이 있다.
  - ### UTF : `Unicode Transformation Format`의 약자로, 유니코드를 어떤 조합으로 인코딩 할 것 인가에 대한 프로토콜이다.
    - `UTF-8`, `UTF-16`, `UTF-32`, `UCS-2`, `UCS-4` 등이 있다.
    - `BOM (Byte Order Mark)` 가 존재한다. CPU 종류에 따라 처리가 달라지면서 생기는 문제를 해결하기 위해 생긴 프로토콜이다.
    - `UTF-8` : `EF BB BF`로 시작한다. 없는 경우가 많다. 아스키 코드표를 포함한다. (프로토콜이 똑같다)
    - `UTF-16` : `UCS-2`의 확장 개념이다. `Little Endian (FF FE, Intel계열)`, `Big Endian (FE FF, Unix계열)`이 있다.
      - c++에서 `wchar_t`로 표기된다.
  - ### ANSI : `MS-DOS`의 기본 인코딩 프로토콜. 원래는 영문판이 기본이었으나 요새는 시스템 로케일을 따라간다. 한국은 CP949(EUC-KR 확장판)코드 페이지를 사용한다.
    - 메모장 저장 시 나오는 ANSI 인코딩은 원래 규격이 아니다. 잘못 썼는데 그냥 그대로 사용하는 것. 실제로는 CP949를 사용한다.
  
  - wide char : UTF-16
  - multi byte : ANSI, UTF-8
  - 코드 페이지 변경(Unicode -> CP949 같은) 시 시스템 로케일을 따라간다.
    - `WideCharToMultiByte(CP_ASP,...)`, `MultiByteToWideChar(CP_ASP,...)` 함수 사용 시 시스템 로케일을 따라감. 다른 로케일 적용하고 싶으면 `locale::facet` 사용하자.

  - 참고 
    - https://sacstory.tistory.com/entry/%EC%9C%A0%EB%8B%88%EC%BD%94%EB%93%9C%EC%99%80-ANSI-%EA%B7%B8%EB%A6%AC%EA%B3%A0-UTF
    - https://www.joelonsoftware.com/2003/10/08/the-absolute-minimum-every-software-developer-absolutely-positively-must-know-about-unicode-and-character-sets-no-excuses/