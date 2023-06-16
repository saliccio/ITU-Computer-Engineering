#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

int main() 
{

    int n;
    scanf("%d", &n);
    int digitcount = 0;
    int result = 1;
    while (result >= 1) {
        result = n / (int)(pow(10, digitcount));
        if(result <1){
            break;
        }else{
            digitcount++;
        }
    }
  	char square[2*n-1][2*n-1][digitcount+1];
    for(int i = n;i>=1;i--){
        if(i>1){
        int start1,start2;
        start1 = n-i;
        start2 = (n-1)+(n-1)-start1;
        for(int x = start1;x<=start2;x++){
            for(int y = start1;y<=start2;y++){
                 sprintf(square[x][y],"%d",i);
            }
            }
        }
        else if(i==1){
            sprintf(square[n-1][n-1],"1");
        }
    }
    for(int i = 0;i<2*n-1;i++){
        for(int j = 0;j<2*n-1;j++){
            printf("%s ",square[i][j]);
        }
        printf("\n");
    }
    return 0;
}
