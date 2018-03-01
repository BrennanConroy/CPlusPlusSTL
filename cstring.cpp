// todo: Figure this mem* stuff out
#include "cstring"

namespace STL
{
	size_t memcmp(const void *ptr1, const void *ptr2, size_t size)
	{
        for (size_t i = 0; i < size; ++i)
        {
            auto left = ((unsigned char *)ptr1)[i];
            auto right = ((unsigned char *)ptr2)[i];
            if (left == right)
            {
                continue;
            }
            if (left > right)
            {
                return 1;
            }
            if (left < right)
            {
                return -1;
            }
        }

        return 0;
	}

	void *memcpy(void *destination, const void *source, size_t size)
	{
        // todo: obviously not optimized
        static_assert(sizeof(char) == 1, "should never happen");
        for (size_t i = 0; i < size; ++i)
        {
            ((char *)destination)[i] = ((char *)source)[i];
        }

        return destination;
	}

	void memset(void *ptr, size_t val, size_t size)
	{
        unsigned char *buffer = (unsigned char *)ptr;
        for (size_t i = 0; i < size; ++i)
        {
            buffer[i] = val;
        }
	}
}