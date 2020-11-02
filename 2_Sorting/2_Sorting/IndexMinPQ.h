/*
	索引优先队列
*/

#pragma once
#include <vector>
#include <functional>
#include <unordered_map>

template <typename Key, typename Value>
class IndexMinPQ {
	std::unordered_map<Key, Value> keys;
	std::vector<Key> pq;

	std::function<bool(const Value& a, const Value& b)> lessfun;

	bool less(const Key& a, const Key& b) {
		return lessfun(keys[a], keys[b]);
	}

	struct Entry {
		const Key& key;
		const Value& value;
	};

public:
	using size_type = typename std::vector<Value>::size_type;
	IndexMinPQ() : lessfun(std::less<Value>()) {};
	IndexMinPQ(const std::function<bool(const Value& a, const Value& b)>& less) : lessfun(less) {};

	void insert(const Key& key, const Value& item) {
		if (keys.find(key) != keys.end())
			return change(key, item);
		keys.emplace(key, item);
		pq.push_back(key);
		swim(pq.size() - 1);
	}

	Entry top() {
		return { pq[0], keys[pq[0]] };
	}

	void pop() {
		if (pq.size() == 1) {
			pq.pop_back();
			keys.clear();
		}
		else {
			using std::swap;
			keys.erase(pq[0]);
			swap(pq[0], *--pq.end());
			pq.pop_back();
			sink(0);
		}
	}

	bool empty() const {
		return pq.size() == 0;
	}

	size_type size() const {
		return pq.size();
	}

	void change(Key k, Value v) {
		int i = std::find(pq.begin(), pq.end(), k) - pq.begin();
		if (i != pq.size()) {
			keys[k] = v;
			swim(i);
			sink(i);
		}

	}

private:
	void swim(size_type k) {
		auto tmp = std::move(pq[k]);
		auto pri = (k - 1) / 2;
		while (k > 0 && less(tmp, pq[pri])) {
			pq[k] = std::move(pq[pri]);
			k = pri;
			pri = (k - 1) / 2;
		}
		pq[k] = std::move(tmp);
	}

	void sink(size_type k) {
		auto tmp = std::move(pq[k]);
		size_type next = 2 * k + 1;
		while (next < pq.size()) {
			if (next != pq.size() - 1 && less(pq[next + 1], pq[next]))
				++next;
			if (less(tmp, pq[next]))
				break;
			pq[k] = std::move(pq[next]);
			k = next;
			next = 2 * k + 1;
		}
		pq[k] = std::move(tmp);
	}
};

template <typename Key, typename Value>
class IndexMinPQ_2 {
	std::unordered_map<Key, Value> keys;
	std::vector<Key> pq;
	//std::unordered_map<Key, int> qp;

	/*
	
			待实现
			
	*/

	std::function<bool(const Value& a, const Value& b)> lessfun;

	bool less(const Key& a, const Key& b) {
		return lessfun(keys[a], keys[b]);
	}

	struct Entry {
		const Key& key;
		const Value& value;
	};

public:
	using size_type = typename std::vector<Value>::size_type;
	IndexMinPQ_2() : lessfun(std::less<Value>()) {};
	IndexMinPQ_2(const std::function<bool(const Value& a, const Value& b)>& less) : lessfun(less) {};

	void insert(const Key& key, const Value& item) {
		if (keys.find(key) != keys.end())
			return change(key, item);
		keys.emplace(key, item);
		pq.push_back(key);
		swim(pq.size() - 1);
	}

	Entry top() {
		return { pq[0], keys[pq[0]] };
	}

	void pop() {
		if (pq.size() == 1) {
			pq.pop_back();
			keys.clear();
		}
		else {
			using std::swap;
			keys.erase(pq[0]);
			swap(pq[0], *--pq.end());
			pq.pop_back();
			sink(0);
		}
	}

	bool empty() const {
		return pq.size() == 0;
	}

	size_type size() const {
		return pq.size();
	}

	void change(Key k, Value v) {
		int i = std::find(pq.begin(), pq.end(), k) - pq.begin();
		if (i != pq.size()) {
			keys[k] = v;
			swim(i);
			sink(i);
		}

	}

private:
	void swim(size_type k) {
		auto tmp = std::move(pq[k]);
		auto pri = (k - 1) / 2;
		while (k > 0 && less(tmp, pq[pri])) {
			pq[k] = std::move(pq[pri]);
			k = pri;
			pri = (k - 1) / 2;
		}
		pq[k] = std::move(tmp);
	}

	void sink(size_type k) {
		auto tmp = std::move(pq[k]);
		size_type next = 2 * k + 1;
		while (next < pq.size()) {
			if (next != pq.size() - 1 && less(pq[next + 1], pq[next]))
				++next;
			if (less(tmp, pq[next]))
				break;
			pq[k] = std::move(pq[next]);
			k = next;
			next = 2 * k + 1;
		}
		pq[k] = std::move(tmp);
	}
};