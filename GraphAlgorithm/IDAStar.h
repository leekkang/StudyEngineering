#pragma once

#include <queue>
#include <functional>

#include "Share.h"


// 일반화한 IDA* 알고리즘 함수
int IDAStar(std::vector<int>& prev, const std::vector<GraphNode>& graph, std::function<void()> heuristic, int srcNode, int destNode) {
	return 0;
}


// 그래프 경로 찾기 특화 함수
int IDAStarGraph(std::vector<int>& path, const std::vector<GraphNode>& graph, int srcNode, int destNode) {
	// 노드 개수 확인 == MakeSet
	int nodeCount = graph.size();

	// 저장할 최단 경로 초기화. 스택처럼 사용한다.
	path.clear();
	int index = 0;		// 인덱스로 배열을 스택처럼 사용
	auto push = [&](int node) {
		if (index == path.size())
			path.push_back(node);
		else
			path[index] = node;
		++index;
	};
	auto pop = [&]() {
		if (index > 0)
			--index;
	};


	// 휴리스틱 함수. 그래프 경로의 경우 목적지 까지의 거리를 모르기 때문에 항상 0을 리턴한다.
	auto heuristic = [&](int index) -> int {
		return 0;
	};

	int result = 0;
	// DFS 를 하는 함수. 재귀형태이기 때문에 auto 타입은 사용하지 못한다.
	std::function<int(int, int, int)> search = [&](int curNode, int gScore, int threshold) -> int {
		int f = gScore + heuristic(curNode);
		if (f > threshold)			// 한계치보다 비용이 크면 바로 리턴
			return f;
		if (curNode == destNode)	// 찾았을 경우 알려주기 위해 0을 리턴
			return 0;

		int minCost = Infinity;
		// 자식 노드들을 돌면서 목적지 노드가 있는지 확인. 없으면 threshold를 변경하기 위해 최소값 (추정 최단 거리)을 리턴
		for (const auto& edge : graph[curNode].vecEdge) {
			const int& endNode = edge.first;
			// 이미 경로에 포함된 노드면 건너뛴다.
			bool found = false;
			for (int i = 0; i < index; ++i) {
				if (path[i] == endNode) {
					found = true;
					break;
				}
			}
			if (found)
				continue;

			// 경로에 집어넣고 확인한다.
			push(endNode);
			int cost = search(endNode, gScore + edge.second, threshold);
			// 찾았으면 0을 리턴
			if (cost == 0)
				return 0;
			if (cost < minCost)
				minCost = cost;
			pop();
		}
		return minCost;
	};

	// 결과 값을 찾을 때까지 반복
	int threshold = heuristic(srcNode);
	push(srcNode);
	while(true) {
		result = search(srcNode, 0, threshold);
		if (result == 0)
			break;
		if (result >= Infinity)
			break;
		threshold = result;
	}

	return result;
}