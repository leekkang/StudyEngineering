- [Time Complexity](#time-complexity)
- [Encoding Algorithm](#encoding-algorithm)
  - [Huffman Code](#huffman-code)
  - [Lempel-Ziv-Welch algorithm](#lempel-ziv-welch-algorithm)
  - [LZ77 Algorithm](#lz77-algorithm)
- [Sorting Algorithm](#sorting-algorithm)
  - [단일 정렬 알고리즘](#단일-정렬-알고리즘)
  - [Bubble Sort](#bubble-sort)
  - [Selection Sort](#selection-sort)
  - [Insertion Sort](#insertion-sort)
  - [Shell's Sort](#shells-sort)
  - [Merge Sort](#merge-sort)
  - [Quick Sort](#quick-sort)
  - [Heap Sort](#heap-sort)
  - [Counting Sort](#counting-sort)
  - [Radix Sort](#radix-sort)
  - [Bucket Sort](#bucket-sort)
  - [복합 정렬 알고리즘](#복합-정렬-알고리즘)
  - [Tim Sort](#tim-sort)
  - [Intro Sort](#intro-sort)
- [Graph Algorithm (Graph Traversal)](#graph-algorithm-graph-traversal)
  - [Kruskal's Algorithm](#kruskals-algorithm)
  - [Prim's Algorithm](#prims-algorithm)
  - [Floyd-Warshall Algorithm](#floyd-warshall-algorithm)
  - [Dijkstra Algorithm](#dijkstra-algorithm)
  - [Bellman-Ford Algorithm](#bellman-ford-algorithm)
  - [A* Algorithm](#a-algorithm)
- [Hash Algorithm](#hash-algorithm)
- [Sieve of Eratosthenes (에라토스테네스의 체)](#sieve-of-eratosthenes-에라토스테네스의-체)

---


## Algorithm Study

  - 몰랐거나 까먹기 쉬운 알고리즘들을 기록해놓는 문서

  - TODO 보간 탐색
    - https://yoongrammer.tistory.com/77?category=987044


# [Time Complexity](https://app.codility.com/programmers/lessons/3-time_complexity/)

  - 개략적으로 프로그램의 러닝타임을 표기하는 방법 (정확한 시간 측정은 노동-집약적(labour-intensive)이다.)
  - [Big-O notation](https://en.wikipedia.org/wiki/Big_O_notation)을 사용한다.
  	- 점근 표기법(Asymptotic notation), 함수의 증가 양상을 다른 함수와의 비교로 사용하는 방법.
$$
\left | f(x) \right | = O(g(x)) \quad as \; x  \rightarrow \infty
$$
  - 컴퓨팅 파워와 프로그램 실행 시간, 반복 횟수로 대략적인 복잡도를 유추할 수 있다.
  	- 파워 / 시간 이 클 수록, 반복 횟수가 높을 수록 복잡도가 낮다.
  - `공간 복잡도(Space complexity)` 또한 시간 복잡도와 표기법이 같다.
  	- 전역 변수, 지역 변수 및 동적 포인터 자료구조와 재귀 함수의 스택 내용, 입력 데이터까지 전부 포함해야 하기 때문에 계산이 좀 더 까다롭다.


---
# [Encoding Algorithm](../EncodingAlgorithm/EncodingAlgorithm.cpp)


## [Huffman Code](../EncodingAlgorithm/Huffman.h)

  - 빈도 종속 인코딩 알고리즘을 사용한 코드
  - 개발자인 데이비드 허프만 이름을 따서 허프만 코드라고 한다.
    - 빈도 종속 인코딩 : 비트 패턴의 길이를 해당 항목이 사용되는 빈도의 역과 관련시켜 결정하는 무손실 데이터 압축방법
  - 이진 트리 자료구조를 만들어 빈도수와 해당 노드의 위치를 이진수로 저장한다.
    - 디코딩 시 노드의 위치를 찾아가서 문자를 읽어온다.
  - [탐욕 알고리즘(greedy algorithm)] 이다.

## [Lempel-Ziv-Welch algorithm](../EncodingAlgorithm/LZWAlgorithm.h)

  - 적응형 사전 인코딩(adaptive dictionary encoding) 알고리즘을 사용한 코드
    - 적응형 사전 인코딩 : 메시지 항목들의 집합을 사전으로, 메시지는 사전의 참조 표시로 인코딩. 인코딩 과정중에 사전의 항목이 변화한다.
  - 1978년 `Lempel`과 `Ziv`에 의해 만들어졌으며,(LZ78) 1984년 `Welch`에 의해 추가 수정되었다.
  - 텍스트 파일과 같이 반복되는 문자열이 있는 파일에서 압축률이 가장 높다.
  - 사전은 무한히 수정되지 않고 최대 항목 수를 지정한다. 결국 자주 발생하는 하위 문자열이 사전에 들어가게 된다.
  - 데이터의 제한된 분석만 수행하기 때문에 최적으로 동작하지는 않는다.

  - 참고
    - https://www2.cs.duke.edu/csed/curious/compression/lzw.html
    - https://ko.wikipedia.org/wiki/LZW

## LZ77 Algorithm

  - TODO



---
# [Sorting Algorithm](../SortAlgorithm/SortAlgorithm.cpp)

  - `Stable Sort (안정 정렬)`
    - 중복된 키의 순서가 변경되지 않게 정렬하는 알고리즘
      - 보통 맞교환이 없으면 stable 하고, 교환이 있으면 unstable 하다.
    - `Insertion`, `Merge`, `Bubble`, `Counting`, `Radix` 가 대표적인 `Stable Sort`이다.
    - `Selection`, `Heap`, `Shell`, `Quick` 이 대표적인 `Unstable Sort`이다.
  - `In-place Algorithm (제자리 정렬)`
    - 추가 메모리 사용량이 정렬 항목 외에 $O(1)$개, 최대 $O(logN)$개를 넘지 않는 정렬 알고리즘
    - `Insertion`, `Selection`, `Bubble`, `Shell`, `Heap`, `Quick` 이 대표적인 `In-place Sort` 이다.
      - `Quick`은 $O(logN)$개의 메모리를 사용하기 때문에 엄격한 정의로는 `Not In-place Sort` 이지만, 일반적으로는 `In-place Sort`로 분류한다.
    - `Merge`, `Counting`, `Radix`, `Bucket` 이 대표적인 `Not In-place Sort` 이다. (시간을 위해 메모리를 희생)
  - `Comparison Sort (비교 정렬)`
    - 비교 동작을 통해 목록 요소들을 읽어내는 정렬 알고리즘
    - $O(NlogN)$ 보다 더 나은 성능을 낼 수 없다.
    - `Quick`, `Heap`, `Merge`, `Shell's`, `Insertion` 등 대다수의 정렬 알고리즘이 여기에 속한다.
    - `Bucket`, `Counting`, `Radix` 등이 `Non-Comparison Sort` 이다.


---
## 단일 정렬 알고리즘


## Bubble Sort

  - 간단해서 비효율적인 알고리즘 (쓰이지 않는다)
  - `n`번째와 `n+1`번째를 비교하여 큰 값을 뒤쪽으로 스왑한다. 배열의 뒤쪽부터 정렬되는 형태
  - `Time Complexity` : $O(N^2)$
  - `Space Complexity` : $O(1)$

## Selection Sort

  - 간단해서 비효율적인 알고리즘2 (쓰이지 않는다)
  - `n`번째와 크기 비교를 했을 때 더 작으면 해당 `index`를 저장, 바깥쪽 루프가 끝났을 때 값을 앞쪽으로 스왑한다. 배열의 앞쪽부터 정렬되는 형태
  - `Time Complexity` : $O(N^2)$
  - `Space Complexity` : $O(1)$


## [Insertion Sort](../SortAlgorithm/InsertionSort.h)

  - 정렬이 된 앞부분과 비교해서 적절한 위치에 `n`번째 값을 삽입한다. 배열의 앞쪽부터 정렬되는 형태
  - 적절한 위치를 선형으로 찾는 대신 `이진 탐색(binary search)` 알고리즘을 사용하는 `이진 삽입 정렬`도 있다.
    - 평균적으로 $O(NlogN)$ 의 복잡도를 가지게 되지만 `Best Case`가 사라진다.
  - 정렬 대상의 길이가 유의미하게 적은 경우 (보통 `< 8`) 속도가 빠른 편이기 때문에 하위 정렬로 많이 사용한다. (생각보다 더 많이 씀)
 
  - `Time Complexity`
    - `Best Case` : $O(N)$ (이미 정렬된 배열)
    - `Average Case` : $O(N^2)$
    - `Worst Case` : $O(N^2)$ (역순으로 정렬된 배열)
  - `Space Complexity` : $O(1)$


## [Shell's Sort](../SortAlgorithm/Shell'sSort.h)

  - `Insertion Sort`의 `Worst Case`를 개선하기 위해 나온 알고리즘. 삽입 정렬보다 빠르다.
  - 일정 `간격`으로 `부분 리스트`를 만들어 `삽입 정렬`을 시행, `간격`이 1이 될때까지 반복한다.(간격이 1이면 부분 리스트 == 전체 리스트)
    - `부분 리스트`의 길이는 `리스트 / 간격` 과 같다. ex) 배열길이 10인 리스트의 간격이 5일 경우, 부분 리스트의 길이는 2가 된다.
    - `간격`이 짝수일 때 보다 홀수일 때가 더 빠르다. (왜 그런진 모름)

  - `Time Complexity`
    - `Best Case` : $O(N)$ (이미 정렬된 배열)
    - `Average Case` : $O(N^{1.5})$
    - `Worst Case` : $O(N^2)$ (역순으로 정렬된 배열)
  - `Space Complexity` : $O(1)$


## [Merge Sort](../SortAlgorithm/MergeSort.h)

  - [분할 정복 알고리즘 (Divide and Conquer Algorithm)] 이다.
  - 리스트의 길이가 0 또는 1이 될 때까지 리스트를 분할한 다음, 각각을 정렬하면서 합친다.
  - 병합 과정에서 추가적으로 배열 길이만큼의 메모리가 필요하다.
  - `Top-Down`과 `Bottom-Up` 두 가지 방식이 있다.
    - `Top-Down`은 이진 트리 `Preorder Traversal`과 동일한 순서로 결합을 한다. 재귀를 사용하는 코드가 여기에 속한다.
    - `Bottom-Up`은 쪼갠 리스트들의 길이가 짧은 순서로 결합을 한다. 재귀를 사용하지 않는 코드가 여기에 속한다.
  - 재귀 함수 호출 시 원본 리스트와 임시 리스트의 인자 전달 순서를 바꿔서 불필요하게 임시 리스트로 복사를 수행하는 오버헤드를 줄이는 방법이 있다.
    - [참고](https://m.blog.naver.com/osw5144/120207767212)
    - [소스 코드](../SortAlgorithm/MergeSort.h)에 구현된 함수는 인자를 넘기지 않기 때문에 사용하지 못한다.

  - `Time Complexity` : $O(NlogN)$
  - `Space Complexity` : $O(N)$


## [Quick Sort](../SortAlgorithm/QuickSort.h)

  - 보편적으로 가장 많이 사용되는 정렬 알고리즘이다.
  - [분할 정복 알고리즘 (Divide and Conquer Algorithm)] 이다.
  - 배열을 일정한 기준(`Pivot`)에 따라 큰 값과 작은 값으로 분할한 다음, 각각을 정렬하면서 합친다.
    - `Merge Sort`와 달리 배열을 임의로 나누지 않기 때문에 효율적이지만, 피벗값이 잘못 선택되면 $O(N^2)$가 될 수 있다.
  - 매 단계에서 피벗의 위치가 확정되기 때문에 이후 정렬할 개수가 1개씩 줄어든다. 때문에 일반적인 경우 $O(NlogN)$ 알고리즘 중 가장 빠르게 동작한다.
    - 실제 동작시간인 $C * NlogN + \alpha$ 에서 $C$ 의 값이 작다.
    - $C$ 는 알고리즘이 `참조 지역성(Localith of Reference)` 의 원리를 잘 만족할 수록 작아진다.
      - 최근에 참조한 메모리나 그 메모리와 인접한 메모리를 다시 참조할 확률이 높다는 이론을 기반으로 CPU가 캐시 메모리에 담아놓는 것
      - 메모리를 연속으로 읽는 작업은 캐시 메모리에서 읽어오기 때문에 빠르고, 무작위로 읽는 작업은 캐시 메모리가 아니라 느리다.
      - 즉, 인접한 메모리를 많이 비교하는 정렬은 상수 $C$의 값이 작다.
  
  - `STL` 라이브러리에서 피벗값을 구하는 방법으로 중위법 + [Tukey's ninther](https://www.johndcook.com/blog/2009/06/23/tukey-median-ninther/) 라는 방법을 사용한다.
    - 중위법 : 시작, 중간, 끝 점의 세 원소의 `중앙값(median)` 을 사용하는 방법
    - 길이가 40 미만인 경우 `Tukey's ninther`를, 이보다 크면 중위법을 사용한다.
  - 중복 키가 많을 때 중복 키에 대해 파티셔닝 하면 시간 복잡도가 `Worst Case`가 된다. 해당 문제점을 방지하기 위해 `3-way partitioning` 기법을 사용한다.
    - 피벗값을 확정지은 후, `중복값, 앞에 오는 값, 뒤에 오는 값` 세 개의 구역으로 분할 하는 것
    - 중복 키가 많을 때 성능이 $N^2$가 되는 것을 방지한다.
    - `Edsger Dijkstra`가 제안한 [Dutch national flag problem](https://en.wikipedia.org/wiki/Dutch_national_flag_problem)의 해결법으로 파티셔닝 기법의 시간복잡도를 $O(N)$ 으로 만들 수 있다.
    - 때문에 전체 시간복잡도는 변하지 않는다.
 
  - `Time Complexity`
    - `Best Case` : $O(NlogN)$
    - `Average Case` : $O(NlogN)$
    - `Worst Case` : $O(N^2)$ (이미 정렬된 배열)
  - `Space Complexity` : $O(logN)$ (최악의 경우 $O(N)$)


## [Heap Sort](../SortAlgorithm/HeapSort.h)

  - 자료구조 [힙(heap)](DataStructure.md)을 사용하는 정렬 알고리즘
    - `힙(heap)`은 `완전 이진트리(Complete Binary Tree)`의 일종으로 `우선순위 큐`를 위하여 만들어진 자료구조
    - 최댓값이나 최솟값을 빠르게 찾아내도록 만들어졌다.
    - `이진 탐색 트리(Binary Search Tree)`와 다르게 중복된 값을 허용한다.
  - 오름차순 정렬일 때 `최대 힙`을, 내림차순 정렬일 때 `최소 힙`을 사용한다. 
    - 정렬 시 힙 생성을 완료하고(heapify) 루트를 맨 뒤로 보낸 후 (= 삭제) 나머지를 다시 정렬하는 작업을 반복하기 때문이다.
      - 최초 전체 배열 heapify ($N/2 * logN$) + 각 노드 heapify ($N * logN$)
    - 이렇게 하는 이유는 대소 관계를 부모 자식 노드만이 특정할 수 있고, 데이터 내 최대 최솟값을 루트 노드만으로 판별할 수 있기 때문이다.
  - `완전 이진트리`를 구현하고, Root값을 제외하도록 index를 변경하면서 나머지 트리를 계속해서 정렬한다.

  - $O(NlogN)$ 알고리즘 중에서는 느린 편이지만 중복 값이 많거나 역으로 정렬된 데이터는 매우 빠른 속도로 정렬이 가능하다.
    - 그냥 배열 돌면서 루트를 끝으로 보내기만 하면 되기 때문이다.
  
  - `Time Complexity` : $O(NlogN)$
  - `Space Complexity` : $O(1)$
  

## [Counting Sort](../SortAlgorithm/CountingSort.h)

  - `비교를 하지 않는 정렬(Non-Comparison)` 알고리즘 이다.
  - 정수 정렬 알고리즘이다.
  - 값을 키로 갖는 배열을 선언하여 해당 값의 개수를 배열안에 넣는다. 그 후 개수에 대한 산술을 사용하여 각 키 값의 위치를 결정한다.
  - 실행 시간이 `값의 개수 + (최댓값 - 최솟값)` 이기 때문에 값 차이가 많이 나지 않는 상황에서만 사용하는게 적합하다.
    - 내부에서 `최댓값 - 최솟값` 크기의 배열을 생성하기 때문에 메모리 상황도 좋지 않다.
    - 실제 루프 횟수 : 최솟값, 최댓값 계산(N) + 빈도수 세기(N) + 누적 빈도수(K) + 카피 배열 채우기(N) + 카피 배열 원본에 복사(N)
  - 더 큰 키를 효율적으로 처리할 수 있는 `기수 정렬(Radix Sort)`에서 서브 루틴으로 자주 사용된다.
 
  - `Time Complexity` : $O(N + K), K = 최댓값 - 최솟값$
  - `Space Complexity` : $O(N + K)$


## [Radix Sort](../SortAlgorithm/RadixSort.h)

  - `비교를 하지 않는 정렬(Non-Comparison)` 알고리즘 이다.
  - 정수 정렬 알고리즘이다.
  - 각 자리수에 따라 값들을 해당 버킷에 집어 넣고 순서대로 빼내서 정렬한다. 이 알고리즘을 최대 자리수 만큼 반복한다.
    - `버킷 소트(Bucket Sort)`의 일종으로 보기도 한다.
  - 크기가 유한하고 사전순으로 정렬이 가능해야 한다.
  - `기수`가 작아질수록 메모리에 읽고 쓰는 비용이 커진다. (`기수`가 `최댓값 - 최솟값` 이 되면 `Counting Sort(계수 정렬)`과 동일해진다.)
  - 기수 정렬은 `최상위 유효숫자(Most Significant Digit, MSD)`나 `최하위 유효숫자(Least Significant Digit, LSD)` 에서 시작하도록 구현할 수 있다.
    - 정렬 순서가 달라진다. [참고](https://ko.wikipedia.org/wiki/%EA%B8%B0%EC%88%98_%EC%A0%95%EB%A0%AC)
      - `1, 10, 2, 3 ...` 순으로 정렬된다.
    - [소스 코드](../SortAlgorithm/RadixSort.h)에 구현된 함수는 `최하위 유효숫자`에서 시작한다.
 
  - `Time Complexity` : $O(W * (N + K)), W = 기수의 크기, K = 진법의 자리수의 개수(기수의 도메인 크기)$
  - `Space Complexity` : $O(W + N)$


## [Bucket Sort](../SortAlgorithm/BucketSort.h)

  - `분산 정렬(Distribution)` 이다.
    - 데이터가 여러 중간 자료구조로 분산된 다음 다시 수집되어 출력되는 정렬 알고리즘을 의미한다.
  - [분할 정복 알고리즘 (Divide and Conquer Algorithm)] 이다.
  - `비교 정렬`, `비교를 하지 않는 정렬` 모두 구현이 가능한 알고리즘이다.
    - 버킷 내부의 정렬 시 사용하는 정렬 방법에 따라 달라진다.
  - 배열의 원소를 여러 버킷으로 분산하여 정렬한다. 보통 버킷 내부의 정렬은 [삽입 정렬](#insertion-sort)을 이용한다.
  - 버킷에 분산하는 과정이 `기수 정렬`에서 `기수`에 분배하는 것과 비슷하다.
  - 버킷의 개수가 $N$개에 가까울 수록, 배열이 균등 분포에 가까울 수록 성능이 올라간다.
    - 버킷의 개수가 $N$개가 되면 `계수 정렬`과 동일해진다.
 
  - `Time Complexity`
    - `Best Case` : $O(N), K \simeq N$
    - `Average Case` : $O(N + N^2/K + K), K = 버킷 수$
    - `Worst Case` : $O(N^2)$ (모든 값이 하나의 버킷으로 들어간 경우)
  - `Space Complexity` : $O(N * K)$


---
## 복합 정렬 알고리즘


## [Tim Sort](../SortAlgorithm/TimSort.h)

  - `Merge Sort + Insertion Sort`의 하이브리드 안정화 정렬 알고리즘이다.
  - `Java`, `Python`, `Android Platform` 등 다양한 프로그램의 기본 정렬 알고리즘으로 사용된다.
  - 실생활에서는 완전 랜덤한 배열을 정렬하지 않기 때문에 어느정도 정렬이 된 배열에 대해서 최고의 성능을 내도록 고안되었다.
  - `Run` 이라는 연속된 순서를 가진 덩어리들로 데이터를 쪼개 `스택`에 넣고 꺼내면서 `병합 정렬`을 진행한다.
    - 최초 $2^x$개의 데이터를 가지는 `MinRun`을 정의한다.
      - `MinRun`의 크기는 `Run`의 개수가 2의 거듭제곱이 되도록 유동적으로 정한다. (소스 코드에는 미반영)
      - 그래야 `병합 정렬` 시 시간이 빠르기 때문이다.
    - 해당 `MinRun`을 `삽입 정렬`으로 정렬한 후, 뒤에 오는 데이터들의 순서가 현재 정렬된 `Run`의 순서와 달라지기 전까지 전부 합친다.
    - 역순이 시작되면 그 지점부터 다시 `MinRun`을 형성하고 위의 과정을 반복한다.
 
    - 현재 정렬 순서와 반대로 정렬되어 있는 `Run`들의 순서를 뒤집는다.
      - !! `팀 소트`는 `안정 정렬`의 조건을 충족시켜야 한다. 뒤집힌 `Run`에 같은 값이 있으면 안된다. -> `MinRun` 생성 시 확인해야 한다.
    - `스택`에 추가할 때 두 개의 `Run`을 꺼내서 맨 위의 `Run`이 **가장 작은 덩어리가 되도록** 병합한다.
      - 피라미드 구조가 되면서 스택을 작게 유지할 수 있다. (피보나치 수열과 비슷함)
      - 병합 시 두 덩어리의 크기가 비슷할 수록 메모리를 최소로 사용할 수 있다.
      - 병합 과정에서 하나의 `Run`을 계속해서 참조하며 원소가 들어갈 위치를 찾을 때, `Galloping` 이라는 최적화 방법을 사용하여 약간 더 빠르게 위치를 찾을 수 있다.
      - [소스 코드](../SortAlgorithm/TimSort.h)에는 구현하지 않았다. (데이터가 굉장히 클 때 의미가 있음)
  - `N`의 크기가 작을 경우($< 2^6$) 성능을 위해 `Binary Insertion Sort`를 대신 사용한다.
  - 자세한 내용은 아래 참고
    - [Naver D2](https://d2.naver.com/helloworld/0315536)
    - [Wikipedia](https://en.wikipedia.org/wiki/Timsort)
  
  - `Time Complexity`
    - `Best Case` : $O(N)$
    - `Average Case` : $O(NlogN)$
    - `Worst Case` : $O(NlogN)$
  - `Space Complexity` : $O(N)$ (`Merge Sort`보다 작은 값)


## [Intro Sort](../SortAlgorithm/IntroSort.h)

  - `Quick Sort + Heap Sort + Insertion Sort`의 하이브리드 정렬 알고리즘이다.
 
  - `Quick Sort`의 `Worst Case`를 보완하기 위해 고안되었다.
  - 현재 `STL` 라이브러리의 `std::sort` 함수가 사용하고 있는 정렬 방법이다.
  - `Quick Sort` 도중 재귀 호출의 깊이가 $\left \lfloor 2LogN \right \rfloor$을 넘어가면 아래의 동작을 수행한다. (`STL` 라이브러리는 `1.5 logN` 의 근사값을 사용한다.)
    - 현재 부분 리스트의 크기가 16 이상일 경우 `Heap Sort`를 수행한다.
    - 현재 부분 리스트의 크기가 16 미만일 경우 `Insertion Sort`를 수행한다.
    - `ceil`은 올림 처리, `floor`는 내림 처리, `round`는 반올림 처리이다.
  - `16`의 값은 연구 결과를 통해 나온 최적의 값이다. (`Tim Sort`의 `Gallop`과 다르게 고정값이다.)
    - 현재 `STL` 라이브러리의 삽입 정렬 리스트 최대 크기값(`_ISORT_MAX`)은 `32`이다.
  
  - `Time Complexity` : $O(NlogN)$
  - `Space Complexity` : $O(1)$


---
# [Graph Algorithm (Graph Traversal)](../GraphAlgorithm/GraphAlgorithm.cpp)

  - `Spanning Tree`
    - 그래프 내의 모든 정점을 최소 간선의 수로 연결하는 부분 그래프
    - $N$개의 정점이 $N - 1$개의 간선으로 연결되어 있다.
    - 하나의 그래프에서 여러 개의 `Spanning Tree`가 나올 수 있다.
    - 모든 정점들이 연결되어 있어야 하며, `사이클`을 포함해서는 안된다.
    - 통신 네트워크 구축 등에 사용된다.
  - `Minimum Spanning Tree (MST)`
    - 간선들의 가중치가 동일하지 않을 경우, 간선들의 가중치 합이 최소가 되는 `Spanning Tree`
    - `Spanning Tree`의 성질을 모두 갖고 있다.
  - 보통 `최소 가중치`를 구하는 알고리즘들은 거의 [탐욕 알고리즘(greedy algorithm)]이다.
  - `그래프`를 표현하는 방법
    1. `Adjacency Matrix (인접 행렬)` : 버텍스 x 버텍스 크기의 `이중 배열` 사용, 간선 수가 많을 때 효율적임
    2. `Adjacency List (인접 리스트)` : 각 버텍스를 `연결 리스트` 형태로 사용, 메모리 상 효율적이나 `간선 존재여부` 탐색 시간이 $O(V)$ 이다. (간선이 많으면 비효율적)
    3. `Edge List (간선 리스트)` : `시작 노드`, `도착 노드`, `가중치` 를 갖는 자료형 배열을 사용, 모든 간선을 반복하는 알고리즘의 경우 효율적이다.


## [Kruskal's Algorithm](../GraphAlgorithm/Kruskal.h)

  - `Minimum Spanning Tree`를 찾는 알고리즘이다.
  - `Edge List (간선 리스트)` 형태의 그래프가 구현이 편하다.
  - 동작 순서
    1. 그래프의 모든 간선들을 가중치 별로 정렬한다. (오름차순)
    2. 사이클 확인용 테이블을 생성한다. (길이: 버텍스 개수)
    3. 간선을 차례로 선택하면서 사이클을 만들지 않는지 확인한다.
    4. 모든 간선을 확인할 때 까지 반복한다.
  - $E$를 간선의 개수, $V$를 정점의 개수라고 할 때, `Kruskal Algorithm`은 $O(ElogV)$ 시간안에 동작한다.
    - 간선의 가중치 별 정렬시간($O(ElogE)$) + [서로소 집합(Disjoint Set)](DataStructure.md#disjoint-set)을 통한 사이클 찾기 동작($O(ElogV)$)
    - $V <= 2E$이기 때문에 $logV == O(logE)$
    - 알고리즘 최종 `Time Complexity`는 $O(ElogE)$이 된다.
 
  - **노드가 많고 간선이 적은 그래프**에서 `MST`를 찾을 때 유용하다.


## [Prim's Algorithm](../GraphAlgorithm/Prim.h)

  - `Minimum Spanning Tree`를 찾는 알고리즘이다.
  - 동작 순서
    1. 임의의 한 노드를 선택한다.
    2. 해당 노드와 연결된 간선들을 저장한다. (큐 또는 배열)
    3. 저장한 간선들 중 `가장 가중치가 작은 간선`을 선택하여 트리에 추가한다. (해당 노드의 방문 확인용 변수도 갱신) 
    4. 선택한 간선을 제거하고 노드와 연결된 간선들을 추가로 저장한다.
    5. 모든 노드를 방문할 때 까지 3, 4번을 반복한다.
  - 시간 복잡도가 주어지는 그래프의 형태와 `최소 비용 간선`을 찾는 알고리즘에 따라 달라진다.
    - 인접 행렬 그래프 : $O(V^2)   (V = 정점의 개수)$
    - 인접 리스트 + 이진 힙 : $O(ElogV)$
    - 인접 리스트 + 피보나치 힙 : $O(E + VlogV)$
 
  - **노드가 적고 간선이 많은 그래프**에서 `MST`를 찾을 때 유용하다.


## [Floyd-Warshall Algorithm](../GraphAlgorithm/FloydWarshall.h)

  - 모든 노드 사이의 최단 거리를 알아내는 [전체-쌍 최단 경로 문제] 알고리즘이다.
  - 이름이 많다 (Floyd, Roy–Warshall, Roy–Floyd, WFI)
  - 두 버텍스 간의 `추정 최단 경로`를 최적이 될 때까지 반복해서 최단 경로로 갱신한다.
  - 한 노드에서 다른 노드로 가는 최단 경로를 계산할 때, `중간에 거쳐가는 노드`를 바꿔가면서 반복한다.
    - 사실 방법만 다를뿐이지 모든 그래프 알고리즘은 이 공식을 사용한다.
    $$
      shortestPath (i,j,0) = w(i,j) \quad (w(i,j) = 간선의 가중치) \\
      shortestPath (i,j,k)= 
      min \Big( shortestPath (i,j,k-1)+ shortestPath (k,j,k-1)\Big)
    $$
    - $k == 1$ 일 때, 각 노드 사이의 최단 거리는 간선의 가중치와 같다.

  - `Time Complexity`가 $\Omega(|V|^3)$ 이다.
    - 그래프에서는 최대 $\Omega(|V|^{2})$의 변이 있을 수 있고, 모든 변의 조합을 확인하기 때문이다. 
    - 노드의 수가 많아질수록 기하급수적으로 느려진다.
  

## [Dijkstra Algorithm](../GraphAlgorithm/Dijkstra.h)

  - 특정 노드와 전체 노드간의 최단거리를 알아내는 [단일-출발 최단 경로 문제] 알고리즘이다.
  - `음이 아닌 가중치가 있는 그래프`에서만 사용이 가능하다.
    - `사이클`이 만들어질 수 있기 때문이다.
  - 동작 순서
    1. 시작 노드(s)에서 모든 노드까지의 거리를 배열에 저장한다. (연결되어 있지 않으면 최댓값을 저장, 시작 노드의 인덱스에는 0을 저장)
    2. 중간에 경유하는 노드를 저장할 배열을 만든다. (없어도 됨, 기본값은 -1)
    3. 시작 노드와 `연결되어 있으면서 방문하지 않은` 노드 중 **가장 가까운 (가장 가중치가 작은)** 노드(m)를 선택한다.
    4. 해당 노드(m)와 연결된 간선 하나를 선택한다.
    5. 간선의 노드(d) 사이 최단거리(dist[d])와 중간 노드(m)를 경유하는 경로의 거리(dist[m] + m.cost)를 비교한다.
    6. 경유 경로의 크기가 작다면 최단거리(dist[d])를 갱신하고 필요하다면 경유지를 저장한다.(prev[d] = m)
    7. 중간 노드(m)을 방문한 상태로 갱신한다.
    8. 모든 노드를 방문할 때 까지 3 ~ 7번을 반복한다.
 - 경유하는 노드를 지정할 때, **가장 가까운 곳부터 확인**해야 한다. 그래야 먼 곳의 경로를 확인할 때 정확하게 최단 거리를 측정할 수 있다.
 - 모든 노드를 경유하는 노드로 만들어서 확인해봐야 하기 때문에 `버텍스 개수 - 1`만큼 반복한다.
  - `Prim's Algorithm`과 비슷하게 최단 거리의 정점을 찾는 방법에 따라 시간 복잡도가 달라진다.
    - 일반 검색 : $O(V^2 + E)   (V = 정점의 개수, E = 간선의 개수)$
    - 우선순위 큐 : $O(VlogE + ElogE)$
    - 피보나치 힙 : $O(VlogV + E)$  -> 상수가 커서 거의 사용하지 않는다.

  - 참고
    - https://www.secmem.org/blog/2019/01/09/wrong-dijkstra/
    - https://ko.wikipedia.org/wiki/%EB%8D%B0%EC%9D%B4%ED%81%AC%EC%8A%A4%ED%8A%B8%EB%9D%BC_%EC%95%8C%EA%B3%A0%EB%A6%AC%EC%A6%98


## [Bellman-Ford Algorithm](../GraphAlgorithm/BellmanFord.h)

  - 특정 노드와 전체 노드간의 최단거리를 알아내는 [단일-출발 최단 경로 문제] 알고리즘이다.
  - `음수 가중치`를 처리할 수 있다. (`음수 가중치 사이클`을 발견할 수 있다.)
  - `Edge List (간선 리스트)` 형태의 그래프가 구현이 편하다.
  - 노드 개수만큼 반복문을 돌면서 최단 경로를 발견하는데, 마지막에 한번 더 반복할 때 최단 경로가 또 갱신된다면, `음수 가중치 사이클`이 존재한다.
    - 최단 경로를 구성하는 간선의 개수는 `노드의 개수 - 1`을 넘을 수 없기 때문이다.
  - 기본적으로 `Dijkstra Algorithm` 과 원리는 동일하지만 음수 가중치를 처리할 수 있기 때문에 더 느리다.
 
  - `Time Complexity`는 $\Theta(|V||E|)$ 이다.


## [A* Algorithm](../GraphAlgorithm/AStar.h)

  - 특정 노드 사이의 최단거리를 알아내는 알고리즘
  - 최적 경로를 찾기 위해 각각의 노드에 대한 `평가 함수`를 정의한다.
    - $f(n) = g(n) + h(n)$
    - g(n) : 시작 노드에서 노드 n 까지의 경로 가중치
    - h(n) : 노드 n ~ 도착 노드 까지의 추정 경로 가중치
 
  - `Dijkstra Algorithm`과 유사하다.
  - 차이점은 각 노드에 대해 해당 노드를 통과하는 최상의 경로를 추정하는 순위값인 `휴리스틱 추정값`($h(n)$)을 기존 가중치($g(n)$)에 더해서 비용 계산을 한다는 것이다.
    - 비교할 때 `간선 가중치`만 쓰는 것이 아니라 `노드들이 가진 추정값`까지 더해서 비교한다는 것이다.
    - `Dijkstra Algorithm` 은 모든 노드 $n$에 대해 항상 $h(n) = 0$ 인 `A* Algorithm`의 특수 케이스이다.
    - `너비 우선 탐색(Breadth-first search, BFS)` 으로 볼 수 있다.
  - 휴리스틱 함수의 구현에 따라 최적 경로가 결정되기 때문에 **최단 경로가 아닐 수 있다.**
    - 정확한 정보를 포기한 대신 `Dijkstra Algorithm` 보다 빠르다.
  - 일반화하면 경로 대신 횟수같은 값으로도 변경해서 적용할 수 있다. 값을 비교할 수만 있으면 된다.
 
  - `데카르트 좌표계` 내에서 특정 좌표까지의 최단거리를 알아낼 때 사용할 수 있다.
    - $g(n)$ 은 `현재 좌표 - 시작 좌표`, $h(n)$ 은 `목적지 좌표 - 현재 좌표`
    - 타일맵 게임의 경우, [Manhatten Distance(맨해튼 거리)](https://ko.wikipedia.org/wiki/%EB%A7%A8%ED%95%B4%ED%8A%BC_%EA%B1%B0%EB%A6%AC)를 $h(n)$ 으로 사용한다.
      - 대각선 거리는 근사값으로 `1.4`를 사용한다. 대각선의 각도가 45도가 되도록 만들어 주는게 핵심

  - 참고
    - https://www.secmem.org/blog/2020/04/19/astar/
    - http://buildnewgames.com/astar/
    - https://terms.naver.com/entry.naver?docId=3567439&cid=58944&categoryId=58970


---
# Hash Algorithm

  - 





---
# Sieve of Eratosthenes (에라토스테네스의 체)

  - 소수 (`Prime Number`) 판별 알고리즘
  - TODO https://m.blog.naver.com/ndb796/221233595886





[탐욕 알고리즘(greedy algorithm)]: https://ko.wikipedia.org/wiki/%ED%83%90%EC%9A%95_%EC%95%8C%EA%B3%A0%EB%A6%AC%EC%A6%98
[분할 정복 알고리즘 (Divide and Conquer Algorithm)]: https://ko.wikipedia.org/wiki/%EB%B6%84%ED%95%A0_%EC%A0%95%EB%B3%B5_%EC%95%8C%EA%B3%A0%EB%A6%AC%EC%A6%98
[단일-쌍 최단 경로 문제]: https://ko.wikipedia.org/wiki/%EC%B5%9C%EB%8B%A8_%EA%B2%BD%EB%A1%9C_%EB%AC%B8%EC%A0%9C
[전체-쌍 최단 경로 문제]: https://ko.wikipedia.org/wiki/%EC%B5%9C%EB%8B%A8_%EA%B2%BD%EB%A1%9C_%EB%AC%B8%EC%A0%9C