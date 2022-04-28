#pragma once
#include "Allocator.h"
#include <chrono>
#include <vector>
#include <time.h>
#include <ratio>
#include <string>
#include <iostream>
#include <vector>

class Tester
{	
	struct Result
	{
		std::chrono::milliseconds milliseconds;
		size_t memory;
	};
private:
	std::chrono::time_point<std::chrono::high_resolution_clock> timerStart;
	std::chrono::time_point<std::chrono::high_resolution_clock> End;
	std::chrono::milliseconds Elapsed;
	std::vector<void*>adresses;
	void print(Tester::Result r) {
		std::cout << "Memory used: " << r.memory
			<< " Ellapsed milliseconds: " << r.milliseconds.count() << std::endl;
	}
public:

	Result result(std::chrono::milliseconds&& ellapsedTime, size_t memoryUsed) {
		Result ans;
		ans.memory = memoryUsed; 
		ans.milliseconds = std::move(ellapsedTime);
		return ans;
	}

	void Allocation(Allocator* al, size_t size, size_t align) {
		Start();
		al->init();
		adresses.push_back(al->alloc(size, align));
		Stop();
		Result r = result(std::move(Elapsed), al->top);
		print(r);
	}
	void Freeing(Allocator* al, size_t block, size_t size, size_t allign) {
		Start();
		al->Free(adresses[block]);
		Stop();
		Result r = result(std::move(Elapsed), al->top);
		print(r);
	}
	void Start() noexcept { timerStart = std::chrono::high_resolution_clock::now(); }
	void Stop() noexcept {
		End = std::chrono::high_resolution_clock::now();
		Elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(End - timerStart);
	}
};

