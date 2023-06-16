#include <stdio.h>
#include <math.h>

float calculate_bsa(float height, float weight){
    return (0.0003207 * pow(height,0.3) * pow(weight,(0.7285-(0.0188 * log10(weight)))));
}

int main(){
    int height; // cm
    int weight; // gr
    printf("Please enter height in cm: ");
    scanf("%d",&height);
    printf("\nPlease enter weight in gr: ");
    scanf("%d",&weight);
    printf("\nBSA is %.5f meter square\n",calculate_bsa((float)height,(float)weight));
}
