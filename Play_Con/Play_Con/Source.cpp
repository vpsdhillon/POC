#include <iostream>
#include <vector>
#include <Windows.h>
#include <string>
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>

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
	test_sh->i = 30;
	for (const auto& obj : vec_sh)
	{
		std::cout << obj->i << "\n";
	}

	boost::shared_ptr<Test> boost_Test_shared = boost::make_shared<Test>();
	boost_Test_shared->i = 50;
}

int main()
{
	Print("This is a GIT controlled repo ");
	PRINT("This is a output pane");
	Fun();
	std::getchar();
}