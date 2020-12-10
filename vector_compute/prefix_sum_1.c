/* ******************************************************************
A serial program to calculate the prefix sums

Wang Guanzheng, 2020.12.20 07:37
****************************************************************** */

#include <stdio.h>
#include <stdlib.h>

void main(){
    int num;
    double* vector;
    printf("Please input the length of the vector: \n");
    scanf("%d", &num);
    printf("Please input the vector: \n");
    vector = malloc(num*sizeof(double));
    for (int i=0; i<num; i++){
        scanf("%lf", &vector[i]);
    }

    for (int i=1; i<num; i++){
        vector[i] += vector[i-1];
    }

    printf("The prefix sum of the vector is: \n");
    for (int i=0; i<num; i++){
        printf("%f ", vector[i]);
    }
}