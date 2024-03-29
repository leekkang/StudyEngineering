﻿#pragma once

#include <vector>

constexpr int Infinity = (int)(1 << (sizeof(int) * 8 - 2)) - 1;

struct GraphNode {
	int index = -1;
	std::vector<std::pair<int, int>> vecEdge;

	GraphNode(){}
    GraphNode(const GraphNode& node) : 
        index(node.index) {
		int size = node.vecEdge.size();
        for (int i = 0; i < size; ++i) {
			vecEdge.push_back(node.vecEdge[i]);
		}
	}
};

struct GraphEdge {
	int srcNode = -1;     // tail
	int destNode = -1;       // head
	int cost = INT_MAX;

	GraphEdge() {}
    GraphEdge(const GraphEdge& edge) : 
        srcNode(edge.srcNode),
        destNode(edge.destNode),
        cost(edge.cost) {
	}
    GraphEdge(int start, int end, int distance) : 
        srcNode(start),
        destNode(end),
        cost(distance) {
	}
    // GraphEdge& operator = (const GraphEdge& edge) {
	// 	node[0] = edge.node[0];
	// 	node[1] = edge.node[1];
	// 	cost = edge.cost;
	// 	return *this;
	// }

    bool operator == (const GraphEdge& edge) const {
		return this->cost == edge.cost;
	}
    bool operator != (const GraphEdge& edge) const {
		return this->cost != edge.cost;
	}
    bool operator < (const GraphEdge& edge) const {
		return this->cost < edge.cost;
	}
    bool operator > (const GraphEdge& edge) const {
		return this->cost > edge.cost;
	}
    bool operator <= (const GraphEdge& edge) const {
		return this->cost <= edge.cost;
	}
    bool operator >= (const GraphEdge& edge) const {
		return this->cost >= edge.cost;
	}
};
