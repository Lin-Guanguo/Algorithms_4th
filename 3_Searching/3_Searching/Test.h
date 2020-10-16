#pragma once
#include <iostream>
#include <sstream>
class Test{
public:
	friend void swap(Test& one, Test& two);
	friend bool operator<(const Test& a, const Test& b);
	friend struct std::hash<Test>;

	//构造函数
	explicit Test():i(0){
		std::cout << "\t$        Test()      i = " << i << " s = " << s << " ID = " << ID << std::endl;
	}

	explicit Test(int i):i(i){
		std::cout << "\t$      Test(int i)   i = " << i << " s = " << s << " ID = " << ID << std::endl;
	}

	explicit Test(std::string _s){
		s = _s;
		std::cout << "\t$    Test(string s)  i = " << i << " s = " << s << " ID = " << ID << std::endl;
	}
	//拷贝构造
	Test(const Test& that) {
		this->i = that.i;
		std::cout << "\t$ Test(const Test& ) i = " << i << " s = " << s << " ID = " << ID << std::endl;
	}

	Test(Test&& that) noexcept {
		this->i = that.i;
		that.i = -1;
		std::cout << "\t$    Test(Test&& )   i = " << i << " s = " << s << " ID = " << ID << std::endl;
	}

	Test& operator=(Test that) {
		swap(*this, that);
		std::cout << "\t$      operator=     i = " << i << " s = " << s << " ID = " << ID << std::endl;
		return *this;
	}
	//析构
	~Test() {
		s = "deleted";
		std::cout << "\t$       ~Test()      i = " << i << " s = " << s << " ID = " << ID << std::endl;
	}
	//打印
	void print() {
		std::cout << "print()  i = " << i << " s = " << s <<" ID = " << ID << std::endl;
	}

	//private:
	int i;
	std::string s;
	static int ID_count;
	const int ID = ID_count++;
};

inline void swap(Test& one, Test& two)
{
	int temp = one.i;
	one.i = two.i;
	two.i = temp;
	std::cout << "\t$swap(Test&, Test&) ID = " << one.ID << " ID = " << two.ID << std::endl;
}

inline bool operator<(const Test& a, const Test& b) {
	std::cout << "\t$        less  <    ID = " << a.ID << " ID = " << b.ID << std::endl;
	return a.i < b.i;
}

namespace std {
	template<>
	struct hash<Test>{
		/*typedef size_t result_type;
		typedef Test argument_type;*/
		using result_type = size_t;
		using argument_type = Test;
		size_t operator()(const Test& t) {
			return std::hash<int>()(t.i) ^
				std::hash<std::string>()(t.s) ^
				std::hash<int>()(t.ID);
		}
	};
}

