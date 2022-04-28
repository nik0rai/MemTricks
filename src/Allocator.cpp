#include "Allocator.h"
#include "Utils.h"
#include <malloc.h>
#include <iostream>

void* Allocator::alloc(size_t _size, size_t align)
{
	size_t currAddr = (size_t)curr + offset;
	size_t padd = Utils::headerANDpadding(currAddr, align, sizeof(HEADER));
	if (offset + padd + _size > size)
		return nullptr;

	offset += padd;

	size_t next = currAddr + padd;
	size_t head = next - sizeof(HEADER);
	HEADER allocHead{ padd };
	HEADER* ptr = (HEADER*)head;
	ptr = &allocHead;

	offset += _size;
	used = offset;
	top = std::max(top, used);
#ifdef _DEBUG
	std::cout << "Alloc" << "\t@C " << (void*)currAddr << "\t@N " << (void*)next << "\tO " << offset << "\tP " << padd << std::endl;
#endif
	return (void*)next;
}

void Allocator::Free(void* pointer)
{
	size_t currAddr = (size_t)pointer;
	size_t headerAddr = currAddr - sizeof(HEADER);
	const HEADER* allocHeader{ (HEADER*)headerAddr };
	offset = currAddr - allocHeader->padding - (size_t)curr;
	used = offset;
#ifdef _DEBUG
	std::cout << "Free" << "\t@C " << (void*)currAddr << "\t@F " << (void*)((char*)curr + offset) << "\tO " << offset << std::endl;
#endif
}

void Allocator::init()
{
	if (curr != nullptr)
		free(curr); //mb use implementation free in os
	curr = malloc(size);
	offset = 0;
}

void Allocator::clear()
{
	offset = 0;
	used = 0;
	top = 0;
}
