#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <curses.h>
#include <ctime>
#include <string>
#include <iostream>

int main()
{
    initscr();
    WINDOW* p_window = newwin(10, 50, 0, 50);
    WINDOW* c_window = newwin(10, 50, 0, 0);
    if (!p_window || !c_window)
    {
        endwin();
        return -1;
    }
    refresh();
    __pid_t pid = fork();
    switch(pid)
    {
    case 0: // this is child process
        box(c_window, 0, 0);
        waddstr(c_window, "this is child process, time is ");
        waddstr(c_window, std::to_string(time(NULL)).c_str());
        wrefresh(c_window);
        break;
    case -1: // creating failed
        endwin();
        return -1;
        break;
    default: // this is parent process
        waitpid(pid, NULL, 0);
        box(p_window, 0, 0);
        waddstr(p_window, "this is parent process, time is ");
        waddstr(p_window, std::to_string(time(NULL)).c_str());
        wrefresh(p_window);
        std::cin.get();
        endwin();
    }
    return 0;
}