# StudyEngineering

* This repository is for personal study.

## VSCode Setting

* [VS code shortcut](https://code.visualstudio.com/docs/editor/codebasics)
* 쓸 것 같은 단축키
  * `ctrl + shift + l` : 현재 커서의 단어를 모두 선택 (`ctrl + f2`와 비슷함)
  * `ctrl + shift + k` : 현재 줄 삭제
  * `ctrl + shift + b` : `task.json`의 설정으로 빌드
  * `ctrl + shift + t` : 방금 종료한 파일 다시 열기
  * `ctrl + shift + d` : 왼쪽 `실행 탭` 열기
  * `ctrl + shift + e` : 왼쪽 `탐색기 탭` 열기
  * `ctrl + shift + x` : 왼쪽 `마켓 플레이스 탭` 열기
  * `ctrl + shift + y` : 디버그 콘솔 열기
  * `ctrl + shift + g` : `Shell launcher` 실행
  * `ctrl + shift + c` : 외부 콘솔 프로그램 열기(`WT powershell`로 되어있음)
  * `ctrl + k  v` : 우측에 미리보기 창 출력
  * `alt + shift + up or down` : 위/아래에 현재 줄 복사
  * `ctrl + alt + up or down` : 위/아래의 동일한 위치에 커서 복사
  * `ctrl + page up or page down` : 편집기 탭 이동
  * `ctrl + w` : 현재 편집기 닫기

* `MSVC compiler`를 사용하기 위해서는 `task.json`과 `launcher.json`을 잘 수정해야 한다.

* 현재 `VS Code`에서 사용하는 확장 프로그램 목록 (MS에서 나온 것 제외)
  * `Markdown All in One`
  * `PlantUML`
  * `Project Manager`
  * `ShaderlabVSCode`
  * `Shell launcher`

* `VS Code` 전역 세팅 백업
  * [settings.json](backup/settings.json)
  * [keybindings.json](backup/keybindings.json)

## Encoding Algorithm

### [Huffman Code](Huffman/Huffman.cpp)

* 빈도 종속 인코딩 알고리즘을 사용한 코드
* 개발자인 데이비드 허프만 이름을 따서 허프만 코드라고 한다.
  * 빈도 종속 인코딩 : 비트 패턴의 길이를 해당 항목이 사용되는 빈도의 역과 관련시켜 결정하는 무손실 데이터 압축방법
* [탐욕 알고리즘(greedy algorithm)] 이다.

### [Lempel-Ziv-Welch algorithm](LZW/LZWAlgorithm.cpp)

* 적응형 사전 인코딩(adaptive dictionary encoding) 알고리즘을 사용한 코드
  * 적응형 사전 인코딩 : 메시지 항목들의 집합을 사전으로, 메시지는 사전의 참조 표시로 인코딩. 인코딩 과정중에 사전의 항목이 변화한다.
* 1978년 `Lempel`과 `Ziv`에 의해 만들어졌으며,(LZ78) 1984년 `Welch`에 의해 추가 수정되었다.
* 텍스트 파일과 같이 반복되는 문자열이 있는 파일에서 압축률이 가장 높다.
* 사전은 무한히 수정되지 않고 최대 항목 수를 지정한다. 결국 자주 발생하는 하위 문자열이 사전에 들어가게 된다.
* 데이터의 제한된 분석만 수행하기 때문에 최적으로 동작하지는 않는다.
* [LZW 참조1], [LZW 참조2:위키피디아]

## Codility

### [Time Complexity](https://app.codility.com/programmers/lessons/3-time_complexity/)

* 개략적으로 프로그램의 러닝타임을 표기하는 방법 (정확한 시간 측정은 노동-집약적(labour-intensive)이다.)
* [Big-O notation]을 사용한다.
	* 점근 표기법(Asymptotic notation), 함수의 증가 양상을 다른 함수와의 비교로 사용하는 방법.
* 컴퓨팅 파워와 프로그램 실행 시간, 반복 횟수로 대략적인 복잡도를 유추할 수 있다.
	* 파워 / 시간 이 클 수록, 반복 횟수가 높을 수록 복잡도가 낮다.
* `공간 복잡도(Space complexity)` 또한 시간 복잡도와 표기법이 같다.
	* 전역 변수, 지역 변수 및 동적 포인터 자료구조와 재귀 함수의 스택 내용, 입력 데이터까지 전부 포함해야 하기 때문에 계산이 좀 더 까다롭다.
	


[탐욕 알고리즘(greedy algorithm)]: https://ko.wikipedia.org/wiki/%ED%83%90%EC%9A%95_%EC%95%8C%EA%B3%A0%EB%A6%AC%EC%A6%98
[LZW 참조1]: https://www2.cs.duke.edu/csed/curious/compression/lzw.html
[LZW 참조2:위키피디아]: https://ko.wikipedia.org/wiki/LZW
[Big-O notation]: https://en.wikipedia.org/wiki/Big_O_notation