#include <stdio.h>

int min_of_four(int a, int b, int c, int d){
	int array[] = {b,c,d};
	int current_min = a;
	int i = 0;
	for(i = 0; i < 3; i++){
		if(array[i] < current_min){
			current_min = array[i];
		}
	}
	return current_min;
}

int main(){
	printf("Enter the numbers\n");
	int a,b,c,d;
	scanf("%d %d %d %d", &a, &b, &c, &d);
	printf("%d\n", min_of_four(a,b,c,d));
	return 0;
}