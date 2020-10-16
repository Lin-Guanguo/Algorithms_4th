#include "SequentialSearchST.h"
#include "BinarySearchST.h"
#include "BST.h"
#include "RedBlackBST.h"
#include "LinearProbingHashST.h"
#include "Test.h"
#include <string>
#include <iostream>
#include <random>
#include <map>

using namespace std;



int main() {

	vector<int> v;
	v.reserve(100);
	for (int i = 0; i < 100; ++i) {
		v.push_back(i);
	}
	random_shuffle(v.begin(), v.end());


	BST<int, std::string> ST{};
	RedBlackBST<int, std::string> ST2{};

	for (auto i : v) {
		ST.put(i, to_string(i));
		ST2.put(i, to_string(i));
	}

	ST.print(cout);
	cout << endl << endl;
	ST2.print(cout);

	//ST.deleteMax();
	//ST.deleteKey(30);
	//ST.deleteKey(40);
	//ST.deleteKey(50);
	//ST.deleteKey(36);//??????

	//ST.printTree(cout);


}