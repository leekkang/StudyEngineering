
#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

#define DEBUG_LOG 1
#define DICTIONARY_CAPACITY 4096

template<typename Out>
void split(const string &s, char delim, Out result) {
	stringstream ss(s);
	string item;
	
	while (getline(ss, item, delim))
		*(result++) = item;
}
vector<string> split(const string &s, const char delim) {
	vector<string> elems;
	split(s, delim, back_inserter(elems));

	return elems;
}

class LZWAlgorithm {
	vector<string> mDic;	// 최초 인코딩된 문자 정보

public:
	///<summary> 최초로 사용될 사전을 생성한다. </summary>
	void SetInitDic(string str) {
		string tmp;
		int index = 0;
		for (char c : str) {
			tmp = c;
			if (find(mDic.begin(), mDic.end(), tmp) == mDic.end()) {
#if DEBUG_LOG
				cout << "새 문자 추가 : [" << tmp << "], 인덱스 : " << index << endl;
				index++;
#endif
				mDic.push_back(tmp);
			} else {
#if DEBUG_LOG
			cout << "이미 존재하는 문자 : " << tmp << endl;
#endif
			}
		}

#if DEBUG_LOG
		cout << "문자로 구성된 사전이 완성되었다." << endl;
#endif
	}

	/// <summary> 받은 문자열을 인코딩한다. </summary>
	/// <param name="str"> 인코딩 대상 문자열 </param>
    /// <returns> 인코딩 완료된 문자열을 반환한다. </returns>
	string Encode(string str) {
		string result = "";
		string tmp = "";
		int index = 0;

		unordered_map <string, int> map;
		for (string s : mDic)
			map[s] = index++;

		int length = str.size();
		for (int i = 0; i < length; i++) {
			char c = str[i];

			if (map.find(tmp + c) != map.end()) {
#if DEBUG_LOG
				cout << "이미 존재하는 문자 : " << tmp << endl;
#endif
				tmp += c;
			} else {
				result += result.size() != 0 ? ("," + to_string(map[tmp])) : to_string(map[tmp]);

				// 문자열 최대 저장 수를 넘어갈 경우 예외처리
				if (map.size() >= DICTIONARY_CAPACITY) {
#if DEBUG_LOG
					cout << "존재하는 단어지만 용량이 넘어감 : " << tmp << endl;
#endif
				} else {
#if DEBUG_LOG
					cout << "새 단어 추가 : [" << tmp + c << "], 인덱스 : " << index << endl;
#endif
					tmp += c;
					map[tmp] = index++;
				}
				tmp = c;
			}

			// 마지막 문자 처리
			if (i + 1 == length) {
				if (map.find(tmp) == map.end()) {
					cout <<"[" + tmp << "]단어가 사전에 없습니다. 일어날 수 없는일?" << endl;
					exit(0);
				}
				result += result.size() != 0 ? ("," + to_string(map[tmp])) : to_string(map[tmp]);
			}
		}

#if DEBUG_LOG
		cout << "인코딩 된 전체 문자열 : " << result << endl;

		cout << "만들어진 사전" << endl;
		for (pair<string, int> m : map) {
			cout << "인덱스 : " << m.second << ", 문자열 : [" << m.first << "]" << endl;
		}
#endif
		return result;
	}

	/// <summary> 받은 문자열을 디코딩한다. </summary>
	/// <param name="str"> 디코딩 대상 문자열 </param>
    /// <returns> 디코딩 완료된 문자열을 반환한다. </returns>
	string Decode(string str) {
		string result = "";
		int index = 0;

		vector<string> map;
		// vector 복사의 2가지 방법 : std::copy vs assign
		map.resize((int)mDic.size());
		copy(mDic.begin(), mDic.end(), map.begin());
		//map.clear();
		//map.assign(mDic.begin(), mDic.end());

		vector<string> target = split(str, ',');
		string prev = map[atoi(target[0].c_str())];
		string curr = "";

		result += prev;
		for (vector<string>::iterator iter = target.begin() + 1; iter < target.end(); iter++) {
			index = atoi((*iter).c_str());
			if (index >= map.size()) {
				cout << "[" + index << "]번째 단어가 사전에 없습니다. 일어날 수 없는일?" << endl;
				exit(0);
			}

			curr = map[index];
			result += curr;
			map.push_back(prev + curr[0]);
#if DEBUG_LOG
			cout << "디코딩 사전에 새 단어 추가 : [" << prev + curr[0] << "]" << endl;
#endif
			prev = curr;
		}

#if DEBUG_LOG
		cout << "디코딩 된 전체 문자열 : " << result << endl;

		cout << "만들어진 사전" << endl;
		index = 0;
		for (string str : map) {
			cout << "인덱스 : " << index++ << ", 문자열 : [" << str << "]" << endl;
		}
#endif
		return result;
	}
};

int main() {
	string input;

	cout << "렘펠지브웰치 알고리즘 테스트, 원하는 문자열을 입력 : ";
	cin >> input;

	LZWAlgorithm lzw;
	lzw.SetInitDic(input);

	string result = lzw.Encode(input);
	cout << "렘펠지브웰치 알고리즘 인코딩 결과 : " << result << endl;

	result = lzw.Decode(result);
	cout << "렘펠지브웰치 알고리즘 디코딩 결과 : " << result << endl;
}
