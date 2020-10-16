#pragma once
#include <string>
using std::string;

class Quick3String {
public:
	template<typename Iter>
	static void sort(Iter begin, Iter end)
	{
		sort(begin, 0, end - begin, 0);
	}
private:
	template<typename Iter>
	static void sort(Iter begin, int lo, int hi, int d)
	{
		if (hi <= lo + 1) return;
		int lt = lo, gt = hi;
		int v = charAt(begin[lo], d);
		int i = lo + 1;
		while (i < gt) {
			int t = charAt(begin[i], d);
			if (t < v) swap(begin, lt++, i++);
			else if (t > v) swap(begin, i, --gt);	//gt指向尾后，先--
			else ++i;
		}
		sort(begin, lo, lt, d);
		if (v >= 0)									//防止相同字符串无限递归
			sort(begin, lt, gt, d + 1);
		sort(begin, gt, hi, d);
	}

	template<typename Iter>
	static void swap(Iter begin, int first, int second)
	{
		using std::swap;
		swap(*(begin + first), *(begin + second));
	}

	static int charAt(string& s, int d)
	{
		if (d < s.length()) return s[d];
		else return -1;
	}
};