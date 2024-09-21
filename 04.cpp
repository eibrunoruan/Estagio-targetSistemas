#include <iostream>
#include <string>
using namespace std;

int main() {
    string estados[] = {"SP", "RJ", "MG", "ES", "Outros"};
    double faturamento[] = {67836.43, 36678.66, 29229.88, 27165.48, 19849.53};
    double percentual, total = 0;

    for (int i = 0; i < 5; i++) {
        total += faturamento[i];
    }

    cout << "Percentual por estado:" << endl;
    for (int i = 0; i < 5; i++) {
        percentual = (faturamento[i] / total) * 100;
        percentual = (int)(percentual * 100 + 0.5) / 100.0;
        cout << estados[i] << ": " << percentual << "%" << endl;
    }

    return 0;
}
