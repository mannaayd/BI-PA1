#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int flag = 0;
int celkem = 0;

long long int prevod(char* cislo, int soustava, int size)
{
    long long int num = 0;
    long long int temp;
    int piv = 0;
    for(int i = size - 1; i >= 0; i--)
    {
        if((int)cislo[i] < 58) temp = (int)cislo[i] - 48;
        else  temp = (int)cislo[i] - 87;
        num = num + temp * pow(soustava, piv);
        piv++;
    }
    return num;
}

void recursevariaton(char* cislo, int soustava, int size, int kol, long long int dol, long long int hor, char prikaz)
{
    long long int temp;
    int op = size % 2 == 0 ? size / 2 : size / 2 + 1; // pocet vsech operaci
    for(int i = 0; i < soustava; i++)
    {
        if(size > 1 && kol == 0 && i == 0) continue;
        cislo[kol] = i < 10 ? 48 + i : 97 + (i - 10);
        cislo[size - kol - 1] =  i < 10 ? 48 + i : 97 + (i - 10);
        if((kol + 1) != op) recursevariaton(cislo, soustava, size, kol + 1, dol, hor, prikaz);
        if((kol + 1) == op)
        {
            temp = prevod(cislo, soustava, size);
            if(temp > hor)
            {
                flag = 1;
                break;
            }
            else if(temp >= dol)
            {
                if(prikaz == 'l')
                {
                    printf("%lld = ", temp);
                    for (int i = 0; i < size; i++) 
                    {
                        printf("%c", cislo[i]);
                    }
                    printf(" (%d)\n", soustava);
                }
                else celkem++;
            }
        }
    }
    return;
}

int main()
{
    char prikaz;
    char *cislo = (char*)malloc(sizeof(char));
    int soustava;
    long long int dol, hor;
    int temp;
    printf("Vstupni intervaly:\n");
    while((temp = scanf(" %c %d %lld %lld", &prikaz, &soustava, &dol, &hor)) != EOF)
    {
        if(temp != 4 || (prikaz != 'l' && prikaz != 'c') || soustava < 2 || soustava > 36 || dol < 0 || dol > hor)
        {
            printf("Nespravny vstup.\n");
            return 0;
        }
        temp = 1;  // pocet cisel ve radku
        celkem = 0;
        flag = 0;
        while(1)
        {
            if(pow(soustava, temp) > dol) break;
            temp++;
        }
        while(1)
        {
            cislo = (char*)realloc(cislo, temp * sizeof(char));
            recursevariaton(cislo, soustava, temp, 0, dol, hor, prikaz);
            temp++;
            if(flag == 1) break;
        }
        if(prikaz == 'c') printf("Celkem: %d\n", celkem);
    }
    free(cislo);
    return 0;
}