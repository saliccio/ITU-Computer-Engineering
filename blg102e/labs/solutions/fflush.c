#include <stdio.h>
#include <stdlib.h>

struct s{
	int a;
	char* b;
	float c;
};

typedef struct s s;

int main(){
	FILE *fp = fopen("fflushtxt", "a+b");
	s str;
	str.a = 0;
	str.b = "abc";
	str.c = 3.14;
	fwrite(&str, sizeof(s), 1, fp);
	fclose(fp);
}