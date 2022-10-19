
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

void ConvertMatrixToEdges(std::vector<GraphEdge>& edges, const std::vector<std::vector<int>>& matrix);
void ConvertMatrixToEdges(std::vector<GraphEdge>& edges, const std::vector<std::vector<int>>& matrix, const std::vector<std::string>& nodeNames);
void ConvertMatrixToEdgesDirected(std::vector<GraphEdge>& edges, const std::vector<std::vector<int>>& matrix, const std::vector<std::string>& nodeNames);
void ConvertMatrixToList(std::vector<GraphNode>& nodes, const std::vector<std::vector<int>>& matrix);
void ConvertMatrixToList(std::vector<GraphNode>& nodes, const std::vector<std::vector<int>>& matrix, const std::vector<std::string>& nodeNames);


void PrintResult(const std::vector<GraphEdge>& result, const std::string& name, const std::vector<std::string>& nodeNames) {
	std::cout << "\n " << name << " Algorithm Result\n";
	int size = result.size();
	for (int i = 0; i < size; ++i) {
        std::cout << "  Connected Node : " << nodeNames[result[i].startNode] << 
									   "-" << nodeNames[result[i].endNode] << ", cost : " << result[i].cost << std::endl;
	}
	std::cout << std::endl;
}
void PrintSinglePairResult(const std::vector<int>& dist, const std::vector<int>& prev, 
						   const std::string& name, const std::vector<std::string>& nodeNames, int src) {
	std::cout << "\n " << name << " Algorithm Result\n";
	int size = dist.size();
	for (int dest = 0; dest < size; ++dest) {
		if (dest == src || dist[dest] == INT_MAX)
			continue;

		std::cout << "  Shortest Path : " << nodeNames[src] << "-" << nodeNames[dest] << ", cost : " << dist[dest] << std::endl;

		// 경로 복원
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
	std::cout << std::endl;
}
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


int main() {
	// 랜덤 그래프 생성은 여기 참조 : https://en.wikipedia.org/wiki/Erd%C5%91s%E2%80%93R%C3%A9nyi_model
	// 에어디쉬-레니 모델, 와츠-스트로가츠 모델 등이 있다.
	constexpr int X = INT_MAX;

	// 그래프 모양은 링크 참조 : https://en.wikipedia.org/wiki/Kruskal%27s_algorithm

	std::vector<std::string> nodeName {"A", "B", "C", "D", "E", "F", "G"};

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
	ConvertMatrixToEdgesDirected(vecEdge, matrix, nodeName);

	// matrix 의 인접 리스트 (Adjacency List)
	std::vector<GraphNode> vecNode;
	ConvertMatrixToList(vecNode, matrix, nodeName);

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
	
	std::vector<GraphEdge> vecResult;
	// 단일-쌍 최단 경로 문제의 결과
	std::vector<int> vecSinglePairDist;
	std::vector<int> vecSinglePairPrevNode;				// 최단 경로 추적을 위한 중간 노드 배열 (최단 경로의 간선 중 마지막 간선의 시작 노드)
	// 전체-쌍 최단 경로 문제의 결과
	std::vector<std::vector<int>> vecAllPairsDist;
	std::vector<std::vector<int>> vecAllPairsNextNode;	// 최단 경로 추적을 위한 중간 노드 배열 (최단 경로의 간선 중 최초 간선의 도착 노드)

	int startNode = 0;

	std::vector<std::pair<std::string, std::function<void()>>> algorithmPair{
		{"Kruskal", [&]() { Kruskal(vecResult, vecEdge); }},
		{"Prim", [&]() { Prim(vecResult, vecNode); }},
		{"PrimQueue", [&]() { PrimWithQueue(vecResult, vecNode); }},
		{"Dijkstra", [&]() { Dijkstra(vecSinglePairDist, vecSinglePairPrevNode, vecNode, startNode); }},
		{"DijkstraQueue", [&]() { DijkstraWithQueue(vecSinglePairDist, vecSinglePairPrevNode, vecNode, startNode); }},
		{"FloydWarshall", [&]() { FloydWarshall(vecAllPairsDist, vecAllPairsNextNode, vecNode); }},
		{"BellmanFord", [&]() { 
			if (!BellmanFord(vecSinglePairDist, vecSinglePairPrevNode, vecEdge))
				std::cout << "Error occured. Negative Edge Weight Cycles detected" << std::endl;
			}},
	};

	std::chrono::steady_clock::time_point start;
	for (const auto& pair : algorithmPair) {

		std::cout << "\n " << pair.first << " Algorithm Start\n";
		start = std::chrono::steady_clock::now();

		pair.second();

		if (vecResult.size()) {
			PrintResult(vecResult, pair.first, nodeName);
			vecResult.clear();
		} else if (vecSinglePairDist.size()) {
			PrintSinglePairResult(vecSinglePairDist, vecSinglePairPrevNode, pair.first, nodeName, startNode);
			vecSinglePairDist.clear();
			vecSinglePairPrevNode.clear();
		} else {
			PrintAllPairsResult(vecAllPairsDist, vecAllPairsNextNode, pair.first, nodeName);
			vecAllPairsDist.clear();
			vecAllPairsNextNode.clear();
		}
			

		std::cout << "  Find Time : " << 
			std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now() - start).count() << " us\n";
		std::cout << "\n " << pair.first << " Algorithm End\n" << std::endl;
	}
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