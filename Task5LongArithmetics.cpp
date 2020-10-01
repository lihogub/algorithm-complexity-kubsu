#include <iostream>

struct number {
    int value;
    number* next = 0;
};

number* add_number_to_list(number* vertice, int value) {
    if (!vertice) {
        number* vertice = new number;
        vertice->value = value;
        return vertice;
    }
    if (!vertice->next) {
        number* new_vertice = new number;
        new_vertice->value = value;
        vertice->next = new_vertice;
        return vertice;
    }
    add_number_to_list(vertice->next, value);
    return vertice;
}

int char_to_int(char c) {
    return (int)c - 48;
}

void output(number* v) {
    if (!v) {
        std::cout << std::endl;
        return;
    }
    std::cout << v->value;
    output(v->next);
}

number* char_to_number_list(char* input_str) {
    number* root = add_number_to_list(0, char_to_int(input_str[0]));
    int i = 1;
    while (input_str[i] != '\0') {
        add_number_to_list(root, char_to_int(input_str[i]));
        i++;
    }
    return root;
}

number* sum_numbers(number* a, number* b) {
    number* root = 0;
    int tmp = 0;
    while (a || b || tmp > 0) {
        if (a) tmp += a->value;
        if (b) tmp += b->value;
        if (!root){
            root = new number;
            root->value = tmp % 10;
            tmp /= 10; 
        }
        else {
            add_number_to_list(root, tmp % 10);
            tmp /= 10;
        }
        if (a) a = a->next;
        if (b) b = b->next;
    }
    return root;
}

number* split(number* )

int main() {
    char long_num[100];
    std::cin >> long_num;
    number* num1 = char_to_number_list(long_num);
    std::cin >> long_num;
    number* num2 = char_to_number_list(long_num);

    output(sum_numbers(num1, num2));


    return 0;
}