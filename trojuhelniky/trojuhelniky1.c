#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <float.h>

int cmpfunc (const void * a, const void * b)
{
  if (*(double*)a > *(double*)b)
    return 1;
  else if (*(double*)a < *(double*)b)
    return -1;
  else
    return 0;  
}

int main()
{
    double arr1[3], arr2[3];
    arr1[0] = 1;
    arr1[1] = 1;
    arr1[2] = 1;
    arr2[0] = 1;
    arr2[1] = 1;
    arr2[2] = 1;
    double a1 = 1, a2 = 1, a3 = 1, b1 = 1, b2 = 1, b3 = 1;
    int tmp;
    printf("Trojuhelnik #1:\n");
    tmp = scanf(" %lf %lf %lf", &a1, &a2, &a3);
    if(tmp != 3 || a1 <= 0 || a2 <= 0 || a3 <= 0)
    {
        printf("Nespravny vstup.\n");
        return 0;
    }

        arr1[0] = a1; 
        arr1[1] = a2;
        arr1[2] = a3;



    if (fabs(arr1[0]-(arr1[1]+arr1[2])) <= 16* DBL_EPSILON * fmax(fabs(arr1[0]),fabs(arr1[1])) || fabs(arr1[1]-(arr1[0]+arr1[2])) <= 16* DBL_EPSILON * fmax(fabs(arr1[0]),fabs(arr1[1])) || fabs(arr1[2]-(arr1[1]+arr1[0])) <= 16* DBL_EPSILON * fmax(fabs(arr1[2]),fabs(arr1[1]))) {
        printf("Strany netvori trojuhelnik.\n");
        return 0;
    } else if (arr1[0]-(arr1[1]+arr1[2]) >= 16* DBL_EPSILON * fmax(fabs(arr1[0]),fabs(arr1[1])) || arr1[1]-(arr1[0]+arr1[2]) >= 16* DBL_EPSILON * fmax(fabs(arr1[0]),fabs(arr1[1])) || arr1[2]-(arr1[1]+arr1[0]) >= 16* DBL_EPSILON * fmax(fabs(arr1[2]),fabs(arr1[1]))) {
        printf("Strany netvori trojuhelnik.\n");
        return 0;
    } 

    printf("Trojuhelnik #2:\n");
    tmp = scanf(" %lf %lf %lf", &b1, &b2, &b3);
    if(tmp != 3 || b1 <= 0 || b2 <= 0 || b3 <= 0)
    {
        printf("Nespravny vstup.\n");
        return 0;
    }

        arr2[0] = b1; 
        arr2[1] = b2;
        arr2[2] = b3;

    if (fabs(arr2[0]-(arr2[1]+arr2[2])) <= 16* DBL_EPSILON * fmax(fabs(arr2[0]),fabs(arr2[1])) || fabs(arr2[1]-(arr2[0]+arr2[2])) <= 16* DBL_EPSILON * fmax(fabs(arr2[0]),fabs(arr2[1])) || fabs(arr2[2]-(arr2[1]+arr2[0])) <= 16* DBL_EPSILON * fmax(fabs(arr2[2]),fabs(arr2[1]))) {
        printf("Strany netvori trojuhelnik.\n");
        return 0;
    } else if (arr2[0]-(arr2[1]+arr2[2]) >= 16* DBL_EPSILON * fmax(fabs(arr2[0]),fabs(arr2[1])) || arr2[1]-(arr2[0]+arr2[2]) >= 16* DBL_EPSILON * fmax(fabs(arr2[0]),fabs(arr2[1])) || arr2[2]-(arr2[1]+arr2[0]) >= 16* DBL_EPSILON * fmax(fabs(arr2[2]),fabs(arr2[1]))) {
        printf("Strany netvori trojuhelnik.\n");
        return 0;
    } 

    qsort(arr1, 3, sizeof(double), cmpfunc);
    qsort(arr2, 3, sizeof(double), cmpfunc);

    if(fabs(arr1[0]/arr2[0] - arr1[1]/arr2[1]) <= 16 * 0.000000001 * fmax(fabs(arr1[0]/arr2[0]), fabs(arr1[1]/arr2[1])) && fabs(arr1[0]/arr2[0] - arr1[2]/arr2[2]) < 16 * 0.000000001 * fmax(fabs(arr1[0]/arr2[0]), fabs(arr1[2]/arr2[2])))
    {
        if(fabs(arr1[0] - arr2[0]) < 16 * 0.000000001 * fmax( fabs(arr1[0]), fabs(arr2[0])) && fabs(arr1[1] - arr2[1]) < 16 * 0.000000001 * fmax(fabs(arr1[1]), fabs(arr2[1])) && fabs(arr1[2] - arr2[2]) < 16 * 0.000000001 * fmax(fabs(arr1[2]), fabs(arr2[2])))
        {
           printf("Trojuhelniky jsou shodne.\n");
        }
        else 
        {
            printf("Trojuhelniky nejsou shodne, ale jsou podobne.\n");
        }
    }
    else 
    {
        printf("Trojuhelniky nejsou shodne ani podobne.\n");
    }
    return 0;
}