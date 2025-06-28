#include <iostream>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char* argv[]) {
    if (argc < 3 || (strcmp(argv[1], "-w") != 0 && strcmp(argv[1], "-f") != 0)) {
        std::cerr << "Usage: " << argv[0] << " -w|-f program [args...]\n";
        return 1;
    }

    bool wait_mode = (strcmp(argv[1], "-w") == 0);
    const char* program = argv[2];

    pid_t pid = fork();
    if (pid == -1) {
        perror("fork");
        return 1;
    }

    if (pid == 0) { 
        execvp(program, argv + 2);
        perror("execvp");
        exit(1);
    }

    if (wait_mode) {
        int status;
        waitpid(pid, &status, 0);
        std::cout << "Process " << pid << " exited with status " 
                  << WEXITSTATUS(status) << "\n";
    } else {
        std::cout << "Started process " << pid << " in background\n";
    }

    return 0;
}
