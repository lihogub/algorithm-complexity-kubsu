#include <iostream>

#include <ctime>


using namespace std;

/*
n numbers 
divide to two equal sets
*/

int* arr;

int ok;
unsigned long long counter;


void f(int index_c, int n, int left_s, int right_s, int half) {
    counter++;
    if (ok) return;

    counter++;
    if (index_c == n) {
        counter++;
        if (left_s == right_s) {
            ok = 1; 
            counter++;
        }
        return;
    }
    counter += 3;
    if (left_s > half || right_s > half) return;
    f(index_c + 1, n, left_s + arr[index_c], right_s, half);
    f(index_c + 1, n, left_s, right_s + arr[index_c], half);
}

int* getArray(int length) {
    int* result = new int[length];
    for (int i = 0; i < length; i++) {
        result[i] = rand() % 100;
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

int main(int argc, char** args){
    srand(time(0));
    for (int i = 0; i < atoi(args[1]); i++){
        ok = 0;
        counter = 0;
        int n = atoi(args[2]);
        
        arr = getArray(n);
        int s = sum(arr, n);
        //cout << argc << endl;
        f(0, n, 0, 0, s/2);
        
        
        //print(arr, n);
        cout << ok << " " << counter << endl;
    }

    return 0;
}
