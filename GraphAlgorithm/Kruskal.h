﻿#pragma once

#include <algorithm>

#include "Share.h"


void Kruskal(std::vector<GraphEdge>& result, const std::vector<GraphEdge>& graph) {
	std::vector<GraphEdge> edges(graph);
	std::sort(edges.begin(), edges.end());

	// 노드 개수 확인 == MakeSet
	int nodeCount = 0;
	for (const auto& edge : edges) {
		if (nodeCount < edge.srcNode)
			nodeCount = edge.srcNode;
		if (nodeCount < edge.destNode)
			nodeCount = edge.destNode;
	}
	++nodeCount;

	// 사이클 테이블
	std::vector<int> cycleTable(nodeCount);
	for (int i = 0; i < nodeCount; ++i) {
		cycleTable[i] = i;
	}

	// 사이클 체크용 함수 (서로소 집합 자료구조)
	std::function<int(int)> GetRoot = [&](int node) -> int {
		int& parent = cycleTable[node];
		if (parent == node)
			return node;
		parent = GetRoot(parent);
		return parent;
	};
	auto Union = [&](int src, int dest) {
		int srcRoot = GetRoot(src);
		int destRoot = GetRoot(dest);
		// 단순하게 인덱스가 작은 노드를 루트로 정한다
		if (srcRoot < destRoot)
			cycleTable[destRoot] = srcRoot;
		else
			cycleTable[srcRoot] = destRoot;
	};
	auto Find = [&](int src, int dest) -> bool {
		return GetRoot(src) ==  GetRoot(dest);
	};


	// 최소 신장 트리 찾기
	int size = edges.size();
	for (int i = 0; i < size; ++i) {
		int src = edges[i].srcNode;
		int dest = edges[i].destNode;

		if (!Find(src, dest)) {
			Union(src, dest);
			result.push_back(edges[i]);
		}
	}
}