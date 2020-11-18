#include <iostream>
#include <random>
#include <vector>
using namespace std;

struct secretData {
    unsigned int p;
    unsigned int m;
    unsigned int i;
    unsigned int y;
    void print() {
        cout << i << " " << y << endl;
    };
};


unsigned int fastpowmod(unsigned int a, unsigned int n, unsigned int m) {
    unsigned int result = 1;
    unsigned int tmp = a;
    while (n > 0) {
        if (n%2) {
            result *= tmp;
            result %= m;
        }
        tmp *= tmp;
        tmp %= m;
        n /= 2;
    }
    return result;
}

unsigned int getPrimeGreaterThan(int X) {
    return 1213;
}

unsigned int* getPolinomeCoefsArray(unsigned int m, unsigned int p, unsigned int X) {
    unsigned int* coefsArray = new unsigned int[m];
    coefsArray[0] = X;
    for (int i = 1; i < m; i++) {
        coefsArray[i] = rand() % p;
    }
    return coefsArray;
}

unsigned int calcPolinomeByModulo(unsigned int x, unsigned int modulo, unsigned int polinomeSize, unsigned int* coefsArray) {
    unsigned int result = 0;
    for (int i = 0; i < polinomeSize; i++) {
        result += coefsArray[i]*fastpowmod(x, i, modulo) % modulo;
        result %= modulo;
    }
    return result;
}

vector<secretData> getSplittedSecretVector(unsigned int m, unsigned int n, unsigned int X) {
    vector<secretData> result;
    unsigned int prime;
    prime = getPrimeGreaterThan(X);
    unsigned int* coefsArray = getPolinomeCoefsArray(m, prime, X);
    for (int i = 1; i <= n; i++) {
        secretData secretSegment;
        secretSegment.p = prime;
        secretSegment.m = m;
        secretSegment.i = i;
        secretSegment.y = calcPolinomeByModulo(i, prime, m, coefsArray);
        result.push_back(secretSegment);
    }
    return result;
}

void showSecretDataVector(vector<secretData> secretDataVector) {
    for (auto item : secretDataVector) {
        item.print();
    }
}

void showPolinome(unsigned int* coefsArray, unsigned int size) {
    for (int i = 0; i < size; i++) {
        cout << coefsArray[i] << " ";
    }
    cout << endl;
}

int main(int argc, const char** args) {

    unsigned int arg1 = atoi(args[1]);
    unsigned int arg2 = atoi(args[2]);
    unsigned int arg3 = atoi(args[3]);
    cout << fastpowmod(arg1, arg2, arg3) << endl;
/*
    vector<secretData> secretDataVector = getSplittedSecretVector(2, 10, 555);
    showSecretDataVector(secretDataVector);
*/
    return 0;
}