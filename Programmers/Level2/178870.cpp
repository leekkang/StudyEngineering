
#include <iostream>

// https://school.programmers.co.kr/learn/courses/30/lessons/178870

#include <string>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> solution(vector<int> sequence, int k) {
    vector<int> answer;

	int size = sequence.size();
    while(sequence[size - 1] > k)
		--size;

	pair<int, int> result {-1, size};

    long long sum = sequence[size - 1];
    int count = 1;
	for (int i = size - 1; i >= 0; --i) {
		if (sum == k) {
			result = make_pair(i, 1);
			break;
		}

		while ((i - count) >= 0 && sum < k) {
			sum += sequence[i - count];
			++count;
		}

		if (sum == k) {
            result = make_pair(i - count + 1, count);
            break;
        }
            
        sum -= sequence[i];
        --count;
	}

    // 같은 수열 중 앞에 있는 것을 찾는다.
    int start = result.first - 1;
    while(start >= 0 && sequence[start] == sequence[start + result.second]) {
        --start;
    }
    result.first = start + 1;

	answer.push_back(result.first);
    answer.push_back(result.first + (result.second - 1));

    return answer;
}

int main() {
	vector<int> result = solution({2, 2, 2, 2, 2}, 6);

	for (int i = 0; i < result.size(); ++i) {
		cout << result[i];
	}
    cout << endl;

	return 0;
}