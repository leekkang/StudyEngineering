
#include <iostream>

// https://school.programmers.co.kr/learn/courses/30/lessons/181187?language=cpp

#include <string>
#include <vector>
#include "math.h"

using namespace std;

long long solution(int r1, int r2) {
    long long answer = 0;

	long long square1 = (long long)r1 * r1;
	long long square2 = (long long)r2 * r2;

	for (int i = 1; i < r2; ++i) {
		long long squareX = (long long)i * i;
		if (i < r1) {
			int boundary1 = (int)ceil(sqrtl(square1 - squareX));
			int boundary2 = (int)floor(sqrtl(square2 - squareX));
			answer += (boundary2 - boundary1 + 1);
		} else {
			answer += ((int)floor(sqrtl(square2 - squareX)) + 1);
		}
	}
	++answer;	// i == r2

	return answer * 4;
}

int main() {
	long long result = solution(1, 1000000);
	cout << result << endl;

	return 0;
}