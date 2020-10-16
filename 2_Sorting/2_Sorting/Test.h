#pragma once
#include <iostream>
#include <sstream>
class Test{
public:
	friend void swap(Test& one, Test& two);
	Test():i(0){
		std::cout << "\t$        Test()      i = " << i << " ID = " << ID << std::endl;
	}
	Test(int i):i(i){
		std::cout << "\t$      Test(int i)   i = " << i << " ID = " << ID << std::endl;
	}
	Test(std::string s){
		std::istringstream in(s);
		in >> i;
		std::cout << "\t$    Test(string s)  i = " << i << " ID = " << ID << std::endl;
	}
	Test(const Test& that) {
		this->i = that.i;
		std::cout << "\t$ Test(const Test& ) i = " << i << " ID = " << ID << std::endl;
	}
	Test(Test&& that) noexcept {
		this->i = that.i;
		that.i = -1;
		std::cout << "\t$    Test(Test&& )   i = " << i << " ID = " << ID << std::endl;
	}
	Test& operator=(Test that) {
		swap(*this, that);
		std::cout << "\t$      operator=     i = " << i << " ID = " << ID << std::endl;
		return *this;
	}
	bool operator<(const Test& that) {
		std::cout << "\t$        less  <    ID = " << ID << " ID = " << that.ID << std::endl;
		return this->i < that.i;
	}
	~Test() {
		std::cout << "\t$       ~Test()      i = " << i << " ID = " << ID << std::endl;
	}
	int i;
	static int ID_count;
	const int ID = ID_count++;
};

int Test::ID_count = 0;

inline void swap(Test& one, Test& two)
{
	int temp = one.i;
	one.i = two.i;
	two.i = temp;
	std::cout << "\t$swap(Test&, Test&) ID = " << one.ID << " ID = " << two.ID << std::endl;
}