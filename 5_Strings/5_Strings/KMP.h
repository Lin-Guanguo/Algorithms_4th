#pragma once
#include<iostream>

using std::string;

class KMP {
private:
	int** dfa;
	static constexpr int R = 128;
	string pat;
public:
	KMP(const string& pat) 
	{
		this->pat = pat;
		int M = pat.length();
		dfa = new int* [R];
		for (int i = 0; i < R; ++i) {
			dfa[i] = new int[M];
			for (int j = 0; j < M; ++j) dfa[i][j] = 0;
		}
		dfa[pat[0]][0] = 1;

		for (int X = 0, j = 1; j < M; ++j) {
			for (int c = 0; c < R; c++)
				dfa[c][j] = dfa[c][X];
			dfa[pat[j]][j] = j + 1;
		}
	}

	int search(const string& txt) 
	{
		int i, j;
		int N = txt.length();
		int M = pat.length();
		for (i = 0, j = 0; i < N && j < M; ++i)
			j = dfa[txt[i]][j];
		if (j == M) return i - M;
		else return N;
	}

	~KMP() 
	{
		for (int i = 0; i < R; ++i)
			delete[] dfa[i];
		delete[] dfa;
	}
};

