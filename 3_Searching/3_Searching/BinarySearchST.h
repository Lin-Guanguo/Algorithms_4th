#pragma once
/*
	二分查找树
*/
#include <memory>
#include <stdexcept>
#include <vector>


template<typename Key, typename Value>
class BinarySearchST
{
public:
	using size_type = typename std::vector<Key>::size_type;

	void put(Key, Value);
	Value& get(Key);
	Value& operator[](Key);
	size_type size() const { return keys.size(); }
	
private:
	std::vector<Key> keys;
	std::vector<Value> values;
	void swap(size_type, size_type);
};

template<typename Key, typename Value>
inline void BinarySearchST<Key, Value>::put(Key key, Value val)
{
	try {
		get(key) = val;
		return;
	}
	catch(std::out_of_range){
		keys.push_back(key);
		values.push_back(val);
		for (auto v = keys.size() - 1; v != 0 && keys[v] < keys[v - 1]; --v) {	//按key排序
			swap(v - 1, v);
		}
		return;
	}
}

template<typename Key, typename Value>
inline Value& BinarySearchST<Key, Value>::get(Key key)
{
	size_type lo = 0;
	size_type hi = keys.size();
	while (lo < hi) {
		size_type mid = (lo + hi) / 2;
		if (keys[mid] < key) { lo = mid + 1; }
		else if (key < keys[mid]) { hi = mid; }
		else if (keys[mid] == key) { return values[mid]; }
	}
	throw std::out_of_range("ST out of range");
}

template<typename Key, typename Value>
inline Value& BinarySearchST<Key, Value>::operator[](Key key)
{
	try {
		return get(key);
	}
	catch (std::out_of_range) {
		put(key, Value());
		return get(key);
	}
}

template<typename Key, typename Value>
inline void BinarySearchST<Key, Value>::swap(size_type a, size_type b)
{
	using std::swap;
	swap(keys[a], keys[b]);
	swap(values[a], values[b]);
}
