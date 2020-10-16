#pragma once
#include <string>

using std::string;

class RabinKrap
{
private:
	static constexpr unsigned long long Q = 997;	//大素数
	static constexpr unsigned R = 128;
	string pat;
	unsigned long long patHash;
	unsigned long long RM;
public:
	RabinKrap(const string& pat) 
		:pat(pat)
	{
		unsigned M = pat.length();
		RM = 1;
		for (int i = 1; i < M; ++i)
			RM = (RM * R) % Q ;
		patHash = hash(pat, M);
	}

	unsigned search(const string& txt)  
	{
		auto N = txt.length();
		auto M = pat.length();
		auto txtHash = hash(txt, M);
		if (patHash == txtHash && check(txt, 0)) return 0;
		for (int i = M; i < N; ++i) {
			txtHash = (txtHash + Q - RM * txt[i - M] % Q) % Q;	//神奇的数学操作，至今没看懂
			txtHash = (txtHash * R + txt[i]) % Q;
			if (patHash == txtHash && check(txt, i - M + 1))
				return i - M + 1;
		}
		return N;
	}

private:
	unsigned long long hash(const string& txt, unsigned M) 
	{
		unsigned long long h = 0;
		for (int i = 0; i < M; ++i)
			h = (R * h + txt[i]) % Q;
		return h;
	}

	bool check(const string& txt, unsigned i) {
		return true;
	}
};