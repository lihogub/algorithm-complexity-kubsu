#include <iostream>
using namespace std;


int fastpow(int a, int x) {
    int counter = 0;

    int result = 1; counter++;
    int tmp = a; counter++;
    counter++;
    while (x != 0) {
        counter += 2;
        if (x % 2 == 1) {
            result *= tmp; counter += 2;
        }
        tmp *= tmp; counter += 2;
        x /= 2; counter += 2;
        counter++;
    }
    return counter;
}

int fakefastpow(int x) {
    int counter = 0;
    counter++; // int result = 1;
    counter++; // int tmp = a;
    counter++;
    while (x != 0) {
        counter += 2;
        if (x % 2 == 1) {
            counter += 2; // result *= tmp; 
        }
        counter += 2; // tmp *= tmp; 
        x /= 2; counter += 2;
        counter++; //its fow next while
    }
    return counter;
}

unsigned long long getSummary(int n) {
    unsigned long long summary = 0;
    int upper_bound = (1 << (n + 1)) - 1;
    for (int i = 1 << n; i <= upper_bound; i++) {
        //cout << i << endl;
        unsigned long long tmp = fakefastpow(i);
        summary += tmp;
    }
    return summary;
}

long double getAvg(int n) {
    long double summary = getSummary(n);
    return summary / ((1 << (n + 1)) - (1 << n));
}

int main(int argc, char** argv) {
    //int a = atoi(argv[1]);
    //int x = atoi(argv[2]);
    for (int i = 1; i < 30; i++)
        cout << getAvg(i) << endl;


    return 0;
}
