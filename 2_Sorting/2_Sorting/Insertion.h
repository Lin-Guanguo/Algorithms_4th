#pragma once
#include <utility>		

class Insertion {
	template<typename Iter>
	void sort(const Iter& begin, const Iter& end) {
		using std::swap;
		if (begin == end) { return; }	//������������
		for (Iter i = begin + 1; i != end; ++i) {
			for (Iter j = i; j != begin && (*j < *(j - 1)); --j) {
				//����(*j < *(j - 1)д��forѭ������Լ���ѭ������
				swap(*j, *(j - 1));
			}
		}
	}
};