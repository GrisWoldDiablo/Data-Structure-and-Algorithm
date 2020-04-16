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
	std::vector<AdjacentVertex*>* adjacencyList; //The adjacency list for the vertices.

	ListGraph(std::initializer_list<int> keys); // Constructor
	ListGraph(std::vector<int> keys); // Constructor
	ListGraph(int keys[], int arraySize); // Constructor
	~ListGraph();

	void AddEdge(int sourceKey, int destinationKey, int weight = 1) override;
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
	void InitializeSingleSource(Vertex* s) override;
	void Relax(Vertex* u, AdjacentVertex* v) override;

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
	adjacencyList = new std::vector<AdjacentVertex*>[maxKey - minKey + 1];
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
	adjacencyList = new std::vector<AdjacentVertex*>[maxKey - minKey + 1];
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
	adjacencyList = new std::vector<AdjacentVertex*>[maxKey - minKey + 1];
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
	for (int i = 0; i < vertices.size(); i++)
	{
		for (auto v : adjacencyList[vertices[i]->key - minKey])
		{
			delete v;
		}
	}
	delete[] adjacencyList;
}

/// <summary>
/// Add an edge to a vertex
/// -----PSEUDO CODE-----
/// (G is the graph)
/// (sK is the source key)
/// (dK is the destination key)
/// (w is the weight if the edge)
/// AddEdge(G,sK,dK,w)
///  dV = NIL
///  for each v in G.vertices
///		if v.key == dK.key
///			dV = v
///  if dV =/= NIL
///		aV = AdjacentVertex(dV,w)
///		G.adj[sK - G.minKey].add(aV)
/// -----PSEUDO CODE-----
/// </summary>
/// <param name="sourceKey">source key</param>
/// <param name="destinationKey">destination key</param>
void ListGraph::AddEdge(int sourceKey, int destinationKey, int weight)
{
	auto destination = find_if(vertices.begin(), vertices.end(), [destinationKey](Vertex* v) {return v->key == destinationKey; });
	if (destination != vertices.end())
	{
		AdjacentVertex av = AdjacentVertex(*destination, weight);
		auto avd = find_if(adjacencyList[sourceKey - minKey].begin(), adjacencyList[sourceKey - minKey].end(), [av](AdjacentVertex* v) {return v->vertex == av.vertex && v->weight == av.weight; });

		if (avd == adjacencyList[sourceKey - minKey].end()) {
			adjacencyList[sourceKey - minKey].push_back(new AdjacentVertex(*destination, weight));
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
	auto sf = find_if(vertices.begin(), vertices.end(), [sourceKey](Vertex* v) {return v->key == sourceKey; });
	Vertex* s = nullptr;
	if (sf != vertices.end())
	{
		s = *sf;
	}
	else
	{
		std::cout << "Source key does not exists." << std::endl;
		return;
	}

	for_each(vertices.begin(), vertices.end(),
		[](Vertex* u)
		{
			u->color = Color::White;
			u->distance = INT_MAX;
			u->predecessor = nullptr;
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
		for (AdjacentVertex* neighbor : adjacencyList[u->key - minKey])
		{
			Vertex* v = neighbor->vertex;
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
		[](Vertex* u)
		{
			u->color = Color::White;
			u->predecessor = nullptr;
		});
	time = 0;
	for_each(vertices.begin(), vertices.end(),
		[this](Vertex* u)
		{
			if (u->color == Color::White)
			{
				DepthFirstSearchVisit(u);
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
	auto sf = find_if(vertices.begin(), vertices.end(), [sourceKey](Vertex* v) {return v->key == sourceKey; });
	Vertex* s = nullptr;
	if (sf != vertices.end())
	{
		s = *sf;
	}
	else
	{
		std::cout << "Source key does not exists." << std::endl;
		return;
	}

	for_each(vertices.begin(), vertices.end(),
		[](Vertex* u)
		{
			u->color = Color::White;
			u->predecessor = nullptr;
		});
	time = 1;

	s->discoveryTime = time;
	s->color = Color::Grey;
	for (AdjacentVertex* neighbor : adjacencyList[s->key - minKey])
	{
		Vertex* v = neighbor->vertex;
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
	for (AdjacentVertex* neighbor : adjacencyList[u->key - minKey])
	{
		Vertex* v = neighbor->vertex;
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
		[](Vertex* u)
		{
			u->color = Color::White;
			u->predecessor = nullptr;
		});
	time = 0;
	for_each(vertices.begin(), vertices.end(),
		[this](Vertex* u)
		{
			if (u->color == Color::White)
			{
				DepthFirstSearchIterativeVisit(u);
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
			if (adjacencyList[v->key - minKey][i]->vertex->color == Color::White)
			{
				adjacencyList[v->key - minKey][i]->vertex->predecessor = v;
				Stk.push(adjacencyList[v->key - minKey][i]->vertex);
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
	auto sf = find_if(vertices.begin(), vertices.end(), [sourceKey](Vertex* v) {return v->key == sourceKey; });
	Vertex* sk = nullptr;
	if (sf != vertices.end())
	{
		sk = *sf;
	}
	else
	{
		std::cout << "Source key does not exists." << std::endl;
		return;
	}

	for_each(vertices.begin(), vertices.end(),
		[](Vertex* u)
		{
			u->color = Color::White;
			u->predecessor = nullptr;
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
			if (adjacencyList[v->key - minKey][i]->vertex->color == Color::White)
			{
				adjacencyList[v->key - minKey][i]->vertex->predecessor = v;
				Stk.push(adjacencyList[v->key - minKey][i]->vertex);
			}
		}
		time++;
		v->finishingTime = time;
	}
}

/// <summary>
/// Solves the single source shortest path problem using weighted edges.
/// -----PSEUDO CODE-----
/// BellmanFord(G,w,s)
///  Initialize-Single-Source(G,s)
///  for i = 0 to length of G.vertices - 1
///		for each edge(u,v) in G.adj
///			Relax(u,v,w)
///	 for each edge(u,v)
///		if v.distance > u.distance + w(u,v)
///			return FALSE
///  return TRUE
/// -----PSEUDO CODE-----
/// </summary>
/// <param name="sourceKey">The vertex's key to search from</param>
/// <returns>TRUE if and only if the graph contains no negative-weight cycles that are reachable from the source</returns>
bool ListGraph::BellmanFord(int sourceKey)
{
	auto sf = find_if(vertices.begin(), vertices.end(), [sourceKey](Vertex* v) {return v->key == sourceKey; });
	Vertex* s = nullptr;
	if (sf != vertices.end())
	{
		s = *sf;
	}
	else
	{
		std::cout << "Source key does not exists." << std::endl;
		return false;
	}

	InitializeSingleSource(s);
	for (auto u : vertices)
	{
		for (int i = 0; i < vertices.size(); i++)
		{
			for (auto v : adjacencyList[vertices[i]->key - minKey])
			{
				Relax(vertices[i], v);
			}
		}
	}

	for (int i = 0; i < vertices.size(); i++)
	{
		for (auto v : adjacencyList[vertices[i]->key - minKey])
		{
			if (v->vertex->distance > vertices[i]->distance + v->weight && vertices[i]->distance != INT_MAX)
			{
				return false;
			}
		}
	}

	return true;
}

/// <summary>
/// initialize all the vertices distance to infinity
/// and predecessors to nil, then set the source vertex distance to 0
/// -----PSEUDO CODE-----
/// (G is the graph, s is the source vertex)
/// Initialize-Single-Source(G,s)
///  for each vertex v in G.vertices
///		v.distance = INFINITY
///		v.predecessor = NIL
///  s.distance = 0
/// -----PSEUDO CODE-----
/// </summary>
/// <param name="s">source vertex</param>
void ListGraph::InitializeSingleSource(Vertex* s)
{
	for_each(vertices.begin(), vertices.end(),
		[](Vertex* u)
		{
			u->distance = INT_MAX;
			u->predecessor = nullptr;
		});
	s->distance = 0;
}

/// <summary>
/// reduce the distance of the adjacent vertex using the weight of the edge
/// -----PSEUDO CODE-----
/// (u is the source vertex, v is the adjacent vertex)
/// Relax(u,v)
///  if v.distance > u.distance + v.weight
///		v.distance = u.distance + v.weight
///		v.predecessor = u
/// -----PSEUDO CODE-----
/// </summary>
/// <param name="u">source vertex</param>
/// <param name="v">adjacent vertex</param>
void ListGraph::Relax(Vertex* u, AdjacentVertex* v)
{
	if (v->vertex->distance > u->distance + v->weight && u->distance != INT_MAX)
	{
		v->vertex->distance = u->distance + v->weight;
		v->vertex->predecessor = u;
	}
}

/// <summary>
/// Find the quickest path from the source key.
/// -----PSEUDO CODE-----
/// Dijkstra(G,s)
///  Inititialize-Single-Source(G,s)
///  Q = G.vertices
///  while Q is not empty
///		u = Extract-Min(Q)
///		for each v in G.adj[u]
///			Relax(u,v)
/// -----PSEUDO CODE-----
/// </summary>
/// <param name="sourceKey">The vertex's key to search from</param>
void ListGraph::Dijkstra(int sourceKey)
{
	auto sf = find_if(vertices.begin(), vertices.end(), [sourceKey](Vertex* v) {return v->key == sourceKey; });
	Vertex* s = nullptr;
	if (sf != vertices.end())
	{
		s = *sf;
	}
	else
	{
		std::cout << "Source key does not exists." << std::endl;
		return;
	}

	InitializeSingleSource(s);
	std::priority_queue<Vertex*, std::vector<Vertex*>, VertexCompareMax> Q;
	
	for (auto u : vertices) {
		Q.push(u);
	}

	while (!Q.empty())
	{
		auto u = Q.top();
		Q.pop();
		for (auto v : adjacencyList[u->key - minKey]) {
			Relax(u, v);
		}
	}
}

void ListGraph::AStar(int sourceKey)
{

}

/// <summary>
/// Prints all the edges of each vertex
/// -----PSEUDO CODE-----
/// (G is the Graph)
/// PrintEdges(G)
///  for i = 0 to length of G.adj - 1
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
		std::cout << vertices[i]->key << '[';
		for (auto av : adjacencyList[i])
		{
			if (av == adjacencyList[i].back())
			{
				std::cout << av->vertex->key << "(" << av->weight << ")";
			}
			else
			{
				std::cout << av->vertex->key << "(" << av->weight << ")" << ',';
			}
		}
		std::cout << ']' << std::endl;
	}
}
#endif // !LISTGRAPH
