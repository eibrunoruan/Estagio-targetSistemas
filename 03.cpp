#include <iostream>
#include <vector>
#include <fstream>
#include <nlohmann/json.hpp>
#include <tinyxml2.h>

using json = nlohmann::json;
using namespace std;
using namespace tinyxml2;

struct Faturamento {
    int dia;
    double valor;
};

void calcularFaturamento(vector<Faturamento>& faturamentos) {
    double menor = -1, maior = -1, soma = 0;
    int diasComFaturamento = 0, diasAcimaMedia = 0;

    for (int i = 0; i < faturamentos.size(); i++) {
        if (faturamentos[i].valor > 0) {
            if (menor == -1 || faturamentos[i].valor < menor) {
                menor = faturamentos[i].valor;
            }
            if (maior == -1 || faturamentos[i].valor > maior) {
                maior = faturamentos[i].valor;
            }
            soma += faturamentos[i].valor;
            diasComFaturamento++;
        }
    }

    double media = (diasComFaturamento > 0) ? soma / diasComFaturamento : 0;

    for (int i = 0; i < faturamentos.size(); i++) {
        if (faturamentos[i].valor > media) {
            diasAcimaMedia++;
        }
    }

    cout << "Menor faturamento: " << menor << endl;
    cout << "Maior faturamento: " << maior << endl;
    cout << "Dias com faturamento acima da média: " << diasAcimaMedia << endl;
}

vector<Faturamento> carregarFaturamentoJson(string arquivoJson) {
    ifstream arquivo(arquivoJson);
    if (!arquivo.is_open()) {
        cout << "Erro: Não foi possível abrir o arquivo JSON!" << endl;
        return {};
    }

    json dados;
    arquivo >> dados;
    arquivo.close();

    vector<Faturamento> faturamentos;
    for (int i = 0; i < dados.size(); i++) {
        Faturamento f;
        f.dia = dados[i]["dia"];
        f.valor = dados[i]["valor"];
        faturamentos.push_back(f);
    }
    return faturamentos;
}

vector<Faturamento> carregarFaturamentoXml(string arquivoXml) {
    XMLDocument doc;
    if (doc.LoadFile(arquivoXml.c_str()) != XML_SUCCESS) {
        cout << "Erro: Não foi possível abrir o arquivo XML!" << endl;
        return {};
    }
    vector<Faturamento> faturamentos;
    XMLElement* row = doc.FirstChildElement("row");
    while (row) {
        Faturamento f;
        row->FirstChildElement("dia")->QueryIntText(&f.dia);
        row->FirstChildElement("valor")->QueryDoubleText(&f.valor);
        faturamentos.push_back(f);
        row = row->NextSiblingElement("row");
    }

    return faturamentos;
}

int main() {
    string tipoArquivo;
    cout << "Você quer carregar o arquivo JSON ou XML? ";
    cin >> tipoArquivo;

    vector<Faturamento> faturamentos;

    if (tipoArquivo == "json") {
        faturamentos = carregarFaturamentoJson("dados.json");
    } else if (tipoArquivo == "xml") {
        faturamentos = carregarFaturamentoXml("dados.xml");
    } else {
        cout << "Tipo de arquivo desconhecido. Tente 'json' ou 'xml'." << endl;
        return 1;
    }
    if (faturamentos.empty()) {
        cout << "Nenhum dado encontrado!" << endl;
        return 1;
    }
    calcularFaturamento(faturamentos);
}
