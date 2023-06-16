#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_STRING_SIZE 20

void substring(char* target, char* string, int start, int end){
	int i;
	int substrindex = 0;
	for(i = start; i < end; i++){
		target[substrindex] = string[i];
		substrindex++;
	}
}

void first(char* target, char* name, char* surname, char* date){
	char first_name[2];
	substring(first_name, name, 0, 1);
	first_name[1] = '\0';
	char surnames[3];
	substring(surnames, surname, 0, 2);
	surnames[2] = '\0';
	char dates[3];
	substring(dates, date, 2, 4);
	dates[2] = '\0';
	strcat(surnames, dates);
	strcat(first_name, surnames);
	strcpy(target, first_name);
}

int second(char* target, char* name, char* surname){
	char first_name[3];
	substring(first_name, name, 0, 2);
	first_name[2] = '\0';
	char surnames[3];
	substring(surnames, surname, 0, 2);
	surnames[2] = '\0';
	srand(time(NULL));
	strcat(first_name, surnames);
	int number = rand() % 9000 + 1000;
	strcpy(target, first_name);
	return number;
}

int main(){
	char name[MAX_STRING_SIZE];
	char surname[MAX_STRING_SIZE];
	char date[5];
	printf("Enter Your Name:");
	scanf("%s", name);
	printf("Enter Your Surname:");
	scanf(" %s", surname);
	printf("Enter Your Birthyear:");
	scanf(" %s", date);
	
	char firstemail[50];
	first(firstemail, name, surname, date);
	printf("Email Candidate 1: %s%s\n", firstemail, "@itu.edu.tr");
	char secondemail[50];
	int number = second(secondemail, name, surname);
	printf("Email Candidate 2: %s%d%s\n",secondemail, number, "@itu.edu.tr");
	printf("Email Candidate 3: %s%s%s%s\n",surname, name,date ,"@itu.edu.tr");
}