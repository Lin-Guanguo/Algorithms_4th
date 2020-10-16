#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>

using namespace std;

void 键索引计数法(vector<pair<string, int>>& studentList) {
	auto comp = [](const pair<string, int>& lhs, const pair<string, int>& rhs) {
		return lhs.second < rhs.second;};
	auto maxNum = std::max_element(studentList.begin(), studentList.end(), comp)->second;
	//组别最大下标
	vector<int> count(maxNum + 2, 0);
	for (auto& i : studentList) {
		count[i.second + 1]++;
	}
	for (int i = 0; i < count.size() - 2; ++i) {	//count的最后一个没用，*count.end() == studentList.size();
		count[i + 1] += count[i];
	}
	//写入临时数组
	vector<pair<string, int>> aux(studentList.size());
	for (auto& i : studentList) {
		aux[count[i.second]++] = std::move(i);
	}
	studentList = std::move(aux);
}

void 键索引计数法_map(vector<pair<string, int>>& studentList) {
	map<int, int> count;
	for (const auto& i : studentList) {
		count[i.second + 1]++;
		count[i.second];	//很重要, 占位, 有不连续的分组编号出现时有用.
	}
	for (auto i = count.begin(); i != --(--count.end()); ) {
		auto last = i;
		(*++i).second += (*last).second;
	}
	//写入临时数组
	vector<pair<string, int>> aux(studentList.size());
	for (auto& i : studentList) {
		aux[count[i.second]++] = std::move(i);
	}
	studentList = std::move(aux);
}

void test_键索引计数法() {
	vector<pair<string, int>> studentList{
		{"K", 1},
		{"A", 4},
		{"B", 2},
		{"C", 1},
		{"D", 0},
		{"E", 1},
		{"F", 3},
		{"O", 3},
		{"L", 6},
	};
	键索引计数法_map(studentList);
	for (auto i : studentList) {
		cout << i.first << " " << i.second << endl;
	}
}

