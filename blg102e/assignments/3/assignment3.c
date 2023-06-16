#include <stdio.h>

struct candidate {
	char letter;
	int votes;
	float percent;
};

typedef struct candidate candidate;

void sortCandidates(candidate* const candidates){   // the function that sorts the candidates in descending order of their votes.
	for(int i = 0; i < 4; i++){
		for(int j = i + 1; j < 4; j++){
			if(candidates[i].percent < candidates[j].percent){
				candidate tempCandidate = candidates[i];
				candidates[i] = candidates[j];
				candidates[j] = tempCandidate;
			}
		}
	}
}

void printResult(candidate* const candidates){    // the function that prints the election result.
	sortCandidates(candidates);    // sorting the candidates, so that the first candidate in the array is guaranteed to be the most voted one.
	if(candidates[0].percent > 50.0){
		printf("Winner: %c\n", candidates[0].letter);
	} else{
		printf("Second round: %c and %c\n", candidates[0].letter, candidates[1].letter);
	}
}

void calculatePercentages(candidate* const candidates){    // the function that calculates the percentage of each candidate and assigns the corresponding values in the structures.
	int totalVotes = 0;
	for(int i = 0; i < 4; i++){    // the loop that calculates the total vote count.
		totalVotes += candidates[i].votes;
	}
	
	for(int i = 0; i < 4; i++){    // the loop that calculates the percentage of each candidate.
		candidates[i].percent = (candidates[i].votes * 100.0) / totalVotes;
	}
}

void readVoteData(const char* fileName, candidate* const candidates){    // the function that reads the text data and writes it to the candidate structures.
	FILE* filePointer = fopen(fileName, "r");    // opening the stream.
	char lineStr[85];    // a static array that represents the line as a string for each iteration.
	while(fgets(lineStr, 85, filePointer) != NULL){    // the loop that iterates through the lines.
		int a, b, c, d;
		sscanf(lineStr, "%d %d %d %d", &a, &b, &c, &d);    // getting 4 integer values in the current line.
		
		// adding new votes to structures.
		candidates[0].votes += a;
		candidates[1].votes += b;
		candidates[2].votes += c;
		candidates[3].votes += d;
	}
	fclose(filePointer);    // closing the stream.
}

void initCandidates(candidate* const candidates){    // the function that assigns the initial values to the candidate structures.
	for(int i = 0; i < 4; i++){
		candidate tempCandidate = {65 + i, 0, 0};    // 65 is the character 'A' in ASCII.
		candidates[i] = tempCandidate;
	}
}

int main(const int argc, const char* const* argv){
	candidate candidates[4];    // the candidate array.
	initCandidates(candidates);    // assigning the letters to the candidates.
	readVoteData(argv[1], candidates);    // reading the text data whose name is passed as an argument.
	calculatePercentages(candidates);    // calculating the percentage of each candidate.
	printResult(candidates);    // printing the election result.
	return 0;
}