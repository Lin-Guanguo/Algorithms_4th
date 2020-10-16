#pragma once
#include <utility>		

class Insertion {
	template<typename Iter>
	void sort(const Iter& begin, const Iter& end) {
		using std::swap;
		if (begin == end) { return; }	//空容器的排序
		for (Iter i = begin + 1; i != end; ++i) {
			for (Iter j = i; j != begin && (*j < *(j - 1)); --j) {
				//条件(*j < *(j - 1)写在for循环里，可以减少循环次数
				swap(*j, *(j - 1));
			}
		}
	}
};