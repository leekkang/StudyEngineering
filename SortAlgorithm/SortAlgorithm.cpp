#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <chrono>
#include <cmath>	// log, log10
#include <iomanip>	// input output manipulation (std::setw,...)

template <typename T>   // template<class T> 와 동일
void Swap(T& left, T& right) {
	T tmp = left;
	left = right;
	right = tmp;
}

template <typename T>
uint64_t SortBubble(T* arr, size_t length) {	// T& 를 어떻게 쓰지..?
	uint64_t count = 0;

	for (int i = 0; i < length; ++i) {	// 반복문은 웬만하면 signed 자료형을 사용하자. unsigned는 버그가 발생할 가능성이 높다.
		for (int j = 1; j < length - i; ++j) {
			if (arr[j - 1] > arr[j]) {
				Swap(arr[j - 1], arr[j]);
			}
			++count;	// 전위연산자는 l-value, 후위연산자는 r-value를 리턴한다.
		}
	}

	return count;
}

template <typename T>
uint64_t SortSelection(T* arr, size_t length) {
	uint64_t count = 0;

	for (int i = 0; i < length; ++i) {
		uint64_t index = i;
		for (int j = i + 1; j < length; ++j) {
			if (arr[index] > arr[j]) {
				index = j;
			}
			++count;
		}

		if (i != index) {
			Swap(arr[i], arr[index]);
		}
	}

	return count;
}

template <typename T>
uint64_t SortInsertion(T* arr, size_t length) {
	uint64_t count = 0;

	for (int i = 1; i < length; ++i) {
		T temp = arr[i];
		int j = i - 1;
		for (; j >= 0 && arr[j] > temp; --j) {
			arr[j + 1] = arr[j];
			++count;
		}
		arr[j + 1] = temp;
		++count;
	}

	return count;
}

template <typename T>
uint64_t SortShell(T* arr, size_t length) {
	uint64_t count = 0;

	auto insertionSort = [&arr, &count](const int& first, const int& last, const int& gap) {
		for (int i = first + gap; i < last; i += gap) {
			T temp = arr[i];
			int j = i - gap;
			for (; j >= first && arr[j] > temp; j -= gap) {
				arr[j + gap] = arr[j];
				++count;
			}
			arr[j + gap] = temp;
			++count;
		}
	};

	for (int gap = static_cast<int>(length / 2); gap > 0; gap /= 2) {
		if (gap % 2 == 0) ++gap;	// 간격이 홀수이면 더 빠르다.

		for (int i = 0; i < gap; ++i) {
			insertionSort(i, length, gap);
		}
	}

	return count;
}

/// <summary> 대략적인 시간복잡도를 출력하는 함수 </summary>
void PrintComplexity(const uint64_t count, const uint64_t n) {
	std::cout << "Loop Count : " << count << ", Sorting Complexity (approximately) : ";
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
	//steady_clock::time_point current = steady_clock::now();   // 물리적 고정 시간
	//milliseconds millis
	//	= duration_cast<milliseconds>(current.time_since_epoch());
	//std::mt19937 generator(millis.count()); 				   // 메르센 트위스터 엔진 (64비트용 : std::mt19937_64)

	// reference : https://modoocode.com/304
	std::random_device device;          // 시드값 생성기 (속도 느림)
	std::mt19937 generator(device());   // 메르센 트위스터 엔진 (64비트용 : std::mt19937_64)

	std::uniform_int_distribution<int> distribution(1, 99);   // 난수 분포(균등 분포)와 범위

	size_t length = 20;
	std::vector<int> unsortedArray(length);	// resize. not reserve
	
	std::cout << "Unsorted Array\n";
	for (auto& e : unsortedArray) {
		e = distribution(generator);
		std::cout << std::setw(3) << e;
	}
	std::cout << std::endl;

	uint64_t loopCount;
	steady_clock::time_point start;
	std::vector<int> sortedArray;


	std::cout << "\n Bubble Sort Start\n";

	sortedArray = unsortedArray; // deep copy
	start = steady_clock::now();
	loopCount = SortBubble<int>(sortedArray.data(), length);
	PrintComplexity(loopCount, length);
	std::cout << "Sorting Time : " << duration_cast<microseconds>(steady_clock::now() - start).count() << " us\n";
	std::cout << "Sorted Array\n";
	for (auto& e : sortedArray) {
		std::cout << std::setw(3) << e;
	}
	std::cout << "\n Bubble Sort End\n" << std::endl;

	
	std::cout << "\n Selection Sort Start\n";

	sortedArray = unsortedArray; // deep copy
	start = steady_clock::now();
	loopCount = SortSelection<int>(sortedArray.data(), length);
	PrintComplexity(loopCount, length);
	std::cout << "Sorting Time : " << duration_cast<microseconds>(steady_clock::now() - start).count() << " us\n";
	// std::cout << "Sorted Array\n";
	// for (auto& e : sortedArray) {
	// 	std::cout << std::setw(3) << e;
	// }
	std::cout << "\n Selection Sort End\n" << std::endl;

	
	std::cout << "\n Insertion Sort Start\n";

	sortedArray = unsortedArray; // deep copy
	start = steady_clock::now();
	loopCount = SortInsertion<int>(sortedArray.data(), length);
	PrintComplexity(loopCount, length);
	std::cout << "Sorting Time : " << duration_cast<microseconds>(steady_clock::now() - start).count() << " us\n";
	// std::cout << "Sorted Array\n";
	// for (auto& e : sortedArray) {
	// 	std::cout << std::setw(3) << e;
	// }
	std::cout << "\n Insertion Sort End\n" << std::endl;

	
	std::cout << "\n Shell Sort Start\n";
	sortedArray = unsortedArray; // deep copy

	std::cout << "Unsorted Array\n";
	for (auto& e : unsortedArray) {
		std::cout << std::setw(3) << e;
	}
	std::cout << std::endl;

	start = steady_clock::now();
	loopCount = SortShell<int>(sortedArray.data(), length);
	PrintComplexity(loopCount, length);
	std::cout << "Sorting Time : " << duration_cast<microseconds>(steady_clock::now() - start).count() << " us\n";
	std::cout << "Sorted Array\n";
	for (auto& e : sortedArray) {
		std::cout << std::setw(3) << e;
	}
	std::cout << "\n Shell Sort End\n" << std::endl;
}