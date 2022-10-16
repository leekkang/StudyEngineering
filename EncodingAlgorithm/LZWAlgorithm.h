
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
	std::vector<std::string> m_vecDict;   // ���� ���ڵ��� ���� ����

  public:
	///< summary> ���ʷ� ���� ������ �����Ѵ�. </summary>
	void SetInitDic(std::string str) {
		std::string tmp;
		int index = 0;
		for (char c : str) {
			tmp = c;
			if (find(m_vecDict.begin(), m_vecDict.end(), tmp) == m_vecDict.end()) {
				if (DebugLog) {
					std::cout << "�� ���� �߰� : [" << tmp << "], �ε��� : " << index << std::endl;
					index++;
				}
				m_vecDict.push_back(tmp);
			} else {
				if (DebugLog)
					std::cout << "�̹� �����ϴ� ���� : " << tmp << std::endl;
			}
		}

		if (DebugLog)
			std::cout << "���ڷ� ������ ������ �ϼ��Ǿ���." << std::endl;
	}

	/// <summary> ���� ���ڿ��� ���ڵ��Ѵ�. </summary>
	/// <param name="str"> ���ڵ� ��� ���ڿ� </param>
	/// <returns> ���ڵ� �Ϸ�� ���ڿ��� ��ȯ�Ѵ�. </returns>
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
					std::cout << "�̹� �����ϴ� ���� : " << tmp << std::endl;
				tmp += c;
			} else {
				result += result.size() != 0 ? ("," + std::to_string(map[tmp])) : std::to_string(map[tmp]);

				// ���ڿ� �ִ� ���� ���� �Ѿ ��� ����ó��
				if (map.size() >= DICTIONARY_CAPACITY) {
					if (DebugLog)
						std::cout << "�����ϴ� �ܾ����� �뷮�� �Ѿ : " << tmp << std::endl;
				} else {
					if (DebugLog)
						std::cout << "�� �ܾ� �߰� : [" << tmp + c << "], �ε��� : " << index << std::endl;
					tmp += c;
					map[tmp] = index++;
				}
				tmp = c;
			}

			// ������ ���� ó��
			if (i + 1 == length) {
				if (map.find(tmp) == map.end()) {
					std::cout << "[" + tmp << "]�ܾ ������ �����ϴ�. �Ͼ �� ������?" << std::endl;
					exit(0);
				}
				result += result.size() != 0 ? ("," + std::to_string(map[tmp])) : std::to_string(map[tmp]);
			}
		}

		if (DebugLog) {
			std::cout << "���ڵ� �� ��ü ���ڿ� : " << result << std::endl;

			std::cout << "������� ����" << std::endl;
			for (std::pair<std::string, int> m : map) {
				std::cout << "�ε��� : " << m.second << ", ���ڿ� : [" << m.first << "]" << std::endl;
			}
		}
		return result;
	}

	/// <summary> ���� ���ڿ��� ���ڵ��Ѵ�. </summary>
	/// <param name="str"> ���ڵ� ��� ���ڿ� </param>
	/// <returns> ���ڵ� �Ϸ�� ���ڿ��� ��ȯ�Ѵ�. </returns>
	std::string Decode(std::string str) {
		std::string result = "";
		int index = 0;

		std::vector<std::string> map;
		// vector ������ 2���� ��� : std::copy vs assign
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
				std::cout << "[" + index << "]��° �ܾ ������ �����ϴ�. �Ͼ �� ������?" << std::endl;
				exit(0);
			}

			curr = map[index];
			result += curr;
			map.push_back(prev + curr[0]);
			if (DebugLog)
				std::cout << "���ڵ� ������ �� �ܾ� �߰� : [" << prev + curr[0] << "]" << std::endl;
			prev = curr;
		}

		if (DebugLog) {
			std::cout << "���ڵ� �� ��ü ���ڿ� : " << result << std::endl;

			std::cout << "������� ����" << std::endl;
			index = 0;
			for (std::string str : map) {
				std::cout << "�ε��� : " << index++ << ", ���ڿ� : [" << str << "]" << std::endl;
			}
		}
		return result;
	}
};
