#include <stdio.h>
#include <stdlib.h>

int main(){
	int array_size;
	int query_count;
	int* array = malloc(sizeof(int) * array_size);
	for(int i = 0; i < array_size; i++){
		array[i] = 0;
	}
	scanf("%d %d", &array_size, &query_count);
	for(int i = 0; i < query_count; i++){
		int a,b,c;
		scanf("%d %d %d", &a, &b, &c);
		for(int j = a; j <= b; j++){
			array[j] += c;
		}
	}
	int max = array[0];
	for(int i = 1; i < array_size; i++){
		if(array[i] > max){
			max = array[i];
		}
	}
	printf("%d", max);
	return 0;
}