/*
 * Author: Alexandre Lepage
 * Date: March 2020
 */
#pragma once

#include "AbstractGraph.h"
#include <queue>

 /// <summary>
 /// 
 /// </summary>
class ListGraph : public AbstractGraph
{
public:
	std::vector<Vertex*>* adjacencyList;

	ListGraph(std::initializer_list<int> keys);
	~ListGraph();
	int GetAdjSize();

	void AddEdge(int sourceKey, int destinationKey) override;
	void BreadthFirstSearch(int sourceKey) override;
	void DepthFirstSearch() override;
	bool BellmanFord(int sourceKey) override;
	void Dijkstra(int sourceKey) override;
	void AStar(int sourceKey) override;
	void PrintEdges();
};

ListGraph::ListGraph(std::initializer_list<int> keys) : AbstractGraph(keys)
{
	adjacencyList = new std::vector<Vertex*>[GetAdjSize()];
}

ListGraph::~ListGraph()
{
	delete[] adjacencyList;
}

int ListGraph::GetAdjSize()
{
	return maxKey - minKey + 1;
}

void ListGraph::AddEdge(int sourceKey, int destinationKey)
{
	auto destination = find_if(vertices.begin(), vertices.end(),
		[destinationKey](Vertex v) {
			return v.key == destinationKey;
		});
	if (destination != vertices.end())
	{
		adjacencyList[sourceKey - minKey].push_back(destination._Ptr);
	}
}

/// <summary>
/// 
/// -----PSEUDO CODE-----
/// (G is the Graph)
/// (s is the source vertex)
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
/// <param name="sourceKey"></param>
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

void ListGraph::PrintEdges()
{
	for (int i = 0; i < GetAdjSize(); i++)
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
