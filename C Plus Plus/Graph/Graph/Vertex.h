/*
 * Author: Alexandre Lepage
 * Date: March 2020
 */

#pragma once

#include <limits.h>
#include <iostream>

 /// <summary>
 /// Enumerator class color
 /// </summary>
enum class Color
{
	White,
	Grey,
	Black
};

/// <summary>
/// overload of the left shift operator for the Color enumerator color
/// </summary>
/// <param name="os">output stream</param>
/// <param name="e">enumerator</param>
/// <returns>color</returns>
std::ostream& operator<<(std::ostream& os, const Color& e)
{
	// write obj to stream
	switch (e)
	{
	default:
		break;
	case Color::White:
		return os << "White";
		break;
	case Color::Grey:
		return os << "Grey";
		break;
	case Color::Black:
		return os << "Black";
		break;
	}
	return os;
}

/// <summary>
/// Custom vertex class
/// </summary>
class Vertex
{
public:
	unsigned int key; // The number of the vertex
	int distance; // How far from the source this vertex is
	Vertex* predecessor; // The vertex preceding this one
	Color color; // The color of this key

	Vertex(int key);

	/// <summary>
	/// Overloading the equal operator
	/// compares the vertices' key
	/// </summary>
	bool operator==(const Vertex& a) const {
		return this->key == a.key; 
	};

	/// <summary>
	/// overload of the left shift operator for vertex 
	/// </summary>
	/// <param name="os">output stream</param>
	/// <param name="e">vertex</param>
	/// <returns>vertex key</returns>
	friend std::ostream& operator<<(std::ostream& os, const Vertex& v)
	{
		return os << v.key;// << ':' << v.color;
	}
	
	/// <summary>
	/// overload of the left shift operator for vertex pointer
	/// </summary>
	/// <param name="os">output stream</param>
	/// <param name="e">vertex</param>
	/// <returns>vertex key</returns>
	friend std::ostream& operator<<(std::ostream& os, const Vertex* v)
	{
		return os << v->key;// << ':' << v->color;
	}
};

/// <summary>
/// Class constructor
/// -----PSEUDO CODE-----
/// (V is the vertex, key is the number of the vertex)
/// Vertex(V,key)
///	 V.key = key
///  V.distance = Infinity
///  V.predecessor = NIL
///  V.color = WHITE
/// -----PSEUDO CODE-----
/// </summary>
/// <param name="key"></param>
Vertex::Vertex(int key) {
	this->key = key;
	this->distance = INT_MAX;
	this->predecessor = nullptr;
	this->color = Color::White;
}

