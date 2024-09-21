#include <iostream>
using namespace std;

int main() {
    char palavra[50] = {"TargetSistemas"};
    int tamanho;
    
    while(palavra[tamanho] != '\0') {
        tamanho++;
    }
    for(int i = tamanho;i >= 0; i--) {
        cout << palavra[i];
    }
}
