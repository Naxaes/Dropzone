#pragma once
#include <cstddef>


struct CacheMemory
{
    unsigned long cache_line;
    unsigned long l1_instruction_cache_line;
    unsigned long l1_data_cache_line;
    unsigned long l2_cache_line;
    unsigned long l3_cache_line;
};


CacheMemory CacheMemorySizes();
size_t      MainMemorySize();


// -- PageSize --
// Returns the page size (int bytes).
inline long PageSize();


// -- CacheLineSize --
// Returns the cache line size (in bytes) of the processor, or 0 on failure.
//
// Source: https://stackoverflow.com/a/4049562/6486738
// Author: Nick Strupat
// Date: October 29, 2010
// Modified: March 5, 2019, Ted Klein Bergman
size_t CacheLineSize();