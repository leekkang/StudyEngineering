
#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
#include <sstream>

#define DICTIONARY_CAPACITY 4096

template <typename Out>
void split(const std::string &s, char delim, Out result) {
	std::stringstream ss(s);
	std::string item;

	while (getline(ss, item, delim))
		*(result++) = item;
}
std::vector<std::string> split(const std::string &s, const char delim) {
	std::vector<std::string> elems;
	split(s, delim, back_inserter(elems));

	return elems;
}

template <bool DebugLog = true>
class LZWAlgorithm {
	std::vector<std::string> m_vecDict;   // 최초 인코딩된 문자 정보

  public:
	///< summary> 최초로 사용될 사전을 생성한다. </summary>
	void SetInitDic(std::string str) {
		std::string tmp;
		int index = 0;
		for (char c : str) {
			tmp = c;
			if (find(m_vecDict.begin(), m_vecDict.end(), tmp) == m_vecDict.end()) {
				if (DebugLog) {
					std::cout << "새 문자 추가 : [" << tmp << "], 인덱스 : " << index << std::endl;
					index++;
				}
				m_vecDict.push_back(tmp);
			} else {
				if (DebugLog)
					std::cout << "이미 존재하는 문자 : " << tmp << std::endl;
			}
		}

		if (DebugLog)
			std::cout << "문자로 구성된 사전이 완성되었다." << std::endl;
	}

	/// <summary> 받은 문자열을 인코딩한다. </summary>
	/// <param name="str"> 인코딩 대상 문자열 </param>
	/// <returns> 인코딩 완료된 문자열을 반환한다. </returns>
	std::string Encode(std::string str) {
		std::string result = "";
		std::string tmp = "";
		int index = 0;

		std::unordered_map<std::string, int> map;
		for (std::string s : m_vecDict)
			map[s] = index++;

		int length = str.size();
		for (int i = 0; i < length; i++) {
			char c = str[i];

			if (map.find(tmp + c) != map.end()) {
				if (DebugLog)
					std::cout << "이미 존재하는 문자 : " << tmp << std::endl;
				tmp += c;
			} else {
				result += result.size() != 0 ? ("," + std::to_string(map[tmp])) : std::to_string(map[tmp]);

				// 문자열 최대 저장 수를 넘어갈 경우 예외처리
				if (map.size() >= DICTIONARY_CAPACITY) {
					if (DebugLog)
						std::cout << "존재하는 단어지만 용량이 넘어감 : " << tmp << std::endl;
				} else {
					if (DebugLog)
						std::cout << "새 단어 추가 : [" << tmp + c << "], 인덱스 : " << index << std::endl;
					tmp += c;
					map[tmp] = index++;
				}
				tmp = c;
			}

			// 마지막 문자 처리
			if (i + 1 == length) {
				if (map.find(tmp) == map.end()) {
					std::cout << "[" + tmp << "]단어가 사전에 없습니다. 일어날 수 없는일?" << std::endl;
					exit(0);
				}
				result += result.size() != 0 ? ("," + std::to_string(map[tmp])) : std::to_string(map[tmp]);
			}
		}

		if (DebugLog) {
			std::cout << "인코딩 된 전체 문자열 : " << result << std::endl;

			std::cout << "만들어진 사전" << std::endl;
			for (std::pair<std::string, int> m : map) {
				std::cout << "인덱스 : " << m.second << ", 문자열 : [" << m.first << "]" << std::endl;
			}
		}
		return result;
	}

	/// <summary> 받은 문자열을 디코딩한다. </summary>
	/// <param name="str"> 디코딩 대상 문자열 </param>
	/// <returns> 디코딩 완료된 문자열을 반환한다. </returns>
	std::string Decode(std::string str) {
		std::string result = "";
		int index = 0;

		std::vector<std::string> map;
		// vector 복사의 2가지 방법 : std::copy vs assign
		map.resize((int)m_vecDict.size());
		copy(m_vecDict.begin(), m_vecDict.end(), map.begin());
		// map.clear();
		// map.assign(m_vecDict.begin(), m_vecDict.end());

		std::vector<std::string> target = split(str, ',');
		std::string prev = map[atoi(target[0].c_str())];
		std::string curr = "";

		result += prev;
		for (std::vector<std::string>::iterator iter = target.begin() + 1; iter < target.end(); iter++) {
			index = atoi((*iter).c_str());
			if (index >= map.size()) {
				std::cout << "[" + index << "]번째 단어가 사전에 없습니다. 일어날 수 없는일?" << std::endl;
				exit(0);
			}

			curr = map[index];
			result += curr;
			map.push_back(prev + curr[0]);
			if (DebugLog)
				std::cout << "디코딩 사전에 새 단어 추가 : [" << prev + curr[0] << "]" << std::endl;
			prev = curr;
		}

		if (DebugLog) {
			std::cout << "디코딩 된 전체 문자열 : " << result << std::endl;

			std::cout << "만들어진 사전" << std::endl;
			index = 0;
			for (std::string str : map) {
				std::cout << "인덱스 : " << index++ << ", 문자열 : [" << str << "]" << std::endl;
			}
		}
		return result;
	}
};
