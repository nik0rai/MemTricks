#include <iostream>
#include <string>

#include "Allocator.h"
//#include "Stack.h"
#include "HashTable.h"
#include "ReversePolishNotation.h"

int main()
{
  std::string str = "(x - y) * 4 - z * k";
    ReversePolishNotation* reversePolishNotation = new ReversePolishNotation();
    std::string srpn = reversePolishNotation->RPN(str);
    std::cout << "Reverse Polish notation: " << srpn << std::endl;
    return 0;
}







/*
HashTable<std::string> h(4);
	h.insert("ananas");
	h.insert("banan");
	h.insert("persik");
	h.insert("petrushka");
	h.print();
	return 0;
*/
