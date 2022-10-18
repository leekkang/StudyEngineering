#pragma once

#include <algorithm>
#include <unordered_map>
#include <queue>

#include "Share.h"


void Dijkstra(std::vector<std::vector<GraphEdge>>& result, const std::vector<GraphNode>& graph, int startNode = 0) {
	// 노드 개수 확인 == MakeSet
	int size = graph.size();

	// 버텍스 방문 확인용 배열
	std::vector<bool> visit(size, false);
	
	// 최초 시작 버텍스에서 각 버텍스 까지의 거리 초기화
	std::vector<int> dist(size, INT_MAX - 1);
	std::vector<int> prev(size, -1);			// 최적 경로의 이전 버텍스 (필요하면 사용)
	
	dist[startNode] = 0;	// 시작 노드에서 시작 노드로 가는 거리는 0이다.


	// (출력용) 각 최단 거리에서 사용하는 간선들 저장
	result.resize(size);
	for (const auto& edge : graph[startNode].vecEdge)
		result[edge.first].push_back(GraphEdge(startNode, edge.first, edge.second));

	auto ResetDistEdges = [&](int dest, int mid, int midCost) {
		int count = result[mid].size();
		if (count == 0)
			return;
		result[dest].clear();
		for (int i = 0; i < count; ++i) {
			result[dest].push_back(result[mid][i]);
		}
		result[dest].push_back(GraphEdge(mid, dest, midCost));
	};


	// 모든 버텍스(+ 간선)를 다 확인할 때 까지 반복
	int visitCount = 0;
	while (visitCount < size) {
		int minCost = INT_MAX;
		int midNode = -1;
		// 시작 버텍스와 연결된 모든 버텍스 중 가장 가까운 버텍스를 중간 노드로 지정
		for (int i = 0; i < dist.size(); ++i) {
			if (!visit[i] && minCost > dist[i]) {
				minCost = dist[i];
				midNode = i;
			}
		}
		visit[midNode] = true;
		++visitCount;

		// 중간 노드와 연결된 모든 버텍스들의 최단 거리 비교
		for (const auto& edge : graph[midNode].vecEdge) {
			// 중간 노드를 경유해서 가는 경로가 저장된 최단 경로보다 짧다면 갱신
			if (dist[edge.first] > dist[midNode] + edge.second) {
				dist[edge.first] = dist[midNode] + edge.second;
				// 중간 노드 저장
				prev[edge.first] = midNode;

				// (출력용) 간선 리스트 갱신
				ResetDistEdges(edge.first, midNode, edge.second);
			}
		}
	}
}


void DijkstraWithQueue(std::vector<std::vector<GraphEdge>>& result, const std::vector<GraphNode>& graph, int startNode = 0) {
	// 노드 개수 확인 == MakeSet
	int size = graph.size();

	// 버텍스 방문 확인용 배열
	std::vector<bool> visit(size, false);
	
	// 최초 시작 버텍스에서 각 버텍스 까지의 거리 초기화
	std::vector<int> dist(size, INT_MAX - 1);
	std::vector<int> prev(size, -1);			// 최적 경로의 이전 버텍스 (필요하면 사용)
	
	dist[startNode] = 0;	// 시작 노드에서 시작 노드로 가는 거리는 0이다.

	// 우선순위 큐 초기화
	std::priority_queue<GraphEdge, std::vector<GraphEdge>, std::greater<GraphEdge>> queue;
	queue.push(GraphEdge(startNode, startNode, 0));	// 최초 반복문 시작을 위해 추가


	// (출력용) 각 최단 거리에서 사용하는 간선들 저장
	result.resize(size);
	for (const auto& edge : graph[startNode].vecEdge)
		result[edge.first].push_back(GraphEdge(startNode, edge.first, edge.second));
		
	auto ResetDistEdges = [&](int dest, int mid, int midCost) {
		int count = result[mid].size();
		if (count == 0)
			return;
		result[dest].clear();
		for (int i = 0; i < count; ++i) {
			result[dest].push_back(result[mid][i]);
		}
		result[dest].push_back(GraphEdge(mid, dest, midCost));
	};

	// 모든 간선이 확인될 때 까지 출력
	while(!queue.empty()) {
		GraphEdge cur = queue.top();
		queue.pop();
		
		// 중간 노드 - 목표 노드 까지의 거리가 이전에 계산된 최단 거리보다 크면 스킵
		if (cur.cost > dist[cur.endNode])
			continue;

		// 중간 노드와 연결된 모든 버텍스들의 최단 거리 비교
		for (const auto& edge : graph[cur.endNode].vecEdge) {
			// 중간 노드를 경유해서 가는 경로가 저장된 최단 경로보다 짧다면 갱신
			if (dist[edge.first] > dist[cur.endNode] + edge.second) {
				dist[edge.first] = dist[cur.endNode] + edge.second;
				// 중간 노드 저장
				prev[edge.first] = cur.endNode;
				// 우선순위 큐에 갱신된 최단 경로 추가
				queue.push(GraphEdge(startNode, edge.first, dist[edge.first]));

				// (출력용) 간선 리스트 갱신
				ResetDistEdges(edge.first, cur.endNode, edge.second);
			}
		}
	}
}