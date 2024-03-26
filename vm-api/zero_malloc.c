#include <stdlib.h>

int main()
{
    int *a = (int*)malloc(100 * sizeof(int));

    *a = 0;

    return 0;
}