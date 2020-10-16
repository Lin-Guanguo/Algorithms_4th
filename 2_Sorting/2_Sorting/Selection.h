#pragma once
#include <utility>		//��׼���swap����������

class Selection {
	template<typename Iter>
	void sort(const Iter& begin, const Iter& end) {
		using std::swap;	//ʹ��swap��׼����������ʹ���Զ���ģ���ʹ�ñ�׼���
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

