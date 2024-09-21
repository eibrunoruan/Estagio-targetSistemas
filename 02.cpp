#include <iostream>
#include <locale>
using namespace std;

void calculaFibonacci (int tamanho) {
    int n1 = 0, n2 = 1;
    bool pertence = false;

    cout << n1 << " " << n2 << " ";

    for (int i = 2; i <= tamanho; i++) {
        int aux = n1 + n2;
        cout << aux << " ";

        if (aux == tamanho) {
            pertence = true;
        }
        n1 = n2;
        n2 = aux;
    }
    if (pertence || tamanho == 0 || tamanho == 1) {
        cout << "Tamanho (" << tamanho << ") pertence a Fibonacci." << endl;
    } else {
        cout << "Tamanho (" << tamanho << ") não pertence a Fibonacci." << endl;
    }
}

int main() {
    setlocale(LC_ALL, "Portuguese");
    int tamanho = 20;

    calculaFibonacci(tamanho);
}