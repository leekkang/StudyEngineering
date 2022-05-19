
## Data Structure
  - 자료구조 관련 정보들을 저장해놓는 문서

  - 참고
    - [Containers library](https://en.cppreference.com/w/cpp/container)
    - [실전 알고리즘 강좌](https://blog.encrypted.gg/category/%EA%B0%95%EC%A2%8C/%EC%8B%A4%EC%A0%84%20%EC%95%8C%EA%B3%A0%EB%A6%AC%EC%A6%98)
    - [C++ STL 컨테이너의 메모리 사용량 1](https://www.secmem.org/blog/2019/11/14/c++-container-memory-usage/)


---
# STL의 Allocator 분석

  - STL의 모든 자료구조가 해당 클래스의 함수로 메모리를 할당받길래 궁금해서 찾아봄
  - TODO

---
# Hash table

  - 해시 함수가 다른 키값에 동일한 해시 코드를 출력할 경우 `해시 충돌`이 발생한다.

  - 참고
    - [실전 알고리즘 해시](https://blog.encrypted.gg/1009?category=773649)

## 해시 충돌 해결방법

  - `Chaining`
    - 해시 테이블 인덱스에 해당하는 자료구조를 연결 리스트로 만드는 방법
    - 동일한 해시 키를 갖는 페어를 리스트에 넣기만 하면 된다.
    - 값을 찾을 때는 리스트를 순회한다. -> `worst case`의 경우 조회 복잡도가 $O(n)$이 된다.
  - `C++`은 해시 충돌 해결 방법으로 `Chaining`을 선택했다. 
    - 각 버킷이 리스트를 갖는 형태가 아니고 리스트가 1개 있고 버킷은 자신이 필요로 하는 노드의 포인터를 값으로 가진다.


## `unordered_map` 동적 할당 메모리 사용량 (64비트 기준)

  - 특성 정보(`_Umap_traits`) 초기화가 일어나지만, 자세한건 모르니 넘어간다. (TODO)
 
  - 맨 처음으로 버킷의 요소인 리스트 (`_List`)를 초기화한다. (벡터인 버킷의 초기화 전에 발생한다.)
    - 리스트는 `_List_node`와 `_List_val`의 페어인 `_Mypair` 변수를 가지고 있다.
      - `_List_node` 구조체는 자기 자신의 포인터 타입인 `_Prev`와 `_Next`, 리스트 값의 타입인 `_Value_type` 변수를 가진다.
 
      - `_List_val` 클래스는 `_List_node`의 포인터 타입인 `_Myhead`와 `size_t` 타입인 `_Mysize` 변수를 가진다.
 
    - 리스트의 생성자에서 `_List_node` 포인터 형태의 `_Newhead`를 생성한다. 이 객체는 `_Myhead` 와 연결된다.
    - 서클 링크드 리스트의 형태이다.
    - 동적 할당 메모리 크기는 `16 + map의 페어 타입 크기` 가 된다.
  - 두 번째로 해시 벡터(`_Hash_vec` 구조체 타입인 `_Vec`)를 초기화 한다.
    - 해시 벡터는 `_List_node`의 반복자 타입인 `_Aliter`와 `_Vector_val`의 페어인 `_Mypair` 변수를 가지고 있다.
      - `_Vector_val` 클래스는 `_Aliter`의 포인터 타입인 `_Myfirst`, `_Mylast`, `_Myend` 변수를 가진다.
  - 키의 마스크 값인 `_Mask` 와 버킷의 크기인 `_Maxidx` 를 초기화한다.
    - `_Mask` 값은 해시 키 체크값으로 사용해야 하기 때문에 `_Maxidx` - 1 이다.
  - 마지막으로 해시 벡터의 크기를 `_Min_buckets * 2 = 16` 만큼 할당한다.
    - `static constexpr _Min_buckets` 의 값은 8이다.
 
    - `STL` 은 버킷의 크기가 `실제 테이블에 들어있는 값`의 **2배보다 항상 크다**는 것을 알 수 있다.
    - 벡터의 크기를 늘릴 때 벡터 안에 있던 값들은 복사하지 않고 초기값(`_MyHead`)으로 변경한다.
      - 어차피 새로운 `해시 함수`를 사용해서 재배치(rehash) 해야 하기 때문이다.
  
      - 테이블에 값이 많이 들어와서 재배치 할 때는 초기화와 함께 리스트를 끝까지 돌면서 `해시 키`를 다시 뽑아낸 후 벡터에 값을 대입한다.
    - 동적 할당 메모리 크기는 `8 * 16 = 128` 이 된다.
  - `unordered_map` 에 값을 추가할 때마다 `_List_node` 의 크기만큼 동적 할당이 발생한다.
    - `std::pair` 는 구조체라 바이트 패딩이 적용된다. 계산할 때 주의할 것
   
    - `std::string`의 크기는 `32 byte` 이다.
  - 추가한 값의 개수가 `bucket_count()` 값과 동일해지는 순간 재배치(rehash)가 발생한다.
    - 버킷의 크기는 $2^3 -> 2^6 -> 2^9$ 순으로 커진다.
   
    - 벡터의 크기는 `버킷의 크기 X 2` 이다.
    - 실제로 할당되는 바이트 수는 약간 달랐다. ($2^9$일 때, 8231 byte가 할당되었다. 예상은 8192 byte 였음)

```cpp
	std::cout << "\n -arch=x64 build\n" << std::endl;

	std::cout << "unordered_map<int, int64_t> define" << std::endl;
	std::unordered_map<int, long long> map;
	std::cout << "\nsizeof map" << std::endl;
	std::cout << sizeof(map) << std::endl;
	std::cout << "\nmap initial bucket_count() : ";
	int count = map.bucket_count();
	std::cout << count << std::endl;
	for (int i = 0; i <= count; ++i) {
		std::cout << "map.emplace " << i + 1 << std::endl;
		map.emplace(std::make_pair(i, i));
	}
	std::cout << map.bucket_count() << std::endl;
	std::cout << "\n delete dynamic duration" << std::endl;
```

![](img/unordered_map_memory.png)

  - 참고
    - [다시 정리하는 C++ STL 자료구조](https://ssinyoung.tistory.com/48)
    - [C++ STL 컨테이너의 메모리 사용량 2](https://www.secmem.org/blog/2019/12/13/c++-container-memory-usage-2/)