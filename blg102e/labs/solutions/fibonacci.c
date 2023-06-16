#include <stdio.h>

long get_fibonacci(long index){
	if(index == 1){
		return 0;
	} else if(index == 2){
		return 1;
	}
	long i;
	long previous = 1;
	long previous2 = 0;
	long value=0;
	for(i = 3; i<= index; i++){
		value = previous + previous2;
		previous2 = previous;
		previous = value;
	}
	return value;
}

int main(){
	printf("Enter the index of the Fibonacci series\n");
	long index;
	scanf("%ld", &index);
	printf("%ld", get_fibonacci(index));
	return 0;
}