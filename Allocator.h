#pragma once
class Allocator
{
private:
	size_t offset;

	Allocator(Allocator& allocate);
public:
	void* curr = nullptr; //current address
	size_t size; //total size
	size_t used; //is beeing used or not
	size_t top; //max memory

	struct HEADER
	{
		char padding;
	};
	Allocator(size_t _size) : size {_size}, used{0}, top{0}{}
	~Allocator() { size = 0; }
	void* alloc(size_t size, size_t align = 0);
	void Free(void* pointer);
	void init();
	void clear();
};

