#include <iostream>
#include <vector>
#include "Allocator.h"
#include "Tester.h"
#include "Stack.h"

int main()
{
	Stack<int> s; s.init(3);

	for (int i = 0; i < s.maxSize; i++)
		s.push(i);
	



	//const std::vector<char> arr{'h','e','l', 'l', 'o'}; //security problem -> stack overflow

	//Allocator* al = new Allocator(1e9); //max size
	//Tester* t = new Tester();


	//for (size_t i = 0; i < arr.size(); i++)
	//	t->Allocation(al, arr[i], 8);

	//std::cout << "\n---------------------------------------------------------------------------\n\n";

	//t->Freeing(al, 1, arr[1], 8); //2nd block to delete
	//t->Freeing(al, 3, arr[3], 8); //4th block to delete
	

	return 0;
}
