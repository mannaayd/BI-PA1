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
    const double pi = 3.14159265;
    double arr1[3], arr2[3];
    arr1[0] = 1;
    arr1[1] = 1;
    arr1[2] = 1;
    arr2[0] = 1;
    arr2[1] = 1;
    arr2[2] = 1;
    char t11, t12, t13, t21, t22, t23;
    double a1 = 1, a2 = 1, a3 = 1, b1 = 1, b2 = 1, b3 = 1, temp = 1;
    int tmp;
    printf("Trojuhelnik #1:\n");
    tmp = scanf(" %c%c%c %lf %lf %lf", &t11, &t12, &t13, &a1, &a2, &a3);
    if(tmp != 6 || a1 <= 0 || a2 <= 0 || a3 <= 0 || (t11 == 'U' && a1 >= 180) || (t12 == 'U' && a2 >= 180) || (t13 == 'U' && a3 >= 180) || ((t11 != 'U' || t12 != 'S' || t13 != 'U') && (t11 != 'S' || t12 != 'U' || t13 != 'S') && (t11 != 'S' || t12 != 'S' || t13 != 'S')))
    {
        printf("Nespravny vstup.\n");
        return 0;
    }

    if(t11 == 'S' && t12 == 'S' && t13 == 'S')
    { 
        arr1[0] = a1; 
        arr1[1] = a2;
        arr1[2] = a3;
    }

    if(t11 == 'U' && t12 == 'S' && t13 == 'U')
    { 
        if((a1 + a3) >= 180)
        {
            printf("Vstup netvori trojuhelnik.\n");
            return 0;
        }
        temp = 180 - (a1 + a3);
        arr1[0] = a2;
        arr1[1] = (arr1[0] * sin((a1 * pi)/180))/sin((temp * pi) / 180);
        arr1[2] = (arr1[0] * sin((a3 * pi)/180))/sin((temp * pi) / 180);
    }

    if(t11 == 'S' && t12 == 'U' && t13 == 'S')
    { 
        arr1[0] = a1;
        arr1[1] = a3;
        arr1[2] = sqrt(pow(arr1[0], 2) + pow(arr1[1], 2) - (2 * arr1[0] * arr1[1] * cos((a2 * pi) / 180)));
    }

    if (fabs(arr1[0]-(arr1[1]+arr1[2])) <= 16* DBL_EPSILON * fmax(fabs(arr1[0]),fabs(arr1[1])) || fabs(arr1[1]-(arr1[0]+arr1[2])) <= 16* DBL_EPSILON * fmax(fabs(arr1[0]),fabs(arr1[1])) || fabs(arr1[2]-(arr1[1]+arr1[0])) <= 16* DBL_EPSILON * fmax(fabs(arr1[2]),fabs(arr1[1]))) {
        printf("Vstup netvori trojuhelnik.\n");
        return 0;
    } else if (arr1[0]-(arr1[1]+arr1[2]) >= 16* DBL_EPSILON * fmax(fabs(arr1[0]),fabs(arr1[1])) || arr1[1]-(arr1[0]+arr1[2]) >= 16* DBL_EPSILON * fmax(fabs(arr1[0]),fabs(arr1[1])) || arr1[2]-(arr1[1]+arr1[0]) >= 16* DBL_EPSILON * fmax(fabs(arr1[2]),fabs(arr1[1]))) {
        printf("Vstup netvori trojuhelnik.\n");
        return 0;
    } 

    printf("Trojuhelnik #2:\n");
    tmp = scanf(" %c%c%c %lf %lf %lf", &t21, &t22, &t23, &b1, &b2, &b3);
    if(tmp != 6 || b1 <= 0 || b2 <= 0 || b3 <= 0 || (t21 == 'U' && b1 >= 180) || (t22 == 'U' && b2 >= 180) || (t23 == 'U' && b3 >= 180) || ((t21 != 'U' || t22 != 'S' || t23 != 'U') && (t21 != 'S' || t22 != 'U' || t23 != 'S') && (t21 != 'S' || t22 != 'S' || t23 != 'S')))
    {
        printf("Nespravny vstup.\n");
        return 0;
    }

    if(t21 == 'S' && t22 == 'S' && t23 == 'S')
    { 
        arr2[0] = b1; 
        arr2[1] = b2;
        arr2[2] = b3;
    }

    if(t21 == 'U' && t22 == 'S' && t23 == 'U')
    { 
        temp = 180 - (b1 + b3);
        arr2[0] = b2;
        arr2[1] = (arr2[0] * sin((b1 * pi) / 180))/sin((temp * pi)/180);
        arr2[2] = (arr2[0] * sin((b3 * pi) / 180))/sin((temp * pi)/180);
    }

    if(t21 == 'S' && t22 == 'U' && t23 == 'S')
    { 
        arr2[0] = b1;
        arr2[1] = b3;
        arr2[2] = sqrt(arr2[0] * arr2[0] + arr2[1] * arr2[1] - (2 * arr2[0] * arr2[1] * cos((b2 * pi)/180)));
    }
    if (fabs(arr2[0]-(arr2[1]+arr2[2])) <= 16* DBL_EPSILON * fmax(fabs(arr2[0]),fabs(arr2[1])) || fabs(arr2[1]-(arr2[0]+arr2[2])) <= 16* DBL_EPSILON * fmax(fabs(arr2[0]),fabs(arr2[1])) || fabs(arr2[2]-(arr2[1]+arr2[0])) <= 16* DBL_EPSILON * fmax(fabs(arr2[2]),fabs(arr2[1]))) {
        printf("Vstup netvori trojuhelnik.\n");
        return 0;
    } else if (arr2[0]-(arr2[1]+arr2[2]) >= 16* DBL_EPSILON * fmax(fabs(arr2[0]),fabs(arr2[1])) || arr2[1]-(arr2[0]+arr2[2]) >= 16* DBL_EPSILON * fmax(fabs(arr2[0]),fabs(arr2[1])) || arr2[2]-(arr2[1]+arr2[0]) >= 16* DBL_EPSILON * fmax(fabs(arr2[2]),fabs(arr2[1]))) {
        printf("Vstup netvori trojuhelnik.\n");
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