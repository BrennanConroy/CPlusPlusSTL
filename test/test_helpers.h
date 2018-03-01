#pragma once

#ifndef _TEST_HELPERS_H_
#define _TEST_HELPERS_H_

#ifdef MySTL
#define STD STL
#else
#define STD std
#endif

template <bool condition>
void assert()
{
    static_assert(condition, "assert failed");
}

template <bool condition>
void assert_true()
{
    static_assert(condition, "assert_true failed");
}

template <>
void assert_true<true>();

template <bool condition>
void assert_false()
{
    static_assert(!condition, "assert_false failed");
}

template <>
void assert_false<false>();

void assert_false(bool condition);
void assert_true(bool condition);

#endif