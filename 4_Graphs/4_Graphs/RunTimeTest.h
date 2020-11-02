#pragma once
#include <functional>
#include <chrono>



auto RunTimeTest(std::function<void(void)> fun)
{
	auto tic = std::chrono::steady_clock::now();
	fun();
	auto toc = std::chrono::steady_clock::now();
	return (toc - tic).count();
}

auto multiTest(std::function<void(void)> fun, int times)
{
	long long sum = 0;
	for (int i = 0; i < times; ++i)
		sum += RunTimeTest(fun);
	return sum;
}