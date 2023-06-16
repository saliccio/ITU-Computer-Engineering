#include <stdio.h>
#include <stdlib.h>

class List{
private:
	typedef struct Node{
		Node* next;
		int value;
	} Node;
	Node* startNode;
	Node* currentNode;
public:
	List(){
		startNode = (Node*) malloc(sizeof(Node));
		currentNode = startNode;
	}
	
	~List(){
		free(startNode);
	}
	
	void push(int val){
		currentNode->next = (Node*) malloc(sizeof(Node));
		currentNode = currentNode->next;
		currentNode->value = val;
	}
	
	void display(){
		printf("%d - ", currentNode->value);
	}
	
	void pop(){
		Node* cNode = startNode;
		while(1){
			if(cNode->next == currentNode){
				currentNode = cNode;
				free(cNode->next);
				cNode->next = NULL;
				break;
			}
			cNode = cNode->next;
		}
	}
};

int main(){
	List mylist;
	
	for (int k = 0; k < 100; k++){
		mylist.push(k);
		mylist.display();
	}
	
	for (int k = 0; k < 90; k++){
		mylist.pop();
		mylist.display();
	}
	printf("\n");
	
	return 0;
}