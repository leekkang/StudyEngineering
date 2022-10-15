#pragma once

#include <memory.h>
#include <type_traits>

#include "Share.h"


// arr[begin, end) (end <= length)
template <class T>
uint32_t SortInsertion(T* arr, int begin, int end) {
	return SortInsertion(arr, begin, end, Ascend<>{});
}

// arr[begin, end) (end <= length)
template <class T>
uint32_t SortInsertionBinary(T* arr, int begin, int end) {
	return SortInsertionBinary(arr, begin, end, Ascend<>{});
}


// arr[begin, end) (end <= length)
#if _HAS_CXX17
template <class T, class Func, std::enable_if_t<std::is_trivially_copyable_v<T>, bool> = true>
#else 
template <class T, class Func, std::enable_if_t<std::is_trivially_copyable<T>::value, bool> = true>
#endif
uint32_t SortInsertion(T* arr, int begin, int end, Func cmp) {
	uint32_t count = 0;

    // memcpy는 뒤의 메모리를 앞에다 붙여넣기 해야 하기 때문에 역순으로 비교한다.
	--end;	// -> arr[begin, end]
	for (int i = end - 1; i >= begin; --i) {
		++count;
		T temp = arr[i];
		// worst case (역순인 경우) 방지를 위해 정렬된 부분의 마지막 값과 비교
		if (cmp(arr[end], temp)) {
        	++count;
			memcpy(arr + i, arr + i + 1, sizeof(T) * (end - i));
			arr[end] = temp;
        	++count;
		} else {
        	++count;
			int j = i + 1;
			for (; j <= end && cmp(arr[j], temp); ++j)
				++count;
			if (--j == i)
				continue;

			memcpy(arr + i, arr + i + 1, sizeof(T) * (j - i));
			arr[j] = temp;
			++count;
		}
	}

	return count;
}
#if _HAS_CXX17
template <typename T, class Func, std::enable_if_t<!std::is_trivially_copyable_v<T>, bool> = true>
#else 
template <typename T, class Func, std::enable_if_t<!std::is_trivially_copyable<T>::value, bool> = true>
#endif
uint32_t SortInsertion(T* arr, int begin, int end, Func cmp) {
	uint32_t count = 0;

	for (int i = begin + 1; i < end; ++i) {
		T temp = arr[i];
		int j = i - 1;
		// worst case (역순인 경우) 방지용 첫번째 값과 비교
		if (cmp(temp, arr[begin])) {
			++count;
			for (; j >= begin; --j) {
				arr[j + 1] = arr[j];
				++count;
			}
			arr[end] = temp;
        	++count;
		} else {
			++count;
			for (; j >= begin && cmp(temp, arr[j]); --j) {
				arr[j + 1] = arr[j];
				++count;
			}
			arr[j + 1] = temp;
			++count;
		}
	}

	return count;
}


// arr[begin, end) (end <= length)
#if _HAS_CXX17
template <typename T, class Func, std::enable_if_t<std::is_trivially_copyable_v<T>, bool> = true>
#else 
template <typename T, class Func, std::enable_if_t<std::is_trivially_copyable<T>::value, bool> = true>
#endif
uint32_t SortInsertionBinary(T* arr, int begin, int end, Func cmp) {
	uint32_t count = 0;

	// 동일한 값일 경우 왼쪽 구역을 선택해서 탐색하는 이진 탐색
	// stable sort 특성을 지켜주기 위해 같은 값이 있으면 앞쪽 값을 선택한다. (삽입 시 앞의 값이 뒤로 가는 것을 방지)
	//! 앞쪽에서 뒤쪽으로 정렬하는 경우에는 for반복문 순서가 바뀌고, 같은 값일 경우 뒤쪽 값을 선택해야 한다.
	auto binarySearchLeft = [&count](T* arr, const T& value, int s, int e, Func cmp) -> int {
		int m;
		// binary search
		while (s < e) {		// [s, e)
			++count;
			m = (s + e) / 2;
			if (cmp(arr[m], value))
				s = m + 1;	// [m + 1, e)
			else
				e = m;		// [s, m)
			++count;
		}
		return e;
	};

	int index = 0;
    // memcpy는 뒤의 메모리를 앞에다 붙여넣기 해야 하기 때문에 역순으로 비교한다. (메모리를 앞으로 당겨오는 식)
	for (int i = end - 2; i >= begin; --i) {
		++count;
		T temp = arr[i];
		// binary search
		index = binarySearchLeft(arr, temp, i + 1, end, cmp);
		// insertion
		memcpy(arr + i, arr + i + 1, sizeof(T) * (index - 1 - i));
		arr[index - 1] = temp;
        ++count;
	}

	return count;
}
// arr[begin, end) (end <= length)
#if _HAS_CXX17
template <typename T, class Func, std::enable_if_t<!std::is_trivially_copyable_v<T>, bool> = true>
#else 
template <typename T, class Func, std::enable_if_t<!std::is_trivially_copyable<T>::value, bool> = true>
#endif
uint32_t SortInsertionBinary(T* arr, int begin, int end, Func cmp) {
	uint32_t count = 0;

	// 동일한 값일 경우 오른쪽 구역을 선택해서 탐색하는 이진 탐색 (일반적으로 사용됨)
	// stable sort 특성을 지켜주기 위해 같은 값이 있으면 뒤쪽 값을 선택한다. (삽입 시 뒤의 값이 앞으로 가는 것을 방지)
	//! 뒤쪽에서 앞쪽으로 정렬하는 경우에는 for반복문 순서가 바뀌고, 같은 값일 경우 앞쪽 값을 선택해야 한다.
	auto binarySearchRight = [&count](T* arr, const T& value, int s, int e, Func cmp) -> int {
		int m;
		// binary search
		while (s < e) {		// [s, e)
			++count;
			m = (s + e) / 2;
			if (cmp(value, arr[m]))
				e = m;		// [s, m)
			else
				s = m + 1;	// [m + 1, e)
			++count;
		}
		return e;
	};

	int e;
	for (int i = begin + 1; i < end; ++i) {
		T temp = arr[i];
		// binary search
		e = binarySearchRight(arr, temp, begin, i, cmp);
		// insertion
		for (int j = i - 1; j >= e; --j) {
			arr[j + 1] = arr[j];
			++count;
		}
		arr[e] = temp;
		++count;
	}

	return count;
}