#include <ctime>
#include <stdio.h>
#include <random>
using namespace std;


struct node {
    int value;
    node* left = NULL;
    node* right = NULL;
};


void remove_binary_tree(node* node_ptr) {
    if (node_ptr == NULL) return;
    remove_binary_tree(node_ptr->left);
    remove_binary_tree(node_ptr->right);
    delete node_ptr;
}

int insert_to_binary_tree(int value, node* node_ptr) {
    int counter = 0;
    counter++;
    if (node_ptr->value == value) 
        return counter;
    counter++;
    if (node_ptr->value < value) {
        counter++;
        if (node_ptr->left) 
            return counter + insert_to_binary_tree(value, node_ptr->left);
        node_ptr->left = new node; counter++;
        node_ptr->left->value = value; counter++;
        return counter;
    }
    counter++;
    if (node_ptr->right) 
        return counter + insert_to_binary_tree(value, node_ptr->right);
    node_ptr->right = new node; counter++;
    node_ptr->right->value = value; counter++;
    return counter;
}

int* test_rand_tree(int n) {
    node* root = new node;
    root->value = rand();
    int* stats = new int[n];
    stats[0] += 1;

    for (int i = 1; i < n; i++) {
        stats[i] += insert_to_binary_tree(rand(), root);
    }
    remove_binary_tree(root);
    return stats;
}

int* test_ordered_tree(int n) {
    node* root = new node;
    root->value = rand();

    int* stats = new int[n];
    stats[0] = 1;

    for (int i = 1; i < n; i++) {
        stats[i] = insert_to_binary_tree(i+1, root);
    }
    remove_binary_tree(root);
    return stats;
}

void show_arr(int* arr, int n) {
    for (int i = 0; i < n; i++) 
        printf("%i %i\n", i+1, arr[i]);
}


void show_arr(double* arr, int n) {
    for (int i = 0; i < n; i++) 
        printf("%i %f\n", i+1, arr[i]);
}

int max_tree_depth(node* node_ptr) {
    if (node_ptr == NULL) return 0;
    int left_d = max_tree_depth(node_ptr->left);
    int right_d = max_tree_depth(node_ptr->right);
    int max_d = left_d > right_d ? left_d : right_d;
    return max_d > 1 ? max_d : 1;
}

double* test_drive(int n, int iterations) {
    double* total_stats = new double[n];
    fill(total_stats, total_stats+n, 0);
    for (int i = 0; i < iterations; i++) {
        //if ((i+1) % (iterations / 100) == 0) printf("%0.1f%\n", 100.0*(i+1)/iterations);
        int* stats = test_rand_tree(n);
        for (int j = 0; j < n; j++) {
            total_stats[j] += stats[j];
        }
        delete[] stats;
    }
    
    for (int i = 0; i < n; i++) {
        total_stats[i] /= iterations;
    }
    
    return total_stats;
}

int main() {
    srand(time(0));
    int n = 20;
    show_arr(test_drive(n, 1000), n);
    return 0;
}