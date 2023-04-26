
#include <iostream>

// https://school.programmers.co.kr/learn/courses/30/lessons/176962
#include <string>
#include <vector>
#include <stack>
#include <queue>

using namespace std;

struct cmp {
	bool operator()(pair<int, int>& src, pair<int, int>& dest) {
		return src.first < dest.first;
	}
};

struct Task {
	int index = 0;
	int startTime = 0;
	int endTime = 0;

	bool operator <(const Task& s) const {
		return startTime > s.startTime;
	}
};

vector<string> solution(vector<vector<string>> plans) {
    vector<string> answer;

	priority_queue<Task> reserve;
	//priority_queue<pair<int, int>, vector<pair<int, int>, cmp>> reserve;
	stack<pair<int, int>> keep;	// 인덱스, 남은 시간

	Task task;
	int size = (int)plans.size();
	for(int i = 0; i < size; ++i) {
		task.index = i;
		task.startTime = stoi(plans[i][1]) * 60 + stoi(plans[i][1].data() + 3);
		task.endTime = task.startTime + stoi(plans[i][2]);
		reserve.push(task);
	}

	task = reserve.top();
	reserve.pop();
	Task newWork;
	
	while(!reserve.empty()) {
		newWork = reserve.top();
		reserve.pop();

		// 과제 못끝낸 경우
		if (task.endTime > newWork.startTime) {
			keep.push(make_pair(task.index, task.endTime - newWork.startTime));
		} else {
			// 끝내고 새로 과제 시작
			answer.push_back(plans[task.index][0]);
			int spaceTime = newWork.startTime - task.endTime;

			// 기존 과제 확인
			while (spaceTime > 0 && !keep.empty()) {
				pair<int, int>& oldWork = keep.top();
				if (oldWork.second > spaceTime) {
					oldWork.second -= spaceTime;
					break;
				} else {
					spaceTime -= oldWork.second;
					answer.push_back(plans[oldWork.first][0]);
					keep.pop();
				}
			}
		}
		task = newWork;
	}

	// 마지막 과제와 킵해놓은 과제
	answer.push_back(plans[task.index][0]);
	while(!keep.empty()) {
		answer.push_back(plans[keep.top().first][0]);
		keep.pop();
	}

    return answer;
}

int main() {
	vector<string> result = solution({{"science", "12:40", "50"},
									  {"music", "12:20", "40"},
									  {"history", "14:00", "30"},
									  {"computer", "12:30", "100"}});
	for (int i = 0; i < result.size(); ++i) {
		cout << result[i] << '\t';
	}
    cout << endl;

	return 0;
}