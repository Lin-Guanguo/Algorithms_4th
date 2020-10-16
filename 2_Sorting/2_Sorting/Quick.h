#pragma once
#include <algorithm>									//std::random_shuffle
#include "Selection.h"

class Quick {
public:
	Quick() = delete;
public:
	template<typename Iter>
	static void sort(const Iter& begin, const Iter& end) {
		std::random_shuffle(begin, end);
		sort(begin, 0, end - begin);
	}
private:
	template<typename Iter>
	static void sort(const Iter& begin, int lo, int hi) {
		if (hi <= lo + 1) {								//必须<=， == 不行
			return;
		}
		int par = partition(begin, lo, hi);
		sort(begin, lo, par);
		sort(begin, par + 1, hi);						//切分元素不做排序，[lo, par), par,[par+1, hi)
	}

	template<typename Iter>
	static int partition(const Iter& begin, int lo, int hi) {
		using std::swap;
		Iter head = begin + lo;	
		Iter tail = begin + hi;	
		Iter v = begin + lo;							//第一个元素作切分
		while (true) {
			while (*++head < *v) {
				if (head == begin + hi - 1) { break; }	//head打成tial浪费好多时间
			}
			while (*v < *(--tail)) {
				if (tail == begin + lo) { break; }		//tail == begin + lo + 1 不行
			}
			if (head >= tail) { break; }
			swap(*head, *tail);
		}
		swap(*v, *tail);
		return tail - begin;
	}
};




class QuickPlus {
public:
	template<typename Iter>
	static void sort(const Iter& begin, const Iter& end) {
		std::random_shuffle(begin, end);
		sort(begin, 0, end - begin);
	}
private:
	template<typename Iter>
	static void sort(const Iter& begin, int lo, int hi) {
		if (hi <= lo + 10) {							//优化点
			Selection::sort(begin + lo, begin + hi);	//Selection效率比Insertion高
			return;
		}
		int par = partition(begin, lo, hi);
		sort(begin, lo, par);
		sort(begin, par + 1, hi);	
	}

	template<typename Iter>
	static int partition(const Iter& begin, int lo, int hi) {
		using std::swap;
		Iter head = begin + lo;
		Iter tail = begin + hi;
		Iter v = begin + lo;
		while (true) {
			while (*++head < *v) {	
				if (head == begin + hi - 1) { break; }	
			}
			while (*v < *--tail) {
				if (tail == begin + lo) { break; }		
			}
			if (head >= tail) { break; }
			swap(*head, *tail);
		}
		swap(*v, *tail);
		return tail - begin;
	}
};
