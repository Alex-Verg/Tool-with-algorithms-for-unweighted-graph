# Tool with algorithms for unweighted graph

This project is my course work on the topic "Algorithms on unweighted graphs" performed in the 1st year of my study in University.

## Description

In this application you can work in console with unweighted graphs. There are elementary tools for work with any graphs:
- create graph;
- add edge;
- add vertex;
- remove edge;
- remove vertex;
- print graph as adjacency list.

There are also two algorithm for searching a graph:
* Breadth-First Search ([BFS](https://en.wikipedia.org/wiki/Breadth-first_search));
* Depth-First Search ([DFS](https://en.wikipedia.org/wiki/Depth-first_search));

And the main part of this project is more applied algorithms:
- algorithm for finding connected components in graph (in directed graph strongly connected component). On of the searching is used for undirected graphs and [Kosaraju's algorithm](https://en.wikipedia.org/wiki/Kosaraju%27s_algorithm) is used for directed graph;
- finding [articulation points](https://www.geeksforgeeks.org/articulation-points-or-cut-vertices-in-a-graph/) in graphs;
- [bridge](https://en.wikipedia.org/wiki/Bridge_(graph_theory)#:~:text=In%20graph%20theory%2C%20a%20bridge,can%20uniquely%20determine%20a%20cut.)-finding algorithms;
- testing [bipartiteness](https://en.wikipedia.org/wiki/Bipartite_graph#:~:text=In%20the%20mathematical%20field%20of,the%20parts%20of%20the%20graph.) of graph;
- [topological sorting](https://en.wikipedia.org/wiki/Topological_sorting#:~:text=In%20computer%20science%2C%20a%20topological,before%20v%20in%20the%20ordering.) \(only for directed graphs\).

I used C++ language and tried to use my basic knowledge of OOP. 

## Instalation

Download this repository in separate folder and run file *mainProg.cpp* in some C++ compiler. Thera all other instructions inside the program.

## Usage

You can use my program to check the correctness of your own implementation of algorithms on unweighted graphs. Also you can learn some basic knowledge about graph and algorithms for work with it. All implementation of algorithms in this project were tested on the site [*eolymp.com*](https://www.eolymp.com/en/).

## Reference

You can learn more about graph and algorithms for in this good book:

Cormen, T., Leiserson, C., Rivest, R. and Stein, C., 2009. Introduction to Algorithm. 3rd ed. London , England: The MIT Press.
