#include <stdio.h>

int main()
{
    int player1_win_count = 0; // player 1's points
    int player2_win_count = 0; // player 2's points
    while (1) { // this infinite loop lets the user specify inputs until the game ends.
        if (player1_win_count - 2 >= player2_win_count && player1_win_count > 3) { // if player1 is above 3 points and above the rival by at least 2 points
            printf("GAME: PLAYER 1\n"); // print the winner to screen.
            break; // the game ended, our program must end as well, so we stop the loop.
        } else if (player2_win_count - 2 >= player1_win_count && player2_win_count > 3) { // if player2 is above 3 points and above the rival by at least 2 points
            printf("GAME: PLAYER 2\n"); // print the winner to screen.
            break; // the game ended, our program must end as well, so we stop the loop.
        }
        if (player1_win_count >= 3 && player2_win_count >= 3) { // this is a common statement for 3 situations, so instead of writing this 3 times, we write once.
            if (player1_win_count == player2_win_count) { // if their points are equal
                printf("DEUCE\n"); // print deuce to screen.
            } else if (player1_win_count - 1 == player2_win_count) { // if player1 is leading by one point
                printf("ADVANTAGE: PLAYER 1\n"); // print the advantage to screen.
            } else if (player2_win_count - 1 == player1_win_count) { // if player2 is leading by one point
                printf("ADVANTAGE: PLAYER 2\n"); // print the advantage to screen.
            }
        } else if (player1_win_count <= 3 && player2_win_count <= 3) { // if their points are equal or less than 3
            int score1 = 0; // score of player1
            int score2 = 0; // score of player2
			
            switch (player1_win_count) { // since we only have one variable, using switch is a better idea than using if.
            case 1:
                score1 = 15;
                break;
            case 2:
                score1 = 30;
                break;
            case 3:
                score1 = 40;
                break;
            } // we have converted player1's points to score.
			
			
            switch (player2_win_count) {
            case 1:
                score2 = 15;
                break;
            case 2:
                score2 = 30;
                break;
            case 3:
                score2 = 40;
                break;
            } // we have converted player2's points to score.
			
			
            printf("%d-%d\n", score1, score2); // print players' scores.
        }
        int winner = 0; // variable to get the winner of round from the user.
        printf("Point: ");
        scanf("%d", &winner); // get the input from the user.
        if (winner == 1) {
            player1_win_count++; // if the user specified 1, increase the point of player1's by 1.
        } else if (winner == 2) {
            player2_win_count++; // if the user specified 2, increase the point of player2's by 1.
        }
    }
    return 0; // we specify that our program ran successfully.
}