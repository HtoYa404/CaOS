#include <iostream>
#include <unistd.h>
#include <pwd.h>
#include <grp.h>

int main(int argc, char *argv[]) {
    std::cout << "Arguments: ";
    for (int i = 1; i < argc; ++i) {   
        std::cout << argv[i] << " ";
    }
    std::cout << std::endl;
    
    std::printf("PID: %i | SID: %i | PGID: %i | PPID: %i\n", getpid(), getsid(0), getpgrp(), getppid());

    struct passwd *pw = getpwuid(getuid());
    std::cout << "User: " << pw->pw_name << std::endl;

    gid_t groups[100];
    int count = getgroups(100, groups);
    while (count--) 
        if (auto gr = getgrgid(groups[count])) 
            std::cout << gr->gr_name << " ";

    std::cout << std::endl;
    return 0;
}
