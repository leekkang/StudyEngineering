#pragma once

#include "InsertionSort.h"


// arr[begin, end) (end <= length)
template <typename T>
uint32_t SortBucket(T* arr, int begin, int end) {
	return SortBucket(arr, begin, end, Ascend<>{});
}
// arr[begin, end) (end <= length)
template <typename T, class Func>
uint32_t SortBucket(T* arr, int begin, int end, Func cmp) {
	return SortBucket<10>(arr, begin, end, cmp);
}

// arr[begin, end) (end <= length)
#if _HAS_CXX17
template <int bucketCount, class T, class Func, std::enable_if_t<std::is_integral_v<T>, bool> = true>
#else 
template <int bucketCount, class T, class Func, std::enable_if_t<std::is_integral<T>::value, bool> = true>
#endif
uint32_t SortBucket(T* arr, int begin, int end, Func cmp) {
	uint32_t count = 0;

	// 최대값 찾기
	int max = 0;
	for (int i = begin; i < end; ++i) {
		if (arr[i] > max) 
			max = arr[i];
	}
	count += (end - begin);

	// 버킷 생성
	// divide
	int* arrIndex = new int[bucketCount] {0};
	T** buckets = new T* [bucketCount] {};
	for (int i = 0; i < bucketCount; ++i) {
		T* bin = new T[end - begin];
		buckets[i] = bin;
	}
	count += bucketCount;

	int value = 0;
	for (int i = begin; i < end; ++i) {
		// 소수점의 경우 std::floor를 추가로 사용한다.
		value = static_cast<int>(bucketCount * arr[i] / max);
		// value가 범위를 벗어나는 경우는 거의 없지만 혹시나 체크해준다.
		// == std::clamp (#include<algorithm>)
		value = (value < 0) ? 0 : (value < bucketCount - 1) ? value
															: bucketCount - 1;
		buckets[value][arrIndex[value]] = arr[i];
		++arrIndex[value];
	}
	count += (end - begin);

	// 버킷 별 정렬 + 합치기
	int index = begin;
	for (int i = 0; i < bucketCount; ++i) {
		// 삽입정렬을 사용한다.
		count += SortInsertion(buckets[i], 0, arrIndex[i], cmp);

		// conquer
		for (int j = 0; j < arrIndex[i]; ++j)
			arr[index++] = buckets[i][j];
		count += arrIndex[i];
	}

	for (int i = 0; i < bucketCount; ++i)
		delete[] buckets[i];
	delete[] buckets;
	delete[] arrIndex;

	return count;
}