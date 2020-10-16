#pragma once
/*
	线性查找树
*/
#include <memory>
#include <stdexcept>


/*
	改成unique_ptr更高效，正在改，麻烦事不少
	shared_ptr + weak_ptr 也不错
*/

template<typename Key, typename Value>
class SequentialSearchST
{
public:
	void put(const Key& k, const Value& v);
	Value& get(const Key& k);
	Value& operator[](const Key& k);
	bool contains(const Key& k);
private:
	struct Node {
		Node(Key k, Value v, std::unique_ptr<Node> next) : key(k), value(v), next(next) {}
		Key key; Value value;
		std::unique_ptr<Node> next;
	};
	std::unique_ptr<Node> first = nullptr;
};

template<typename Key, typename Value>
inline void SequentialSearchST<Key, Value>::put(const Key& k, const Value& v) {
	for (auto i = first.get(); i != nullptr; i = i->next.get()) {
		if (i->key == k) {
			i->value = v;
			return;
		}
	}
	first = std::make_unique<Node>(k, v, first);	//从头加，可以省略判断空链表的操作
	return;
}

template<typename Key, typename Value>
inline Value& SequentialSearchST<Key, Value>::get(const Key& k)
{
	for (auto i = first.get(); i != nullptr; i = i->next.get()) {
		if (i->key == k) {
			return i->value;
		}
	}
	throw std::out_of_range("ST out of range");
}

template<typename Key, typename Value>
inline Value& SequentialSearchST<Key, Value>::operator[](const Key& k)
{
	for (auto i = first.get(); i != nullptr; i = i->next.get()) {
		if (i->key == k) {
			return i->value;
		}
	}
	first = std::make_unique<Node>(k, Value(), first);
	return first->value;
}

template<typename Key, typename Value>
inline bool SequentialSearchST<Key, Value>::contains(const Key& k)
{
	for (auto i = first.get(); i != nullptr; i = i->next.get()) {
		if (i->key == k) {
			return true;
		}
	}
	return false;
}

