#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include <conio.h>
#include <cassert>

using namespace std;

typedef struct{
    int hora;
    int minuto;
    int segundo;
} Hora;

typedef struct{
    int dia;
    int mes;
    int ano;
} Data;

typedef struct{
    string causaDaMorte;
    Data dataDaMorte;
    Hora horaDaMorte;
} Relatorio;

typedef struct{
    string nome;
    int idade;
    int id;
    Relatorio relatorio;
} Morto;

void clearScreen();
void tentativaAcesso();
bool login(int tentativasRestantes);
int crudMenu();
void criar(Morto* mortos, int*& contabilidadeMortuaria);
void ver(Morto* mortos, int*& contabilidadeMortuaria);
void modificar(Morto* mortos, int*& contabilidadeMortuaria);
void excluir(Morto* mortos, int*& contabilidadeMortuaria);
bool gerenciamento(int escolhaMenu, Morto* mortos, bool statusMenu, int*& contabilidadeMortuaria);
void ordenarPorId(Morto* mortos, int*& contabilidadeMortuaria);

void clearScreen(){
    system("cls");
}

void tentativaAcesso(){ //mensagem de tentativa de acesso
    string texto = "Tentativa de acesso ao sistema";

    for (char c : texto) {
        cout << c << flush;

        this_thread::sleep_for(chrono::milliseconds(50)); 
    }

    cout << endl;
}

bool login(int tentativasRestantes){ //usuario e senha
    string usuario, senha;
    string usuarioCorreto = "matt", senhaCorreta = "cenora";
    
    cout << "Digite seu usuario: ";
    cin >> usuario;

    cout << "Digite sua senha: ";
    cin >> senha;

    clearScreen();

    if(usuario == usuarioCorreto && senha == senhaCorreta){
        cout << "Acesso ao sistema liberado!" << endl;
        cout << "Pressione Enter para acessar o menu...";

        cin.get();
        
        return true;
    }
    else{
        cout << "Login falhou. Tentativas restantes: " << tentativasRestantes - 1 << endl;
        
        if(tentativasRestantes > 1){
            return login(tentativasRestantes - 1);
        } 
        else{
            cout << "Limite de tentativas atingido. Tente novamente mais tarde." << endl;
            return false;
        }
    }
}

int crudMenu(){ //menu de gerenciamento
    int keyStatus = 1;
    bool menuStatus = true;
    string textMenu;

    while(menuStatus){
        clearScreen();
        
        textMenu = "Qual o medo abundante de todas as verdades?\n";
        textMenu = textMenu + (keyStatus == 1 ? "> " : "  ") + "1. Criacao\n";
        textMenu = textMenu + (keyStatus == 2 ? "> " : "  ") + "2. Analise\n";
        textMenu = textMenu + (keyStatus == 3 ? "> " : "  ") + "3. Modificacao\n";
        textMenu = textMenu + (keyStatus == 4 ? "> " : "  ") + "4. Ressurreicao\n";
        textMenu = textMenu + (keyStatus == 5 ? "> " : "  ") + "5. Log Off\n";

        cout << textMenu;

        int key = _getch();

        switch(key){
            case 13: // Enter
                if(keyStatus == 5){
                    menuStatus = false;
                    return 5;
                }
                else{
                    return keyStatus;
                }
                break;
            case 72: // Seta para cima
                if (keyStatus > 1) {
                    keyStatus--;
                }
                break;
            case 80: // Seta para baixo
                if (keyStatus < 5) {
                    keyStatus++;
                }
                break;
            default:
                break;
        }
    }
    
    return 0;
}

void criar(Morto* mortos, int*& contabilidadeMortuaria){
    clearScreen();
    
    cout << "Adicione os dados do contribuinte:\n";
    
    cout << "Nome: ";
    getline(cin, mortos[*contabilidadeMortuaria].nome);
    
    cout << "Idade: ";
    cin >> mortos[*contabilidadeMortuaria].idade;
    
    cout << "ID: ";
    cin >> mortos[*contabilidadeMortuaria].id;
    
    cout << "Causa da morte: ";
    cin.ignore();
    getline(cin, mortos[*contabilidadeMortuaria].relatorio.causaDaMorte);
    
    cout << "Data da morte (dia / mes / ano): ";
    cin >> mortos[*contabilidadeMortuaria].relatorio.dataDaMorte.dia >> mortos[*contabilidadeMortuaria].relatorio.dataDaMorte.mes >> mortos[*contabilidadeMortuaria].relatorio.dataDaMorte.ano;
    
    cout << "Hora da morte (hora : minuto : segundo): ";
    cin >> mortos[*contabilidadeMortuaria].relatorio.horaDaMorte.hora >> mortos[*contabilidadeMortuaria].relatorio.horaDaMorte.minuto >> mortos[*contabilidadeMortuaria].relatorio.horaDaMorte.segundo;

    (*contabilidadeMortuaria)++; // Incrementa a quantidade de mortos
    
    cout << "\nMorto criado com sucesso!\n";
    cin.ignore();
    
    cout << "Pressione Enter para voltar ao menu...";
    cin.get();
}

void ver(Morto* mortos, int*& contabilidadeMortuaria){
    clearScreen();
    
    cout << "Mortos registrados: " << endl;
    
    for(int i = 0; i < *contabilidadeMortuaria; i++){
        cout << "Morto " << i + 1 << ":\n";
        cout << "Nome: " << mortos[i].nome << endl;
        cout << "Idade: " << mortos[i].idade << endl;
        cout << "ID: " << mortos[i].id << endl;
        cout << "Relatorio de Morte:\n";
        cout << "   Causa: " << mortos[i].relatorio.causaDaMorte << endl;
        cout << "   Data: " << mortos[i].relatorio.dataDaMorte.dia << "/" << mortos[i].relatorio.dataDaMorte.mes << "/" << mortos[i].relatorio.dataDaMorte.ano << endl;
        cout << "   Hora: " << mortos[i].relatorio.horaDaMorte.hora << ":" << mortos[i].relatorio.horaDaMorte.minuto << ":" << mortos[i].relatorio.horaDaMorte.segundo << endl;
        cout << endl;  
    }

    int escolha;
    cout << "Desejas uma ordenacao, senhor? (Aperte 1)" << endl;
    cin >> escolha;

    if(escolha == 1){
        ordenarPorId(mortos, contabilidadeMortuaria);

        cout << "Mortos ordenados por ID: " << endl << endl;
        
        for(int i = 0; i < *contabilidadeMortuaria; i++){
            cout << "Morto " << i + 1 << ":\n";
            cout << "Nome: " << mortos[i].nome << endl;
            cout << "Idade: " << mortos[i].idade << endl;
            cout << "ID: " << mortos[i].id << endl;
            cout << "Relatorio de Morte:\n";
            cout << "   Causa: " << mortos[i].relatorio.causaDaMorte << endl;
            cout << "   Data: " << mortos[i].relatorio.dataDaMorte.dia << "/" << mortos[i].relatorio.dataDaMorte.mes << "/" << mortos[i].relatorio.dataDaMorte.ano << endl;
            cout << "   Hora: " << mortos[i].relatorio.horaDaMorte.hora << ":" << mortos[i].relatorio.horaDaMorte.minuto << ":" << mortos[i].relatorio.horaDaMorte.segundo << endl;
            cout << endl;  
        }
        
        cout << "Pressione Enter para voltar ao menu...";
        cin.ignore();
        cin.get();
    }
    else{
        cout << "Pressione Enter para voltar ao menu...";
        cin.get(); 
    }
}

void modificar(Morto* mortos, int*& contabilidadeMortuaria){
    clearScreen();
    
    cout << "Mortos registrados:\n";
    
    for(int i = 0; i < *contabilidadeMortuaria; i++){
        cout << "Morto " << i + 1 << ":\n";
        cout << "Nome: " << mortos[i].nome << endl;
        cout << "Idade: " << mortos[i].idade << endl;
        cout << "ID: " << mortos[i].id << endl;
        cout << "Relatorio de Morte:\n";
        cout << "   Causa: " << mortos[i].relatorio.causaDaMorte << endl;
        cout << "   Data: " << mortos[i].relatorio.dataDaMorte.dia << "/" << mortos[i].relatorio.dataDaMorte.mes << "/" << mortos[i].relatorio.dataDaMorte.ano << endl;
        cout << "   Hora: " << mortos[i].relatorio.horaDaMorte.hora << ":" << mortos[i].relatorio.horaDaMorte.minuto << ":" << mortos[i].relatorio.horaDaMorte.segundo << endl;
        cout << endl;
    }

    int escolha;
    
    cout << "Escolha o numero do morto que deseja modificar: ";
    cin >> escolha;
    
    escolha--;

    if(escolha >= 0 && escolha < *contabilidadeMortuaria){
        cin.ignore();
        cout << "Nome [" << mortos[escolha].nome << "]: ";
        getline(cin, mortos[escolha].nome);
        
        cout << "Idade [" << mortos[escolha].idade << "]: ";
        cin >> mortos[escolha].idade;
        
        cout << "ID [" << mortos[escolha].id << "]: ";
        cin >> mortos[escolha].id;
        
        cout << "Causa da morte [" << mortos[escolha].relatorio.causaDaMorte << "]: ";
        cin.ignore();
        getline(cin, mortos[escolha].relatorio.causaDaMorte);
        
        cout << "Data da morte (dia / mes / ano separados por espaco) [" << mortos[escolha].relatorio.dataDaMorte.dia << "/" << mortos[escolha].relatorio.dataDaMorte.mes << "/" << mortos[escolha].relatorio.dataDaMorte.ano << "]: ";
        cin >> mortos[escolha].relatorio.dataDaMorte.dia >> mortos[escolha].relatorio.dataDaMorte.mes >> mortos[escolha].relatorio.dataDaMorte.ano;
        
        cout << "Hora da morte (hora : minuto : segundo separados por espaco) [" << mortos[escolha].relatorio.horaDaMorte.hora << ":" << mortos[escolha].relatorio.horaDaMorte.minuto << ":" << mortos[escolha].relatorio.horaDaMorte.segundo << "]: ";
        cin >> mortos[escolha].relatorio.horaDaMorte.hora >> mortos[escolha].relatorio.horaDaMorte.minuto >> mortos[escolha].relatorio.horaDaMorte.segundo;

        cout << "\nMorto modificado com sucesso!\n";
    }
    else{
        cout << "Numero de morto invalido.\n";
    }

    cout << "Pressione Enter para voltar ao menu...";
    cin.ignore();
    cin.get(); 
}

void excluir(Morto* mortos, int*& contabilidadeMortuaria){
    clearScreen();
    
    cout << "Mortos registrados:\n";
    
    for(int i = 0; i < *contabilidadeMortuaria; ++i){
        cout << "Morto " << i + 1 << ":\n";
        cout << "Nome: " << mortos[i].nome << endl;
        cout << "Idade: " << mortos[i].idade << endl;
        cout << "ID: " << mortos[i].id << endl;
        cout << "Relatorio de Morte:\n";
        cout << "   Causa: " << mortos[i].relatorio.causaDaMorte << endl;
        cout << "   Data: " << mortos[i].relatorio.dataDaMorte.dia << "/" << mortos[i].relatorio.dataDaMorte.mes << "/" << mortos[i].relatorio.dataDaMorte.ano << endl;
        cout << "   Hora: " << mortos[i].relatorio.horaDaMorte.hora << ":" << mortos[i].relatorio.horaDaMorte.minuto << ":" << mortos[i].relatorio.horaDaMorte.segundo << endl;
        cout << endl;  
    }

    int escolha;
    
    cout << "Escolha o numero do morto que deseja ressuscitar: ";
    cin >> escolha;
    
    escolha--;

    if(escolha >= 0 && escolha < *contabilidadeMortuaria){
        for (int i = escolha; i < *contabilidadeMortuaria - 1; i++){
            mortos[i] = mortos[i + 1];
        }
        (*contabilidadeMortuaria)--;

        cout << "\nMorto excluido com sucesso!\n";
    }
    else{
        cout << "Numero de morto invalido.\n";
    }

    cout << "Pressione Enter para voltar ao menu...";
    cin.ignore();
    cin.get(); 
}

bool gerenciamento(int escolhaMenu, Morto* mortos, bool statusMenu, int*& contabilidadeMortuaria){
    switch(escolhaMenu){
        case 1:
            criar(mortos, contabilidadeMortuaria);
            break;
        case 2:
            ver(mortos, contabilidadeMortuaria);
            break;
        case 3:
            modificar(mortos, contabilidadeMortuaria);
            break;
        case 4:
            excluir(mortos, contabilidadeMortuaria);
            break;
        case 5:
            statusMenu = false;
            break;
        default:
            break;
    }

    return statusMenu;
}

void ordenarPorId(Morto* mortos, int*& contabilidadeMortuaria){
    for(int i = 0; i < *contabilidadeMortuaria - 1; i++){
        int menorIndex = i;
        
        for(int j = i + 1; j < *contabilidadeMortuaria; j++){
            if(mortos[j].id < mortos[menorIndex].id){
                menorIndex = j;
            }
        }
        if(menorIndex != i){
            Morto temp = mortos[i];
            mortos[i] = mortos[menorIndex];
            mortos[menorIndex] = temp;
        }
    }
}

int main(){
    bool statusMenu = true;
    int tentativas = 3;
    const int MAX_MORTOS = 10;
    Morto mortos[MAX_MORTOS];
    int *ptrContabilidadeMortuaria = new int(3);

    assert(ptrContabilidadeMortuaria != nullptr);
    
    mortos[0] = {"Kurt Cobain", 27, 1, {"Dor de cabeca", {5, 4, 1994}, {18, 47, 99}}};
    mortos[1] = {"Olavo de Carvalho", 74, 5, {"Otario", {24, 1, 2022}, {12, 22, 13}}};
    mortos[2] = {"Pairulito", 101, 0, {"Queimadura Solar", {16, 1, 2017}, {0, 0, 1}}};

    tentativaAcesso(); //mensagem de tentativa de acesso
    
    if(!login(tentativas)){ //login com usuario e senha
        cout << "Acesso negado. Encerrando o programa." << endl;
        return 0;  
    } 
    else{
        cout << "Acesso permitido. Bem-vindo!" << endl;
    }
    
    while(statusMenu == true){
        int escolhaMenu = crudMenu(); //chama o menu após confirmação de login

        statusMenu = gerenciamento(escolhaMenu, mortos, statusMenu, ptrContabilidadeMortuaria);
    }

    delete ptrContabilidadeMortuaria;
    
    return 0; 
}