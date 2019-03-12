#if _WIN32 ||  _WIN64
    #include  "windows/memory.cpp"
#elif __CYGWIN__                    // Windows with Cygwin (POSIX)
    #error Cygwin currently not supported
#elif __APPLE__ || __MACH__
    #include  "macos/memory.cpp"
#elif __linux__                     // any GNU/Linux distribution
    #include  "linux/memory.cpp"
#elif __unix || __unix__
    #error Unix currently not supported
#elif __FreeBSD__
    #error  FreeBSD currently not supported
#elif defined(BSD)                  // BSD (DragonFly BSD, FreeBSD, OpenBSD, NetBSD)
    #error BSD (DragonFly BSD, FreeBSD, OpenBSD, NetBSD) currently not supported
#elif defined(__QNX__)              // QNX
    #error QNX currently not supported
#elif _AIX                          // AIX
    #error AIX currently not supported
#elif __hpux                        // HP-UX
    #error HP-UX currently not supported
#elif __sun                         // Solaris
    #error Solaris currently not supported
#else
    #error Unrecognized platform
#endif

#include <iostream>


int main()
{
    auto main_size = MainMemorySize();
    auto page_size = PageSize();
    auto caches    = CacheMemorySizes();

    printf("Main Memory size:           %li bytes.\n", main_size);
    printf("Page Size:                  %li bytes.\n", page_size);

    printf("Cache Line:                 %li bytes.\n", caches.cache_line);
    printf("L1 Instruction Cache Line:  %li bytes.\n", caches.l1_instruction_cache_line);
    printf("l1 Data Cache Line:         %li bytes.\n", caches.l1_data_cache_line);
    printf("L2 Cache Line:              %li bytes.\n", caches.l2_cache_line);
    printf("L3 Cache Line:              %li bytes.\n", caches.l3_cache_line);

}