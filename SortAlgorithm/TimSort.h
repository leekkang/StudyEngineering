#pragma once

#include "InsertionSort.h"

// arr[begin, end) (end <= length)
template <typename T, class Func>
uint32_t SortTim(T* arr, int begin, int end, Func cmp) {
	uint32_t count = 0;

	// Run 스택. pair의 값은 (run 시작 인덱스, run 길이)를 의미한다.
	std::vector<std::pair<int, int>> stack;
	int stackIndex = -1;

	// Galloping Mode를 위한 상수값
	//! 미구현
	int minGallop = 3;

	// 동일한 값일 경우 오른쪽을 우선해서 탐색하는 이진 탐색 (일반적으로 사용됨)
	auto binarySearchRight = [&arr, &count](const T& value, const int& start, const int& end) -> int {
		int s = start, e = end, m;
		// binary search
		while (s < e) {
			++count;
			m = (s + e) / 2;
			if (arr[m] > value)
				e = m;
			else
				s = m + 1;
		}
		return e;
	};
	// 동일한 값일 경우 왼쪽을 우선해서 탐색하는 이진 탐색 (왼쪽에 값을 넣고 싶을 때 사용됨)
	auto binarySearchLeft = [&arr, &count](const T& value, const int& start, const int& end) -> int {
		int s = start, e = end, m;
		// binary search
		while (s < e) {
			++count;
			m = (s + e) / 2;
			if (arr[m] >= value)
				e = m;
			else
				s = m + 1;
		}
		return e;
	};

	// 이진 삽입 정렬
	auto insertionAscend = [&](const int& start, const int& end) {   // [start, end) (start는 포함, end는 미포함)
		int e;
		for (int i = start + 1; i < end; ++i) {
			T temp = arr[i];
			// binary search
			e = binarySearchRight(temp, start, i);
			// insertion
			for (int j = i - 1; j >= e; --j) {
				arr[j + 1] = arr[j];
				++count;
			}
			arr[e] = temp;
			++count;
		}
	};
	auto insertionDescend = [&](const int& start, const int& end) {   // [start, end) (start는 포함, end는 미포함)
		int s, e, m;
		for (int i = start + 1; i < end; ++i) {
			T temp = arr[i];
			s = start;
			e = i;
			// binary search (내림차순) (stable하다.)
			while (s < e) {
				++count;
				m = (s + e) / 2;
				if (arr[m] < temp)
					e = m;
				else
					s = m + 1;
			}
			// insertion
			for (int j = i - 1; j >= e; --j) {
				arr[j + 1] = arr[j];
				++count;
			}
			arr[e] = temp;
			++count;
		}
	};

	// 병합 프로세스
	auto mergeProcess = [&](std::pair<int, int>& run, const int& start, const int& middle, const int& end) {
		// 병합이 필요하지 않은 경우 -> 앞쪽 run의 맨 뒤 값이 뒤쪽 run의 선두 값보다 작다.
		if (arr[middle - 1] <= arr[middle])
			return;

		std::vector<int> tempArr;
		int leftStart = start, rightEnd = end;

		// 병합이 필요한 연속영역 체크 -> 앞쪽 run 중 뒷쪽 run의 선두보다 적은 것, 뒷쪽 run의 뒷 요소 중 앞쪽 run의 맨 뒤 요소보다 큰 것
		// 2의 거듭제곱을 체크해서 전체 범위 대신 좀 더 좁은 범위를 이진 탐색하도록 만든다.
		int i = 1;
		while (leftStart < middle && arr[leftStart] < arr[middle]) {
			leftStart += i;
			i *= 2;
			++count;
		}
		leftStart = binarySearchRight(arr[middle], leftStart - i / 2, leftStart < middle ? leftStart : middle);

		i = 1;
		while (rightEnd >= middle && arr[rightEnd - i] >= arr[middle - 1]) {
			rightEnd -= i;
			i *= 2;
			++count;
		}
		rightEnd = binarySearchLeft(arr[middle - 1], (rightEnd - i) > middle ? (rightEnd - i) : middle, rightEnd);

		// Merge Low (앞쪽 run의 길이가 더 짧다)
		if ((middle - start) <= (end - middle)) {
			tempArr.assign(&arr[leftStart], &arr[leftStart] + (middle - leftStart));
			int left = 0;
			int right = middle;
			int tempMid = (middle - leftStart);
			int index = leftStart;
			while (index < rightEnd) {
				// 왼쪽 리스트가 끝나지 않은 상황에서, 오른쪽 리스트가 끝났거나 왼쪽의 값이 오른쪽 값보다 작을 경우
				if (left < tempMid && (right >= rightEnd || tempArr[left] <= arr[right])) {
					arr[index] = tempArr[left++];
				} else {
					arr[index] = arr[right++];
				}

				++count;
				++index;
			}
		} else {
			// Merge High (뒷쪽 run의 길이가 더 짧다)
			tempArr.assign(&arr[middle], &arr[middle] + (rightEnd - middle));
			int left = middle - 1;
			int right = rightEnd - middle - 1;
			int index = rightEnd - 1;
			while (index >= leftStart) {
				// 오른쪽 리스트가 끝나지 않은 상황에서, 왼쪽 리스트가 끝났거나 오른쪽의 값이 왼쪽 값보다 클 경우
				if (right >= 0 && (left < leftStart || arr[left] <= tempArr[right])) {
					arr[index] = tempArr[right--];
				} else {
					arr[index] = arr[left--];
				}

				++count;
				--index;
			}
		}

		// run 길이 변경
		run.second = end - start;
	};

	// 데이터 개수가 너무 적은 경우 전체 배열에 대해 binary insertion sort를 사용한다.
	if (length < 64) {
		SortInsertionBinary(arr, begin, end, cmp);
		return count;
	}

	// computing MinRun (복잡하기 때문에 32로 고정한다.)
	// 참고 : https://hg.python.org/cpython/file/tip/Objects/listsort.txt
	int minRun = 32;   // 2의 제곱수. 2^5 ~ 2^6 사이의 값에서 유동적으로 잡는다.

	int startIndex, endIndex = 0;
	do {
		// Run 을 생성한다.
		startIndex = endIndex;
		endIndex = (startIndex + minRun) > length ? length : (startIndex + minRun);

		// Run을 이진 삽입 정렬로 정렬한다.
		if (arr[startIndex + 1] >= arr[startIndex]) {
			// ascending
			insertionAscend(startIndex, endIndex);
			while (endIndex < length && arr[endIndex] >= arr[endIndex - 1]) {
				++endIndex;
				++count;
			}
		} else {
			insertionDescend(startIndex, endIndex);
			while (endIndex < length && arr[endIndex] < arr[endIndex - 1]) {
				++endIndex;
				++count;
			}
			// 증가하는 run이 되도록 뒤집는다.
			int left = startIndex, right = endIndex - 1;
			while (left < right) {
				Swap(arr[left++], arr[right--]);
				// std::swap(arr[left++], arr[right--]);
				++count;
			}
		}

		// 스택에 넣는다.
		if (stack.size() == stackIndex + 1) {
			stack.emplace_back(startIndex, endIndex - startIndex);
		} else {
			// stack[stackIndex].first = startIndex;
			// stack[stackIndex].second = endIndex - startIndex;
			stack[stackIndex + 1] = {startIndex, endIndex - startIndex};
		}
		++stackIndex;

	// Merge 검사를 한다.
	CHECK_MERGE:
		// 1st rule : Z > X + Y
		if (stackIndex > 1 && stack[stackIndex - 2].second <= (stack[stackIndex].second + stack[stackIndex - 1].second)) {
			// Z > X 인 경우 => X, Y 병합
			if (stack[stackIndex - 2].second > stack[stackIndex].second) {
				mergeProcess(stack[stackIndex - 1], stack[stackIndex - 1].first,
							 stack[stackIndex].first, stack[stackIndex].first + stack[stackIndex].second);
			} else {   // Z < X 인 경우 => Y, Z 병합
				mergeProcess(stack[stackIndex - 2], stack[stackIndex - 2].first,
							 stack[stackIndex - 1].first, stack[stackIndex - 1].first + stack[stackIndex - 1].second);
				// X를 Y 자리로 옮긴다.
				stack[stackIndex - 1] = stack[stackIndex];
			}

			--stackIndex;
			goto CHECK_MERGE;
		}

		// 2nd rule : Y > X
		if (stackIndex > 0 && stack[stackIndex - 1].second <= stack[stackIndex].second) {
			mergeProcess(stack[stackIndex - 1], stack[stackIndex - 1].first,
						 stack[stackIndex].first, stack[stackIndex].first + stack[stackIndex].second);
			--stackIndex;
			goto CHECK_MERGE;
		}

	} while (endIndex < length);

	// 스택에 값이 남아있으면 머지한다.
	while (stackIndex > 0) {
		mergeProcess(stack[stackIndex - 1], stack[stackIndex - 1].first,
					 stack[stackIndex].first, stack[stackIndex].first + stack[stackIndex].second);
		--stackIndex;
	}

	return count;
}