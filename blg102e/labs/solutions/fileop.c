#include <stdio.h>
#include <stdlib.h>

#define MAX_CHARACTERS 512

struct Student{
	char NAME[50];
	int ID;
	int EXAMS[3];
	int HWS[3];
	char LETTER_GRADE;
};

typedef struct Student Student;

void read_from_text_file(const char* const file_name, char* target){
	FILE* file = fopen(file_name, "r");
	if(file == NULL){
		exit(1);
	}
	int index = 0;
	char c;
	while(1){
		c = fgetc(file);
		if(feof(file)){
			break;
		}
		target[index] = c;
		index++;
	}
	fclose(file);
}

void write_into_binary_file(const char* const file_name, Student* value){
	FILE* file = fopen(file_name, "wb");
	if(file == NULL){
		exit(1);
	}
	fwrite(value, sizeof(Student), 1, file);
	fclose(file);
}

void read_from_binary_file(const char* const file_name, Student* target){
	FILE* file = fopen(file_name, "rb");
	if(file == NULL){
		exit(1);
	}
	fread(target, sizeof(Student), 1, file);
	fclose(file);
}

void write_into_text_file(const char* const file_name, const char* const value){
	FILE* file = fopen(file_name, "w");
	if(file == NULL){
		exit(1);
	}
	fputs(value, file);
	fclose(file);
}

int main(int argc, char* argv[]){
	char read_value[MAX_CHARACTERS];
	read_from_text_file(argv[1], read_value);
	printf("%s\n", read_value);
	Student student1 = {"name", 1, {70,50,80}, {100, 80, 70}, 'A'};
	write_into_binary_file(argv[2], &student1);
	Student student2;
	read_from_binary_file(argv[2], &student2);
	write_into_text_file(argv[3], "Furkan 2 100 100 100 100 100 100 A");
	return 0;
}