#include "test_helpers.h"
#include "string_test.h"
#include <string>
#include <utility>

void constructor_tests();
void assignment_tests();

void string_test()
{
	// Note: No constexpr methods on STD::string
    //todo: testing!
	constructor_tests();
    assignment_tests();

    STD::string s;
    s.push_back('l');
    s.push_back('g');

    auto i = s.begin();
    auto ss = *i;
    ++i;
    ss = *i;
    //assert_true(ss == 'g');
}

void constructor_tests()
{
    // basic_string()
	STD::string s;
	assert_true(s.size() == 0);
	assert_true(s.capacity() > 0);

	//STD::string s2("text");

    // basic_string(const charT* s, const Allocator& a = Allocator())
    char *tmp = "text";
    STD::string s3(tmp);
    assert_true(s3.size() == 4);
    assert_true(s3.capacity() > 4);
    auto str = s3.c_str();
    assert_true(str[0] == 't' && str[1] == 'e' && str[2] == 'x' && str[3] == 't' && str[4] == 0);

    // basic_string(const basic_string& str)
    STD::string s4(s3);
    assert_true(s4.size() == s3.size());
    assert_true(s4.capacity() == s3.capacity());
    str = s4.c_str();
    assert_true(str[0] == 't' && str[1] == 'e' && str[2] == 'x' && str[3] == 't' && str[4] == 0);

    // basic_string(basic_string&& str)
    STD::string s5(STD::move(s4));
    assert_true(s5.size() == 4);
    assert_true(s5.capacity() > s5.size());
    str = s5.c_str();
    assert_true(str[0] == 't' && str[1] == 'e' && str[2] == 'x' && str[3] == 't' && str[4] == 0);

    // basic_string(size_type n, charT c, const Allocator& a = Allocator())
    STD::string s6(5, 'x');
    assert_true(s6.size() == 5);
    assert_true(s6.capacity() > s6.size());
    str = s6.c_str();
    assert_true(str[0] == 'x' && str[1] == 'x' && str[2] == 'x' && str[3] == 'x' && str[4] == 'x');

    // basic_string(const charT* s, size_type n, const Allocator& a = Allocator())
    STD::string s7("text", 3);
    assert_true(s7.size() == 3);
    assert_true(s7.capacity() > s7.size());
    str = s7.c_str();
    assert_true(str[0] == 't' && str[1] == 'e' && str[2] == 'x');

    // basic_string(const Allocator& a)
    // basic_string(const basic_string& str, size_type pos, size_type n = npos, const Allocator& a = Allocator())
    // basic_string(InputIterator begin, InputIterator end, const Allocator& a = Allocator())
    // basic_string(initializer_list<charT>, const Allocator& = Allocator())
    // basic_string(const basic_string& str, const Allocator& alloc)
    // basic_string(basic_string&& str, const Allocator& alloc)
}

void assignment_tests()
{
    // basic_string& operator=(const basic_string& str)
    STD::string s("text", 4);
    STD::string s2;
    s2 = s;
    assert_true(s2.size() == 4);
    assert_true(s2.capacity() > s2.size());
    auto str = s2.c_str();
    assert_true(str[0] == 't' && str[1] == 'e' && str[2] == 'x' && str[3] == 't');

    // basic_string& operator=(basic_string&& str) noexcept(allocator_traits<Allocator>::propagate_on_container_move_assignment::value || allocator_traits<Allocator>::is_always_equal::value)
    // basic_string& operator=(const charT* s)
    // basic_string& operator=(charT c)
    // basic_string& operator=(initializer_list<charT>)
}