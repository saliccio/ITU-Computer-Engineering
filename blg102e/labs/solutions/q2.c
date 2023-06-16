#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_LEN 50

// represents a block of repeated characters
struct block {
    char c;   // the character that is repeated
    int num;  // the number of times the character is repeated
};

/**
 * Convert a phrase into its encoded form
 * and store the result in an array of blocks.
 *
 * @param p the phrase to encode
 * @param e the array where to store the result
 * @return the number of items in the resulting array
 */
int encode(const char *p, struct block *e)
{
	for(int i = 0; i < MAX_LEN; i++){
		e[i].num = 0;
	}
	
    int length = strlen(p);
	int uniqueCharIndex = 0;
	char lastChar = p[0];
	e[0].c = p[0];
	e[0].num++;
	for(int i = 1; i < length; i++){
		char currentChar = p[i];
		if(currentChar != lastChar){
			uniqueCharIndex++;
		}
		e[uniqueCharIndex].c = currentChar;
		e[uniqueCharIndex].num++;
		lastChar = currentChar;
	}
	return uniqueCharIndex + 1;
}

int main()
{
    // get the phrase to encode
    char phrase[MAX_LEN];
    printf("Phrase: ");
    scanf("%s", phrase);

    // encode the phrase
    struct block encoded[MAX_LEN];
    int n_blocks = encode(phrase, encoded);

    // print the encoded form
    for (int i = 0; i < n_blocks; i++) {
        if (i > 0) {
            printf(" ");
        }
        printf("%c:%d", encoded[i].c, encoded[i].num);
    }
    printf("\n");

    return EXIT_SUCCESS;
}
