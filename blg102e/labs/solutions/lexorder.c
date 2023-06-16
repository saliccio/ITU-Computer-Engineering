#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

int arr_contains_char(const char* arr, const char* ch, int arr_size){
    for(int i = 0;i<arr_size;i++){
        if(strcmp(&arr[i],ch) == 0){
            return 1;
        }
    }
    return 0;
}

int lexicographic_sort(const char* a, const char* b) {
    int boolvalue = strcmp(a,b);
    if(boolvalue < 0){
        boolvalue = 0;
    }
    return boolvalue;
}

int lexicographic_sort_reverse(const char* a, const char* b) {
    int boolvalue = strcmp(b,a);
    if(boolvalue < 0){
        boolvalue = 0;
    }
    return boolvalue;
}

int sort_by_number_of_distinct_characters(const char* a, const char* b) {
    int distinct1 = 0;
    int distinct2 = 0;
    char* presentchars1 = malloc(sizeof(char) * (strlen(a)+1));
    for(int i = 0;i<strlen(a);i++){
        presentchars1[i] = '\0';
    }
    char* presentchars2 = malloc(sizeof(char) * (strlen(b)+1));
    for(int i = 0;i<strlen(b);i++){
        presentchars2[i] = '\0';
    }
    for(int i = 0;i<strlen(a);i++){
        if(arr_contains_char(a,&a[i],strlen(presentchars1))){
            continue;
        }
        presentchars1[distinct1] = a[i];
        distinct1++;
    }
    free(presentchars1);
    for(int i = 0;i<strlen(b);i++){
        if(arr_contains_char(b,&b[i],strlen(presentchars2))){
            continue;
        }
        presentchars2[distinct2] = b[i];
        distinct2++;
    }
    free(presentchars2);
    if(distinct2 > distinct1){
        return 0;
    }else if(distinct1 > distinct2){
        return 1;
    }
    else if(distinct1 == distinct2){
        return lexicographic_sort(a, b);
    }
    return -1;
}

int sort_by_length(const char* a, const char* b) {
    if(strlen(a) < strlen(b)){
        return 0;
    }
    else if(strlen(b) < strlen(a)){
        return 1;
    }
    else if(strlen(b) == strlen(a)){
        return lexicographic_sort(a, b);
    }
    return -1;
}

void string_sort(char** arr,const int len,int (*cmp_func)(const char* a, const char* b)){
    char** untouched = malloc(sizeof(char*) * len);
    for(int i = 0;i<len;i++){
        untouched[i] = malloc(sizeof(char) * (strlen(arr[i])+1));
        untouched[i] = arr[i];
    }
    for(int i = 0;i<len;i++){
        int greater_than = 0;
        for(int j = 0;j<len;j++){
            if(i == j){
                continue;
            }
            if(cmp_func(untouched[i],untouched[j])){
                greater_than++;
            }
        }
        arr[greater_than] = untouched[i];
    }
    free(untouched);
}


int main() 
{
    int n;
    scanf("%d", &n);
  
    char** arr;
	arr = (char**)malloc(n * sizeof(char*));
  
    for(int i = 0; i < n; i++){
        *(arr + i) = malloc(1024 * sizeof(char));
        scanf("%s", *(arr + i));
        *(arr + i) = realloc(*(arr + i), strlen(*(arr + i)) + 1);
    }
  
    string_sort(arr, n, lexicographic_sort);
    for(int i = 0; i < n; i++)
        printf("%s\n", arr[i]);
    printf("\n");

    string_sort(arr, n, lexicographic_sort_reverse);
    for(int i = 0; i < n; i++)
        printf("%s\n", arr[i]); 
    printf("\n");

    string_sort(arr, n, sort_by_length);
    for(int i = 0; i < n; i++)
        printf("%s\n", arr[i]);    
    printf("\n");

    string_sort(arr, n, sort_by_number_of_distinct_characters);
    for(int i = 0; i < n; i++)
        printf("%s\n", arr[i]); 
    printf("\n");
    getch();
}