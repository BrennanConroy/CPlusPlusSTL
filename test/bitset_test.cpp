#include "test_helpers.h"
#include "bitset_test.h"
#include <bitset>

// todo
void bitset_test()
{
    auto t = STD::bitset<64>();
    t.set();
    auto b = t.to_ullong();
    auto tt = t.count();
    auto v = t[1];
    v.flip();
    bool bb = v;
    //assert_true<>();

    auto set = STD::bitset<10>();
    set.set();
    assert_true(set.count() == 10);
    set.set(1, 0);
    assert_true(set.count() == 9);
    set.set(6, 0);
    assert_true(set.count() == 8);
    set.flip();
    assert_true(set.count() == 2);
    assert_true(set.to_ulong() == 66);
}