- [StudyEngineering](#studyengineering)
  - [VSCode Setting](#vscode-setting)
  - [Codility](#codility)
    - [Time Complexity](#time-complexity)
  - [Encoding Algorithm](#encoding-algorithm)
    - [Huffman Code](#huffman-code)
    - [Lempel-Ziv-Welch algorithm](#lempel-ziv-welch-algorithm)
  - [Sorting Algorithm](#sorting-algorithm)
    - [Bubble Sort](#bubble-sort)
    - [Selection Sort](#selection-sort)
    - [Insertion Sort](#insertion-sort)
    - [Shell Sort](#shell-sort)
    - [Merge Sort](#merge-sort)
    - [Quick Sort](#quick-sort)
    - [Heap Sort](#heap-sort)
    - [Counting Sort](#counting-sort)
    - [Radix Sort](#radix-sort)
    - [Bucket Sort](#bucket-sort)
    - [Tim Sort](#tim-sort)
    - [Intro Sort](#intro-sort)
  - [Graph Algorithm](#graph-algorithm)
    - [Kruskal's Algorithm](#kruskals-algorithm)
    - [Prim's Algorithm](#prims-algorithm)
    - [Dijkstra Algorithm](#dijkstra-algorithm)
    - [Bellman-Ford Algorithm](#bellman-ford-algorithm)
    - [Floyd-Warshall Algorithm](#floyd-warshall-algorithm)
    - [A* Algorithm](#a-algorithm)

# StudyEngineering

* This repository is for personal study.

## VSCode Setting

* [VS code shortcut](https://code.visualstudio.com/docs/editor/codebasics)
* 쓸 것 같은 단축키
  * `ctrl + shift + l` : 현재 커서의 단어를 모두 선택 (`ctrl + f2`와 비슷함)
  * `ctrl + shift + k` : 현재 줄 삭제 (`shift + delete`와 동일)
  * `ctrl + shift + b` : `task.json`의 설정으로 빌드
  * `ctrl + shift + t` : 방금 종료한 파일 다시 열기
  * `ctrl + shift + d` : 왼쪽 `실행 탭` 열기
  * `ctrl + shift + x` : 왼쪽 `마켓 플레이스 탭` 열기
  * `ctrl + shift + y` : 디버그 콘솔 열기
  * `ctrl + shift + g` : `Shell launcher` 실행
  * `ctrl + shift + c` : 외부 콘솔 프로그램 열기(`WT powershell`로 되어있음)
  * `ctrl + k  v` : 우측에 미리보기 창 출력
  * `ctrl + k ctrl + s` : 키 바인딩 창 출력
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
  * `Better Comments`
  * `Auto Comment Blocks`

* [Clang-Format Style Documentation](https://clang.llvm.org/docs/ClangFormatStyleOptions.html)

* `VS Code` 전역 세팅 백업
  * [settings.json](backup/settings.json)
  * [keybindings.json](backup/keybindings.json)

* `VS Code` 지역 세팅 설명
  * [c_cpp_properties.json](.vscode/c_cpp_properties.json)
    * `C/C++ Extention`의 설정파일
    * 컴파일러, cpp 버전, intelliSence 모드 등을 설정할 수 있다.
    * `C/C++:구성 편집(UI)` 에서 수정할 수 있다.

## Codility

### [Time Complexity](https://app.codility.com/programmers/lessons/3-time_complexity/)

* 개략적으로 프로그램의 러닝타임을 표기하는 방법 (정확한 시간 측정은 노동-집약적(labour-intensive)이다.)
* [Big-O notation]을 사용한다.
	* 점근 표기법(Asymptotic notation), 함수의 증가 양상을 다른 함수와의 비교로 사용하는 방법.
	* `\left | f(x) \right | = O(g(x)) \quad as \; x  \rightarrow \infty`
* 컴퓨팅 파워와 프로그램 실행 시간, 반복 횟수로 대략적인 복잡도를 유추할 수 있다.
	* 파워 / 시간 이 클 수록, 반복 횟수가 높을 수록 복잡도가 낮다.
* `공간 복잡도(Space complexity)` 또한 시간 복잡도와 표기법이 같다.
	* 전역 변수, 지역 변수 및 동적 포인터 자료구조와 재귀 함수의 스택 내용, 입력 데이터까지 전부 포함해야 하기 때문에 계산이 좀 더 까다롭다.


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

## [Sorting Algorithm](SortAlgorithm/SortAlgorithm.cpp)

* `Stable Sort (안정 정렬)`
  * 중복된 키의 순서가 변경되지 않게 정렬하는 알고리즘
  * `Insertion`, `Merge`, `Bubble`, `Counting` 이 대표적인 `Stable Sort`이다.
  * `Selection`, `Heap`, `Shell`, `Quick` 이 대표적인 `Unstable Sort`이다.
* `In-place Algorithm (제자리 정렬)`
  * 추가 메모리 사용량이 정렬 항목 외에 `O(1)`개, 최대 `O(log(N))`개를 넘지 않는 정렬 알고리즘
  * `Insertion`, `Selection`, `Bubble`, `Shell`, `Heap`, `Quick` 이 대표적인 `In-place Sort` 이다.
    * `Quick`은 `O(log(N))`개의 메모리를 사용하기 때문에 엄격한 정의로는 `Not In-place Sort` 이지만, 일반적으로는 `In-place Sort`로 분류한다.
  * `Merge`, `Counting`, `Radix`, `Bucket` 이 대표적인 `Not In-place Sort` 이다.
* `Comparison Sort (비교 정렬)`
  * 비교 동작을 통해 목록 요소들을 읽어내는 정렬 알고리즘
  * `O(NlogN)` 보다 더 나은 성능을 낼 수 없다.
  * `Quick`, `Heap`, `Merge`, `Shell`, `Insertion` 등 대다수의 정렬 알고리즘이 여기에 속한다.
  * `Bucket`, `Counting`, `Radix` 등이 `Non-Comparison Sort` 이다.

### Bubble Sort

* 간단해서 비효율적인 알고리즘 (쓰이지 않는다)
* `n`번째와 `n+1`번째를 비교하여 큰 값을 뒤쪽으로 스왑한다. 배열의 뒤쪽부터 정렬되는 형태
* `Time Complexity` : `O(N^2)`
* `Space Complexity` : `O(1)`

### Selection Sort

* 간단해서 비효율적인 알고리즘2 (쓰이지 않는다)
* `n`번째와 크기 비교를 했을 때 더 작으면 해당 `index`를 저장, 바깥쪽 루프가 끝났을 때 값을 앞쪽으로 스왑한다. 배열의 앞쪽부터 정렬되는 형태
* `Time Complexity` : `O(N^2)`
* `Space Complexity` : `O(1)`


### Insertion Sort

* 정렬이 된 앞부분과 비교해서 적절한 위치에 `n`번째 값을 삽입한다. 배열의 앞쪽부터 정렬되는 형태
* `Time Complexity`
  * `Best Case` : `O(N)` (이미 정렬된 배열)
  * `Average Case` : `O(N^2)`
  * `Worst Case` : `O(N^2)` (간격이 잘못 설정된 경우)
* `Space Complexity` : `O(1)`


### Shell Sort

* `Insertion Sort`의 `Worst Case`를 개선하기 위해 나온 알고리즘. 삽입 정렬보다 빠르다.
* 일정 `간격`으로 `부분 리스트`를 만들어 `삽입 정렬`을 시행, `간격`이 1이 될때까지 반복한다.(간격이 1이면 부분 리스트 == 전체 리스트)
  * `부분 리스트`의 길이는 `리스트 / 간격` 과 같다. ex) 배열길이 10인 리스트의 간격이 5일 경우, 부분 리스트의 길이는 2가 된다.
  * `간격`이 짝수일 때 보다 홀수일 때가 더 빠르다.
* `Time Complexity`
  * `Best Case` : `O(N)` (이미 정렬된 배열)
  * `Average Case` : `O(N^1.5)`
  * `Worst Case` : `O(N^2)` (역순으로 정렬된 배열)
* `Space Complexity` : `O(N)`


### Merge Sort

* [분할 정복 알고리즘 (Divide and Conquer Algorithm)] 이다.
* 리스트의 길이가 0 또는 1이 될 때까지 리스트를 분할한 다음, 각각을 정렬하면서 합친다.
* 병합 과정에서 추가적으로 배열 길이만큼의 메모리가 필요하다.
* `Top-Down`과 `Bottom-Up` 두 가지 방식이 있다.
  * `Top-Down`은 이진 트리 `Preorder Traversal`과 동일한 순서로 결합을 한다. 재귀를 사용하는 코드가 여기에 속한다.
  * `Bottom-Up`은 쪼갠 리스트들의 길이가 짧은 순서로 결합을 한다. 재귀를 사용하지 않는 코드가 여기에 속한다.
* 재귀 함수 호출 시 원본 리스트와 임시 리스트의 인자 전달 순서를 바꿔서 불필요하게 임시 리스트로 복사를 수행하는 오버헤드를 줄이는 방법이 있다.
  * [참고](https://m.blog.naver.com/osw5144/120207767212)
  * [SortAlgorithm.cpp](SortAlgorithm/SortAlgorithm.cpp) 에 구현된 함수는 인자를 넘기지 않기 때문에 사용하지 못한다.
* `Time Complexity` : `O(NlogN)`
* `Space Complexity` : `O(N)`


### Quick Sort

* 보편적으로 가장 많이 사용되는 정렬 알고리즘이다.
* [분할 정복 알고리즘 (Divide and Conquer Algorithm)] 이다.
* 배열을 일정한 기준(`Pivot`)에 따라 큰 값과 작은 값으로 분할한 다음, 각각을 정렬하면서 합친다.
  * `Merge Sort`와 달리 배열을 임의로 나누지 않기 때문에 효율적이지만, 피벗값이 잘못 선택되면 `O(N^2)`가 될 수 있다.
  * [SortAlgorithm.cpp](SortAlgorithm/SortAlgorithm.cpp) 에 구현된 함수는 리스트의 마지막 값을 피벗으로 한다.
* `Time Complexity`
  * `Best Case` : `O(NlogN)`
  * `Average Case` : `O(NlogN)`
  * `Worst Case` : `O(N^2)` (이미 정렬된 배열)
* `Space Complexity` : `O(1)`

### Heap Sort

* 자료구조 `힙(heap)`을 사용하는 정렬 알고리즘
  * `힙(heap)`은 `완전 이진트리(Complete Binary Tree)`의 일종으로 `우선순위 큐`를 위하여 만들어진 자료구조
  * 최대값이나 최소값을 빠르게 찾아내도록 만들어졌다.
  * `이진 탐색 트리(Binary Search Tree)`와 다르게 중복된 값을 허용한다.
* 오름차순 정렬일 때 최대 힙을, 내림차순 정렬일 때 최소 힙을 사용한다. (루트 값을 맨 뒤로 보내는 정렬이기 때문)
* `완전 이진트리`를 구현하고, Root값을 제외하도록 index를 변경하면서 나머지 트리를 계속해서 정렬한다.
  * 0번 인덱스는 사용하지 않는다.
* `Time Complexity` : `O(NlogN)`
* `Space Complexity` : `O(1)`

### Counting Sort

* `비교를 하지 않는 정렬(Non-Comparison)` 알고리즘 이다.
* 정수 정렬 알고리즘이다.
* 값을 키로 갖는 배열을 선언하여 해당 값의 개수를 배열안에 넣는다. 그 후 개수에 대한 산술을 사용하여 각 키 값의 위치를 결정한다.
* 실행 시간이 `최대값 + 값의 개수` 이기 때문에 값 차이가 많이 나지 않는 상황에서만 사용하는게 적합하다.
* 더 큰 키를 효율적으로 처리할 수 있는 `기수 정렬(Radix Sort)`에서 서브 루틴으로 자주 사용된다.
* `Time Complexity` : `O(N + K)`, `K = 최대값`
* `Space Complexity` : `O(K)`

### Radix Sort

* `비교를 하지 않는 정렬(Non-Comparison)` 알고리즘 이다.
* 정수 정렬 알고리즘이다.
* 각 자리수에 따라 값들을 해당 버킷에 집어 넣고 순서대로 빼내서 정렬한다. 이 알고리즘을 최대 자리수 만큼 반복한다.
  * `버킷 소트(Bucket Sort)`의 일종으로 보기도 한다.
* 크기가 유한하고 사전순으로 정렬이 가능해야 한다.
* 기수 정렬은 `최상위 유효숫자(Most Significant Digit, MSD)`나 `최하위 유효숫자(Least Significant Digit, LSD)` 에서 시작하도록 구현할 수 있다.
  * 정렬 순서가 달라진다. [참고](https://ko.wikipedia.org/wiki/%EA%B8%B0%EC%88%98_%EC%A0%95%EB%A0%AC)
  * [SortAlgorithm.cpp](SortAlgorithm/SortAlgorithm.cpp) 에 구현된 함수는 최하위 유효숫자에서 시작한다.
* `Time Complexity` : `O(N * W)`, `W = 최대 자리수`
* `Space Complexity` : `O(N + W)`

### Bucket Sort

* 비교 정렬, 비교를 하지 않는 정렬 모두 구현이 가능한 알고리즘이다.
* `분산 정렬(Distribution)` 이다.
  * 데이터가 여러 중간 자료구조로 분산된 다음 다시 수집되어 출력되는 정렬 알고리즘을 의미한다.
* [분할 정복 알고리즘 (Divide and Conquer Algorithm)] 이다.
* 배열의 원소를 여러 버킷으로 분산하여 정렬한다. 보통 버킷 내부의 정렬은 [삽입 정렬](#insertion-sort)을 이용한다.
* 버킷의 개수가 `N`개에 가까울 수록, 배열이 균등 분포에 가까울 수록 성능이 올라간다.
* `Time Complexity`
  * `Best Case` : `O(N)`
  * `Average Case` : `O(N + N^2/k + k)`, `k = 버킷 수`
  * `Worst Case` : `O(N^2)` (모든 값이 하나의 버킷으로 들어간 경우)
* `Space Complexity` : `O(N * K)`

### Tim Sort

* `Merge Sort + Insertion Sort`의 하이브리드 안정화 정렬 알고리즘이다.
* `Java`, `Python`, `Android Platform` 등 다양한 프로그램의 기본 정렬 알고리즘으로 사용된다.
* 실생활에서는 완전 랜덤한 배열을 정렬하지 않기 때문에 어느정도 정렬이 된 배열에 대해서 최고의 성능을 내도록 고안되었다.
* `N`의 크기가 작을 경우(`< 2^6`) 성능을 위해 `Binary Insertion Sort`를 대신 사용한다.
* [참고](https://d2.naver.com/helloworld/0315536), [참고2](https://orchistro.tistory.com/175), [참고3](https://en.wikipedia.org/wiki/Timsort)
* `Time Complexity`
  * `Best Case` : `O(N)`
  * `Average Case` : `O(NlogN)`
  * `Worst Case` : `O(NlogN)`
* `Space Complexity` : `O(N)` (`Merge Sort`보다 작은 값)

### Intro Sort

* `Quick Sort + Heap Sort + Insertion Sort`의 하이브리드 정렬 알고리즘이다.
* `Quick Sort`의 `Worst Case`를 보완하기 위해 고안되었다.
* 재귀 호출의 깊이가 `\left \lfloor 2LogN \right \rfloor`을 넘어가면 아래의 동작을 수행한다.
  * 현재 부분 리스트의 크기가 16 이상일 경우 `Heap Sort`를 수행한다.
  * 현재 부분 리스트의 크기가 16 미만일 경우 `Insertion Sort`를 수행한다.
  * `ceil`은 올림 처리, `floor`는 내림 처리, `round`는 반올림 처리이다.
* `16`의 값은 연구 결과를 통해 나온 최적의 값이다. (`Tim Sort`의 `Gallop`과 다르게 고정값이다.)
* `Time Complexity` : `O(NlogN)`
* `Space Complexity` : `O(1)`

## [Graph Algorithm](GraphAlgorithm/GraphAlgorithm.cpp)

* `Spanning Tree`
  * 그래프 내의 모든 정점을 최소 간선의 수로 연결하는 부분 그래프
  * `N`개의 정점이 `N - 1`개의 간선으로 연결되어 있다.
  * 하나의 그래프에서 여러 개의 `Spanning Tree`가 나올 수 있다.
  * 모든 정점들이 연결되어 있어야 하며, `사이클`을 포함해서는 안된다.
  * 통신 네트워크 구축 등에 사용된다.
* `Minimum Spanning Tree (MST)`
  * 간선들의 가중치가 동일하지 않을 경우, 간선들의 가중치 합이 최소가 되는 `Spanning Tree`
  * `Spanning Tree`의 성질을 모두 갖고 있다.

### Kruskal's Algorithm

* `Minimum Spanning Tree`를 찾는 알고리즘이다.
* [탐욕 알고리즘(greedy algorithm)]이다.
* 가장 가중치가 작은 간선부터 시작하여, 사이클을 만들지 않으면서 가중치가 작은 간선을 전체 트리가 만들어질 때까지 차례로 선택한다.
* `E`를 간선의 개수, `V`를 정점의 개수라고 할 때, `Kruskal Algorithm`은 `O(ElogN)` 시간안에 동작한다.
  * 간선의 가중치 별 정렬시간(`O(ElogE)`) + [서로소 집합(Disjoint Set)](https://ko.wikipedia.org/wiki/%EC%84%9C%EB%A1%9C%EC%86%8C_%EC%A7%91%ED%95%A9_%EC%9E%90%EB%A3%8C_%EA%B5%AC%EC%A1%B0)을 통한 사이클 찾기 동작(`O(ElogV)`)
  * `V <= 2E`이기 때문에 `O(logV) == O(logE)`
  * 알고리즘 최종 `Time Complexity`는 `O(ElogN)`이 된다.

### Prim's Algorithm

* `Minimum Spanning Tree`를 찾는 알고리즘이다.
  
### Dijkstra Algorithm

### Bellman-Ford Algorithm

### Floyd-Warshall Algorithm

### A* Algorithm

[탐욕 알고리즘(greedy algorithm)]: https://ko.wikipedia.org/wiki/%ED%83%90%EC%9A%95_%EC%95%8C%EA%B3%A0%EB%A6%AC%EC%A6%98
[LZW 참조1]: https://www2.cs.duke.edu/csed/curious/compression/lzw.html
[LZW 참조2:위키피디아]: https://ko.wikipedia.org/wiki/LZW
[Big-O notation]: https://en.wikipedia.org/wiki/Big_O_notation
[분할 정복 알고리즘 (Divide and Conquer Algorithm)]: https://ko.wikipedia.org/wiki/%EB%B6%84%ED%95%A0_%EC%A0%95%EB%B3%B5_%EC%95%8C%EA%B3%A0%EB%A6%AC%EC%A6%98