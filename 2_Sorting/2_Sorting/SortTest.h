#pragma once	
#include <chrono>
#include <iostream>

template<typename Iter>
bool isSorted(const Iter& begin, const Iter& end) {
	for (Iter i = begin + 1 ; i != end; ++i) {
		if (*i < *(i - 1)) {
			return false;
		}
	}
	return true;
}

template<typename Iter>
int SortTest(const Iter& begin, const Iter& end, void(*s)(const Iter&, const Iter&)) {
	int time0 = clock();
	(*s)(begin, end);
	int time1 = clock();
	if (isSorted(begin, end)) {
		std::cout << "sort secceed spend time = " << time1 - time0 << std::endl;
		return time1 - time0;
	}
	else {
		std::cout << "sort failed" << std::endl;
		return 0;
	}
}