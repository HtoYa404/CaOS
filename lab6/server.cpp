#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include "matrixes.hpp"

#define PORT 8080
#define BUFFER_SIZE 1024

Matrix receiveMatrix(int sock) {
    int h, w;
    recv(sock, &h, sizeof(int), 0);
    recv(sock, &w, sizeof(int), 0);

    Matrix m(h, w);
    for (int i = 0; i < h; ++i) {
        recv(sock, m.matrix[i], sizeof(int) * w, 0);
    }

    return m;
}

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }
    
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);
        
    std::cout << "Waiting for client connection..." << std::endl;
    if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
        perror("accept");
        exit(EXIT_FAILURE);
    }

    Matrix m1 = receiveMatrix(new_socket);
    Matrix m2 = receiveMatrix(new_socket);
    
    std::cout << "Received matrixes: \n";
    output(m1);
    output(m2);
    
    std::cout << "Product of matrices: \n";
    Matrix product = multiply(m1, m2);
    output(product);
    
    close(new_socket);
    close(server_fd);
    return 0;
}
