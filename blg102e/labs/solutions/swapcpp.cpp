#include <stdio.h>

void swap(int* val1, int* val2){
	int temp = *val1;
	*val1 = *val2;
	*val2 = temp;
}

void swapR(int& val1, int& val2){
	int temp = val1;
	val1 = val2;
	val2 = temp;
}

int main(){
	int x = 10;
	int y = 45;
	
	swap(&x, &y);
	
	printf("x = %d \n", x);
	printf("y = %d \n", y);
	
	swapR(x, y);
	
	printf("x = %d \n", x);
	printf("y = %d \n", y);
	
	return 0;
}