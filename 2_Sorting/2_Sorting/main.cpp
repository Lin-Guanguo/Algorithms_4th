#include "Selection.h"
#include "Insertion.h"
#include "Shell.h"
#include "Merge.h"
#include "Quick.h"
#include "BinaryHeap.h"
#include "Test.h"
#include "SortTest.h"


#include <iostream>
#include <vector>
#include <array>
#include <random>
#include <chrono>
#include <iterator>
#include <algorithm>

using namespace std;
int main() {
	const int N = 10000;
	vector<unsigned int> v;
	v.reserve(N);
	default_random_engine e(0);
	uniform_int_distribution<> u(0, 10000);

	MaxPQ<int> pq;
	for (int i = 0; i < N; ++i) {
		v.push_back(u(e));
	}
	v[0] = 0;	//堆排序需要这句，因为堆排序不排第一个

	for (int i = 0; i < 10; ++i) {
		auto temp(v);
		SortTest(temp.begin(), temp.end(), Merge::sort);
	}
	cout << endl << endl;


	for (int i = 0; i < 10; ++i) {
		auto temp(v);
		SortTest(temp.begin(), temp.end(), Quick::sort);
	}
	
	
	return 0;
}


	/*cout << " Selection :\t";
	for (int i = 0; i < 10; i++) {
		auto temp(v);
		int time0 = clock();
		Selection(temp.begin(), temp.end());
		int time1 = clock();
		cout << time1 - time0 << "\t";
	}
	cout << endl;

	cout << " Insertion :\t";
	for (int i = 0; i < 10; i++) {
		auto temp(v);
		int time0 = clock();
		Insertion(temp.begin(), temp.end());
		int time1 = clock();
		cout <<  time1 - time0 << "\t";
	}
	cout << endl;*/