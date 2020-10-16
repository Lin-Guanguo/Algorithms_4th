#pragma once
#include <utility>
#include <vector>

class BinaryHeap {
public:
	template<typename Iter>
	static void swim(const Iter& begin, const Iter& end, int k) {
		using std::swap;
		while (k > 1 && compare(begin, k / 2, k)) {
			swap(*(begin + k / 2), *(begin + k));
			k /= 2;
		}
	}
	template<typename Iter>
	static void sink(const Iter& begin, const Iter& end, int k) {
		using std::swap;
		while (2 * k < end - begin) {										// < ���� N = end - begin - 1, ���� 2*k <= N
			auto j = 2 * k;
			if (j != end - begin - 1 && compare(begin, j, j + 1)) { ++j; }	//ȡ�ϴ���ӽڵ㣬j != end - begin - 1 ��ֹȡ�����һ���������Ŀսڵ㣬����д != �� <
			if (!compare(begin, k, j)) { break; }							//! ���ȼ�����><=
			swap(*(begin + k), *(begin + j));
			k = j;
		}
	}
private:
	template<typename Iter>
	static bool compare(const Iter& begin, int a, int b) {
		return *(begin + a) < *(begin + b);									//����<�ţ��ɸ�������˳�򣬿��Է�װ�ĸ��ã�����û��Ҫ
	}
};


class HeapSort {
public:
	template<typename Iter>
	static void sort(const Iter& begin, const Iter& end) {
		int N = end - begin;
		for (int k = (N - 1) / 2; k != 0; --k) {
			BinaryHeap::sink(begin, end, k);
		}
		while (N > 1) {
			using std::swap;
			swap(*(begin + 1), *(begin + --N));
			BinaryHeap::sink(begin, begin + N, 1);
		}
	}
};

template<typename Item>
class MaxPQ {
public:
	using size_type = typename std::vector<Item>::size_type;	//typename����Ҫ����Ȼ��Ĭ��ʶ��Ϊ��̬��Ա������������
	MaxPQ() :pq(1) {};
	void insert(const Item& that) {
		pq.push_back(that);
		swim(pq.size() - 1);
	}
	const Item& top() {
		return pq[1];
	}
	void pop() {
		using std::swap;
		swap(pq[1], *--pq.end());
		pq.pop_back();
		sink(1);
	}
	bool empty() {
		return pq.size() == 1;
	}
	size_type size() {
		return pq.size() - 1;
	}
private:
	std::vector<Item> pq;
	void swim(size_type k) {
		using std::swap;
		while (k > 1 && pq[k / 2] < pq[k]) {
			swap(pq[k / 2], pq[k]);
			k /= 2;
		}
	}
	void sink(size_type k) {
		using std::swap;
		while (2 * k < pq.size()) {										
			auto j = 2 * k;
			if (j != pq.size() - 1 && pq[j] < pq[j+1]) { ++j; }	
			if (pq[j] < pq[k]) { break; }
			swap(pq[k], pq[j]);
			k = j;
		}
	}
};

