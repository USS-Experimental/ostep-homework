#include <stdlib.h>
#include <stdio.h>

int main()
{
    int *a = (int*)malloc(100 * sizeof(int));

    a[1] = 1;

    free(a[1]);

    printf("%d\n", a[1]);

    //free(a);

    //printf("%d\n", a[0]);

    return 0;
}