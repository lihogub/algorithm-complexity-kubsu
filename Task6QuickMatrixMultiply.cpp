#include <iostream>
#include <math.h>
#include <random>
#include <ctime>

using namespace std;

struct matrix{
    int* arr = 0;
    int size = 0;
};


void print(matrix* m) {
    for (int i = 0; i < m->size; i++){
        for (int j = 0; j < m->size; j++)
            printf("%4i ", m->arr[i*m->size + j]);
        cout << endl;
    }
}

matrix* split(matrix* m) {
    matrix* matrix_arr = new matrix[4];
    int new_size = m->size / 2;

    matrix_arr[0].arr = new int[new_size*new_size];
    matrix_arr[0].size = new_size;
    for (int i = 0; i < new_size; i++) {
        for (int j = 0; j < new_size; j++) {
            matrix_arr[0].arr[i*new_size + j] = m->arr[i*new_size*2 + j];
        }
    }
    
    matrix_arr[1].arr = new int[new_size*new_size];
    matrix_arr[1].size = new_size;
    for (int i = 0; i < new_size; i++) {
        for (int j = 0; j < new_size; j++) {
            matrix_arr[1].arr[i*new_size + j] = m->arr[i*new_size*2 + (j + new_size)];
        }
    }

    matrix_arr[2].arr = new int[new_size*new_size];
    matrix_arr[2].size = new_size;
    for (int i = 0; i < new_size; i++) {
        for (int j = 0; j < new_size; j++) {
            matrix_arr[2].arr[i*new_size + j] = m->arr[(i + new_size)*new_size*2 + j];

        }
    }

    matrix_arr[3].arr = new int[new_size*new_size];
    matrix_arr[3].size = new_size;
    for (int i = 0; i < new_size; i++) {
        for (int j = 0; j < new_size; j++) {
            matrix_arr[3].arr[i*new_size + j] = m->arr[i*new_size*4 + new_size + j];
        }
    }

    /*
    print(m);
    print(&matrix_arr[0]);
    print(&matrix_arr[1]);
    print(&matrix_arr[2]);
    print(&matrix_arr[3]);
    */
    return matrix_arr;
}

matrix* merge(matrix* c1, matrix* c2, matrix* c3, matrix* c4) {
    int new_size = c1->size*2;
    matrix* result = new matrix;
    result->arr = new int[new_size*new_size];
    result->size = new_size;

    for (int i = 0; i < new_size / 2; i++) 
        for (int j = 0; j < new_size / 2; j++) 
            result->arr[i*new_size + j] = c1->arr[i*new_size + j];

    for (int i = 0; i < new_size / 2; i++) 
        for (int j = 0; j < new_size / 2; j++) 
            result->arr[i*new_size + (j + new_size/2)] = c2->arr[i*new_size + j];

    for (int i = 0; i < new_size / 2; i++) 
        for (int j = 0; j < new_size / 2; j++) 
            result->arr[(i + new_size/2)*new_size + j] = c3->arr[i*new_size + j];
    
    for (int i = 0; i < new_size / 2; i++) 
        for (int j = 0; j < new_size / 2; j++) 
            result->arr[(i + new_size/2)*new_size + (j + new_size/2)] = c4->arr[i*new_size + j];
    return result;
}

matrix* sum(matrix* a, matrix* b) {
    matrix* result = new matrix;
    result->arr = new int[a->size * a->size];
    result->size = a->size;
    for (int i = 0; i < result->size; i++) 
        for (int j = 0; j < result->size; j++) 
            result->arr[i * result->size + j] = a->arr[i * result->size + j] + b->arr[i * result->size + j];
    return result;
}

matrix* sub(matrix* a, matrix* b) {
    matrix* result = new matrix;
    result->arr = new int[a->size * a->size];
    result->size = a->size;
    for (int i = 0; i < result->size; i++) 
        for (int j = 0; j < result->size; j++) 
            result->arr[i * result->size + j] = a->arr[i * result->size + j] - b->arr[i * result->size + j];
    return result;
}

matrix* multiply(matrix* a, matrix* b) {
    if (a->size == 1) {
        matrix* result = new matrix;
        result->arr = new int[1];
        result->arr[0] = a->arr[0] * b->arr[0];
        result->size = 1;
        return result;
    }
    matrix* a_arr = split(a);
    matrix* b_arr = split(b);

    matrix* a11 = &a_arr[0];
    matrix* a12 = &a_arr[1];
    matrix* a21 = &a_arr[2];
    matrix* a22 = &a_arr[3];

    matrix* b11 = &b_arr[0];
    matrix* b12 = &b_arr[1];
    matrix* b21 = &b_arr[2];
    matrix* b22 = &b_arr[3];

    matrix* p1 = multiply(sum(a11, a22), sum(b11, b22));
    matrix* p2 = multiply(sum(a21, a22), b11);
    matrix* p3 = multiply(a11, sub(b12, b22));
    matrix* p4 = multiply(a22, sub(b21, b11));
    matrix* p5 = multiply(sum(a11, a12), b22);
    matrix* p6 = multiply(sub(a21, a11), sum(b11, b12));
    matrix* p7 = multiply(sub(a12, a22), sum(b21, b22));


    matrix* c1 = sum(sub(sum(p1, p4),p5), p7);
    matrix* c2 = sum(p3, p5);
    matrix* c3 = sum(p2, p4);
    matrix* c4 = sub(sum(sum(p3, p6), p1), p2);
    /*
    print(c1);
    print(c2);
    print(c3);
    print(c4);
    */

    return merge(c1, c2, c3, c4);
}

matrix* simpleMultiply(matrix* a, matrix* b) {
    matrix* result = new matrix;
    result->size = a->size;
    result->arr = new int[result->size*result->size];
    for (int i = 0; i < result->size; i++)
        for (int j = 0; j < result->size; j++){
            result->arr[i*result->size + j] = 0;
            for (int k = 0; k < result->size; k++) {
                result->arr[i*result->size + j] += a->arr[i*result->size + k]*b->arr[k*result->size + j];
            }
        }
    return result;
}


matrix* createMatrix(int n) {
    int size = pow(2, n);
    matrix* result = new matrix;
    result->arr = new int[size*size];
    result->size = size;
    for (int i = 0; i < size*size; i++) result->arr[i] = rand() % 10;
    return result;
}


int main() {
    srand(time(0));
    int n = 1;
    matrix* a = createMatrix(n);
    matrix* b = createMatrix(n);
    print(a);
    print(b);
    print(simpleMultiply(a, b));

    print(multiply(a, b));

    return 0;
}