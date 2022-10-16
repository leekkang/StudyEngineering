
#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
#include <functional>
#include <algorithm>
#include <chrono>

#include "Huffman.h"
#include "LZWAlgorithm.h"


int main() {
	std::string input {"test encoding test test of Huffman and LZW Algorithm. is it work correctly?"};

	constexpr bool bPrintLog = false;   	// 진행상황 로그 출력 여부

	HuffmanTree<bPrintLog> tree; // TODO 수정 필요
	tree.SetHuffmanTree(input);

	LZWAlgorithm<bPrintLog> lzw;
	lzw.SetInitDic(input);
	
	std::vector<std::string> vecName { "허프만", "렘펠지브웰치" };
	std::vector<std::pair<std::function<std::string(std::string)>,
						  std::function<std::string(std::string)>>>
		vecFunc{
			{ [&](std::string input) -> std::string { return tree.Encode(input); }, 
			  [&](std::string input) -> std::string { return tree.Decode(input); } },
			{ [&](std::string input) -> std::string { return lzw.Encode(input); }, 
			  [&](std::string input) -> std::string { return lzw.Decode(input); } }
		};

	std::chrono::steady_clock::time_point start;
	
	std::string result;
	int size = vecName.size();
	for (int i = 0; i < size; ++i) {
		std::cout << "\n " << vecName[i] << " 알고리즘 테스트\n";
		start = std::chrono::steady_clock::now();

		result = vecFunc[i].first(input);
		std::cout << "\n    " << vecName[i] << " 알고리즘 인코딩 결과\n" << result << "\n";
		std::cout << "  Encoding Time : " << 
			std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now() - start).count() << " us\n";

		start = std::chrono::steady_clock::now();
		result = vecFunc[i].second(result);
		std::cout << "\n    " << vecName[i] << " 알고리즘 디코딩 결과\n" << result << "\n";
		std::cout << "  Decoding Time : " << 
			std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now() - start).count() << " us\n";

		std::cout << "\n " << vecName[i] << " 알고리즘 테스트 종료\n" << std::endl;
	}
}