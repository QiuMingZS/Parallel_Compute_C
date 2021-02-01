/* ******************************************************************************** */
/* Decription: To realize the function of bubble sort                               */
/* File Name: bubble_sort.c                                                         */
/* Last modified: 2021.01.25 21:15, Guanzheng Wang                                  */
/* ******************************************************************************** */
#include <stdio.h>

int main()
{
    float vec[10];
    float temp;
	printf("Hello, This is Bubble, \nPlease input 10 numbers to be sorted:\n");
    for (int i = 0; i < 10; i++)
    {
        scanf("%f", &vec[i]);
    }
	for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9 - i; j++)
        {
            if (vec[j] > vec[j+1])
            {
                temp = vec[j+1];
                vec[j+1] = vec[j];
                vec[j] = temp;
            }
        }
    }
	
	printf("Bubble sorted result: \n");
	for (int i = 0; i < 10; i++)
	{
		printf("%f ", vec[i]);
	}

    return 0;
}
