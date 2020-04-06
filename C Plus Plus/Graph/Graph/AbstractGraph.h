/*
 * Author: Alexandre Lepage
 * Date: March 2020
 */

#pragma once

#include "Vertex.h"
#include <vector>
#include <limits.h>
#include <iostream>

 /// <summary>
 /// Custom Abstract Graph class
 /// </summary>
class AbstractGraph
{
protected:
	// class variables
	std::vector<Vertex>  vertices; // List of the vertices in the Graph
	int minKey = INT_MAX; // The minimum value of the keys
	int maxKey = INT_MIN; // The maximum value of the keys
	int time = 0;

	AbstractGraph(std::initializer_list<int> keys); // Constructor

public:
	void PrintVertices(); //
	void PrintPath(int sourceKey, int destinationKey);

private:
	void PrintPath(Vertex& s, Vertex& v);

public:
	virtual void AddEdge(int sourceKey, int destinationKey) {};
	virtual void BreadthFirstSearch(int sourceKey) {};
	virtual void DepthFirstSearch() {};
	virtual bool BellmanFord(int sourceKey) { return false; };
	virtual void Dijkstra(int sourceKey) {};
	virtual void AStar(int sourceKey) {};

};

/// <summary>
/// Class constructor
/// -----PSEUDO CODE-----
/// (G is the graph, Keys is the graph vertices' keys)
/// AbstractGraph(G, Keys)
///  for each key in keys
///		G.vertices.add(key)
///		if key < G.minKey
///			G.minKey = key
///		if key > G.maxKey
///			G.maxKey = key
/// -----PSEUDO CODE-----
/// </summary>
/// <param name="keys">list of keys of the vertices to add to the graph</param>
AbstractGraph::AbstractGraph(std::initializer_list<int> keys)
{
	for (int key : keys)
	{
		vertices.push_back(Vertex(key));
		if (key < minKey)
		{
			minKey = key;
		}
		if (key > maxKey)
		{
			maxKey = key;
		}
	}
}

/// <summary>
/// Print all the vertices part of the graph with their current color.
/// -----PSEUDO CODE-----
/// (G is the graph)
/// PrintVertices(G)
///	 for each v in G.vertices
///		print "v.key:v.color"
/// -----PSEUDO CODE-----
/// </summary>
void AbstractGraph::PrintVertices()
{
	for (Vertex v : vertices)
	{
		std::cout << v << ':' << v.color << std::endl;
	}
}

/// <summary>
/// Find the source and the destination vertices corresponding to the keys.
/// Then print the path from one to the other if they exist.
/// -----PSEUDO CODE-----
/// (G is the graph, sK is the source vertex key, dK is the destination vertex key)
/// PrintPath(G,sK,dK)
///	 sV = NIL
///  dV = NIL
///	 for each v in G.vertices
///		if sK == v.key
///			sV = v
///		else if dK == v.key
///			dV = v
///  if sV == NIL
///		print "source key does not exist"
///		return
///  if dV == NIL
///		print "destination key does not exist"
///		return
///	 PrintPath(G,sV,dV)
/// -----PSEUDO CODE-----
/// </summary>
/// <param name="sourceKey">The source key</param>
/// <param name="destinationKey">The destination key</param>
void AbstractGraph::PrintPath(int sourceKey, int destinationKey)
{
	auto foundSource = find_if(vertices.begin(), vertices.end(), [sourceKey](Vertex v) {return v.key == sourceKey; });
	auto foundDestination = find_if(vertices.begin(), vertices.end(), [destinationKey](Vertex v) {return v.key == destinationKey; });
	Vertex sourceVertex = NULL;
	Vertex destinationVertex = NULL;
	if (foundSource != vertices.end())
	{
		sourceVertex = *foundSource;
	}
	else
	{
		std::cout << "Source key does not exists." << std::endl;
		return;
	}
	if (foundDestination != vertices.end())
	{
		destinationVertex = *foundDestination;
	}
	else
	{
		std::cout << "Destination key does not exists." << std::endl;
		return;
	}
	PrintPath(sourceVertex, destinationVertex);
	std::cout << std::endl;
}

/// <summary>
/// Print the path from the source vertex to the destination vertex if one exist.
/// If not, print that none exist.
/// -----PSEUDO CODE-----
/// (G is the graph, sV is the source vertex, dV is the destination vertex)
/// PrintPath(G,sV,dV)
///  if dV == sV
///		print "sV.key"
///	 else if dV.predecessor == NIL
///		print "No path from sV.key to dV.key exist"
///  else
///		PrintPath(G, sV, dV.predecessor)
///		print "->dV.key"
/// -----PSEUDO CODE-----
/// </summary>
/// <param name="sourceVertex">source vertex</param>
/// <param name="destinationVertex">destination vertex</param>
void AbstractGraph::PrintPath(Vertex& sourceVertex, Vertex& destinationVertex)
{
	if (destinationVertex == sourceVertex)
	{
		std::cout << sourceVertex.key;
	}
	else if (destinationVertex.predecessor == nullptr)
	{
		std::cout << "No path from " << sourceVertex << " to " << destinationVertex << " exists.";
	}
	else
	{
		PrintPath(sourceVertex, *destinationVertex.predecessor);
		std::cout << "->" << destinationVertex;
	}
}
