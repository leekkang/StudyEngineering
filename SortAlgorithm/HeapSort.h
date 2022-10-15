#pragma once

#include <memory.h>
#include <type_traits>

#include "Share.h"


// arr[begin, end) (end <= length)
template <typename T>
uint32_t SortHeap(T* arr, int begin, int end) {
	return SortHeap(arr, begin, end, Ascend<>{});
}

// arr[begin, end) (end <= length)
template <typename T>
uint32_t SortHeapFromSTL(T* arr, int begin, int end) {
	return SortHeapFromSTL(arr, begin, end, Ascend<>{});
}


// arr[begin, end) (end <= length)
template <typename T, class Func>
uint32_t SortHeap(T* arr, int begin, int end, Func cmp) {
	uint32_t count = 0;
	// !오름 차순이면 최대 힙을, 내림 차순이면 최소 힙을 구성한다.
	
	// 인자로 받은 노드를 루트 노드로 하는 트리 내에서 노드의 위치를 결정하는 함수이다.
	// 포함 관계 : [top, bottom)
	auto downHeap = [&](int top, int bottom) { 
		// 자식을 가지는 노드의 최대 인덱스 = 트리 노드 길이 / 2 - 1
		// 자식 노드가 없으면 루프문 종료
		for (; top < (bottom >> 1);) {
			++count;
			int child = top;
			int left = top * 2 + 1;
			int right = left + 1;

			count += 2;
			// 먼저 왼쪽 자식 노드와 비교한다. (오른쪽 값이면 왼쪽 값이 될 수 있도록 변경한다 -> 정렬순서와 반대로)
			if (cmp(arr[begin + child], arr[begin + left]))
				child = left;
			// 오른쪽 자식이 있을 때 비교한다. 위에서 값이 바뀌었다면 형제 노드의 크기 비교가 진행된다.
			if (right < bottom && cmp(arr[begin + child], arr[begin + right]))
				child = right;

			// 위치가 바뀌지 않으면 종료
			if (child == top)
				break;

			++count;
			Swap(arr[begin + child], arr[begin + top]);
			top = child;
		}
	};

	// Build Heap (Heapify) -> 자료구조가 힙 성질을 만족하도록 수정하는 연산. 전체 배열의 절반값부터 루트 노드까지 올라가면서 스위칭한다.
	int bottom = end - begin;
	for (int top = bottom >> 1; top > 0;) {
		--top;
		++count;
		downHeap(top, bottom);
	}

	// 루트와 가장 끝 인덱스의 값을 교환한 후 힙 구조를 다시 만든다.
	for (; end - begin > 1;) {
		--end;
		++count;
		Swap(arr[end], arr[begin]);
		downHeap(0, end - begin);
	}
	
	return count;
}

// STL 내부의 heap sort와 로직을 동일하게 만들어 봄. 코드 흐름 참고용
// 코드의 재사용성을 위해 기능별로 나눠서 함수가 불필요해 보이는 부분이 있을 수 있다. 
// -> 배열의 마지막 값을 루트로 보내는 것은 똑같지만, 위의 코드는 자식 노드와 값을 바로 비교하고 스왑한다.
//    이 코드에는 1. 값을 빼내 hole을 만들고, 2. 해당 hole을 가지 제일 밑으로 보낸 뒤, 3. 값을 hole에 넣고, 
// 				 4. 루트쪽으로 올라오면서 값을 비교하며 hole의 위치를 잡은 뒤, 5. hole에 값을 넣는다.
// arr[begin, end) (end <= length)
template <typename T, class Func>
uint32_t SortHeapFromSTL(T* arr, int begin, int end, Func cmp) {
	uint32_t count = 0;

	// _Push_heap_by_index 함수 부분 -> hole 부분에 값을 넣고 트리를 heapify 한다.
	// 오름차순 정렬이면 max heap을, 내림차순 정렬이면 min heap을 만든다. (비교 부분의 인자가 거꾸로다.)
	auto PushHeapByIndex = [&](int hole, int top, T&& value) {
		// top 노드가 나올 때 까지 부모와 값 비교 
		for (int i = (hole - 1) >> 1; top < hole && cmp(arr[begin + i], value); i = (hole - 1) >> 1) { 
			// move hole up to parent
			arr[begin + hole] = std::move(arr[begin + i]);
			hole = i;
		}

		arr[begin + hole] = std::forward<T>(value);
	};

	// _Pop_heap_hole_by_index 함수 부분 -> 값이 빠진 노드를 트리 가장 밑으로 내린다.
	// 이 때 value의 값 비교는 하지 않는다.   
	// [begin, bottom)
	auto PopHeapHoleByIndex = [&](int hole, int bottom, T&& value) {
		// percolate hole to bottom, then push _Val
		if (bottom > 0);

		const int top = hole;
		int index     = hole;
		
		// 자식이 있는 노드의 최대 인덱스값.
		const int maxNonLeaf = (bottom - 1) >> 1;
		while (index < maxNonLeaf) {
			index = 2 * index + 2;
			// 왼쪽 자식 노드가 정렬 시 오른쪽에 온다면 인덱스를 1 감소시킨다. (정렬 순서와는 반대로다.)
			if (cmp(arr[begin + index], arr[begin + (index - 1)]))
				--index;
				
			arr[begin + hole] = std::move(arr[begin + index]);
			hole = index;
		}

		// ex) 길이가 8인 배열의 트리 구조
		//     0
		//   1   2
		//  3 4 5 6
		// 7
		// 오버플로우를 막기 위해 자식이 1개 있는 마지막 노드는 따로 계산한다.
		if (index == maxNonLeaf && bottom % 2 == 0) { 
			arr[begin + hole] = std::move(arr[begin + (bottom - 1)]);
			hole = bottom - 1;
		}

		PushHeapByIndex(hole, top, std::forward<T>(value));
	};

	// _Make_heap_unchecked 함수 부분 -> 전체 데이터 절반부터 반복문 돌면서 마지막 값을 빼낸 뒤 _Pop_heap_hole_by_index 호출
	int bottom = end - begin;
	for (int hole = bottom >> 1; hole > 0;) {
		--hole;
		T value = std::move(arr[begin + hole]);
		PopHeapHoleByIndex(hole, bottom, std::forward<T>(value));
	}
	
	// _Sort_heap_unchecked 함수 -> 반복문 돌면서 _Pop_heap_unchecked 호출
	for (; end - begin > 1;) {
		// _Pop_heap_unchecked 함수 부분 -> 마지막 인덱스 1 감소 후 해당 값 빼내서 _Pop_heap_hole_unchecked 호출
        --end;
        T value = std::move(arr[end]);

		// _Pop_heap_hole_unchecked 함수 부분 -> 첫 번째 인덱스에 빼낸 값 추가 후 _Pop_heap_hole_by_index 호출
        arr[end] = std::move(arr[begin]);
		PopHeapHoleByIndex(0, end - begin, std::forward<T>(value));
	}
	
	return count;
}