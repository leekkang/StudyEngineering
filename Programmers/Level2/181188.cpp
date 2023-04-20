
#include <iostream>

// https://school.programmers.co.kr/learn/courses/30/lessons/181188?language=cpp

#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int solution(vector<vector<int>> targets) {
	int answer = 0;

	// 끝점 기준 오름차순
	int size = (int)targets.size();
	if (size > 1)
		sort(targets.begin(), targets.end(), [](const vector<int>& src, const vector<int>& dest) {
			if (src[1] == dest[1])
				return src[0] < dest[0];
			return src[1] < dest[1];
		});

	int end = targets[0][1];
    ++answer;
	for (int i = 1; i < size; ++i) {
		if (end <= targets[i][0]) {
			end = targets[i][1];
			++answer;
		}
	}

	return answer;
}

int main() {
	int result = solution({{4, 5}, {4, 8}, {10, 14}, {11, 13}, {5, 12}, {3, 7}, {1, 4}});
	cout << result << endl;

	return 0;
}