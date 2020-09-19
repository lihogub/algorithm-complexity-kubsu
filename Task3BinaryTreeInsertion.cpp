#include <stdio.h>
#include <random>
#include <ctime>

struct node {
    int value;
    node* left = NULL;
    node* right = NULL;
};

int* sum(int* arr1, int* arr2, int n) {
    for (int i = 0; i < n; i++) {
        arr1[i] += arr2[i];
    }
    delete[] arr2;
    return arr1;
}

double* divide(int* arr, int n, int divisor) {
    double* result = new double[n];
    for (int i = 0; i < n; i++) {
        result[i] = 1.0 * arr[i] / divisor;
    }
    delete[] arr;
    return result;
}

void remove_tree(node* tree) {
    if (tree == NULL) return;
    remove_tree(tree->left);
    remove_tree(tree->right);
    delete tree;
}

int add_to_tree(node* tree, int value) {
    int counter = 0;
    counter++;
    if (tree->value == value) return counter;
    counter++;
    if (tree->value > value) {
        counter++;
        if (tree->right) return counter + add_to_tree(tree->right, value);
        tree->right = new node; counter++;
        tree->right->value = value; counter++;
        return counter;
    }
    if (tree->left) return counter + add_to_tree(tree->left, value);
    tree->left = new node; counter++;
    tree->left->value = value; counter++;
    return counter;
}

int* make_test(int n) {
    int* stats = new int[n];
    node* root = new node;
    root->value = rand();
    stats[0] = 2;
    for (int i = 1; i < n; i++) {
        stats[i] = add_to_tree(root, rand());
    }
    remove_tree(root);
    return stats;
}

int* get_summary(int n, int iterations) {
    int* stats = new int[n];
    std::fill(stats, stats + n, 0);
    for (int i = 0; i < iterations; i++) {
        if (i % (iterations / 100) == 0) printf("%0.1f%\n", (100.0 * i / iterations));
        stats = sum(stats, make_test(n), n);
    }
    return stats;
}

double* get_avg_stats(int n, int iterations) {
    return divide(get_summary(n, iterations), n, iterations);
}

void show_arr(int* arr, int n) {
    for (int i = 0; i < n; i++) {
        printf("%i %i\n", (i+1), arr[i]);
    }
}

void show_arr(double* arr, int n) {
    for (int i = 0; i < n; i++) {
        printf("%i %f\n", (i+1), arr[i]);
    }
    delete[] arr;
}

void compare(double* arr, int n, double f (int n)) {
    for (int i = 0; i < n; i++) {
        printf("%i %f %f %f\n", (i+1), arr[i], f(i+1), arr[i]/f(i+1));
    }
    delete[] arr;
}

double approx_function(int n) {
    return 2.74079*log2(n) + 0.06016*n + 1.93983;
}

int main() {
    int n = 20;
    compare(get_avg_stats(n, 10000000), n, approx_function);
    return 0;
}
