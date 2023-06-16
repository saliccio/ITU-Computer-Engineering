#include <stdio.h>

int main(){
	while(1){
		int number = 0;
		printf("Enter number: ");
		scanf("%d",&number);
		if(number <= 0){
			break;
		}
		int sum = 0;
		for(int i = 1; i < number; i++){
			if(number % i == 0){
				sum += i;
			}
		}
		if(number == sum){
			printf("%d is a perfect number.\n", number);
		}
		else{
			printf("%d is not a perfect number.\n", number);
		}
	}
	return 1;
}