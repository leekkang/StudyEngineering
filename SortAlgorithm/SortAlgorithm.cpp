
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
#include "RadixSort.h"
#include "BucketSort.h"
#include "TimSort.h"

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
		// {"Heap", SortHeap<int, Compare>},
		// {"HeapSTL", SortHeapFromSTL<int, Compare>},
		// {"Counting", SortCounting<int, Compare>},
		// {"Radix", SortRadix<int, Compare>},
		// {"Bucket", SortBucket<int, Compare>},
		 {"Tim", SortTim<int, Compare>},
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