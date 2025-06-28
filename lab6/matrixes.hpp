#pragma once

#include <cmath>
using namespace std;

struct Matrix {
    int height;
    int width;
    int** matrix;
    Matrix(int h, int w) : height(h), width(w) {
        matrix = new int*[height];
        for (int i = 0; i < height; ++i) {
            matrix[i] = new int[width];
        }
    }
    void fill() {
        for (int i = 0; i < height; ++i) {
            for (int j = 0; j < width; ++j) {
                matrix[i][j] = rand() % 100;  
            }
        }
    }
	void readFromUser() {
        std::cout << "Enter elements row by row:\n";
        for (int i = 0; i < height; ++i) {
            std::cout << "Row " << i + 1 << ": ";
            for (int j = 0; j < width; ++j) {
                std::cin >> matrix[i][j];
            }
        }
    }
};

Matrix multiply(const Matrix& a, const Matrix& b) {
    Matrix c(a.height, b.width);
    for (int i = 0; i < a.height; ++i) {
        for (int j = 0; j < b.width; ++j) {
            c.matrix[i][j] = 0;  
            for (int k = 0; k < a.width; ++k) {
                c.matrix[i][j] += a.matrix[i][k] * b.matrix[k][j];
            }
        }
    }
    return c;
}

void output(const Matrix a) {
    for (int i = 0; i < a.height; ++i) {
        for (int j = 0; j < a.width; ++j) {
            cout << a.matrix[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}
/*
int main() {
    int w1, w2, h1, h2;
    cin >> h1 >> w1 >> h2 >> w2;
    if (w1 != h2) {
        cout << "incompatible matrix dimensions for multiplication" << endl;
        return 1;
    }
    Matrix m1(h1, w1);
    Matrix m2(h2, w2);
    m1.fill();
    m2.fill();
    output(m1);
    output(m1);
    output(multiply(m1, m2));
    return 0;
}*/
