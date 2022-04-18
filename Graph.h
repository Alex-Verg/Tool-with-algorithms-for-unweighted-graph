#ifndef GRAPH_H
#define GRAPH_H
#pragma once
#include <vector>
#include <set>
#include <utility>
#include <queue>
#include <iostream>
#include <stack>

class Graph
{
	int m_vertexes;
	int m_edges;
	bool m_oriented;
	std::vector <std::set<int>> m_listAdjacency;
	std::set<int> m_deletedVertexes;

	std::vector<std::set<int>> stronglyConnected();
	std::vector<std::set<int>> weaklyConnected();
	bool topSortStep(int st_ver, std::vector<int>& visited, std::vector<int>& sort);
	void dfsCutPoint(int st_ver, std::vector<int>& visited, std::vector<int>& inTime,
		std::vector<int>& toComp, std::set<int>& cutPoints, int* timer, int p = -1);
	void dfsBridges(int st_ver, std::vector<int>& visited, std::vector<int>& inTime,
		std::vector<int>& toComp, std::set<std::pair<int, int>>& bridges, int* timer, int p = -1);

public:
	void inputGraph(int ver, int edg, const std::vector<std::pair<int, int>>& preList, int orient=0);
	bool addEdge(const std::pair<int, int>& edge);
	int addVertex();
	bool deleteEdge(const std::pair<int, int>& edge);
	bool deleteVertex(int vertex);

	void DFS(int start_v=1);
	void BFS(int start_v=1);

	std::vector<std::set<int>> componentsSearch();
	std::set<int> cutpointsSearch();
	std::set<std::pair<int, int>> bridgesSearch();
	

	std::vector<std::set<int>> isBepartite();
	std::vector<int> topologicalSort();

	void print();
	bool isOrient();
	Graph();
	//Graph(bool orient);
	~Graph();
};

#endif