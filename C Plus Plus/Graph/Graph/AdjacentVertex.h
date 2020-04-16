/*
* Author: Alexandre Lepage
* Date: April 2020
*/

#ifndef ADJACENTVERTEX
#define ADJACENTVERTEX
#include "Vertex.h"

class AdjacentVertex
{
public:
	Vertex* vertex;
	int weight;

	AdjacentVertex(Vertex* vertex, int weight);
};

AdjacentVertex::AdjacentVertex(Vertex* vertex, int weight)
{
	this->vertex = vertex;
	this->weight = weight;
}

#endif // ADJACENTVERTEX
