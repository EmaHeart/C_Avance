#include <stdio.h>
#include <stdlib.h>




int main()
{
    int *tab;
    tab = (int*)malloc(5*sizeof(int));
    for(int i=0;i<5;i++)
    {
        scanf("%d", tab+i);
    }
    printf("************");
    for(int i=0;i<5;i++)
    {
        printf("%d", *(tab+i));
    }
    return 0;
}