#include <iostream>
#include <fstream>
#include <string>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include "matrixes.cpp"

#define FIFO_NAME "./fifofile"
Matrix receiveMatrix(int fd) {
    int h, w;
    read(fd, &h, sizeof(int));
    read(fd, &w, sizeof(int));

    Matrix m(h, w);
    for (int i = 0; i < h; ++i) {
        read(fd, m.matrix[i], sizeof(int) * w);
    }

    return m;
}

int main() {
    mkfifo(FIFO_NAME, 0600);
	int fd = open(FIFO_NAME, O_RDONLY);
    if (fd < 0) {
        std::cerr << "Failed to open FIFO for reading\n";
        return 1;
    }else{
		std::cout << "FIFO created, waiting for client\n";
	}

    Matrix m1 = receiveMatrix(fd);
    Matrix m2 = receiveMatrix(fd);
    std::cout << "recieved matrixes: \n";
	output(m1);
	output(m2);
	std::cout << "result of multiplication: \n";

	Matrix res = multiply(m1, m2);
	output(res);
    
	close(fd);
    unlink(FIFO_NAME);
    return 0;
}

