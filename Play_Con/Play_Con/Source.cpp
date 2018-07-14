#include <iostream>
#include <vector>
#include <Windows.h>
#include <string>
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#include <functional>
#include <map>
#include <list>

using namespace std;

#define PRINT(X) \
	( \
		cout << __FILE__ << " (" << __LINE__ << ") " << __func__ << " @ " \
		<< __DATE__ << " " << __TIME__ << " - " << X << endl \
	)

void Print(std::string str)
{
	str = str + "\n";
	::OutputDebugString(str.c_str());
	std::cout << str;
}

class Test
{
public:
	int i = 10;

	Test()
	{
		Print("Test Constructor");
	}

	Test(const Test& t)
	{
		i = t.i;
		Print("Copy Constructor");
	}

	~Test()
	{
		Print("~Test Destructor");
	}
};

typedef std::vector<shared_ptr<Test> > vec_shared;

void Fun()
{
	Test t;
	std::vector<Test> vec;
	t.i = 20;
	vec.push_back(t);
	t.i = 30;

	using Iter = std::vector<Test>::const_iterator;
	for (Iter it = vec.begin(); it != vec.end(); ++it)
	{
		std::cout << (*it).i << "\n";
	}

	vec_shared vec_sh;
	shared_ptr<Test> test_sh = make_shared<Test>();
	test_sh->i = 20;
	vec_sh.push_back(test_sh);

	for (const auto& obj : vec_sh)
	{
		std::cout << obj->i << "\n";
	}

	boost::shared_ptr<Test> boost_Test_shared = boost::make_shared<Test>();
	boost_Test_shared->i = 50;
};

std::function<int(int)> Fibonacci = [](int number) -> int 
{
	if (number < 1)
	{
		return 0;
	}
	else if (number == 1)
	{
		return 1;
	}
	return (Fibonacci(number - 1) + Fibonacci(number - 2));
};

typedef std::map<int, int> customMap;


class ListTest
{
public:
	string str;
	ListTest() : str("Test")
	{}
};

typedef std::shared_ptr<ListTest> ListTestShared;
typedef std::list<ListTestShared> ListTestList;


auto main() -> int
{
	ListTestList testList;

	for (int i = 0; i < 5; i++)
	{
		testList.push_back(std::make_shared<ListTest>());
	}

	ListTestList::iterator it = testList.begin(), ti = testList.end();

	while (it != ti)
	{
		ListTestShared &test = *it;
		it++;
	}

	ListTestList::iterator it1 = testList.begin(), ti1 = testList.end();

	while (it1 != ti1)
	{
		std::cout << (*it1)->str << "\n";
		it1++;
	}

	getchar();
	return 0;

	Print("This is a GIT controlled repo");
	PRINT("This is a output pane");
	//Fun();

	customMap custom;
	custom[1] = 10;
	custom[1] = 20;
	custom.insert(std::pair<int, int>(1, 30));
	custom.emplace(std::pair<int, int>(1, 30));
	std::cout << custom[1];

	//Fun();
	std::getchar();
}