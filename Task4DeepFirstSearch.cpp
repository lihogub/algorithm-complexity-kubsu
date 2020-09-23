#include <random>
#include <ctime>

int* make_random_graph(int size) {
    int* graph = new int[size*size];
    for (int i = 0; i < size; i++) 
        for (int j = 0; j < size; j++) {
            if (i != j) {
                int tmp = rand() % 2;
                graph[i*size + j] = tmp;
                graph[j*size + i] = tmp;
            }
            else graph[i*size + i] = 0;
        }
    return graph; 
}


int sum_arr(int* arr, int size) {
    int S = 0;
    for (int i = 0; i < size; i++) {
        S += arr[i];
    }
    return S;
}

int goFrom(int source_vertice, int vertice_count, int* graph, int* passed_vertices, int verbose);

int test_connection(int* graph, int size) {
    int* passed_vertices = new int[size];
    std::fill(passed_vertices, passed_vertices + size, 0);
    goFrom(0, size, graph, passed_vertices, 0);
    if (sum_arr(passed_vertices, size) == size) {
        delete[] passed_vertices;
        return 1;
    }
    delete[] passed_vertices;
    return 0;
}

int* make_random_connected_graph(int size) {
    int* graph = make_random_graph(size);
    while (!test_connection(graph, size)) {
        delete[] graph;
        graph = make_random_graph(size);
    }
    return graph;
}

int goFrom(int source_vertice, int vertice_count, int* graph, int* passed_vertices, int verbose) {
    int counter = 0;
    counter++;
    passed_vertices[source_vertice] = 1; 
    for (int i = 0; i < vertice_count; i++) {
        counter += 4;
        if ((!passed_vertices[i]) && graph[source_vertice*vertice_count + i]) {
        if (verbose) printf("%i %i\n", source_vertice, i);
        counter += goFrom(i, vertice_count, graph, passed_vertices, verbose);
        }      
    }
    return counter;
}

int test_drive(int size) {
    int* graph = make_random_connected_graph(size);
    int* passed_vertices = new int[size];
    std::fill(passed_vertices, passed_vertices+size, 0);
    int operations = goFrom(0, size, graph, passed_vertices, 1);
    delete[] graph;
    delete[] passed_vertices;
    return operations;
}

int main() {
    srand(time(0));
    printf("%i\n", test_drive(10000));
    

    return 0;
}