#include <iostream>
#include "math.h"
using namespace std;

int main()
{

    int decimalInput; // decimal a ser convertido
    int resultcodificado = 0; //2 = 0, 1 = 1
    int potencia = 0;
    
    cout << "Numero em decimal: ";
    cin >> decimalInput;

    while (decimalInput > 0)
    {
        //cout << decimal % 2;
        if (decimalInput % 2 == 0)
        {
            //cout << 2;
            resultcodificado += 0 * pow(10, potencia);
        }
        else
        {
            //cout << decimalInput % 2;
            resultcodificado += 1 * pow(10, potencia);
        }

        potencia++;
        decimalInput /= 2;
    }
    cout << "Numero em binario: " << resultcodificado << endl;

    return 0;
}
