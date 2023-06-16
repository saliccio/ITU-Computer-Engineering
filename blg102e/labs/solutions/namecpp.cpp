#include <stdio.h>
#include <stdlib.h>
#include <string.h>

class Name{
private:
	char value[100];
public:
	Name(const char* p){
		strcpy(value, p);
	}
	
	~Name(){
		
	}
	
	void display(){
		printf("%s\n", value); 
	}
	
	void reverse(){
		char temp[100];
		strcpy(temp, value);
		size_t length = strlen(value);
		for(int i = 0; i < length; i++){
			temp[length - i - 1] = value[i];
		}
		strcpy(value, temp);
	}
};

int main(){
	Name myName("nese");
	
	myName.display();
	myName.reverse();
	myName.display();
	
	return 0;
}