#include "Graph.h"
#include <Windows.h>


std::vector<std::set<int>> Graph::stronglyConnected()
{
	std::vector<int> visited(m_vertexes + 1, 0);
	std::vector<std::set<int>> components;
	int count_comp = 0, cur_v, i;
	std::stack<int> ver_stack;
	std::stack<int> order;

	for (i = 1; i < m_vertexes + 1; i++) {
		if ((visited[i] == 0) && (m_deletedVertexes.find(i) == m_deletedVertexes.end())) {
			ver_stack.push(i);
			while (!ver_stack.empty()) {
				cur_v = ver_stack.top();
				if (visited[cur_v] == 0) {
					visited[cur_v] = 1;
					for (auto j = m_listAdjacency[cur_v].rbegin(); j != m_listAdjacency[cur_v].rend(); j++) {
						if (visited[*j] == 0) ver_stack.push(*j);
					}
				}
				else if (visited[cur_v] == 1) {
					visited[cur_v] = 2;
					ver_stack.pop();
					order.push(cur_v);
				}
				else if (visited[cur_v] == 2) ver_stack.pop();
			}
		}
	}

	std::vector<std::set<int>> invertGraph;
	invertGraph.resize(m_vertexes + 1);
	for (i = 1; i < m_vertexes + 1; i++) {
		for (auto j : m_listAdjacency[i]) invertGraph[j].insert(i);
	}

	visited.clear();
	visited.resize(m_vertexes + 1);

	while (!order.empty()) {
		cur_v = order.top();
		order.pop();
		if (visited[cur_v] == 0) {
			count_comp++;
			components.resize(count_comp);
			ver_stack.push(cur_v);
			components[count_comp - 1].insert(cur_v);
			while (!ver_stack.empty()) {
				cur_v = ver_stack.top();
				if (visited[cur_v] == 0) {
					visited[cur_v] = 1;
					for (auto j = invertGraph[cur_v].rbegin(); j != invertGraph[cur_v].rend(); j++) {
						if (visited[*j] == 0) {
							ver_stack.push(*j);
							components[count_comp - 1].insert(*j);
						}
					}
				}
				else if (visited[cur_v] == 1) {
					visited[cur_v] = 2;
					ver_stack.pop();
				}
				else if (visited[cur_v] == 2) ver_stack.pop();
			}
		}
	}

	return components;
}									//FIX

std::vector<std::set<int>> Graph::weaklyConnected()
{
	std::vector<bool> visit(m_vertexes + 1, false);
	std::vector<std::set<int>> components;
	int count_comp = 0, cur_v;
	std::queue<int> ver_que;
	for (int i = 1; i < m_vertexes + 1; i++) {
		if ((!visit[i]) && (m_deletedVertexes.find(i) == m_deletedVertexes.end())) {
			count_comp++;
			components.resize(count_comp);
			ver_que.push(i);
			visit[i] = true;
			while (!ver_que.empty()) {
				cur_v = ver_que.front();
				ver_que.pop();
				components[count_comp - 1].insert(cur_v);
				for (auto neighbour : m_listAdjacency[cur_v]) {
					if (!visit[neighbour]) {
						visit[neighbour] = true;
						ver_que.push(neighbour);
					}
				}
			}
		}
	}
	visit.clear();

	return components;
}

bool Graph::topSortStep(int st_ver, std::vector<int>& visited, std::vector<int>& sort)
{
	if (visited[st_ver] == 0) {
		visited[st_ver] = 1;
		for (auto j : m_listAdjacency[st_ver]) {
			if (!topSortStep(j, visited, sort)) return false;
		}
		visited[st_ver] = 2;
		sort.push_back(st_ver);
		return true;
	}
	else if (visited[st_ver] == 1) return false;
	else if (visited[st_ver] == 2) return true;
}

void Graph::dfsCutPoint(int st_ver, std::vector<int>& visited, std::vector<int>& inTime, std::vector<int>& toComp, std::set<int>& cutPoints, int* timer, int p)
{
	visited[st_ver] = 1;
	inTime[st_ver] = toComp[st_ver] = (*timer)++;
	int children = 0;
	for (auto j : m_listAdjacency[st_ver]) {
		if (j == p) continue;
		if (visited[j]) toComp[st_ver] = (toComp[st_ver] < inTime[j]) ? toComp[st_ver] : inTime[j];
		else {
			dfsCutPoint(j, visited, inTime, toComp, cutPoints, timer, st_ver);
			toComp[st_ver] = (toComp[st_ver] < toComp[j]) ? toComp[st_ver] : toComp[j];
			if (inTime[st_ver] <= toComp[j] && p != -1) cutPoints.insert(st_ver);
			children++;
		}
	}
	if (p == -1 && children > 1) cutPoints.insert(st_ver);
}

void Graph::dfsBridges(int st_ver, std::vector<int>& visited, std::vector<int>& inTime, std::vector<int>& toComp, std::set<std::pair<int, int>>& bridges, int* timer, int p)
{
	visited[st_ver] = 1;
	inTime[st_ver] = toComp[st_ver] = (*timer)++;
	for (auto j : m_listAdjacency[st_ver]) {
		if (j == p) continue;
		if (visited[j]) toComp[st_ver] = (toComp[st_ver] < inTime[j]) ? toComp[st_ver] : inTime[j];
		else {
			dfsBridges(j, visited, inTime, toComp, bridges, timer, st_ver);
			toComp[st_ver] = (toComp[st_ver] < toComp[j]) ? toComp[st_ver] : toComp[j];
			if (inTime[st_ver] < toComp[j]) {
				if (st_ver < j) bridges.insert(std::make_pair(st_ver, j));
				else bridges.insert(std::make_pair(j, st_ver));
			}
		}
	}
}

void Graph::inputGraph(int ver, int edg, const std::vector<std::pair<int, int>>& preList, int orient)
{	
	m_deletedVertexes.clear();
	m_listAdjacency.clear();
	m_edges = 0;
	m_oriented = (bool)orient;
	m_vertexes = ver;
	m_listAdjacency.resize(m_vertexes+1);
	std::pair <int, int> cur_edge;
	for (int i = 0; i < preList.size(); i++) {
		cur_edge = preList[i];
		addEdge(cur_edge);
	}
}

bool Graph::addEdge(const std::pair<int, int>& edge)
{
	//Якщо вершин в графі нема, то ребро не додається
	if ((edge.first > m_vertexes) || (edge.second > m_vertexes) || 
		(m_deletedVertexes.find(edge.first) != m_deletedVertexes.end()) || 
		(m_deletedVertexes.find(edge.second) != m_deletedVertexes.end()) ||
		(m_listAdjacency[edge.first].find(edge.second) != m_listAdjacency[edge.first].end())) return false;
	
	if (m_listAdjacency[edge.first].find(edge.second) == m_listAdjacency[edge.first].end()) {
		(m_listAdjacency[edge.first]).insert(edge.second);
		m_edges++;
	}
	
	if (!m_oriented) m_listAdjacency[edge.second].insert(edge.first);
	return true;
}

int Graph::addVertex()
{
	m_vertexes++;
	m_listAdjacency.resize(m_vertexes + 1);
	return m_vertexes;
}

bool Graph::deleteEdge(const std::pair<int, int>& edge)
{
	//Якщо вершин в графі нема, то ребро не видаляється
	if ((edge.first > m_vertexes) || (edge.second > m_vertexes) ||
		(m_deletedVertexes.find(edge.first) != m_deletedVertexes.end()) ||
		(m_deletedVertexes.find(edge.second) != m_deletedVertexes.end()) ||
		(m_listAdjacency[edge.first].find(edge.second) == m_listAdjacency[edge.first].end())) return false;

	m_listAdjacency[edge.first].erase(edge.second);
	m_edges--;

	//Якщо граф неорінтований видаляється суміжність для двох вершин
	if (!m_oriented) m_listAdjacency[edge.second].erase(edge.first);

	return true;
}

bool Graph::deleteVertex(int vertex)
{
	//Якщо вершини нема, то вона не видаляється
	if ((vertex > m_vertexes + 1) || (m_deletedVertexes.find(vertex) != m_deletedVertexes.end())) return false;

	//Якщо граф неорінтований достатньо видалити вершини із списків суміжності суміжних з нею вершин
	if (!m_oriented) {												
		for (auto i : m_listAdjacency[vertex]) {
			if (m_deletedVertexes.find(i) == m_deletedVertexes.end()) m_listAdjacency[i].erase(vertex);
		}
	}																	
	//Якщо граф орінтований необхідно передбачити можливе видалення із списків суміжності усіх вершин графа
	else {
		for (int i = 1; i < m_vertexes + 1; i++) {
			if (m_deletedVertexes.find(i) == m_deletedVertexes.end()) {
				if (m_listAdjacency[i].find(vertex) != m_listAdjacency[i].end()) {
					m_listAdjacency[i].erase(vertex);
					m_edges--;
				}
			}
		} 
	}
	m_edges -= m_listAdjacency[vertex].size();
	m_listAdjacency[vertex].clear();
	m_deletedVertexes.insert(vertex);
	return true;
}

void Graph::DFS(int start_v)
{
	std::vector<byte> visited(m_vertexes + 1, 0);
	int count_comp = 0, cur_v;
	std::stack<int> ver_stack;
	if (m_deletedVertexes.find(start_v) == m_deletedVertexes.end() && start_v < m_vertexes && start_v > 0) std::cout << "Обхід в глибину починаючи з вершини " << start_v;
	else std::cout << "Обхід в глибину починаючи з вершини " << start_v <<
		" неможливий," << std::endl << "бо вона відсутня, тому обхід почнеться з наступної доступної вершини";

	for (int i = 0; i < m_vertexes + 1; i++) {
		if ((visited[i] == 0) && (m_deletedVertexes.find(i) == m_deletedVertexes.end())) {
			if (!i) {
				if (m_deletedVertexes.find(start_v) != m_deletedVertexes.end() || start_v > m_vertexes || start_v<0) continue;
				ver_stack.push(start_v);
			}
			else ver_stack.push(i);
			count_comp++;
			std::cout << std::endl << std::endl << "Обхід зі спроби №" << count_comp << std::endl;

			while (!ver_stack.empty()){
				cur_v = ver_stack.top();
				if (visited[cur_v] == 0) {
					visited[cur_v] = 1;
					std::cout << cur_v << " ";
					for (auto j = m_listAdjacency[cur_v].rbegin(); j != m_listAdjacency[cur_v].rend(); j++) {
						if (visited[*j] == 0) ver_stack.push(*j);
					}
				}
				else if (visited[cur_v] == 1) { 
					visited[cur_v] = 2; 
					ver_stack.pop();
				}
				else if (visited[cur_v] == 2) ver_stack.pop();
			}
		}
	}
	visited.clear();
}

void Graph::BFS(int start_v)
{
	std::vector<int> distance(m_vertexes + 1, -1);
	int count_comp = 0, cur_v, cur_len = 0;
	std::queue<int> ver_que;
	if (m_deletedVertexes.find(start_v) == m_deletedVertexes.end() && start_v < m_vertexes && start_v > 0) std::cout << "Обхід в ширину починаючи з вершини " << start_v;
	else std::cout << "Обхід в ширину починаючи з вершини " << start_v << 
		" неможливий, бо вона відсутня, тому обхід почнеться з наступної доступної вершини";

	for (int i = 0; i < m_vertexes + 1; i++) {
		if ((distance[i] == -1) && (m_deletedVertexes.find(i) == m_deletedVertexes.end())) {
			if (!i) {
				if (m_deletedVertexes.find(start_v) != m_deletedVertexes.end() || start_v > m_vertexes || start_v < 0) continue;
				ver_que.push(start_v);
				distance[start_v] = 0;
			}
			else {
				ver_que.push(i);
				distance[i] = 0;
			}
			count_comp++;
			cur_len = 0;
			std::cout << std::endl << std::endl << "Обхід зі спроби №" << count_comp << std::endl <<
				"Початкова вершини обходу при спробі:" << std::endl;

			while (!ver_que.empty()) {
				cur_v = ver_que.front();
				ver_que.pop();
				if (distance[cur_v] > cur_len) {
					cur_len++;
					std::cout << std::endl << "Вершини, які від початкової вершини доступні на відстані " << cur_len << ":" << std::endl;
				}
				std::cout << cur_v << " ";
				for (auto neighbour : m_listAdjacency[cur_v]) {
					if (distance[neighbour] == -1) {
						distance[neighbour] = distance[cur_v] + 1;
						ver_que.push(neighbour);
					}
				}
			}
		}
	}
	distance.clear();
	std::cout << std::endl;
}

std::vector<std::set<int>> Graph::componentsSearch()
{
	if (m_oriented) return stronglyConnected();
	else return weaklyConnected();
}

std::set<int> Graph::cutpointsSearch()
{
	std::vector<int> visited(m_vertexes + 1, 0);
	std::vector<int> inTime(m_vertexes + 1, 0);
	std::vector<int> toComp(m_vertexes + 1, 0);
	std::set<int> cutPoints;

	int timer = 0;

	for (int i = 1; i < m_vertexes + 1; i++) {
		if (!visited[i] && (m_deletedVertexes.find(i) == m_deletedVertexes.end()))
			dfsCutPoint(i, visited, inTime, toComp, cutPoints, &timer);
	}

	return cutPoints;
}

std::set<std::pair<int, int>> Graph::bridgesSearch()
{
	std::vector<int> visited(m_vertexes + 1, 0);
	std::vector<int> inTime(m_vertexes + 1, 0);
	std::vector<int> toComp(m_vertexes + 1, 0);
	std::set<std::pair<int, int>> bridges;

	int timer = 0;

	for (int i = 1; i < m_vertexes + 1; i++) {
		if (!visited[i] && (m_deletedVertexes.find(i) == m_deletedVertexes.end()))
			dfsBridges(i, visited, inTime, toComp, bridges, &timer);
	}

	return bridges;
}

std::vector<std::set<int>> Graph::isBepartite()
{
	std::vector<int> visit(m_vertexes + 1, 0);
	std::vector<std::set<int>> parts(2);
	int cur_v;
	std::queue<int> ver_que;

	for (int i = 1; i < m_vertexes + 1; i++) {
		if ((!visit[i]) && (m_deletedVertexes.find(i) == m_deletedVertexes.end())) {
			ver_que.push(i);
			visit[i] = 1;
			while (!ver_que.empty()) {
				cur_v = ver_que.front();
				ver_que.pop();
				if (visit[cur_v] == 1) parts[1].insert(cur_v);
				else if (visit[cur_v] == -1) parts[0].insert(cur_v);
				
				for (auto neighbour : m_listAdjacency[cur_v]) {
					if (visit[neighbour] == 0) {
						visit[neighbour] = -1 * visit[cur_v];
						ver_que.push(neighbour);
					}
					else if (visit[neighbour] == visit[cur_v]) {
						parts.clear();
						return parts;
					}
				}
			}
		}
	}
	visit.clear();

	return parts;
}

std::vector<int> Graph::topologicalSort()
{
	std::vector<int> visited(m_vertexes + 1, 0);
	std::vector<int> sort;
		
	for (int i = 1; i < m_vertexes + 1; i++) {
		if (m_deletedVertexes.find(i) == m_deletedVertexes.end()) {
			if (!topSortStep(i, visited, sort)) {
				sort.clear();
				return sort;
			};
		}
	}
	visited.clear();
	return sort;
}

void Graph::print()
{
	//Print graph as List of Adjacency
	std::cout << "Граф має " << m_vertexes - m_deletedVertexes.size();
	if ((m_vertexes - m_deletedVertexes.size()) > 10 && (m_vertexes - m_deletedVertexes.size()) < 20) std::cout << " вершин та ";
	else {
		switch ((m_vertexes - m_deletedVertexes.size()) % 10)
		{
		case 1: {std::cout << " вершину та ";  break; }
		case 2: {std::cout << " вершини та ";  break; }
		case 3: {std::cout << " вершини та ";  break; }
		case 4: {std::cout << " вершини та ";  break; }
		case 11: {std::cout << " вершин та ";  break; }
		case 12: {std::cout << " вершин та ";  break; }
		case 13: {std::cout << " вершин та ";  break; }
		case 14: {std::cout << " вершин та ";  break; }
		default: {std::cout << " вершин та ";  break; }
		}
	}
	
	std::cout << m_edges;
	if (m_edges > 10 && m_edges < 20) std::cout << " ребер.";
	else {
		switch (m_edges % 10)
		{
		case 1: {std::cout << " ребро.";  break; }
		case 2: {std::cout << " ребра.";  break; }
		case 3: {std::cout << " ребра.";  break; }
		case 4: {std::cout << " ребра.";  break; }
		default: {std::cout << " ребер.";  break; }
		}
	}
	
	std::cout << "\nСписок суміжності графа:\n";
	for (int cur_v = 1; cur_v < m_listAdjacency.size(); cur_v++) {
		if (m_deletedVertexes.find(cur_v) == m_deletedVertexes.end()) {
			std::cout << cur_v << ": ";
			for (auto neighbour : m_listAdjacency[cur_v]) {
				std::cout << neighbour << ", ";
			}
			std::cout << "\b\b;\n";
		}
	}
	std::cout << "Кінець списку суміжності." << std::endl;
}

bool Graph::isOrient()
{
	return m_oriented;
}

Graph::Graph()
{
	this->m_oriented = false;
	this->m_vertexes = 0;
	this->m_edges = 0;
	this->m_listAdjacency.resize(0);
	this->m_deletedVertexes;
}

/*Graph::Graph(bool orient)
{
	m_oriented = orient;
	m_vertexes = 0;
	m_edges = 0;
}*/

Graph::~Graph()
{
	for (int i = 0; i < m_listAdjacency.size(); i++) {
		m_listAdjacency.at(i).clear();
	}
	this->m_listAdjacency.clear();
	this->m_deletedVertexes.clear();
}
