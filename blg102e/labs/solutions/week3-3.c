#include <stdio.h>

float celcius_from_fahrenheit(float fahrenheit){
    float celciusvalue = 5.0 / 9.0 * (fahrenheit - 32.0);
    return celciusvalue;
}

int main(){
    printf("Enter temperature in Celcius or Fahrenheit with letter: ");
    float temperature = 0.0;
    char temp_type;
    float altitude = 0.0;
    scanf("%f %c",&temperature, &temp_type);
    printf("Enter altitude in meters: ");
    scanf("%f", &altitude);
    float celcius_temp = temperature;
    if(temp_type == 'F' || temp_type == 'f'){
        celcius_temp = celcius_from_fahrenheit(temperature);
    }
    else if(temp_type != 'C' && temp_type != 'c'){
        printf("Please enter C or F as letter.\n");
        return -1;
    }
    const float boiling_point = 100.0 - (altitude / 300.0);
    if(celcius_temp <= 0){
        printf("Water is solid at %.3f%c at %.3f meters\n",temperature, temp_type, altitude);
    }
    else if(celcius_temp > 0 && celcius_temp < boiling_point){
        printf("Water is liquid at %.3f%c at %.3f meters\n",temperature, temp_type, altitude);
    }
    else{
        printf("Water is gas at %.3f%c at %.3f meters\n",temperature, temp_type, altitude);
    }
    return 0;
}