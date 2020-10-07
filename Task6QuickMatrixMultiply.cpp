#include <iostream>
#include <math.h>
#include <random>
#include <ctime>

using namespace std;

struct matrix{
    int* arr = 0;
    int size = 0;
};

matrix* split(matrix* m) {
    matrix* matrix_arr = new matrix[4];
    int new_size = m->size / 2;

    matrix_arr[0].arr = new int[new_size*new_size];
    matrix_arr[0].size = new_size;
    for (int i = 0; i < new_size; i++) {
        for (int j = 0; j < new_size; j++) {
            matrix_arr[0].arr[i*new_size + j] = m->arr[i*new_size + j];
        }
    }

    matrix_arr[1].arr = new int[new_size*new_size];
    matrix_arr[1].size = new_size;
    for (int i = 0; i < new_size; i++) {
        for (int j = new_size; j < 2*new_size; j++) {
            matrix_arr[1].arr[i*new_size + (j-new_size)] = m->arr[i*new_size + j];
        }
    }

    matrix_arr[2].arr = new int[new_size*new_size];
    matrix_arr[2].size = new_size;
    for (int i = new_size; i < 2*new_size; i++) {
        for (int j = 0; j < new_size; j++) {
            matrix_arr[2].arr[(i - new_size)*new_size + j] = m->arr[i*new_size + j];
        }
    }
    matrix_arr[3].arr = new int[new_size*new_size];
    matrix_arr[3].size = new_size;
    for (int i = new_size; i < 2*new_size; i++) {
        for (int j = new_size; j < 2*new_size; j++) {
            matrix_arr[3].arr[(i - new_size)*new_size + (j - new_size)] = m->arr[i*new_size + j];
        }
    }
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
    matrix* p1 = multiply(sum(&a_arr[0], &a_arr[3]), sum(&b_arr[0], &b_arr[3]));
    matrix* p2 = multiply(sum(&a_arr[2], &a_arr[3]), &b_arr[0]);
    matrix* p3 = multiply(&a_arr[0], sub(&b_arr[1], &b_arr[3]));
    matrix* p4 = multiply(&a_arr[3], sub(&b_arr[2], &b_arr[0]));
    matrix* p5 = multiply(sum(&a_arr[0], &a_arr[1]), &b_arr[3]);
    matrix* p6 = multiply(sub(&a_arr[2], &a_arr[0]), sum(&b_arr[0], &b_arr[1]));
    matrix* p7 = multiply(sub(&a_arr[1], &a_arr[3]), sum(&b_arr[2], &b_arr[3]));

    matrix* c1 = sub(sum(p1, p4), sum(p5, p7));
    matrix* c2 = sum(p3, p5);
    matrix* c3 = sum(p2, p4);
    matrix* c4 = sum(sub(p1,p2), sum(p3, p6));

    return merge(c1, c2, c3, c4);
}

matrix* createMatrix(int n) {
    int size = pow(2, n);
    matrix* result = new matrix;
    result->arr = new int[size*size];
    result->size = size;
    for (int i = 0; i < size*size; i++) result->arr[i] = rand() % 10;
    return result;
}

void print(matrix* m) {
    for (int i = 0; i < m->size; i++){
        for (int j = 0; j < m->size; j++)
            printf("%4i ", m->arr[i*m->size + j]);
        cout << endl;
    }
}

int main() {
    srand(time(0));
    matrix* a = createMatrix(0);
    matrix* b = createMatrix(0);
    print(a);
    print(b);
    print(multiply(a, b));





    return 0;
}