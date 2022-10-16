
#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
#include <functional>
#include <algorithm>

template <bool DebugLog = true>
class HuffmanTree {
	/// <summary> 허프만 트리 노드 </summary>
	struct Node {
		char m_Char;         // 저장된 문자
		int m_Frequency;     // 빈도수
		Node* m_LeftNode;    // 왼쪽 노드
		Node* m_RightNode;   // 오른쪽 노드

		Node(char c, int freq)
			: m_Char(c), m_Frequency(freq) {
			m_LeftNode = m_RightNode = nullptr;
		}

		Node(char c, int freq, Node* left, Node* right)
			: m_Char(c), m_Frequency(freq), m_LeftNode(left), m_RightNode(right) {
		}

		void SetChild(Node* left, Node* right) {
			m_LeftNode = left;
			m_RightNode = right;
		}
	};

	Node* m_Root = nullptr;                          	// 허프만 트리 루트
	std::unordered_map<char, std::string> m_mapTable;   // 인코딩된 문자 정보

  public:
	/// <summary> 인코딩 문자 정보 테이블을 생성하는 함수 </summary>
	void SetTable(Node* root, std::string code) {
		if (root->m_LeftNode != nullptr) {
			SetTable(root->m_LeftNode, code + '0');
		}
		if (root->m_RightNode != nullptr) {
			SetTable(root->m_RightNode, code + '1');
		}

		// 리프 노드를 찾았다.
		m_mapTable.insert(std::pair<char, std::string>(root->m_Char, code));
		if (DebugLog)
			std::cout << "리프 노드 : " << root->m_Char << ", 빈도수 : " << root->m_Frequency << std::endl;
	}

	/// <summary> 허프만 트리와 인코딩 문자 정보를 생성하는 함수 </summary>
	void SetHuffmanTree(std::string str) {
		if (str.length() == 0) return;

		std::unordered_map<char, int> map;   // 문자, 빈도수 저장
		for (std::string::iterator i = str.begin(); i != str.end(); ++i) {
			if (map.find(*i) != map.end()) {
				map[*i]++;
			} else {
				map.insert(std::pair<char, int>(*i, 1));
			}
		}

		if (DebugLog) {
			std::cout << "빈도수 확인" << std::endl;
			for (std::unordered_map<char, int>::iterator i = map.begin(); i != map.end(); ++i) {
				std::cout << i->first << " : " << i->second << std::endl;
			}
			std::cout << std::endl;
		}

		// 정렬을 위해 벡터로 변경
		// 리스트는 이중 연결 리스트로 되어있어 사전 할당 메모리가 없고 무작위 액세스가 불가능하지만 삽입과 제거가 빠르다.
		// 그리고 목록에서 삽입 또는 삭제를 해도 반복자가 유효하다. 그러나 반복자 이외의 모든 산술연산이 불가능하다.
		// https://stackoverflow.com/questions/2209224/vector-vs-list-in-stl
		std::vector<Node*> container;
		Node* tmp;
		for (std::unordered_map<char, int>::iterator i = map.begin(); i != map.end(); ++i) {
			container.emplace_back(new Node(i->first, i->second));
		}
		std::sort(container.begin(), container.end(), [](Node* a, auto b) -> bool {
			return a->m_Frequency < b->m_Frequency;
		});

		// 트리 작성 예외처리
		if (container.size() == 1) {
			m_Root = *(container.begin());
			m_mapTable.insert(std::pair<char, std::string>(m_Root->m_Char, "0"));
			return;
		}

		// 트리 작성
		/*function<Node(std::vector<Node>::iterator)> GetParent = [](std::vector<Node>::iterator it)-> Node {
			Node parent(' ', it->m_Frequency + (it + 1)->m_Frequency, &(*it), &(*(it + 1)));
			return parent;
		};*/
		std::vector<Node*>::iterator it = container.begin();
		int index = 0;
		while (true) {
			Node* tmp = new Node(' ', container[index]->m_Frequency + container[index + 1]->m_Frequency, container[index], container[index + 1]);   // = GetParent(it);
			if ((index + 2) >= container.size()) {
				m_Root = tmp;
				break;
			}

			auto i = index + 1;
			for (; i != container.size(); ++i) {
				if (container[i]->m_Frequency <= tmp->m_Frequency)
					continue;
				else
					break;
			}
			if (i == container.size())
				container.emplace_back(tmp);
			else
				container.insert(container.begin() + i, tmp);
			if (DebugLog)
				std::cout << "삽입 확인 : " << tmp->m_Frequency << " 는 " << container[i - 1]->m_Frequency << "뒤에 위치한다." << std::endl;
			index += 2;
		}

		// 문자 정보 테이블 작성
		SetTable(m_Root, "");
	}

	Node* GetHuffmanTree() {
		return m_Root;
	}

	/// <summary> 받은 문자열을 인코딩한다. </summary>
	/// <param name="str"> 인코딩 대상 문자열 </param>
	std::string Encode(std::string str) {
		std::string result = "";
		for (std::string::iterator i = str.begin(); i != str.end(); ++i) {
			result += m_mapTable[*i];
			if (DebugLog)
				std::cout << "문자 : " << *i << "를 다음 코드로 인코딩 : " << m_mapTable[*i] << std::endl;
		}

		if (DebugLog)
			std::cout << "인코딩 된 전체 문자열 : " << result << std::endl;
		return result;
	}

	/// <summary> 받은 문자열을 디코딩한다. </summary>
	/// <param name="str"> 디코딩 대상 문자열 </param>
	std::string Decode(std::string str) {
		std::string result = "";

		// 문자 테이블에서 해당 하는 문자를 가져옴
		std::function<char(std::unordered_map<char, std::string>, std::string)> GetDecodeChar =
			[](std::unordered_map<char, std::string> table, std::string encoded) -> char {
			for (std::unordered_map<char, std::string>::iterator i = table.begin(); i != table.end(); ++i) {
				if ((*i).second == encoded)
					return (*i).first;
			}

			return ' ';
		};

		Node* target = m_Root;
		std::string word = "";
		for (std::string::iterator i = str.begin(); i != str.end(); ++i) {
			// 리프 노드를 발견했다.
			if (target->m_LeftNode == nullptr && target->m_RightNode == nullptr) {
				result += GetDecodeChar(m_mapTable, word);
				target = m_Root;
				word = "";
			}
			word += *i;

			if (*i == '0')
				target = target->m_LeftNode;
			else
				target = target->m_RightNode;
		}
		result += GetDecodeChar(m_mapTable, word);

		return result;
	}
};