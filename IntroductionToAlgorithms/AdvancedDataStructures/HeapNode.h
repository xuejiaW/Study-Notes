#pragma once

#include "Wheels.h"
template <class T>
class HeapNode
{
public:
	HeapNode() {}
	~HeapNode()
	{
		if (child != nullptr)
			delete(child);
	}
	T value;
	Wheels<HeapNode<T>>* child;
	int degree;
	HeapNode(T v) :value(v), degree(0), child(nullptr) {};
private:
};
