#pragma once

//#include <utility> // std::pair
#include <vector>
#include "InsertionSort.h"


// arr[begin, end) (end <= length)
template <typename T>
uint32_t SortTim(T* arr, int begin, int end) {
	return SortTim(arr, begin, end, Ascend<>{});
}

// arr[begin, end) (end <= length)
template <typename T, class Func>
uint32_t SortTim(T* arr, int begin, int end, Func cmp) {
	uint32_t count = 0;

	// Run 스택. pair의 값은 [run 시작 인덱스, run 끝 인덱스)를 의미한다.
	std::vector<std::pair<int, int>> stack;
	int stackTop = -1;

	// 데이터 개수가 너무 적은 경우 전체 배열에 대해 binary insertion sort를 사용한다.
	if (end - begin < 64) { // 2^6
		return SortInsertionBinary(arr, begin, end, cmp);
	}

	// computing MinRun (복잡하기 때문에 32로 고정한다.)
	// 참고 : https://hg.python.org/cpython/file/tip/Objects/listsort.txt
	int minRun = 32;   // 2의 제곱수. 2^5 ~ 2^6 사이의 값에서 유동적으로 잡는다.

	bool ascend = std::is_same<Func, Ascend<>>::value;
	int runStart, runEnd = begin;
	while (runEnd < end) {
		// Run 을 생성한다.
		runStart = runEnd;
		runEnd = runStart + minRun;
		if (runEnd > end)
			runEnd = end;

		// Run을 이진 삽입 정렬로 정렬한다. 같은 값은 순차로 정렬할 때 포함시킨다. 역순엔 포함되지 않음
		if (cmp(arr[runStart + 1], arr[runStart])) {
			// 역순
			if (ascend)
				count += SortInsertionBinary<T, Descend<>>(arr, runStart, runEnd, Descend<>{});
			else
				count += SortInsertionBinary<T, Ascend<>>(arr, runStart, runEnd, Ascend<>{});
				
			// 다음 값이 역으로 정렬되어 있을 때 현재 run에 포함한다.
			while (runEnd < end && cmp(arr[runEnd], arr[runEnd - 1])) {
				++runEnd;
			}
			// run이 되도록 뒤집는다.
			//? minRun 생성 시 역순인데 같은 값이 포함되어 있으면 스왑시 stable이 성립하지 않을텐데? 어떻게 처리하지??
			int left = runStart, right = runEnd - 1;
			while (left < right) {
				Swap(arr[left++], arr[right--]);
				++count;
			}
		} else {
			// 순차
			count += SortInsertionBinary(arr, runStart, runEnd, cmp);
			// 다음 값이 같거나 순차 정렬되어 있을 때 현재 run에 포함한다.
			while (runEnd < end && !cmp(arr[runEnd], arr[runEnd - 1])) {
				++runEnd;
			}
		}
		count += runEnd - runStart;

		// 스택에 넣는다
		if (stack.size() == stackTop + 1)
			stack.emplace_back(runStart, runEnd);
		else
			stack[stackTop + 1] = {runStart, runEnd};
		++stackTop;

	// Merge 검사를 한다 -> 스택의 구조 : 바텀에서 탑 방향으로 Z, Y, X 순서. Z가 가장 크고 X가 가장 작다
	// goto 구문이 보기 싫으면 for(;;) 또는 while(true) 문으로 교체할 수 있다.
	CHECK_MERGE:
		// 1st rule : Z > X + Y
		// 스택에 런이 3개 이상 있고 Z가 X + Y 보다 작은 경우 => Y, Z 병합
		if (stackTop > 1 && 
			stack[stackTop - 2].second <= (stack[stackTop].second + stack[stackTop - 1].second)) {
			
			// Z 시작, Y 시작, Y 끝 인덱스를 인자로 넘긴다.
			count += MergeProcess(arr, stack[stackTop - 2], stack[stackTop - 1], cmp);
			// run의 범위를 수정한다.
			stack[stackTop - 2].second = stack[stackTop - 1].second;
			// X를 Y 자리로 옮긴다. (바텀쪽으로 한 칸 내린다.)
			stack[stackTop - 1] = stack[stackTop];
			--stackTop;

			goto CHECK_MERGE;
		}

		// 2nd rule : Y > X
		// 스택에 새로 들어온 X 가 Y 보다 큰 경우 => X, Y 병합
		if (stackTop > 0 && stack[stackTop - 1].second <= stack[stackTop].second) {
			// Y 시작, X 시작, X 끝 인덱스를 인자로 넘긴다.
			count += MergeProcess(arr, stack[stackTop - 1], stack[stackTop], cmp);
			// run의 범위를 수정한다.
			stack[stackTop - 1].second = stack[stackTop].second;
			--stackTop;

			goto CHECK_MERGE;
		}

	}

	// 스택에 값이 남아있으면 머지한다.
	while (stackTop > 0) {
		count += MergeProcess(arr, stack[stackTop - 1], stack[stackTop], cmp);
		stack[stackTop - 1].second = stack[stackTop].second;

		--stackTop;
	}

	return count;
}

template <typename T, class Func>
uint32_t MergeProcess (T* arr, const std::pair<int, int>& left, const std::pair<int, int>& right, Func cmp) {
	// 병합이 필요하지 않은 경우 (이미 정렬된 경우) -> 앞쪽 run의 끝 값과 뒤쪽 run의 처음 값이 순차 정렬인 경우 (같을 경우도 포함)
	if (!cmp(arr[right.first], arr[left.second - 1]))
		return 1;

	uint32_t count = 1;

	// 동일한 값일 경우 오른쪽을 우선해서 탐색하는 이진 탐색 (일반적으로 사용됨)
	auto binarySearchRight = [&](const T& value, const int& start, const int& end) -> int {
		int s = start, e = end, m;
		// binary search
		while (s < e) {
			++count;
			m = (s + e) / 2;
			if (cmp(value, arr[m]))
				e = m;
			else
				s = m + 1;
		}
		return e;
	};
	// 동일한 값일 경우 왼쪽을 우선해서 탐색하는 이진 탐색 (왼쪽에 값을 넣고 싶을 때 사용됨)
	auto binarySearchLeft = [&](const T& value, const int& start, const int& end) -> int {
		int s = start, e = end, m;
		// binary search
		while (s < e) {
			++count;
			m = (s + e) / 2;
			if (!cmp(arr[m], value))
				e = m;
			else
				s = m + 1;
		}
		return e;
	};


	// Galloping Mode를 위한 상수값
	//! 미구현
	int minGallop = 3;

	int mergeBegin = left.first;
	int mergeEnd = right.second;

	// 정렬이 필요없는 부분을 제외한다. (병합이 필요한 연속 영역 체크)
	// 앞쪽 run 값 중 뒤쪽 run의 처음 값과 순차 정렬이 안되는 지점, (mergeBegin)
	// 뒷쪽 run 값 중 앞쪽 run의 끝 값과 순차 정렬이 안되는 지점 (mergeEnd) 을 찾는다.
	int i = 1;
	while (mergeBegin < left.second && cmp(arr[mergeBegin], arr[left.second])) {
		// 2의 거듭제곱을 체크해서 전체 범위 대신 좀 더 좁은 범위를 이진 탐색하도록 만든다.
		mergeBegin += i;
		i *= 2;
		++count;
	}
	// 왼쪽 런의 중간 부분 ~ 왼쪽 런 끝까지 검색
	mergeBegin = binarySearchRight(arr[left.second], 
									mergeBegin - i / 2,
									mergeBegin < left.second ? mergeBegin : left.second);

	i = 1;
	while (left.second <= mergeEnd && !cmp(arr[mergeEnd - i], arr[left.second - 1])) {
		mergeEnd -= i;
		i *= 2;
		++count;
	}
	// 오른쪽 런의 중간 부분 ~ 오른쪽 런 끝까지 검색
	mergeEnd = binarySearchLeft(arr[left.second - 1], 
								(mergeEnd - i) > left.second ? (mergeEnd - i) : left.second, 
								 mergeEnd);


	T* arrTemp;
	// Merge Low (왼쪽 run의 길이가 더 짧다)
	if ((left.second - left.first) <= (right.second - left.second)) {
		// 임시 저장 영역 :			  여기
		// left.first-----mergeStart-----left.second-----------mergeEnd-----------right.second
		//				    		왼쪽런			   오른쪽런

		// 왼쪽 런의 중간 부분 ~ 왼쪽 런 끝까지를 임시 저장한다.
		arrTemp = new T[left.second - mergeBegin];
		memcpy(arrTemp, &arr[mergeBegin], sizeof(T) * (left.second - mergeBegin));

		int l = left.first;
		int r = left.second;
		int index = mergeBegin;
		while (index < mergeEnd) {
			// 왼쪽 런이 끝나지 않은 상황에서, 오른쪽 런이 끝났거나 임시 저장한 왼쪽의 값이 오른쪽 값보다 작을 경우
			if (l < left.second && (r >= mergeEnd || !cmp(arr[r], arrTemp[l - left.first])))
				arr[index] = arrTemp[l++ - left.first];
			else
				arr[index] = arr[r++];

			++count;
			++count;
			++index;
		}
	} 
	// Merge High (오른쪽 run의 길이가 더 짧다)
	else {
		// 임시 저장 영역 :								 		여기
		// left.first----------mergeStart----------left.second------mergeEnd-----right.second
		//								   왼쪽런		      오른쪽런

		// 오른쪽 런의 시작 부분 ~ 오른쪽 런 중간 부분 까지를 임시 저장한다.
		arrTemp = new T[mergeEnd - left.second];
		memcpy(arrTemp, &arr[left.second], sizeof(T) * (mergeEnd - left.second));

		int l = left.second - 1;
		int r = mergeEnd - 1;
		int index = mergeEnd - 1;
		while (index >= mergeBegin) { // 오른쪽에서 왼쪽으로 서치
			// 오른쪽 런이 끝나지 않은 상황에서, 왼쪽 런이 끝났거나 임시 저장한 오른쪽의 값이 왼쪽 값보다 클 경우
			if (r >= left.second && (l < mergeBegin || !cmp(arrTemp[r - left.second], arr[l])))
				arr[index] = arrTemp[(r-- - left.second)];
			else
				arr[index] = arr[l--];

			++count;
			++count;
			--index;
		}
	}

	delete[] arrTemp;

	return count;
}