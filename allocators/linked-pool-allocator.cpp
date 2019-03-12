#include <cstdlib>
#include <utility>
#include <iostream>

/*

 Worst case scenario:
     Freeing the last element in the allocator when all previous elements has been free requires O(n) iterations
     through the free list. This could be halved by using a doubly linked list.




 */



constexpr unsigned PAGE_SIZE = 4096;

template <typename Type>
struct Node
{
    union
    {
        Type  value;
        Node* next;   // TODO(ted): Should use unsigned to point to next index.
    };
};


template <typename Type, unsigned count = PAGE_SIZE>
struct LinkedPoolAllocator
{
    static constexpr unsigned element_count = count;

    Node<Type>  elements[count];
    Node<Type>* free_list = &elements[0];

    LinkedPoolAllocator()
    {
        for (unsigned i = 0; i < count-1; ++i)
            elements[i].next = &elements[i+1];

        elements[count-1].next = nullptr;
    }
};


template <typename Type, typename ... TypeArguments>
Type& Allocate(LinkedPoolAllocator<Type>& allocator, TypeArguments&& ... arguments)
{
    if (!allocator.free_list)
        exit(-1);

    Type& data = allocator.free_list->value;
    allocator.free_list = allocator.free_list->next;

    data = { std::forward<TypeArguments>(arguments)... };
    return data;
}


template <typename Type>
void Free(Type& data, LinkedPoolAllocator<Type>& allocator)
{

    unsigned long data_index;
    {
        long data_address  = reinterpret_cast<intptr_t>(&data);
        long start_address = reinterpret_cast<intptr_t>(&allocator.elements);
        long end_address   = reinterpret_cast<intptr_t>(&allocator.elements) + (allocator.element_count * sizeof(Type));

        long address_offset = data_address - start_address;
        if (address_offset < 0 || address_offset > end_address)  // Data is not a member of the allocator.
            return;

        data_index = address_offset / sizeof(Node<Type>);
    }

    Node<Type>* data_node = &allocator.elements[data_index];
    Node<Type>* free_node = allocator.free_list;

    if (!free_node)  // Allocator has no free slots.
        return;

    // If the free node is after current node.
    if (free_node > data_node)
    {
        data_node->next = free_node;
        allocator.free_list = data_node;

        return;
    }


    // If the free node is before current node, we find the free node that is just before the current node.
    {
        Node<Type>* previous_free_node = free_node;
        Node<Type>* next_free_node = free_node->next;

        while (next_free_node < data_node)
        {
            previous_free_node = next_free_node;
            next_free_node = next_free_node->next;
        }

        // 'previous_free_node' should be the node just before the current node.
        // 'next_free_node'     should be the node just after  the current node.
        previous_free_node->next = data_node;
        data_node->next = next_free_node;
    }
}





struct Value
{
    int i;
    int j;
};



int main()
{
    LinkedPoolAllocator<int> int_allocator;

    int& x = Allocate(int_allocator);
    int& y = Allocate(int_allocator);
    int& z = Allocate(int_allocator);

    Free(y, int_allocator);

    LinkedPoolAllocator<Value> struct_allocator;

    Value& a = Allocate(struct_allocator, 1, 5);
    Value& b = Allocate(struct_allocator, 2, 5);
    Value& c = Allocate(struct_allocator, 3, 5);

    std::cout << a.i << ' ' << a.j << '\n';
    std::cout << b.i << ' ' << b.j << '\n';
    std::cout << c.i << ' ' << c.j << '\n';

    Free(c, struct_allocator);
}










