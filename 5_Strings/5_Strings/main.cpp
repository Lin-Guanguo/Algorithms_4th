#include <random>
#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <algorithm>

#include "MSD.h"
#include "Quick3String.h"
#include "TrieST.h"
#include "Trie3ST.h"
#include "RabinKarp.h"
#include "KMP.h"
#include "BoyerMoore.h"
#include "Huffman.h"
#include "Regex.h"


using namespace std;
using std::cout;


void test_LSD();
void test_键索引计数法();
void test_sort();
void test_TrieST(); 
void test_subString();
void test_compress();
void test_regex();

int main() {
	test_regex();

}


void test_sort() {
	default_random_engine E;
	uniform_int_distribution<int> randomChar('a', 'z');
	uniform_int_distribution<int> randomLen(1, 20);
	int max = 200;
	vector<string> vs;
	vs.reserve(max);
	for (auto i = 0; i < max; ++i) {
		string s;
		for (int j = 0; j < randomLen(E); ++j) {
			s += (char)randomChar(E);
		}
		vs.push_back(std::move(s));
	}
	Quick3String::sort(vs.begin(), vs.end());
	for (auto i : vs) { cout << i << endl; }
	cout << endl << endl;
}

void test_TrieST() {
	TrieST<int> ST{};
	vector<string> v{
		"she", "sells", "sea", "shells", "by", "the", "sea", "shore"
	};

	int i = 0;
	for (auto& s : v) {
		ST.put(s, i++);
	}

	/*for (auto& s : v) {
		cout << ST.get(s) << " ";
	}
	cout <<"size = " << ST.getSize() << endl;


	for (auto& s : v) {
		try {
			cout << ST.get(s) << " ";
		}
		catch (std::out_of_range& e) {
			cout << "delete";
		}
	}
	cout <<"size = " << ST.getSize() << endl;

	cout << endl << "##############" << endl;*/

	
	for (auto i : ST)
		cout << i << " ";


}

void test_subString() {
	default_random_engine E;
	uniform_int_distribution<int> randomChar('a', 'z');
	uniform_int_distribution<int> randomLen(1, 20);

	string txt;
	int max = 200;
	txt.reserve(max);
	for (int i = 0; i < max; ++i)
		txt += (char)randomChar(E);
	string pat = txt.substr(30, 20);
	cout << txt << endl << pat << endl << endl;;


	RabinKrap find{ pat };
	auto res = find.search(txt);

	cout << "location = " << res << endl;
	if (res != txt.length()) {
		for (int i = 0; i < txt.length(); ++i) {
			if (i == res) cout << " \" ";
			else if (i == res + pat.length()) cout << " \" ";
			cout << txt[i];
		}
	}
}

void test_regex(){
	NFA_plus  nfa("((A|B|C|D)A)");
	cout << nfa.recognizes("FOSOWFAAAAAAAAA") << endl;

}

void test_compress() 
{
	string inFile = ".\\in.docx";
	string outFile = ".\\out.docx";
	string compressFile = ".\\compress.data";

	Huffman_forALL::compress(inFile, compressFile);
	Huffman_forALL::expand(compressFile, outFile);

	auto countBit = [&](string file) {
		BinaryIO::BinaryInput in(file);
		unsigned long long size = 0;
		bool b;
		while (in >> b)
			++size;
		return size;
	};

	auto size1 = countBit(inFile);
	cout << "input size =\t" << size1 << endl;

	auto size2 = countBit(compressFile);
	cout << "compress size =\t" << size2 << endl;

	auto size3 = countBit(outFile);
	cout << "output size =\t" << size3 << endl;

	cout << "compress rate =\t" << (double)size2 / size1;
}