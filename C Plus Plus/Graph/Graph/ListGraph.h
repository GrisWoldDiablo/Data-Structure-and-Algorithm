/*
 * Author: Alexandre Lepage
 * Date: March 2020
 */

#ifndef LISTGRAPH
#define LISTGRAPH
#include "AbstractGraph.h"
#include <queue>
#include <stack>

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
	void DepthFirstSearchKey(int sourceKey) override;
	void DepthFirstSearchIterative() override;
	void DepthFirstSearchIterativeKey(int sourceKey) override;
	bool BellmanFord(int sourceKey) override;
	void Dijkstra(int sourceKey) override;
	void AStar(int sourceKey) override;
	void PrintEdges();

private:
	void DepthFirstSearchVisit(Vertex* u) override;
	void DepthFirstSearchIterativeVisit(Vertex* u) override;
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
		if (find(adjacencyList[sourceKey - minKey].begin(), adjacencyList[sourceKey - minKey].end(), destination._Ptr) == adjacencyList[sourceKey - minKey].end()) {
			adjacencyList[sourceKey - minKey].push_back(destination._Ptr);
		}
	}
}

/// <summary>
/// This is populating the predecessors from the keys that leads to the source key
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
	Vertex* s = nullptr;
	if (sf != vertices.end())
	{
		s = sf._Ptr;
	}
	else
	{
		std::cout << "Source key does not exists." << std::endl;
		return;
	}

	for_each(vertices.begin(), vertices.end(),
		[](Vertex& u)
		{
			u.color = Color::White;
			u.distance = INT_MAX;
			u.predecessor = nullptr;
		});
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

/// <summary>
/// Going through all vertices and setting subtrees and timestamps
/// (recursive)
/// -----PSEUDO CODE-----
/// (G is the graph to search)
/// DFS(G)
///  for each vertex u in G.vertices
///		u.color = WHITE
///		u.predecessor = NIL
///  G.time = 0
///  for each u in G.vertices
///		if u.color == WHITE
///			u.predecessor = u
///			DFS-VISIT(G,v)
/// -----PSEUDO CODE-----
/// </summary>
void ListGraph::DepthFirstSearch()
{
	for_each(vertices.begin(), vertices.end(),
		[](Vertex& u)
		{
			u.color = Color::White;
			u.predecessor = nullptr;
		});
	time = 0;
	for_each(vertices.begin(), vertices.end(),
		[this](Vertex& u)
		{
			if (u.color == Color::White)
			{
				DepthFirstSearchVisit(&u);
			}
		});
}

/// <summary>
/// Finding path that leads to that source vertex
/// (recursive)
/// -----PSEUDO CODE-----
/// (G is the graph to search, s is the source vertex)
/// DFS(G,s)
///  for each vertex u in G.vertices
///		u.color = WHITE
///		u.predecessor = NIL
///  G.time = 1
///  u.discoveryTime = G.time
///  u.color = GRAY
///  for each v in G.adj[u]
///		if v.color == WHITE
///			v.predecessor = u
///			DFS-VISIT(G,v)
///  u.color = BLACK
///  G.time = G.time + 1
///  u.finishingTime = G.time
/// -----PSEUDO CODE-----
/// </summary>
/// <param name="sourceKey">The vertex's key to search from</param>
void ListGraph::DepthFirstSearchKey(int sourceKey)
{
	auto sf = find_if(vertices.begin(), vertices.end(), [sourceKey](Vertex v) {return v.key == sourceKey; });
	Vertex* s = nullptr;
	if (sf != vertices.end())
	{
		s = sf._Ptr;
	}
	else
	{
		std::cout << "Source key does not exists." << std::endl;
		return;
	}

	for_each(vertices.begin(), vertices.end(),
		[](Vertex& u)
		{
			u.color = Color::White;
			u.predecessor = nullptr;
		});
	time = 1;

	s->discoveryTime = time;
	s->color = Color::Grey;
	for (Vertex* v : adjacencyList[s->key - minKey])
	{
		if (v->color == Color::White)
		{
			v->predecessor = s;
			DepthFirstSearchVisit(v);
		}
	}
	s->color = Color::Black;
	time++;
	s->finishingTime = time;
}

/// <summary>
/// Visiting all the vertices from the adjacency list
/// (recursive)
/// -----PSEUDO CODE-----
/// (G is the graph to search, u is the source vertex)
/// DFS-Visit(G,u)
///  G.time = G.time + 1
///  u.discoveryTime = G.time
///  u.color = GRAY
///  for each v in G.adj[u]
///		if v.color == WHITE
///			v.predecessor = u
///			DFS-VISIT(G,v)
///  u.color = BLACK
///  G.time = G.time + 1
///  u.finishingTime = G.time
/// -----PSEUDO CODE-----
/// </summary>
/// <param name="u">The vertex to search from</param>
void ListGraph::DepthFirstSearchVisit(Vertex* u)
{
	time++;
	u->discoveryTime = time;
	u->color = Color::Grey;
	for (Vertex* v : adjacencyList[u->key - minKey])
	{
		if (v->color == Color::White)
		{
			v->predecessor = u;
			DepthFirstSearchVisit(v);
		}
	}
	u->color = Color::Black;
	time++;
	u->finishingTime = time;
}

/// <summary>
/// Going through all vertices and setting subtrees and timestamps
/// (Iterative)
/// -----PSEUDO CODE-----
/// (G is the graph to search)
/// DFS-Iterative(G)
///  for each vertex u in G.vertices
///		u.color = WHITE
///		u.predecessor = NIL
///  G.time = 0
///  for each u in G.vertices
///		if u.color == WHITE
///			u.predecessor = u
///			DFS-Iterative(G,v)
/// -----PSEUDO CODE-----
/// </summary>
void ListGraph::DepthFirstSearchIterative()
{
	for_each(vertices.begin(), vertices.end(),
		[](Vertex& u)
		{
			u.color = Color::White;
			u.predecessor = nullptr;
		});
	time = 0;
	for_each(vertices.begin(), vertices.end(),
		[this](Vertex& u)
		{
			if (u.color == Color::White)
			{
				DepthFirstSearchIterativeVisit(&u);
			}
		});
}

/// <summary>
/// Visiting all the vertices from the adjacency list
/// (iterative)
/// -----PSEUDO CODE-----
/// (G is the graph to search, s is the source vertex)
/// DFS-IterativeKey(G,s)
///  for each vertex u in G.vertices
///		u.color = WHITE
///		u.predecessor = NIL
///	 G.time = 0
///	 let Stk be a stack
///	 Stk.push(s)
///	 while Stk is not empty
///		v = Stk.top()
///		G.time = G.time + 1
///		v.discovertyTime = time
///		v.color = BLACK
///		for i = size of G.adj[v.key] - 1 to 1
///			if G.adj[v.key][i].color == WHITE
///				G.adj[v.key][i].predecessor = v
///				Stk.push(G.adj[v.key][i])
///		G.time = G.time + 1
///		v.finishingTime = G.time
/// -----PSEUDO CODE-----
/// </summary>
/// <param name="u">The vertex to search from</param>
void ListGraph::DepthFirstSearchIterativeVisit(Vertex* u)
{
	Vertex* v = nullptr;
	std::stack<Vertex*> Stk;
	Stk.push(u);
	while (!Stk.empty())
	{
		v = Stk.top();
		Stk.pop();
		time++;
		v->discoveryTime = time;
		v->color = Color::Black;
		for (int i = adjacencyList[v->key - minKey].size() - 1; i >= 0; i--)
		{
			if (adjacencyList[v->key - minKey][i]->color == Color::White)
			{
				adjacencyList[v->key - minKey][i]->predecessor = v;
				Stk.push(adjacencyList[v->key - minKey][i]);
			}
		}
		time++;
		v->finishingTime = time;
	}
}
/// <summary>
/// Visiting all the vertices from the adjacency list
/// (iterative)
/// -----PSEUDO CODE-----
/// (G is the graph to search, s is the source vertex)
/// DFS-IterativeKey(G,s)
///  for each vertex u in G.vertices
///		u.color = WHITE
///		u.predecessor = NIL
///	 G.time = 0
///	 let Stk be a stack
///	 Stk.push(s)
///	 while Stk is not empty
///		v = Stk.top()
///		G.time = G.time + 1
///		v.discovertyTime = time
///		v.color = BLACK
///		for i = size of G.adj[v.key] - 1 to 1
///			if G.adj[v.key][i].color == WHITE
///				G.adj[v.key][i].predecessor = v
///				Stk.push(G.adj[v.key][i])
///		G.time = G.time + 1
///		v.finishingTime = G.time
/// -----PSEUDO CODE-----
/// </summary>
/// <param name="sourceKey">The vertex to search from</param>
void ListGraph::DepthFirstSearchIterativeKey(int sourceKey)
{
	auto sf = find_if(vertices.begin(), vertices.end(), [sourceKey](Vertex v) {return v.key == sourceKey; });
	Vertex* sk = nullptr;
	if (sf != vertices.end())
	{
		sk = sf._Ptr;
	}
	else
	{
		std::cout << "Source key does not exists." << std::endl;
		return;
	}

	for_each(vertices.begin(), vertices.end(),
		[](Vertex& u)
		{
			u.color = Color::White;
			u.predecessor = nullptr;
		});
	time = 0;
	auto v = sk;
	std::stack<Vertex*> Stk;
	Stk.push(v);
	while (!Stk.empty())
	{
		v = Stk.top();
		Stk.pop();
		time++;
		v->discoveryTime = time;
		v->color = Color::Black;
		for (int i = adjacencyList[v->key - minKey].size() - 1; i >= 0; i--)
		{
			if (adjacencyList[v->key - minKey][i]->color == Color::White)
			{
				adjacencyList[v->key - minKey][i]->predecessor = v;
				Stk.push(adjacencyList[v->key - minKey][i]);
			}
		}
		time++;
		v->finishingTime = time;
	}
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

	for (size_t i = 0; i < vertices.size(); i++)
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



#endif // !LISTGRAPH
