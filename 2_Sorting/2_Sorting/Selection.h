#pragma once
#include <utility>		//标准库的swap函数在这里

class Selection {
	template<typename Iter>
	void sort(const Iter& begin, const Iter& end) {
		using std::swap;	//使用swap的准备，会优先使用自定义的，再使用标准库的
		for (Iter i = begin; i != end; ++i) {
			Iter min = i;
			for (Iter j = i; j != end; ++j) {
				if (*j < *min) {
					min = j;
				}
			}
			swap(*i, *min);
		}
	}
};

