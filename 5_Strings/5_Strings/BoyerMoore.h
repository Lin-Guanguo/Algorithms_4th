#pragma once
#include <string>

using std::string;

class BoyerMoore
{
private:
	static constexpr int R = 128;
	int* right;
	string pat;
public:
	BoyerMoore(const string& pat)
	{
		this->pat = pat;
		int M = pat.length();
		right = new int[R];
		for (int c = 0; c < R; ++c)
			right[c] = -1;
		for (int j = 0; j < M; ++j)
			right[pat[j]] = j;	//最右一次出现位置
	}

	int search(const string& txt)
	{
		int N = txt.length();
		int M = pat.length();
		int skip;
		for (int i = 0; i < N - M + 1; i += skip) {
			skip = 0;
			for (int j = M - 1; j >= 0; --j) {
				if (pat[j] != txt[i + j]) {
					skip = j - right[txt[i + j]];
					if (skip < 1) skip = 1;
					break;
				}
			}
			if (skip == 0) return i;
		}
		return N;
	}

	~BoyerMoore()
	{
		delete[] right;
	}

};