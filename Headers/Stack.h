#include "Tester.h"
#include "Allocator.h"

#pragma once
template<typename T>
class Stack
{
private:
	T top;
	T* items;
public:
	int maxSize; //max capacity of stack

	void init(int capa) {
		maxSize = capa;
		top = -1;
		Allocator* al = new Allocator(maxSize);
		al->init();
		items = (T*)al->alloc(sizeof(T) * capa, 8);

		//items = (T*)malloc(sizeof(T) * capa); //default malloc
	}
	int size() { return top + 1; }
	bool isEmpty() { return size() == 0; }
	bool isFull() { return top == (maxSize - 1); }
	void push(T value) {
		if (!isFull()) {
			top++;
			items[top] = value;
		}
	}
	T getTop() { return (!isEmpty()) ? items[top] : -1; } //-1 means stack was actually empty
	T pop() {
		if (!isEmpty()) {
			top--;
			return items[top];
		}
	}
	void print() {
		for (int i = maxSize - 1; i >= 0; i--)
			std::cout << items[i] << std::endl;
	}
};