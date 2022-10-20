#pragma once

#include "Share.h"

// Edge List 형태의 그래프를 사용한다. 리턴값이 false이면 음수 사이클이 존재한다는 뜻이다.
bool BellmanFord(std::vector<int>& dist, std::vector<int>& prev, const std::vector<GraphEdge>& graph, int srcNode = 0) {
	// 노드 개수 확인 == MakeSet
	int nodeCount = 0;
	for (const auto& edge : graph) {
		if (nodeCount < edge.startNode)
			nodeCount = edge.startNode;
		if (nodeCount < edge.endNode)
			nodeCount = edge.endNode;
	}
	++nodeCount;
	
	// 최초 시작 버텍스에서 각 버텍스 까지의 거리 초기화
	dist.resize(nodeCount, INT_MAX);
	prev.resize(nodeCount, -1);				// 최적 경로의 이전 버텍스 (경로 추적에 사용)
	
	dist[srcNode] = 0;	// 시작 노드에서 시작 노드로 가는 거리는 0이다.

	int edgeCount = graph.size();
	for (int i = 0; i < nodeCount; ++i) {
		for (int j = 0; j < edgeCount; ++j) {
			const auto& edge = graph[j];
			//! 값의 범위를 벗어날 수 있어서 추가함. INT_MAX 대신 Share.h의 Infinity를 사용하면 해당 조건문을 지워도 된다.
			if (dist[edge.startNode] == INT_MAX)	
				continue;

			if (dist[edge.endNode] > dist[edge.startNode] + edge.cost) {
				dist[edge.endNode] = dist[edge.startNode] + edge.cost;
				// 중간 노드 저장
				prev[edge.endNode] = edge.startNode;
			}
		}
	}

	// 음수 사이클이 있는지 확인
	for (int j = 0; j < edgeCount; ++j) {
		const auto& edge = graph[j];
		//! 값의 범위를 벗어날 수 있어서 추가함. INT_MAX 대신 Share.h의 Infinity를 사용하면 해당 조건문을 지워도 된다.
		if (dist[edge.startNode] == INT_MAX)	
			continue;
			
		if (dist[edge.endNode] > dist[edge.startNode] + edge.cost) {
			return false;
		}
	}

	return true;
}