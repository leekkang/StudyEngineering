
#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <chrono>
#include <cmath>        // log, log10
#include <iomanip>      // input output manipulation (std::setw,...)
#include <functional>   // std::function

#include "InsertionSort.h"
#include "Shell'sSort.h"
#include "MergeSort.h"
#include "QuickSort.h"
#include "HeapSort.h"
#include "CountingSort.h"

// arr[begin, end) (end <= length)
template <typename T, class Func>
uint32_t SortBubble(T* arr, const int begin, const int end, Func cmp) {
	uint32_t count = 0;
	for (int i = begin; i < end; ++i) {   // 반복문은 웬만하면 signed 자료형을 사용하자. unsigned는 버그가 발생할 가능성이 높다.
		for (int j = begin + 1; j < end - i; ++j) {
			if (cmp(arr[j], arr[j - 1])) {
				Swap(arr[j - 1], arr[j]);
				++count; 
			}
			++count;   // 전위연산자는 l-value, 후위연산자는 r-value를 리턴한다.
		}
	}

	return count;   // 자잘한 연산은 제외하고 주가되는 비교, 대입만 측정한다.
}
template <class T>
uint32_t SortBubble(T* arr, int begin, int end) {
	return SortBubble(arr, begin, end, Ascend<>{});
}

// arr[begin, end) (end <= length)
template <typename T, class Func>
uint32_t SortSelection(T* arr, const int begin, const int end, Func cmp) {
	uint32_t count = 0;
	for (int i = begin; i < end; ++i) {
		uint32_t index = i;
		for (int j = i + 1; j < end; ++j) {
			if (cmp(arr[j], arr[index]))
				index = j;
				
			++count;
		}

		if (i != index) {
			Swap(arr[i], arr[index]);
			++count;
		}
		++count;
	}

	return count;
}
template <class T>
uint32_t SortSelection(T* arr, int begin, int end) {
	return SortSelection(arr, begin, end, Ascend<>{});
}

// arr[begin, end) (end <= length)
template <typename T>
uint32_t SortRadix(T* arr, const size_t length) {
	uint32_t count = 0;
	int radix = 10;

	// 최대 자리수 찾기
	int maxRadix = 0;
	for (int i = 0; i < length; ++i) {
		++count;
		if (arr[i] > maxRadix) maxRadix = arr[i];
	}
	maxRadix = static_cast<int>(log10(static_cast<double>(maxRadix)) + 1);   // radix에 따라가도록 변경해야함.

	// 카운팅 배열
	std::vector<T> countArr(radix);

	int index, pval, i;
	for (int n = 0; n < maxRadix; ++n) {
		pval = static_cast<int>(pow(radix, n));

		// initialize
		countArr.assign(radix, 0);
		// for (int i = 0; i < radix; ++i) countArr[i] = 0;

		// counting sort 를 사용한다.
		for (i = 0; i < length; ++i) {
			++count;
			++countArr[static_cast<int>(arr[i] / pval) % radix];
		}
		// 누적 합 계산
		for (i = 1; i < radix; ++i) {
			++count;
			countArr[i] += countArr[i - 1];
		}

		// 카피 배열 작성
		std::vector<T> temp(length);
		for (i = length - 1; i >= 0; --i) {
			++count;
			index = static_cast<int>(arr[i] / pval) % radix;
			--countArr[index];
			temp[countArr[index]] = arr[i];
		}

		// 카피 배열 원본에 복사 (소팅 알고리즘에 포함되는 부분은 아님)
		for (i = 0; i < length; ++i) {
			++count;
			arr[i] = temp[i];
		}
	}

	return count;
}

// arr[begin, end) (end <= length)
template <typename T>
uint32_t SortBucket(T* arr, const size_t length) {
	uint32_t count = 0;
	int bucketNumber = 10;   // 생성되는 버킷의 개수

	// 최대값 찾기
	int max = 0;
	for (int i = 0; i < length; ++i) {
		++count;
		if (arr[i] > max) max = arr[i];
	}

	// 버킷 생성
	std::vector<std::vector<T>> buckets(bucketNumber);
	int value;
	for (int i = 0; i < length; ++i) {
		++count;
		// 소수점의 경우 std::floor를 추가로 사용한다.
		value = static_cast<int>(bucketNumber * arr[i] / max);
		buckets[(value < 0) ? 0 : (value < bucketNumber - 1) ? value
															 : bucketNumber - 1]
			.push_back(arr[i]);   // == std::clamp (#include<algorithm>)
	}

	// 삽입 정렬
	auto insertion = [&](T* bucket, const int& len) {
		for (int i = 1; i < len; ++i) {
			T temp = bucket[i];
			int j = i - 1;
			for (; j >= 0 && bucket[j] > temp; --j) {
				bucket[j + 1] = bucket[j];
				++count;
			}
			bucket[j + 1] = temp;
			++count;
		}
	};

	// 버킷 별 정렬 + 합치기
	int index = 0;
	for (int i = 0; i < bucketNumber; ++i) {
		size_t bucketLen = buckets[i].size();
		insertion(buckets[i].data(), bucketLen);

		for (int j = 0; j < bucketLen; ++j) {
			++count;
			arr[index++] = buckets[i][j];
		}
	}

	return count;
}

// arr[begin, end) (end <= length)
template <typename T>
uint32_t SortTim(T* arr, const size_t length) {
	uint32_t count = 0;

	// Run 스택. pair의 값은 (run 시작 인덱스, run 길이)를 의미한다.
	std::vector<std::pair<int, int>> stack;
	int stackIndex = -1;

	// Galloping Mode를 위한 상수값
	int minGallop = 3;

	// 동일한 값일 경우 오른쪽을 우선해서 탐색하는 이진 탐색 (일반적으로 사용됨)
	auto binarySearchRight
		= [&arr, &count](const T& value, const int& start, const int& end) -> int {
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

		// TODO : Galloping Mode 구현
		int gallopCount;
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
		insertionAscend(0, length);
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

// arr[begin, end) (end <= length)
template <typename T>
uint32_t SortIntro(T* arr, const size_t length) {
	uint32_t count = 0;

	// Heap Sort
	auto shiftdown = [&](int root, const int& end, const int& correction) {   // [root, end]
		// 자식 노드가 없으면 종료
		while (root * 2 < end) {
			++count;

			// 0번 index를 사용하기 위해 약간의 계산을 추가한다.
			int current = root;
			int left = (root + 1) * 2 - 1;
			int right = (root + 1) * 2;

			if (arr[left + correction] > arr[current + correction]) current = left;
			if (right <= end && arr[right + correction] > arr[current + correction]) current = right;

			// 이미 정렬된 노드면 종료
			if (current == root) {
				return;
			} else {
				Swap(arr[current + correction], arr[root + correction]);
				// std::swap<T>(arr[current + correction], arr[root + correction]);
				root = current;
			}
		}
	};
	auto heap = [&](const int& begin, const int& len) {
		// 부분 배열의 heap sort는 root 값을 0으로 맞추기 위해서 보정값을 사용한다.
		int correction = begin;
		int end = len - 1;

		// Build Heap (Heapify)
		for (int parent = end / 2; parent >= 0; --parent) {
			shiftdown(parent, end, correction);
		}

		while (end > 0) {
			++count;
			Swap(arr[end], arr[begin]);
			// std::swap<T>(arr[end], arr[0]);
			--end;
			shiftdown(0, end, correction);
		}
	};
	auto insertion = [&](const int& begin, const int& end) {
		T temp;
		for (int i = begin + 1; i < end; ++i) {
			temp = arr[i];
			int j = i - 1;
			for (; j >= 0 && arr[j] > temp; --j) {
				++count;
				arr[j + 1] = arr[j];
			}

			arr[j + 1] = temp;
			++count;
		}
	};

	// Quick Sort
	std::function<void(const int&, const int&, const int&)> quick = [&](const int& begin, const int& end, const int& depth) {
		// end 도 인덱스에 포함된다. -> arr[end] : o, arr[end-1] : o 	-> [begin, end]
		++count;
		if (end - begin + 1 < 16) {
			insertion(begin, end + 1);
			return;
		} else if (depth == 0) {
			heap(begin, end - begin + 1);   // length를 인자로 주어야 한다.
			return;
		}

		// divide
		int left = begin - 1;
		int pivot = end;
		for (int i = begin; i < end; ++i) {
			// 리스트 끝까지 순회하면서 피벗보다 작은 값들을 앞으로 옮긴다.
			if (arr[i] < arr[pivot]) {
				Swap(arr[++left], arr[i]);
				// std::swap(arr[++left], arr[i]);
			}
			++count;
		}
		Swap(arr[++left], arr[pivot]);
		// std::swap(arr[++left], arr[pivot]);
		++count;

		// depth = (depth >> 1) + (depth >> 2); // allow 1.5 log2(N) divisions
		//  conquer
		quick(begin, left - 1, depth - 1);
		quick(left + 1, end, depth - 1);
	};

	int maxDepth = 2 * log2(length);

	quick(0, length - 1, maxDepth);

	return count;
}

/// <summary> 대략적인 시간복잡도를 출력하는 함수 </summary>
void PrintComplexity(uint32_t count, uint32_t n) {
	std::cout << "\nLoop Count : " << count << ", Sorting Complexity (approximately) : ";
	if (count < n) {
		std::cout << "1 ~ N (1 ~ " << n << ")\n";
	} else if (count < n * log2(n)) {
		std::cout << "N ~ Nlog2_N (" << n << " ~ " << n * log2(n) << ")\n";
	} else if (count < n * n) {
		std::cout << "Nlog2_N ~ N^2 (" << n * log2(n) << " ~ " << n * n << ")\n";
	} else if (count < pow(2, n)) {
		std::cout << "N^2 ~ 2^N (" << n * n << " ~ " << pow(2, n) << ")\n";
	} else {
		std::cout << "2^N ~ N! (" << pow(2, n) << " ~)\n";
	}
}

using namespace std::chrono;

int main() {
	// reference : http://egloos.zum.com/sweeper/v/2996847
	////system_clock::time_point current = system_clock::now(); // 컴퓨터 시스템 시간. system_clock == high_resolution_clock
	// steady_clock::time_point current = steady_clock::now();   // 물리적 고정 시간
	// milliseconds millis
	//	= duration_cast<milliseconds>(current.time_since_epoch());
	// std::mt19937 generator(millis.count()); 				   // 메르센 트위스터 엔진 (64비트용 : std::mt19937_64)

	// reference : https://modoocode.com/304
	std::random_device device;          // 시드값 생성기 (속도 느림)
	std::mt19937 generator(device());   // 메르센 트위스터 엔진 (64비트용 : std::mt19937_64)

	std::uniform_int_distribution<int> distribution(1, 999);   // 난수 분포(균등 분포)와 범위

	size_t length{100};                       // Uniform Initialization (up to C++11)
	std::vector<int> unsortedArray(length);   // resize. not reserve


	constexpr bool bUseSorted = false;   	// 정렬된 배열을 사용
	constexpr bool bPrintArray = true;   	// 대상 배열 출력 여부
#define 		bSortAscend 	true		// true이면 오름차순, false이면 내림차순으로 출력

	if (bUseSorted) {
		// 정렬된 배열은 굳이 출력하지 않는다.
		int num = 1;
		for (auto& e : unsortedArray) {
			e = num++;
		}
	} else {
		if (bPrintArray)
			std::cout << "Unsorted Array\n";
		for (auto& e : unsortedArray) {
			e = distribution(generator);
			if (bPrintArray) {
				std::cout << std::setw(4) << e;
			}
		}
	}
	std::cout << std::endl;

#if bSortAscend
	using Compare = Ascend<>;
#else 
	using Compare = Descend<>;
#endif

	using funcPointer = uint32_t (*)(int*, int, int, Compare);
	std::vector<std::pair<std::string, void*>> sortPair {
		// {"Bubble", SortBubble<int, Compare>},
		// {"Selection", SortSelection<int, Compare>},
		// {"Insertion", SortInsertion<int, Compare>},
		// {"InsertionBinary", SortInsertionBinary<int, Compare>},
		// {"Shell", SortShell<int, Compare>},
		// {"MergeTop", SortMergeTopDown<int, Compare>},
		// {"MergeBottom", SortMergeBottomUp<int, Compare>},
		// {"Quick", SortQuick<int, Compare>},
		// {"QuickPartition", SortQuickPartition<int, Compare>},
		 {"Heap", SortHeap<int, Compare>},
		// {"HeapSTL", SortHeapFromSTL<int, Compare>},
		 {"Counting", SortCounting<int, Compare>},
		// {"Radix", SortRadix<int, Compare>},
		// {"Bucket", SortBucket<int, Compare>},
		// {"Tim", SortTim<int, Compare>},
		// {"Intro", SortIntro<int, Compare>},
	};

	steady_clock::time_point start;
	std::vector<int> sortedArray;

	for (const auto& pair : sortPair) {
		std::cout << "\n " << pair.first << " Sort Start\n";

		sortedArray = unsortedArray;   // deep copy

		start = steady_clock::now();
		uint32_t loopCount = ((funcPointer)pair.second)(sortedArray.data(), 30, (int)length, Compare{});
		PrintComplexity(loopCount, (uint32_t)length);
		std::cout << "Sorting Time : " << duration_cast<microseconds>(steady_clock::now() - start).count() << " us\n";

		if (bPrintArray) {
			std::cout << "\n " << pair.first << " Sort's Sorted Array\n";
			for (const auto& e : sortedArray) {
				std::cout << std::setw(4) << e;
			}
			std::cout << "\n";
		}

		std::cout << "\n " << pair.first << " Sort End\n" << std::endl;
	}
}