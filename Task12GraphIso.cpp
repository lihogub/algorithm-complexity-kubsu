#include <iostream>
#include "math.h"
using namespace std;

int counter = 0;

void f(int c=1) {
    counter += c;
}

class Matrix {
    private:
        int* mapping = 0;
        int* matrix = 0;
        int size = 0;
    public:
        Matrix(int size) {
            (*this).size = size; 
            f();
            matrix = new int[size*size]; 
            f(3);
            mapping = new int[size]; 
            f(2);
            for (int i = 0; i < size; i++) {
                mapping[i] = i; 
                f();
                for (int j = i; j < size; j++) {
                    f();
                    if (i != j) {
                        f();
                        int tmp = rand() % 2;
                        f(3);
                        matrix[i*size + j] = tmp;
                        f(3);
                        matrix[j*size + i] = tmp;
                    } else {
                        f(3);
                        matrix[i*size+i] = 0;
                    }
                }
            }
        }
        
        Matrix(const Matrix &m) {
            f();
            size = m.size;
            f(3);
            matrix = new int[size*size];
            f(2);
            mapping = new int[size];
            for (int i = 0; i < size; i++) {
                f(1);
                mapping[i] = m.mapping[i];
                for (int j = 0; j < size; j++) {
                    f(3);
                    int tmp = rand() % 2;
                    f(5);
                    matrix[i*size + j] = m.matrix[i*size + j];
                    f(5);
                    matrix[j*size + i] = m.matrix[j*size + i];
                }
            }
        }

        void show() {
            for (int i = 0; i < 2*size-1; i++) {
                cout << "-";
            }
            cout << endl;
            for (int i = 0; i < size; i++) {
                for (int j = 0; j < size; j++) {
                    cout << matrix[i*size + j] << " ";
                }
                cout << endl;
            }
        }

        void showMapping() {
            for (int i = 0; i < 2*size-1; i++) {
                cout << "-";
            }
            cout << endl;
            for (int i = 0; i < size; i++) {
                cout << mapping[i] << " ";
            }
            cout << endl;
        }

        int change(int a, int b) {
            f(3);
            swap(mapping[a], mapping[b]);
            for (int i = 0; i < size; i++) {
                f(7);
                swap(matrix[i*size + a], matrix[i*size + b]);
            }
            for (int i = 0; i < size; i++) {
                f(7);
                swap(matrix[a*size + i], matrix[b*size + i]);
            }
            return 0;
        }

        bool isEqual(const Matrix& m) {
            f();
            if (size!= m.size)
                return false;
            for (int i = 0; i < size; i++) {
                for (int j = i; j < size; j++) {
                    f(5);
                    if (matrix[i*size + j] != m.matrix[i*size + j])
                        return false;
                }
            }
            return true;
        }

        void shuffle() {
            for (int i = 0; i < size*size; i++) {
                change(rand()%size, rand()%size);
            }
        }

};

bool isSucceed = false;
Matrix succeedMatrix(0);

void tryPermutation(Matrix& origin, Matrix& matrix, bool* fixedVertices, int& totalVertices, int depth) {
    f(2);
    if (depth > totalVertices || isSucceed) return;
    f();
    if (origin.isEqual(matrix)) {
        f();
        isSucceed = true;
        f();
        succeedMatrix = matrix;
        return;
    }
    for (int i = 0; i < totalVertices; i++) {
        f();
        if (fixedVertices[i]) continue;
        for (int j = 0; j < totalVertices; j++) {
            f();
            if (fixedVertices[j]) continue;
            f();
            matrix.change(i, j);
            f();
            fixedVertices[i] = true;
            f();
            tryPermutation(origin, matrix, fixedVertices, totalVertices, depth+1);
            f();
            fixedVertices[i] = false;
            f();
            matrix.change(i, j);
        }
    }
}

unsigned long long testDrive(int size, int iterations) {
    unsigned long long s = 0;

    for (int i = 0; i < iterations; i++) {
        isSucceed = false;
        Matrix origin(size);
        Matrix copy = origin;
        copy.shuffle();
        bool fixedV[size] = {0};
        counter = 0;
        tryPermutation(origin, copy, fixedV, size, 0);
        s += counter;
    }
    s /= iterations;
    return s;
}

unsigned long long factorial(int n) {
    unsigned long long m = 1;
    for (int i = 2; i <= n; i++) {
        m *= i;
    }
    return m;
} 

unsigned long long appr(int n) {
    unsigned long long result = 0;
    

}

int main() {
    srand(time(0));
    for (int size = 1; size < 10; size++){
        cout << size << ";" << testDrive(size, 10) << endl;
    }
    return 0;
}
