#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct
{
    double x;
    double y;
    char *name;
} flight;

typedef struct
{
    int a;
    int b;
} pair;

int equal(double x, double y)
{
    return fabs(x - y) <= 16 * 0.000000001 * fmax(fabs(x), fabs(y)) ? 1 : 0;
}

void swap(double* a, double* b)
{
    double temp;
    temp = *(a);
    *(a) = *(b);
    *(b) = temp;
    return;
}

double range(double x1, double y1, double x2, double y2)
{
    if(x1 > x2) swap(&x1, &x2);
    if(y1 > y2) swap(&y1, &y2);
    return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
}

int main()
{
    flight *flights = (flight*)malloc(sizeof(flight));
    pair *list = (pair*)malloc(sizeof(pair));
    int count = 0;
    int flag = 0;
    double x, y;
    char tmp_char, tmp1, tmp2, tmp3;
    int tmp_int;
    printf("Zadejte lety:\n");
    while(!flag)
    {
        if(scanf(" %c", &tmp1) == EOF) break;
        if(tmp1 != '[')
        {
            printf("Nespravny vstup.\n");
            for(int i = 0; i < count; i++)
            {
                free(flights[i].name);
            }
            free(flights);
            free(list);
            return 0;
        }
        
        tmp_int = scanf(" %lf %c %lf %c", &x, &tmp2, &y, &tmp3);
        if(tmp_int != 4 || tmp3 != ']' || tmp2 != ',')
        {
            printf("Nespravny vstup.\n");
            for(int i = 0; i < count; i++)
            {
                free(flights[i].name);
            }
            free(flights);
            free(list);
            return 0;
        }
        count++;
        flights = (flight*)realloc(flights, count * sizeof(flight));
        flights[count - 1].x = x;
        flights[count - 1].y = y;
        flights[count - 1].name = (char*)malloc(sizeof(char));

        while(1)
        {
            scanf("%c", &tmp_char);
            if(tmp_char != ' ' && tmp_char != '\t') break;
            if(tmp_char == '\n')
            {
                printf("Nespravny vstup.\n");
                for(int i = 0; i < count; i++)
                {
                    free(flights[i].name);
                }
                free(flights);
                free(list);
                return 0;
            }
        }
        flights[count - 1].name[0] = tmp_char;
        tmp_int = 1;
        while(1)
        {
            tmp_int++;
            flights[count - 1].name = (char*)realloc(flights[count - 1].name, tmp_int * sizeof(char));
            if(scanf("%c", &tmp_char) == EOF)
            {
                flag = 1;
                flights[count - 1].name[tmp_int - 1] = '\0';
                break;
            }
            if(tmp_char == '\n')
            {
                flights[count - 1].name[tmp_int - 1] = '\0';
                break;
            }
            flights[count - 1].name[tmp_int - 1] = tmp_char;
        }
    }
    if(count < 2)
    {
        printf("Nespravny vstup.\n");
        for(int i = 0; i < count; i++)
        {
            free(flights[i].name);
        }
        free(flights);
        free(list);
        return 0;
    }
    tmp_int = 0;
    double min = range(flights[0].x, flights[0].y, flights[1].x, flights[1].y);
    for(int i = 0; i < count; i++)
    {
        if(i == count - 1) break;
        for(int c = i + 1; c < count; c++)
        {
            if(min > range(flights[i].x, flights[i].y, flights[c].x, flights[c].y))
            {
                min = range(flights[i].x, flights[i].y, flights[c].x, flights[c].y);
            }
        }
    }
    for(int i = 0; i < count; i++)
    {
        if(i == count - 1) break;
        for(int c = i + 1; c < count; c++)
        {
            if(equal(min, range(flights[i].x, flights[i].y, flights[c].x, flights[c].y)))
            {
                tmp_int++;
                list = (pair*)realloc(list, tmp_int * sizeof(pair));
                list[tmp_int - 1].a = i;
                list[tmp_int - 1].b = c;
            }
        }
    }
    printf("Nejmensi vzdalenost: %.6lf\n", min);
    for(int i = 0; i < tmp_int; i++)
    {
        printf("%s - %s\n", flights[list[i].a].name, flights[list[i].b].name);
    }
    for(int i = 0; i < count; i++)
    {
        free(flights[i].name);
    }
    free(list);
    free(flights);
    return 0;
}