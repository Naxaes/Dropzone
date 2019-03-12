#include <stddef.h>
#include <sys/sysctl.h>
#include <unistd.h>         /* sysconf(3) */

#include "../memory.h"


inline long PageSize()
{
    return PAGE_SIZE;
    // return sysconf(_SC_PAGESIZE);
    // return sysconf(_SC_PAGE_SIZE);
}


size_t CacheLineSize()
{
    size_t line_size = 0;
    size_t sizeof_line_size = sizeof(line_size);
    sysctlbyname("hw.cachelinesize", &line_size, &sizeof_line_size, 0, 0);
    return line_size;
}

CacheMemory CacheMemorySizes()
{

    size_t line_size = 0;
    size_t sizeof_line_size = sizeof(line_size);

    sysctlbyname("hw.cachelinesize", &line_size, &sizeof_line_size, nullptr, 0);
    unsigned long cache_line = line_size;
    sysctlbyname("hw.l1icachesize", &line_size, &sizeof_line_size, nullptr, 0);
    unsigned long l1_instruction_cache_line = line_size;
    sysctlbyname("hw.l1dcachesize", &line_size, &sizeof_line_size, nullptr, 0);
    unsigned long l1_data_cache_line = line_size;
    sysctlbyname("hw.l2cachesize", &line_size, &sizeof_line_size, nullptr, 0);
    unsigned long l2_cache_line = line_size;
    sysctlbyname("hw.l3cachesize", &line_size, &sizeof_line_size, nullptr, 0);
    unsigned long l3_cache_line = line_size;

    return {cache_line, l1_instruction_cache_line, l1_data_cache_line, l2_cache_line, l3_cache_line};
}

size_t MainMemorySize()
{
    size_t memory_size = 0;
    size_t sizeof_memory_size = sizeof(memory_size);

    sysctlbyname("hw.memsize", &memory_size, &sizeof_memory_size, nullptr, 0);
    return memory_size;
}