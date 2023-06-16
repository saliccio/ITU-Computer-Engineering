#include <stdio.h>

int main(){
	printf("Number: ");
	int number = 0;
	scanf("%d", &number);
	printf("Digit: ");
	int digit = 0;
	scanf("%d", &digit);
	
	int tempNumber = number;
	while(tempNumber > 0){
		int lastDigit = tempNumber % 10;
		if(lastDigit == digit){
			printf("%d contains %d.\n", number, digit);
			return 0;
		}
		tempNumber /= 10;
	}
	printf("%d does not contain %d.\n", number, digit);
	return 0;
}