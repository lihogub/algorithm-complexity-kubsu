#include <stdio.h>
#include <random>

struct longNumNode{
    int value;
    longNumNode *next = 0;
    longNumNode *prev = 0;
    longNumNode(int val) {
        value = val;
    }
};

struct longNum{
    int length = 0;
    longNumNode* root = 0;
    longNumNode* tail = 0;
    longNum() {}
    longNum(int value) {
        root = new longNumNode(value);
        tail = root;
        length = 1;
    }
};

int max(int a, int b) {
    if (a > b) return a;
    else b;
}

longNum* addCharToRight(longNum* node, int value) {
    node->length++;
    node->tail->next = new longNumNode(value);
    node->tail->next->prev = node->tail;
    node->tail = node->tail->next; 
    return node;
}

longNum* addCharToLeft(longNum* node, int value) {
    node->length++;
    node->root->prev = new longNumNode(value);
    node->root->prev->next = node->root;
    node->root = node->root->prev;
    return node;
}


int char_to_int(char c) {
    return (int)c - 48;
}

void printLR(longNum* num) {
    longNumNode* node = num->root;
    while (node) {
        printf("%i", node->value);
        node = node->next;
    }
    printf("\n");
}

void printRL(longNum* num) {
    longNumNode* node = num->tail;
    while (node) {
        printf("%i", node->value);
        node = node->prev;
    }
    printf("\n");
}

longNum* sum(longNum* a, longNum* b) {
    longNumNode* an = a->root;
    longNumNode* bn = b->root;
    int tmp = 0;
    tmp += an->value;
    tmp += bn->value;
    longNum* c = new longNum(tmp%10);
    tmp /= 10;
    an = an->next;
    bn = bn->next;
    while (an || bn || tmp) {
        if(an) tmp += an->value;
        if(bn) tmp += bn->value;
        addCharToRight(c, tmp%10);
        tmp /= 10;
        if (an) an = an->next;
        if (bn) bn = bn->next;
    }
    return c;
}

longNum* extendToNearestPowerOfTwo(longNum* num) {
    int size = 1;
    while (size < num->length) size *= 2;
    for (int i = num->length; i < size; i++) {
        addCharToRight(num, 0);
    }
    return num;
}

longNum* split(longNum* num) {
    longNum* result = new longNum[2];
    result[0].length = num->length / 2;
    result[1].length = num->length / 2;
    result[0].root = num->root;
    result[1].tail = num->tail;
    longNumNode* tmp;
    tmp = num->root; 
    for (int i = 0; i < num->length / 2 - 1; i++) tmp = tmp->next;
    tmp->next = 0;
    result[0].tail = tmp;
    tmp = num->tail; 
    for (int i = 0; i < num->length / 2 - 1; i++) tmp = tmp->prev;
    tmp->prev = 0;
    result[1].root = tmp;
    return result;
}

void equalizeLength(longNum* a, longNum* b) {
    extendToNearestPowerOfTwo(a);
    extendToNearestPowerOfTwo(b);
    while (a->length != b->length) {
        if (a->length > b->length) {
            addCharToRight(b, 0);
            extendToNearestPowerOfTwo(b);
        }
        else{
            addCharToRight(a, 0);
            extendToNearestPowerOfTwo(a);
        }
    }

}

longNum* multiplyElem(longNum* num, longNum* value) {
    longNumNode* current = num->root;
    int tmp = 0;
    tmp += current->value * value->root->value;
    longNum* result = new longNum(tmp%10);
    tmp /= 10;
    current = current->next;
    while (current || tmp) {
        if (current) tmp += current->value * value->root->value;
        addCharToRight(result, tmp%10);
        tmp /= 10;
        if (current) current = current->next;
    }
    return result;
}

longNum* power_of_ten(int n) {
    longNum* result = new longNum(1);
    for (int i = 0; i < n; i++) addCharToLeft(result, 0);
    return result;
}

longNum* multiply(longNum* U, longNum* V){
    equalizeLength(U, V);
    if (U->length == 1 && V->length == 1) {
        printf("0");
        longNum* result = new longNum(V->root->value*U->root->value % 10);
        addCharToRight(result, V->root->value*U->root->value / 10);
        return result;
    }
    if (U->length > 1 && V->length == 1) {
        printf("1");
        return multiplyElem(U, V);
    }
    if (V->length > 1 && U->length == 1) {
        printf("2");
        return multiplyElem(V, U);
    }
    int current_length = U->length;
    longNum* U_arr = split(U);
    longNum* V_arr = split(V);
    longNum* s = new longNum(0);
    s = sum(s, multiply(multiply(&U_arr[1], &V_arr[1]), power_of_ten(current_length)));
    s = sum(s, multiply(multiply(&U_arr[1], &V_arr[0]), power_of_ten(current_length/2)));
    s = sum(s, multiply(multiply(&U_arr[0], &V_arr[1]), power_of_ten(current_length/2)));
    s = sum(s, multiply(&U_arr[0], &V_arr[0]));
    return s;
}



int main() {
    longNum* num1 = new longNum(6);
    for (int i = 1; i < 6; i++) addCharToRight(num1, i%10);

    longNum* num2 = new longNum(6);
    for (int i = 1; i < 3; i++) addCharToRight(num2, i%10);

    printLR(num1);
    printLR(num2);
    printLR(multiply(num1, num2));
    return 0;
 }