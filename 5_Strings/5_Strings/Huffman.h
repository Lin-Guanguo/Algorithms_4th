#pragma once
#include "BinaryIO.h"
#include <string>
#include <queue>
#include <vector>



class Huffman_forASCII
{
private:
	static constexpr unsigned int R = 128;

	class Node
	{
	public:
		char ch;
		unsigned freq;
		Node* left, * right;
		Node(char c, unsigned freq, Node* left, Node* right)
			:ch(c), freq(freq), left(left), right(right){}
		bool isLeaf() const { return !(left || right); }
		bool operator < (const Node& that) const { return this->freq < that.freq;}
	};

	class Trie 
	{
	public:
		Node* root = nullptr;
		string* st = nullptr;
		Trie(unsigned* freq)
		{
			buildTrie(freq);
			st = new string[R];
			buildCode(root, "");
		}

		Trie(BinaryIO::BinaryInput& in)
		{
			root = readBinary(in);
		}

		void toBinary(BinaryIO::BinaryOutput& out)
		{
			toBinary(root, out);
		}

		~Trie()
		{
			if (st) delete[] st;
			destory(root);
		}

		const string& code(char c) const
		{
			return st[c];
		}

	private:
		void buildTrie(unsigned* freq)
		{
			auto compre = [](const Node* a, const Node* b) {return *b < *a; };
			std::priority_queue<Node*, std::vector<Node*>, decltype(compre)>
				pq(compre);

			for (char c = 0; c < R; ++c)
				if (freq[c] > 0)
					pq.push(new Node{ c, freq[c], nullptr, nullptr });

			while (pq.size() > 1) {
				Node* x = pq.top(); pq.pop();
				Node* y = pq.top(); pq.pop();
				Node* parent = new Node('\0', x->freq + y->freq, x, y);
				pq.push(parent);
			}
			root = pq.top();
		}

		void buildCode(Node* x, string s)
		{
			if (x->isLeaf()) {
				st[x->ch] = s; return;
			}
			buildCode(x->left, s + '0');
			buildCode(x->right, s + '1');
		}

		void destory(Node* x)
		{
			if (x == nullptr) return;
			destory(x->left); destory(x->right);
			delete x;
		}

		void toBinary(Node* x, BinaryIO::BinaryOutput& out)
		{
			if (x->isLeaf()) {
				out.writeBit(true);
				out.writeChar(x->ch);
				return;
			}
			out.writeBit(false);
			toBinary(x->left, out);
			toBinary(x->right, out);
		}

		Node* readBinary(BinaryIO::BinaryInput& in)
		{
			if (in.readBit())
				return new Node{ in.readChar(), 0, nullptr, nullptr };
			return new Node{ '\0', 0, readBinary(in), readBinary(in) };

		}

	//调试用
	public:
		void print()
		{
			std::cerr << "\n###TriePrint####\n";
			print(root);
			std::cerr << std::endl;
			if(st!= nullptr)
				for (char i = 0; i < R; ++i) 
					if (!st[i].empty())
						std::cerr << i << st[i] << "\n";
			std::cerr << "\n###TriePrint####\n";
		}

		void print(Node* x)
		{
			if (x == nullptr) return;
			std::cerr << x->ch << "|";
			print(x->left);
			print(x->right);
		}
	};
public:
	static void compress(std::string inputFile, std::string compressFile)
	{
		unsigned charCount = 0;
		unsigned freq[R] = { 0 };
		{
			BinaryIO::BinaryInput in(inputFile);		
			char c;
			while (in >> c) {
				freq[c]++;
				charCount++;
			}
		}
		Trie trie(freq);
		BinaryIO::BinaryInput in(inputFile);
		BinaryIO::BinaryOutput out(compressFile);
		trie.toBinary(out);
		out.writeUInt(charCount);

		char c;
		while (in >> c) {
			for (auto& i : trie.code(c))
				out.writeBit(i == '1');
		}
	}

	static void expand(std::string compressFile, std::string outputFile)
	{
		BinaryIO::BinaryInput in(compressFile);
		BinaryIO::BinaryOutput out(outputFile);
		Trie trie{ in };
		auto N = in.readUInt();

		for(int i = 0; i < N; ++i) {
			auto x = trie.root;
			while (!x->isLeaf()) { 
				if (in.readBit())
					x = x->right;
				else 
					x = x->left;
			}
			out.writeByte(x->ch);
		}
	}

};

class Huffman_forALL
{
private:
	static constexpr unsigned int R = 256;

	class Node
	{
	public:
		unsigned char ch;
		unsigned freq;
		Node* left, * right;
		Node(unsigned char c, unsigned freq, Node* left, Node* right)
			:ch(c), freq(freq), left(left), right(right) {}
		bool isLeaf() const { return !(left || right); }
		bool operator < (const Node& that) const { return this->freq < that.freq; }
	};

	class Trie
	{
	public:
		Node* root = nullptr;
		string* st = nullptr;
		Trie(unsigned* freq)
		{
			buildTrie(freq);
			st = new string[R];
			buildCode(root, "");
		}

		Trie(BinaryIO::BinaryInput& in)
		{
			root = readBinary(in);
		}

		void toBinary(BinaryIO::BinaryOutput& out)
		{
			toBinary(root, out);
		}

		~Trie()
		{
			if (st) delete[] st;
			destory(root);
		}

		const string& code(unsigned char c) const
		{
			return st[c];
		}

	private:
		void buildTrie(unsigned* freq)
		{
			auto compre = [](const Node* a, const Node* b) {return *b < *a; };
			std::priority_queue<Node*, std::vector<Node*>, decltype(compre)>
				pq(compre);

			for (int c = 0; c < R; ++c)
				if (freq[c] > 0)
					pq.push(new Node{ (unsigned char)c, freq[c], nullptr, nullptr });

			while (pq.size() > 1) {
				Node* x = pq.top(); pq.pop();
				Node* y = pq.top(); pq.pop();
				Node* parent = new Node('\0', x->freq + y->freq, x, y);
				pq.push(parent);
			}
			root = pq.top();
		}

		void buildCode(Node* x, string s)
		{
			if (x->isLeaf()) {
				st[x->ch] = s; return;
			}
			buildCode(x->left, s + '0');
			buildCode(x->right, s + '1');
		}

		void destory(Node* x)
		{
			if (x == nullptr) return;
			destory(x->left); destory(x->right);
			delete x;
		}

		void toBinary(Node* x, BinaryIO::BinaryOutput& out)
		{
			if (x->isLeaf()) {
				out.writeBit(true);
				out.writeUChar(x->ch);
				return;
			}
			out.writeBit(false);
			toBinary(x->left, out);
			toBinary(x->right, out);
		}

		Node* readBinary(BinaryIO::BinaryInput& in)
		{
			if (in.readBit())
				return new Node{ in.readUChar(), 0, nullptr, nullptr };
			return new Node{ '\0', 0, readBinary(in), readBinary(in) };

		}

		//调试用
	public:
		void print()
		{
			std::cerr << "\n###TriePrint####\n";
			print(root);
			std::cerr << std::endl;
			if (st != nullptr)
				for (int i = 0; i < R; ++i)
					if (!st[i].empty())
						std::cerr << i << st[i] << "\n";
			std::cerr << "\n###TriePrint####\n";
		}

		void print(Node* x)
		{
			if (x == nullptr) return;
			std::cerr << x->ch << "|";
			print(x->left);
			print(x->right);
		}
	};
public:
	static void compress(std::string inputFile, std::string compressFile)
	{
		unsigned charCount = 0;
		unsigned freq[R] = { 0 };
		{
			BinaryIO::BinaryInput in(inputFile);
			char c;
			while (in >> c) {
				freq[(unsigned char)c]++;
				charCount++;
			}
		}
		Trie trie(freq);
		BinaryIO::BinaryInput in(inputFile);
		BinaryIO::BinaryOutput out(compressFile);
		trie.toBinary(out);
		out.writeUInt(charCount);

		char c;
		while (in >> c) {
			for (auto& i : trie.code(c))
				out.writeBit(i == '1');
		}
	}

	static void expand(std::string compressFile, std::string outputFile)
	{
		BinaryIO::BinaryInput in(compressFile);
		BinaryIO::BinaryOutput out(outputFile);
		Trie trie{ in };
		auto N = in.readUInt();

		for (int i = 0; i < N; ++i) {
			auto x = trie.root;
			while (!x->isLeaf()) {
				if (in.readBit())
					x = x->right;
				else
					x = x->left;
			}
			out.writeByte(x->ch);
		}
	}
};

