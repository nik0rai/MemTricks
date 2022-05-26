#include <iostream>
#include <string>

#include "Allocator.h"
#include "Stack.h"
#include "HashTable.h"

int main()
{
	HashTable<std::string> h(4);
	h.insert("ananas");
	h.insert("banan");
	h.insert("persik");
	h.insert("petrushka");
	h.print();
	return 0;
}
