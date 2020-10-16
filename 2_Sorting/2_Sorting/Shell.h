#pragma once
#include <utility>		

class Shell {
public:
	template<typename Iter>
	static void sort(const Iter& begin, const Iter& end) {
		using std::swap;
		int N = end - begin;
		int h = 1;
		while (h < N / 3) { h = 3 * h + 1; }
		while (h >= 1) {
			for (Iter i = begin + h; i != end; ++i) {
				for (Iter j = i; j >=  begin + h && (*j < *(j - h)); j -= h) {	//必须用>= , != 不行
					swap(*j, *(j - h));
				}
			}
			h /= 3;
		}
	}
};