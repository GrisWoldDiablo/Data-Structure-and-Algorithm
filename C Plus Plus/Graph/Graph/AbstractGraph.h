/*
 * Author: Alexandre Lepage
 * Date: March 2020
 */

#pragma once
#include "Vertex.h"
#include <vector>
#include <limits.h>


/// <summary>
/// 
/// </summary>
class AbstractGraph
{

protected:
    std::vector<Vertex>  vertices;
    int minKey = INT_MAX;
    int maxKey = INT_MIN;
    int time = 0;

public:
    AbstractGraph(std::initializer_list<int> keys);
    void PrintVertices();
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

protected:
    void InitializeSingleSource(int sourceKey);

};

/// <summary>
/// 
/// </summary>
/// <param name="keys"></param>
AbstractGraph::AbstractGraph(std::initializer_list<int> keys)
{
    for(int key : keys)
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

void AbstractGraph::PrintVertices()
{
    for (Vertex v : vertices)
    {
        std::cout << v << ':' << v.color << std::endl;
    }
}

void AbstractGraph::PrintPath(int sourceKey, int destinationKey)
{
    auto sf = find_if(vertices.begin(), vertices.end(), [sourceKey](Vertex v) {return v.key == sourceKey; });
    auto vf = find_if(vertices.begin(), vertices.end(), [destinationKey](Vertex v) {return v.key == destinationKey; });
    Vertex s = NULL;
    Vertex v = NULL;
    if (sf != vertices.end())
    {
        s = *sf;
    }
    else
    {
        std::cout << "Source key does not exists." << std::endl;
        return;
    }
	if (vf != vertices.end())
	{
		v = *vf;
	}
	else
	{
        std::cout << "Destination key does not exists." << std::endl;
        return;
	}
    PrintPath(s, v);
    std::cout << std::endl;
}

void AbstractGraph::PrintPath(Vertex& s, Vertex& v)
{
    if (v == s)
    {
        std::cout << s.key;
    }
    else if (v.predecessor == nullptr)
    {
        std::cout << "No path from " << s << " to " << v << " exists.";
    }
    else
    {
        PrintPath(s, *v.predecessor);
        std::cout << "->" << v;
    }
}

/// <summary>
/// 
/// </summary>
/// <param name="sourceKey"></param>
void AbstractGraph::InitializeSingleSource(int sourceKey)
{
    for (Vertex vertex : vertices)
    {
        vertex.distance = INT_MAX;
        vertex.predecessor = nullptr;
    }
}

