
#include <iostream>

// https://school.programmers.co.kr/learn/courses/30/lessons/172927

#include <string>
#include <vector>

using namespace std;

void GetFatigue(int& min, int fatigue, int index, vector<int>& picks, vector<string>& minerals) {
    bool pick = false;
    for(int j = 0; j < 3; ++j) {
        if (picks[j] == 0) 
            continue;
        
        pick = true;
        --picks[j];
        
        int count = index + 5;
        int size = (int)minerals.size();
        while(index < count) {
            if (index >= size)
                break;

            if (minerals[index] == "diamond") {
                fatigue += (j == 0 ? 1 : j == 1 ? 5 : 25);
            } else if (minerals[index] == "iron") {
                fatigue += (j == 2 ? 5 : 1);
            } else {
                fatigue += 1;
            }
			++index;
		}
        
        if (index >= size) {
            if (min > fatigue)
                min = fatigue;
        } else {
            GetFatigue(min, fatigue, count, picks, minerals);
        }
            
        ++picks[j];
    }
    if (!pick)
        if (min > fatigue)
            min = fatigue;
}

int solution(vector<int> picks, vector<string> minerals) {
    int answer = 0;
    
    int min = INT_MAX;
    GetFatigue(min, 0, 0, picks, minerals);
    answer = min;
    
    return answer;
}

int main() {
	int result = solution({0, 1, 1}, {"diamond", "diamond", "diamond", "diamond", "diamond", "iron", "iron", "iron", "iron", "iron", "diamond"});
	cout << result << endl;

	return 0;
}