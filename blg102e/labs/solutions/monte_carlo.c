#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int main(){
	while(1){
		printf("Enter iteration count: ");
		int iteration_count = 0;
		scanf("%d", &iteration_count);
		if(iteration_count <= 0){
			break;
		}
		srand(time(NULL));
		int inside_circle_count = 0;
		for(int i = 0; i < iteration_count; i++){
			float x = (((float)rand() / (float)(RAND_MAX)) * 2) - 1;
			float y = (((float)rand() / (float)(RAND_MAX)) * 2) - 1;
			if(x * x + y * y <= 1){
				inside_circle_count++;
			}
		}
		printf("Estimate value of pi is %lf for %d iterations.\n", (4.0 * (float)inside_circle_count) / (float)iteration_count, iteration_count);
	}
	return 1;
}