// ============================================================
// INF101 - Trabalho Sistema Bancario - ETAPA 1 (desafio)
// "Se quisessemos cadastrar ate 5 contas, qual solucao seria possivel?"
// SOLUCAO: usar ARRAYS (vetores) paralelos, um para cada variavel.
// A posicao i de cada array guarda os dados da mesma conta.
// ============================================================
#include <iostream>
#include <string>
#include <limits>
#include <iomanip>
#include <cctype>
using namespace std;

const int MAX_CONTAS = 5;

// Arrays no lugar das variaveis individuais
int    numeroConta[MAX_CONTAS];
string nomeCliente[MAX_CONTAS];
string cpf[MAX_CONTAS];
int    tipoConta[MAX_CONTAS];
double saldo[MAX_CONTAS];
bool   contaAtiva[MAX_CONTAS];
int    qtdContas = 0; // Quantas contas ja foram cadastradas

// Le um inteiro com seguranca (retorna 0 se a entrada for invalida)
int lerInt(const string& msg) {
    int x;
    cout << msg;
    if (!(cin >> x)) {
        cin.clear();
        x = 0;
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return x;
}

// Le um double com seguranca (retorna -1 se a entrada for invalida)
double lerDouble(const string& msg) {
    double x;
    cout << msg;
    if (!(cin >> x)) {
        cin.clear();
        x = -1;
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return x;
}

// Procura uma conta pelo numero; retorna o indice ou -1 se nao achar
int buscarConta(int numero) {
    for (int i = 0; i < qtdContas; i++) {
        if (numeroConta[i] == numero) return i;
    }
    return -1;
}

// Pede o numero da conta e devolve o indice (ou -1 se nao existir)
int selecionarConta() {
    if (qtdContas == 0) {
        cout << "\nNenhuma conta cadastrada.\n";
        return -1;
    }
    int n = lerInt("\nNumero da conta: ");
    int idx = buscarConta(n);
    if (idx == -1) cout << "Conta nao encontrada!\n";
    return idx;
}

void cadastrar() {
    if (qtdContas >= MAX_CONTAS) {
        cout << "\nLimite de " << MAX_CONTAS << " contas atingido!\n";
        return;
    }
    int i = qtdContas; // Proxima posicao livre

    // Numero > 0 e nao repetido
    int n;
    while (true) {
        n = lerInt("\nNumero da conta (maior que zero): ");
        if (n <= 0) cout << "Numero invalido!\n";
        else if (buscarConta(n) != -1) cout << "Ja existe conta com esse numero!\n";
        else break;
    }
    numeroConta[i] = n;

    // Nome
    do {
        cout << "Nome do titular: ";
        getline(cin, nomeCliente[i]);
        if (nomeCliente[i].empty()) cout << "Nome nao pode ser vazio!\n";
    } while (nomeCliente[i].empty());

    // CPF com 11 digitos
    bool ok;
    do {
        cout << "CPF (11 digitos, somente numeros): ";
        getline(cin, cpf[i]);
        ok = (cpf[i].size() == 11);
        for (size_t k = 0; k < cpf[i].size(); k++) {
            if (!isdigit((unsigned char)cpf[i][k])) ok = false;
        }
        if (!ok) cout << "CPF invalido!\n";
    } while (!ok);

    // Tipo 1 ou 2
    do {
        tipoConta[i] = lerInt("Tipo da conta (1 = Corrente, 2 = Poupanca): ");
        if (tipoConta[i] != 1 && tipoConta[i] != 2) cout << "Tipo invalido!\n";
    } while (tipoConta[i] != 1 && tipoConta[i] != 2);

    // Saldo >= 0
    do {
        saldo[i] = lerDouble("Saldo inicial (nao negativo): ");
        if (saldo[i] < 0) cout << "Saldo invalido!\n";
    } while (saldo[i] < 0);

    contaAtiva[i] = true;
    qtdContas++;
    cout << "\nConta cadastrada com sucesso! (" << qtdContas << "/" << MAX_CONTAS << ")\n";
}

void consultar() {
    int i = selecionarConta();
    if (i == -1) return;
    cout << "\n----- DADOS DA CONTA -----\n";
    cout << "Numero : " << numeroConta[i] << endl;
    cout << "Titular: " << nomeCliente[i] << endl;
    cout << "CPF    : " << cpf[i] << endl;
    cout << "Tipo   : " << (tipoConta[i] == 1 ? "Corrente" : "Poupanca") << endl;
    cout << "Saldo  : R$ " << saldo[i] << endl;
    cout << "Status : " << (contaAtiva[i] ? "Ativa" : "Inativa") << endl;
}

void verificarSaldo() {
    int i = selecionarConta();
    if (i == -1) return;
    if (!contaAtiva[i]) {
        cout << "\nConta inativa! Ative a conta para verificar o saldo.\n";
        return;
    }
    cout << "\nSaldo atual: R$ " << saldo[i] << endl;
}

void alterarTipo() {
    int i = selecionarConta();
    if (i == -1) return;
    if (!contaAtiva[i]) {
        cout << "\nConta inativa! Ative a conta para alterar o tipo.\n";
        return;
    }
    int novo = lerInt("Novo tipo (1 = Corrente, 2 = Poupanca): ");
    if (novo == 1 || novo == 2) {
        tipoConta[i] = novo;
        cout << "Tipo alterado com sucesso!\n";
    } else {
        cout << "Tipo invalido! Nada foi alterado.\n";
    }
}

void alternarStatus() {
    int i = selecionarConta();
    if (i == -1) return;
    contaAtiva[i] = !contaAtiva[i];
    cout << "\nConta agora esta " << (contaAtiva[i] ? "ATIVA" : "INATIVA") << ".\n";
}

int main() {
    cout << fixed << setprecision(2);
    int opcao;

    do {
        cout << "\n********************************\n";
        cout << "**        BANCO INF101        **\n";
        cout << "********************************\n";
        cout << "1 - Cadastrar conta\n";
        cout << "2 - Consultar conta\n";
        cout << "3 - Verificar saldo\n";
        cout << "4 - Alterar tipo da conta\n";
        cout << "5 - Ativar/Desativar conta\n";
        cout << "6 - Sair\n";
        opcao = lerInt("Escolha uma opcao: ");

        switch (opcao) {
            case 1: cadastrar();       break;
            case 2: consultar();       break;
            case 3: verificarSaldo();  break;
            case 4: alterarTipo();     break;
            case 5: alternarStatus();  break;
            case 6: cout << "\nEncerrando o sistema. Ate logo!\n"; break;
            default: cout << "\nOpcao invalida! Tente novamente.\n";
        }
    } while (opcao != 6);

    return 0;
}
