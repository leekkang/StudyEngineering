

#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
#include <functional>
#include <algorithm>

using namespace std;

#define DEBUG_LOG 0

class HuffmanTree {
	/// <summary> 허프만 트리 노드 </summary>
	struct Node {
		char mChar;         // 저장된 문자
		int mFrequency;     // 빈도수
		Node* mLeftNode;    // 왼쪽 노드
		Node* mRightNode;   // 오른쪽 노드

		Node(char c, int freq)
			: mChar(c), mFrequency(freq) {
			mLeftNode = mRightNode = nullptr;
		}

		Node(char c, int freq, Node* left, Node* right)
			: mChar(c), mFrequency(freq), mLeftNode(left), mRightNode(right) {
		}

		void SetChild(Node* left, Node* right) {
			mLeftNode = left;
			mRightNode = right;
		}
	};

	Node* mRoot = nullptr;                // 허프만 트리 루트
	unordered_map<char, string> mTable;   // 인코딩된 문자 정보

  public:
	HuffmanTree() {
		mRoot = nullptr;
	}

	/// <summary> 인코딩 문자 정보 테이블을 생성하는 함수 </summary>
	void SetTable(Node* root, string code) {
		if (root->mLeftNode != nullptr) {
			SetTable(root->mLeftNode, code + '0');
		}
		if (root->mRightNode != nullptr) {
			SetTable(root->mRightNode, code + '1');
		}

		// 리프 노드를 찾았다.
		mTable.insert(pair<char, string>(root->mChar, code));
#if DEBUG_LOG
		cout << "리프 노드 : " << root->mChar << ", 빈도수 : " << root->mFrequency << endl;
#endif
	}

	/// <summary> 허프만 트리와 인코딩 문자 정보를 생성하는 함수 </summary>
	void SetHuffmanTree(string str) {
		if (str.length() == 0) return;

		unordered_map<char, int> map;   // 문자, 빈도수 저장
		for (string::iterator i = str.begin(); i != str.end(); ++i) {
			if (map.find(*i) != map.end()) {
				map[*i]++;
			} else {
				map.insert(pair<char, int>(*i, 1));
			}
		}

#if DEBUG_LOG
		cout << "빈도수 확인" << endl;
		for (unordered_map<char, int>::iterator i = map.begin(); i != map.end(); ++i) {
			cout << i->first << " : " << i->second << endl;
		}
		cout << endl;
#endif

		// 정렬을 위해 벡터로 변경
		// 리스트는 이중 연결 리스트로 되어있어 사전 할당 메모리가 없고 무작위 액세스가 불가능하지만 삽입과 제거가 빠르다.
		// 그리고 목록에서 삽입 또는 삭제를 해도 반복자가 유효하다. 그러나 반복자 이외의 모든 산술연산이 불가능하다.
		// https://stackoverflow.com/questions/2209224/vector-vs-list-in-stl
		vector<Node*> container;
		Node* tmp;
		for (unordered_map<char, int>::iterator i = map.begin(); i != map.end(); ++i) {
			container.emplace_back(new Node(i->first, i->second));
		}
		sort(container.begin(), container.end(), [](Node* a, auto b) -> bool {
			return a->mFrequency < b->mFrequency;
		});

		// 트리 작성 예외처리
		if (container.size() == 1) {
			mRoot = *(container.begin());
			mTable.insert(pair<char, string>(mRoot->mChar, "0"));
			return;
		}

		// 트리 작성
		/*function<Node(vector<Node>::iterator)> GetParent = [](vector<Node>::iterator it)-> Node {
			Node parent(' ', it->mFrequency + (it + 1)->mFrequency, &(*it), &(*(it + 1)));
			return parent;
		};*/
		vector<Node*>::iterator it = container.begin();
		int index = 0;
		while (true) {
			Node* tmp = new Node(' ', container[index]->mFrequency + container[index + 1]->mFrequency, container[index], container[index + 1]);   // = GetParent(it);
			if ((index + 2) >= container.size()) {
				mRoot = tmp;
				break;
			}

			auto i = index + 1;
			for (; i != container.size(); ++i) {
				if (container[i]->mFrequency <= tmp->mFrequency)
					continue;
				else
					break;
			}
			if (i == container.size())
				container.emplace_back(tmp);
			else
				container.insert(container.begin() + i, tmp);
#if DEBUG_LOG
			cout << "삽입 확인 : " << tmp->mFrequency << " 는 " << container[i - 1]->mFrequency << "뒤에 위치한다." << endl;
#endif
			index += 2;
		}

		// 문자 정보 테이블 작성
		SetTable(mRoot, "");
	}

	Node* GetHuffmanTree() {
		return mRoot;
	}

	/// <summary> 받은 문자열을 인코딩한다. </summary>
	/// <param name="str"> 인코딩 대상 문자열 </param>
	string Encode(string str) {
		string result = "";
		for (string::iterator i = str.begin(); i != str.end(); ++i) {
			result += mTable[*i];
#if DEBUG_LOG
			cout << "문자 : " << *i << "를 다음 코드로 인코딩 : " << mTable[*i] << endl;
#endif
		}

#if DEBUG_LOG
		cout << "인코딩 된 전체 문자열 : " << result << endl;
#endif
		return result;
	}

	/// <summary> 받은 문자열을 디코딩한다. </summary>
	/// <param name="str"> 디코딩 대상 문자열 </param>
	string Decode(string str) {
		string result = "";

		// 문자 테이블에서 해당 하는 문자를 가져옴
		function<char(unordered_map<char, string>, string)> GetDecodeChar =
			[](unordered_map<char, string> table, string encoded) -> char {
			for (unordered_map<char, string>::iterator i = table.begin(); i != table.end(); ++i) {
				if ((*i).second == encoded)
					return (*i).first;
			}

			return ' ';
		};

		Node* target = mRoot;
		string word = "";
		for (string::iterator i = str.begin(); i != str.end(); ++i) {
			// 리프 노드를 발견했다.
			if (target->mLeftNode == nullptr && target->mRightNode == nullptr) {
				result += GetDecodeChar(mTable, word);
				target = mRoot;
				word = "";
			}
			word += *i;

			if (*i == '0')
				target = target->mLeftNode;
			else
				target = target->mRightNode;
		}
		result += GetDecodeChar(mTable, word);

		return result;
	}
};

int main() {
	string input;

	cout << "허프만 코드 테스트, 원하는 문자열을 입력 : ";
	cin >> input;

	HuffmanTree tree;
	tree.SetHuffmanTree(input);

	string result = tree.Encode(input);
	cout << "허프만 코드 인코딩 결과 : " << result << endl;

	result = tree.Decode(result);
	cout << "허프만 코드 디코딩 결과 : " << result << endl;
}

//#include <iostream>
//#include <unordered_map>
//using namespace std;
//
//unordered_map<char, string> umap;
//int main() {
//	// Declaring umap to be of <string, int> type
//	// key will be of string type and mapped value will
//	// be of double type
//
//	// inserting values by using [] operator
//	umap['a'] = "10";
//	umap['b'] = "20";
//	umap['c'] = "30";
//
//	// Traversing an unordered map
//	for (auto x : umap) {
//		string str(x.first + " ");
//		std::cout << x.first << endl;
//	}
//
//}