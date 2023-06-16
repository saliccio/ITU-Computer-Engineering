#include <stdio.h>

long factorial(int number){
	long result = 1;
	for(int i = number; i > 0; i--){
		result = result * i;
	}
	return result;
}

long combination(int n, int r){
	long result = 1;
	for(int i = n; i > n-r; i--){
		result = result * i;
	}
	result = result / factorial(r);
    return result;
}

int main(){
	int n = 0;
	scanf("%d", &n);
	int r = 0;
	scanf("%d", &r);
	printf("%ld",combination(n,r));
	return 0;
}