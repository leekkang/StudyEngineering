#pragma once

#include <memory.h>
#include <type_traits>
#include <vector>
#include <functional>

#include "Share.h"


// arr[begin, end) (end <= length)
template <typename T, class Func>
uint32_t SortMergeTopDown(T* arr, int begin, int end, Func cmp) {
	uint32_t count = 0;
	std::vector<T> temp(end - begin);   // resize. not reserve

	// 하향식 2-way merge sort
	// 재귀함수로 사용하기 때문에 auto 타입으로 정의하지 못한다. -> inline이 아니다.
	std::function<void(const int&, const int&)> merge = [&](const int& s, const int& e) {
		// e 는 인덱스에 포함되지 않는다. -> arr[e] : x, arr[e-1] : o 	-> [s, e)
		++count;
		if (e - s < 2) // 1개 남으면 combine을 진행한다.
			return;

		// begin + end 가 홀수면 왼쪽 리스트의 길이가 오른쪽 리스트의 길이보다 짧다.
		// divide
		int m = (s + e) / 2;

		// conquer
		merge(s, m);
		merge(m, e);

		++count;
		// 왼쪽과 오른쪽이 섞이는 경우에만 결합체크와 복사를 한다. 섞이지 않는다면 이미 정렬되어 들어가 있을 것이다.
		if (!cmp(arr[m], arr[m - 1]))	// == arr[m - 1] <= arr[m]
			return;

		// combine
		int left = s, right = m;
		for (int i = s - begin; i < e - begin; ++i) {
			// 왼쪽 리스트가 끝나지 않은 상황에서, 오른쪽 리스트가 끝났거나 왼쪽의 값이 오른쪽 값보다 작거나 같은 경우 (left <= right를 표현하기 위해 > 의 역을 취했다.)
			// 동일한 값인 경우 순서를 보존해야 하기 때문에 왼쪽 값을 우선해서 넣는다. 
			if (left < m && (right >= e || !cmp(arr[right], arr[left])))
				temp[i] = arr[left++];
			else
				temp[i] = arr[right++];

			++count;
			++count;
		}

		// copy
		if constexpr (std::is_trivially_copyable_v<T>) {
			memcpy(&arr[s], &temp[s - begin], sizeof(T) * (e - s));
			++count;
		} else {
			for (int i = s; i < e; ++i) {
				arr[i] = temp[i - begin];
				++count;
			}
		}
	};

	merge(begin, end);

	return count;
}
template <class T>
uint32_t SortMergeTopDown(T* arr, int begin, int end) {
	return SortMergeTopDown(arr, begin, end, Ascend<>{});
}

// arr[begin, end) (end <= length)
template <typename T, class Func>
uint32_t SortMergeBottomUp(T* arr, int begin, int end, Func cmp) {
	uint32_t count = 0;
	int length = end - begin;
	std::vector<T> temp(length);   // resize. not reserve

	int left, right, m, e;
	// divide
	for (int width = 1; width < length; width *= 2) {
		++count;
		// conquer
		for (int s = begin; s < end; s += width * 2) {	// s는 나뉘어진 블록들의 시작 인덱스이다.
			++count;
			e = std::min(s + width * 2, end);           // e는 다음 블록의 시작 인덱스와 배열의 끝 중 작은 값이다.
			left = s;
			right = std::min(s + width, end);   		// 중간값 또한 배열의 끝보다 작은 값이어야 한다.
			m = right;

			++count;
			// 왼쪽과 오른쪽이 섞이는 경우에만 결합체크와 복사를 한다. 섞이지 않는다면 이미 정렬되어 들어가 있을 것이다.
			if (m == e || !cmp(arr[m], arr[m - 1]))		// == arr[m - 1] <= arr[m]
				continue;

			// combine
			for (int i = s - begin; i < e - begin; ++i) {
				// 왼쪽 리스트가 끝나지 않은 상황에서, 오른쪽 리스트가 끝났거나 왼쪽의 값이 오른쪽 값보다 작을 경우 (left <= right를 표현하기 위해 > 의 역을 취했다.)
				// 동일한 값인 경우 순서를 보존해야 하기 때문에 왼쪽 값을 우선해서 넣는다.
				if (left < m && (right >= e || !cmp(arr[right], arr[left])))
					temp[i] = arr[left++];
				else
					temp[i] = arr[right++];

				++count;
				++count;
			}

			// copy
			if constexpr (std::is_trivially_copyable_v<T>) {
				memcpy(&arr[s], &temp[s - begin], sizeof(T) * (e - s));
				++count;
			} else {
				for (int i = s; i < e; ++i) {
					arr[i] = temp[i - begin];
					++count;
				}
			}
		}
	}

	return count;
}
template <class T>
uint32_t SortMergeBottomUp(T* arr, int begin, int end) {
	return SortMergeBottomUp(arr, begin, end, Ascend<>{});
}