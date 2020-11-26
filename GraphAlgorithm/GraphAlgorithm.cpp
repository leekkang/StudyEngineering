#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include <cmath>        // log, log10
#include <iomanip>      // input output manipulation (std::setw,...)
#include <functional>   // std::function

template <typename T>   // template<class T> 와 동일
void Swap(T& left, T& right) {
	if (left == right) return;

	T tmp = left;
	left = right;
	right = tmp;
}

template <typename T>
uint32_t SortBubble(T* arr, const size_t length) {   // T& 를 어떻게 쓰지..?
	uint32_t count = 0;

	for (int i = 0; i < length; ++i) {   // 반복문은 웬만하면 signed 자료형을 사용하자. unsigned는 버그가 발생할 가능성이 높다.
		for (int j = 1; j < length - i; ++j) {
			if (arr[j - 1] > arr[j]) {
				Swap(arr[j - 1], arr[j]);
				//std::swap<T>(arr[j - 1], arr[j]);
			}
			++count;   // 전위연산자는 l-value, 후위연산자는 r-value를 리턴한다.
		}
	}

	return count;   // 자잘한 연산은 제외하고 주가되는 비교, 대입만 측정한다.
}

void Kruskal(std::vector<std::vector<int>>& map, const int& n) {

}

	/// <summary> 대략적인 시간복잡도를 출력하는 함수 </summary>
void PrintComplexity(const uint32_t count, const uint32_t n) {
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
	// 랜덤 그래프 생성은 여기 참조 : https://en.wikipedia.org/wiki/Erd%C5%91s%E2%80%93R%C3%A9nyi_model
	// 에어디쉬-레니 모델, 와츠-스트로가츠 모델 등이 있다.

	size_t length{7};                       // Uniform Initialization (up to C++11)
	// 그래프는 링크 참조 : https://en.wikipedia.org/wiki/Kruskal%27s_algorithm
	std::vector<std::vector<int>> graph = {
		{0, 7, 0, 5, 0, 0, 0},	// a
		{7, 0, 8, 9, 7, 0, 0},	// b
		{0, 8, 0, 0, 5, 0, 0},	// c
		{5, 9, 0, 0, 15, 6, 0},	// d
		{0, 7, 5, 15, 0, 8, 9},	// e
		{0, 0, 0, 6, 8, 0, 11},	// f
		{0, 0, 0, 0, 9, 11, 0},	// g
	};

	bool bPrintGraph = false;

	if (bPrintGraph) {
		std::cout << "Graph Matrix\n";
	}
	if (bPrintGraph) {
		for (auto& v : graph) {
			for (const auto& e : v) {
				std::cout << std::setw(5) << e;
			}
		}
		std::cout << "\n";
	}
	std::cout << std::endl;

	uint32_t loopCount;
	steady_clock::time_point start;

	using funcPoint = uint32_t (*)(int*, const size_t);   // == typedef uint32_t(*funcPoint)(int*, const size_t)

	std::vector<std::pair<std::string, funcPoint>> sortPair{
		{"Bubble", SortBubble<int>},
	};

	for (const auto& pair : sortPair) {
		std::cout << "\n " << pair.first << " Algorithm Start\n";

		start = steady_clock::now();
		pair.second(sortedArray.data(), length);
		PrintComplexity(loopCount, length);
		std::cout << "Sorting Time : " << duration_cast<microseconds>(steady_clock::now() - start).count() << " us\n";

		if (pair.first == "Intro") {
			std::cout << "Sorted Array\n";
			for (const auto& e : sortedArray) {
				std::cout << std::setw(4) << e;
			}
		}

		std::cout << "\n " << pair.first << " Sort End\n"
				  << std::endl;
	}
}