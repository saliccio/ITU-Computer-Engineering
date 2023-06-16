#include <stdio.h>
#include <stdlib.h>
 
#define ARRAY_SIZE 10
 
void swap(int *first, int*second){
    int i;
	for(i = 0; i < ARRAY_SIZE; i++){
		second[ARRAY_SIZE - 1 - i] = first[i];
	}
}

 
int main(){
	int x;
	scanf("%d", &x);
    int my_array[ARRAY_SIZE];
	int i;
    for(i=0; i<ARRAY_SIZE; i++){
		int entered_number;
		scanf("%d", &entered_number);
		my_array[i] = entered_number;
	}
    //random_fill_array(my_array);
     
    printf("ORIGINAL ARRAY: ");
	int j;
    for (j = 0; j < ARRAY_SIZE; printf("%-5d", my_array[j++]));
    printf("\n");
	
    int swapped_array[ARRAY_SIZE];
	swap(my_array, swapped_array);
 
    printf("REVERSE ARRAY:  ");
	int k;
    for (k = 0; k < ARRAY_SIZE; printf("%-5d", swapped_array[k++]));
    printf("\n");
 
    return EXIT_SUCCESS;
}
