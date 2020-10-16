#pragma once
#include "Selection.h"

class Merge {
public:
	template<typename Iter>
	static void sort(const Iter& begin, const Iter& end) {
		int N = end - begin;
		aux = new int[N];
		sort(begin, 0, N);
		delete[] aux;
	}
private:
	template<typename Iter>
	static void sort(const Iter& begin, int lo, int hi) {
		if (hi <= lo + 1) { //�����ϵĲ�һ����hi==lo+1 ʱ��ֻ��һ��Ԫ�أ������� hi <= lo ʱ
			return; 
		}
		int mid = lo + (hi - lo) / 2;
		sort(begin, lo, mid);
		sort(begin, mid, hi);
		merge(begin, lo, mid, hi);
	}
	template<typename Iter>
	static void merge(const Iter& begin, int lo, int mid, int hi) {
		Iter k = begin + lo;
		for (int i = lo; i != hi; ++i) {
			aux[i] = *k; ++k;
		}
		int i = lo;
		int j = mid;
		for (k = begin + lo; k != begin + hi; ++k) {
			if (i == mid) { *k = aux[j]; ++j; }
			else if (j == hi) { *k = aux[i]; ++i; }
			else if (aux[j] < aux[i]) { *k = aux[j]; ++j; }
			else { *k = aux[i]; ++i; }
		}
	}
	static int* aux;
};
int* Merge::aux = nullptr;




class MergePlus {	//�Ż�����С����ʹ�� ѡ������
public:
	template<typename Iter>
	static void sort(const Iter& begin, const Iter& end) {
		int N = end - begin;
		aux = new int[N];
		sort(begin, 0, N);
		delete[] aux;
	}
private:
	template<typename Iter>
	static void sort(const Iter& begin, int lo, int hi) {
		if (hi - lo <= 10) {	//�Ż���
			Selection::sort(begin + lo, begin + hi);
			return;
		}
		int mid = lo + (hi - lo) / 2;
		sort(begin, lo, mid);
		sort(begin, mid, hi);
		merge(begin, lo, mid, hi);
	}
	template<typename Iter>
	static void merge(const Iter& begin, int lo, int mid, int hi) {
		Iter k = begin + lo;
		for (int i = lo; i != hi; ++i) {
			aux[i] = *k; ++k;
		}
		int i = lo;
		int j = mid;
		for (k = begin + lo; k != begin + hi; ++k) {
			if (i == mid) { *k = aux[j]; ++j; }
			else if (j == hi) { *k = aux[i]; ++i; }
			else if (aux[j] < aux[i]) { *k = aux[j]; ++j; }
			else { *k = aux[i]; ++i; }
		}
	}
	static int* aux;
};
int* MergePlus::aux = nullptr;




class MergeBU {	//�Ե�����
public:
	template<typename Iter>
	static void sort(const Iter& begin, const Iter& end) {
		int N = end - begin;
		aux = new int[N];

		for (int size = 1; size < N; size *= 2) {	//�ɽ��С����ѡ������ ���Ż�
			for (int lo = 0; lo < N - size; lo += 2 * size) {
				merge(begin, lo, lo + size, (lo + 2 * size < N) ? lo + 2 * size : N);
			}
		}

		delete[] aux;
	}
private:
	template<typename Iter>
	static void merge(const Iter& begin, int lo, int mid, int hi) {
		Iter k = begin + lo;
		for (int i = lo; i != hi; ++i) {
			aux[i] = *k; ++k;
		}
		int i = lo;
		int j = mid;
		for (k = begin + lo; k != begin + hi; ++k) {
			if (i == mid) { *k = aux[j]; ++j; }
			else if (j == hi) { *k = aux[i]; ++i; }
			else if (aux[j] < aux[i]) { *k = aux[j]; ++j; }
			else { *k = aux[i]; ++i; }
		}
	}
	static int* aux;
};
int* MergeBU::aux = nullptr;