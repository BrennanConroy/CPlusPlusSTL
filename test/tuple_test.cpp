#include "test_helpers.h"
#include "tuple_test.h"
#include <tuple>

void tuple_test()
{
    //parameterless constructor
    assert_true<STD::is_same<STD::tuple<int>, decltype(STD::tuple<int>())>::value>();
    assert_true<STD::is_same<STD::tuple<float, float, int *>, decltype(STD::tuple<float, float, int *>())>::value>();

    //explicit parameter constructor
    assert_true<STD::is_same<STD::tuple<int, float>, decltype(STD::tuple<int, float>(10, 4.f))>::value>();
    //assert_true<STD::is_same<STD::tuple<int, float>, decltype(STD::tuple<int, float>(10))>::value>(); shouldn't compile?

    //explicit parameter constructor with not same type params
    assert_true<STD::is_same<STD::tuple<int, int>, decltype(STD::tuple<int, int>(10.f, 4.f))>::value>();

    assert_true<STD::is_same<STD::tuple<int, float>, decltype(STD::tuple<int, float>(STD::tuple<int, float>(10, 3.f)))>::value>();
}