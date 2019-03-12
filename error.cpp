#include <iostream>
#include <cstring>
#include <cstdarg>

#ifndef ASSERTION_MESSAGE_BUFFER_SIZE
#define ASSERTION_MESSAGE_BUFFER_SIZE 256
#endif

#ifndef TERMINATE_ON_ASSERTION_FAILURE
#define TERMINATE_ON_ASSERTION_FAILURE true
#endif


#define Assert(statement, ...) AssertImplementation(statement, #statement, __FILE__, __LINE__, __VA_ARGS__)
void AssertImplementation(bool status, const char* statement, const char* file, unsigned line, const char* message, ...)
{
    if (status)
        return;
    
    char* buffer = new char[ASSERTION_MESSAGE_BUFFER_SIZE];
    strncpy(buffer, message, ASSERTION_MESSAGE_BUFFER_SIZE);

    va_list argptr;
    va_start(argptr, message);
    vsnprintf(buffer, ASSERTION_MESSAGE_BUFFER_SIZE, message, argptr);
    va_end(argptr);

    fprintf(
            stderr,
            "[Assertion Error] (%s):\n"
            "\tFile:     %s\n"
            "\tLine:     %i\n"
            "\tMessage:  %s\n",
            statement, file, line, buffer
    );

    if constexpr (TERMINATE_ON_ASSERTION_FAILURE)
        exit(-1);
}
