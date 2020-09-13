#include <iostream>
#include <stdio.h>

int carry(int n, int a, int b, int c) {
	int counter = 0;                             // обнуляем счетчик
	counter++;                                   // учитываем сравнение
	if (n == 1) {
		//printf("%i -> %i\n", a, b); 
		counter++;                               // учитываем перекладывание
		counter++;                               // учитываем return
		return counter;
	}
	counter += 1 + 1 + carry(n - 1, a, c, b);    // учитываем вычитание, вызов функции и значение функции
	//printf("%i -> %i\n", a, b); 
	counter++;                                   // учитываем перекладывание
	counter += 1 + 1 +  carry(n - 1, c, b, a);   // учитываем вычитание, вызов функции и значение функции
	counter++;                                   // учитываем return
	return counter;
}

int main() {
    /* выводим кол-во операций для разного кол-ва колец башни*/
	for (int size = 1; size <= 20; size++)
		printf("%i %i \n", size, carry(size, 1, 2, 3));
	return 0;
}
