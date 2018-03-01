#include "test_helpers.h"
#include "type_traits_test.h"
#include <type_traits>

class TestClass
{
public:
    void Func1();
    int Func2() const;
    const int *Func3();
    const int * volatile Func4();
    const void ** Func5(...);
    volatile void *Func6() const;
    volatile int LValue() &;
    const int RValue() &&;
    void *Member1;
    const long *Member2;
    volatile STD::nullptr_t * const Member3;
};

enum A
{
    First
};

enum B : unsigned
{
};

enum class C
{
};

void type_traits_test()
{
    //is_const tests
    assert_true<STD::is_const<const volatile int>::value>(); // true
    assert_false<STD::is_const<const int*>::value>(); // false
    assert_false<STD::is_const<const int&>::value>(); // false
    assert_false<STD::is_const<int[3]>::value>(); // false
    assert_true<STD::is_const<const int[3]>::value>(); // true
    assert_true<STD::is_const<int * const>::value>();

    //is_volatile tests
    assert_true<STD::is_volatile<volatile int>::value>();
    assert_true<STD::is_volatile<const volatile int>::value>();
    assert_false<STD::is_volatile<int>::value>();
    assert_false<STD::is_volatile<volatile int *>::value>();
    assert_true<STD::is_volatile<int * volatile>::value>();
    assert_true<STD::is_volatile<volatile int[3]>::value>();

    //is_reference tests
    assert_false<STD::is_reference<int>::value>();
    assert_true<STD::is_reference<int &>::value>();
    assert_true<STD::is_reference<int &&>::value>();
    assert_true<STD::is_reference<int *&&>::value>();
    assert_true<STD::is_reference<const int *&>::value>();

    //is_void tests
    assert_false<STD::is_void<int>::value>();
    assert_true<STD::is_void<void>::value>();
    assert_true<STD::is_void<const void>::value>();
    assert_true<STD::is_void<const volatile void>::value>();
    assert_true<STD::is_void<volatile void>::value>();
    assert_false<STD::is_void<void *>::value>();

    //is_same tests
    assert_true<STD::is_same<int, int>::value>();
    assert_false<STD::is_same<int, short>::value>();
    assert_false<STD::is_same<int, int *>::value>();
    assert_true<STD::is_same<char *, char *>::value>();
    assert_true<STD::is_same<void *[3], void *[3]>::value>();
    assert_false<STD::is_same<void **, void *[3]>::value>();

    //is_null_pointer tests
    assert_true<STD::is_null_pointer<decltype(nullptr)>::value>();
    assert_false<STD::is_null_pointer<int *>::value>();
    assert_true<STD::is_null_pointer<STD::nullptr_t>::value>();
    assert_true<STD::is_null_pointer<const STD::nullptr_t>::value>();
    assert_true<STD::is_null_pointer<volatile STD::nullptr_t>::value>();
    assert_true<STD::is_null_pointer<const volatile STD::nullptr_t>::value>();

    //is_array tests
    assert_false<STD::is_array<int>::value>();
    assert_true<STD::is_array<int[]>::value>();
    assert_true<STD::is_array<const void *[]>::value>();
    assert_true<STD::is_array<volatile int[3]>::value>();
    assert_true<STD::is_array<const volatile long *[]>::value>();

    //is_lvalue_reference tests
    assert_false<STD::is_lvalue_reference<int>::value>();
    assert_true<STD::is_lvalue_reference<int &>::value>();
    assert_false<STD::is_lvalue_reference<int &&>::value>();
    assert_true<STD::is_lvalue_reference<const void *&>::value>();
    assert_true<STD::is_lvalue_reference<volatile long &>::value>();
    assert_true<STD::is_lvalue_reference<const volatile int &>::value>();
    assert_true<STD::is_lvalue_reference<int const &>::value>();

    //is_rvalue_reference tests
    assert_false<STD::is_rvalue_reference<int>::value>();
    assert_true<STD::is_rvalue_reference<int &&>::value>();
    assert_false<STD::is_rvalue_reference<int &>::value>();
    assert_true<STD::is_rvalue_reference<const void *&&>::value>();
    assert_true<STD::is_rvalue_reference<volatile long &&>::value>();
    assert_true<STD::is_rvalue_reference<const volatile int &&>::value>();
    assert_true<STD::is_rvalue_reference<int const &&>::value>();

    //is_pointer tests
    assert_false<STD::is_pointer<int>::value>();
    assert_true<STD::is_pointer<int *>::value>();
    assert_true<STD::is_pointer<int **>::value>();
    assert_false<STD::is_pointer<int *&>::value>();
    assert_true<STD::is_pointer<const int **>::value>();
    assert_true<STD::is_pointer<volatile int *>::value>();
    assert_true<STD::is_pointer<volatile int * const>::value>();
    assert_true<STD::is_pointer<volatile int * volatile const>::value>();
    assert_true<STD::is_pointer<const volatile int *>::value>();
    assert_true<STD::is_pointer<decltype(&type_traits_test)>::value>();
    assert_false<STD::is_pointer<decltype(&TestClass::Func1)>::value>();
    assert_false<STD::is_pointer<decltype(&TestClass::Member1)>::value>();

    //is_function tests
    assert_true<STD::is_function<decltype(type_traits_test)>::value>();
    assert_true<STD::is_function<int (int)>::value>();
    assert_true<STD::is_function<int(int &, int, bool)>::value>();
    assert_true<STD::is_function<int && const(int)>::value>();
    assert_true<STD::is_function<volatile int(int const)>::value>();
    assert_true<STD::is_function<void const * volatile(int volatile, int const *)>::value>();
    assert_true<STD::is_function<int (...)>::value>();
    assert_true<STD::is_function<int(...) &>::value>();
    assert_true<STD::is_function<int(bool) && noexcept>::value>();
    assert_true<STD::is_function<auto(void *) -> int>::value>();
    assert_true<STD::is_function<auto(long, short) -> const int * const>::value>();
    assert_true<STD::is_function<const void **(...)>::value>();
    assert_false<STD::is_function<const decltype(&TestClass::Func2)>::value>();

    //is_member_pointer tests
    assert_true<STD::is_member_pointer<decltype(&TestClass::Member1)>::value>();
    assert_true<STD::is_member_pointer<decltype(&TestClass::Member2)>::value>();
    assert_true<STD::is_member_pointer<const decltype(&TestClass::Member3)>::value>();
    assert_false<STD::is_member_pointer<int>::value>();
    assert_true<STD::is_member_pointer<decltype(&TestClass::Func1)>::value>();

    //is_member_object_pointer tests
    assert_true<STD::is_member_object_pointer<decltype(&TestClass::Member1)>::value>();
    assert_false<STD::is_member_object_pointer<decltype(&TestClass::Func1)>::value>();
    assert_false<STD::is_member_object_pointer<decltype(&type_traits_test)>::value>();

    //is_member_function_pointer tests
    assert_true<STD::is_member_function_pointer<decltype(&TestClass::Func1)>::value>();
    assert_false<STD::is_member_function_pointer<decltype(&type_traits_test)>::value>();
    assert_false<STD::is_member_function_pointer<int>::value>();
    assert_false<STD::is_member_function_pointer<void *>::value>();
    assert_true<STD::is_member_function_pointer<const decltype(&TestClass::Func2)>::value>();
    assert_true<STD::is_member_function_pointer<decltype(&TestClass::Func3)>::value>();
    assert_true<STD::is_member_function_pointer<decltype(&TestClass::Func4)>::value>();
    assert_true<STD::is_member_function_pointer<decltype(&TestClass::Func5)>::value>();
    assert_true<STD::is_member_function_pointer<decltype(&TestClass::Func6)>::value>();
    assert_false<STD::is_member_function_pointer<decltype(&TestClass::Member1)>::value>();

    //is_enum tests
    assert_true<STD::is_enum<A>::value>();
    assert_true<STD::is_enum<decltype(A::First)>::value>();
    assert_false<STD::is_enum<TestClass>::value>();
    assert_false<STD::is_enum<int>::value>();
    assert_false<STD::is_enum<decltype(&TestClass::Func1)>::value>();
    assert_true<STD::is_enum<B>::value>();
    assert_true<STD::is_enum<C>::value>();

    //is_floating_point tests
    assert_true<STD::is_floating_point<float>::value>();
    assert_true<STD::is_floating_point<double>::value>();
    assert_true<STD::is_floating_point<long double>::value>();
    assert_false<STD::is_floating_point<int>::value>();
    assert_true<STD::is_floating_point<const float>::value>();
    assert_true<STD::is_floating_point<volatile double>::value>();
    assert_false<STD::is_floating_point<double *>::value>();

    //is_integral tests
    assert_true<STD::is_integral<bool>::value>();
    assert_true<STD::is_integral<char>::value>();
    assert_true<STD::is_integral<signed char>::value>();
    assert_true<STD::is_integral<unsigned char>::value>();
    assert_true<STD::is_integral<short>::value>();
    assert_true<STD::is_integral<signed short>::value>();
    assert_true<STD::is_integral<unsigned short>::value>();
    assert_true<STD::is_integral<int>::value>();
    assert_true<STD::is_integral<signed int>::value>();
    assert_true<STD::is_integral<unsigned int>::value>();
    assert_true<STD::is_integral<long>::value>();
    assert_true<STD::is_integral<signed long>::value>();
    assert_true<STD::is_integral<unsigned long>::value>();
    assert_true<STD::is_integral<long long>::value>();
    assert_true<STD::is_integral<signed long long>::value>();
    assert_true<STD::is_integral<unsigned long long>::value>();
    assert_true<STD::is_integral<char16_t>::value>();
    assert_true<STD::is_integral<char32_t>::value>();
    assert_true<STD::is_integral<wchar_t>::value>();
    assert_true<STD::is_integral<const long>::value>();
    assert_true<STD::is_integral<volatile char>::value>();
    assert_false<STD::is_integral<double>::value>();
    assert_false<STD::is_integral<int *>::value>();
    assert_false<STD::is_integral<void>::value>();

    //is_arithmetic tests
    assert_true<STD::is_arithmetic<bool>::value>();
    assert_true<STD::is_arithmetic<char>::value>();
    assert_true<STD::is_arithmetic<signed char>::value>();
    assert_true<STD::is_arithmetic<unsigned char>::value>();
    assert_true<STD::is_arithmetic<short>::value>();
    assert_true<STD::is_arithmetic<signed short>::value>();
    assert_true<STD::is_arithmetic<unsigned short>::value>();
    assert_true<STD::is_arithmetic<int>::value>();
    assert_true<STD::is_arithmetic<signed int>::value>();
    assert_true<STD::is_arithmetic<unsigned int>::value>();
    assert_true<STD::is_arithmetic<long>::value>();
    assert_true<STD::is_arithmetic<signed long>::value>();
    assert_true<STD::is_arithmetic<unsigned long>::value>();
    assert_true<STD::is_arithmetic<long long>::value>();
    assert_true<STD::is_arithmetic<signed long long>::value>();
    assert_true<STD::is_arithmetic<unsigned long long>::value>();
    assert_true<STD::is_arithmetic<char16_t>::value>();
    assert_true<STD::is_arithmetic<char32_t>::value>();
    assert_true<STD::is_arithmetic<wchar_t>::value>();
    assert_true<STD::is_arithmetic<const long>::value>();
    assert_true<STD::is_arithmetic<volatile char>::value>();
    assert_true<STD::is_arithmetic<float>::value>();
    assert_true<STD::is_arithmetic<double>::value>();
    assert_true<STD::is_arithmetic<long double>::value>();
    assert_true<STD::is_arithmetic<const float>::value>();
    assert_true<STD::is_arithmetic<volatile double>::value>();
    assert_false<STD::is_arithmetic<int *>::value>();
    assert_false<STD::is_arithmetic<void>::value>();

    //is_signed tests
    assert_true<STD::is_signed<int>::value>();
    assert_true<STD::is_signed<signed int>::value>();
    assert_true<STD::is_signed<signed char>::value>();
    assert_true<STD::is_signed<signed long>::value>();
    assert_true<STD::is_signed<signed long long>::value>();
    assert_true<STD::is_signed<signed short>::value>();
    assert_true<STD::is_signed<float>::value>();
    assert_true<STD::is_signed<double>::value>();
    assert_true<STD::is_signed<long double>::value>();
    assert_false<STD::is_signed<char16_t>::value>();
    assert_false<STD::is_signed<char32_t>::value>();
    assert_false<STD::is_signed<wchar_t>::value>();
    assert_false<STD::is_signed<unsigned char>::value>();
    assert_false<STD::is_signed<signed int *>::value>();
    assert_false<STD::is_signed<void>::value>();

    //is_unsigned tests
    assert_true<STD::is_unsigned<unsigned int>::value>();
    assert_true<STD::is_unsigned<unsigned char>::value>();
    assert_true<STD::is_unsigned<unsigned long>::value>();
    assert_true<STD::is_unsigned<unsigned long long>::value>();
    assert_true<STD::is_unsigned<unsigned short>::value>();
    assert_true<STD::is_unsigned<char16_t>::value>();
    assert_true<STD::is_unsigned<char32_t>::value>();
    assert_true<STD::is_unsigned<wchar_t>::value>();
    assert_false<STD::is_unsigned<signed char>::value>();
    assert_false<STD::is_unsigned<unsigned int *>::value>();
    assert_false<STD::is_unsigned<void>::value>();

    //is_fundamental tests
    assert_true<STD::is_fundamental<int>::value>();
    assert_true<STD::is_fundamental<bool>::value>();
    assert_true<STD::is_fundamental<char16_t>::value>();
    assert_true<STD::is_fundamental<char32_t>::value>();
    assert_true<STD::is_fundamental<wchar_t>::value>();
    assert_true<STD::is_fundamental<char>::value>();
    assert_true<STD::is_fundamental<long>::value>();
    assert_true<STD::is_fundamental<long long>::value>();
    assert_true<STD::is_fundamental<float>::value>();
    assert_true<STD::is_fundamental<double>::value>();
    assert_true<STD::is_fundamental<long double>::value>();
    assert_true<STD::is_fundamental<void>::value>();
    assert_true<STD::is_fundamental<decltype(nullptr)>::value>();
    assert_true<STD::is_fundamental<STD::nullptr_t>::value>();
    assert_false<STD::is_fundamental<TestClass>::value>();
    assert_false<STD::is_fundamental<void *>::value>();
    assert_false<STD::is_fundamental<const int &>::value>();

    //add_const tests
    assert_true<STD::is_const<STD::add_const_t<int>>::value>();
    assert_true<STD::is_const<STD::add_const_t<const int>>::value>();
    assert_true<STD::is_const<STD::add_const_t<void *>>::value>();
    assert_true<STD::is_const<STD::add_const_t<int *const>>::value>();
    assert_false<STD::is_const<STD::add_const_t<int &>>::value>(); //reference types don't add const
    assert_true<STD::is_const<STD::add_const_t<TestClass>>::value>();

    //add_volatile tests
    assert_true<STD::is_volatile<STD::add_volatile_t<int>>::value>();
    assert_true<STD::is_volatile<STD::add_volatile_t<volatile int>>::value>();
    assert_true<STD::is_volatile<STD::add_volatile_t<char *>>::value>();
    assert_true<STD::is_volatile<STD::add_volatile_t<float * volatile>>::value>();
    assert_false<STD::is_volatile<STD::add_volatile_t<int &>>::value>();
    assert_true<STD::is_volatile<STD::add_volatile_t<TestClass>>::value>();

    //add_cv tests
    assert_true<STD::is_const<STD::add_cv_t<int>>::value && STD::is_volatile<STD::add_cv_t<int>>::value>();
    assert_true<STD::is_const<STD::add_cv_t<volatile const int>>::value && STD::is_volatile<STD::add_cv_t<volatile const int>>::value>();
    assert_true<STD::is_const<STD::add_cv_t<void *>>::value && STD::is_volatile<STD::add_cv_t<void *>>::value>();
    assert_true<STD::is_const<STD::add_cv_t<TestClass>>::value && STD::is_volatile<STD::add_cv_t<TestClass>>::value>();
    assert_false<STD::is_const<STD::add_cv_t<int &>>::value || STD::is_volatile<STD::add_cv_t<int &>>::value>();

    //add_lvalue_reference tests
    //add_rvalue_reference tests
    //remove_extent tests
    //remove_all_extents tests
    //enable_if tests
    //conditional tests
    //remove_pointer tests
    //add_pointer tests
}