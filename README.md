# StudyEngineering

* This repository is for personal study.

## [Huffman Code](Huffman.cpp)

* 빈도 종속 인코딩 알고리즘을 사용한 코드
* 개발자인 데이비드 허프만 이름을 따서 허프만 코드라고 한다.
  * 빈도 종속 인코딩 : 비트 패턴의 길이를 해당 항목이 사용되는 빈도의 역과 관련시켜 결정하는 무손실 데이터 압축방법
* [탐욕 알고리즘(greedy algorithm)](https://ko.wikipedia.org/wiki/%ED%83%90%EC%9A%95_%EC%95%8C%EA%B3%A0%EB%A6%AC%EC%A6%98) 이다.

## [Lempel-Ziv-Welch algorithm](LZWAlgorithm.cpp)

* 적응형 사전 인코딩(adaptive dictionary encoding) 알고리즘을 사용한 코드
  * 적응형 사전 인코딩 : 메시지 항목들의 집합을 사전으로, 메시지는 사전의 참조 표시로 인코딩. 인코딩 과정중에 사전의 항목이 변화한다.
* 1978년 `Lempel`과 `Ziv`에 의해 만들어졌으며,(LZ78) 1984년 `Welch`에 의해 추가 수정되었다.
* 텍스트 파일과 같이 반복되는 문자열이 있는 파일에서 압축률이 가장 높다.
* 사전은 무한히 수정되지 않고 최대 항목 수를 지정한다. 결국 자주 발생하는 하위 문자열이 사전에 들어가게 된다.
* 데이터의 제한된 분석만 수행하기 때문에 최적으로 동작하지는 않는다.
* [참조](https://www2.cs.duke.edu/csed/curious/compression/lzw.html), [참조:위키피디아](https://ko.wikipedia.org/wiki/LZW)
