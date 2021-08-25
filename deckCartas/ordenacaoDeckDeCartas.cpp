#include <iostream>
#include <stdlib.h>
#include <time.h>

using namespace std;

/* 
Programa que mostra dois processor de exemplo para
ordenar um deck com 20 cartas. todas com os mesmos valores 
conforme exemplificado em aula.

Tive que implementar todo o cenário antes de iniciar o algoritmo em si.
Sei que não está com as melhores práticas, a intenção é a melhor didática
possível e simplificação de código.

O core do exemplo está detalhado na função sortDistribuicao, e também criei um 
sistema de peso para as cartas, assim podemos aplicar outros modos de 
ordenação convencional. Espero que gostem. Deu trabalho fazer e foi bem divertido.
Autor: Kevin R */

/* Ordem para os numeros vai de 
    1-13 => j = 11, q = 12, k = 13, A = 1;
    Naipes: Asci to naipe
       5 ♣ | 4 ♦ | 3 ♥ | 6 ♠
Pesos  100 | 200 | 300 | 400

*/

/* Constantes para manipulação do deck
    Troque os NUMERO_UTILIZADOS se desejar
 */

const int NUMERO_UTILIZADOS[] = { 2, 1, 4, 13, 6, 11} ;
const int TAM_NUMEROS = sizeof(NUMERO_UTILIZADOS)/ sizeof(int);
const int QUANTIDADE_DE_CARTAS = TAM_NUMEROS * 4; // 4 = 4 NAIPES

struct carta
{
    unsigned short int n; // numero [1,13]
    char l;               // letra [3,6]

    /* Retorna o valor dessa carta, o valor peso dela */
    int value()
    {
        int soma = 0;
        soma += n;
        int vl = (int)l;

        switch (vl)
        {
        case 5:
            soma += 100;
            break;
        case 6:
            soma += 400;
            break;
        case 4:
            soma += 200;
            break;
        case 3:
            soma += 300;
            break;
        }

        return soma;
    }
};

/* Escreve a carta como J♥ */
void show(carta c)
{

    //imprime o numero
    if (c.n == 1)
        cout << 'A';
    else if (c.n == 11)
        cout << 'J';
    else if (c.n == 12)
        cout << 'Q';
    else if (c.n ==13)
        cout << 'K'; 
    else
        cout << c.n;

    // imprime a letra
    cout << c.l;
}

void mostrarDeck(carta deck[])
{
    //mostrar as cartas
    for (int i = 0; i < QUANTIDADE_DE_CARTAS; i++)
    {
        cout << " ";
        show(deck[i]);
        //cout << deck[i].n << deck[i].l;
    }
    cout << endl;
}

void embaralharDeck(carta deck[], int vezes = 100)
{
    for (int i = 0; i <= vezes; i++)
    {
        int index1 = rand() % QUANTIDADE_DE_CARTAS;
        int index2 = rand() % QUANTIDADE_DE_CARTAS;
        //troca de valores

        carta tmp = deck[index1];
        deck[index1] = deck[index2];
        deck[index2] = tmp;
    }
}

void sortSelectDeck(carta deck[], int tamanhoArrayDeck)
{

    for (int i = 0; i < tamanhoArrayDeck; i++)
    {
        int maiorV = deck[i].value();
        int indexMaior = i;
        for (int y = i + 1; y < tamanhoArrayDeck; y++)
        {
            if (deck[y].value() < maiorV)
            {
                //cout << deck[y].value() << " < " << maiorV << endl;
                maiorV = deck[y].value();
                indexMaior = y;
            }
        }

        /* cout << "\t swap ";
        show(deck[indexMaior]);
        cout << " <-> ";
        show(deck[i]);
        cout << endl; */

        //swap
        carta tmp = deck[indexMaior];
        deck[indexMaior] = deck[i];
        deck[i] = tmp;
    }
}

void sortSelect(int array[], int tamanhoArray)
{

    for (int i = 0; i < tamanhoArray; i++)
    {
        int maiorV = array[i];
        int indexMaior = i;
        for (int y = i + 1; y < tamanhoArray; y++)
        {
            if (array[y] < maiorV)
            {
                //cout << deck[y] << " < " << maiorV << endl;
                maiorV = array[y];
                indexMaior = y;
            }
        }

        /* cout << "\t swap ";
        show(array[indexMaior]);
        cout << " <-> ";
        show(array[i]);
        cout << endl; */

        //swap
        int tmp = array[indexMaior];
        array[indexMaior] = array[i];
        array[i] = tmp;
    }
}

bool haveNumberInDeck(const int array[], int n)
{

    for (int i = 0; i < TAM_NUMEROS; i++)
        if (array[i] == n)
            return true;

    return false;
    
}

void sortDistribuicao(carta deck[])
{
    /* Conforme exemplificado pelo professor
    Primeiro separamos as cartas quanto ao seu numero
    e depois com relção aos seus naipes depois basta
    pega a partir da pilha de mais valor para a de menor valor
    colocando em estrutura de pilha.
    Ex: 5 | 4 < 5 | 3 < 4 < 5 ... | n-1 < n;

    Detalhes para implementação

    Para separarmos em "blocos"(buckets), devemos pensar na quantidade 
    de bukets usados e no critério de inserção de cada carta no seu
    respectivo bucket.
        Para separarmos quanto ao naipe, usei o valor do próprio naipe.
            5 ♣ | 4 ♦ | 3 ♥ | 6 ♠

        Sendo assim o 3 = bucket 0,
                      4 = bucket 1,
                      5 = bucket 2,
                      6 = bucket 3,
            o que resultara numa expresão:
                f(x) = x-3 ou f(naipe) = naipe-3 ou indiceBucket = naipe-3
        Sendo assim precisaremos de 4 bukets para separarmos
        quanto ao naipe. Sabemos também que em cada bucket deve
        ter espaço para 5 cartas. 
        *Para simplificação do  problema extremamente definido,
        não usarei uma liked-list nem uma hash table
        no sentido concreto da estrutura.

        Para fácil compreensão serão utilizadas apenas arrays 
        bidimensionais como no exemplo a seguir.

        Os quatro buckets ficaram dispostos da seguinte forma:

        Buckets
            0   || carta1 | carta2 | carta3 ... 
            1   || carta1 | carta2 | carta3 ...
            2   || carta1 | carta2 | carta3 ...
            3   || carta1 | carta2 | carta3 ...

        O que nos daria uma estrutura que será representada dessa forma:  */

    carta bucketsNaipes[4][TAM_NUMEROS];

    /* Agora precisamos do critério de inserção, que já temos acima
       indiceBucket = naipe-3

       Precisamos iterar sobre cada carta e então colocá-la no seu bucket correto.
     */


    /* Para inserirmos no bucket precisamos saber também a posição
        em que colocaremos no bucket.
        Exemplo: 
        Considere que vemos inserir no bucket 1.

        Buckets
            1   ||      |      |      ...
            3   ||      |      |      ...
        
        Buckets
            1   ||carta1|      |      ...
            3   ||      |      |      ...

        Agora bucket 1 novamente e depois no 3.

        Buckets
            1   ||carta1|carta2|      ...
            3   ||carta1|      |      ...

        Precisamos dizer ao computador em que posição do bucket ele deve
        inserir cada carta. Ele não é tão inteligente quanto você.

        Para termos esse controle usarei uma estrutura
        que em vez de guardar cartas guardará as posições em que cada próxima carta
        deverá ser inserida.

        {0,0,0,0} => como no exemplo acima teriamos algo como:
        {0,2,0,1} => porque o proximo do bucket 1
        precisará ser inserio da posição 2 da array( que vai de 0-4 )
        e o próximo do bucket 3 precisará entrar na posição 1;

        Depois de pegar a posição basta incrementar o valor para a proxima posição
        ficando assim: {0,3,0,2}
        
        Bom, iniciarei esse estrutura de posições com zeros , pois a posição
        inicial de todas as inseções é na posição 0 ,ou seja, a primeira posição.*/

    int posicaoDosBucketsNaipe[4] = {0,0,0,0};

    /* Primeiro vou separar os buckets para os números 
        que vão de [0,13];
        Depois inicializarei todas as posições de inserção com zero.

        Não se preocupe, farei primeiro isso com os números embora já tenha declarado
        a estrutura para os bukets dos naipes primeiro.
        Fiz assim para a melhor compreesão. O princípio é o mesmo.
     */

    carta bucketsNumeros[13][TAM_NUMEROS]; // 13 numeros, 5 cartas de cada
    int posicaoDosBucketsNumero[13] = {0,0,0,0,0,  0,0,0,0,0, 0,0,0}; // 13 posições

    /* Vamos iterar sobre todas as cartas e colocá-las
    em seus buckerts de números */

    for (int i = 0; i < QUANTIDADE_DE_CARTAS; i++)
    {
        // cout << "Carta:  ";
        // show(deck[i]);

        /* indiceBucket = o próprio valor da carta - 1, visto que A = 1,
            Sendo assim a carta com valor 1 vai pro indice 0 e a com valor 13 vai pro 12;
          */
        int indiceBucketNumero = deck[i].n - 1;

        // cout << "\n\t indiceN: " << indiceBucketNumero << endl;

        /* posição em que colocaremos no bucket. */
        int posicaoDeInsercaoNoBucketNumero = posicaoDosBucketsNumero[indiceBucketNumero];

        // cout << "\t pos: " << posicaoDeInsercaoNoBucketNumero << endl;

        /* Tendo tudo já em mãos basta já realizarmos
        as inserções nos bukets correspondentes */
        bucketsNumeros[indiceBucketNumero][posicaoDeInsercaoNoBucketNumero] = deck[i];
        
        // configura a proxima posição de inserçaõ
        posicaoDosBucketsNumero[indiceBucketNumero]++;
    }

    /* Veremos os resultados aqui abaixo para debug,
        caso deseje descomente até o fim do debug

        Irei filtrar apenas os buckets que estamos usando;
        e precisarei dessa informação para mais pra frente 
        buscar apenas os buckets dos numeros que estamos utilizando.
        *Após rever um pouco, decidi colocar essa informação em uma constante
        chamada NUMERO_UTILIZADOS;
    */
    cout << "Buckets Numeros" << endl;
    for (int i = 0; i < 13; i++)
    {
        if ( !( haveNumberInDeck(NUMERO_UTILIZADOS,i+1) ) )
            continue;

        printf(" index %d    ||",i);
        for (int j = 0; j < 4; j++)
        {
                cout << "  ";
                show(bucketsNumeros[i][j]);
                cout << "  |";       
            }
        cout << endl;
    }
    /* Fim debug */

    /* Agora que temos os buckets em ordem pelos numeros
        Podemos montar uma pilha deles pegando do de maior valor
        para o de menor valor, nesse caso pegando do J até o 2:
        J | 5 < J | 4 < 5 < J ... | n-1 < n; 
     */

    carta deckOrdenadoPorNumeros[QUANTIDADE_DE_CARTAS];


    /* Agora pegarei os numeros de cada bucket
     de ordem crescente e então colocarei  na array deckOrdenadoPorNumeros */

    
    int tmpi = QUANTIDADE_DE_CARTAS-1; //variavel para indice temporario;

    /* Farei um clone dos numeros utilizados em ordem */
    int sorteNUMERO_UTILIZADOS[TAM_NUMEROS];

    for (int i = 0; i < TAM_NUMEROS; i++)
        sorteNUMERO_UTILIZADOS[i] = NUMERO_UTILIZADOS[i];

    sortSelect(sorteNUMERO_UTILIZADOS,TAM_NUMEROS);
    
    
    for (int indiceBucketNumeros = TAM_NUMEROS-1; indiceBucketNumeros >= 0; indiceBucketNumeros--)
    {
        for (int indicePosBucketNum = 0; indicePosBucketNum < 4 ; indicePosBucketNum++)
        {
            
           /*  cout << "(" <<indiceBucketNumeros << "," << indicePosBucketNum << ")\n";
            cout << "POS:  " << tmpi <<" = \t(" <<NUMERO_UTILIZADOS[indiceBucketNumeros]-1 << "," << indicePosBucketNum << ")";
            cout << "=";
            show(bucketsNumeros[ NUMERO_UTILIZADOS[indiceBucketNumeros]-1 ][indicePosBucketNum]);
            cout << "\n"; */
            
            deckOrdenadoPorNumeros[tmpi] = bucketsNumeros[ sorteNUMERO_UTILIZADOS[indiceBucketNumeros]-1 ][indicePosBucketNum];
            tmpi--;
        }
    }
    
    
    /* Visualizando o deck ordenado por numeros na mão como fica */
    cout << "\nDeck com ordenacao dos numeros\n";
    mostrarDeck(deckOrdenadoPorNumeros);
    cout << "\n";

     /* Vamos iterar sobre todas as cartas e colocá-las
    em seus buckerts de naipes */

    for (int i = 0; i < QUANTIDADE_DE_CARTAS; i++)
    {
        /* indiceBucket = naipe-3 */
        int indiceBucketNaipe = deckOrdenadoPorNumeros[i].l - 3;

        /* posição em que colocaremos no bucket. */
        int posicaoDeInsercaoNoBucketNaipe = posicaoDosBucketsNaipe[indiceBucketNaipe];

        /* Tendo tudo já em mãos basta já realizarmos
        as inserções nos bukets correspondentes */
        bucketsNaipes[indiceBucketNaipe][posicaoDeInsercaoNoBucketNaipe] = deckOrdenadoPorNumeros[i];
        
        // configura a proxima posição de inserçaõ
        posicaoDosBucketsNaipe[indiceBucketNaipe]++;
    }

    /* Veremos os resultados aqui abaixo para debug,
        caso deseje descomente até o fim do debug
    */
    cout << "Buckets por naipes" << endl;
    for (int i = 0; i < 4; i++)
    {
        printf("    %d    ||",i);
        for (int j = 0; j < TAM_NUMEROS; j++)
        {
            cout << "  ";
            show(bucketsNaipes[i][j]);
            cout << "  |";       
        }
        cout << endl;
    }
    /* Fim debug */

    /* Agora vamos colocar os decks por ordem no deck original
        a sequência dos buckets será 2,1,0,3 ==  ♣ |  ♦ |  ♥ |  ♠
     */

    int sequencia[4] = {2,1,0,3};
    tmpi = 0;

    for (int i = 0; i < 4; i++)
    {
        int numeroSequencia = sequencia[i];
        for (int j = 0; j < TAM_NUMEROS; j++)
        {
            deck[tmpi] = bucketsNaipes[numeroSequencia][j];
            tmpi++;
        }
        
    }
    
    
}

int main()
{
    srand(time(NULL)); // gera uma seed pra numero aleatorios

    /*
          5 ♣ | 4 ♦ | 3 ♥ | 6 ♠
    Pesos  100 | 200 | 300 | 400
    */

    /* Gerar o deck com QUANTIDADE_DE_CARTAS
       pra cada, em todos os Naipes
    */
    carta deck[QUANTIDADE_DE_CARTAS];

    for (unsigned int naipe = 3; naipe <= 6; naipe++)
    {
        for (int i = 1; i <= TAM_NUMEROS; i++)
        {
            int index = ((naipe - 3) * TAM_NUMEROS) + (i - 1);
            //cout << "index="<<  index << endl;
            deck[index].n = NUMERO_UTILIZADOS[i - 1];
            deck[index].l = naipe;
        }
    }

    //mostrar as cartas
    cout << "Deck:\n";
    mostrarDeck(deck);

    // embaralhando as cartas n vezes
    embaralharDeck(deck);

    //mostrar cartas embaralhadas
    cout << "Deck embaralhado: \n";
    mostrarDeck(deck);
    cout << endl;

    /* Com o método value é possivel dar um sort no deck
        unsando métodos de ordenação comum como o buble, select, merge...
    */
    
    //sortSelectDeck(deck, QUANTIDADE_DE_CARTAS);

    sortDistribuicao(deck);

    cout << "\nDeck ordenado \n";
    mostrarDeck(deck);

    cout << endl;

    return 0;
}