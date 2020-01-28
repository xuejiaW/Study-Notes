#include <iostream>
#include <cmath>
#include "Wheels.h"
#include "HeapNode.h"

using namespace std;

template <class T>
class FabonacciHeap
{
public:
	FabonacciHeap()
	{
		rootList = nullptr;
		minimum = nullptr;
		number = 0;
	}
	~FabonacciHeap()
	{
		emptyH();
	}

	void emptyH()
	{
		if (rootList != nullptr)
		{
			rootList->emptyW();
			delete(rootList);
		}
		rootList = nullptr;
	}

	bool isEmptyH()
	{
		return minimum == nullptr;
	}

	void insertH(T value)
	{
		HeapNode<T> node = HeapNode<T>(value);
		if (rootList == nullptr)
			rootList = new Wheels<HeapNode<T>>();

		Node<HeapNode<T>>* inserted = rootList->InsertW(node);

		if (minimum == nullptr || value < minimum->value.value)
			minimum = inserted;

		number++;
	}

	//The extractH operation won't relase the node,caller should release the node manally
	Node<HeapNode<T>>* extractH()
	{
		Node<HeapNode<T>>* min = minimum;
		if (min != nullptr)
		{
			Wheels<HeapNode<T>>* wheels = min->value.child;
			if (wheels != nullptr)
			{
				Node<HeapNode<T>>* childOfMin = wheels->extractW();
				while (childOfMin != nullptr)
				{
					rootList->InsertW(childOfMin);
					childOfMin = wheels->extractW();
				}
			}
			rootList->deleteW(min);

			minimum = rootList->isEmptyW() ? nullptr : min->next;
			consolidata();

		}
		number--;
		return min;
	}

	Node<HeapNode<T>>* FindMinimum()
	{
		Node<HeapNode<T>>* current = rootList->headW();
		Node<HeapNode<T>>* min = current;
		if (current == nullptr)
		{
			return nullptr;
		}
		T minValue = current->value.value;
		while (current != nullptr)
		{
			current = current->next;
			if (current->value.value < minValue)
			{
				minValue = current->value.value;
				min = current;
			}
			if (current == rootList->headW())
				break;
		}
		return min;
	}

	void consolidata()
	{

		if (minimum == nullptr)
			return;
		const int max = log(number * 1.0) / log(2) + 1;
		Node<HeapNode<T>>** nodeDegreeArray = new Node<HeapNode<T>> * [max];
		for (int i = 0; i < max; i++)
			nodeDegreeArray[i] = nullptr;

		Node<HeapNode<T>>* current = rootList->headW();
		Node<HeapNode<T>>* end = rootList->headW()->prev;
		while (current != nullptr)
		{
			//Node "current" should finally be inserted into the array

			bool shouldExist = current == end;
			int degree = current->value.degree;

			while (nodeDegreeArray[degree] != nullptr)
			{
				Node<HeapNode<T>>* sameDegreeNode = nodeDegreeArray[degree];
				//Exchange current with sameDegreeNode,to ensure current be the smaller one
				if (current->value.value > sameDegreeNode->value.value)
				{
					Node<HeapNode<T>>* temp = current;
					current = sameDegreeNode;
					sameDegreeNode = temp;
				}

				HeapLink(sameDegreeNode, current);

				nodeDegreeArray[degree] = nullptr;
				degree++;
			}

			nodeDegreeArray[degree] = current;

			current = current->next;
			if (shouldExist) // Have go around the wheels,How to terminate?
			{
				break;
			}
		}

		//Use nodeDegreeArray load new rootlist
		minimum = nullptr;
		for (int i = 0; i < max; i++)
		{
			if (nodeDegreeArray[i] != nullptr)
			{
				if (minimum == nullptr)
				{
					rootList = new Wheels<HeapNode<T>>();
					rootList->InsertW(nodeDegreeArray[i]);
					minimum = nodeDegreeArray[i];
				}
				else
				{

					rootList->InsertW(nodeDegreeArray[i]);

					if (nodeDegreeArray[i]->value.value < minimum->value.value)
						minimum = nodeDegreeArray[i];
				}
			}
		}
		delete nodeDegreeArray;
	}

	void HeapLink(Node<HeapNode<T>>* nodeY, Node<HeapNode<T>>* nodeX)
	{
		rootList->deleteW(nodeY);
		if (nodeX->value.child == nullptr)
			nodeX->value.child = new Wheels<HeapNode<T>>();
		nodeX->value.child->InsertW(nodeY);
		nodeX->value.degree++;
	}

	Node<HeapNode<T>>* minimumH()
	{
		if (minimum != nullptr)
		{
			cout << "minimum: " << minimum->value.value << endl;
		}
		return minimum;
	}

private:
	//Every element's type is Node<HeapNode<T>>
	Wheels<HeapNode<T>>* rootList;
	Node<HeapNode<T>>* minimum;
	int number;
};
