#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main()
{
    int sloupcu = 0, radku = 1, sloupcudo = 0;
    char tmp;
    int flag = 0;
    char **arr = NULL;
    arr = (char**)realloc(arr, sizeof(char*) * radku);
    arr[0] = NULL;
    int kontrola;
    printf("Zadejte hraci plochu:\n");
    while(1)
    {
        //radku++;
        if((kontrola = scanf("%c", &tmp)) == EOF){
            if(radku == 1)
            {
                printf("Nespravny vstup.\n");
                for(int c = 0; c < radku; c++)
                {
                    free(arr[c]);
                }
                free(arr);
                return 0;
            }
            break;
        }
        if(kontrola != 1 || (tmp != '.' && tmp != '*' && tmp != '\n'))
        {
            printf("Nespravny vstup.\n");
            for(int c = 0; c < radku; c++)
            {
                free(arr[c]);
            }
            free(arr);
            return 0;
        }
        if(tmp == '\n')
        {
            if(flag && sloupcu != sloupcudo)
            {
                printf("Nespravny vstup.\n");
                for(int c = 0; c < radku; c++)
                {
                    free(arr[c]);
                }
                free(arr);
                return 0;
            }
            flag = 1;
            radku++;
            sloupcudo = sloupcu;
            sloupcu = 0;
            arr = (char**)realloc(arr, sizeof(char*) * radku);
            arr[radku - 1] = NULL;
        }
        else
        {
            sloupcu++;
            arr[radku-1] = (char*)realloc(arr[radku-1], sloupcu * sizeof(char));
            arr[radku-1][sloupcu - 1] = tmp;
        }
    }
    printf("Vyplnena hraci plocha:\n");
    int pocet_min;
    for(int i = 0; i < radku - 1; i++)
    {
        for(int c = 0; c < sloupcudo; c++)
        {
            pocet_min = 0;
            if(arr[i][c] == '*')
            {
                printf("*");
                continue;
            }

            if(i + 1 < radku - 1)                       if(arr[i+1][c] == '*') pocet_min++;
            if(i + 1 < radku - 1 && c + 1 < sloupcudo)  if(arr[i+1][c+1] == '*') pocet_min++;
            if(c + 1 < sloupcudo)                       if(arr[i][c+1] == '*') pocet_min++;
            if(c + 1 < sloupcudo && i - 1 >= 0)          if(arr[i-1][c+1] == '*') pocet_min++;
            if(i - 1 >= 0)                               if(arr[i-1][c] == '*') pocet_min++;
            if(c - 1 >= 0)
            {
                if(arr[i][c-1] == '*') pocet_min++;
                if(i - 1 >= 0) if(arr[i-1][c-1] == '*') pocet_min++;
                if(i + 1 < radku - 1)  if(arr[i+1][c-1] == '*') pocet_min++;
            }
            if(pocet_min == 0) printf(".");
            else printf("%d", pocet_min);
        }
        printf("\n");
    }
    for(int c = 0; c < radku - 1; c++)
    {
        free(arr[c]);
    }
    free(arr);
    return 0;
}