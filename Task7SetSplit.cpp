#include <iostream>
#include <ctime>
#include <math.h>

using namespace std;

bool* bitmap;
int* arr;
bool isFound;
int counter;

int* getArray(int length) {
    int* result = new int[length];
    for (int i = 0; i < length; i++) {
        result[i] = rand() % 999 + 1;
    }
    return result;
}

int sum(int* arr, int length) {
    int s = 0;
    for (int i = 0; i < length; i++) {
        s += arr[i];
    }
    return s;
}

void print(int* arr, int length) {
    for (int i = 0; i < length; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

void print(bool* arr, int length) {
    for (int i = 0; i < length; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

void f(int index, int n, int summary, int half) {
    
    counter++;
    if (isFound) return;

    counter++;
    if (summary > half) return;
    
    counter++;
    if (summary == half) {
        counter++;
        isFound = true;
        return;
    }

    counter++;
    if (index == n) return;

    //bitmap[index + 1] = true;
    counter += 3;
    f(index+1, n, summary + arr[index+1], half);
        
    //bitmap[index + 1] = false;
    counter += 3;
    f(index+1, n, summary, half);
}

void printHeaps(bool* b, int length) {
    int l_sum = 0;
    for (int i = 0; i < length; i++) {
        if (b[i]) {
            cout << arr[i] << " ";
            l_sum += arr[i];
        }
    }
    cout << " -> " << l_sum << endl;
    int r_sum = 0;
    for (int i = 0; i < length; i++) {
        if (!b[i]) {
            cout << arr[i] << " ";
            r_sum += arr[i];
        }
    }
    cout << " -> " << r_sum << endl;
}

void nullify(bool* arr, int length) {
    for (int i = 0; i < length; i++) {
        arr[i] = false;
    }
}

void testDrive(int arrLength, int iterations) {
    int min_ops = INT16_MAX;
    int max_ops = -1;
    int impossible_c = 0;
    double sum_ops = 0;
    for (int i = 0; i < iterations; i++) {
        arr = getArray(arrLength);
        isFound = false;
        counter = 0;

        int s = sum(arr, arrLength);
        if (s%2) {arr[0]++; s++;}
        
        f(-1, arrLength, 0, s/2);
        delete[] arr;
        min_ops = min(min_ops, counter);
        max_ops = max(max_ops, counter);
        sum_ops += counter;
    }

    cout << min_ops << " " << sum_ops / iterations << " " << max_ops << " " << endl;
    FILE* file = fopen("stats.json", "a");
    fprintf(file, "[%i, %i, %f, %i],",arrLength, min_ops, 1.0*sum_ops / iterations, max_ops);
    fclose(file);
}


int main(int argc, char** args){
    srand(time(0));
    int iterations = atoi(args[1]);
    int arrLengthFrom = atoi(args[2]);
    int arrLengthTo = atoi(args[3]);
    /*
    FILE* file = fopen("stats.json", "w");
    fprintf(file, "");
    fclose(file);
    */
    for (int i = arrLengthFrom; i <= arrLengthTo; i++) {
        cout << i << " ";
        testDrive(i, iterations);
    }
    return 0;
}


