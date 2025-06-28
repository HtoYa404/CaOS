#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "matrixes.hpp"

#define PORT 8080

void sendMatrix(int sock, const Matrix& m) {
    send(sock, &m.height, sizeof(int), 0);
    send(sock, &m.width, sizeof(int), 0);
    for (int i = 0; i < m.height; ++i) {
        send(sock, m.matrix[i], sizeof(int) * m.width, 0);
    }
}

int main() {
    int sock = 0;
    struct sockaddr_in serv_addr;

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        std::cerr << "Socket creation error" << std::endl;
        return 1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
    
    int h, w;
    std::cout << "Enter dimensions for both matrices (height width): ";
    std::cin >> h >> w;

    Matrix m1(h, w), m2(h, w);
    std::cout << "Enter elements for Matrix 1:\n";
    m1.readFromUser();

    std::cout << "Enter elements for Matrix 2:\n";
    m2.readFromUser();

    sendMatrix(sock, m1);
    sendMatrix(sock, m2);

    close(sock);
    return 0;
}
