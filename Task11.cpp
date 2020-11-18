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

unsigned int findMultInverse(unsigned int number, unsigned int prime) {
    return fastpowmod(number, prime-2, prime);
}

unsigned int getPrimeGreaterThan(int X) {
    int upperLimit = X + (X/10);
    bool* numbers = new bool[upperLimit];
    for (int i = 2; i < upperLimit; i++) {
        numbers[i] = false;
    }
    int s = floor(sqrt(X));
    for (int i = 2; i <= s; i++) {
        if (numbers[i]) 
            continue;
        for (int m = 2; i*m < upperLimit; m++) {
            numbers[i*m] = true;
        }
    }
    for (int i = ((X + upperLimit) / 2); i < upperLimit; i++) {
        if (!numbers[i]) 
            return i;
    }
    return 0;
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

unsigned int makePositiveByModulo(int number, int modulo) {
    if (number < 0) {
        return (unsigned int)(modulo + (number % modulo));
    } else {
        return (unsigned int)number;
    }
}

unsigned int getLagrangeComponent(unsigned int i, vector<secretData> secretDataVector) {
    int topValue = 1;
    int botValue = 1;
    int m = secretDataVector[0].m;
    int modulo = secretDataVector[0].p;
    int excluded = secretDataVector[i-1].i;
    for (int k = 1; k <= m; k++) {
        int secretDataNumber = secretDataVector[k-1].i;
        if (secretDataNumber != excluded) {
            topValue *= -secretDataNumber;
            botValue *= i - secretDataNumber;
        }
    }

    return makePositiveByModulo(topValue, modulo)*findMultInverse(makePositiveByModulo(botValue, modulo), modulo);
}

vector<secretData> encodeSecret(unsigned int m, unsigned int n, unsigned int X) {
    return getSplittedSecretVector(m, n, X);
}

unsigned int decodeSecret(vector<secretData> secretDataVector) {
    unsigned int prime = secretDataVector[0].p;
    unsigned int keepersNeeded = secretDataVector[0].m;
    unsigned int summary = 0;
    for (int keeper = 1; keeper <= keepersNeeded; keeper++) {
        summary += secretDataVector[keeper-1].y * getLagrangeComponent(keeper, secretDataVector);
    }
    return summary % prime;
}

int main(int argc, const char** args) {
    unsigned int m, n, secret;
    cout << "Enter secret number: ";
    cin >> secret;
    cout << "Enter segments count: ";
    cin >> n;
    cout << "Enter segments count to decrypt: ";
    cin >> m;
    vector<secretData> encryptedSecret = encodeSecret(m, n, secret);
    cout << "Segments: " << endl; 
    showSecretDataVector(encryptedSecret);
    cout << "Decoded secret: " << decodeSecret(encryptedSecret) << endl;
    return 0;
}