/*
 * Author: Alexandre Lepage
 * Date: March 2020
 */
#pragma once

#include "AbstractGraph.h"
#include <queue>

 /// <summary>
 /// Custom ListGraph class for graph algorithms
 /// </summary>
class ListGraph : public AbstractGraph
{
public:
	std::vector<Vertex*>* adjacencyList; //The adjacency list for the vertices.

	ListGraph(std::initializer_list<int> keys); // Constructor
	ListGraph(std::vector<int> keys); // Constructor
	ListGraph(int keys[], int arraySize); // Constructor
	~ListGraph();

	void AddEdge(int sourceKey, int destinationKey) override;
	void BreadthFirstSearch(int sourceKey) override;
	void DepthFirstSearch() override;
	bool BellmanFord(int sourceKey) override;
	void Dijkstra(int sourceKey) override;
	void AStar(int sourceKey) override;
	void PrintEdges();
};

/// <summary>
/// Class constructor
/// -----PSEUDO CODE-----
/// (G is the graph, Keys is the graph vertices' keys)
/// ListGraph(G,Keys)
///	 AbstractGraph(G,Keys)
///  let adjacencyList be a new list of (G.maxKey - G.minKey + 1) size
/// -----PSEUDO CODE-----
/// </summary>
/// <param name="keys">list of keys of the vertices to add to the graph</param>
ListGraph::ListGraph(std::initializer_list<int> keys) : AbstractGraph(keys)
{
	adjacencyList = new std::vector<Vertex*>[maxKey - minKey + 1];
}

/// <summary>
/// Class constructor
/// -----PSEUDO CODE-----
/// (G is the graph, Keys is the graph vertices' keys)
/// ListGraph(G,Keys)
///	 AbstractGraph(G,Keys)
///  let adjacencyList be a new list of (G.maxKey - G.minKey + 1) size
/// -----PSEUDO CODE-----
/// </summary>
/// <param name="keys">list of keys of the vertices to add to the graph</param>
ListGraph::ListGraph(std::vector<int> keys) : AbstractGraph(keys)
{
	adjacencyList = new std::vector<Vertex*>[maxKey - minKey + 1];
}

/// <summary>
/// Class constructor
/// -----PSEUDO CODE-----
/// (G is the graph, Keys is the array of graph vertices' keys, aSize is size of the array)
/// ListGraph(G,Keys)
///	 AbstractGraph(G,Keys)
///  let adjacencyList be a new list of (G.maxKey - G.minKey + 1) size
/// -----PSEUDO CODE-----
/// </summary>
/// <param name="keys">array of the keys of the vertices to add to the graph</param>
/// <param name="arraySize">size of the array</param>
ListGraph::ListGraph(int keys[], int arraySize) : AbstractGraph(keys, arraySize)
{
	adjacencyList = new std::vector<Vertex*>[maxKey - minKey + 1];
}

/// <summary>
/// Class deconstructor
/// -----PSEUDO CODE-----
/// ~ListGraph(G)
///  delete adjacencyList
/// -----PSEUDO CODE-----
/// </summary>
ListGraph::~ListGraph()
{
	delete[] adjacencyList;
}

/// <summary>
/// Add an edge to a vertex
/// -----PSEUDO CODE-----
/// AddEdge(G,sK,dK)
///  dV = NIL
///  for each v in G.vertices
///		if v.key == dK.key
///			dV = v
///  if dV =/= NIL
///		G.adjacencyList[sK - G.minKey].add(dV)
/// -----PSEUDO CODE-----
/// </summary>
/// <param name="sourceKey">source key</param>
/// <param name="destinationKey">destination key</param>
void ListGraph::AddEdge(int sourceKey, int destinationKey)
{
	auto destination = find_if(vertices.begin(), vertices.end(), [destinationKey](Vertex v) {return v.key == destinationKey; });
	if (destination != vertices.end())
	{
		adjacencyList[sourceKey - minKey].push_back(destination._Ptr);
	}
}

/// <summary>
/// This is populate the predecessors from the keys that leads to the source key
/// -----PSEUDO CODE-----
/// (G is the Graph, s is the source vertex)
/// BFS(G,s)
///  for each vertex u in G.V
///     u.color = WHITE
///     u.distance = INFINITY
///     u.predecessor = NIL
///  s.color = GRAY
///  s.distance = 0
///  s.predecessor = NIL
///  let Q be a new Queue of vertex
///  Q.Enqueue(s)
///  while Q.size =/= 0
///     u = Q.Dequeue()
///     for each v in G.adj[u]
///         if v.color == WHITE
///             v.color = GRAY
///             v.distance = u.distance + 1
///             v.predecessor = u
///             Q.Enqueue(v)
///     u.color = black
/// -----PSEUDO CODE-----
/// </summary>
/// <param name="sourceKey">the source key</param>
void ListGraph::BreadthFirstSearch(int sourceKey)
{
	auto sf = find_if(vertices.begin(), vertices.end(), [sourceKey](Vertex v) {return v.key == sourceKey; });
	Vertex* s = NULL;
	if (sf != vertices.end())
	{
		s = sf._Ptr;
	}
	else
	{
		std::cout << "Source key does not exists." << std::endl;
		return;
	}

	std::for_each(vertices.begin(), vertices.end(),
		[](Vertex& u)
		{
			u.color = Color::White;
			u.distance = INT_MAX;
			u.predecessor = nullptr;
		});
	//for (Vertex& u : vertices)
	//{
	//	u.color = Color::White;
	//	u.distance = INT_MAX;
	//	u.predecessor = nullptr;
	//}
	s->color = Color::Grey;
	s->distance = 0;
	s->predecessor = nullptr;
	std::queue<Vertex*> Q;
	Q.push(s);
	while (!Q.empty())
	{
		Vertex* u = Q.front();
		Q.pop();
		for (Vertex* v : adjacencyList[u->key - minKey])
		{
			PrintVertices();
			std::cout << "-" << std::endl;
			if (v->color == Color::White)
			{
				v->color = Color::Grey;
				v->distance = u->distance + 1;
				v->predecessor = u;
				Q.push(v);
			}
		}
		u->color = Color::Black;
	}
}

void ListGraph::DepthFirstSearch()
{

}

bool ListGraph::BellmanFord(int sourceKey)
{
	return false;
}

void ListGraph::Dijkstra(int sourceKey)
{

}

void ListGraph::AStar(int sourceKey)
{

}

/// <summary>
/// Prints all the edges of each vertex
/// -----PSEUDO CODE-----
/// (G is the Graph)
/// PrintEdges(G)
///  for i = 0 to length of G.adjacencyList - 1
///		print "G.vertices[i].key["
///		for each v in adjacencyList[i]
///			if v == adjacencyList[i] last element
///				print "v.key"
///			else
///				print "v.key,"
///		print "]"
/// -----PSEUDO CODE-----
/// </summary>
void ListGraph::PrintEdges()
{
	for (int i = 0; i < adjacencyList->size(); i++)
	{
		std::cout << vertices[i].key << '[';
		for (auto vertex : adjacencyList[i])
		{
			if (vertex == adjacencyList[i].back())
			{
				std::cout << vertex->key;
			}
			else
			{
				std::cout << vertex->key << ',';
			}
		}
		std::cout << ']' << std::endl;
	}
}
