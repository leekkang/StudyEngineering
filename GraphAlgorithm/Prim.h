#pragma once

#include <algorithm>
#include <unordered_map>
#include <queue>

#include "Share.h"


void Prim(std::vector<GraphEdge>& result, const std::vector<GraphNode>& graph, int startNode = 0) {
	// 노드 개수 확인 == MakeSet
	int size = graph.size();

	// 트리에 포함된 버텍스 테이블. 트리에 포함되면 해당 인덱스 값이 true가 된다.
	std::vector<bool> vertexTable(size, false);
	vertexTable[startNode] = true; // 최초 트리 생성
	int count = 1;

	while(count < size) {
		int minCost = INT_MAX;
		int endNode = -1;
		// 현재 만들어진 트리에 있는 버텍스와 연결된 모든 간선중 가장 비용이 낮은 간선을 체크
		for (int j = 0; j < size; ++j) {
			// 연결되지 않은 버텍스임
			if (!vertexTable[j])
				continue;

			const std::vector<std::pair<int, int>>& edges = graph[j].vecEdge;
			for (int i = 0; i < edges.size(); ++i) {
				// 이미 연결된 정점이면 스킵
				if (vertexTable[edges[i].first])
					continue;
				// 최소 비용 검색
				if (minCost > edges[i].second) {
					minCost = edges[i].second;
					startNode = j;
					endNode = edges[i].first;
				}
			}
		}

		// 확인된 간선이 있을 경우 트리에 추가
		if (endNode != -1) {
			++count;
			vertexTable[endNode] = true;
			result.push_back(GraphEdge(startNode, endNode, minCost));
		} else {
			// 간선이 없는 버텍스가 존재함 -> 연결 그래프가 아니다
			break;
		}
	}

	if (count != size) {
		// 간선이 없는 버텍스가 존재함 -> 연결 그래프가 아니다
	}
}


void PrimWithQueue(std::vector<GraphEdge>& result, const std::vector<GraphNode>& graph, int startNode = 0) {
	// 노드 개수 확인 == MakeSet
	int size = graph.size();

	// 트리에 포함된 버텍스 테이블. 트리에 포함되면 해당 인덱스 값이 true가 된다.
	std::vector<bool> vertexTable(size, false);
	vertexTable[startNode] = true; // 최초 트리 생성
	int count = 1;

	// 우선순위 큐 초기화
	std::priority_queue<GraphEdge, std::vector<GraphEdge>, std::greater<GraphEdge>> queue;
	const std::vector<std::pair<int, int>>& edges = graph[startNode].vecEdge;
	// 큐에 간선 추가
	for (int i = 0; i < edges.size(); ++i)
		queue.push(GraphEdge(startNode, edges[i].first, edges[i].second));
	GraphEdge edge;

	while(count < size) {
		// 현재 만들어진 트리에 있는 버텍스와 연결된 모든 간선중 가장 비용이 낮은 간선을 체크
		while(queue.size() > 0) {
			edge = queue.top();
			// 트리에 없는 버텍스가 나올때까지 큐에서 빼냄
			if (vertexTable[edge.startNode] && vertexTable[edge.endNode])
				queue.pop();
			else {
				startNode = vertexTable[edge.startNode] ? edge.endNode : edge.startNode;
				break;
			}
		}
		if (queue.size() == 0) {
			// 간선이 없는 버텍스가 존재함 -> 연결 그래프가 아니다
			break;
		}

		// 확인된 간선이 있을 경우 트리에 추가
		++count;
		vertexTable[edge.startNode] = true;
		vertexTable[edge.endNode] = true;
		result.push_back(edge);
		
		// 새로 추가한 버텍스에 연결된 간선들을 큐에 추가
		const std::vector<std::pair<int, int>>& edges = graph[startNode].vecEdge;
		for (int i = 0; i < edges.size(); ++i) {
			// 이미 연결된 정점이면 스킵
			if (vertexTable[edges[i].first])
				continue;
			queue.push(GraphEdge(startNode, edges[i].first, edges[i].second));
		}
	}

	if (count != size) {
		// 간선이 없는 버텍스가 존재함 -> 연결 그래프가 아니다
	}
}