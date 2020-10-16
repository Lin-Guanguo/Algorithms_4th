#pragma once
#include <string>
#include <string_view>
#include <stdexcept>
#include <iostream>
#include <vector>
#include <optional>

using std::string;
using std::vector;

template<typename Value>
class Trie3ST
{
private:
	struct Node
	{
		Node(char c) : c(c) {; left = mid = right = nullptr; }
		char c;
		std::optional<Value> value;
		Node* left, * mid, * right;
	};
	Node* root = nullptr;
	unsigned int size = 0;
public:
	unsigned getSize() const { return size; }

	const Value& get(const string& key)
	{
		auto x = get(root, key, 0);
		if (x == nullptr) throw std::out_of_range("can't find such key to get");
		return x->value.value();
	}

private:
	Node* get(Node* x, const string& key, unsigned d)
	{
		if (x == nullptr) return nullptr;
		char c = key[d];
		if (c < x->c)
			return get(x->left, key, d);
		else if (c > x->c)
			return get(x->right, key, d);
		else if (d < key.length() - 1)
			return get(x->mid, key, d + 1);
		else
			return x;
	}

public:
	void put(const string& key, const Value& value)
	{
		root = put(root, key, value, 0);
	}

private:
	Node* put(Node* x, const string& key, const Value& value, unsigned d)
	{
		char c = key[d];
		if (x == nullptr) x = new Node(c);
		if (c < x->c)
			x->left = put(x->left, key, value, d);
		else if (c > x->c)
			x->right = put(x->right, key, value, d);
		else if (d < key.length() - 1)
			x->mid = put(x->mid, key, value, d + 1);
		else {
			if (!x->value)
				++size;
			x->value = value;
		}
		return x;
	}

};