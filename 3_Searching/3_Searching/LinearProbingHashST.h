#pragma once
#include <type_traits>
#include <stdexcept>
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <memory>

template<typename Key, typename Value>
class LinearProbingHashST {
private:
	size_t N = 0;
	size_t M;
	size_t minM;
	bool* haveKeys;
	Key* keys;
	Value* values;
public:
	LinearProbingHashST()
		:LinearProbingHashST(997)
	{}
	LinearProbingHashST(size_t M) 
	{
		this->M = M;
		this->minM = M;
		keys = (Key*)std::malloc(sizeof(Key) * M);
		values = (Value*)std::malloc(sizeof(Value) * M);
		haveKeys = (bool*)std::malloc(sizeof(bool) * M);
		for (size_t i = 0; i < M; ++i) haveKeys[i] = false;
	}

	void print(std::ostream& out) 
	{
		out << "size = " << N << ", " << "M = " << M << " " << std::endl;
		for (size_t i = 0; i < M; ++i) {
			if (haveKeys[i]) {
				out << "[ " << keys[i] << " : " << values[i] << " ]\t";
			}
		}
		out << std::endl;
	}

	void put(Key k, Value v) 
	{
		if (N > M / 2) resize(M * 2);
		auto i = hash(k);
		for (i; haveKeys[i]; ++i) 
			if (keys[i] == k) { values[i] = v; return; }	//这里不++N
		new(keys + i) Key(k);
		new(values + i) Value(v);
		haveKeys[i] = true;
		++N;
	}

	Value get(Key k)
	{
		for (auto i = hash(k); haveKeys[i]; i = (i + 1) % M)
			if (keys[i] == k)
				return values[i];
		throw std::out_of_range("can't find such key");
	}

	void deleteKey(Key k)
	{
		auto deleteLocate = [this](int i) {
			keys[i].~Key();
			values[i].~Value();
			haveKeys[i] = false;
			--N;
		};
		bool moveFlag = 0;
		auto i = hash(k);
		for (i; haveKeys[i]; ++i) {		//应该够跟高效的基于memcpy的算法，待实现
			if (moveFlag) {
				Key redoKey = std::move(keys[i]);
				Value redoValue = std::move(values[i]);
				deleteLocate(i);
				put(std::move(redoKey), std::move(redoValue));
			}
			else if (keys[i] == k) { 
				deleteLocate(i);
				moveFlag = 1;
			}
		}
		if (moveFlag == 0) throw std::out_of_range("havn't find such key to delete");
		if (N < M / 8 && M > minM) resize(M / 2);
	}
private:
	typename std::hash<Key>::result_type hash(Key k)
	{
		return std::hash<Key>()(k) % M;
	}

	void resize(size_t newM) 
	{
		auto oldM = M;
		auto oldHaveKeys = haveKeys;
		auto oldKeys = keys;
		auto oldValues = values;
		M = newM;

		keys = (Key*)std::malloc(sizeof(Key) * M);
		values = (Value*)std::malloc(sizeof(Value) * M);
		haveKeys = (bool*)std::malloc(sizeof(bool) * M);
		for (size_t i = 0; i < M; ++i) haveKeys[i] = false;
		
		for (size_t i = 0; i < oldM; ++i) {
			if (oldHaveKeys[i]) {
				auto j = hash(oldKeys[i]);
				for (j; haveKeys[j]; ++j);
				std::memcpy(keys + j, oldKeys + i, sizeof(Key));
				std::memcpy(values + j, oldValues + i, sizeof(Value));
				haveKeys[j] = true;
			}
		}
		std::free(oldHaveKeys);
		std::free(oldKeys);
		std::free(oldValues);
	}

};