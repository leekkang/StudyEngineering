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
uint64_t SortBubble(T&& arr, size_t length) {
	uint64_t count = 0;

	for (int i = 0; i < length; ++i) {
		for (int j = 0; j < (length - 1) - i; ++j) {
			if (arr[j] > arr[j + 1]) {
				Swap(arr[j], arr[j + 1]);
				count++;
			}
		}
	}

	return count;
}

/// <summary> 대략적인 시간복잡도를 출력하는 함수 </summary>
void PrintComplexity(const uint64_t count, const uint64_t n) {
	std::cout << "Loop Count : " << count << ", Sorting Complexity (approximately) : ";
	if (count < n) {
		std::cout << "1 ~ N (1 ~ " << n << ")\n";
	} else if (count < n * log(n)) {
		std::cout << "N ~ NlogN (" << n << " ~ " << n * log(n) << ")\n";
	} else if (count < n * n) {
		std::cout << "NlogN ~ N^2 (" << n * log(n) << " ~ " << n * n << ")\n";
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

	std::uniform_int_distribution<int> distribution(1, 100);   // 난수 분포(균등 분포)와 범위

	size_t length = 10;
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

	std::cout << "\nBubble Sort Start\n";

	sortedArray = unsortedArray; // deep copy
	start = steady_clock::now();
	loopCount = SortBubble<int*>(sortedArray.data(), length);
	PrintComplexity(loopCount, length);
	std::cout << "Sorting Time : " << duration_cast<microseconds>(steady_clock::now() - start).count() << " us\n";
	std::cout << "Sorted Array\n";
	for (auto& e : sortedArray) {
		std::cout << std::setw(3) << e;
	}
	std::cout << "\nBubble Sort End\n" << std::endl;
}