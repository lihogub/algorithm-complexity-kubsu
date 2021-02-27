#include <iostream>
#include <math.h>
#include <vector>
using namespace std;
typedef u_int64_t ULL;
typedef int64_t LL;


bool numbers[1000000] = {0};
int primes[1000000] = {0};

void generatePrimes(int a, int b) {
    for (int i = 2; i < b; i++) {
        for (int m = max(a/i, 2); m*i < b; m++) {
            numbers[m*i] = 1;
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

ULL getPrime(int i) {
    return primes[i];
}


ULL stringToULL(char* s) {
    return *(ULL*)s;
}

ULL GCD(ULL a, ULL b) {
    return !b ? a : GCD(b , a%b);
}

ULL getK(ULL a, ULL b) {
    return (a-1)*(b-1);
}
ULL fastModExp(ULL a, ULL k, ULL modulus) {
    ULL result = 1;
    ULL temp;
    if (k > 0) { 
        if ((k % 2) == 0) {
            temp = fastModExp(a,k/2,modulus);
            result = (temp * temp) % modulus;
        }
        else {
            temp = fastModExp(a,k-1,modulus);
            result = (a * temp) % modulus;
        }
    }
    return result;
}

ULL getN(ULL a, ULL b) {
    return a*b;
}

ULL getPublicKey(ULL k) {
    for (ULL publicKey = 2; publicKey < k; publicKey++)
        if (GCD(publicKey, k) == 1) 
            return publicKey;
    return 0;
}

LL getPrivateKey(LL publicKey, LL k) {
	if (publicKey == 1) return 1;
	return (1 - getPrivateKey(k % publicKey, publicKey) * k) / publicKey + k;
}

ULL encrypt(ULL plainText, ULL openKey, int n) {
    return fastModExp(plainText, openKey, n);
}

ULL decrypt(ULL cypherText, ULL closeKey, int n) {
    return fastModExp(cypherText, closeKey, n);
}


int main() {

    generatePrimes(46250, 56000);
    //printPrimes();


    ULL a = getPrime(1);
    ULL b = getPrime(5);
    ULL n = getN(a, b);
    ULL k = getK(a, b);
    ULL open = 65537;
    //ULL open = getPublicKey(k);
    ULL close = getPrivateKey(open, k);

    cout << "a " << a << endl;
    cout << "b " << b << endl;
    cout << "n " << n << endl;
    cout << "k " << k << endl;
    cout << "open " << open << endl;
    cout << "close " << close << endl;

    
    //ULL plainText = stringToULL((char*)buf);
   
    ULL plainText = 1073741824;
    cout << "plaintext: " << plainText << endl;
    
    ULL cypherText = encrypt(plainText, open, n);
    cout << "cyphertext: " << cypherText << endl;
    plainText = decrypt(cypherText, close, n);
    cout << "plaintext: " << plainText << endl;



    //cout << fastPow(545, 503, 943) << endl;



    return 0;
}
