#ifndef _STDDEF_
#define _STDDEF_

namespace STD
{
    typedef signed ptrdiff_t;
    typedef unsigned size_t;
    typedef int max_align_t;
    //typedef unsigned wchar_t;

#define NULL 0
#define offsetof(type, member) ((unsigned)&(((type *)0)->member))
}

#endif