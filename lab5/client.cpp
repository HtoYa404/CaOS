#include <iostream>
#include <fstream>
#include <string>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include "matrixes.cpp"

#define FIFO_NAME "./fifofile"

void sendMatrix(int fd, const Matrix& m) {
    write(fd, &m.height, sizeof(int));
    write(fd, &m.width, sizeof(int));
    for (int i = 0; i < m.height; ++i) {
        write(fd, m.matrix[i], sizeof(int) * m.width);
    }
}

int main() {
    int h, w;
    std::cout << "Enter dimensions for both matrices (height width): ";
    std::cin >> h >> w;

    Matrix m1(h, w), m2(h, w);
    std::cout << "Enter elements for Matrix 1:\n";
    m1.readFromUser();

    std::cout << "Enter elements for Matrix 2:\n";
    m2.readFromUser();

    int fd = open(FIFO_NAME, O_WRONLY);
    if (fd < 0) {
        std::cerr << "Failed to open FIFO for writing\n";
        return 1;
    }

    sendMatrix(fd, m1);
    sendMatrix(fd, m2);

    close(fd);
    return 0;
}
