#ifndef INTERFACE_H
#define INTERFACE_H
#pragma once
#include <windows.h>
#include <iostream>
#include <chrono>
#include <thread>
#include <fstream>
#include <string>
#include "Graph.h"

class UserInterface
{
	bool m_isGraph;

	void fromFile(std::string path);
	void graphMenu();

	void inputEdgeList(Graph& gr);
	void graphEdge(Graph& gr, bool add);
	void addGraphVertex(Graph& gr);
	void deleteGraphVertex(Graph& gr);

	void printGraph(Graph& gr);
	void FS(Graph& gr, bool BFS);
	void graphComponents(Graph& gr);
	void graphCutPoints(Graph& gr);
	void graphBridges(Graph& gr);
	void isGraphBipartite(Graph& gr);
	void graphTopSort(Graph& gr);

	void consoleClear();
	void wait();

public:
	void mainMenu();
	UserInterface();
};

#endif