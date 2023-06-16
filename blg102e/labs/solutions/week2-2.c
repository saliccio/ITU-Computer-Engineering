#include <stdio.h>
#include <math.h>

int main(){
    printf("Enter the first coefficient: ");
    float a;
    scanf("%d",&a);
    printf("\nEnter the second coefficient: ");
    float b;
    scanf("%d",&b);
    printf("\nEnter the third coefficient: ");
    float c;
    scanf("%d",&c);
    float discriminant = (b * b) - (4.0 * a * c);
    float x1=((b * -1.0) + sqrt(discriminant)) / (2.0 * a);
    float x2=((b * -1.0) - sqrt(discriminant)) / (2.0 * a);
    printf("\nFirst root: %f\nSecond root: %f",x1,x2);
}