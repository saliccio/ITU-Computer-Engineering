#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(){
    int i = 0;
    srand(time(NULL));
    int win_count = 0;
    while(i < 100000){
        int sum = rand() % 6 + 1 + (rand() % 6 + 1);
        if(sum == 7 || sum == 11){
            win_count++;
        }
        else if(sum == 4 || sum == 5 || sum == 6 || sum == 8 || sum == 9 || sum == 10){
            int new_dice_sum = 0;
            while(new_dice_sum != 7 && new_dice_sum != sum){
                new_dice_sum = rand() % 6 + 1 + (rand() % 6 + 1);
                if(new_dice_sum == sum){
                    win_count++;
                }
            }
        }
        i++;
    }
    float win_rate = win_count / 100000.0;
    char* text;
    if(win_rate >= 0.5){
        text = "sense";
    }
    else{
        text = "no sense";
    }
    printf("Win rate is %f, so playing this game makes %s\n", win_rate, text);
}