#pragma once
#include <utility>
#include <vector>
#include <functional>

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
		while (2 * k < end - begin) {										// < 书上 N = end - begin - 1, 所以 2*k <= N
			auto j = 2 * k;
			if (j != end - begin - 1 && compare(begin, j, j + 1)) { ++j; }	//取较大的子节点，j != end - begin - 1 防止取到最后一个二叉树的空节点，可以写 != 和 <
			if (!compare(begin, k, j)) { break; }							//! 优先级高与><=
			swap(*(begin + k), *(begin + j));
			k = j;
		}
	}
private:
	template<typename Iter>
	static bool compare(const Iter& begin, int a, int b) {
		return *(begin + a) < *(begin + b);									//更改<号，可更改排序顺序，可以封装的更好，不过没必要
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

template<typename Value>
class MinPQ {
	std::vector<Value> itok;
	std::function<bool(const Value& a, const Value& b)> less;
public:
	using size_type = typename std::vector<Value>::size_type;
	MinPQ() :itok(), less(std::less<Value>()) {};
	MinPQ(const std::function<bool(const Value& a, const Value& b)>& less) : less(less) {};

	void insert(const Value& that) {
		itok.push_back(that);
		swim(itok.size() - 1);
	}

	const Value& top() {
		return itok[0];
	}

	void pop() {
		if (itok.size() == 1) {
			itok.pop_back();
		}
		else {
			using std::swap;
			swap(itok[0], *--itok.end());
			itok.pop_back();
			sink(0);
		}
	}

	bool empty() {
		return itok.size() == 0;
	}

	size_type size() {
		return itok.size();
	}

private:
	void swim(size_type k) {
		auto tmp = std::move(itok[k]);
		auto pri = (k - 1) / 2;
		while (k > 0 && less(tmp, itok[pri])) {
			itok[k] = std::move(itok[pri]);
			k = pri;
			pri = (k - 1) / 2;
		}
		itok[k] = std::move(tmp);
	}

	void sink(size_type k) {
		auto tmp = std::move(itok[k]);
		size_type next = 2 * k + 1;
		while (next < itok.size()) {
			if (next != itok.size() - 1 && less(itok[next + 1], itok[next]))
				++next;
			if (less(tmp, itok[next]))
				break;
			itok[k] = std::move(itok[next]);
			k = next;
			next = 2 * k + 1;
		}
		itok[k] = std::move(tmp);
	}

};

