#include <iostream>
#include <random>
#include <math.h>
using namespace std;

int global_counter = 0;

struct longNum{
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

int freeLongNum(longNum* num) {
    if (!num) return 0;
    if (!num->arr) return 0;
    delete[] num->arr;
    return 0;
}

longNum* sum(longNum* a, longNum* b) {
    longNum* c = new longNum;                               global_counter++;
    c->arr = new int[max(a->length, b->length) + 1];        global_counter += 2;
    int length = 0;                                         global_counter++;
    int tmp = 0;                                            global_counter++;
    int a_ptr, b_ptr, c_ptr;                                global_counter += 3;
    a_ptr = b_ptr = c_ptr = 0;                              global_counter += 3;
                                                            global_counter += 4;
    while (a_ptr < a->length || b_ptr < b->length || tmp) {
                                                           global_counter += 4;
                                                           global_counter++;
        if (a_ptr < a->length) { tmp += a->arr[a_ptr];     global_counter += 2;}
                                                           global_counter++;
        if (b_ptr < b->length) { tmp += b->arr[b_ptr];     global_counter += 2;}
        c->arr[c_ptr] = tmp%10;                            global_counter += 2;
        c_ptr++;                                           global_counter += 2;
        tmp /= 10;                                         global_counter += 2;
                                                           global_counter++;
        if (a_ptr < a->length) {a_ptr++;                   global_counter += 2;}
                                                           global_counter++;
        if (b_ptr < b->length) {b_ptr++;                   global_counter += 2;}
    }
    c->length = c_ptr;                                     global_counter++;
    return c;
}

longNum* stringToLongNum(string s) {
    longNum* result = new longNum;
    result->length = s.length();
    result->arr = new int[s.length()];
    for (int i = 0; i < s.length(); i++) {
        result->arr[s.length() - 1 - i] = (int)s.at(i) - 48;
    }
    return result;
}

void printLR(longNum* num) {
    for (int i = 0; i < num->length; i++) {
        cout << num->arr[i];
    }
    cout << endl;
}

void printRL(longNum* num) {
    int meaningful = 0;
    for (int i = num->length - 1; i >= 0; i--) {
        if (num->arr[i] || meaningful) {
            cout << num->arr[i];
            meaningful = 1;
        }
    }
    if (!meaningful) cout << 0;
    cout << endl;
}

longNum* split(longNum* num) {
    longNum* result = new longNum[2];                                                           global_counter++;
    result[0].length = num->length / 2;                                                         global_counter += 2;
    result[1].length = num->length / 2;                                                         global_counter += 2; 
    result[0].arr = new int[result[0].length];                                                  global_counter++;
    result[1].arr = new int[result[1].length];                                                  global_counter++;
    for (int i = 0; i < num->length / 2; i++) {result[0].arr[i] = num->arr[i];                  global_counter++;}
    for (int i = 0; i < num->length / 2; i++) {result[1].arr[i] = num->arr[num->length / 2 + i]; global_counter += 3;}
    return result;
}

longNum* multiplyElementary(longNum* U, longNum* V) {
    longNum* result = new longNum;                                              global_counter++;
    result->arr = new int[1];                                                   global_counter++;
    result->arr[0] = U->arr[0]*V->arr[0];                                       global_counter += 2;
    result->length = 1;                                                         global_counter++;
    return result;
}

int nearestSize(longNum* a, longNum* b) {
    int max_length = max(a->length, b->length);                                 global_counter++;
    int target_length = pow(2, ceil(log2(max_length)));                         global_counter += 4;
    return target_length;
}

longNum* extendTo(longNum* num, int length) {
                                                                                global_counter++;
    if (num->length == length) return num;
    longNum* result = new longNum;                                              global_counter++;
    result->length = length;                                                    global_counter++;
    result->arr = new int[length];                                              global_counter++;
    for (int i = 0; i < num->length; i++) {result->arr[i] = num->arr[i];        global_counter++;}
    for (int i = num->length; i < length; i++) {result->arr[i] = 0;             global_counter++;}
    return result;
}

longNum* powerize(longNum* num, int power) {
    longNum* result = new longNum;                                              global_counter++;
    result->arr = new int[num->length + power];                                 global_counter += 2;
    for (int i = 0; i < power; i++) {result->arr[i] = 0;                        global_counter++;}
    for (int i = 0; i < num->length; i++) {result->arr[power + i] = num->arr[i]; global_counter += 2;}
    result->length = num->length + power;                                       global_counter += 2;  
    return result;
}

longNum* multiply(longNum* U, longNum* V) {
    int nearest_common_length = nearestSize(U, V);                              global_counter++;
                                                                                global_counter++;
    if (nearest_common_length == 1) return multiplyElementary(U, V);
    U = extendTo(U, nearest_common_length);                                     global_counter++;
    V = extendTo(V, nearest_common_length);                                     global_counter++;
    longNum* U2U1 = split(U);                                                   global_counter++;
    longNum* V2V1 = split(V);                                                   global_counter++;
    
    longNum* U2 = &U2U1[0];                                                     global_counter++;
    longNum* U1 = &U2U1[1];                                                     global_counter++;
    longNum* V2 = &V2V1[0];                                                     global_counter++;
    longNum* V1 = &V2V1[1];                                                     global_counter++;

    longNum* U1V1 = multiply(U1, V1);
    longNum* U2V1 = multiply(U2, V1);
    longNum* U1V2 = multiply(U1, V2);
    longNum* U2V2 = multiply(U2, V2);
    freeLongNum(U1);
    freeLongNum(U2);
    freeLongNum(V1);
    freeLongNum(V2);
    longNum* U1V1Beta = powerize(U1V1, nearest_common_length);
    freeLongNum(U1V1);
    longNum* U2V1BetaHalf = powerize(U2V1, nearest_common_length / 2);
    freeLongNum(U2V1);
    longNum* U1V2BetaHalf = powerize(U1V2, nearest_common_length / 2);
    freeLongNum(U1V2);
    longNum* result1 = sum(U1V1Beta, U2V1BetaHalf);
    freeLongNum(U1V1Beta);
    freeLongNum(U2V1BetaHalf);
    longNum* result2 = sum(U1V2BetaHalf, U2V2);
    freeLongNum(U1V2BetaHalf);
    freeLongNum(U2V2);
    longNum* result = sum(result1, result2);
    freeLongNum(result1);
    freeLongNum(result2);
    return result;
}

longNum* generateLongNum(int length) {
    string s = "";
    for (int i = 0; i < length; i++)
        s.push_back(rand() % 10);
    return stringToLongNum(s);
}

int testDrive(int length) {
    global_counter = 0;
    longNum* num1 = generateLongNum(length);
    longNum* num2 = generateLongNum(length);
    multiply(num1, num2);
    return global_counter;
}

double approx(int n) {
    return 201.807 * n * n + 10.538 * n * log2(n) - 189.807 * n;
}

void getStats(int lower_bound, int upper_bound) {
    for (int i = lower_bound; i <= upper_bound; i += 1) {
        int ops = testDrive(i);
        cout << i << " " << ops << " " << approx(i) << " " << ops / approx(i) << endl;
    }
}




int main() {
    srand(time(0));
    
    getStats(1, 128);

    return 0;
}