#include <iostream>
#include <cmath> // não vou importar atoa
using namespace std;

/*  Autor: Kevin Souza
    Calculadora Polonesa Inversa v3.3
*/

#define PI 3.14159265

/* Stack Size, max operands */
#define TAM 10

/* Atalho de tipagem genérica */
typedef float ItemType;

struct Stack
{
    ItemType data[TAM];
    int length = 0;
};

bool isEmpty(Stack &p)
{
    return (p.length == 0);
}

bool isFull(Stack &p)
{
    return (p.length == TAM);
}

void push(Stack &p, ItemType n)
{
    if (!isFull(p))
    {
        p.data[p.length] = n;
        p.length++;
    }
    else
    {
        cout << "Stack cheia!" << endl;
    }
}

ItemType pop(Stack &p)
{
    if (!isEmpty(p))
    {
        ItemType tmp = p.data[p.length - 1];
        p.length--;
        return tmp;
    }
    else
    {
        cout << "Stack vazia!" << endl;
        return false;
    }
}

void describe(Stack p)
{
    if (isEmpty(p))
    {
        cout << "Stack: vazia" << endl;
        return;
    }

    cout << "Stack: ";
    for (int i = 0; i < p.length; i++)
    {
        cout << p.data[i] << " ";
    }
    cout << endl;
}

/* NPR */

// my registers, to serve as cpu registers, and avoid DRY
float ax, bx;

/* Idermediario para a realização das aperações, coloca os valores nos
    registradores ax,bx caso tenha o suficiante para realizar a operação */
bool stackOperandLenghtLtTwo(Stack &p)
{
    if (p.length < 2)
    {
        cout << "\tNao ha operadores suficientes para realizar a operacao\n";
        return false;
    }

    ax = pop(p);
    bx = pop(p);

    return true;
}

/* Idermediario para a realização das aperações, coloca os valores nos
    registradores ax,bx caso tenha o suficiante para realizar a operação */
bool stackOperandLenghtLtOne(Stack &p)
{
    if (p.length < 1)
    {
        cout << "\tNao ha operadores suficientes para realizar a operacao\n";
        return false;
    }

    ax = pop(p);

    return true;
}

/* Retorna a igualdade de duas strings */
bool stringEquals(string a, string b)
{
    return a.compare(b) == 0;
}

/* Verificar se os caracteres são numeros e inclui outras validações */
bool isNumber(const string& str)
{
    /* Verificadores de duplicidade */
    bool haveDot = false;
    bool haveMinus = false;
    
    int count = 0;

    // for tipo Lua.
    for (char const &c : str) {

        // tem dois . ou - retorna false
        if (c == '.' && haveDot) return false; // tem dois .
        if (c == '-' && haveMinus) return false; // tem dois -
        if (c == '.') haveDot = true;
        if (c == '-') haveMinus = true;

        // nao é numero nem ponto
        if ( (c < 48 || c > 57) && (c != 46) && (c != 45)) return false;

        // ha um - fora da posicao 0
        if (c==45 && count > 0) return false;

        count++;
    }
            
    return true;
}

/* Uma simples função de fatorial, sem muitas verificações */
float fatorial(float n)
{
    float fac = 1;
    if (n < 0)
    {
        cout << "\t Nao ha fatorial de numero negativo." << endl;
        return n;
    }
    else {
        for(int i = 1; i <= n; ++i) {
            fac *= i;
        }   
    }
    return fac;

}

void instructions()
{
    cout << " ====== Intrucoes ====== " << endl;
    cout << "Use 'r' para ver a pilha atual" << endl;
    cout << "Use '=' para ver o valor atual" << endl;
    cout << "Use 'h' para exibir o menu de ajuda" << endl;
    cout << "Escreva 'del' para apagar o ultimo valor inserido" << endl;
    cout << "Escreva 'reset' para apagar todos os valores inseridos" << endl;
    cout << "====== Operacoes basicas ====== " << endl;
    cout << "Operacoes basicas: + - * / " << endl;
    cout << "====== Constantes ====== " << endl;
    cout << " 'pi' => "<<PI << endl;
    cout << "====== Operacoes extras ====== " << endl;
    cout << "//  (divisao inteira)    | ^ (pontencia)  | ! (fatorial) " << endl;
    cout << "log (log de a na base b) | raiz (raiz de a no grau b)" << endl;
    cout << "sen, cos, tan | todos em radianos" << endl;
    cout << "asen, acos, atan | todos em radianos" << endl;
    cout << "Escreva 'exit' para encerrar a aplicacao"  << endl;
}

void showStackTopAsResult(Stack p)
{
    cout << "\t= ";
    cout << (float) p.data[p.length-1];
    cout<< endl;
}

int main()
{
    Stack operands;
    string op = "";

    instructions();

    while (!stringEquals(op,"exit"))
    {
        cout << "> ";
        getline(cin, op);

        // verificar se é numero decimal e se a stack está cheia
        if (isNumber(op))
        {
            if (isFull(operands))
            {
                cout << "\tNao ha mais espaco na memoria." << endl;
            }
            else
            {
                push(operands, std::stof(op)); // converte pra float e da push
            }
        }
        /* Verificação de constantes */
        else if (stringEquals(op,"pi"))
        {
            push(operands,PI);
        }
         /* Comandos */
        else if (stringEquals(op,"exit"))
        {
            cout << "Programa encerrado." << endl;
        }
        else if (stringEquals(op,"r"))
        {
            cout << "Atual ";
            describe(operands);
            cout << endl;
        }
        else if (stringEquals(op,"h"))
        {
            instructions();
        }
        else if (stringEquals(op,"="))
        {
            cout << "\tR: ";
            cout << (float) operands.data[operands.length-1];
            cout<< endl;
        }
        else if (stringEquals(op,"del"))
        {
            if (!isEmpty(operands))
                cout << "\tValor: " << pop(operands) << " apaguado." << endl;
            else
                cout << "\tNao ha valores na memoria." << endl;
        }
        else if (stringEquals(op,"reset"))
        {
            while (!isEmpty(operands))
            {
                pop(operands);
            }
            cout << "\tMemoria resetada." << endl;
        }

        /* operações binarias */
        else if(stringEquals(op,"+"))
        {
            if (stackOperandLenghtLtTwo(operands))
            {
                push(operands, ax+bx);
                showStackTopAsResult(operands);
            }
        }
        else if (stringEquals(op,"*"))
        {
            if (stackOperandLenghtLtTwo(operands))
            {
                push(operands, ax*bx);
                showStackTopAsResult(operands);
            }
        }
        else if (stringEquals(op,"^"))
        {
            if (stackOperandLenghtLtTwo(operands))
            {
                push(operands, pow(bx,ax));
                showStackTopAsResult(operands);
            }
        }
        else if (stringEquals(op,"/"))
        {
            if (stackOperandLenghtLtTwo(operands))
            {
                /* Verifica div 0 */
                if (ax == 0.0)
                {
                    /* Solta uma camapainha \a como som de erro */
                    cout << "\t Nao e possivel dividir por zero! \a" << endl;
                    // devolve os valores para stack
                    push(operands,bx);
                    push(operands,ax);
                }else
                {
                    push(operands, bx/ax);
                }
                showStackTopAsResult(operands);
            }
        }
        else if (stringEquals(op,"//"))
        {
            if (stackOperandLenghtLtTwo(operands))
            {
                /* Verifica div 0 */
                if (ax == 0.0)
                {
                    /* Solta uma camapainha \a como som de erro */
                    cout << "\t Nao e possivel dividir por zero! \a" << endl;
                    // devolve os valores para stack
                    push(operands,bx);
                    push(operands,ax);
                }else
                {
                    push(operands, (int) (bx/ax));
                }
                showStackTopAsResult(operands);
            }
        }
        else if (stringEquals(op,"%"))
        {
            if (stackOperandLenghtLtTwo(operands))
            {
                /* Verifica div 0 */
                if (ax == 0.0)
                {
                    /* Solta uma camapainha \a como som de erro */
                    cout << "\t Nao e possivel dividir por zero! \a" << endl;
                    // devolve os valores para stack
                    push(operands,bx);
                    push(operands,ax);
                }else
                {
                    // pois é nao aceita bx % ax
                    push(operands,  fmod(bx,ax));
                }
                showStackTopAsResult(operands);
            }
        }
        else if (stringEquals(op,"log"))
        {
            if (stackOperandLenghtLtTwo(operands))
            {
                push(operands,  log(bx)/log(ax));
                showStackTopAsResult(operands);
            }
        }
        else if (stringEquals(op,"-"))
        {
            if (stackOperandLenghtLtTwo(operands))
            {
                push(operands, bx-ax);
                showStackTopAsResult(operands);
            }
        }
        
        /* operações unarias */
        else if (stringEquals(op,"!"))
        {
            if (stackOperandLenghtLtOne(operands))
            {
                
                
                push(operands, fatorial(ax));
                showStackTopAsResult(operands);
            }
        }
        else if (stringEquals(op,"sen"))
        {
            if (stackOperandLenghtLtOne(operands))
            {
                push(operands, sin(ax));
                showStackTopAsResult(operands);
            }
        }
        else if (stringEquals(op,"cos"))
        {
            if (stackOperandLenghtLtOne(operands))
            {
                push(operands, cos(ax));
                showStackTopAsResult(operands);
            }
        }
        else if (stringEquals(op,"tan"))
        {
            if (stackOperandLenghtLtOne(operands))
            {
                push(operands, tan(ax));
                showStackTopAsResult(operands);
            }
        }
        else if (stringEquals(op,"asen"))
        {
            if (stackOperandLenghtLtOne(operands))
            {
                push(operands, asin(ax));
                showStackTopAsResult(operands);
            }
        }
        else if (stringEquals(op,"acos"))
        {
            if (stackOperandLenghtLtOne(operands))
            {
                push(operands, acos(ax));
                showStackTopAsResult(operands);
            }
        }
        else if (stringEquals(op,"atan"))
        {
            if (stackOperandLenghtLtOne(operands))
            {
                push(operands, atan(ax));
                showStackTopAsResult(operands);
            }
        }

        else
        {
            cout << "Operacao invalida..." << endl;
        }
    }

    return 0;
}
