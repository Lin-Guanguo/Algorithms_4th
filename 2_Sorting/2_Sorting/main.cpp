#include "Selection.h"
#include "Insertion.h"
#include "Shell.h"
#include "Merge.h"
#include "Quick.h"
#include "BinaryHeap.h"
#include "Test.h"
#include "SortTest.h"
#include "IndexMinPQ.h"


#include <iostream>
#include <vector>
#include <array>
#include <random>
#include <chrono>
#include <iterator>
#include <algorithm>
#include <queue>
#include <list>

void pq_test();

using namespace std;
int main() {
	pq_test();
	priority_queue<int> pq;
	unordered_map<int, int> m;

}

void pq_test() {
	default_random_engine E;
	uniform_int_distribution<int> U(1,1000);

	IndexMinPQ<int, int> ipq;
	for (int i = 0; i < 100; ++i) {
		ipq.insert(i, 100 - i);
	}

	while (!ipq.empty()) {
		cout << ipq.top().key << " | " << ipq.top().value << "\n";
		ipq.pop();
	}

	for (int i = 0; i < 100; ++i) {
		ipq.insert(i, 100 - i);
	}

	cout << "\n\n\n";

	for (int i = 0; i < 100; ++i) {
		ipq.change(i, i);
	}

	while (!ipq.empty()) {
		cout << ipq.top().key << " | " << ipq.top().value << "\n";
		ipq.pop();
	}
}