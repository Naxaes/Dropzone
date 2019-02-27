
// #ifdef _WIN32
//     #include  "Windows 32-bit";
// #elif _WIN64
//     #include  "Windows 64-bit";
// #elif __CYGWIN__                    // Windows with Cygwin (POSIX)
//     #include  "Windows 32-bit (Cygwin)";
// #elif __APPLE__ || __MACH__
//     #include  "Mac OSX";
// #elif __linux__                     // any GNU/Linux distribution
//     #include  "Linux";
// #elif __unix || __unix__
//     #include  "Unix";
// #elif __FreeBSD__
//     #include  "FreeBSD";
// #elif defined(BSD)                  // BSD (DragonFly BSD, FreeBSD, OpenBSD, NetBSD)
//     #include  "BSD (DragonFly BSD, FreeBSD, OpenBSD, NetBSD)";
// #elif defined(__QNX__)              // QNX
//     #include  "QNX";
// #elif _AIX                          // AIX
//     #include  "AIX";
// #elif __hpux                        // HP-UX
//     #include  "HP-UX";
// #elif __sun                         // Solaris
//     #include  "Solaris";
// #else
//     #include  "Unknown";
// #endif







constexpr char[] OSName()
{
    // http://nadeausoftware.com/articles/2012/01/c_c_tip_how_use_compiler_predefined_macros_detect_operating_system
    #ifdef _WIN32
        return "Windows 32-bit";
    #elif _WIN64
        return "Windows 64-bit";
    #elif __CYGWIN__                    // Windows with Cygwin (POSIX)
        return "Windows 32-bit (Cygwin)";
    #elif __APPLE__ || __MACH__
        return "Mac OSX";
    #elif __linux__                     // any GNU/Linux distribution
        return "Linux";
    #elif __unix || __unix__
        return "Unix";
    #elif __FreeBSD__
        return "FreeBSD";
    #elif defined(BSD)                  // BSD (DragonFly BSD, FreeBSD, OpenBSD, NetBSD)
        return "BSD (DragonFly BSD, FreeBSD, OpenBSD, NetBSD)";
    #elif defined(__QNX__)              // QNX
        return "QNX";
    #elif _AIX                          // AIX
        return "AIX";
    #elif __hpux                        // HP-UX
        return "HP-UX";
    #elif __sun                         // Solaris
        return "Solaris";
    #else
        return "Unknown";
    #endif
}
