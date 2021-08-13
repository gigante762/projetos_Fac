#include <iostream>

using namespace std;


void describe(int v[],int size)
{
    for (int i = 0; i < size; i++)
    {
        cout << v[i] << " ";
    }
    cout  << endl;
}

void swap(int &a, int &b)
{
    int tmp = a;
    a = b;
    b = tmp;
}

void selectSort(int v[], int size)
{
    for (int i = 0; i < size; i++)
    {
        int menor = i;
        for (int j = i; j < size; j++)
            if (v[j] < v[menor])
               menor = j;
               
        swap(v[i],v[menor]);
        
    }
}



int main()
{
   int v[] = {5,3,7,6,1,2,0,4,8,9};

   describe(v,10);
   selectSort(v,10);
   describe(v,10);


   return 0;
}
