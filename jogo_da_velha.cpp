#include <iostream>
using namespace std;

char tab[3][3];

bool vezX = true;
char winner = 'V';

void reset()
{
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            tab[i][j] = ' ';
}

void print(char sometab[3][3])
{
    char vez = vezX ? 'X' : 'O';
    cout << "X: 0 1 2 Vez: " <<  vez << "\n";
    for (int i = 0; i < 3; i++)
    {
        printf("%d |%c|%c|%c|\n",i,sometab[i][0],sometab[i][1],sometab[i][2]);
    }
        
}

char checkWinner(char sometab[3][3])
{
    char vez = vezX ? 'X' : 'O';
    // todas as linhas
    bool winner = true;

    int count = 0;
    //cout << "horizontal \n";
    for (int l = 0; l < 3; l++)
    {
        for (int r = 0; r < 3; r++)
        {
            if (sometab[l][r] != vez)
            {
                count = 0;
                break;
            }
            else
            {
                count++;
                //cout << count;
            }
        }
        if (count == 3)
        {
            //cout << "Teve vencedor\n";
            return vez;
        }
        else
        {
           // cout << "nao teve vencedor\n";
        }

    }

   // cout << "vertical \n";
    for (int l = 0; l < 3; l++)
    {
        for(int r = 0; r < 3; r++)
        {
            if (sometab[r][l] != vez)
            {
                count = 0;
                break;
            }
            else
            {
                count++;
                //cout << count;
            }
        }
        if (count == 3)
        {
            //cout << "Teve vencedor\n";
            return vez;
        }
        else
        {
            //cout << "nao teve vencedor\n";
        }
    }

    // diagonais
    //cout << "diagonais sup esq to inf dir \n";
    for (int l = 0; l < 3; l++)
    {
        
        if (sometab[l][l] != vez)
        {
            count = 0;
            break;
        }
        else
        {
            count++;
            //cout << count;
        }
        
        if (count == 3)
        {
            //cout << "Teve vencedor\n";
            return vez;
        }
        else
        {
            //cout << "nao teve vencedor\n";
        }
    }

    //cout << "diagonais sup dir to inf esq \n";
    if (sometab[2][0] == vez && sometab[1][1] == vez && sometab[2][0] == vez)
        return vez;

    return 'V'; //velha
    
}

bool validChoice(int x, int y)
{
    if (x < 0 || x > 2 || y < 0 || y > 2 )
        return false;

    if (tab[y][x] != ' ')
        return false;
        
    return true;
}


int main()
{

    reset();

    /* char testTab[3][3] = {
        {'X', 'O', 'X'},
        {'O', 'X', 'O'},
        {'X', 'O', 'O'},
    }; */

    print(tab);
    //print(testTab);

    //winner = checkWinner(testTab);

    
    for (int i = 0; i < 9 && winner == 'V'; i++)
    {
        int x,y;
        cout << "Pos X Y: ";
        cin >> x >> y;

        if (validChoice(x,y))
        {
            if(vezX)
                tab[y][x] = 'X';
            else
                tab[y][x] = 'O';

            winner = checkWinner(tab);
            vezX = !vezX;
        }
        else
        {
            cout << "Digite uma posicao valida.\n";
            i--;
        }

        print(tab);
        cout << "\n";
    } 

    cout << "O vencedor foi : " << winner << "\n"; 

    return 0;
}
