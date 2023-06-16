#include <stdio.h>

float celcius_from_fahrenheit(float fahrenheit){
    float celciusvalue = 5.0 / 9.0 * (fahrenheit - 32.0);
    return celciusvalue;
}

int main(){
    printf("Enter temperature in Celcius or Fahrenheit with letter: ");
    float temperature = 0.0;
    char temp_type;
    scanf("%f %c",&temperature, &temp_type);
    float celcius_temp = temperature;
    if(temp_type == 'F' || temp_type == 'f'){
        celcius_temp = celcius_from_fahrenheit(temperature);
    }
    else if(temp_type != 'C' && temp_type != 'c'){
        printf("Please enter C or F as letter.\n");
        return -1;
    }
    if(celcius_temp <= 0){
        printf("\nWater is solid at %.3f %c\n",temperature, temp_type);
    }
    else if(celcius_temp > 0 && celcius_temp < 100){
        printf("\nWater is liquid at %.3f %c\n",temperature, temp_type);
    }
    else{
        printf("\nWater is gas at %.3f %c\n",temperature, temp_type);
    }
    return 0;
}