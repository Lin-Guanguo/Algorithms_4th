#pragma once
#include <stdexcept>
#include <iostream>
#include <queue>
#include <utility>

template<typename Key, typename Value>
class RedBlackBST {
private:
	class TreeNode {
	public:
		TreeNode(Key k, Value v,  bool isRed, size_t n = 1, TreeNode* left = nullptr, TreeNode* right= nullptr)
			:key(k), value(v), isRed(isRed), size(n), left(left), right(right){}
		Key key;
		Value value;
		bool isRed;
		TreeNode* left, * right;
		size_t size;
	};
	using Node = TreeNode*;
	Node root = nullptr;
public:
	RedBlackBST() {}
	void print(std::ostream& out) 
	{
		out << "size = " << size() << ", height = " << height() << " ";
		print(root, out);
	}

	void printTree(std::ostream& out) 
	{
		out << "size = " << size() << ", height = " << height() << " \n";
		std::queue<std::pair<Node, bool>> q;
		q.push({ root,true });
		while (!q.empty()) {
			Node x = q.front().first;
			bool isLineEnd = q.front().second;
			if (x != nullptr) {
				out << "[" << x->key << " : " << x->value << " : " << (x->isRed ? "RED  ":"BLACK") << "] " 
					<< (isLineEnd ? "\n" : "");
				q.push({ x->left, false });
				q.push({ x->right, isLineEnd });
			}
			q.pop();
		}
	}

	int height() 
	{
		int max = 0;
		height(root, 0, max);
		return max;
	}
private:
	void print(Node node, std::ostream& out) 
	{
		if (node != nullptr) {
			print(node->left, out);
			out << "[" << node->key << " : " << node->value << " : " << (node->isRed ? "RED  ":"BLACK")<< "] ";
			print(node->right, out);
		}
	}

	void height(Node h, int count, int& max)
	{
		if (h == nullptr) {
			if (count > max) max = count;
			return;
		}
		height(h->left, count + 1, max);
		height(h->right, count + 1, max);
	}

public:
	size_t size() 
	{
		return root->size;
	}
private:
	size_t size(Node n) 
	{
		if (n == nullptr) return 0;
		else return n->size;
	}

public:
	Value get(Key k)
	{
		return get(root, k)->value;
	}
private:
	Node get(Node node, Key k)
	{
		if (node == nullptr) throw std::out_of_range("BST get out of range");
		else if (node->key == k) 
			return node;
		else if (node->key > k) 
			return get(node->left, k);
		else
			return get(node->right, k);
	}

public:
	Key select(size_t k)
	{
		return select(root, k)->key;
	}
private:
	Node select(Node node, size_t k)
	{
		if (node == nullptr) throw std::out_of_range("select key out of range");
		size_t t = size(node->left);
		if		(t > k) return select(node->left, k);
		else if (t < k)  return select(node->right, k - t - 1);
		else return node;
	}

public:
	size_t rank(Key k) 
	{
		return rank(root, k);
	}
private:
	size_t rank(Node node, Key k)
	{
		if (node == nullptr) return 0;
		else if (node->key > k) return rank(node->left, k);
		else if (node->key < k) return rank(node->right, k) + size(node->left) + 1;
		else return size(node->left);
	}

public:
	Key min() 
	{
		return min(root)->key;
	}
	Key max() 
	{
		return max(root)->key;
	}
private:
	Node min(Node node) 
	{
		if (node->left == nullptr) return node;
		else return min(node->left);
	}
	Node max(Node node) {
		if (node->right == nullptr) return node;
		else return min(node->right);
	}

private:
	bool isRed(Node node) 
	{
		return node == nullptr ? false : node->isRed;
	}

	Node rotateLeft(Node h) 
	{
		Node x = h->right;
		h->right = x->left;
		x->left = h;
		x->isRed = h->isRed;
		h->isRed = true;
		x->size = h->size;
		h->size = size(h->left) + size(h->right) + 1;
		return x;
	}

	Node rotateRight(Node h) 
	{
		Node x = h->left;
		h->left = x->right;
		x->right = h;
		x->isRed = h->isRed;
		h->isRed = true;
		x->size = h->size;
		h->size = size(h->left) + size(h->right) + 1;
		return x;
	}

	void flipColors(Node h)
	{
		h->isRed = true;
		h->left->isRed = false;
		h->right->isRed = false;
	}

public:
	void put(Key k, Value v) 
	{
		root = put(root, k, v);
	}
private:
	Node put(Node h, Key k, Value v)
	{
		if (h == nullptr)
			return new TreeNode(k, v, true);
		if (h->key > k) h->left = put(h->left, k, v);
		else if (h->key < k) h->right = put(h->right, k, v);
		else h->value = v;

		if (isRed(h->right) && !isRed(h->left)) h = rotateLeft(h);
		if (isRed(h->left) && isRed(h->left->left)) h = rotateRight(h);
		if (isRed(h->left) && isRed(h->right)) flipColors(h);
		h->size = h->size = size(h->left) + size(h->right) + 1;
		return h;
	}

public:

private:


};