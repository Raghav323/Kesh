#include "../include/defs.hpp"
#include "../include/Search.hpp"

#ifndef WIN32
#include <sys/select.h>
#include <unistd.h>
#else
#include <Windows.h>
#endif

bool InputWaiting() {
#ifndef WIN32
    fd_set readfds;
    struct timeval tv;
    FD_ZERO(&readfds);
    FD_SET(fileno(stdin), &readfds);
    tv.tv_sec = 0;
    tv.tv_usec = 0;
    select(16, &readfds, nullptr, nullptr, &tv);
    return (FD_ISSET(fileno(stdin), &readfds));
#else
    static int init = 0;
    static HANDLE inh;
    DWORD dw;

    if (!init) {
        init = 1;
        inh = GetStdHandle(STD_INPUT_HANDLE);
        int pipe = !GetConsoleMode(inh, &dw);
        if (!pipe) {
            SetConsoleMode(inh, dw & ~(ENABLE_MOUSE_INPUT | ENABLE_WINDOW_INPUT));
            FlushConsoleInputBuffer(inh);
        }
    }

    if (PeekNamedPipe(inh, nullptr, 0, nullptr, &dw, nullptr)) {
        return dw > 0;
    } else {
        GetNumberOfConsoleInputEvents(inh, &dw);
        return dw > 1;
    }
#endif
}

