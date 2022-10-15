#pragma once

#include <memory.h>
#include <type_traits>
#include <vector>
#include <functional>
#include <random>

#include "Share.h"

//! 포함관계를 잘 확인하자

// mid의 배열값을 세 배열값의 중앙값으로 변경한다.
// arr[begin, end] (end < length)
template <typename T, class Func>
void SwapMedian3Index(T* arr, int begin, int mid, int end, Func cmp) {
    // sort median of three elements to middle
    if (cmp(arr[mid], arr[begin]))
		Swap(arr[mid], arr[begin]);

    if (cmp(arr[end], arr[mid])) { 	// swap middle and last, then test first again
		Swap(arr[end], arr[mid]);

		if (cmp(arr[mid], arr[begin]))	// mid 한번 더 체크
			Swap(arr[mid], arr[begin]);
    }
}

// arr[begin, end] (end < length)
template <typename T, class Func>
void GuessMedian(T* arr, int begin, int mid, int end, Func cmp) {
    // sort median element to middle
	const int count = end - begin;

	if (40 < count) { // Tukey'begin ninther
		// 각 인덱스에서 중간값을 찾은 후 그 인덱스들로 중간값을 한번 더 찾는다. (결과값은 mid 에 들어간다.)
        const int step = (count + 1) >> 3;  // +1 can't overflow because range was made inclusive in caller
        const int twoStep = step << 1; 		// note: intentionally discards low-order bit
        SwapMedian3Index(arr, begin, begin + step, begin + twoStep, cmp);
        SwapMedian3Index(arr, mid - step, mid, mid + step, cmp);
        SwapMedian3Index(arr, end - twoStep, end - step, end, cmp);

        SwapMedian3Index(arr, begin + step, mid, end - step, cmp);
    } else {
        SwapMedian3Index(arr, begin, mid, end, cmp);
    }
}

// algorithm 헤더에 있는 코드를 간략화한 것. 피벗값은 중앙값 사용, 3-way partitioning 기법 사용. 피벗 구역의 범위를 리턴한다.
// arr[begin, end) (end <= length)
template <typename T, class Func>
std::pair<int, int> PartitionWithGuessMedian(T* arr, int begin, int end, Func cmp, uint32_t* counter = nullptr) {
	uint32_t count = 0;

	// 피벗 생성 (median of 3)
    int mid = (begin + end) / 2;
	SwapMedian3Index(arr, begin, mid, end - 1, cmp);
	count += 3;

	// 3-way partitioning
	T pivot = arr[mid];		//! 피벗값을 따로 빼놓지 않으면 정렬이 제대로 안된다. 스왑할 때 위치가 바뀌는 경우가 있기 때문
	int pStart = begin;
	int pEnd = end - 1;
	for (int j = begin; j <= pEnd;) {
		++count;
		if (cmp(arr[j], pivot)) {			// j값이 피벗값보다 왼쪽값이다. -> pStart와 스왑, pStart 인덱스 증가
			++count;
			Swap(arr[pStart], arr[j]);
			++pStart;
			++j;
		} else if (cmp(pivot, arr[j])) {	// j값이 피벗값보다 오른쪽값이다. -> pEnd와 스왑, pEnd 인덱스 감소
			++count;
			Swap(arr[j], arr[pEnd]);
			--pEnd;
		} else {
			++count;
			++j;
		}
	}
	if (counter)
		*counter += count;

	return std::make_pair(pStart, pEnd + 1);
}

// algorithm 헤더에 있는 코드 거의 그대로 가져옴. 안정성을 위한 추가 처리 부분이 많아서 여기서 사용하진 않음. 그냥 참고용. 피벗 구역의 범위를 리턴한다.
// arr[begin, end) (end <= length)
template <typename T, class Func>
std::pair<int, int> PartitionWithGuessMedianFromSTL(T* arr, int begin, int end, Func cmp) {
	// 피벗 생성 (median of 3 + Tukey'begin ninther)
    int pivot = (begin + end) / 2;
    GuessMedian(arr, begin, pivot, end - 1, cmp);

	// 3-way partitioning : 피벗을 기준으로 중복값, 앞에 오는 값, 뒤에 오는 값 세 개의 구역으로 파티셔닝 하는 것
	// 중복 키가 많을 때 성능이 N^2가 되는 것을 방지한다.
	// 각 구역의 포함관계는 [start, end) 이다.
    int pStart = pivot;
    int pEnd  = pStart + 1;

	// 현재 피벗값 좌우에 있는 중복되는 값들을 찾아낸다.
	// 비교 함수에 equal 이 포함되어 있으면 해당 while문은 그냥 지나간다.
	// ex) cmp가 less 인 경우 : arr[pStart - 1] >= arr[pStart] && arr[pStart] >= arr[pStart - 1]    ->    arr[pStart] == arr[pStart - 1]
    while (begin < pStart && !cmp(arr[pStart - 1], arr[pStart]) && !cmp(arr[pStart], arr[pStart - 1]))
        --pStart;
    while (pEnd < end && !cmp(arr[pEnd], arr[pStart]) && !cmp(arr[pStart], arr[pEnd])) {
        ++pEnd;
    }

    int left  = pStart;
	int right = pEnd;

	// 현재 인덱스들 위치 관계 : begin < left == pStart == pivot < pEnd == right < end
	
	// 구역을 나눈다.
    for (;;) {
		// 오른쪽 구역에 존재하는 좌측 값 찾기
        for (; right < end; ++right) {
            if (cmp(arr[pStart], arr[right]))	// right가 우측값임
                continue;
			if (cmp(arr[right], arr[pStart])) {	// right가 우측값이 아님 (스왑 대상)
                break;
            } else if (pEnd != right) {			// 피벗값과 right의 값이 같고 위치가 멀다 -> pEnd의 위치를 right와 교환
                Swap(arr[pEnd], arr[right]);
                ++pEnd;
            } else {
                ++pEnd;
            }
        }
		// 왼쪽 구역에 존재하는 우측 값 찾기
        for (; begin < left; --left) {
            if (cmp(arr[left - 1], arr[pStart]))			// left 좌측값임
                continue;
            if (cmp(arr[pStart], arr[left - 1])) {		// left 좌측값이 아님 (스왑 대상)
                break;
			} else if (--pStart != left - 1) {  // 피벗값과 left의 값이 같고 위치가 멀다 -> pStart의 위치를 left와 교환
				Swap(arr[pStart], arr[left - 1]);
			}
		}

        if (begin == left && right == end) {	// 피벗값 중복 구역 확정
            return std::pair<int, int>(pStart, pEnd);
        }

		// 왼쪽 구역에 값이 없다 == 피벗이 왼쪽으로 치우쳤다. -> 피벗 위치를 오른쪽으로 한 칸씩 밀어낸다.
		// 현재 왼쪽에 넘겨야 하는 right 값과 피벗 구역 시작위치 값을 교환한다.
        if (left == begin) {
			// right가 피벗 구역과 떨어져 있으면 피벗 구역 다음 값(피벗값보다는 큰)을 임시로 왼쪽으로 넘긴 후 right 값과 교환한다.
			// 피벗 구역의 가장 왼쪽 값이 오른쪽으로 이동한다. (unstable)
            if (pEnd != right)
                Swap(arr[pStart], arr[pEnd]);

            ++pEnd;
            Swap(arr[pStart], arr[right]);
            ++pStart;
            ++right;
        }
		// 오른쪽 구역에 값이 없다 == 피벗이 오른쪽으로 치우쳤다. -> 피벗 위치를 왼쪽으로 한 칸씩 밀어낸다.
		// 현재 오른쪽에 넘겨야 하는 left 값과 피벗 구역 끝위치 값을 교환한다. 
		else if (right == end) {
			// left가 피벗 구역과 떨어져 있으면 피벗 구역 이전 값(피벗값보다는 작은)과 임시로 교환한 후 피벗 구역 끝 값과 교환한다. 
			// 피벗 구역의 가장 오른쪽 값이 왼쪽으로 이동한다. (unstable)
            if (--left != --pStart)	
                Swap(arr[left], arr[pStart]);

            Swap(arr[pStart], arr[--pEnd]);
        } 
		// 양쪽 구역에 교환 대상이 존재한다 -> 스왑 후 인덱스 변경
		else {	
            Swap(arr[right], arr[--left]);
            ++right;
        }
    }
}


// 피벗값으로 중앙값 사용, 3-way partitioning 기법으로 중복값 정렬 시 성능이 보장되는 함수
// arr[begin, end) (end <= length)
template <typename T, class Func>
uint32_t SortQuickPartition(T* arr, int begin, int end, Func cmp) {
	uint32_t count = 0;

	while (end - begin >= 2) {
		++count;
		// divide
		auto pair = PartitionWithGuessMedian(arr, begin, end, cmp);

		// conquer
		if (pair.first - begin < end - pair.second) {   // 피벗 오른쪽 구역 정렬
			count += SortQuickPartition(arr, begin, pair.first, cmp);
			begin = pair.second;
		} else {   // 피벗 왼쪽 구역 정렬
			count += SortQuickPartition(arr, pair.second, end, cmp);
			end = pair.first;
		}
		++count;
	}

	return count;
}
template <typename T>
uint32_t SortQuickPartition(T* arr, int begin, int end) {
	return SortQuickPartition(arr, begin, end, Ascend<>{});
}


// 피벗값으로 중앙값 사용, 인덱스 2개 사용, 재귀 호출
// arr[begin, end) (end <= length)
template <typename T, class Func>
uint32_t SortQuick(T* arr, int begin, int end, Func cmp) {
	if (end - begin < 2)
		return 0;

	uint32_t count = 0;
	// devide
    int mid = (begin + end) / 2;
	SwapMedian3Index(arr, begin, mid, end - 1, cmp);
	count += 3;

	T pivot = arr[mid];	//! 인덱스 1개와는 다르게 피벗값을 따로 빼놓지 않으면 정렬이 제대로 안된다. 스왑할 때 위치가 바뀌는 경우가 있기 때문
	int left = begin;
	int right = end - 1;
	for (; left <= right;) {
		while(cmp(arr[left], pivot)) { // left값이 피벗값보다 왼쪽 값인 경우에만 인덱스 상승
			++count;
			++left;
		}
		while(cmp(pivot, arr[right])) { // right값이 피벗값보다 오른쪽 값인 경우에만 인덱스 감소
			++count;
			--right;
		}

		if (left <= right) {
			++count;
			Swap(arr[left], arr[right]);
			++left;
			--right;
		}
	}

	// conquer
	count += SortQuick(arr, begin, right + 1, cmp);
	count += SortQuick(arr, left, end, cmp);

	return count;
}
template <typename T>
uint32_t SortQuick(T* arr, int begin, int end) {
	return SortQuick(arr, begin, end, Ascend<>{});
}


// 인덱스 1개 사용, 피벗값을 가장 오른쪽 값으로 결정
// arr[begin, end) (end <= length)
template <typename T, class Func>
uint32_t SortQuickSinglePivot(T* arr, int begin, int end, Func cmp) {
	if (end - begin < 2)
		return 0;

	uint32_t count = 0;

	// divide
	int left = begin - 1;
	int pivot = end - 1;   // pivot 을 오른쪽 끝으로 잡는다.
	for (int i = begin; i < end - 1; ++i) {
		// 리스트 끝까지 순회하면서 피벗보다 작은 값들을 앞으로 옮긴다.
		++count;
		if (cmp(arr[i], arr[pivot]))
			Swap(arr[++left], arr[i]);
	}
	Swap(arr[++left], arr[pivot]);
	++count;

	// conquer
	count += SortQuickSinglePivot(arr, begin, left, cmp);
	count += SortQuickSinglePivot(arr, left + 1, end, cmp);

	return count;
}
template <typename T>
uint32_t SortQuickSinglePivot(T* arr, int begin, int end) {
	return SortQuickSinglePivot(arr, begin, end, Ascend<>{});
}