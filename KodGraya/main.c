#include <stdio.h>
#include <stdlib.h>

void drukowanieTablicy(int tab[], int size){
    for(int k=0; k<size; k++){
        printf("%d", tab[k]);
    }
    printf("\n");
}

void kodGraya(int n){
    int temp[32];
    int i = 0, j = 0;
    while (n>0){
        temp[i] = n% 2;
        n = n/2;
        i++;
    }
    temp[i]=0;
    i++;
    int wynik[i];
    while (i>1){
        wynik[j] = temp[i-1]^temp[i-2];
        i--;
        j++;
    }
    drukowanieTablicy(wynik, j);
}

int main()
{
    kodGraya(1);
    return 0;
}
