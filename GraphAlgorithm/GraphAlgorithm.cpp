
#include <iostream>
#include <string>
#include <chrono>
#include <cmath>        // log, log10
#include <iomanip>      // input output manipulation (std::setw,...)
#include <functional>   // std::function

#include "Kruskal.h"
#include "Prim.h"
#include "Dijkstra.h"
#include "FloydWarshall.h"
#include "BellmanFord.h"
#include "AStar.h"
#include "IDAStar.h"

void ConvertMatrixToEdges(std::vector<GraphEdge>& edges, const std::vector<std::vector<int>>& matrix);
void ConvertMatrixToEdges(std::vector<GraphEdge>& edges, const std::vector<std::vector<int>>& matrix, const std::vector<std::string>& nodeNames);
void ConvertMatrixToEdgesDirected(std::vector<GraphEdge>& edges, const std::vector<std::vector<int>>& matrix, const std::vector<std::string>& nodeNames);
void ConvertMatrixToList(std::vector<GraphNode>& nodes, const std::vector<std::vector<int>>& matrix);
void ConvertMatrixToList(std::vector<GraphNode>& nodes, const std::vector<std::vector<int>>& matrix, const std::vector<std::string>& nodeNames);


// 경로 복원 후 포함된 노드를 출력
void PrintTrailedPath(int dest, const std::vector<int>& prev, const std::vector<std::string>& nodeNames);

// Minimun Spanning Tree 출력
void PrintSpanningTree(const std::vector<GraphEdge>& result, const std::string& name, const std::vector<std::string>& nodeNames);
// 단일 경로 출력
void PrintSingleResult(const std::vector<int>& prev, int src, int dest, int cost, const std::string& name, const std::vector<std::string>& nodeNames);
// 단일-출발 최단 경로들 출력
void PrintSinglePairResult(const std::vector<int>& dist, const std::vector<int>& prev,
						   const std::string& name, const std::vector<std::string>& nodeNames, int src);
// 전체-쌍 최단 경로들 출력
void PrintAllPairsResult(const std::vector<std::vector<int>>& dist, const std::vector<std::vector<int>>& next,
						 const std::string& name, const std::vector<std::string>& nodeNames);


int main() {
	// 랜덤 그래프 생성은 여기 참조 : https://en.wikipedia.org/wiki/Erd%C5%91s%E2%80%93R%C3%A9nyi_model
	// 에어디쉬-레니 모델, 와츠-스트로가츠 모델 등이 있다.
	constexpr int X = INT_MAX;

	// 그래프 모양은 링크 참조 : https://en.wikipedia.org/wiki/Kruskal%27s_algorithm

	std::vector<std::string> vecName {"A", "B", "C", "D", "E", "F", "G"};

	// 그래프 표현 방식 3가지 : Adjacency Matrix, Adjacency List, Edge List

	// 그래프 행렬 (Adjacency Matrix)
	std::vector<std::vector<int>> matrix = {
		{X, 7, X, 5, X, X, X},	// A
		{7, X, 8, 9, 7, X, X},	// B
		{X, 8, X, X, 5, X, X},	// C
		{5, 9, X, X, 15, 6, X},	// D
		{X, 7, 5, 15, X, 8, 9},	// E
		{X, X, X, 6, 8, X, 11},	// F
		{X, X, X, X, 9, 11, X},	// G
	};

	// 간선 배열 (Edge list)
	std::vector<GraphEdge> vecEdge;
	ConvertMatrixToEdgesDirected(vecEdge, matrix, vecName);

	// matrix 의 인접 리스트 (Adjacency List)
	std::vector<GraphNode> vecNode;
	ConvertMatrixToList(vecNode, matrix, vecName);

	// 버텍스의 이차원 좌표 (필요한 알고리즘의 경우 사용)
	std::vector<std::pair<int, int>> vecCoordinate {
		{0, 4},  // A
		{3, 3},  // B
		{6, 4},  // C
		{1, 0},  // D
		{5, 1},  // E
		{3, -1}, // F
		{6, -3}, // G
	};
	// 맨해튼 거리 + 유클리드 거리 휴리스틱 함수 (필요한 알고리즘의 경우 사용)
	auto heuristic = [&](int cur, int dest) -> int {
		if (cur == dest)
			return 0;
		int width = abs(vecCoordinate[cur].first - vecCoordinate[dest].first);
		int height = abs(vecCoordinate[cur].second - vecCoordinate[dest].second);
		return abs(width - height) * 10 + (width < height ? width : height) * 14;
	};

	constexpr bool bPrintGraph = false;

	if (bPrintGraph) {
		std::cout << "Graph Matrix\n";
		for (auto& v : matrix) {
			for (const auto& e : v) {
				std::cout << std::setw(5) << e;
			}
		}
		std::cout << "\n";
	}
	std::cout << std::endl;
	
	std::vector<GraphEdge> vecSpanningTree;
	// 단일-쌍 최단 경로 문제의 결과
	std::vector<int> vecSinglePairDist;
	std::vector<int> vecSinglePairPrevNode;				// 최단 경로 추적을 위한 중간 노드 배열 (최단 경로의 간선 중 마지막 간선의 시작 노드)
	// 전체-쌍 최단 경로 문제의 결과
	std::vector<std::vector<int>> vecAllPairsDist;
	std::vector<std::vector<int>> vecAllPairsNextNode;	// 최단 경로 추적을 위한 중간 노드 배열 (최단 경로의 간선 중 최초 간선의 도착 노드)

	int srcNode = 0;
	int destNode = 5;
	std::vector<std::pair<std::string, std::function<void()>>> algorithmPair{
		{"Kruskal", 		[&]() { Kruskal(vecSpanningTree, vecEdge); }},
		{"Prim", 			[&]() { Prim(vecSpanningTree, vecNode); }},
		{"PrimQueue", 		[&]() { PrimWithQueue(vecSpanningTree, vecNode); }},
		{"Dijkstra", 		[&]() { Dijkstra(vecSinglePairDist, vecSinglePairPrevNode, vecNode, srcNode); }},
		{"DijkstraQueue", 	[&]() { DijkstraWithQueue(vecSinglePairDist, vecSinglePairPrevNode, vecNode, srcNode); }},
		{"FloydWarshall", 	[&]() { FloydWarshall(vecAllPairsDist, vecAllPairsNextNode, vecNode); }},
		{"BellmanFord", [&]() { 
			if (!BellmanFord(vecSinglePairDist, vecSinglePairPrevNode, vecEdge))
				std::cout << "Error occured. Negative Edge Weight Cycles detected" << std::endl;
		}},
		{"AStarGraph", [&]() { 
			int cost = AStarGraph(vecSinglePairPrevNode, vecNode, srcNode, destNode);
			PrintSingleResult(vecSinglePairPrevNode, srcNode, destNode, cost, "AStarGraph", vecName);
			vecSinglePairPrevNode.clear();
		}},
		{"AStarCoordinate", [&]() { 
			int cost = AStarCoordinate(vecSinglePairPrevNode, vecNode, heuristic, srcNode, destNode);
			PrintSingleResult(vecSinglePairPrevNode, srcNode, destNode, cost, "AStarCoordinate", vecName);
			vecSinglePairPrevNode.clear();
		}},
		{"IDAStarGraph", [&]() {
			std::vector<int> path;
			int cost = IDAStarGraph(path, vecNode, srcNode, destNode);
			std::cout << "  Shortest Path : " << vecName[srcNode] << "-" << vecName[destNode] << ", cost : " << cost << std::endl;
			std::cout << "    Connected Node : ";
			for (int i = 0; i < path.size() - 1; ++i)
				std::cout << vecName[path[i]] << "-";
			std::cout << vecName[path[path.size() - 1]] << std::endl;
		}},
		{"IDAStarCoordinate", [&]() {
			std::vector<int> path;
			int cost = IDAStarCoordinate(path, vecNode, heuristic, srcNode, destNode);
			std::cout << "  Shortest Path : " << vecName[srcNode] << "-" << vecName[destNode] << ", cost : " << cost << std::endl;
			std::cout << "    Connected Node : ";
			for (int i = 0; i < path.size() - 1; ++i)
				std::cout << vecName[path[i]] << "-";
			std::cout << vecName[path[path.size() - 1]] << std::endl;
		}},
	};

	std::chrono::steady_clock::time_point src;
	for (const auto& pair : algorithmPair) {

		std::cout << "\n " << pair.first << " Algorithm Start\n";
		src = std::chrono::steady_clock::now();

		pair.second();

		if (vecSpanningTree.size()) {
			PrintSpanningTree(vecSpanningTree, pair.first, vecName);
			vecSpanningTree.clear();
		} else if (vecSinglePairDist.size()) {
			PrintSinglePairResult(vecSinglePairDist, vecSinglePairPrevNode, pair.first, vecName, srcNode);
			vecSinglePairDist.clear();
			vecSinglePairPrevNode.clear();
		} else if (vecAllPairsDist.size()) {
			PrintAllPairsResult(vecAllPairsDist, vecAllPairsNextNode, pair.first, vecName);
			vecAllPairsDist.clear();
			vecAllPairsNextNode.clear();
		}
			

		std::cout << "  Find Time : " << 
			std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now() - src).count() << " us\n";
		std::cout << "\n " << pair.first << " Algorithm End\n" << std::endl;
	}
}


// 경로 복원 후 포함된 노드를 출력
void PrintTrailedPath(int dest, const std::vector<int>& prev, const std::vector<std::string>& nodeNames) {
	int mid = prev[dest];
	std::vector<int> path;
	while (mid != -1) {
		path.push_back(mid);
		mid = prev[mid];
	}

	std::cout << "    Connected Node : ";
	for (int j = path.size() - 1; j >= 0; --j)
		std::cout << nodeNames[path[j]] << "-";
	std::cout << nodeNames[dest] << std::endl;
}

// Minimun Spanning Tree 출력
void PrintSpanningTree(const std::vector<GraphEdge>& result, const std::string& name, const std::vector<std::string>& nodeNames) {
	std::cout << "\n " << name << " Algorithm Result\n";
	int size = result.size();
	for (int i = 0; i < size; ++i) {
        std::cout << "  Connected Node : " << nodeNames[result[i].srcNode] << 
									   "-" << nodeNames[result[i].destNode] << ", cost : " << result[i].cost << std::endl;
	}
	std::cout << std::endl;
}
// 단일 경로 출력
void PrintSingleResult(const std::vector<int>& prev, int src, int dest, int cost, const std::string& name, const std::vector<std::string>& nodeNames) {
	std::cout << "  Shortest Path : " << nodeNames[src] << "-" << nodeNames[dest] << ", cost : " << cost << std::endl;
	PrintTrailedPath(dest, prev, nodeNames);
}
// 단일-출발 최단 경로들 출력
void PrintSinglePairResult(const std::vector<int>& dist, const std::vector<int>& prev, 
						   const std::string& name, const std::vector<std::string>& nodeNames, int src) {
	std::cout << "\n " << name << " Algorithm Result\n";
	int size = dist.size();
	for (int dest = 0; dest < size; ++dest) {
		if (dest == src || dist[dest] == INT_MAX)
			continue;

		std::cout << "  Shortest Path : " << nodeNames[src] << "-" << nodeNames[dest] << ", cost : " << dist[dest] << std::endl;
		PrintTrailedPath(dest, prev, nodeNames);
	}
	std::cout << std::endl;
}
// 전체-쌍 최단 경로들 출력
void PrintAllPairsResult(const std::vector<std::vector<int>>& dist, const std::vector<std::vector<int>>& next, 
						 const std::string& name, const std::vector<std::string>& nodeNames) {
	std::cout << "\n " << name << " Algorithm Result\n";
	int size = dist.size();
	for (int src = 0; src < size; ++src) {
		for (int dest = 0; dest < size; ++dest) {
			if (dest == src || dist[src][dest] == INT_MAX)
				continue;

			std::cout << "  Shortest Path : " << nodeNames[src] << "-" << nodeNames[dest] << ", cost : " << dist[src][dest] << std::endl;

			// 경로 복원
			int mid = next[src][dest];
			if (mid == -1)	// 위에서 체크하고 있지만(dest == src) 한번 더 체크
				continue;
			std::vector<int> path;
			path.push_back(src);
			while (mid != dest) {
				path.push_back(mid);
				mid = next[mid][dest];
			}

			std::cout << "    Connected Node : ";
			for (int j = 0; j < path.size(); ++j)
				std::cout << nodeNames[path[j]] << "-";
			std::cout << nodeNames[dest] << std::endl;
		}
	}
	std::cout << std::endl;
}


void ConvertMatrixToEdges(std::vector<GraphEdge>& edges, const std::vector<std::vector<int>>& matrix) {
	std::vector<std::string> nodeNames;
	int size = matrix.size();
	for (int i = 0; i < size; ++i)
		nodeNames.push_back(std::to_string(i));
		
	ConvertMatrixToEdges(edges, matrix, nodeNames);
}

void ConvertMatrixToEdges(std::vector<GraphEdge>& edges, const std::vector<std::vector<int>>& matrix, const std::vector<std::string>& nodeNames) {
	int size = matrix.size();
	if (nodeNames.size() != size) {
		std::cout << "Insufficient Node Name Number : " << nodeNames.size() << std::endl;
		return;
	}
	for (int i = 0; i < size; ++i) {
		auto& vecCost = matrix[i];
		if (vecCost.size() != size) {
			std::cout << "matrix is incorrect shape : " << i << std::endl;
			return;
		}
		for(int j = i + 1; j < size; ++j) {
			if (vecCost[j] == INT_MAX)
				continue;
			edges.push_back(GraphEdge(i, j, vecCost[j]));
		}
	}
}

void ConvertMatrixToEdgesDirected(std::vector<GraphEdge>& edges, const std::vector<std::vector<int>>& matrix, const std::vector<std::string>& nodeNames) {
	int size = matrix.size();
	if (nodeNames.size() != size) {
		std::cout << "Insufficient Node Name Number : " << nodeNames.size() << std::endl;
		return;
	}
	for (int i = 0; i < size; ++i) {
		auto& vecCost = matrix[i];
		if (vecCost.size() != size) {
			std::cout << "matrix is incorrect shape : " << i << std::endl;
			return;
		}
		for(int j = 0; j < size; ++j) {
			if (vecCost[j] == INT_MAX)
				continue;
			edges.push_back(GraphEdge(i, j, vecCost[j]));
		}
	}
}

void ConvertMatrixToList(std::vector<GraphNode>& nodes, const std::vector<std::vector<int>>& matrix) {
	std::vector<std::string> nodeNames;
	int size = matrix.size();
	for (int i = 0; i < size; ++i)
		nodeNames.push_back(std::to_string(i));
		
	ConvertMatrixToList(nodes, matrix, nodeNames);
}

void ConvertMatrixToList(std::vector<GraphNode>& nodes, const std::vector<std::vector<int>>& matrix, const std::vector<std::string>& nodeNames) {
	int size = matrix.size();
	if (nodeNames.size() != size) {
		std::cout << "Insufficient Node Name Number : " << nodeNames.size() << std::endl;
		return;
	}
	nodes.resize(size);
	for (int i = 0; i < size; ++i) {
		nodes[i].index = i;
		auto& vecCost = matrix[i];
		if (vecCost.size() != size) {
			std::cout << "matrix is incorrect shape : " << i << std::endl;
			return;
		}
		for(int j = 0; j < size; ++j) {
			if (vecCost[j] == INT_MAX)
				continue;
			nodes[i].vecEdge.push_back({j, vecCost[j]});
		}
	}
}