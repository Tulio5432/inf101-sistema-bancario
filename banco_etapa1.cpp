// ============================================================
// INF101 - Programacao de Computadores I
// Trabalho: Sistema de Registro e Gestao de Contas Bancarias
// ETAPA 1 - Uma conta, usando somente variaveis individuais
// ============================================================
#include <iostream>
#include <string>
#include <limits>
#include <iomanip>
#include <cctype>
using namespace std;

int main() {
    // ---------- Variaveis obrigatorias ----------
    int numeroConta = 0;       // Numero da conta
    string nomeCliente = "";   // Nome do titular
    string cpf = "";           // CPF do titular
    int tipoConta = 0;         // 1 = Corrente; 2 = Poupanca
    double saldo = 0.0;        // Saldo atual
    bool contaAtiva = false;   // Indica se a conta esta ativa

    // ---------- Variaveis extras ----------
    bool contaCadastrada = false; // Indica se ja existe conta cadastrada
    string telefone = "";         // Campo extra no cadastro (teste)
    int opcao = 0;                // Opcao escolhida no menu

    cout << fixed << setprecision(2); // Mostra saldo com 2 casas decimais

    do {
        // ---------- Menu ----------
        cout << "\n********************************\n";
        cout << "**        BANCO INF101        **\n";
        cout << "********************************\n";
        cout << "1 - Cadastrar conta\n";
        cout << "2 - Consultar conta\n";
        cout << "3 - Verificar saldo\n";
        cout << "4 - Alterar tipo da conta\n";
        cout << "5 - Ativar/Desativar conta\n";
        cout << "6 - Sair\n";
        cout << "Escolha uma opcao: ";

        // Le a opcao; se digitar letra, trata como opcao invalida (0)
        if (!(cin >> opcao)) {
            cin.clear();
            opcao = 0;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (opcao) {

        // ---------------- 1 - CADASTRAR ----------------
        case 1: {
            if (contaCadastrada) {
                cout << "\nJa existe uma conta cadastrada (esta etapa suporta apenas 1).\n";
                break;
            }

            // Numero da conta > 0
            do {
                cout << "\nNumero da conta (maior que zero): ";
                if (!(cin >> numeroConta)) {
                    cin.clear();
                    numeroConta = 0;
                }
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                if (numeroConta <= 0) cout << "Numero invalido!\n";
            } while (numeroConta <= 0);

            // Nome do titular (nao pode ficar vazio)
            do {
                cout << "Nome do titular: ";
                getline(cin, nomeCliente);
                if (nomeCliente.empty()) cout << "Nome nao pode ser vazio!\n";
            } while (nomeCliente.empty());

            // CPF: 11 digitos numericos
            bool cpfValido;
            do {
                cout << "CPF (11 digitos, somente numeros): ";
                getline(cin, cpf);
                cpfValido = (cpf.size() == 11);
                for (size_t i = 0; i < cpf.size(); i++) {
                    if (!isdigit((unsigned char)cpf[i])) cpfValido = false;
                }
                if (!cpfValido) cout << "CPF invalido!\n";
            } while (!cpfValido);

            // Tipo da conta: 1 ou 2
            do {
                cout << "Tipo da conta (1 = Corrente, 2 = Poupanca): ";
                if (!(cin >> tipoConta)) {
                    cin.clear();
                    tipoConta = 0;
                }
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                if (tipoConta != 1 && tipoConta != 2) cout << "Tipo invalido!\n";
            } while (tipoConta != 1 && tipoConta != 2);

            // Saldo inicial >= 0
            do {
                cout << "Saldo inicial (nao negativo): ";
                if (!(cin >> saldo)) {
                    cin.clear();
                    saldo = -1;
                }
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                if (saldo < 0) cout << "Saldo invalido!\n";
            } while (saldo < 0);

            // Campo extra (opcional)
            cout << "Telefone (opcional, Enter para pular): ";
            getline(cin, telefone);

            contaAtiva = true;       // Toda conta nova nasce ativa
            contaCadastrada = true;
            cout << "\nConta cadastrada com sucesso!\n";
            break;
        }

        // ---------------- 2 - CONSULTAR ----------------
        case 2:
            if (!contaCadastrada) {
                cout << "\nNenhuma conta cadastrada.\n";
            } else {
                cout << "\n----- DADOS DA CONTA -----\n";
                cout << "Numero : " << numeroConta << endl;
                cout << "Titular: " << nomeCliente << endl;
                cout << "CPF    : " << cpf << endl;
                cout << "Tipo   : " << (tipoConta == 1 ? "Corrente" : "Poupanca") << endl;
                cout << "Saldo  : R$ " << saldo << endl;
                cout << "Status : " << (contaAtiva ? "Ativa" : "Inativa") << endl;
                if (!telefone.empty()) cout << "Telefone: " << telefone << endl;
            }
            break;

        // ---------------- 3 - VERIFICAR SALDO ----------------
        case 3:
            if (!contaCadastrada) {
                cout << "\nNenhuma conta cadastrada.\n";
            } else if (!contaAtiva) {
                cout << "\nConta inativa! Ative a conta para verificar o saldo.\n";
            } else {
                cout << "\nSaldo atual: R$ " << saldo << endl;
            }
            break;

        // ---------------- 4 - ALTERAR TIPO ----------------
        case 4:
            if (!contaCadastrada) {
                cout << "\nNenhuma conta cadastrada.\n";
            } else if (!contaAtiva) {
                cout << "\nConta inativa! Ative a conta para alterar o tipo.\n";
            } else {
                int novoTipo;
                cout << "\nTipo atual: " << (tipoConta == 1 ? "Corrente" : "Poupanca") << endl;
                cout << "Novo tipo (1 = Corrente, 2 = Poupanca): ";
                if (!(cin >> novoTipo)) {
                    cin.clear();
                    novoTipo = 0;
                }
                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                if (novoTipo == 1 || novoTipo == 2) {
                    tipoConta = novoTipo;
                    cout << "Tipo alterado com sucesso!\n";
                } else {
                    cout << "Tipo invalido! Nada foi alterado.\n";
                }
            }
            break;

        // ---------------- 5 - ATIVAR/DESATIVAR ----------------
        case 5:
            if (!contaCadastrada) {
                cout << "\nNenhuma conta cadastrada.\n";
            } else {
                contaAtiva = !contaAtiva; // Inverte o estado
                cout << "\nConta agora esta " << (contaAtiva ? "ATIVA" : "INATIVA") << ".\n";
            }
            break;

        // ---------------- 6 - SAIR ----------------
        case 6:
            cout << "\nEncerrando o sistema. Ate logo!\n";
            break;

        default:
            cout << "\nOpcao invalida! Tente novamente.\n";
        }

    } while (opcao != 6);

    return 0;
}
