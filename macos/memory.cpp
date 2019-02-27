#include <unistd.h>  /* sysconf(3) */

inline long PageSize() { return sysconf(_SC_PAGESIZE);  /* _SC_PAGE_SIZE is OK too. */ }
