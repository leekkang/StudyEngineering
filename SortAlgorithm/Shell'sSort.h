#pragma once

#include "Share.h"

// arr[begin, end) (end <= length)
template <typename T, class Func>
uint32_t SortShell(T* arr, int begin, int end, Func cmp) {
	uint32_t count = 0;

	auto insertionSort = [&arr, &cmp, &count](const int& begin, const int& end, const int& gap) {
		for (int i = begin + gap; i < end; i += gap) {
			++count;
			T temp = arr[i];
			int j = i - gap;
			for (; j >= begin && cmp(temp, arr[j]); j -= gap) {
				arr[j + gap] = arr[j];
				++count;
			}
			arr[j + gap] = temp;
			++count;
		}
	};

	for (int gap = static_cast<int>((end - begin) / 2); gap > 0; gap /= 2) {
		if (gap % 2 == 0) ++gap;   // 간격이 홀수이면 더 빠르다.

		for (int i = 0; i < gap; ++i) {
			insertionSort(begin + i, end, gap);
		}
	}

	return count;
}

template <class T>
uint32_t SortShell(T* arr, int begin, int end) {
	return SortShell(arr, begin, end, Ascend<>{});
}