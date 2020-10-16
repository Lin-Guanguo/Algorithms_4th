#pragma once
#include <string>

using std::string;

class MSD {
public:
	template<typename Iter>
	static void sort(Iter begin, Iter end)
	{
		int N = end - begin;
		aux = new string[N];
		sort(begin, 0, N, 0);
		delete[] aux;
	}
private:
	static constexpr int M = 15;
	static constexpr int R = 127;
	static string* aux;
	template<typename Iter>
	static void sort(Iter begin, int lo, int hi, int d)
	{
		if (hi <= lo + M) {
			std::sort(begin + lo, begin + hi);	//专用小数组排序算法，待完成
			return;
		}
		int count[R + 2] = { 0 };

		for (int i = lo; i < hi; ++i)
			count[charAt(begin[i], d) + 2]++;

		for (int r = 0; r < R + 1; ++r)
			count[r + 1] += count[r];

		for (int i = lo; i < hi; ++i)
			aux[count[charAt(begin[i], d) + 1]++] = std::move(begin[i]);
		//+1处理短的字符串,越界字符charAt返回-1
		for (int i = lo; i < hi; ++i)
			begin[i] = std::move(aux[i - lo]);
		//这步结束后，count[r] = count[r + 1](原来的),最后全到末尾时,
		//count[0]=0,其他都为max。再经过此轮处理，count全为max，停止递归

		for (int r = 0; r < R; ++r)
			sort(begin, lo + count[r], lo + count[r + 1], d + 1);
		//没有lo+0 ~ lo+count[0]的递归排序，是循环停止的关键
		//count[0]正好是记录字符串越界的，在排序完成后永远不需要递归再排，
		//正好承担了终止递归的任务。
	}

	static int charAt(string& s, int d)
	{
		if (d < s.length()) return s[d];
		else return -1;
	}

};
inline string* MSD::aux;