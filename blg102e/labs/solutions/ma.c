#include <stdio.h>
#include <stdlib.h>

int main(){
	int size;
	int start_point;
	scanf ("%d %d", &size, &start_point);
	int cumulative_sum = 0;
	int* arr = malloc(sizeof(int) * size);
	for(int i = 1; i <= size; i++){
		int number = 0;
		scanf("%d", &number);
		if(i < start_point){
			arr[i - 1] = 0;
		} else{
		arr[i - 1] = number;
		}
		cumulative_sum += number;
		printf("%.3lf ", (double)cumulative_sum / i);
	}
	printf("\n");
	for(int i = 1; i <= size; i++){
		if(i < start_point){
			printf("%.3lf ",0.000);
			continue;
		}
		int sum = 0;
		for(int j = 0; j < start_point; j++){
			sum += arr[i + j - 1];
		}
		printf("%.3lf ", (double)(sum) / (start_point));
	}
	printf("\n");
	return 0;
}