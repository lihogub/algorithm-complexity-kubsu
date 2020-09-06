#include <stdio.h>
#include <ctime>
#include <random>
#include <chrono>
#include <string>
using namespace std;


int sort_array(int* arr, int size) {
    int actions = 0;
    for (int i = 0; i < size; i++) {
        int ok = 1; actions++;
        for (int j = 0; j < size - 1; j++) {
            actions += 2;
            if (arr[j] > arr[j+1]) {
                int tmp = arr[j]; actions++;
                arr[j] = arr[j+1]; actions += 2;
                arr[j+1] = tmp; actions += 2;
                ok = 0; actions++;
            }
        }
        actions++;
        if (ok) break; 
    }
    return actions;
}


int* create_rand_array(int size) {
    int* arr = new int[size];
    for (int i = 0; i < size; i++) {
        arr[i] = rand() % (size * size);
    }
    return arr;
}


int* create_already_sorted_array(int size) {
    int* arr = new int[size];
    for (int i = 0; i < size; i++) {
        arr[i] = i;
    }
    return arr;
}


int* create_totally_unsorted_array(int size) {
    int* arr = new int[size];
    for (int i = 0; i < size; i++) {
        arr[i] = size - i - 1;
    }
    return arr;
}


int show_array(int* arr, int size) {
    printf("> ");
    for (int i = 0; i < size; i++) 
        printf("%i ", arr[i]);
    printf("\n");
    return 0;
}


int* get_stats(int* arr_gen_f(int), int array_size, int iterations) {
    int *results = new int[3];
    long int actions = 0;
    long int max_actions = 0;
    long int min_actions = INT64_MAX;
    for (int iteration = 0; iteration < iterations; iteration++) {
	int* arr_to_sort = arr_gen_f(array_size);
        int tmp_actions = sort_array(arr_to_sort, array_size);
        max_actions = tmp_actions > max_actions ? tmp_actions : max_actions;
        min_actions = tmp_actions < min_actions ? tmp_actions : min_actions;
        actions += tmp_actions;
	    delete [] arr_to_sort;
    }
    results[0] = min_actions;
    results[1] = actions / iterations;
    results[2] = max_actions;
    return results;
}


int do_tests(int* arr_gen_f(int), const char* out_file_name, int iterations, int arr_size_upper_limit) {
        FILE* file = fopen(out_file_name, "w");
        fprintf(file, "");
        fclose(file);
        for (int size = 2; size <= arr_size_upper_limit; size++) {
            int* stats = get_stats(arr_gen_f, size, iterations);
            file = fopen(out_file_name, "a");
            fprintf(file, "%i %i %i %i\n",size, stats[0], stats[1], stats[2]);
            // printf("%i %i %i %i\n",size, stats[0], stats[1], stats[2]);
            fclose(file);
        }
    return 0;
}


int main() {
    srand(time(0));
    int upper_limit;
    printf("Enter upper limit of arrays: ");
    scanf("%i", &upper_limit);

    int iterations;
    printf("Enter iterations: ");
    scanf("%i", &iterations);

    do_tests(create_already_sorted_array, "min_log.txt", iterations, upper_limit);
    do_tests(create_rand_array, "avg_log.txt", iterations, upper_limit);
    do_tests(create_totally_unsorted_array, "max_log.txt", iterations, upper_limit);

    return 0;
}
