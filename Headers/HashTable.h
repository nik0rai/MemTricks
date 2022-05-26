#pragma once
#include "Allocator.h"
#include <vector>

template <class T>
class HashTable
{
private:
	Allocator* al;	
	struct Node
	{
		T data;
		Node* next;
	};
	std::vector<Node*> chain;
	void init();
public:
	size_t size;

	HashTable(size_t size) {
		this->size = size;

		al = new Allocator(4096, 8);

		//chain = new Node[size];
		//chain = (Node*)al->Allocate(size * sizeof(Node)); //or Node*
		init();
	}

	void insert(T value) {
		Node* nNode = (Node*)al->Allocate(sizeof(value));
		//Node* nNode = new Node;
		nNode->data = value;
		nNode->next = NULL;

		int key = hash(value);

		if (chain[key] == NULL)
			chain[key] = nNode;
		else {
			Node* temp = chain[key];
			while (temp->next)
				temp = temp->next;
			
			temp->next = nNode;
		}
	}

	unsigned long hash(char* arr) {
		size_t hash = std::hash<char*>{}(arr);
		std::cout << hash << std::endl;
		return hash % size;
	}

	unsigned long hash(std::string s)
	{
		size_t hash = std::hash<string>{}(s);
		std::cout << hash<<std::endl;
		return hash % size;
	}

	unsigned long hash(int value) {
		return value % size;
	}

	T remove(T value) {
		int key = hash(value);
		if (chain[key]->data == value) {
			chain[key] = NULL;
			return value;
		}		
		else std::cout << "Not present in table!" << std::endl;
		return NULL;
	}

	T get(T value) {
		int key = hash(value);
		if (chain[key]->data == value)
			return chain[key]->data;
		return NULL;
	}

	void print() {
		for (size_t i = 0; i < size; i++)
		{
			auto temp = chain[i];
			std::cout << "[" << i << "]";
			while (temp)
			{
				std::cout << "->" << temp->data;
				temp = temp->next;
			}
			std::cout << "->NULL" << std::endl;
		}
	}
};

template<class T>
inline void HashTable<T>::init()
{
	for (size_t i = 0; i < size; i++)
		chain.push_back(NULL);
}
