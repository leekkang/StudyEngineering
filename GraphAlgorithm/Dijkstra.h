#pragma once

#include <queue>

#include "Share.h"


void Dijkstra(std::vector<int>& dist, std::vector<int>& prev, const std::vector<GraphNode>& graph, int startNode = 0) {
	// 노드 개수 확인 == MakeSet
	int nodeCount = graph.size();

	// 버텍스 방문 확인용 배열
	std::vector<bool> visit(nodeCount, false);
	
	// 최초 시작 버텍스에서 각 버텍스 까지의 거리 초기화
	dist.resize(nodeCount, INT_MAX);
	prev.resize(nodeCount, -1);				// 최적 경로의 이전 버텍스 (경로 추적에 사용)
	
	dist[startNode] = 0;	// 시작 노드에서 시작 노드로 가는 거리는 0이다.


	// 모든 버텍스(+ 간선)를 다 확인할 때 까지 반복
	int visitCount = 0;
	while (visitCount < nodeCount) {
		int minCost = INT_MAX;
		int midNode = -1;
		// 시작 버텍스와 연결된 모든 버텍스 중 가장 가까운 버텍스를 중간 노드로 지정
		for (int i = 0; i < dist.size(); ++i) {
			if (!visit[i] && minCost >= dist[i]) {	//! dist가 INT_MAX인 경우에도 해당 조건문을 들어올 수 있게 이퀄 관계를 추가
				minCost = dist[i];
				midNode = i;
			}
		}
		visit[midNode] = true;
		++visitCount;

		// 중간 노드와 연결된 모든 버텍스들의 최단 거리 비교
		for (const auto& edge : graph[midNode].vecEdge) {
			const int& endNode = edge.first;
			const int& cost = edge.second;
			// 중간 노드를 경유해서 가는 경로가 저장된 최단 경로보다 짧다면 갱신
			if (dist[endNode] > dist[midNode] + cost) {
				dist[endNode] = dist[midNode] + cost;
				// 중간 노드 저장
				prev[endNode] = midNode;
			}
		}
	}
}


void DijkstraWithQueue(std::vector<int>& dist, std::vector<int>& prev, const std::vector<GraphNode>& graph, int srcNode = 0) {
	// 노드 개수 확인 == MakeSet
	int nodeCount = graph.size();
	
	// 최초 시작 버텍스에서 각 버텍스 까지의 거리 초기화
	dist.resize(nodeCount, INT_MAX);
	prev.resize(nodeCount, -1);				// 최적 경로의 이전 버텍스 (경로 추적에 사용)
	
	dist[srcNode] = 0;	// 시작 노드에서 시작 노드로 가는 거리는 0이다.

	// 우선순위 큐 초기화
	using pair = std::pair<int, int>;	// 가중치, 도착 노드
	std::priority_queue<pair, std::vector<pair>, std::greater<pair>> queue;
	queue.push(pair(0, srcNode));		// 최초 반복문 시작을 위해 추가


	// 모든 간선이 확인될 때 까지 출력
	while(!queue.empty()) {
		pair cur = queue.top();
		queue.pop();
		
		// 중간 노드 까지의 거리가 이전에 계산된 최단 거리보다 크면 스킵 (느긋한 삭제)
		const int& midNode = cur.second;
		if (cur.first > dist[midNode])
			continue;

		// 중간 노드와 연결된 모든 버텍스들의 최단 거리 비교
		for (const auto& edge : graph[midNode].vecEdge) {
			const int& endNode = edge.first;
			const int& cost = edge.second;
			// 중간 노드를 경유해서 가는 경로가 저장된 최단 경로보다 짧다면 갱신
			if (dist[endNode] > dist[midNode] + cost) {
				dist[endNode] = dist[midNode] + cost;
				// 중간 노드 저장
				prev[endNode] = midNode;
				// 우선순위 큐에 갱신된 최단 경로 추가 (겹쳐도 그냥 넣음. 위에서 삭제함)
				queue.push(pair(dist[endNode], endNode));
			}
		}
	}
}