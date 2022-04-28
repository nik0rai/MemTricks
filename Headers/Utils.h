#pragma once
#include <cstddef>
class Utils
{
public:
	static const size_t padding(size_t base, size_t allign) {
		const size_t mult = 1 + (base / allign);
		const size_t padding = (mult * allign) - base;
		return padding;
	}

	static const size_t headerANDpadding(size_t base, size_t allign, size_t header) {
		size_t padd = padding(base, allign);

		if (padd < header) {
			header -= padd; //we are calculating next aligned addr for header to fit in
			if (header % allign > 0) padd += allign * (1 + (header / allign));
			else padd += allign * (header / allign);
		}
		return padd;
	}
};

