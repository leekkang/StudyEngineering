
#include <iostream>

// https://school.programmers.co.kr/learn/courses/30/lessons/181186?language=cpp

#include <string>
#include <vector>
#include "math.h"

using namespace std;

int solution(int n) {
	int answer = 0;
	vector<long long> vec(100001, 0);
	vec[1] = 1;
	vec[2] = 3;
	vec[3] = 10;
	vec[4] = 23;  // 10 + 2 * 3  + 5 * 1  + 2
	vec[5] = 62;  // 23 + 2 * 10 + 5 * 3  + 2 * 1 + 2 
	vec[6] = 170; // 62 + 2 * 23 + 5 * 10 + 2 * 3 + 2 * 1 + 4

	// 추가되는 패턴의 개수
	// 1, 2, 5, 2, 2, 4, 2, 2, 4 ...
	// f(x)     = f(x - 1) + 2 * f(x - 2) + 5 * f(x - 3) + 2 * f(x - 4) + 2 * f(x - 5) + 4 * f(x - 6) ...
	// f(x + 3) = f(x + 2) + 2 * f(x + 1) + 5 * f(x) + 2 * f(x - 1) + 2 * f(x - 2) + 4 * f(x - 3) ...
	// f(x + 3) - f(x) = f(x + 2) + 2 * f(x + 1) + 5 * f(x) + f(x - 1) - f(x - 3)

	// 최종식 : f(x + 3) = f(x + 2) + 2 * f(x + 1) + 6 * f(x) + f(x - 1) - f(x - 3)

	long long moduler = 1000000007;
	for (int i = 7; i <= n; ++i) {
		vec[i] = vec[i - 1] + vec[i - 2] * 2 + vec[i - 3] * 6 + vec[i - 4] - vec[i - 6];
		if (vec[i] > 0)
			vec[i] %= moduler;
		else {
			do {
				vec[i] += moduler;
			} while (vec[i] < 0);
		}
	}
	answer = (int)vec[n];

	return answer;
}

int main() {
	int result = solution(12345);
	cout << result << endl;

	return 0;
}