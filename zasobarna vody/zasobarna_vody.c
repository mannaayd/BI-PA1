#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
    int alt;
    int h;
    int sec;
}n;


int cmpfunci (const void * a, const void * b)
{
    const int *n1 = (int*)a;
    const int *n2 = (int*)b;
    return *n1 - *n2;
}

int main()
{
    int nadrz, tmp;
    int objem;
    printf("Zadejte pocet nadrzi:\n");
    tmp = scanf(" %d", &nadrz);
    if (tmp != 1 || nadrz <= 0 || nadrz > 200000)
    {
        printf("Nespravny vstup.\n");
        return 0;
    }
    int d, w;
    n *arr = (n*)malloc(nadrz*sizeof(n));
    printf("Zadejte parametry nadrzi:\n");
    for(int i = 0; i < nadrz; i++)
    {
        tmp = scanf(" %d %d %d %d", &arr[i].alt, &arr[i].h, &d, &w);
        arr[i].sec = d * w;
        if (tmp != 4 || arr[i].h <= 0 || w <= 0 || d <= 0)
        {
            printf("Nespravny vstup.\n");
            return 0;
        }
    }
    int *nums = (int*)malloc(sizeof(int) * 2 * nadrz);
    int *numsd = (int*)malloc(sizeof(int));
    tmp = 0;
    for(int i = 0; i < nadrz * 2; i+=2)
    {
        nums[i] = arr[tmp].alt;
        nums[i + 1] = arr[tmp].alt + arr[tmp].h;
        tmp++;
    }
    qsort(nums, nadrz * 2, sizeof(int), cmpfunci);
    int s = 0;
    int sec;
    double vyska;
    for(int i = 0; i < nadrz * 2; i++)
    {
        if(nums[i] == tmp && i != 0) continue;
        s++;
        numsd = (int*)realloc(numsd, sizeof(int)*s);
        numsd[s - 1] = nums[i];
        tmp = nums[i];
    }
    free(nums);
    printf("Zadejte objem vody:\n");
    while((tmp = scanf(" %d", &objem)) != EOF)
    {
        if(tmp != 1 || objem < 0 )
        {
            printf("Nespravny vstup.\n");
            return 0;
        }
        if(objem == 0)
        {
            printf("Prazdne.\n");
            continue;
        }
        tmp = 0;
        for(int i = 0; i < s - 1; i++)
        {
            sec = 0;
            for(int c = 0; c < nadrz; c++)
            {
                if(arr[c].alt <= numsd[i] && (arr[c].alt + arr[c].h) >= numsd[i+1])
                {
                    sec += arr[c].sec;
                }
            }
            if(sec * (numsd[i+1] - numsd[i]) < objem)
            {
                objem -= sec * (numsd[i + 1] - numsd[i]);
            }
            else
            {

                vyska = ((long double)objem/(long double)sec) + (long double)numsd[i];
                tmp = 1;
                break;
            }
        }
        if(tmp == 1)
        {
            printf("h = %.6lf\n", vyska);
        }
        else printf("Pretece.\n");
    } 
    free(arr);
    free(numsd);
    return 0;
}