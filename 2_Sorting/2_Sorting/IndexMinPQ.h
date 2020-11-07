/*
	索引优先队列
*/

#pragma once
#include <vector>
#include <functional>
#include <list>
#include <unordered_map>
#include <cassert>

template <typename Key, typename Value>
class IndexMinPQ {
	std::unordered_map<Key, Value> ktov;
	std::unordered_map<Key, int> ktoi;
	std::vector<Key> itok;	//堆

	std::function<bool(const Value& a, const Value& b)> less;

	struct Entry {
		const Key& key;
		const Value& value;
	};
public:
	using size_type = typename std::vector<Key>::size_type;
	IndexMinPQ() : less(std::less<Value>()) {};
	IndexMinPQ(const std::function<bool(const Value& a, const Value& b)>& less) : less(less) {};

	void insert(const Key& key, const Value& value) {
		if (ktov.find(key) != ktov.end())
			return change(key, value);
		ktov.emplace(key, value);
		itok.push_back(key);
		ktoi.emplace(key, itok.size() - 1);
		swim(itok.size() - 1);
		assert(ktov.size() == ktoi.size() && ktov.size() == itok.size());
		assert(ktov[itok[ktoi[key]]] == value);
	}

	Entry top() {
		return Entry{ itok[0], ktov[itok[0]] };
	}
		
	void pop() {
		if (itok.size() == 1) {
			ktoi.erase(itok[0]);
			ktov.erase(itok[0]);
			itok.pop_back();
		}
		else {
			ktoi.erase(itok[0]);
			ktov.erase(itok[0]);
			itok[0] = *--itok.end();
			itok.pop_back();
			sink(0);
		}
		assert(ktov.size() == ktoi.size() && ktov.size() == itok.size());
	}

	bool empty() const {
		return itok.size() == 0;
	}

	size_type size() const {
		return itok.size();
	}

	void change(const Key& key, const Value& value) {
		ktov[key] = value;
		sink(ktoi[key]);
		swim(ktoi[key]);
		assert(ktov.size() == ktoi.size() && ktov.size() == itok.size());
		assert(ktov[itok[ktoi[key]]] == value);
	}

private:
	void swim(size_type i) {
		auto tmpk = itok[i];
		auto pri = (i - 1) / 2;
		while (i > 0 && less(ktov[tmpk], ktov[itok[pri]])) {
			itok[i] = std::move(itok[pri]);
			ktoi[itok[i]] = i;
			i = pri;
			pri = (i - 1) / 2;
		}
		itok[i] = std::move(tmpk);
		ktoi[itok[i]] = i;
	}

	void sink(size_type i) {
		auto tmpk = std::move(itok[i]);
		size_type next = 2 * i + 1;
		while (next < itok.size()) {
			if (next != itok.size() - 1 && less(ktov[itok[next + 1]], ktov[itok[next]]))
				++next;
			if (less(ktov[tmpk], ktov[itok[next]]))
				break;
			itok[i] = std::move(itok[next]);
			ktoi[itok[i]] = i;
			i = next;
			next = 2 * i + 1;
		}
		itok[i] = std::move(tmpk);
		ktoi[itok[i]] = i;
	}
};



