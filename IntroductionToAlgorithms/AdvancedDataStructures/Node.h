#pragma once
template <class T>
class Node
{
public:
	T value;
	Node<T>* next;
	Node<T>* prev;

	Node(T v) :value(v), next(nullptr), prev(nullptr) {}
	~Node() {}
};
