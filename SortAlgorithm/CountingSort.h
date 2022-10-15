#pragma once

#include <memory.h>
#include <type_traits>

#include "Share.h"


// arr[begin, end) (end <= length)
#if _HAS_CXX17
template <class T, class Func, std::enable_if_t<std::is_integral_v<T>, bool> = true>
#else 
template <class T, class Func, std::enable_if_t<std::is_integral<T>::value, bool> = true>
#endif
uint32_t SortCounting(T* arr, int begin, int end, Func cmp) {
	uint32_t count = 0;

	// 최솟값, 최댓값 찾기
	int min = INT_MAX;
	int max = 0;
	for (int i = begin; i < end; ++i) {
		++count;
		if (arr[i] < min) 
			min = arr[i];
		if (arr[i] > max) 
			max = arr[i];
	}

	// 카운팅 배열 작성
	int length = max - min + 1;
	T* countArr = new T[length] {};
	//memset(countArr, 0, sizeof(T) * length);
	for (int i = begin; i < end; ++i)
		++countArr[arr[i] - min];
	count += (end - begin);


	// 누적 개수 배열 작성 -> 카피 배열의 인덱스로 사용
	for (int i = 1; i < length; ++i)
		countArr[i] += countArr[i - 1];
	count += length - 1;

	// 카피 배열 작성 -> 정렬의 안정성(stable)을 보장하기 위해 반복문을 거꾸로 진행
	T* temp = new T[end - begin] {};
	//memset(temp, 0, sizeof(T) * (end - begin));
	for (int i = end - 1; i >= begin; --i) {
		// 개수이기 때문에 인덱스로 사용하려면 -1 해준다.
		temp[--countArr[arr[i] - min]] = arr[i];
	}
	count += (end - begin);

	// 카피 배열 원본에 복사
	memcpy(&arr[begin], temp, sizeof(T) * (end - begin));
	++count;

	delete[] temp;
	delete[] countArr;

	return count;
}
#if _HAS_CXX17
template <class T, std::enable_if_t<std::is_integral_v<T>, bool> = true>
#else 
template <class T, std::enable_if_t<std::is_integral<T>::value, bool> = true>
#endif
uint32_t SortCounting(T* arr, int begin, int end) {
	return SortCounting(arr, begin, end, Ascend<>{});
}