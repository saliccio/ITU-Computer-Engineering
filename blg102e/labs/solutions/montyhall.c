#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(){
    int select_scenario = 0;
    int not_select_scenario = 0;
    int i = 1;
    srand(time(NULL));
    while(i <= 10000){
        int trophy_door = rand() % 3 + 1;
        int selected_door = rand() % 3 + 1;
        if(trophy_door == selected_door){
            not_select_scenario++;
        }
        else{
            select_scenario++;
        }
    i++;
    }
    printf("Win rate in change scenario: %f\n", select_scenario / 10000.0);
    printf("Win rate in not to change scenario: %f\n", not_select_scenario / 10000.0);
}