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

void pq_test();

using namespace std;
int main() {
	pq_test();
}




void pq_test() {
	/*MinPQ<int> pq{ std::greater<int>() };
	pq.insert(5);
	pq.insert(2);
	pq.insert(6);
	pq.insert(7);
	pq.insert(9);

	while (!pq.empty()) {
		cout << pq.top() << " | ";
		pq.pop();
	}*/

	IndexMinPQ<int, int> ipq;
	ipq.insert(1, 2);
	ipq.insert(2, 7);
	ipq.insert(6, 5);
	ipq.insert(4, 66);
	ipq.insert(4, 6);
	ipq.insert(6, 88);

	while (!ipq.empty()) {
		cout << ipq.top().key << " | " << ipq.top().value << "\n";
		ipq.pop();
	}
}