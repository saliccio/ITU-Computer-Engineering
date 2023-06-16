#include <conio.h>
#include <stdio.h>

int main(){
    printf("Enter fahrenheit value: ");
    float value=0;
    scanf("%f",&value); //ask for fahrenheit
    float celciusvalue=0;
    celciusvalue = 5.0 / 9.0 * (value - 32.0);	//convert
    printf("\nCelcius value of %.1fF is %.1f",value,celciusvalue); //print the final value
    getch();
}