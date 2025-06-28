#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <syslog.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/resource.h>
#include <iostream>

void sigusr1_handler(int signum) {
    syslog(LOG_INFO, "Received SIGUSR1 signal");
    signal(SIGUSR1, sigusr1_handler); 
}

void sigint_handler(int signum) {
    syslog(LOG_INFO, "Daemon exiting on SIGINT signal");
    closelog();
    exit(EXIT_SUCCESS);
}

void daemonize() {
    pid_t pid, sid;
    
    pid = fork();
    if (pid < 0) {
        exit(EXIT_FAILURE);
    }
    
    if (pid > 0) {
		std::cout << "proces sucsesfully starterd with PID: " << pid;
		exit(EXIT_SUCCESS);
    }
    
    sid = setsid();
    if (sid < 0) {
        exit(EXIT_FAILURE);
    }
    
    chdir("/");
    
    struct rlimit flim;
    getrlimit(RLIMIT_NOFILE, &flim);
    for (int fd = 0; fd < flim.rlim_max; fd++) {
        close(fd);
    }
    
    openlog("daemon", LOG_PID, LOG_LOCAL0);
    syslog(LOG_INFO, "Daemon started with PID: %d", getpid());
}

int main() {
    daemonize();
    
    signal(SIGUSR1, sigusr1_handler);
    signal(SIGINT, sigint_handler);
    
    while(1) {
        pause(); 
 	}
    
    return EXIT_SUCCESS;
}
