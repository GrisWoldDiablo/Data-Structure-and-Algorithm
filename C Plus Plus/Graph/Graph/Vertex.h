/*
 * Author: Alexandre Lepage
 * Date: March 2020
 */

#pragma once

 /// <summary>
 /// 
 /// </summary>
enum class Color
{
	White,
	Grey,
	Black
};

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
/// 
/// </summary>
class Vertex
{
public:
	unsigned int key;
	int distance;
	Vertex* predecessor;
	Color color;

	Vertex(int key);
	bool operator==(const Vertex& a) const { return this->key == a.key; };
	friend std::ostream& operator<<(std::ostream& os, const Vertex& v)
	{
		// write obj to stream
		return os << v.key << ':' << v.color;
	}
	
	friend std::ostream& operator<<(std::ostream& os, const Vertex* v)
	{
		// write obj to stream
		return os << v->key << ':' << v->color;
	}
};

Vertex::Vertex(int key) {
	this->key = key;
	this->distance = INT_MAX;
	this->predecessor = nullptr;
	this->color = Color::White;
}

