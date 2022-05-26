#pragma once
#include "List.h"
#include <assert.h>


class Allocator {
public:
	size_t totalSize;
	size_t chunkSize;
	size_t chunksPerBlock;
	size_t used = 0;
	void* startPtr = nullptr;


	struct Chunk {};
	using Node = List<Chunk>::Node;
	List<Chunk> list;

	Allocator(size_t chunkSize, size_t chunksPerBlock) {
		assert(chunkSize >= 8 && "Chunk size must be greater or equal to 8");

		this->chunkSize = chunkSize;
		this->chunksPerBlock = chunksPerBlock;
		Init();
	}

	void* AllocateBlock() {

		size_t blockSize = chunkSize * chunksPerBlock;

		Chunk* blockBegin = reinterpret_cast<Chunk*>(malloc(blockSize));

		for (int i = 0; i < chunksPerBlock; i++) {
			size_t address = (size_t)blockBegin + i * chunkSize;
			cout << "Addres [" << i << "] segment: #" << (Node*)address << endl;
			list.Push((Node*)address);
		}

		list.ShowSegments(list.head);

		return blockBegin;

	}

	void* Allocate(size_t allocationSize) {

		assert(allocationSize <= this->chunkSize && "Allocation size must be less or equal to chunk size");

		Node* freePosition = list.Pop();

		if (freePosition == NULL) {
			AllocateBlock();
			freePosition = list.Pop();
		}

		used += chunkSize;
		return (void*)freePosition;
	}


	void Init() {
		startPtr = malloc(totalSize);
		used = 0;
		AllocateBlock();
	}


	void Free(void* ptr) {
		std::cout << "Free segment: #" << (Node*)ptr << std::endl;
		used -= chunkSize;
		list.Push((Node*)ptr);
	}

};
