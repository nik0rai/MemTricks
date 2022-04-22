#include <assert.h>
#include <iostream>

// Holder node
struct node {
	size_t size; //size of one node
	bool isCurrentlyUsed; // determine if node ois being used
	node* next;
	void* data; //pointer
};

// I guess it goes with pre alocated memory 
// (just checked how sbrk is made in unix system, so desided to preted like it is unix)
#define MEMORY_CAPACITY 1024 * 1024 * 1024 //pre-alocated mem it is equals 1GB (very large chunk)
void* sbrk(intptr_t val) {
	static char memory[MEMORY_CAPACITY] = { 0 };
	static char* breakPointer = memory;

	char* const limit = memory + MEMORY_CAPACITY;
	char* const original = breakPointer;

	if (val < memory - breakPointer || val >= limit - breakPointer) // mb will be problem with overflow 
	{
		errno = ENOMEM;
		return (void*)-1;
	}
	breakPointer += val;

	return original;
}

class Allocator
{
public:
	Allocator();
	~Allocator();
	size_t alligment(size_t byte);
	void* alloc(size_t size);
	void free(void* data);
private:
	node* request(size_t size);	
	size_t allocateSize(size_t size);
	node* start = nullptr; //begining of heap
	node* end = start; //current last item (actually updates on each allocation)
};

Allocator::Allocator()
{
}

Allocator::~Allocator()
{
}

// Request mem from OS
node* Allocator::request(size_t size) // now we are able to request maps
{
	auto n = (node*)sbrk(0); // we get curr heap break
	if (sbrk(allocateSize(size)) == (void*)-1)
		return nullptr;
	return n;
}
// In case we need total allocated size
size_t Allocator::allocateSize(size_t size) {
	return size + sizeof(node) - sizeof(std::declval<node>().data);
}
void* Allocator::alloc(size_t size) {
	size = alligment(size); //we perfom alligment for specific of archtecture (i.e. x32 or x64)
	auto node = request(size); //we ask from os for some memory
	node->isCurrentlyUsed = true; //if we asked about it -> is getting to be used
	node->size = size;

	// initialize heap
	if (start == nullptr)
		start = node;

	// connect nodes
	if (end != nullptr)
		end->next = node;

	end = node;
	return node->data;
}
void Allocator::free(void* data)
{
	// goto:create free function
}

// We will automatically allign bytes by archtecture of user`s machine
// Example:
// x64 -> aligment(4) => gets us 8
// x32 -> aligment(4) => gets us 4
size_t Allocator::alligment(size_t byte) {
	return (byte + sizeof(void*) - 1) & ~(sizeof(void*) - 1);
}


int main()
{
	Allocator *al = new Allocator();
	auto res = al->alloc(5);
	auto second_res = al->alloc(12);
	std::cout << "first: " << res << " second: " << std::endl; //doesn`t work...fuck
	return 0;
}
