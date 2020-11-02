#include "RunTimeTest.h"
#include "SqList.h"
#include "Test.h"
#include <iostream>


int Test::ID_count = 0;
using namespace std;


int main()
{
	SqList<Test> list;

	list.emplace_front(10);
}