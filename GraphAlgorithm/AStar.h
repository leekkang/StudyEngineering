#pragma once

#include <queue>
#include <functional>

#include "Share.h"


// 이차원 좌표를 사용하는 A* 알고리즘 함수
int AStarCoordinate(std::vector<int>& prev, const std::vector<GraphNode>& graph, std::function<int(int, int)> heuristic, int srcNode, int destNode) {
	// 노드 개수 확인 == MakeSet
	int nodeCount = graph.size();
	
	// 최초 시작 버텍스에서 각 버텍스 까지의 거리 초기화
	std::vector<int> g(nodeCount, INT_MAX);
	prev.resize(nodeCount, -1);				// 최적 경로의 이전 버텍스 (경로 추적에 사용)
	
	g[srcNode] = 0;	// 시작 노드에서 시작 노드로 가는 거리는 0이다.

	// 우선순위 큐 초기화
	// f score 의 크기를 기준으로 정렬된다. f(n) = 현재 가중치 값 + 목적지 까지 추정 가중치 값
	using pair = std::pair<int, int>;	// 총 비용, 비용이 확정된 경로의 마지막 노드   (f(n), n)
	std::priority_queue<pair, std::vector<pair>, std::greater<pair>> queue;
	queue.push(pair(heuristic(srcNode, destNode), srcNode));		// 최초 반복문 시작을 위해 추가

	// 모든 간선이 확인될 때 까지 출력
	while(!queue.empty()) {
		pair cur = queue.top();
		queue.pop();
		
		const int& f = cur.first;
		int curNode = cur.second;
		// 목적지를 찾으면 반복문 종료
		if (curNode == destNode)
			break;

		int curCost = f - heuristic(curNode, destNode);
		// 중간 노드 까지의 거리가 이전에 계산된 최단 거리보다 크면 스킵 (느긋한 삭제)
		if (curCost > g[curNode])
			continue;

		// 중간 노드와 연결된 모든 버텍스들의 최단 거리 비교
		for (const auto& edge : graph[curNode].vecEdge) {
			const int& endNode = edge.first;
			const int& cost = edge.second;
			// 중간 노드를 경유해서 가는 경로가 저장된 최단 경로보다 짧다면 갱신
			if (g[endNode] > g[curNode] + cost) {
				g[endNode] = g[curNode] + cost;
				// 중간 노드 저장
				prev[endNode] = curNode;
				// 우선순위 큐에 갱신된 최단 경로 추가 (겹쳐도 그냥 넣음. 위에서 삭제함)
				queue.push(pair(g[endNode] + heuristic(endNode, destNode), endNode));
			}
		}
	}

	return g[destNode];
}


// 그래프 경로 찾기 특화 함수
int AStarGraph(std::vector<int>& prev, const std::vector<GraphNode>& graph, int srcNode, int destNode) {
	// 노드 개수 확인 == MakeSet
	int nodeCount = graph.size();
	
	// 최초 시작 버텍스에서 각 버텍스 까지의 거리 초기화
	std::vector<int> g(nodeCount, INT_MAX);
	prev.resize(nodeCount, -1);				// 최적 경로의 이전 버텍스 (경로 추적에 사용)
	
	g[srcNode] = 0;	// 시작 노드에서 시작 노드로 가는 거리는 0이다.

	// 휴리스틱 함수. 그래프 경로의 경우 목적지 까지의 거리를 모르기 때문에 항상 0을 리턴한다.
	auto heuristic = [&](int index) -> int {
		return 0;
	};

	// 우선순위 큐 초기화
	// f score 의 크기를 기준으로 정렬된다. f(n) = 현재 가중치 값 + 목적지 까지 추정 가중치 값
	using pair = std::pair<int, int>;	// 총 비용, 비용이 확정된 경로의 마지막 노드   (f(n), n)
	std::priority_queue<pair, std::vector<pair>, std::greater<pair>> queue;
	queue.push(pair(heuristic(srcNode), srcNode));		// 최초 반복문 시작을 위해 추가

	// 모든 간선이 확인될 때 까지 출력
	while(!queue.empty()) {
		pair cur = queue.top();
		queue.pop();
		
		const int& f = cur.first;
		int curNode = cur.second;
		// 목적지를 찾으면 반복문 종료
		if (curNode == destNode)
			break;

		int curCost = f - heuristic(curNode);
		// 중간 노드 까지의 거리가 이전에 계산된 최단 거리보다 크면 스킵 (느긋한 삭제)
		if (curCost > g[curNode])
			continue;

		// 중간 노드와 연결된 모든 버텍스들의 최단 거리 비교
		for (const auto& edge : graph[curNode].vecEdge) {
			const int& endNode = edge.first;
			const int& cost = edge.second;
			// 중간 노드를 경유해서 가는 경로가 저장된 최단 경로보다 짧다면 갱신
			if (g[endNode] > g[curNode] + cost) {
				g[endNode] = g[curNode] + cost;
				// 중간 노드 저장
				prev[endNode] = curNode;
				// 우선순위 큐에 갱신된 최단 경로 추가 (겹쳐도 그냥 넣음. 위에서 삭제함)
				queue.push(pair(g[endNode] + heuristic(endNode), endNode));
			}
		}
	}

	return g[destNode];
}