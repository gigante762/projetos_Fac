#include <iostream>

using namespace std;


void shiftToRight(int array[], int tam, int posInicial, int posFinal)
{
    for (int i = posFinal; i >= posInicial; i--)
    {
        array[i] = array[i-1];
    }
}

void printArray(int array[], int tam)
{
    cout << "|";
    for (int i = 0; i < tam; i++)
    {
        cout << " " << array[i] << " |";
    }
    cout  << endl;
    
}

void insertSortDebug(int array[], int tam)
{
    if (tam <= 1)
        return;

    int currentPos = 1;
    int tmp = 0;

    for (int i = currentPos; i < tam; i++)
    {

        cout << "currentPos: " << currentPos << endl;
        //cout << "i: " << i << endl;

        int indTroca = currentPos;
        for (int j = currentPos; j >= 0; j--)
        { 
            if (array[currentPos]  < array[j-1])
            {
                indTroca = j-1;
                cout << array[j-1] << " > " << array[currentPos] << endl;
                cout << "\ttrocar com o " << indTroca << endl;
            }

        }

        // passar o valor para temp
        cout << "Trocando...\n";
        tmp = array[currentPos];
        array[currentPos] = 0;
        printArray(array,tam);
        shiftToRight(array,tam,indTroca,currentPos);
        array[indTroca] = 0;
        printArray(array,tam);

        array[indTroca] = tmp;
        printArray(array,tam);

        currentPos++;
    
    }
    
}

void insertSort(int array[], int tam)
{
     if (tam <= 1)
        return;

    int currentPos = 1;
    int tmp = 0;

    for (int i = currentPos; i < tam; i++)
    {
        int indTroca = currentPos;

        for (int j = currentPos; j >= 0; j--)
        {
            if (array[currentPos]  < array[j-1])
            {
                indTroca = j-1;
            }
        }

        tmp = array[currentPos];
        
        for (int k = currentPos; k >= indTroca; k--)
        {
            array[k] = array[k-1];
        }

        array[indTroca] = tmp;
        currentPos++;
    
    }
}

void insertSort2(int vetor[], int tam){
    int aux;
    int j;
    for(int i=1; i < tam; i++){
        aux = vetor[i];
        j = i - 1;
        while(j >= 0 && aux < vetor[j]){
            vetor[j+1] = vetor[j];
            j--;
        }
        vetor[j+1] = aux;
    }
}

int main()
{
    
    int array[] = {7,4,2,3};
    cout << "Array incial: ";
    printArray(array,4);
    insertSort2(array, 4);
    cout << "Array final:  ";
    printArray(array,4);

    return 0;
}
