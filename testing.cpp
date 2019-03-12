#include <iostream>
#include "allocators/linked-pool-allocator.cpp"


#define Test(name) all_tests[name] = Test()



struct Test
{

};

#include <unordered_map>
struct TestMatrix
{
    std::unordered_map<const char*, Test> tests;
} all_tests;


bool CheckImplementation(
        bool assertion,
        const char* statement,
        const char* value,
        const char* file,
        int line
)
{


}


int m()
{
    LinkedPoolAllocator<int> allocator;


    Check(Allocate(allocator,  5),  5);
    Check(Allocate(allocator, -5), -5);
    Check(Allocate(allocator,  0),  0);
}