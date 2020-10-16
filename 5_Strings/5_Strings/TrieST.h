#pragma once
#include <string>
#include <string_view>
#include <stdexcept>
#include <iostream>
#include <vector>
#include <optional>
#include <memory>
#include <unordered_map>

using std::string;
using std::vector;
using std::unordered_map;
using std::shared_ptr;
using std::weak_ptr;

template<typename Value>
class TrieST
{
private:
	static constexpr unsigned R = 128;
	struct Node
	{
		Node() { for (auto& i : next) i = nullptr; }
		std::optional<Value> value;
		Node* next[R];
	};
	Node* root;
	unsigned int size = 0;;
public:
	unsigned getSize() const { return size; }
	void put(const string& key, const Value& value) 
	{
		root = put(root, key, value, 0);
		storeChange();
	}

private:
	Node* put(Node* x, const string& key, const Value& value, unsigned d)
	{
		if (x == nullptr) x = new Node();
		if (d == key.length()) {			
			if (!x->value)		//When an object of type optional<T> is contextually converted to bool, the conversion returns true if the object contains a value and false if it does not contain a value.
				++size;
			x->value = value; 
			return x; 
		}
		char c = key[d];
		x->next[c] = put(x->next[c], key, value, d + 1);
		return x;
	}

public:
	const Value& get(const string& key) 
	{
		auto x = get(root, key, 0);
		if (x == nullptr) throw std::out_of_range("ST can't find such key : " + key);
		return x->value.value();
	}

private:
	Node* get(Node* x, const string& key, unsigned d)
	{
		if (x == nullptr)  return nullptr; //此处不抛异常，兼容其他方法
		if (d == key.length()) return x;
		char c = key[d];
		return get(x->next[c], key, d + 1);
	}
	
public:
	void deleteKey(const string& key) 
	{
		root = deleteKey(root, key, 0);
		--size;
		storeChange();
	}

private:
	Node* deleteKey(Node* x, const string& key, unsigned d) 
	{
		if (x == nullptr) throw std::out_of_range("can't find such key to delete");
		if (d == key.length()) x->value.reset();
		else {
			char c = key[d];
			x->next[c] = deleteKey(x->next[c], key, d + 1);
		}

		if (x->value) return x;

		for (auto& p : x->next)
			if (p != nullptr) return x;

		delete x; return nullptr;
	}

public:
	vector<string> keys()
	{
		return keysWithPrefix("");
	}
															//优化: 缓存+返回string_view
	vector<string> keysWithPrefix(const string& pre) 
	{
		vector<string> res{}; 
		res.reserve(size);
		collect(get(root, pre, 0), pre, res);
		res.shrink_to_fit();
		return res;
	}

private:
	void collect(Node* x, string pre, vector<string>& res)
	{
		if (x == nullptr) return;
		if (x->value) res.push_back(pre);
		for (char c = 0; c < R; ++c)
			collect(x->next[c], pre + c, res);
	}

public:
	vector<string> keysThatMatch(const string& pat)
	{
		vector<string> res{};
		res.reserve(size);
		collect(root, {}, pat, res);
		res.shrink_to_fit();
		return res;
	}

private:
	void collect(Node* x, string pre, const string& pat, vector<string>& res)
	{
		int d = pre.length();
		if (x == nullptr) return;
		if (d == pat.length()) {
			if(x->value)
				res.push_back(pre);
		}
		else {
			char next = pat[d];
			if (next == '.')
				for (char c = 0; c < R; ++c)
					collect(x->next[c], pre + c, pat, res);
			else
				collect(x->next[next], pre + next, pat, res);
		}
	}



	//以下是骚操作部分
	//keys缓存
	//有待优化
private:
	void storeChange()
	{
		keysBuffer.reset();
	}
	weak_ptr<vector<string>> keysBuffer;
public:
	class iterator : public vector<string>::iterator
	{
		shared_ptr<vector<string>> keysBuffer;
	public:
		iterator(vector<string>::iterator arg, shared_ptr<vector<string>> keysBuffer)
			:vector<string>::iterator(arg), keysBuffer(keysBuffer) {}
	};

	iterator begin() 
	{
		shared_ptr<vector<string>> p = keysBuffer.lock();
		if (!p) {
			p.reset(new vector<string>{ std::move(keys()) });
			keysBuffer = p;
		}
		return iterator{ p->begin(), p };
	}

	iterator end() 
	{
		shared_ptr<vector<string>> p = keysBuffer.lock();
		if (!p) {
			p.reset(new vector<string>{ std::move(keys()) });
			keysBuffer = p;
		}
		return iterator{ p->end(), p };
	}

};