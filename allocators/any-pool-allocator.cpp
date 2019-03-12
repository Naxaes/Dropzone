#include <utility>
#include <iostream>

using uint = unsigned;

constexpr unsigned PAGE_SIZE = 4096;  // 4096 = 64 * 64 = 8 * 8 * 8 * 8 = 2^12

template <uint n = PAGE_SIZE, typename ... Types>
struct AnyPoolAllocator
{
    constexpr static uint capacity_in_bytes    = n;
    constexpr static uint sizes[] = { sizeof...(Types) };

    uint  bytes_used = 0;
    void* content[capacity_in_bytes]{};
    uint* element_sizes[capacity_in_bytes]{};
};

struct Node
{
    uint type;
    uint start;
};

template <uint n, typename ... Types>
uint InitializeTypeIndex(const AnyPoolAllocator<n, Types...>& allocator)
{
    static uint index = 0;
    return index++;
}

template <typename Type, uint n, typename ... Types>
Type Type(AnyPoolAllocator<n, Types...>& allocator, Node node)
{
    static uint index = InitializeTypeIndex(allocator);
    return index;
};


template <typename Type, uint n, typename ... Types>
Type Get(AnyPoolAllocator<n, Types...>& allocator, Node node)
{

};



template <typename Type>
struct Memory
{
    Type* buffer    = nullptr;
    uint  max_count = 0;

    Type& operator[] (uint index)
    {
        if (index > max_count)
            throw "Not valid!";

        return buffer[index];
    }

    inline Type* begin() { return &buffer[0]; }
    inline Type* end()   { return &buffer[max_count]; }
};


template <typename Type, uint n, typename ... Types>
Memory<Type> Allocate(uint count, AnyPoolAllocator<n, Types...>& allocator)
{
    // Static assert Type in Types.
    static_assert(true);

    uint size_in_bytes = sizeof(Type) * count;

    if (allocator.bytes_used + size_in_bytes > allocator.capacity_in_bytes)
        return {nullptr, 0};

    Type* data = reinterpret_cast<Type*>(&allocator.content[allocator.bytes_used]);
    allocator.bytes_used += size_in_bytes;

    for (size_t i = 0; i < n; ++i)
        allocator.element_sizes[i] = reinterpret_cast<uint*>(sizeof(Type));

    return {data, count};
}
//
// template <typename Type, uint count>
// Memory<Type> Allocate(const Type (&data)[count], PoolAllocator<Type>& allocator)
// {
//     Memory<Type> memory = Allocate(count, allocator);
//     std::memcpy(memory.buffer, data, count * sizeof(Type));
//     return memory;
// }

template <uint n, typename ... Types>
void Clear(AnyPoolAllocator<n, Types...>& allocator)
{
    allocator.bytes_used = 0;
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
    AnyPoolAllocator<PAGE_SIZE, int, double, Test> allocator;

    auto a = Allocate<int>(1, allocator);
    auto b = Allocate<Test>(1, allocator);
    auto c = Allocate<int>(1, allocator);
    auto d = Allocate<Test>(1, allocator);
    auto e = Allocate<int>(1, allocator);
    auto f = Allocate<Test>(1, allocator);
    auto g = Allocate<int>(1, allocator);

    Memory<char> string{"No", 3};

    a[0] = 0;
    b[0] = {0, false, string};
    c[0] = 1;
    d[0] = {1, true, string};
    e[0] = 2;
    f[0] = {2, false, string};
    g[0] = 3;

    std::cout << a[0] << std::endl;
    std::cout << b[0].i << ' ' << b[0].y << ' ' << b[0].string << '\n';
    std::cout << c[0] << std::endl;
    std::cout << d[0].i << ' ' << d[0].y << ' ' << d[0].string << '\n';
    std::cout << e[0] << std::endl;
    std::cout << f[0].i << ' ' << f[0].y << ' ' << f[0].string << '\n';
    std::cout << g[0] << std::endl;






    Clear(allocator);

}


















