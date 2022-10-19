#pragma once

#include <algorithm>

#include "Share.h"

//! 현재 로직에서 음수 처리는 불가능하다
void FloydWarshall(std::vector<std::vector<int>>& dist, std::vector<std::vector<int>>& next, const std::vector<GraphNode>& graph) {
	// 노드 개수 확인 == MakeSet
	int size = graph.size();
	
	// 최초 각 버텍스 별 거리 배열, 경로 복원을 위한 배열 초기화
	dist.resize(size);
	next.resize(size);
	for (int i = 0; i < size; ++i) {
		dist[i].resize(size, INT_MAX);
		dist[i][i] = 0;					// 시작 노드에서 시작 노드로 가는 거리는 0이다.

		next[i].resize(size, -1);
	}

	// 최초 간선들을 최단 거리 배열에 추가한다.
	for (int i = 0; i < size; ++i) {
		int edgeSize = graph[i].vecEdge.size();
		for (int j = 0; j < edgeSize; ++j) {
			const auto& edge = graph[i].vecEdge[j];

			dist[i][edge.first] = edge.second;
			next[i][edge.first] = edge.first;		// 현재 최단 거리의 도착 노드를 저장한다.
		}
	}

	// 중간 노드(k)를 변경하면서 모든 노드들의 최단 거리를 갱신한다.
	for (int k = 0; k < size; ++k) {
		// 시작 노드(i), 도착 노드(j)
		for (int i = 0; i < size; ++i) {
			for (int j = 0; j < size; ++j) {
				//! 값의 범위를 벗어날 수 있어서 추가함. INT_MAX 대신 Share.h의 Infinity를 사용하면 해당 조건문을 지워도 된다.
				if (dist[i][k] == INT_MAX || dist[k][j] == INT_MAX)	
					continue;
				if (dist[i][j] > dist[i][k] + dist[k][j]) {
					dist[i][j] = dist[i][k] + dist[k][j];
					next[i][j] = next[i][k];		// 현재 저장되어 있는 도착 노드를 중간 노드로 변경한다.
				}
			}
		}
	}
}