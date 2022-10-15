#pragma once

#include <functional>
#include "InsertionSort.h"
#include "HeapSort.h"

// arr[begin, end) (end <= length)
template <typename T>
uint32_t SortIntro(T* arr, int begin, int end) {
	return SortIntro(arr, begin, end, Ascend<>{});
}

// arr[begin, end) (end <= length)
template <typename T, class Func>
uint32_t SortIntro(T* arr, int begin, int end, Func cmp) {
	uint32_t count = 0;

	// Quick Sort -> [begin, end)
	std::function<void(int, int, int)> quick = [&](int s, int e, int depth) {
		++count;
		for (;;) {
			if (e - s <= 16) {
				SortInsertion(arr, s, e, cmp);
				return;
			}
			if (depth <= 0) {
				SortHeap(arr, s, e, cmp);   // length를 인자로 주어야 한다.
				return;
			}

			// divide
			// 피벗 생성 (median of 3 + Tukey'begin ninther)
			int mid = (begin + end) / 2;
			GuessMedian(arr, s, mid, e - 1, cmp);
			count += 12;

			// 3-way partitioning
			T pivot = arr[mid];   //! 피벗값을 따로 빼놓지 않으면 정렬이 제대로 안된다. 스왑할 때 위치가 바뀌는 경우가 있기 때문
			int pStart = s;
			int pEnd = e - 1;
			for (int j = s; j <= pEnd;) {
				++count;
				if (cmp(arr[j], pivot)) {   // j값이 피벗값보다 왼쪽값이다. -> pStart와 스왑, pStart 인덱스 증가
					++count;
					Swap(arr[pStart], arr[j]);
					++pStart;
					++j;
				} else if (cmp(pivot, arr[j])) {   // j값이 피벗값보다 오른쪽값이다. -> pEnd와 스왑, pEnd 인덱스 감소
					++count;
					Swap(arr[j], arr[pEnd]);
					--pEnd;
				} else {
					++count;
					++j;
				}
			}

			// STL 내부에서 사용하는 depth 공식
			depth = (depth >> 1) + (depth >> 2);   // allow 1.5 log2(N) divisions

			// conquer
			if (pStart - begin < end - pEnd + 1) {   // 피벗 오른쪽 구역 정렬
				quick(s, pStart, depth - 1);
				begin = pEnd + 1;
			} else {   // 피벗 왼쪽 구역 정렬
				quick(pEnd + 1, e, depth - 1);
				end = pStart;
			}
			++count;
		}
	};

	int maxDepth = 2 * log2(end - begin);

	quick(begin, end, maxDepth);

	return count;
}