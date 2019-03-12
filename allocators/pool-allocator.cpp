#include <utility>
#include <iostream>

using uint = unsigned;

constexpr unsigned PAGE_SIZE = 4096;  // 4096 = 64 * 64 = 8 * 8 * 8 * 8 = 2^12


template <typename Type, uint n = PAGE_SIZE>
struct PoolAllocator
{
    constexpr static uint capacity_in_bytes = n;
    constexpr static uint element_capacity  = n / sizeof(Type);

    Type content[element_capacity] = {};
    uint elements_allocated = 0;

    inline Type* begin() { return &content[0]; }
    inline Type* end()   { return &content[element_capacity]; }
};


template <typename Type>
struct Memory
{
    Type* buffer    = nullptr;
    uint  max_count = 0;

    Type& operator[] (uint index)
    {
        if (index > max_count)
            return nullptr;

        return buffer[index];
    }

    inline Type* begin() { return &buffer[0]; }
    inline Type* end()   { return &buffer[max_count]; }
};


template <typename Type>
Memory<Type> Allocate(uint count, PoolAllocator<Type>& allocator)
{
    if (allocator.elements_allocated + count > allocator.element_capacity)
        return {nullptr, 0};

    Type* data = &allocator.content[allocator.elements_allocated];
    allocator.elements_allocated += count;

    return {data, count};
}

template <typename Type, uint count>
Memory<Type> Allocate(const Type (&data)[count], PoolAllocator<Type>& allocator)
{
    Memory<Type> memory = Allocate(count, allocator);
    std::memcpy(memory.buffer, data, count * sizeof(Type));
    return memory;
}

template <typename Type>
void Clear(PoolAllocator<Type>& allocator)
{
    allocator.elements_allocated = 0;
}

template <typename Type, uint count>
bool Write(Memory<Type>& memory, const Type (&data)[count], uint offset = 0)
{
    if (offset + count > memory.max_count)
        return false;

    for (uint i = 0; i < count; ++i)
        memory.buffer[offset + i] = data[i];

    return true;
}

template <typename Type>
bool Write(Memory<Type>& memory, const Type&& data, uint offset = 0)
{
    if (offset + 1 > memory.max_count)
        return false;

    memory.buffer[offset] = data;

    return true;
}



template <typename Type>
std::ostream& operator<< (std::ostream& os, Memory<Type>& memory)
{
    for (const auto& item : memory)
        os << item << ' ';
    return os;
}



struct Test
{
    int   i;
    bool  y;
    Memory<char> string;
};


int main()
{
    PoolAllocator<char> string_allocator {};
    PoolAllocator<int>  array_allocator {};
    PoolAllocator<Test> test_allocator {};

    Memory<char> string = Allocate(10, string_allocator);
    Memory<int>  array  = Allocate({1, 2, 3, 4, 5, 6, 7, 8, 9, 10}, array_allocator);

    Memory<Test> test1  = Allocate(3, test_allocator);
    Memory<Test> test2  = Allocate(
        {
            {1, false, Allocate({'N', 'o', '\0'},                string_allocator)},
            {5, true,  Allocate({'Y', 'e', 's', '\0'},           string_allocator)},
            {0, true,  Allocate({'M', 'a', 'y', 'b', 'e', '\0'}, string_allocator)}
        }, test_allocator
    );


    Write(string, 'H');
    Write(string, "ello", 1);  // String literals append a null character at the end.
    for (auto& character : string)
        std::cout << character;
    std::cout << std::endl;


    for (auto& element : array)
        std::cout << element << ' ';
    std::cout << std::endl;


    Write(test1, {1, false, Allocate("No",    string_allocator)}, 0);
    Write(test1, {5, true,  Allocate("Yes",   string_allocator)}, 1);
    Write(test1, {0, true,  Allocate("Maybe", string_allocator)}, 2);

    for (auto& item : test1)
        std::cout << item.i << ' ' << item.y << ' ' << item.string << '\n';
    std::cout << std::endl;


    for (auto& item : test2)
        std::cout << item.i << ' ' << item.y << ' ' << item.string << '\n';
    std::cout << std::endl;


    // After allocator is cleared, there are no guarantee that memory won't be overridden.
    Clear(string_allocator);
    Clear(array_allocator);
    Clear(test_allocator);
}