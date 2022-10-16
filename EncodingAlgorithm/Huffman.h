
#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
#include <functional>
#include <algorithm>

template <bool DebugLog = true>
class HuffmanTree {
	/// <summary> ������ Ʈ�� ��� </summary>
	struct Node {
		char m_Char;         // ����� ����
		int m_Frequency;     // �󵵼�
		Node* m_LeftNode;    // ���� ���
		Node* m_RightNode;   // ������ ���

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

	Node* m_Root = nullptr;                          	// ������ Ʈ�� ��Ʈ
	std::unordered_map<char, std::string> m_mapTable;   // ���ڵ��� ���� ����

  public:
	/// <summary> ���ڵ� ���� ���� ���̺��� �����ϴ� �Լ� </summary>
	void SetTable(Node* root, std::string code) {
		if (root->m_LeftNode != nullptr) {
			SetTable(root->m_LeftNode, code + '0');
		}
		if (root->m_RightNode != nullptr) {
			SetTable(root->m_RightNode, code + '1');
		}

		// ���� ��带 ã�Ҵ�.
		m_mapTable.insert(std::pair<char, std::string>(root->m_Char, code));
		if (DebugLog)
			std::cout << "���� ��� : " << root->m_Char << ", �󵵼� : " << root->m_Frequency << std::endl;
	}

	/// <summary> ������ Ʈ���� ���ڵ� ���� ������ �����ϴ� �Լ� </summary>
	void SetHuffmanTree(std::string str) {
		if (str.length() == 0) return;

		std::unordered_map<char, int> map;   // ����, �󵵼� ����
		for (std::string::iterator i = str.begin(); i != str.end(); ++i) {
			if (map.find(*i) != map.end()) {
				map[*i]++;
			} else {
				map.insert(std::pair<char, int>(*i, 1));
			}
		}

		if (DebugLog) {
			std::cout << "�󵵼� Ȯ��" << std::endl;
			for (std::unordered_map<char, int>::iterator i = map.begin(); i != map.end(); ++i) {
				std::cout << i->first << " : " << i->second << std::endl;
			}
			std::cout << std::endl;
		}

		// ������ ���� ���ͷ� ����
		// ����Ʈ�� ���� ���� ����Ʈ�� �Ǿ��־� ���� �Ҵ� �޸𸮰� ���� ������ �׼����� �Ұ��������� ���԰� ���Ű� ������.
		// �׸��� ��Ͽ��� ���� �Ǵ� ������ �ص� �ݺ��ڰ� ��ȿ�ϴ�. �׷��� �ݺ��� �̿��� ��� ��������� �Ұ����ϴ�.
		// https://stackoverflow.com/questions/2209224/vector-vs-list-in-stl
		std::vector<Node*> container;
		Node* tmp;
		for (std::unordered_map<char, int>::iterator i = map.begin(); i != map.end(); ++i) {
			container.emplace_back(new Node(i->first, i->second));
		}
		std::sort(container.begin(), container.end(), [](Node* a, auto b) -> bool {
			return a->m_Frequency < b->m_Frequency;
		});

		// Ʈ�� �ۼ� ����ó��
		if (container.size() == 1) {
			m_Root = *(container.begin());
			m_mapTable.insert(std::pair<char, std::string>(m_Root->m_Char, "0"));
			return;
		}

		// Ʈ�� �ۼ�
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
				std::cout << "���� Ȯ�� : " << tmp->m_Frequency << " �� " << container[i - 1]->m_Frequency << "�ڿ� ��ġ�Ѵ�." << std::endl;
			index += 2;
		}

		// ���� ���� ���̺� �ۼ�
		SetTable(m_Root, "");
	}

	Node* GetHuffmanTree() {
		return m_Root;
	}

	/// <summary> ���� ���ڿ��� ���ڵ��Ѵ�. </summary>
	/// <param name="str"> ���ڵ� ��� ���ڿ� </param>
	std::string Encode(std::string str) {
		std::string result = "";
		for (std::string::iterator i = str.begin(); i != str.end(); ++i) {
			result += m_mapTable[*i];
			if (DebugLog)
				std::cout << "���� : " << *i << "�� ���� �ڵ�� ���ڵ� : " << m_mapTable[*i] << std::endl;
		}

		if (DebugLog)
			std::cout << "���ڵ� �� ��ü ���ڿ� : " << result << std::endl;
		return result;
	}

	/// <summary> ���� ���ڿ��� ���ڵ��Ѵ�. </summary>
	/// <param name="str"> ���ڵ� ��� ���ڿ� </param>
	std::string Decode(std::string str) {
		std::string result = "";

		// ���� ���̺��� �ش� �ϴ� ���ڸ� ������
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
			// ���� ��带 �߰��ߴ�.
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