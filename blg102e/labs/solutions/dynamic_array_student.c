#include <assert.h>
#include <ctype.h>
#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

 
void arrayAppend(int** sourceArr, int* arrSize, int value){
	*sourceArr = realloc(*sourceArr,sizeof(int) * ((*arrSize) + 1));
	(*sourceArr)[*arrSize] = value;
	*arrSize = *arrSize + 1;
}
 
int* dynamicArray(int n, int queries_rows, int queries_columns, int** queries, int* result_count) {
	int **array = malloc(sizeof(int*) * n);
	int *lastAnswerVariables = malloc(sizeof(int));
	int lastAnswer = 0;
	int* subArraySizes = malloc(sizeof(int) * n);
	
	for(int i = 0; i < queries_rows; i++){
		int type = queries[i][0];
		int x = queries[i][1];
		int y = queries[i][2];
		
		
		int idx = (x^lastAnswer) % n;
		switch(type){
			case 1:
			arrayAppend(&(array[idx]), &(subArraySizes[idx]), y);
			break;
			
			case 2:
			lastAnswer = array[idx][y % (subArraySizes[idx])];
			arrayAppend(&lastAnswerVariables, result_count, lastAnswer);
			break;
		}
	}
	free(array);
	array = NULL;
	free(subArraySizes);
	subArraySizes = NULL;
	return lastAnswerVariables;
/*
Your function should:
    1) Create a 2-D array whose columns are appendable (dynamic)
    2) Create a 1-D dynamic array which will be used for storing the lastAnswer variables
    3) Handle 2 types of queries and fills in the aforementioned 2-D and 1-D arrays, based on the instructions
    4) Return the 1-D array and its size in the result_count variable
    5) Deletes the redundant variables which are created dynamically (by using malloc functions)
*/


}

int main()
{
    int n, q;
    scanf("%d %d", &n, &q);
    
    int** queries = malloc(q * sizeof(int*));
    
    for (int i = 0; i < q; i++) {
        *(queries + i) = malloc(3 * sizeof(int));
        scanf("%d %d %d", &queries[i][0], &queries[i][1], &queries[i][2]);
    }
    
    int result_count;
    int* result = dynamicArray(n, q, 3, queries, &result_count);
    
    for (int i = 0; i < result_count; i++){
        printf("%d", *(result + i));
        printf("\n");
    }
    
    free(result);
    result = NULL;
    return 0;
}

