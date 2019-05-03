#include <iostream>

using namespace std;

char mat[20][25];
    // harta va fi retinuta intr-o matrice de caractere
    // care va fi afisata la consola
int i_snake[30], j_snake[30], snake_length;
int direction, next_direction;
    // 1 - sus
    // 2 - jos
    // 3 - stanga
    // 4 - dreapta

int score;
int i_food, next_i_food;
int j_food, next_j_food;
int i, j;
int i_direction[4];
int j_direction[4];

int main()
{
    // avem nevoie de un seed (de un numar foarte mare, pseudo-random)
    // cu care vom genera alte numere random

    // cand sarpele merge in sus, capul sau se afla cu o linie mai mica
    i_direction[1] = -1;
    i_direction[2] = 1;

    j_direction[3] = -1;
    j_direction[4] = 1;


    // desenam peretii matricii, de care sarpele nu poate trece
    for (i = 0; i < 25; i++)
    {
        mat[0][i] = '*';
        mat[19][i] = '*';
    }
    for (i = 0; i < 20; i++)
    {
        mat[i][0] = '*';
        mat[i][24] = '*';
    }

    // initial, merge spre dreapta
    direction = 4;

    snake_length = 3;
    i_snake[0] = 2;
    i_snake[1] = 2;
    i_snake[2] = 2;

    j_snake[0] = 1;
    j_snake[1] = 2;
    j_snake[2] = 3;

    i_food = 5;
    j_food = 8;
    mat[i_food][j_food] = '8';

    // "desenam" sarpele pe matrice
    for (i = 0; i < snake_length; i++)
        mat[ i_snake[i] ][ j_snake[i] ] = 'O';

    while (true)
    {
        cout << "Scor: " << score << '\n';
        for (i = 0; i < 20; i++)
        {
            for (j = 0; j < 25; j++)
                cout << mat[i][j];
            cout << endl;
        }

        char k;
        // preluam directia de la tastatura, dupa care apasam ENTER
        cin >> k;

        if (k == 'w')
            next_direction = 1;
        else if (k == 'a')
            next_direction = 3;
        else if (k == 's')
            next_direction = 2;
        else if (k == 'd')
            next_direction = 4;
        else if (k == 'x')
            break;

        // in caz ca are voie sa isi schimbe directia asa cum dorim noi
        // de exemplu, cand sarpele merge in jos si noi ii spunem sa mearga in sus, atunci nu are voie
        if (!(next_direction == 4 && direction == 3 ||
              next_direction == 3 && direction == 4 ||
              next_direction == 1 && direction == 2 ||
              next_direction == 2 && direction == 1))
        {

            i_snake[snake_length] = i_snake[snake_length - 1] + i_direction[next_direction];
            j_snake[snake_length] = j_snake[snake_length - 1] + j_direction[next_direction];


            // daca atinge peretele, atunci sarpele moare, iar jocul se termina
            if (mat[ i_snake[snake_length] ] [ j_snake[snake_length] ] == '*')
            {
                cout << "GAME OVER!\n";
                break;
            }

            // daca ajunge la mancare, sarpele creste
            if (mat[ i_snake[snake_length] ] [ j_snake[snake_length] ] == '8')
            {
                snake_length++;
                score++;

                bool ok = 0;
                while (!ok)
                {
                    ok = 1;

                    // pune mancare in alta pozitie
                    // folosind o functie pseudo-random
                    next_i_food = ((i_food * 666013)%6013)%18+1;
                    next_j_food = ((j_food * 666013)%6013)%23+1;
                    for (i = 0; i < snake_length; i++)
                        if (i_snake[i] == next_i_food && j_snake[i] == next_j_food)
                        {
                            ok = 0;
                            break;
                        }
                }
                i_food = next_i_food;
                j_food = next_j_food;
                mat[i_food][j_food] = '8';
            }
            else
            {
                // mutam coada in caz ca sarpele nu mananca, deci nu creste
                mat[ i_snake[0] ][ j_snake[0] ] = ' ';
                for (i = 0; i < snake_length; i++)
                {
                    i_snake[i] = i_snake[i+1];
                    j_snake[i] = j_snake[i+1];
                }
            }

            // mutam capul
            mat[ i_snake[snake_length - 1] ] [ j_snake[snake_length - 1] ] = 'O';


        }

        direction = next_direction;
        for (i = 0; i < 28; i++)
            cout << endl;

    }
    return 0;
}
