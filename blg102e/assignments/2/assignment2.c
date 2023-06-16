#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// global variables
int g_rowCount;
int g_seatPerRow;
int g_aisleCount;
int *g_aislePositions;

enum CellStatus {NotReserved, JustReserved, BeforeReserved};  // enum to hold cell status
enum CellStatus **g_cellsData; // 2d array that stores the states of cells.

// initialization function that takes values to create layout.
void layoutInitialization(){
	printf("Number of rows:");
	scanf("%d", &g_rowCount);
	
	printf("Number of seats per row:");
	scanf("%d", &g_seatPerRow);
	
	printf("Number of aisles:");
	scanf("%d", &g_aisleCount);
	
	g_aislePositions = malloc(sizeof(int) * (g_aisleCount));
	for(int i = 1; i < g_aisleCount + 1; i++){
		printf("Add aisle %d after seat:", i);
		scanf("%d", &(g_aislePositions[i - 1]));
	}
}

// function that prints the current layout
void printLayout(){
	// columns
	printf("  ");
	int aisleIndex = 0;
	for(int i = 65; i < 65 + g_seatPerRow; i++){
		if(aisleIndex < g_aisleCount && g_aislePositions[aisleIndex] == i - 65){
			printf(" | |");
			aisleIndex++;
			i--;
			continue;
		}
		printf(" %c", i);
	}
	
	//rows
	for(int y = 0; y < g_rowCount; y++){
		printf(" \n%d ", y + 1);
		aisleIndex = 0;
		for(int x = 0; x < g_seatPerRow; x++){
			if(aisleIndex < g_aisleCount && g_aislePositions[aisleIndex] == x){
				printf(" | |");
				aisleIndex++;
				x--;
				continue;
			}
			
			enum CellStatus cellData = g_cellsData[x][y];
			char charToPrint;
			switch(cellData){
				case NotReserved:
				charToPrint = '-';
				break;
				case JustReserved:
				charToPrint = '+';
				break;
				case BeforeReserved:
				charToPrint = 'X';
				break;
			}
			printf(" %c", charToPrint);
		}
	}
	printf("\n");
}

// distance function
double calculateDistance(int x1, int y1, int x2, int y2){
	int xAdditive = 0;
	for(int i = 0; i < g_aisleCount; i++){ // taking aisles into account
		int aislePosition = g_aislePositions[i];
		if((aislePosition > x1 && aislePosition <= x2) || (aislePosition > x2 && aislePosition <= x1)){
			xAdditive++;
		}
	}
	return  abs(y1 - y2) + ((xAdditive + abs(x1 - x2)) / 2.0);
}

// adjusted distance function
double calculateAdjustedDistance(double distance){
	if(distance == 0.0){
		return 0.0;
	}
	double value = 100.0 - pow(100.0, 1.0 / distance);
	value = value * 100000;
	value = value / 100000.0;   // truncating redundant double digits.
	return value;
}

// function that calculates a seat's score
double calculateSeatScore(int seatX, int seatY){
	double score = 0.0;
	for(int x = 0; x < g_seatPerRow; x++){
		for(int y = 0; y < g_rowCount; y++){
			enum CellStatus currentCell = g_cellsData[x][y];
			if((x == seatX && y == seatY) || currentCell == NotReserved){
				continue;
			}
			score += calculateAdjustedDistance(calculateDistance(x, y, seatX, seatY));
		}
	}
	return score;
}

// function that calculates seat block's score
double calculateSeatBlockScore(int seatCount, int startX, int startY){
	double score = 0.0;
	for(int i = 0; i < seatCount; i++){
		score += calculateSeatScore(startX + i, startY);
	}
	return score;
}

// function that returns the aisle count in a seat block
int getSeatBlockAisleCount(int startX, int endX){
	int count = 0;
	for(int i = 0; i < g_aisleCount; i++){
		int hasLeftOfAisle = 0;
		int hasRightOfAisle = 0;
		for(int j = startX; j < endX + 1; j++){
			int relative = j - g_aislePositions[i];
			if(relative < 0){
				hasLeftOfAisle = 1;
			}
			else if(relative >= 0){
				hasRightOfAisle = 1;
			}
			if(hasLeftOfAisle && hasRightOfAisle){
				count++;
				break;
			}
		}
	}
	return count;
}

// function that returns the optimal seat block for family reservations.
void findSeatBlockStart(int seatCount, int *returnX, int *returnY){
	if(seatCount > g_seatPerRow){
		*returnX = -1;
		return;
	}
	double maxScore = -999999.0;
	int bestX = -1;
	int bestY = -1;
	int lastMaxAisleCount = 0;
	for(int y = g_rowCount - 1; y >= 0; y--){
		for(int x = g_seatPerRow - seatCount; x >= 0; x--){
			int seatExistsInInterval = 0;
			for(int i = x; i < x + seatCount; i++){
				if(g_cellsData[i][y] != NotReserved){
					seatExistsInInterval = 1;
					break;
				}
			}
			if(seatExistsInInterval){
				continue;
			}
			double score = calculateSeatBlockScore(seatCount, x, y);
			int aisleCount = getSeatBlockAisleCount(x, x + seatCount - 1);
			if(score > maxScore){
				maxScore = score;
				bestX = x;
				bestY = y;
				lastMaxAisleCount = aisleCount;
			}
			else if(score == maxScore){
				if(aisleCount < lastMaxAisleCount){
					maxScore = score;
					bestX = x;
					bestY = y;
					lastMaxAisleCount = aisleCount;
				}
				else if(aisleCount == lastMaxAisleCount){
					if(y < bestY){
						maxScore = score;
						bestX = x;
						bestY = y;
						lastMaxAisleCount = aisleCount;
					}
					else if(y == bestY){
						if(x < bestX){
							maxScore = score;
							bestX = x;
							bestY = y;
							lastMaxAisleCount = aisleCount;
						}
					}
				}
			}
		}
	}
	
	*returnX = bestX;
	*returnY = bestY;
}

// function that makes a reservation
int setReservation(int reservationCount){
	
	// family reservation
	if(reservationCount > 1){
		int x;
		int y;
		findSeatBlockStart(reservationCount, &x, &y);
		if(x == -1){
			return 0;
		}
		for(int i = x; i < x + reservationCount; i++){
			g_cellsData[i][y] = JustReserved;
		}
		return 1;
	}
	
	// single reservation
	double maxScore = -999999;
	int targetX = -1;
	int targetY = -1;
	for(int y = g_rowCount - 1; y >= 0; y--){
		for(int x = g_seatPerRow - 1; x >= 0; x--){
			if(g_cellsData[x][y] != NotReserved){
				continue;
			}
			double score = calculateSeatScore(x, y);
			if(score > maxScore){
				maxScore = score;
				targetX = x;
				targetY = y;
			}
			else if(score == maxScore){
				if(y < targetY){
					maxScore = score;
					targetX = x;
					targetY = y;
				}
				else if(y == targetY){
					if(x < targetX){
						maxScore = score;
						targetX = x;
						targetY = y;
					}
				}
			}
		}
	}
	if(targetX != -1){ // if a seat is found
		g_cellsData[targetX][targetY] = JustReserved;
		return 1;
	}
	else{
		return 0;
	}
}

// function that converts '+' characters to 'X' characters in the layout.
void convertOldSeats(){
    for(int x = 0; x < g_seatPerRow; x++){
		for(int y = 0; y < g_rowCount; y++){
			if(g_cellsData[x][y] == JustReserved){
				g_cellsData[x][y] = BeforeReserved;
			}
		}
	}
}

// function that prints the reserved seats.
void printReservedSeats(){
	for(int x = 0; x < g_seatPerRow; x++){
		for(int y = 0; y < g_rowCount; y++){
			if(g_cellsData[x][y] == JustReserved){
				printf(" %d%c", (y + 1), (65 + x));
			}
		}
	}
	printf("\n");
}

// function that is responsible to get input.
void processInput(){
	while(1){
		printf("\nThe number of people in the reservation\n (0: print current reservations, -1: exit):");
		int input;
		scanf("%d", &input);
		if(input == -1){
			break;
		}
		else if(input == 0){
			printLayout();
		}
		else if (input > 0){
			int result = setReservation(input);
			if(result){
				printf("Reserved seats:");
				printReservedSeats();
				printLayout();
			}
			else{
				printf("\nNo available seats for the requested reservation!\n");
			}
		}
		convertOldSeats();
	}
}

// calling necessary functions in the main function
int main(){
	layoutInitialization();
	g_cellsData = malloc(sizeof(enum CellStatus*) * g_seatPerRow);
	for(int x = 0; x < g_seatPerRow; x++){
		g_cellsData[x] = malloc(sizeof(enum CellStatus) * g_rowCount);
		for(int y = 0; y < g_rowCount; y++){
			g_cellsData[x][y] = NotReserved;
		}
	}
	printLayout();
	processInput();
	return 0;
}