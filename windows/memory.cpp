#include <windows.h>
#include <stdlib.h>

#include "../memory.h"


inline long PageSize()
{
    SYSTEM_INFO si;
    GetSystemInfo(&si);
    return si.dwPageSize;
}


size_t CacheLineSize()
{
    size_t line_size = 0;
    DWORD buffer_size = 0;
    DWORD i = 0;
    SYSTEM_LOGICAL_PROCESSOR_INFORMATION * buffer = 0;

    GetLogicalProcessorInformation(0, &buffer_size);
    buffer = (SYSTEM_LOGICAL_PROCESSOR_INFORMATION *)malloc(buffer_size);
    GetLogicalProcessorInformation(&buffer[0], &buffer_size);

    for (i = 0; i != buffer_size / sizeof(SYSTEM_LOGICAL_PROCESSOR_INFORMATION); ++i)
    {
        if (buffer[i].Relationship == RelationCache && buffer[i].Cache.Level == 1)
        {
            line_size = buffer[i].Cache.LineSize;
            break;
        }
    }

    free(buffer);
    return line_size;
}


CacheMemory CacheMemorySizes()
{
    throw "Not implemented";
};

size_t MainMemorySize()
{
    throw "Not implemented";
}