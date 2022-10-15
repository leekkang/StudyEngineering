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
uint32_t SortRadix(T* arr, int begin, int end, Func cmp) {
	uint32_t count = 0;
	// 현재 기수법의 자리수 개수. 기본 10진법
	int radix = 10;

	// 최대 자리수 찾기
	int max = 0;
	for (int i = begin; i < end; ++i) {
		if (arr[i] > max) 
			max = arr[i];
	}
	count += (end - begin);
	int maxRadix = 0;
	while (max > 0) {
		++maxRadix;
		max /= radix;
	}
	count += maxRadix;

	// 카운팅 배열, 카피 배열
	T* countArr = new T[radix] {};
	T* temp = new T[end - begin] {};

	int pval = 1;
	for (int n = 0; n < maxRadix; ++n) {
		// initialize
		memset(countArr, 0, sizeof(T) * radix);

		// 각 기수 별 자리수를 이용해 counting sort 를 진행한다.
		for (int i = begin; i < end; ++i)
			++countArr[static_cast<int>(arr[i] / pval) % radix];
		count += (end - begin);

		// 누적 합 계산
		for (int i = 1; i < radix; ++i)
			countArr[i] += countArr[i - 1];
		count += radix - 1;

		// 카피 배열 작성 -> 정렬의 안정성(stable)을 보장하기 위해 반복문을 거꾸로 진행
		for (int i = end - 1; i >= begin; --i) {
			int index = static_cast<int>(arr[i] / pval) % radix;
			// 개수이기 때문에 인덱스로 사용하려면 -1 해준다.
			temp[--countArr[index]] = arr[i];
		}
		count += (end - begin);

		// 카피 배열 원본에 복사
		memcpy(&arr[begin], temp, sizeof(T) * (end - begin));
		++count;

		// 기수 자리 증가
		pval *= radix;
	}
	
	delete[] temp;
	delete[] countArr;

	return count;
}
#if _HAS_CXX17
template <class T, std::enable_if_t<std::is_integral_v<T>, bool> = true>
#else 
template <class T, std::enable_if_t<std::is_integral<T>::value, bool> = true>
#endif
uint32_t SortRadix(T* arr, int begin, int end) {
	return SortRadix(arr, begin, end, Ascend<>{});
}