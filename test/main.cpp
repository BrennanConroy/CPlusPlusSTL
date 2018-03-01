//#ifdef MySTL
//#define STD STL
//#else
//#define STD std
//#endif

#include <tuple>
#include <exception>
#include <string>
//#include <bitset>
#include <memory>
#include "cstddef_test.hpp"
//#include "exception_test.hpp"
#include "type_traits_test.h"
#include "tuple_test.h"
#include "bitset_test.h"
#include "string_test.h"
#include "algorithm_test.h"

struct foo{
	char a;
char b[10];
char c;
};

void isbaseof()
{
    if(!STD::is_base_of<STD::tuple<>, STD::tuple<int, float>>::value)
    {
        __debugbreak();
    }
    if (STD::is_base_of<STD::tuple<>, int>::value)
    {
        __debugbreak();
    }
}

int main(char **, int)
{
    type_traits_test();
    tuple_test();
    bitset_test();
    string_test();
    algorithm_test();

    int *i = new int;
    auto ptr = STD::unique_ptr<int>(i);
    auto ptr2 = STD::unique_ptr<int>(STD::move(ptr));
    //auto ptr3 = STD::unique_ptr<short>(STD::move(ptr2));

    STD::tuple<int, char, float> g(15, 'p', 4.f);
    g = STD::tuple<int, char, float>(5, 'f', 4.4f);
    g = STD::tuple<char, int, float>('t', 5, 3.3f);
    STD::tuple<int, int, float> gg(g);
    STD::tuple<double, float, foo> ggg(STD::tuple<double, float, foo>(3.0, 3.f, foo()));
    STD::pair<int, float> p(1, 4.5f);
    STD::tuple<int, float> pt;
    pt = STD::move(p);
    STD::tuple<int, char, float> gs(4, 'b', 1.93f);
    g.swap(gs);
    auto b = STD::get<1>(g);
    //bool k = g == gg;
    //STD::tuple<int, float> t(p);
    //isbaseof();

    //STD::string str();
    /*STD::bitset<10> bit;
    bit &= STD::bitset<10>();
    bit.set();
    bit.set(4, false);
    auto nbit = ~bit;
    bit.test(4);

    auto size = sizeof(STD::bitset<1000>);*/

	return offsetof(foo, c);
}