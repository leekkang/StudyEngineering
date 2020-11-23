#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <chrono>
#include <cmath>        // log, log10
#include <iomanip>      // input output manipulation (std::setw,...)
#include <functional>   // std::function

template <typename T>   // template<class T> 와 동일
void Swap(T& left, T& right) {
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

template <typename T>
uint32_t SortSelection(T* arr, const size_t length) {
	uint32_t count = 0;

	for (int i = 0; i < length; ++i) {
		uint32_t index = i;
		for (int j = i + 1; j < length; ++j) {
			if (arr[index] > arr[j]) {
				index = j;
			}
			++count;
		}

		if (i != index) {
			Swap(arr[i], arr[index]);
			//std::swap<T>(arr[i], arr[index]);
		}
		++count;
	}

	return count;
}

template <typename T>
uint32_t SortInsertion(T* arr, const size_t length) {
	uint32_t count = 0;

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
uint32_t SortShell(T* arr, const size_t length) {
	uint32_t count = 0;

	auto insertionSort = [&arr, &count](const int& begin, const int& end, const int& gap) {
		for (int i = begin + gap; i < end; i += gap) {
			T temp = arr[i];
			int j = i - gap;
			for (; j >= begin && arr[j] > temp; j -= gap) {
				arr[j + gap] = arr[j];
				++count;
			}
			arr[j + gap] = temp;
			++count;
		}
	};

	for (int gap = static_cast<int>(length / 2); gap > 0; gap /= 2) {
		if (gap % 2 == 0) ++gap;   // 간격이 홀수이면 더 빠르다.

		for (int i = 0; i < gap; ++i) {
			insertionSort(i, length, gap);
		}
	}

	return count;
}

template <typename T>
uint32_t SortMergeTopDown(T* arr, const size_t length) {
	uint32_t count = 0;
	std::vector<T> temp(length);   // resize. not reserve

	// 하향식 2-way merge sort
	// 재귀함수로 사용하기 때문에 auto 타입으로 정의하지 못한다. -> inline이 아니다.
	std::function<void(const int&, const int&)> merge = [&](const int& begin, const int& end) {
		// end 는 인덱스에 포함되지 않는다. -> arr[end] : x, arr[end-1] : o
		++count;
		if (end - begin < 2)
			return;

		// begin + end 가 홀수면 왼쪽 리스트의 길이가 오른쪽 리스트의 길이보다 짧다.
		// divide
		int middle = (begin + end) / 2;

		// conquer
		merge(begin, middle);
		merge(middle, end);

		// combine
		int left = begin, right = middle;
		for (int i = begin; i < end; ++i) {
			// 왼쪽 리스트가 끝나지 않은 상황에서, 오른쪽 리스트가 끝났거나 왼쪽의 값이 오른쪽 값보다 작을 경우
			if (left < middle && (right >= end || arr[left] <= arr[right]))
				temp[i] = arr[left++];
			else
				temp[i] = arr[right++];

			++count;
		}

		// copy
		for (int i = begin; i < end; ++i)
			arr[i] = temp[i];
	};

	merge(0, length);

	return count;
}

template <typename T>
uint32_t SortMergeBottomUp(T* arr, const size_t length) {
	uint32_t count = 0;
	std::vector<T> temp(length);   // resize. not reserve

	int left, right, middle, end;
	// divide
	for (int width = 1; width < length; width *= 2) {
		// conquer
		for (int begin = 0; begin < length; begin += width * 2) {
			end = std::min(begin + width * 2, static_cast<int>(length));
			// combine
			left = begin;
			right = std::min(begin + width, static_cast<int>(length));
			middle = right;
			for (int i = begin; i < end; ++i) {
				// 왼쪽 리스트가 끝나지 않은 상황에서, 오른쪽 리스트가 끝났거나 왼쪽의 값이 오른쪽 값보다 작을 경우
				if (left < middle && (right >= end || arr[left] <= arr[right]))
					temp[i] = arr[left++];
				else
					temp[i] = arr[right++];

				++count;
			}
		}
		
		// copy
		for (int i = 0; i < length; ++i)
			arr[i] = temp[i];
	}

	return count;
}

template <typename T>
uint32_t SortQuick(T* arr, const size_t length) {
	uint32_t count = 0;

	// 재귀함수로 사용하기 때문에 auto 타입으로 정의하지 못한다. -> inline이 아니다.
	std::function<void(const int&, const int&)> quick = [&](const int& begin, const int& end) {
		// end 도 인덱스에 포함된다. -> arr[end] : o, arr[end-1] : o
		if (begin >= end)
			return;

		// divide
		int left = begin - 1;
		int pivot = end;	// pivot 을 오른쪽 끝으로 잡는다.
		for (int i = begin; i < end; ++i) {
			// 리스트 끝까지 순회하면서 피벗보다 작은 값들을 앞으로 옮긴다.
			if (arr[i] < arr[pivot]) {
				++left;
				if (left != i)	// 둘이 같은 값이면 굳이 바꿀 필요가 없다.
					Swap(arr[left], arr[i]);
					//std::swap<T>(arr[left], arr[i]);
				++count;
			}
		}
		Swap(arr[++left], arr[pivot]);
		//std::swap<T>(arr[++left], arr[pivot]);
		++count;

		// conquer
		quick(begin, left - 1);
		quick(left + 1, end);
	};

	quick(0, length - 1);

	return count;
}

template <typename T>
uint32_t SortHeap(T* arr, const size_t length) {
	uint32_t count = 0;

	auto siftdown = [&](int root, const int& len) {
		// 자식 노드가 없으면 종료
		for (; root * 2 < len ;) {
			++count;

			// 0번 index를 사용하기 위해 약간의 계산을 추가한다.
			int current = root;
			int left = (root + 1) * 2 - 1;
			int right = (root + 1) * 2;

			if (arr[left] > arr[current]) current = left;
			if (right <= len && arr[right] > arr[current]) current = right;
			
			// 이미 정렬된 노드면 종료
			if (current == root) {
				return;
			} else {
				Swap(arr[current], arr[root]);
				//std::swap<T>(arr[current], arr[root]);
				root = current;
			}
		}
	};


	// Build Heap (Heapify)
	// 0번 인덱스는 사용하지 않는다.
	for (int parent = (length - 1) / 2; parent >= 0; --parent) {
		siftdown(parent, length - 1);
	}

	int end = length - 1;
	for (; end > 0;) {
		++count;
		Swap(arr[end], arr[0]);
		//std::swap<T>(arr[end], arr[0]);
		--end;
		siftdown(0, end);
	}

	return count;
}

template <typename T>
uint32_t SortCounting(T* arr, const size_t length) {
	uint32_t count = 0;

	// 최대값 찾기
	int max = 0;
	for (int i = 0; i < length; ++i) {
		++count;
		if (arr[i] > max) max = arr[i];
	}

	// 카운팅 배열 작성
	std::vector<T> countArr(max + 1, 0);
	for (int i = 0; i < length; ++i) {
		++count;
		++countArr[arr[i]];
	}
	// 누적 합 계산
	for (int i = 1; i < max + 1; ++i) {
		++count;
		countArr[i] += countArr[i - 1];
	}

	// 카피 배열 작성
	std::vector<T> temp(length);
	for (int i = 0; i < length; ++i) {
		++count;
		--countArr[arr[i]];
		temp[countArr[arr[i]]] = arr[i];
	}

	// 카피 배열 원본에 복사 (소팅 알고리즘에 포함되는 부분은 아님)
	for (int i = 0; i < length; ++i) {
		++count;
		arr[i] = temp[i];
	}

	return count;
}

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
	maxRadix = static_cast<int>(log10(static_cast<double>(maxRadix)) + 1);	// radix에 따라가도록 변경해야함.

	// 카운팅 배열
	std::vector<T> countArr(radix);

	int index, pval, i;
	for (int n = 0; n < maxRadix; ++n) {
		pval = static_cast<int>(pow(radix, n));

		// initialize
		countArr.assign(radix, 0);
		//for (int i = 0; i < radix; ++i) countArr[i] = 0;

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

template <typename T>
uint32_t SortBucket(T* arr, const size_t length) {
	uint32_t count = 0;
	int bucketNumber = 10;	// 생성되는 버킷의 개수

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
		buckets[(value < 0) ? 0 : (value < bucketNumber - 1) ? value : bucketNumber - 1].push_back(arr[i]);	// == std::clamp (#include<algorithm>)
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
	// reference : http://egloos.zum.com/sweeper/v/2996847
	////system_clock::time_point rootrent = system_clock::now(); // 컴퓨터 시스템 시간. system_clock == high_resolution_clock
	//steady_clock::time_point rootrent = steady_clock::now();   // 물리적 고정 시간
	//milliseconds millis
	//	= duration_cast<milliseconds>(rootrent.time_since_epoch());
	//std::mt19937 generator(millis.count()); 				   // 메르센 트위스터 엔진 (64비트용 : std::mt19937_64)

	// reference : https://modoocode.com/304
	std::random_device device;          // 시드값 생성기 (속도 느림)
	std::mt19937 generator(device());   // 메르센 트위스터 엔진 (64비트용 : std::mt19937_64)

	std::uniform_int_distribution<int> distribution(1, 999);   // 난수 분포(균등 분포)와 범위

	size_t length{100};                       // Uniform Initialization (up to C++11)
	std::vector<int> unsortedArray(length);   // resize. not reserve

	std::cout << "Unsorted Array\n";
	for (auto& e : unsortedArray) {
		e = distribution(generator);
		std::cout << std::setw(4) << e;
	}
	//// Sorted array test code
	// int num = 1;
	// for (auto& e : unsortedArray) {
	// 	e = num++;
	// 	std::cout << std::setw(4) << e;
	// }
	std::cout << std::endl;

	uint32_t loopCount;
	steady_clock::time_point root;
	std::vector<int> sortedArray;

	// std::vector<std::string> name{
	// 	"Bubble",
	// 	"Selection",
	// 	"Insertion",
	// 	"Shell",
	// 	"Merge",
	// 	"Quick",
	// };
	using funcPoint = uint32_t (*)(int*, const size_t);   // == typedef uint32_t(*funcPoint)(int*, const size_t)
	// funcPoint function[]{
	// 	SortBubble<int>,
	// 	SortSelection<int>,
	// 	SortInsertion<int>,
	// 	SortShell<int>,
	// 	SortMergeBottomUp<int>,
	// 	SortQuick<int>,
	// };

	std::vector<std::pair<std::string, funcPoint>> sortPair{
		{"Bubble", SortBubble<int>},
		{"Selection", SortSelection<int>},
		{"Insertion", SortInsertion<int>},
		{"Shell", SortShell<int>},
		{"Merge", SortMergeBottomUp<int>},
		{"Quick", SortQuick<int>},
		{"Heap", SortHeap<int>},
		{"Counting", SortCounting<int>},
		{"Radix", SortRadix<int>},
		{"Bucket", SortBucket<int>},
	};
	
	bool bPrintArray = true;
	for (const auto& pair : sortPair) {
		std::cout << "\n " << pair.first << " Sort root\n";

		sortedArray = unsortedArray;   // deep copy

		root = steady_clock::now();
		loopCount = pair.second(sortedArray.data(), length);
		PrintComplexity(loopCount, length);
		std::cout << "Sorting Time : " << duration_cast<microseconds>(steady_clock::now() - root).count() << " us\n";

		if (bPrintArray) {
			std::cout << "Sorted Array\n";
			for (const auto& e : sortedArray) {
				std::cout << std::setw(4) << e;
			}
		}

		std::cout << "\n " << pair.first << " Sort End\n"
				  << std::endl;
	}
}