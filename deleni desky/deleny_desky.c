#include <stdio.h>


int error()
{
    printf("Nespravny vstup.\n");
    return 0;
}

int inputData(int *length, int *width, int *max_square)
{
    int check;
    printf("Velikost:\n");
    check = scanf(" %d %d", length, width);
    if(check != 2 || *length <= 0 || *width <= 0) return error();
    printf("Maximalni plocha:\n");
    check = scanf(" %d", max_square);
    if(check != 1 || *max_square <= 0) return error();
    return 1;
}

int findMinCuts(int square, int *max_square)
{
    return square % (*max_square) > 0 ? (square / (*max_square)) + 1 : (square / (*max_square));
}

int cutDeskRecursive(int length, int width, int *max_square, int state)
{
    int cuts = 0;
    int cuts_before;
    int swap;
    if(length < width)
    {
        swap = length;
        length = width;
        width = swap;
    }
    for(int i = 0; i < state; i++)
    {
        printf(" ");
    }
    printf("%d [%d , %d]\n", state, length, width);
    if(length * width > *max_square || (double)(length/width) > 2)
    {
        cuts++;
        state++;
        cuts_before = cuts;
        for(int i = length/2; i > 0; i--)
        {
            cuts += cutDeskRecursive(i, width, max_square, state);
            cuts += cutDeskRecursive(length - i, width, max_square, state);
            printf("cuts now %d\n", cuts);
            cuts = cuts_before;
        }
    }
    return cuts;
}

int main()
{
    int length, width, max_square, min_cuts;
    if(!inputData(&length, &width, &max_square)) return 0;
    max_square--;
    min_cuts = findMinCuts(length * width, &max_square);
    printf("Rezu = %d\n", min_cuts);
    
    return 0;
}