/* @Author
Student Name: Furkan Salık
Student ID : 150200056
Date: 14/12/2021 */

// PLEASE DO NOT REMOVE DECLARED VARIBLES AND FUNCTIONS OF CLASSES, IF YOU PREFER, YOU CAN ADD NEW ONES
#ifndef _H
#define _H

using namespace std;

#define ARRAY_SIZE 100 // This is max length of token array, Do not worry about longer case. 
class Token{
    public:
        string symbol; // To store character or symbol
        string code;   // To store encoded version of symbol
        int count=0;   // To store frequency of symbol
};

class Node{
    public:
        Token token;  // To store token
        Node *left;   // To use in binary tree
        Node *right;  // To use in binary tree
        Node *next = NULL;   // To use in priority queue
};

class PriorityQueue{
    public:
        Node * head;
        Node * tail;
        void push(Node*);
        int token_count;
        PriorityQueue();
        Node *pop();
};

class HuffmanBinaryTree{
    public:
        Node * root;
        HuffmanBinaryTree();
        Node *merge(Node*,Node*);                      // To merge two nodes and place the new node conveniently 
        void delete_postorder_traversal(Node *);	 // To release allocated memory
        ~HuffmanBinaryTree();                           
};


class Huffman{
    public:
        int token_count=0;                               // To store number of token
        Token token_array[ARRAY_SIZE];                   // To store tokens that includes symbol, corresponding code and frequency  
        PriorityQueue priority_queue;                    // To store priority queue
        HuffmanBinaryTree huffman_binary_tree;           // To store huffman binary tree
        void find_frequencies();                         // It reads symbols from 'input.txt' file and count frequecy of each symbol 
        void get_priority_queue();			   // It constructs the priority queue
        void get_huffman_tree();			   // It constructs the huffman tree 	
        void get_codes(Node*,string);			   // It extract code for each symbol according to the huffman tree	
        double calculate_compression_ratio();            // It calculates the compression ratio
        string return_code(string);			   // It returns the code of given string
    
    private:
        int findindex(Token *,string);                   // It returns the index of given string parameter in Token array
};
#endif
