#include <stdio.h>

struct long_num{
    int* arr;
    int length;
};

int max(int a, int b) {
    if (a > b) return a;
    return b;
}

int min(int a, int b) {
    if (a < b) return a;
    return b;
}

int long_num_to_int(long_num* num) {
    int s = 0;
    int m = 1;
    for (int i = 0; i < num->length; i++) {
        s += num->arr[i]*m;
        m *= 10;
    }
    return s;
}

long_num* split_array(long_num* number) {
    long_num* result = new long_num[2]; 
    result[0].length = number->length / 2;
    result[1].length = number->length - number->length / 2;
    result[0].arr = new int[result[0].length];
    result[1].arr = new int[result[1].length];
    for (int i = 0; i < result[0].length; i++){
        result[0].arr[i] = number->arr[i];
    }
    for (int i = 0; i < result[1].length; i++){
        result[1].arr[i] = number->arr[i + result[0].length];
    }
    return result;
}

long_num* multiply_to_power_ten(long_num* num, int power) {
    num->length;
    long_num* new_num = new long_num;
    new_num->length = num->length + power;
    for (int i = 0; i < power; i++) 
        new_num->arr[i] = 0;
    for (int i = 0; i < new_num->length; i++) 
        new_num->arr[i + power] = num->arr[i];
    return new_num;
}

long_num* sum(long_num* a, long_num* b) {
    long_num* result = new long_num;
    result->length = max(a->length, b->length) + 1;
    result->arr = new int[result->length];
    int buffer = 0;
    for (int i = 0; i < min(a->length, b->length); i++) {
        buffer += a->arr[i] + b->arr[i];
        result->arr[i] = buffer % 10;
        buffer /= 10;
    }
    for (int i = min(a->length, b->length); i < result->length; i++) {
        result->arr[i] = buffer % 10;
        buffer /= 10;
    }
    return result;
}

long_num* multiply(long_num* U, long_num* V) {
    if (U->length == 1 && V->length == 1) {
        long_num* num = new long_num;
        num->arr[0] = U->arr[0]*V->arr[0];
        num->length = 1;
        return num;
    }
    long_num* U2U1 = split_array(U);
    long_num* V2V1 = split_array(V);
    long_num U2 = U2U1[0];
    long_num U1 = U2U1[1];
    long_num V2 = V2V1[0];
    long_num V1 = V2V1[1];





    return 0;
}



int main() {
    int arr1[] = {7, 8, 9};
    int arr2[] = {1, 1, 1};
    long_num* a = new long_num;
    long_num* b = new long_num;
    a->arr = arr1;
    a->length = 3;
    b->arr = arr2;
    b->length = 3;


    printf("%i\n", long_num_to_int(sum(a,b)));

    return 0;
}