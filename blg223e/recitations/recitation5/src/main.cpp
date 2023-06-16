/*
PLEASE DO NOT CHANGE THIS FILE, OTHERWISE YOUR CODE WILL NOT BE EVALUATED AND WILL BE GRADED AS 0 
*/

#include <iostream> 

#include "StudentsTrie.h"

using namespace std;

int main(int argc, char* argv[]){
	//system("clear");// make this line as comment if you are compiling on Windows 
	//system("cls"); // make this line as comment if you are compiling on Linux or Mac

    StudentsTrie st(argv[1]); 

    st.print_trie();

	return EXIT_SUCCESS;
}


