#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <string>

using namespace std;

#define MAXIMO_COMPRAS 3
#define MAXIMO_CLIENTES 3
#define MAXIMO_PRODUTOS 3

#define SISTEMA "linux" // linux | windows

/* 
    Sistema para anotação de venda fiada

    Um cadastro para uma venda fiada. Chega de ser enrolado ao vender fiado.
    Teremos os clientes e os cliente tem as suas compra 
    e as compras a data, junto com o preço e a quantidade.
    Pare de tomar calote!

    Autor: Kevin R.
    Versão: 2.3.1
    
*/

/* Definiçaõ das Structs */
typedef struct Pessoa Tpessoa;
typedef struct Compra Tcompra;

struct Compra
{
    string nome = "";
    string dataCompra = "";
    unsigned int quantidade = 0;
    float total = 0;
};

struct Pessoa
{
    unsigned int id = 0; // PK
    string nome = "";
    Tcompra compras[MAXIMO_COMPRAS];
    unsigned int totalCompras = 0;
};

struct Produto
{
    int id = 0;
    string nome = ""; // PK, é eu sei...
    float preco = 0;
};

/* Fim Definiçaõ das Structs */

/* Opções para o menu */
const string OPCOES[3][5] = {{
                                 "===Gerenciar Clientes===",
                                 "Cadastrar cliente",
                                 "Ver cliente",
                                 "Editar cliente",
                                 "Remover cliente",
                             },
                             {
                                 "===Gerenciar Produtos===",
                                 "Cadastrar produtos",
                                 "Ver produtos",
                                 "Editar produtos",
                                 "Remover produtos",
                             },
                             {
                                 "===Gerenciar Compras de clientes===",
                                 "Registrar Compra para cliente",
                                 "Ver compras de um cliente",
                                 "Ver divida total um cliente",
                                 "Quitar compra de um cliente",
                             }};

/* Mostra os dados de uma pessoa */
void show(Pessoa p)
{
    cout << "Nome: " << p.nome << endl;
    cout << "\tId: " << p.id << endl;
    cout << "\tTotal de compras: " << p.totalCompras << endl;
}

/* Mostra os dados de um produto */
void show(Produto p)
{
    cout << "Nome: " << p.nome << endl;
    cout << "\tId: " << p.id << endl;
    cout << "\tPreco: " << p.preco << endl;
}
/* Mostra os dados de uma compra */
void show(Compra c)
{
    cout << "Produto: " << c.nome << endl;
    cout << "\tData: " << c.dataCompra;
    cout << "\tQuantidade: " << c.quantidade << endl;
    cout << "\tTotal: " << c.total << endl;
}

/* Array de pessoas */
Pessoa clientes[MAXIMO_CLIENTES];

/* Array de pessoas */
Produto produtos[MAXIMO_PRODUTOS];

/* Exibe todos os clientes */
void showAllCliente()
{
    bool justOne = false;
    for (int i = 0; i < MAXIMO_CLIENTES; i++)
    {
        if (clientes[i].id != 0)
        {
            show(clientes[i]);
            justOne = true;
        }
    }

    if (!justOne)
        cout << "Nao ha clientes cadastrados.\n";
}

/* Deleta os valores de uma compra */
void deleteCompra(Compra &c)
{
    //a data pode deixar pra escrever por cima
    c.nome = "";
    c.total = 0;
    c.quantidade = 0;
}

/* Cria uma novo cliente se houver vaga.
 Retorna true caso crie e false caso não tenha vaga
*/
bool cadastrarCliente()
{
    //cout << "Criar cliente, procurar vaga..." << endl;
    // procura por vaga
    int index = -1;

    for (int i = 0; i < MAXIMO_CLIENTES; i++)
    {
        if (clientes[i].id == 0)
        {
            index = i;
            break;
        }
    }

    if (index != -1)
    {
        cout << "Digite um nome: ";
        string tmpName;
        cin.ignore();
        getline(cin, tmpName);

        clientes[index].nome = tmpName;
        clientes[index].id = rand();

        return true;
    }
    return false;
}

/* Edita o nome de uma determinada pessoa */
void editarCliente(Pessoa &p)
{
    cout << "Nome: " << p.nome << endl;

    cout << "Digite o novo nome: ";
    string tmpName;
    cin.ignore();
    getline(cin, p.nome);
}

/* Edita o nome de uma determinada pessoa */
void removerCliente(Pessoa &p)
{
    cout << "Removendo " << p.nome << "..." << endl;

    p.nome = "";
    p.id = 0;

    // reseta todos os registros de compras;
    for (int i = 0; i < MAXIMO_COMPRAS; i++)
    {
        deleteCompra(p.compras[i]);
    }
}

/* Retorna index da array de cliente com base em um determinado id
    Caso não encontre retorna -1; */
int findCliente(int dados)
{
    int found = -1;

    for (int i = 0; i < MAXIMO_CLIENTES; i++)
    {
        if (clientes[i].id == dados)
        {
            return i;
        }
    }

    return found;
}

/* Exibe um menu com opções */
void printOpcoes()
{
    cout << "1- Gerenciar Clientes" << endl;
    cout << "2- Gerenciar Produtos" << endl;
    cout << "3- Gerenciar Compras de clientes" << endl;
}

/* Limpra o terminal com base no sistem operacional */
void cls()
{
    if (SISTEMA == "linux")
        system("cls");
    else
        system("lmp");
}

/* Exibe os menus de OPCOES e retorna o valor escolhido */
int menuPesonalizados(int menu)
{
    menu--;
    cout << OPCOES[menu][0] << endl;
    for (int i = 1; i < 5; i++)
    {
        cout << i << "- " << OPCOES[menu][i] << endl;
    }

    cout << "\n0- para sair\n";

    int op;
    cout << "> ";
    cin.ignore();
    cin >> op;

    return op;
}

/* Verifica se um numero esta entre um minimo e maximo */
bool checkeBetween(int val, int min, int max)
{
    return (val >= min && val <= max);
}

/* Cria uma novo produto se houver espaço.
 Retorna true caso crie e false caso não.
*/
bool cadastrarProduto()
{
    int index = -1;

    for (int i = 0; i < MAXIMO_PRODUTOS; i++)
    {
        if (produtos[i].id == 0)
        {
            index = i;
            break;
        }
    }

    if (index != -1)
    {
        cout << "Digite um nome para o produto: ";
        string tmpName;
        float tmpValor;
        cin.ignore();
        getline(cin, produtos[index].nome);

        cout << "Digite um preco para '" << produtos[index].nome << "': ";
        //cin.ignore();
        cin >> produtos[index].preco;
        //produtos[index].nome = tmpName;
        //produtos[index].preco = tmpValor;
        produtos[index].id = rand();
        return true;
    }
    return false;
}

/* Exibe todos os produtos */
void showAllProdutos()
{
    bool justOne = false;
    for (int i = 0; i < MAXIMO_PRODUTOS; i++)
    {
        if (produtos[i].id != 0)
            show(produtos[i]);
    }

    if (!justOne)
        cout << "Nao ha produtos cadastrados.\n";
}

/* Retorna o indice de um produto com base no nome */
int findProduto(string dados)
{
    int found = -1;

    for (int i = 0; i < MAXIMO_PRODUTOS; i++)
    {
        if (produtos[i].nome.compare(dados) == 0)
        {
            return i;
        }
    }

    return found;
}

void editarProduto(Produto &p)
{

    cout << "Nome antigo do produto: " << p.nome << endl;
    cout << "Digite o novo nome: ";
    //cin.ignore();
    getline(cin, p.nome);

    cout << "Nome antigo do produto: " << p.preco << endl;
    cout << "Digite o novo preco: ";
    //cin.ignore();
    cin >> p.preco;
}

void removerProduto(Produto &p)
{
    cout << "Removendo " << p.nome << "..." << endl;

    p.nome = "";
    p.id = 0;
    p.preco = 0;
}

void showAllCompras(Pessoa p)
{
    cout << "Compras de " << p.nome << endl;

    bool justOne = false;
    for (int i = 0; i < MAXIMO_COMPRAS; i++)
    {
        if (p.compras[i].quantidade != 0)
        {
            show(p.compras[i]);
            justOne = true;
        }
    }

    if (!justOne)
        cout << "Nao ha compras para o cliente " << p.nome << ".\n";
}

void quitarDivida(Compra &c)
{
    c.dataCompra = "";
    c.nome = "";
    c.quantidade = 0;
    c.total = 0;
}

/* Verifica se um cliente tem alguma compra */
bool hasCompra(Pessoa p)
{
    bool justOne = false;

    for (int i = 0; i < MAXIMO_COMPRAS; i++)
    {
        if (p.compras[i].quantidade != 0)
        {
            return true;
        }
    }

    return false;
}

/* Exibe a divida total de uma pessoa */
void verDividaTotal(Pessoa &p)
{
    cout << "\nDividas total de " << p.nome << endl;

    if (!hasCompra(p))
    {
        cout << "Nao ha dividas para o cliente " << p.nome << ".\n";
        return;
    }

    int sumitens = 0;
    float sumValor = 0;
    for (int i = 0; i < MAXIMO_COMPRAS; i++)
    {
        if (p.compras[i].quantidade != 0)
        {
            sumitens += p.compras[i].quantidade;
            sumValor += p.compras[i].total;
        }
    }

    cout << p.nome << " deve um total de R$" << sumValor << "\n";
    cout << p.nome << " Referente a " << sumitens << " produtos \n";

    cout << "Deseja quitar todas as suas dividas? (s/n) ";
    cin.ignore();
    char c;
    cin >> c;
    if (c == 's')
    {
        for (int i = 0; i < MAXIMO_COMPRAS; i++)
        {
            quitarDivida(p.compras[i]);
            p.totalCompras--;
        }

        cout << "Todas as dividas de " << p.nome << " foram quitadas\n";
    }
}

/* Registra uma compra para uma pessoa */
bool cadastrarCompra(Pessoa &p)
{
    if (p.totalCompras >= 5)
    {
        cout << "Nao ha para mais credito para "<< p.nome <<".\n" ;
        return false;
    }

    cout << "Compra para " << p.nome << endl;
    string tmpName;

    cout << "Nome do produto: ";
    cin.ignore();
    getline(cin, tmpName);

    int prodId = findProduto(tmpName);
    if (prodId == -1)
    {
        cout << "Produto nao localizado\n";
        return false;
    }

    int qtd = 0;
    do
    {
        cout << "Digite a quantidade: ";
        cin >> qtd;
    } while (!checkeBetween(qtd, 1, 1410065407)); // just a gambi;

    time_t result = time(NULL);
    string strData = ctime(&result);

    float tot = produtos[prodId].preco * qtd;

    // colocar a compra
    int idx = 0;
    for (int i = 0; i < MAXIMO_COMPRAS; i++)
    {
        if (p.compras[i].quantidade == 0)
        {
            idx = i;
            break;
        }
    }
    p.compras[idx].total = tot;
    p.compras[idx].quantidade = qtd;
    p.compras[idx].dataCompra = strData;
    p.compras[idx].nome = produtos[prodId].nome;

    p.totalCompras++;
    return true;
}

/* Carrega alguns dados já prontos */
void montarCenarioTest()
{
    clientes[0].nome = "Kevin";
    clientes[0].id = 21;

    clientes[1].nome = "Breno";
    clientes[1].id = 16;

    produtos[0].nome = "leite";
    produtos[0].id = 3;
    produtos[0].preco = 4.5;

    produtos[1].nome = "coca";
    produtos[1].id = 2;
    produtos[1].preco = 3;
}

int menu()
{
    short int op;
    cout << "==== Bem vindo a venda fiada ==== \n";
    cout << "Escolha uma opcao: \n";
    printOpcoes();
    cout << "> ";
    cin >> op;
    cout << "==== ----------------------- ==== \n";

    return op;
}

/* Recebe as escolhas do menu e intermedeia o processo de execução */
void processarOpcao(int menuop, int submenuop)
{
    if (menuop == 1)
    {
        if (submenuop == 1)
        {
            if (!cadastrarCliente())
                cout << "Nao ha vagas para mais clientes.\n";
        }
        else if (submenuop == 2)
            showAllCliente();
        else if (submenuop == 3)
        {
            int dados;
            cout << "Digite o id do cliente: ";
            cin >> dados;

            int indexCLiente = findCliente(dados);

            if (indexCLiente != -1)
            {
                editarCliente(clientes[indexCLiente]);
            }
            else
            {
                cout << "Cliente nao localizado!\n";
            }
        }
        else if (submenuop == 4)
        {
            int dados;
            cout << "Digite o id do cliente: ";
            cin >> dados;

            int indexCLiente = findCliente(dados);

            if (indexCLiente != -1)
            {
                removerCliente(clientes[indexCLiente]);
            }
            else
            {
                cout << "Cliente nao localizado!\n";
            }
        }
    }

    else if (menuop == 2)
    {
        if (submenuop == 1)
        {
            if (!cadastrarProduto())
                cout << "Nao ha espaco para mais produtos.\n";
        }
        else if (submenuop == 2)
            showAllProdutos();
        else if (submenuop == 3)
        {
            string dados;
            cout << "Digite o nome do produto: ";
            cin.ignore();
            getline(cin, dados);

            int indexProduto = findProduto(dados);

            if (indexProduto != -1)
            {
                editarProduto(produtos[indexProduto]);
            }
            else
            {
                cout << "Produto nao localizado!\n";
            }
        }
        else if (submenuop == 4)
        {
            string dados;
            cout << "Digite o nome do produto: ";
            cin.ignore();
            getline(cin, dados);

            int indexProduto = findProduto(dados);

            if (indexProduto != -1)
            {
                removerProduto(produtos[indexProduto]);
            }
            else
            {
                cout << "Produto nao localizado!\n";
            }
        }
    }

    else if (menuop == 3)
    {
        if (submenuop == 1)
        {
            int dados;
            cout << "Digite o id do cliente: ";
            cin >> dados;

            int indexCLiente = findCliente(dados);

            if (indexCLiente != -1)
            {
                if (!cadastrarCompra(clientes[indexCLiente]))
                    cout << "Nao foi possivel comprar fiado.\n";
            }
            else
            {
                cout << "Cliente nao localizado!\n";
            }
        }

        else if (submenuop == 2)
        {
            int dados;
            cout << "Digite o id do cliente: ";
            cin >> dados;

            int indexCLiente = findCliente(dados);

            if (indexCLiente != -1)
            {
                showAllCompras(clientes[indexCLiente]);
            }
            else
            {
                cout << "Cliente nao localizado!\n";
            }
        }

        else if (submenuop == 3)
        {
            int dados;
            cout << "Digite o id do cliente: ";
            cin >> dados;

            int indexCLiente = findCliente(dados);

            if (indexCLiente != -1)
            {
                verDividaTotal(clientes[indexCLiente]);
            }
            else
            {
                cout << "Cliente nao localizado!\n";
            }
            //verDividaTotal();
        }

        else if (submenuop == 4)
        {
            int dados;
            cout << "Digite o id do cliente: ";
            cin >> dados;

            int indexCLiente = findCliente(dados);

            if (indexCLiente != -1)
            {

                if (!hasCompra(clientes[indexCLiente]))
                {
                    cout << "Nao ha dividas para o cliente " << clientes[indexCLiente].nome << ".\n";
                    return;
                }

                int codigos_compra[MAXIMO_COMPRAS];
                cout << "Escolha o codigo temporario da compra para quitar: \n";
                for (int i = 0; i < MAXIMO_COMPRAS; i++)
                {
                    if (clientes[indexCLiente].compras[i].quantidade != 0)
                    {
                        show(clientes[indexCLiente].compras[i]);
                        codigos_compra[i] = rand();
                        cout << "\tcod: " << codigos_compra[i] << endl;
                    }
                }

                cout << "Digite o codigo da compra: ";
                int code;
                cin.ignore();
                cin >> code;

                for (int i = 0; i < MAXIMO_COMPRAS; i++)
                {
                    if (code == codigos_compra[i])
                    {
                        cout << "Compra de '" << clientes[indexCLiente].compras[i].nome << "'" << endl;
                        cout << "No valor de R$" << clientes[indexCLiente].compras[i].total;
                        cout << "  ---- Quitada com sucesso\n";
                        quitarDivida(clientes[indexCLiente].compras[i]);
                    }
                }
            }
            else
            {
                cout << "Cliente nao localizado!\n";
            }
        }
    }
    // just because
    else
    {
    }
}

int main()
{
    srand(time(NULL)); // seed pros ids
    char garbage;      // Para segurar o continue do menu

    /* Monta dados para test */
    montarCenarioTest();

    while (true)
    {
        cls();
        int opMenu = menu();
        while (!checkeBetween(opMenu, 1, 3))
        {
            cls();
            cout << "Valores invalidos...\n";
            opMenu = menu();
        }

        cls();
        int opSubmenu = menuPesonalizados(opMenu);

        while (!checkeBetween(opSubmenu, 0, 4))
        {
            cls();
            cout << "Valores invalidos...\n";
            opSubmenu = menuPesonalizados(opMenu);
        }

        processarOpcao(opMenu, opSubmenu);

        cout << "\n\nDigite 'a' e Enter para continuar ";
        cin >> garbage;
    }

    return 0;
}