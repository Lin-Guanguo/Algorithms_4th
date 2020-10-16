#pragma once
#include <stdexcept>
#include <iostream>
#include <queue>
#include <utility>

template<typename Key, typename Value>
class BST {
private:
	class TreeNode {
	public:
		TreeNode(Key k, Value v, size_t n = 1, TreeNode* left = nullptr, TreeNode* right= nullptr)
			:key(k), value(v), size(n), left(left), right(right){}
		Key key;
		Value value;
		TreeNode* left, * right;
		size_t size;
	};
	using Node = TreeNode*;
	Node root = nullptr;
public:
	BST() {}
	void print(std::ostream& out) 
	{
		out << "size = " << size()<< ", height = " << height() << " \n";
		print(root, out);
		out << "\n";
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
				out << "[" << x->key << " : " << x->value << "] " << (isLineEnd ? "\n" : "");
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
			out << "[" << node->key << " : " << node->value << "] ";
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
	Key min() {
		return min(root)->key;
	}
	Key max() {
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

public:
	void put(Key k, Value v) 
	{
		root = put(root, k, v);
	}
private:
	Node put(Node node, Key k, Value v)	
	{
		if (node == nullptr) return new TreeNode(k, v);
		else if (node->key > k) node->left = put(node->left, k, v);
		else if (node->key < k) node->right = put(node->right, k, v);
		else node->value = v;
		node->size = size(node->left) + size(node->right) + 1;
		return node;
	}

public:
	void deleteMin() {
		root = deleteMin(root);
	}
	void deleteMax() {
		root = deleteMax(root);
	}
private:
	Node deleteMin(Node node) 
	{
		if (node->left == nullptr) {
			auto right = node->right;
			delete node;
			return right;
		}
		else {
			node->left = deleteMin(node->left);
			node->size = size(node->left) + size(node->right) + 1;
			return node;
		}
	}
	Node deleteMinDontFree(Node node) 
	{
		if (node->left == nullptr) {
			return node->right;
		}
		else {
			node->left = deleteMin(node->left);
			node->size = size(node->left) + size(node->right) + 1;
			return node;
		}
	}
	Node deleteMax(Node node) 
	{
		if (node->right == nullptr) {
			auto left = node->left;
			delete node;
			return left;
		}
		else {
			node->right = deleteMin(node->right);
			node->size = size(node->left) + size(node->right) + 1;
			return node;
		}
	}


public:
	void deleteKey(Key k) 
	{
		root = deleteKey(root, k);
	}
private:
	Node deleteKey(Node node, Key k)
	{
		if (node == nullptr) throw std::out_of_range("can't find this key to delete");
		if		(node->key > k) node->left = deleteKey(node->left, k);
		else if (node->key < k) node->right = deleteKey(node->right, k);
		else {
			if (node->right == nullptr) return deleteMax(node);
			//else if	(node->left == nullptr) return deleteMin(node);	//Ã»±ØÒª
			else {
				Node replace = min(node->right);
				node->right = deleteMinDontFree(node->right);
				replace->left = node->left;
				replace->right = node->right;
				delete node;
				node = replace;
			}
		}
		node->size = size(node->left) + size(node->right) + 1;
		return node;
	}


};