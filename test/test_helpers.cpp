#include "test_helpers.h"

template <>
void assert_true<true>()
{
}

template <>
void assert_false<false>()
{
}

void assert_true(bool condition)
{
	if (!condition)
	{
		__debugbreak();
	}
}

void assert_false(bool condition)
{
	if (condition)
	{
		__debugbreak();
	}
}