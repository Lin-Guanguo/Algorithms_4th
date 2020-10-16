#include <string>
#include <map>
#include <vector>
#include <chrono>
#include <memory>
#include <array>
using namespace std;

void LSD_byMap(vector<string>& List) 
{
	for (int w = List[0].size() - 1; w >= 0; --w) {
		map<char, int> count;
		for (const auto& s : List) {
			count[s[w] + 1]++;
			count[s[w]];//很重要, 必须要, 初始化为0占位, 下一步填充 
		}
		for (auto i = count.begin(); i != --(--count.end()); ) {
			auto last = i;
			(*++i).second += (*last).second;
		}

		vector<string> aux(List.size());
		for (auto& s : List) {
			aux[count[s[w]]++] = std::move(s);
		}
		List = std::move(aux);
	}
}

void LSD(vector<string>& a) 
{
	int w = a[0].length();
	int R = 128;
	int N = a.size();
	vector<string> aux(N);	//在外面建，循环内新建数组开销较大
	for (int d = w - 1; d >= 0; --d) {
		vector<int> count(R+1, 0);
		for (int i = 0; i < N; ++i) 
			count[a[i][d] + 1]++;
		
		for (int r = 0; r < R; r++) 
			count[r + 1] += count[r];
		
		for (int i = 0; i < N; ++i) 
			aux[ count[ a[i][d] ]++ ] = std::move(a[i]);

		for (int i = 0; i < N; ++i)
			a[i] = std::move(aux[i]);	//不能整个移动vector，移动后的vector无法再使用
	}
}

#include <random>
#include <iostream>
void test_LSD() {
	default_random_engine E;
	uniform_int_distribution<int> UID(10000, 99999);

	bool succeed_flag = true;
	auto tic = chrono::steady_clock::now();
	for (int n = 0; n < 1000; ++n) {
		int max = 20;
		vector<string> vs; 
		vs.reserve(max);
		for (auto i = 0; i < max; ++i) {
			vs.push_back(to_string(UID(E)));
		}
		LSD(vs);
		if (!is_sorted(vs.begin(), vs.end())) succeed_flag = false;
	}
	auto toc = chrono::steady_clock::now();
	auto time = (toc - tic).count();

	cout << (succeed_flag ? "succeed " : "falied ");
	cout <<"spend time " << time << endl;
}