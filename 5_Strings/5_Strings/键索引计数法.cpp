#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>

using namespace std;

void ������������(vector<pair<string, int>>& studentList) {
	auto comp = [](const pair<string, int>& lhs, const pair<string, int>& rhs) {
		return lhs.second < rhs.second;};
	auto maxNum = std::max_element(studentList.begin(), studentList.end(), comp)->second;
	//�������±�
	vector<int> count(maxNum + 2, 0);
	for (auto& i : studentList) {
		count[i.second + 1]++;
	}
	for (int i = 0; i < count.size() - 2; ++i) {	//count�����һ��û�ã�*count.end() == studentList.size();
		count[i + 1] += count[i];
	}
	//д����ʱ����
	vector<pair<string, int>> aux(studentList.size());
	for (auto& i : studentList) {
		aux[count[i.second]++] = std::move(i);
	}
	studentList = std::move(aux);
}

void ������������_map(vector<pair<string, int>>& studentList) {
	map<int, int> count;
	for (const auto& i : studentList) {
		count[i.second + 1]++;
		count[i.second];	//����Ҫ, ռλ, �в������ķ����ų���ʱ����.
	}
	for (auto i = count.begin(); i != --(--count.end()); ) {
		auto last = i;
		(*++i).second += (*last).second;
	}
	//д����ʱ����
	vector<pair<string, int>> aux(studentList.size());
	for (auto& i : studentList) {
		aux[count[i.second]++] = std::move(i);
	}
	studentList = std::move(aux);
}

void test_������������() {
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
	������������_map(studentList);
	for (auto i : studentList) {
		cout << i.first << " " << i.second << endl;
	}
}

