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
			std::sort(begin + lo, begin + hi);	//ר��С���������㷨�������
			return;
		}
		int count[R + 2] = { 0 };

		for (int i = lo; i < hi; ++i)
			count[charAt(begin[i], d) + 2]++;

		for (int r = 0; r < R + 1; ++r)
			count[r + 1] += count[r];

		for (int i = lo; i < hi; ++i)
			aux[count[charAt(begin[i], d) + 1]++] = std::move(begin[i]);
		//+1����̵��ַ���,Խ���ַ�charAt����-1
		for (int i = lo; i < hi; ++i)
			begin[i] = std::move(aux[i - lo]);
		//�ⲽ������count[r] = count[r + 1](ԭ����),���ȫ��ĩβʱ,
		//count[0]=0,������Ϊmax���پ������ִ���countȫΪmax��ֹͣ�ݹ�

		for (int r = 0; r < R; ++r)
			sort(begin, lo + count[r], lo + count[r + 1], d + 1);
		//û��lo+0 ~ lo+count[0]�ĵݹ�������ѭ��ֹͣ�Ĺؼ�
		//count[0]�����Ǽ�¼�ַ���Խ��ģ���������ɺ���Զ����Ҫ�ݹ����ţ�
		//���óе�����ֹ�ݹ������
	}

	static int charAt(string& s, int d)
	{
		if (d < s.length()) return s[d];
		else return -1;
	}

};
inline string* MSD::aux;