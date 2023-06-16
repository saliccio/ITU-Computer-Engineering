#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct word{
	char* data;
};
typedef struct word word;
struct sentence{
	word* data;
	int wordCount;
};
typedef struct sentence sentence;

struct paragraph{
	sentence* data;
	int sentenceCount;
};
typedef struct paragraph paragraph;

struct document{
	paragraph* data;
	int paragraphCount;
};
typedef struct document document;

void appendStringArray(char*** array, char* value, int* count){
	*array = realloc(array, sizeof(char*) * (*count + 1));
	(*array)[*count] = value;
	*count = *count + 1;
}

document get_document(char* data){
	int paragraphCount = 0;
	int i = 0;
	while((char c = data[i]) != '\0'){
		if(c == '\n'){
			paragraphCount++;
		}
		i++;
	}
}

paragraph kth_paragraph(document doc, int k){
	
}

sentence kth_sentence_in_mth_paragraph(document doc, int k, int m){
	return doc.data[m].data[k];
}

word kth_word_in_mth_sentence_of_nth_paragraph(document doc, int k, int m, int n){
	return doc.data[n].data[m].data[k];
}

int main(){
	document doc = get_document("Thinking of you is pretty hopeful.It is like listening to the most beautiful song from the most beautiful voice on earth.\nBut hope is not enough for me anymore.\nI don’t want to listen to songs anymore.I want to sing.");
	printf("Query Type : ");
	int type;
	scanf("%d", &type);
}