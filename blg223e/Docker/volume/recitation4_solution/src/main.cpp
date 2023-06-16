/*
PLEASE DO NOT CHANGE THIS FILE, OTHERWISE YOUR CODE WILL NOT BE EVALUATED AND WILL BE GRADED AS 0 
*/

#include <iostream> 
#include <stdlib.h>
#include <iomanip>
#include <string.h>

#include "huffman.h"

using namespace std;

Huffman huff;

void print_menu();
bool perform_operation(char);
void run_huffman();
void get_code_of();
void print_calculate_compression_ratio();

int main(int argc, char* argv[]){
	system("clear");// make this line as comment if you are compiling on Windows 
	//system("cls"); // make this line as comment if you are compiling on Linux or Mac
	bool end = false; 
	char choice; 	
	while (!end) { 
		print_menu(); 
		cin >> choice;
		end = perform_operation(choice); 
		}

	return EXIT_SUCCESS;
}

void get_code_of(){
    string symbol;
	cout << "Type symbol whose code that you want to see: ";
	cin >> symbol; 
	cout<<"Code of "<<symbol<<" is "<<huff.return_code(symbol)<<endl;
}

void run_huffman(){
	huff.find_frequencies();
	//huff.print_frequencies_and_codes();
	huff.get_priority_queue();
	huff.get_huffman_tree();
	huff.get_codes(huff.huffman_binary_tree.root,"");
	//huff.print_frequencies_and_codes();	
}

void print_calculate_compression_ratio(){
	cout<<"Compression ratio is "<<huff.calculate_compression_ratio()<<endl;
}

void print_menu(){
	cout << endl << endl;
	cout << "THE APPLICATION OF HUFFMAN ALGORITHM" << endl;
	cout << "Choose an operation" << endl;
	cout << "R: Run Huffman" << endl;
	cout << "G: Get Code of Given Symbol" << endl;
	cout << "C: Calculate Compression Ration" << endl;
	cout << "E: Exit" << endl;	
	cout << endl;
	cout << "Enter a choice {R,G,C,E}: ";
}
bool perform_operation(char choice){
	bool terminate=false;
	switch (choice) {	 
		case 'R': case 'r': 
			run_huffman();
			break;
		case 'G': case 'g': 
			get_code_of();
			break;	
		case 'C': case 'c': 
			print_calculate_compression_ratio();
			break;	
		case 'E': case 'e': 
			cout << "Are you sure you want to exit the program? (Y/N):";
			cin >> choice;
			if(choice=='Y' || choice=='y')
				terminate=true; 
			break; 
		default: 
			cout << "Error: You have entered an invalid choice" << endl; 
			cout << "Please try again {D,M,E}  :" ;
			cin >> choice;
			terminate = perform_operation(choice);
			break; 
	}
	return terminate;
}