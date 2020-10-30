#include <iostream>
using namespace std;
typedef unsigned long long cypher;

bool numbers[1000000] = {0};
int primes[1000000] = {0};
void generatePrimes(int a, int b) {
    for (int i = 2; i < b; i++) {
        for (int m = max(a/i, 2); i*m < b; m++) {
            numbers[i*m] = 1;
        }
    }
    primes[1] = 1;
    int primesPtr = 1;
    for (int i = a; i < b; i++) {
        if (!numbers[i]) {
            primes[primesPtr] = i;
            primesPtr++;
        }
    }

}

cypher pow(cypher text, int k) {
    cypher tmp = text;
    for (int i = 0; i < k; i++) 
        text *= tmp;
    return text;
}

void print(int a, int b) {
    for (int i = a; i < b; i++) {
        cout << i << " " << !numbers[i] << endl;
    }
}

void printPrimes() {
    for (int i = 1; primes[i] != 0; i++) {
        cout << primes[i] << endl;
    }
}

int getPrime(int i) {
    return primes[i];
}


cypher stringToULL(char* s) {
    return *(cypher*)s;
}

int getK(int a, int b) {
    return (a-1)*(b-1);
}

int GCD(int a, int b) {
    return !b ? a : GCD(b , a%b);
}

int getMutualSimpleByModulo(int number, int modulo) {
    for (int i = 2; i < number; i++) {
        if (GCD(number, i) % modulo == 1) return i;
    }
    return -1;
}

int getMutualSimple(int number) {
    for (int i = 2; i < number; i++) {
        if (GCD(number, i) == 1) return i;
    }
    return -1;
}

cypher encrypt(cypher msg, int pub, int k) {
    return pow(msg, pub) % k;
}

cypher decrypt(cypher msg, int close, int k) {
    return pow(msg, close) % k;
}

int main() {
    generatePrimes(1, 1000);
    //printPrimes();
    int a = getPrime(5);
    int b = getPrime(10);

    int k = getK(a, b);
    int pub = getMutualSimple(k);
    int close = getMutualSimpleByModulo(pub, k);
    
    cout << pub << endl;
    cout << close << endl;

/*
    char buf[16] = {0};
    cin >> buf;
    */
    cypher enc = encrypt(0, pub, k);
    cout << enc << endl;
    cout << decrypt(enc, close, k);

    return 0;
}
